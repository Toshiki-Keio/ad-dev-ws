#include <iostream>
#include <vector>
#include <linux/serial.h>  // 必要な場合はインストール
// #include <sstream>
#include <unistd.h>         // usleep関数を使うため

class InfraredSensor {
public:
    InfraredSensor() : count(0), time_period(30000) {  // time_periodはマイクロ秒
        try {
            ser.setPort("/dev/ttyACM0");
            ser.setBaudrate(9600);
            serial::Timeout to = serial::Timeout::simpleTimeout(1000);
            ser.setTimeout(to);
            ser.open();
        }
        catch (serial::IOException& e) {
            std::cerr << "Unable to open port" << std::endl;
        }
        if(ser.isOpen()) {
            std::cout << "Serial Port initialized" << std::endl;
        }
        else {
            std::cerr << "Serial Port not opened" << std::endl;
        }
    }

    void getInfraredData() {
        count++;
        std::string line;
        if(ser.available()) {
            line = ser.readline();
            std::vector<int> data = processLine(line);
            std::reverse(data.begin(), data.end());
            printData(data);
        }
    }

private:
    serial::Serial ser;
    int count;
    int time_period;  // マイクロ秒単位
    std::vector<int> processLine(const std::string& line) {
        std::vector<int> data;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            try {
                data.push_back(std::stoi(token));
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid data: " << token << std::endl;
            }
        }
        return data;
    }

    void printData(const std::vector<int>& data) {
        std::cout << "[ ";
        for (int d : data) {
            std::cout << d << " ";
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    InfraredSensor infrared_sensor;
    try {
        while (true) {
            infrared_sensor.getInfraredData();
            usleep(infrared_sensor.time_period);  // time_periodはマイクロ秒
        }
    }
    catch (...) {
        std::cerr << "Something error occurred" << std::endl;
    }
    return 0;
}
