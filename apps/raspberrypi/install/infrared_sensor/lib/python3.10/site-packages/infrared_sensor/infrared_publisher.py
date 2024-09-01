import rclpy
from rclpy.node import Node
from std_msgs.msg import String,Float32,Int32,Int32MultiArray
import serial
import numpy as np

# Nodeクラスを継承
class Talker(Node):
    def __init__(self):
        # Node.__init__を引数node_nameにtalkerを渡して継承
        super().__init__("infrared_publisher")
        self.count = 0

        self.ser = serial.Serial('/dev/ttyACM0', 9600) # シリアルポートの設定に注意

        # Node.create_publisher(msg_type, topic)に引数を渡してpublisherを作成
        self.pub = self.create_publisher(Int32MultiArray, "infrared_sensor",10)
        self.time_period = 0.03

        # Node.create_timer(timer_period_sec, callback)に引数を渡してタイマーを作成
        self.tmr = self.create_timer(self.time_period, self.callback)

    def callback(self):
        self.count += 1

        # std_msgs.msg.Stringのインスタンス化
        msg = Int32MultiArray()

        data = []
        for element in self.ser.readline().decode().strip().split(','):
            data.append(int(element))

        data = list(reversed(data))

        # msg.dataにデータを格納
        msg.data = data

        # Node.get_logger().info(message)で表示したい内容を引数messageに渡す
        self.get_logger().info("Infrared sensor states: {0}".format(msg.data))

        # msgを公開
        self.pub.publish(msg)


def main():
    # rclpy.init()でRCLを初期化
    rclpy.init()

    # Nodeのインスタンス化
    node = Talker()

    # Node処理をループさせ実行
    rclpy.spin(node)

    # Nodeを破壊
    node.destroy_node()

    # RCLを終了
    rclpy.shutdown()

if __name__ == "__main__":
    main()
