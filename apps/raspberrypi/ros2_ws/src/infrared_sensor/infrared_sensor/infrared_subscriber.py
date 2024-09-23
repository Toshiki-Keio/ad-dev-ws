import rclpy
from rclpy.node import Node
from std_msgs.msg import String,Int32

# Nodeクラスを継承
class Listener(Node):
    def __init__(self):
        # 引数node_nameにlistenerを渡す。
        super().__init__("infrared_subscriber")

        # 引数msg_type、topic_name、callbackに渡してSubscriptionを作成
        self.create_subscription(Int32, "rover", self.callback,10)

    # 処理用callback関数
    def callback(self, msg):
        print(msg.data)


def main():
    # RCLの初期化を実行
    rclpy.init()

    # Listenerクラスのコンスタンス化
    node = Listener()

    # ループに入りnode内の処理を実行させる
    rclpy.spin(node)

    # nodeを破壊
    node.destroy_node()

    # RCLをシャットダウン
    rclpy.shutdown()

if __name__ == "__main__":
    main()
