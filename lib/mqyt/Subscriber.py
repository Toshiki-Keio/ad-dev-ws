#!/usr/bin/env python
import paho.mqtt.client as mqtt     # MQTTのライブラリをインポート
import numpy as np
import cv2
import json
import base64

class Subscriber:
    """
    a subscriber of mqtt topic message

    topic: topic name
    type: message type ("txt" or "img")
    func: callback function
    host: mqtt host
    port: port number
    """

    def __init__(self, topic, type, callback, endless, host='broker.emqx.io', port=1883):
        self.func = callback
        self.type = type
        self.topic = topic

        # MQTTの接続設定
        self.client = mqtt.Client()                 # クラスのインスタンス(実体)の作成
        self.client.on_connect = self.on_connect         # 接続時のコールバック関数を登録
        self.client.on_disconnect = self.on_disconnect   # 切断時のコールバックを登録
        self.client.on_message = self.callback         # メッセージ到着時のコールバック

        self.client.connect(host, port, 60)  # 接続先はMQTTサーバー
        
        # 通信処理スタート
        if endless:
            self.client.loop_forever()                  # 永久ループして待ち続ける
        else:
            self.client.loop_start()                  # 永久ループして待ち続ける
        
    # ブローカーに接続できたときの処理
    def on_connect(self, client, userdata, flag, rc):
        print("Connected with result code " + str(rc))  # 接続できた旨表示
        client.subscribe(self.topic)  # subするトピックを設定 

    # ブローカーが切断したときの処理
    def on_disconnect(self, client, userdata, rc):
        if  rc != 0:
            print("Unexpected disconnection.")

    # メッセージが届いたときの処理
    def callback(self, client, userdata, msg):
        # msg.topicにトピック名が，msg.payloadに届いたデータ本体が入っている
        # print("Received message '" + str((msg.payload).decode('utf-8')) + "' on topic '" + msg.topic + "' with QoS " + str(msg.qos))
        if self.type == "txt":
            msg_str = str((msg.payload).decode('utf-8'))
            self.func(msg_str)
        elif self.type == "txtarray":
            msg_json = json.loads(msg.payload)
            self.func(msg_json)
        elif self.type == "img":
            img_binary = base64.b64decode(msg.payload[len("data:image/jpg;base64,"):])
            jpg=np.frombuffer(img_binary,dtype=np.uint8)
            img = cv2.imdecode(jpg, cv2.IMREAD_COLOR)
            self.func(img)
        else:
            assert False, "invalid type"

def callback(msg):
    print("callback result", msg)

if __name__ == "__main__":

    subscriber = Subscriber("topic_pub", "txt", callback, endless = True)
