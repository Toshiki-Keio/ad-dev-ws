import serial
import numpy as np
import time
# Nodeクラスを継承
class InfraredSensor:
    def __init__(self):
        # Node.__init__を引数node_nameにtalkerを渡して継承
        self.count = 0
        self.ser = serial.Serial('/dev/ttyACM0', 9600) # シリアルポートの設定に注意
        # Node.create_publisher(msg_type, topic)に引数を渡してpublisherを作成
        self.time_period = 0.03

    def getInfraredData(self):
        self.count += 1
        # std_msgs.msg.Stringのインスタンス化
        data = []
        for element in self.ser.readline().decode().strip().split(','):
            data.append(int(element))
        data = list(reversed(data))
        print(data)

if __name__ == "__main__":
    infrared_sensor = InfraredSensor()
    try:
        while True:
            infrared_sensor.getInfraredData()
            time.sleep(infrared_sensor.time_period)
    except:
        print("Something error occured")
        pass
