#include "select_test.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

int main()
{

     VideoCapture cap(0);
    // 判定摄像头是否打开
    if (!cap.isOpened())
    {
        cout << "摄像头打开失败." << endl;
        return -1;
    }

    Mat img;
    // d.数据收发
	int i = 1;
    while (1)
		{
            
			char key = waitKey(100);
			cap >> img;
			imshow("frame", img);
			string filename = format("/home/china/paizhao/photo/%d.jpg", i);
 
			switch (key)
			{
			case 'p':
				i++;
				if(imwrite(filename, img))
				{
					cout <<"保存成功"<<endl;
				}
				imshow("photo", img);
				waitKey(500);
				destroyWindow("photo");
				break;
			default:
				break;
			}
		}
}
