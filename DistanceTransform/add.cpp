#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include <iostream>
#include <string>
//using namespace cv;
uchar inf = 255;

//using namespace std;
//D:/imagesCV/mouse.jpg


cv::Mat loadImage(std::string s) {
    cv::Mat img = cv::imread(s, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        throw std::runtime_error("Failed to load image from path: " + s);
    }
    return img;

}

cv::Mat toWhiteBackground(cv::Mat img) {
    cv::Mat invertedImg;
    int totalPixels = img.total();
    int whitePixels = cv::countNonZero(img);
    int blackPixels = totalPixels - whitePixels;
    if (blackPixels > whitePixels) {
        cv::bitwise_not(img, invertedImg);
        return invertedImg;
    }
    return img;

}

cv::Mat distanceTransform(cv::Mat img) {
    double m1 = 1;
    double m2 = 2;
    int rows = img.rows;
    int cols = img.cols;
    int type = img.type();

    cv::Mat dstr(cv::Size(cols, rows), type);
    //top to bottom
    for (int j = 0; j < cols; j++) {
        //left to right
        for (int i = 0; i < rows; i++) {
            //if pixel is background
            if (img.at<uchar>(i, j) > 0) {
                dstr.at<uchar>(i, j) = 0;

            }
            //if pixel is fg
            else {
                uchar d0 = inf;
                uchar d1 = inf;
                uchar d2 = inf;
                uchar d3 = inf;
                if (i > 0) {
                    d0 = m1 + dstr.at<uchar>(i - 1, j);
                    if (j > 0) {
                        d1 = m2 + dstr.at<uchar>(i - 1, j - 1);

                    }

                }
                if (j > 0) {
                    d2 = m1 + dstr.at<uchar>(i, j - 1);
                    if (i < (rows - 1)) {
                        d3 = m2 + dstr.at<uchar>(i + 1, j - 1);
                    }
                }

                dstr.at<uchar>(i, j) = std::min({ d0, d1, d2, d3 });

            }


        }
    }


    // bottom to top and right to left   
    for (int j = cols - 1; j >= 0; j--) {
        for (int i = rows - 1; i >= 0; i--) {

            if (dstr.at<uchar>(i, j) > 0) {

                uchar d0 = inf;
                uchar d1 = inf;
                uchar d2 = inf;
                uchar d3 = inf;
                if (i < rows - 1) {
                    d0 = m1 + dstr.at<uchar>(i + 1, j);
                    if (j < cols - 1) {
                        d1 = m2 + dstr.at<uchar>(i + 1, j + 1);
                    }
                }
                if (j < cols - 1) {
                    d2 = m1 + dstr.at<uchar>(i, j + 1);
                    if (i > 0) {
                        d3 = m2 + dstr.at<uchar>(i - 1, j + 1);
                    }
                }

                dstr.at<uchar>(i, j) = std::min({ dstr.at<uchar>(i, j), d0, d1, d2, d3 });


            }
        }
    }

    return dstr;
}


void generateLaTeXCode(const cv::Mat& image, const std::string& latexFilename) {
    std::ofstream latexFile(latexFilename);

    latexFile << "\\documentclass{standalone}\n"
        << "\\usepackage{pgfplots}\n"
        << "\\pgfplotsset{compat=newest}\n\n"
        << "\\begin{document}\n"
        << "\\begin{tikzpicture}\n"
        << "\\begin{axis}[view={120}{40}]\n\n";

    latexFile << "\\addplot3[surf,]\n"
        << "coordinates {\n";
    std::cout << image.rows << " " << image.cols << "\n";
    int imageSize = image.rows * image.cols;
    int step = std::sqrt(imageSize / 1000);

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            if (i % step == 0 && j % step == 0) {
                latexFile << "(" << j << "," << i << "," << (int)image.at<uchar>(i, j) << ") ";

            }

        }

    }


    latexFile << "};\n\n"
        << "\\end{axis}\n"
        << "\\end{tikzpicture}\n"
        << "\\end{document}\n";

    latexFile.close();
}