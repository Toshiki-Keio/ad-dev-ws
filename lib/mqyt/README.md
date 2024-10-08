# mqyt

mqyt is a Python Library for communication among local scripts and remote server via MQTT.

## Installation

### for user

```shell
pip install git+https://github.com/Takahashi-Lab-Keio/mqyt.git
```
### for developer

```shell
git clone git@github.com:Takahashi-Lab-Keio/mqyt.git
cd mqyt
pip install -e .
```

Using this installation method, the mqyt module is synchronized to the local mqyt code.

## Tutorial
### Publisher

```python
import mqyt

# create publisher instance
publisher = mqyt.Publisher()

# publish message
# port (optional): connection port number (1883 if TCP connection)
# host (optional): host name
# type: "txt" (str) or "img" (numpy.ndarray)
# msg: published data, topic: topic name
publisher.publish(port=1883, host="broker.emqx.io", type="txt", msg="ytlab", topic="topic_pub")
```
### Subscriber

```python
import mqyt

# callback function that called when the topic is subscribed
def callback(msg):
    print("calback_result", msg)

if __name__ == "__main__":
    # create subscriber instance
    # port (optional): connection port number (1883 if TCP connection)
    # host (optional): host name
    # type: "txt" (str) or "img" (numpy.ndarray)
    # callback: callback function, topic: topic name
    # endless: True or False. 
    ## Set True if you don't want to shutdown the program.
    ## Set False if there is another loops and program does not shutdown.
    subscriber = mqyt.Subscriber(port=1883, host="broker.emqx.io", type="txt", callback=callback, topic="topic_sub", endless=True)

```

## Sample application
https://github.com/Takahashi-Lab-Keio/ytlab_IoT_robotics

## License
Copyright &copy; 2022 Takahashi Lab.
Licensed under the MIT license.
