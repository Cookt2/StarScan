/* Capstone Project Spring 2018
Purpose: Recognize constellations from night sky images using computer vision techniques
Student: Taylor Cook
Prof:    Dr. Reale */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

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
    
    //loading image
    string filepath = string(argv[1]);
    Mat image = imread(filepath, IMREAD_GRAYSCALE);
    string filename = getFilename(filepath);
    
    //setting up generated image of stars using green points
    Mat FImage(image.size(),CV_8UC3);
    Vec3b color;
    int starcount = 0; //amount of pixels that contain stars
    color[0] = 0.0; //blue
    color[1] = 255.0; //green
    color[2] = 0.0; //red
    
    //filtervalue is 0-255 (255 catches nothing/0 catches everything)
    double intensity = 150.0;
    //1d array containing locations of stars (y * #rows + x)
    double* hits = new double[FImage.rows*FImage.cols];

    //finding all pixels greater than filtervalue (intensity filter)
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if ((int)image.at<uchar>(i,j) >= intensity) {
                hits[j*image.rows+i]++;
                //cout<<i<<","<<j<<": hit"<<endl;
            }
        }
    }
    
    //testing algorthim
    /*Mat checkedpixels(image.size(),CV_BGR2GRAY);
    int starnumber = 1;
    bool stardone = true;
    //counting amount of pixels that contain stars
    for (int i = 0; i < FImage.rows; i++) {
        for (int j = 0; j < FImage.cols; j++) {
            stardone = true;
            if (hits[j*FImage.rows+i] == 1) {
                hits[j*FImage.rows+i] = starnumber;
                int u = i;
                int r = j;
                while (stardone) {
                    if (hits[r*FImage.rows+u+1] == 1) {
                        hits[r*FImage.rows+u+1] = starnumber;
                        u++;
                    }
                    else if (hits[(1+r)*FImage.rows+u] == 1){
                        
                    }
                    
                }
                starnumber++;
                FImage.at<Vec3b>(i,j) = color;
                starcount++;
            }
            else
                hits[j*FImage.rows+i] = 0;
       }
    }
    */
    for (int i = 0; i < FImage.rows; i++) {
        for (int j = 0; j < FImage.cols; j++) {
            if (hits[j*FImage.rows+i] == 1) {
                FImage.at<Vec3b>(i,j) = color;
            }
        }
    }
    
    //edge detection using canny
    Mat edge;
    Canny(FImage, edge, 10, 220);
    
    //displaying statistics of image
    cout<<"intensity filter value: "<<intensity<<endl;
    cout<<"number of pixels containing stars in img: "<<starcount<<endl;
    
    //saving output
    string outputDir = string(argv[2]);
    string outputFile = outputDir + "/" + filename;
    
    //which file to save?
    //imwrite(outputFile, FImage);
    imwrite(outputFile, edge);
    
    //displaying image, computed image,and edges
    imshow(filename, image);
    imshow("pixels containing stars", FImage);
    imshow("edge detection", edge);
    waitKey(-1);
    destroyAllWindows();
    
	return 0;
}
