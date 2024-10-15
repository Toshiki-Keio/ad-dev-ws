from infrared_sensor import InfraredSensor
import time

import sys
import os
lib_path = os.path.abspath(os.path.join(__file__, "../../../../lib"))
# sys.pathにlibフォルダのパスを追加
sys.path.append(lib_path)

from mqyt.Publisher import Publisher

if __name__ == "__main__":
    infrared_sensor = InfraredSensor()
    publisher = Publisher()
    count=0

    try:
        while True:
            infrared_sensor.getInfraredData()
            publisher.publish("topic_pub", "txt", count)
            count+=1
            time.sleep(1)
    except:
        print("Something error occured")
        pass