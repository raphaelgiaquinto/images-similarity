#include "main.hpp"


int main(int argc, char** argv) {

    if(argc < 3) {
        return EXIT_FAILURE;
    }

    cv::Mat im0;
    cv::MatND hist_im0;

    cv::Mat im1;
    cv::MatND hist_im1;

    im0 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    im1 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);

    float hranges[] = { 0, 255 };
    const float* ranges[] = {hranges};
    int channels[] = {0};
    int hist_size[] = {255};

    cv::calcHist(&im0, 1, channels, cv::Mat(), hist_im0, 1, hist_size, ranges, true, false);
    cv::calcHist(&im1, 1, channels, cv::Mat(), hist_im1, 1, hist_size, ranges, true, false);

    double diff = cv::compareHist( hist_im0, hist_im1, cv::HISTCMP_HELLINGER );

    std::cout << "| 0 same " << std::endl;
    std::cout << "| ~ 0.1 similar " << std::endl;
    std::cout << "| 0.2 - 0.3 really similar " << std::endl;
    std::cout << "| 0.3 - 0.5 approximately similar " << std::endl;
    std::cout << "| 0.5 - 0.8 quite different " << std::endl;
    std::cout << "| > 0.8 much different " << std::endl;

    std::cout << "Distance between images (hellinger distance): " << std::fixed << diff << std::endl;
   
    return EXIT_SUCCESS;
}