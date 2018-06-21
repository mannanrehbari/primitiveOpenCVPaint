#include <iostream>
#include <cstdio>
#include "opencv2/opencv.hpp"


#define NUM_ARGS 2
using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if(argc != NUM_ARGS){
      printf("USAGE: ./yourprogram image \n");
      return 0;
    }
    else{
        Mat imgIn = imread(argv[1], CV_LOAD_IMAGE_COLOR);
        imshow("Primitive OpenCV Paint", imgIn);
        waitKey(0);
        return 0;
    }

}
