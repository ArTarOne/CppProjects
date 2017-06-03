#pragma once

// ***** FIRST *****

// ��������� ����������� ��������
void recogniseStickersByThreshold(cv::Mat image, std::vector<cv::Mat> &stickers);

// ���������� �������
void transparenRect(cv::Mat image, int x, int y, int w, int h, cv::Scalar clr);


// ***** SECOND *****

// Reading and Writing Video
// �������� < http://docs.opencv.org/3.0-beta/modules/videoio/doc/reading_and_writing_video.html> 
int readVideoFromCamera();

// Capture Video from File or Camera
// �������� < http://opencv-srf.blogspot.ru/2011/09/capturing-images-videos.html> 
int readVideoFromFile();

int useFilterCanny();

int useLSD();


// ***** THIRD *****

int useHistogramm();



// ***** FOUR *****

int useSIFT();

int useSURF();