#include <iostream>

#include "add.h"

//using namespace cv;





int main() {

    std::cout << "Enter the path to image (only jpg, jpeg or png and only Latin words) \n";
    std::string path;
    std::getline(std::cin, path);

    cv::Mat img;

    bool imageLoadedSuccessfully = false;
    while (!imageLoadedSuccessfully) {
        try {
            img = loadImage(path);
            imageLoadedSuccessfully = true;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << ". Try again \n";
            std::cin >> path;
        }
    }


    cv::Mat binaryImage;
    threshold(img, binaryImage, 210, 255, cv::THRESH_BINARY);

    cv::Mat imgWithWhiteBg;
    imgWithWhiteBg = toWhiteBackground(binaryImage);

    cv::Mat distanceTransformedImg;
    distanceTransformedImg = distanceTransform(imgWithWhiteBg);


    std::cout << "If you whant demonstation enter 'demo' if you whant visualisation enter 'vis'\n";
    std::string comand;
    std::getline(std::cin, comand);


    if (comand != "demo" && comand != "vis")
        std::cout << "No comand " << comand << ". Try again\n";
    else if (comand == "demo") {
        cv::namedWindow("First OpenCV Application", cv::WINDOW_AUTOSIZE);
        cv::imshow("First OpenCV Application", distanceTransformedImg);
        cv::moveWindow("First OpenCV Application", 0, 45);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }
    else if (comand == "vis")
    {
        generateLaTeXCode(distanceTransformedImg, "test.tex");
    }





    return 0;
}