#include "Tests.h"
#include "ResolveHistogramm.h"

void firstTest()
{
    cv::Mat image = ones().inpImage();              // �������� �����������
    cv::resize(image, image, cv::Size(800, 600));   // ��������������� �����������

    cv::Rect rect = cv::Rect(0, 0, 100, 200);
    cv::Scalar col = cv::Scalar(0, 200, 0);

    cv::rectangle(image, rect, col, 2);             // �������� ������������� �� �����������

    transparenRect(image, 100, 100, 300, 500, cv::Scalar(255, 255, 255));

    cv::imshow("tmp", image);                       // ����������� �����������

    std::vector<cv::Mat> stickers;
    recogniseStickersByThreshold(image, stickers);

    int i = 0;
    for (auto & sticker : stickers)
    {
        cv::imshow(to_string(i), image);
        i++;
    }

    //cv::namedWindow("Win");    // ����������� ������� ����
    cv::waitKey(0);            // ��������� ����� � �������� �������
}

void secondTest()
{
    //readVideoFromCamera();
    //readVideoFromFile();
    //useFilterCanny();
    useLSD();
    cv::waitKey(0);            
}

void thirdTest()
{

}

void fourTest()
{

}

void resolves()
{
	resolveHistogramm();
}
