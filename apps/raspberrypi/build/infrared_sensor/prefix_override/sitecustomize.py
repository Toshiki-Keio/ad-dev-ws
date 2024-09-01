import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/ubuntu/ad-dev-ws/apps/raspberrypi/install/infrared_sensor'
