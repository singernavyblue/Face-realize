#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat frame, string img_path);

/** Global variables */
String face_cascade_name = "haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade; // 定义人脸分类器

/** @function main */
int main(void)
{
    if (!face_cascade.load(face_cascade_name))
    {
        printf("--(!)Error loading face cascade\n");
        return -1;
    };
    for (int i = 1; i <= 10; i++)
    {
        string img_path;
        img_path = format("../photo/%d.jpg", i);
        // cout << img_path << endl;
        Mat frame = imread(img_path);
        imshow("0", frame);
        // VideoCapture capture;
        // Mat frame;

        //-- 1. Load the cascades

        //-- 2. Read the video stream
        // capture.open(0);
        // if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

        // while (capture.read(frame))
        //{
        //  if (frame.empty())
        //  {
        //  printf(" --(!) No captured frame -- Break!");
        //  break;
        //  }

        //-- 3. Apply the classifier to the frame

        img_path = format("../photo/%d.jpg", i);
        detectAndDisplay(frame, img_path);

        int c = waitKey(0);
        if ((char)c == 27)
        {
            return 0;
        } // escape
        //}
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame, string img_path)
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    face_cascade.detectMultiScale(frame_gray, faces);

    for (size_t i = 0; i < faces.size(); i++)
    {
        // cout << "324434\n";
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
        rectangle(frame, faces[i], Scalar(0, 255, 0), 2, 8, 0);
        Mat my_face;
        Mat faceROI = frame_gray(faces[i]);
        resize(faceROI, my_face, Size(92, 112));
        // imshow("faceROI", faceROI);
        // cout << img_path << endl;s
        imwrite(img_path, my_face);
    }
    //-- Show what you got
    // imshow(window_name, frame);
}
