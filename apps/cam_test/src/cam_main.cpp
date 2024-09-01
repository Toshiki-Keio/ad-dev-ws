#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "カメラを開けませんでした。" << std::endl;
        return -1;
    }

    // 解像度を設定（例：640x480）
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    // フレームレートを設定（例：30 fps）
    cap.set(cv::CAP_PROP_FPS, 30);

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "フレームの取得に失敗しました。" << std::endl;
            break;
        }

        // 現在の解像度とフレームレートを表示
        std::cout << "解像度: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << "x"
                  << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
        std::cout << "フレームレート: " << cap.get(cv::CAP_PROP_FPS) << std::endl;

        cv::imwrite('test.jpg', frame)

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
