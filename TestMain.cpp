/* Capstone Project Spring 2018
Purpose: Recognize constellations from night sky images using computer vision techniques
Student: Taylor Cook
Prof:    Dr. Reale */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <math.h>
#include "opencv2/opencv.hpp"
#include <unistd.h>

using namespace cv;
using namespace std;

#


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
    
    //Important constants
    const long double PI = 3.141592653589793238;
    
    //Important variables (these values change for accuracy
    //filtervalue is 0-255 (255 catches nothing/0 catches everything)
    double intensity = 100.0;
    int searchzone = 15;
    int starsize = 2;
    
    //internal representation of big dipper
                                //tary - currenty, tarx - currentx
    double angle1 = 360-(180*atan2(84.2271 - 36.5, 345.691 - 268.5))/PI;
    double d1 = sqrt(pow((84.2271 - 36.5),2)+ pow((345.691 - 268.5),2));
    if (angle1 >= 360) {
        angle1 = angle1-360;
    }
    
    double angle2 = 360-180*atan2(141.62 - 84.2271, 364.62 - 345.691)/PI;
    double d2 = sqrt(pow((141.62 - 84.2271),2)+ pow((364.62 - 345.691),2));
    if (angle2 >= 360) {
        angle2 = angle2-360;
    }
    
    double angle3 = 360-180*atan2(205.861 - 141.62, 392.861 - 364.62)/PI;
    double d3 = sqrt(pow((205.861 - 141.62),2)+ pow((392.861 - 364.62),2));
    if (angle3 >= 360) {
        angle3 = angle3-360;
    }

    double angle4 = 360-180*atan2(257 - 205.861, 367 - 392.861)/PI;
    double d4 = sqrt(pow((257 - 205.861),2)+ pow((367 - 392.861),2));
    if (angle4 >= 360) {
        angle4 = angle4-360;
    }

    double angle5 = 360-180*atan2(324 - 257, 437.5 - 367)/PI;
    double d5 = sqrt(pow((324 - 257),2)+ pow((437.5 - 367),2));
    if (angle5 >= 360) {
        angle5 = angle5-360;
    }
    
    double angle6 = 360-180*atan2(285.62 - 324, 493.62 - 437.5)/PI;
    double d6 = sqrt(pow((285.62 - 324),2)+ pow((493.62 - 437.5),2));
    if (angle6 >= 360) {
        angle6 = angle6-360;
    }
    
    //displays big dipper angles and distances
    /*cout<<"Angle 1->6: "<<angle1<<", "<<angle2<<", "<<angle3<<", "<<angle4<<", "<<angle5<<", "<<angle6<<endl;
    cout<<"Distance 1->6: "<<d1<<", "<<d2<<", "<<d3<<", "<<d4<<", "<<d5<<", "<<d6<<endl;
    */
    
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
        drawContours( drawing, contours, i, color1, starsize, 8, hierarchy, 2, Point() );
    }
    
    //Simple Blob Dection
    //referenced from: https://docs.opencv.org/3.3.1/d0/d7a/classcv_1_1SimpleBlobDetector.html
    SimpleBlobDetector::Params params;
    params.filterByArea = true;
    params.minArea = 1;
    params.maxArea = 1000.0f;
    params.filterByColor = true;
    params.blobColor = 255;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    params.filterByCircularity = true;
    params.minCircularity = 0.1f;
    params.maxCircularity = 1.0f;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
    vector<KeyPoint> keypoints;
    detector->detect( drawing,keypoints);
    Mat blobimage;
    drawKeypoints( drawing, keypoints, blobimage, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
    
    //displaying center locations of each star
    double* locx = new double[keypoints.size()];
    double* locy = new double[keypoints.size()];
    
    int r = 0;
    for(vector<KeyPoint>::iterator blobIt = keypoints.begin(); blobIt != keypoints.end(); blobIt++){
        //cout <<"Star #"<<r+1<< " center at: " << blobIt->pt.x << ", " << blobIt->pt.y << endl;
        locx[r] = blobIt->pt.x;
        locy[r] = blobIt->pt.y;
        r++;
    }
    
    int starcount  = 2;
    for (int i = keypoints.size()-1; i >= 0; i--) {
        
        double current1x, current1y, current2x, current2y;
        current1x = locx[i];
        current1y = locy[i];
        
        for (int f = keypoints.size()-1; f >= 0; f--) {
            current2x = locx[f];
            current2y = locy[f];
            if (current1x == current2x && current1y == current2y) {

            }
            else {

            double testd1 = sqrt(pow((current2y - current1y),2)+ pow((current2x - current1x),2));
            double scale = testd1/d1;
            double orientation = -1 * (angle1 - (360-180*atan2(current2y - current1y, current2x - current1x)/PI));
            double newdistance = scale*d2;
            double newangle = orientation + angle2;
            
            double xoffset = locx[f] + cos(newangle*PI/180)*newdistance;
            double yoffset = locy[f]+ -1*sin(newangle*PI/180)*newdistance;
                //testing statements
                /*cout<<"x1: "<<current1x<<"y1: "<<current1y<<endl;
                cout<<"x2: "<<current2x<<"y2: "<<current2y<<endl;
                cout<<"x3: "<<xoffset<<"y3: "<<yoffset<<endl;
                cout<<"angle: "<<newangle<<endl;
                cout<<"scale: "<<scale<<endl;
                cout<<"testd1: "<<testd1<<endl;
                cout<<"orientation: "<<orientation<<endl;*/
                
            for (int r = keypoints.size(); r >= 0 ; r--) {
                    if ((locx[r] <= searchzone+xoffset && locx[r] >= xoffset-searchzone)  && (locy[r] <= searchzone+yoffset && locy[r] >= yoffset-searchzone)) {
                        starcount++;

                        double xoffset3 = locx[r]+(cos(((orientation+angle3)*PI)/180))*(d3*scale);
                        double yoffset3 = locy[r]+(-1*sin(((orientation+angle3)*PI)/180))*(d3*scale);
                        
                        for (int q = keypoints.size(); q >= 0; q--) {
                            if ((locx[q] <= searchzone+xoffset3 && locx[q] >= xoffset3-searchzone)  && (locy[q] <= searchzone+yoffset3 && locy[q] >= yoffset3-searchzone)){
                                starcount++;

                                double xoffset4 = locx[q]+(cos(((orientation+angle4)*PI)/180))*(d4*scale);
                                double yoffset4 = locy[q]+(-1*sin(((orientation+angle4)*PI)/180))*(d4*scale);

                                for (int q = keypoints.size(); q >= 0; q--) {
                                    if ((locx[q] <= searchzone+xoffset4 && locx[q] >= xoffset4-searchzone)  && (locy[q] <= searchzone+yoffset4 && locy[q] >= yoffset4-searchzone)){
                                        starcount++;

                                        double xoffset5 = locx[q]+(cos(((orientation+angle5)*PI)/180))*(d5*scale);
                                        double yoffset5 = locy[q]+(-1*sin(((orientation+angle5)*PI)/180))*(d5*scale);
                                        for (int q = keypoints.size(); q >= 0; q--) {
                                            if ((locx[q] <= searchzone+xoffset5 && locx[q] >= xoffset5-searchzone)  && (locy[q] <= searchzone+yoffset5 && locy[q] >= yoffset5-searchzone)){
                                                starcount++;
                                                
                                                double xoffset6 = locx[q]+(cos(((orientation+angle6)*PI)/180))*(d6*scale);
                                                double yoffset6 = locy[q]+(-1*sin(((orientation+angle6)*PI)/180))*(d6*scale);
                                                for (int q = keypoints.size(); q >= 0; q--) {
                                                    if ((locx[q] <= searchzone+xoffset6 && locx[q] >= xoffset6-searchzone)  && (locy[q] <= searchzone+yoffset6 && locy[q] >= yoffset6-searchzone)){
                                                        starcount++;

                                                        Point a6(xoffset6,yoffset6), b6(xoffset5,yoffset5);
                                                        line(blobimage, a6, b6, color);
                                                        Point a5(xoffset4,yoffset4), b5(xoffset5,yoffset5);
                                                        line(blobimage, a5, b5, color);
                                                        Point a4(xoffset3,yoffset3), b4(xoffset4,yoffset4);
                                                        line(blobimage, a4, b4, color);
                                                        Point a3(xoffset3,yoffset3), b3(xoffset,yoffset);
                                                        line(blobimage, a3, b3, color);
                                                        Point a2(current2x,current2y), b2(xoffset,yoffset);
                                                        line(blobimage, a2, b2, color);
                                                        Point a1(current2x,current2y), b1(current1x,current1y);
                                                        line(blobimage, a1, b1, color);
                                                        Point a7(xoffset6,yoffset6), b7(xoffset3,yoffset3);
                                                        line(blobimage, a7, b7, color);
                                                        
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    Mat constel(image.size(),CV_8UC1);
    
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            constel.at<uchar>(i,j) = 0;
        }
    }
    
    for (int k = 0; k < keypoints.size(); k++) {
        constel.at<uchar>(round(locy[k]),round(locx[k])) = 255;
        
    }
    
    //displaying statistics of image
    cout<<"intensity filter value: "<<intensity<<endl;
    cout<<"Search zone size: "<<searchzone<<endl;
    cout<<"# of Stars: "<<keypoints.size()<<endl;
    //cout<<"Size of stars: "<<starsize<<" pixels"<<endl;
    
    //saving output
    string outputDir = string(argv[2]);
    string outputFile = outputDir + "/" + filename;
    imwrite(outputFile, blobimage);
    
    imshow( "Result", blobimage);

    waitKey(-1);
    destroyAllWindows();
    
	return 0;
}



