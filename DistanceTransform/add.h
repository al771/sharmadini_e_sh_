#ifndef ADD_H
#define ADD_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <iostream>
#include <string>


cv::Mat loadImage(std::string s);
cv::Mat toWhiteBackground(cv::Mat img);
cv::Mat distanceTransform(cv::Mat img);
void generateLaTeXCode(const cv::Mat& image, const std::string& latexFilename);
#endif