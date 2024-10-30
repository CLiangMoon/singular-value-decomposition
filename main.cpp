// #include <iostream>
// #include <opencv2/opencv.hpp>

// void compressImage(const cv::Mat& input, int k) {
//     // 创建一个与输入图像相同大小的压缩图像
//     cv::Mat compressedImage = cv::Mat::zeros(input.size(), input.type());
//     cv::Mat U, S, Vt;
//     // 对每个颜色通道进行SVD分解
//     for (int c = 0; c < 3; ++c) {
//         cv::Mat channel;
//         cv::extractChannel(input, channel, c);

//         // 将通道转换为浮点型
//         cv::Mat channelFloat;
//         channel.convertTo(channelFloat, CV_32F);

//         // 进行SVD分解
//         cv::SVD::compute(channelFloat, S, U, Vt);

//         // 只保留前k个奇异值
//         cv::Mat Sk = cv::Mat::zeros(k, k, CV_32F);
//         for (int i = 0; i < k; ++i) {
//             Sk.at<float>(i, i) = S.at<float>(i);
//         }

//         // 重构图像
//         cv::Mat compressedChannel = U.colRange(0, k) * Sk * Vt.rowRange(0, k);

//         // 转换回8位无符号整数
//         cv::Mat compressedChannel8U;
//         compressedChannel.convertTo(compressedChannel8U, CV_8U);

//         // 将重构的通道放回压缩图像中
//         cv::insertChannel(compressedChannel8U, compressedImage, c);
//     }

//     std::cout<<"原本图像的奇异值数："<<std::endl;
//     //std::cout<<S;
//     int original_v = S.rows;
//     std::cout<<original_v<<std::endl;
    
//     // 显示原始和压缩后的图像
//     cv::imshow("Original Image", input);
//     cv::imshow("Compressed Image", compressedImage);
//     cv::waitKey(0);
// }

// int main() {
//     // std::string imagePath;
//     // std::cout << "请输入图像路径: ";
//     // std::cin >> imagePath;

//     // 读取彩色图像
//     cv::Mat image = cv::imread("../2.png", cv::IMREAD_COLOR);
//     if (image.empty()) {
//         std::cerr << "无法读取图像!" << std::endl;
//         return -1;
//     }

//     int k;
//     std::cout << "请输入要保留的奇异值个数: ";
//     std::cin >> k;

//     // 确保k不超过图像的最小维度
//     k = std::min(k, std::min(image.rows, image.cols));

//     compressImage(image, k);

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

void compressImage(const cv::Mat& input, double energyThreshold) {
    // 创建一个与输入图像相同大小的压缩图像
    cv::Mat compressedImage = cv::Mat::zeros(input.size(), input.type());

    // 对每个颜色通道进行SVD分解
    for (int c = 0; c < 3; ++c) {
        cv::Mat channel;
        cv::extractChannel(input, channel, c);

        // 将通道转换为浮点型
        cv::Mat channelFloat;
        channel.convertTo(channelFloat, CV_32F);

        // 进行SVD分解
        cv::Mat U, S, Vt;
        cv::SVD::compute(channelFloat, S, U, Vt);

        // 计算累积能量
        double totalEnergy = cv::sum(S)[0];
        double currentEnergy = 0;
        int k = 0;

        // 找到满足能量阈值的奇异值个数
        while (k < S.rows && (currentEnergy / totalEnergy) < energyThreshold) {
            currentEnergy += S.at<float>(k);
            k++;
        }
        
        if(c==2) 
        {  
            std::cout<<"匹配的奇异值数："<<k<<std::endl;
            std::cout<<"原本图像的奇异值数: "<<S.rows<<std::endl;
        }
        // 只保留前k个奇异值
        cv::Mat Sk = cv::Mat::zeros(k, k, CV_32F);
        for (int i = 0; i < k; ++i) {
            Sk.at<float>(i, i) = S.at<float>(i);
        }

        // 重构图像
        cv::Mat compressedChannel = U.colRange(0, k) * Sk * Vt.rowRange(0, k);

        // 转换回8位无符号整数
        cv::Mat compressedChannel8U;
        compressedChannel.convertTo(compressedChannel8U, CV_8U);

        // 将重构的通道放回压缩图像中
        cv::insertChannel(compressedChannel8U, compressedImage, c);
    }

    // 显示原始和压缩后的图像
    cv::imshow("Original Image", input);
    cv::imshow("Compressed Image", compressedImage);
    cv::waitKey(0);
}

int main() {
    // std::string imagePath;
    // std::cout << "请输入图像路径: ";
    // std::cin >> imagePath;

    // 读取彩色图像
    cv::Mat image = cv::imread("../2.png", cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "无法读取图像!" << std::endl;
        return -1;
    }

    // 设置能量阈值（例如，95%）
    double energyThreshold = 0.95;

    compressImage(image, energyThreshold);

    return 0;
}
