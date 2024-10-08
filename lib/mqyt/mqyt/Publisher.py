#!/usr/bin/env python
import paho.mqtt.client as mqtt     # MQTTのライブラリをインポート
from time import sleep
import cv2
import os
import json
import base64

class Publisher:
    """
    a publisher of mqtt topic message

    host: mqtt host
    port: port number
    """

    def __init__(self, host='broker.emqx.io', port=1883):
        # MQTTの接続設定
        self.client = mqtt.Client()                 # クラスのインスタンス(実体)の作成
        self.client.on_connect = self.on_connect         # 接続時のコールバック関数を登録
        self.client.on_disconnect = self.on_disconnect   # 切断時のコールバックを登録
        self.client.on_publish = self.on_publish         # メッセージ送信時のコールバック
        
        self.client.connect(host, port, 60)  # 接続先はMQTTサーバー
        sleep(0.2)

        # 通信処理スタート
        self.client.loop_start()    # subはloop_forever()だが，pubはloop_start()で起動だけさせる
        
    # ブローカーに接続できたときの処理
    def on_connect(self, client, userdata, flag, rc):
        print("Connected with result code " + str(rc))

    # ブローカーが切断したときの処理
    def on_disconnect(self, client, userdata, rc):
        if rc != 0:
            print("Unexpected disconnection.")

    # publishが完了したときの処理
    def on_publish(self, client, userdata, mid):
        print("publish: {0}".format(mid))
        self.finish_publication = True

    def publish(self, topic, type, msg):
        """
        publish msg to remote server

        topic: topic name
        type: message type ("txt" or "img")
        msg: published msg
        """
        self.finish_publication = False
        if type == "txt":
            self.client.publish(topic, msg)    # トピック名とメッセージを決めて送信
        elif type == "txtarray":
            msg_json = json.dumps(msg)
            self.client.publish(topic, msg_json)    # トピック名とメッセージを決めて送信
        elif type == "img":
            # msg: ndarray
            ret, dst_data = cv2.imencode('.jpg', msg)
            dst_str = base64.b64encode(dst_data)
            data = "data:image/jpg;base64," + dst_str.decode()
            self.client.publish(topic, data)    # トピック名とメッセージを決めて送信
        else:
            assert False, "invalid type"
        # wait
        while(not self.finish_publication):
            pass
        
if __name__ == "__main__":

    publisher = Publisher()
    count=0
    while True:
        publisher.publish("topic_pub", "txt", count)
        count+=1
        sleep(1)
