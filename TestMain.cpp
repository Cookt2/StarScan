/* Capstone Project Spring 2018
Purpose: Recognize constellations from night sky images using computer vision techniques
Student: Taylor Cook
Prof:    Dr. Reale */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"


using namespace cv;
using namespace std;

//code from prof Reale's assignment 2 CS490
string getFilename(string path) {
    // Find right-most / or \\ character
    size_t found = path.rfind("/");
    if (found == string::npos) {
        found = path.rfind("\\");
    }
    // Didn't find anything; start at beginning
    if (found == string::npos) {
        found = 0;
    }
    
    size_t newLen = path.length() - found;
    string filename = path.substr(found, newLen);
    
    return filename;
}


int main(int argc, char **argv) {
    
    //loading and displaying orginal image
    string filepath = string(argv[1]);
    Mat image = imread(filepath, IMREAD_GRAYSCALE);
    Mat image2 = imread(filepath, IMREAD_GRAYSCALE);
    string filename = getFilename(filepath);
    imshow("Original",image);
    
    //FImage contains star pixels highlighted in green
    Mat FImage(image.size(),CV_8UC3);
    Vec3b color;
    color[0] = 0.0; //blue
    color[1] = 255.0; //green
    color[2] = 0.0; //red
    
    //filtervalue is 0-255 (255 catches nothing/0 catches everything)
    double intensity = 150.0;
    //1d array containing locations of stars (y * #rows + x)
    double* hits = new double[FImage.rows*FImage.cols];
    
    //finding the locations of stars
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if ((int)image.at<uchar>(i,j) >= intensity) {
                hits[j*image.rows+i]++;
            }
        }
    }
    
    //creating binary image from orginal
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if (hits[j*image.rows+i] == 1) {
                image.at<uchar>(i,j) = 255;
            }
            else
                image.at<uchar>(i,j) = 0;
        }
    }
    
    //display new binary image
    //imshow("image", image);

    //recoloring binary image to green stars
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if (hits[j*image.rows+i] == 1) {
                   FImage.at<Vec3b>(i,j) = color;
            }
            else
                FImage.at<Vec3b>(i,j) = (0);
        }
    }
    
    //canny edge detection
    Mat edge;
    Canny(FImage, edge, 10, 220);
    
    //Finding contours
    //referenced from: https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/find_contours/find_contours.html
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( edge, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    Mat drawing = Mat::zeros( edge.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color1 = Scalar( 255, 255, 255);
        drawContours( drawing, contours, i, color1, 2, 8, hierarchy, 2, Point() );
    }
    
    //Simple Blob Dection
    //referenced from: https://docs.opencv.org/3.3.1/d0/d7a/classcv_1_1SimpleBlobDetector.html
    SimpleBlobDetector::Params params;
    params.filterByArea = true;
    params.minArea = 0.1f;
    params.maxArea = 1000.0f;
    params.filterByColor = true;
    params.blobColor = 255;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    params.filterByCircularity = false;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
    vector<KeyPoint> keypoints;
    detector->detect( drawing,keypoints);
    Mat blobimage;
    drawKeypoints( drawing, keypoints, blobimage, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
    //imshow("KeyPoints", im_with_keypoints);
    
    //displaying center locations of each star
    double* locx = new double[keypoints.size()];
    double* locy = new double[keypoints.size()];
    
    int r = 0;
    for(vector<KeyPoint>::iterator blobIt = keypoints.begin(); blobIt != keypoints.end(); blobIt++){
        cout <<"Star #"<<r+1<< " center at: " << blobIt->pt.x << ", " << blobIt->pt.y << endl;
        locx[r] = blobIt->pt.x;
        locy[r] = blobIt->pt.y;
        r++;
    }
    
    Mat constel(image.size(),CV_8UC1);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            for (int k = 0; k < keypoints.size(); k++) {
                if (j == round(locx[k]) && i == round(locy[k])) {
                    constel.at<uchar>(i,j) = 255;
                }
            }
        }
    }
    
    //Beginning to build search algorithm..
    bool found = false;
    int constellation[2][7];

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            
            if (constel.at<uchar>(i,j) == 255) {
                
            }
        }
    }
    
    
    //experimenting with drawing lines.. (will be removed)
    //Point a(locx[0],locy[0]), b(locx[1],locy[1]);
    //line(blobimage, a, b, color);
    
    //displaying statistics of image
    cout<<"intensity filter value: "<<intensity<<endl;
    cout<<"# of Stars: "<<keypoints.size()<<endl;
    
    //saving output
    string outputDir = string(argv[2]);
    string outputFile = outputDir + "/" + filename;
    imwrite(outputFile, blobimage);
    
    //verious displays for testing
    imshow( "Result", blobimage);
    //imshow("Filtered", FImage);
    //imshow("Edge", edge);
    
    waitKey(-1);
    destroyAllWindows();
    
	return 0;
}
