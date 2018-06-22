/*
@author Abdul Mannan
Jun 21 2018
*/



// include necessary dependencies
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;
using namespace std;

// original image and a copy for reset
Mat imageIn, originalImg;
Mat croppedImage;

static void clickCallback(int event, int x, int y, int flags, void* userdata);
string togList[5] = {"EYEDROPPER", "CROP", "PENCIL", "PAINT BUCKET", "RESET"};
int currentTool = 0;
int eyeDropValue[3] = {255,255,255};


//start and end points for crop ROI
Point point1, point2;
int drag = 0;




void eyeDropFunction(int y , int x){

  Vec3b intensity = croppedImage.at<Vec3b>(y,x);
  eyeDropValue[0] = intensity.val[0];
  eyeDropValue[1] = intensity.val[1];
  eyeDropValue[2] = intensity.val[2];

  cout << "BGR" << eyeDropValue[0] << " " << eyeDropValue[1] << " " << eyeDropValue[2] << endl;
  return ;
}

void paintBucket(int y, int x){
    Vec3b currentValue = croppedImage.at<Vec3b>(y,x);
}
static void clickCallback(int event, int x, int y, int flags, void* userdata)
{
    if(event == cv::EVENT_LBUTTONDOWN)
    {
        if(0 == currentTool){
          eyeDropFunction(y, x);
          return ;

        } else if(1 == currentTool){
          point1 = Point(x,y);
        } else if(currentTool ==3){
          //paint BUCKET
          paintBucket(y, x);

        }


    } else if(event == EVENT_RBUTTONDOWN)
    {
      if(currentTool == 4){
        currentTool = 0;
      } else{
        currentTool++;
      }
        cout << "Selected[" << currentTool << "]:"<<togList[currentTool] << endl;
        return ;
    } else if(event == EVENT_LBUTTONUP)
    {
        if(currentTool == 1){
          point2 = Point(x,y);

          //cout << "Point 1: (" << point1.x << ", " << point1.y << ")" << endl;
          //cout << "Point 2: (" << point2.x << ", " << point2.y << ")" << endl;
          if( !(point1.x == point2.x && point1.y == point2.y))
          {
            Rect rectROI(point1, point2);
            //rectangle(imageIn, rectROI.tl(), rectROI.br(), Scalar(0,255,255), 1,8,0);

            croppedImage = croppedImage(rectROI);
            imshow("imageIn", croppedImage);

          } else{
            cout << "Region cannot be cropped!" << endl;
          }
      }
    } else if(event == EVENT_LBUTTONDBLCLK)
    {
      if(currentTool == 4)
      {
        imshow("imageIn", originalImg);
        imageIn = croppedImage = originalImg.clone();

      }

    } else if(event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)){
      if( currentTool == 2){
        // cout << "Point: (" << x << ", " << y << ")" << endl;
        croppedImage.at<Vec3b>(y,x) = Vec3b(eyeDropValue[0], eyeDropValue[1], eyeDropValue[2]);
        imshow("imageIn", croppedImage);
      }
    }
    return;
}

int main(int argc, char **argv)
{
    // open the input image

	originalImg = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
  imageIn = croppedImage= originalImg.clone();
	/* / check for file error
	if(!imageIn.data)
	{
		std::cout << "Error while opening file " << inputFileName << std::endl;
		return 0;
	}
  */
  // display the input image
  namedWindow("imageIn", WINDOW_AUTOSIZE);
  setMouseCallback("imageIn", clickCallback, &imageIn);
	imshow("imageIn", imageIn);

	//setMouseCallback("imageIn", clickCallback, &imageIn);
	waitKey();
}
