#include <iostream>

#include "add.h"


/**
 * \file main.cpp
 * \brief ������� ����������� ���� ��������� ��������� �����������.
 */


 /**
  * \brief ������� ������� ���������.
  * \param argc ���������� ���������� ��������� ������.
  * \param argv ������ ���������� ��������� ������.
  * \return ���������� 0 � ������ ������, 1 � ������ ������.
  *
  * ��������� ��������� ���� � ����������� � ������ ������� ('demo' ��� 'vis').
  * � ����������� �� ������� ����������� ��������������� ����� ������ � ������������.
  */
int main(int argc, char* argv[]) {

    

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
 
    if (argc < 4) {
        std::cerr << "Usage: <path_from> <path_to> <command>\n";
        return 1;
    }
    std::string path_rom = argv[1];
    std::string path_to = argv[2];
    std::string command = argv[3];
    cv::Mat img;

    bool imageLoadedSuccessfully = false;
    
        try {
            img = loadImage(path);
            imageLoadedSuccessfully = true;
        }
        catch (const std::exception& e) {
            std::cerr << "Try again \n";
            return 1;
      
        }
    


    cv::Mat binaryImage;
    threshold(img, binaryImage, 210, 255, cv::THRESH_BINARY);

    cv::Mat imgWithWhiteBg;
    imgWithWhiteBg = toWhiteBackground(binaryImage);

    cv::Mat distanceTransformedImg;
    distanceTransformedImg = distanceTransform(imgWithWhiteBg);

   

    if (command != "demo" && command != "vis")
        std::cout << "No comand " << command << ". Try again\n";
    else if (command == "demo") {
      
        bool isSuccess1 = cv::imwrite("../../result/binimage.jpg", binaryImage); 
        bool isSuccess2 = cv::imwrite("../../result/dtimage.jpg", distanceTransformedImg); 


        if ( isSuccess2) {
            std::cout << "Images saved successfully." << std::endl;
        }
        else {
            std::cout << "Error: Failed to save the image." << std::endl;
        }

    }
    else if (command == "vis")
    {
        try {
            generateLaTeXCode(distanceTransformedImg, "../../result/test.tex");
            std::cout << "Latex file saved successfully." << std::endl;
        }
        
        catch (const std::exception& e) {
            std::cout << "Error: Failed to save the Latex file." << std::endl;
           
        }
    }





    return 0;
}