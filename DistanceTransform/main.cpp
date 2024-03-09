#include <iostream>

#include "add.h"

//using namespace cv;





int main(int argc, char* argv[]) {

    /*
    std::cout << "Enter the path to image (only jpg, jpeg or png and only Latin words) \n";
    std::string path;
    std::getline(std::cin, path);
    */

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <path> <string>\n";
        return 1;
    }
    std::string path = argv[1];
    std::string command = argv[2];
    cv::Mat img;

    bool imageLoadedSuccessfully = false;
    
        try {
            img = loadImage(path);
            imageLoadedSuccessfully = true;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << ". Try again \n";
      
        }
    


    cv::Mat binaryImage;
    threshold(img, binaryImage, 210, 255, cv::THRESH_BINARY);

    cv::Mat imgWithWhiteBg;
    imgWithWhiteBg = toWhiteBackground(binaryImage);

    cv::Mat distanceTransformedImg;
    distanceTransformedImg = distanceTransform(imgWithWhiteBg);

    /*
    std::cout << "If you whant demonstation enter 'demo' if you whant visualisation enter 'vis'\n";
    std::string comand;
    std::getline(std::cin, comand);
    */

    if (command != "demo" && command != "vis")
        std::cout << "No comand " << command << ". Try again\n";
    else if (command == "demo") {
        /*
        cv::namedWindow("First OpenCV Application", cv::WINDOW_AUTOSIZE);
        cv::imshow("First OpenCV Application", distanceTransformedImg);
        cv::moveWindow("First OpenCV Application", 0, 45);
        cv::waitKey(0);
        cv::destroyAllWindows();
        */
        bool isSuccess = cv::imwrite("../../out/image.jpg", distanceTransformedImg); 

        if (isSuccess) {
            std::cout << "Image saved successfully." << std::endl;
        }
        else {
            std::cout << "Error: Failed to save the image." << std::endl;
        }

    }
    else if (command == "vis")
    {
        bool isSuccess = generateLaTeXCode(distanceTransformedImg, "../../out/test.tex");
        if (isSuccess) {
            std::cout << "Latex file saved successfully." << std::endl;
        }
        else {
            std::cout << "Error: Failed to save the Latex file." << std::endl;
        }
    }





    return 0;
}