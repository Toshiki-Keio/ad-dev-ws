#include <iostream>
#include <linux/serial.h>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <algorithm> // std::reverseを使うために必要

class InfraredSensor {
public:
    InfraredSensor() : count(0), time_period(30) {
        // シリアルポートの設定
        try {
            ser.setPort("/dev/ttyACM0");
            ser.setBaudrate(9600);
            ser.open();
        } catch (const std::exception &e) {
            std::cerr << "Error opening serial port: " << e.what() << std::endl;
            exit(1);
        }
    }

    ~InfraredSensor() {
        if (ser.isOpen()) {
            ser.close();
        }
    }

    void getInfraredData() {
        count++;
        std::string line;
        if (ser.available()) {
            line = ser.readline(ser.available(), "\n");
            std::vector<int> data = parseData(line);
            std::reverse(data.begin(), data.end());
            printData(data);
        }
    }

private:
    int count;
    int time_period; // ミリ秒
    serial::Serial ser; // serial::Serialをメンバーとして定義

    std::vector<int> parseData(const std::string &line) {
        std::vector<int> data;
        std::stringstream ss(line);
        std::string item;

        while (std::getline(ss, item, ',')) {
            data.push_back(std::stoi(item));
        }
        return data;
    }

    void printData(const std::vector<int> &data) {
        for (const int &value : data) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    InfraredSensor infrared_sensor;
    while (true) {
        infrared_sensor.getInfraredData();
        std::this_thread::sleep_for(std::chrono::milliseconds(infrared_sensor.time_period));
    }
    return 0;
}
