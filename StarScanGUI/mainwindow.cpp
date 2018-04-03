#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include "opencv2/opencv.hpp"
#include <unistd.h>

using namespace cv;
using namespace std;
const long double PI = 3.141592653589793238;

//Important variables (these values change for accuracy)
//filtervalue is 0-255 (255 catches nothing/0 catches everything)
double intensity;
int searchzone;
int starsize = 2;
bool visualmode = true;
bool testingmode = false;

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

void CalcPoints(double &xcalc, double &ycalc, double orientation, double scale, double angle, double distance){

    double newdistance = scale*distance;
    double newangle = orientation + angle;
    xcalc = xcalc + cos(newangle*PI/180)*newdistance;
    ycalc = ycalc + -1*sin(newangle*PI/180)*newdistance;

}

bool CheckPoints( double xtry, double ytry, int numstars, double locx[], double locy[], int &foundx, int &foundy) {

    for (int j = numstars; j >= 0; j--) {
        if ((locx[j] <= searchzone+xtry && locx[j] >= xtry-searchzone)  && (locy[j] <= searchzone+ytry && locy[j] >= ytry-searchzone)) {
            foundx = locx[j];
            foundy = locy[j];
            return true;
        }
    }
    return false;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    visualmode = ui->checkBox->isChecked();
    testingmode = ui->checkBox_2->isChecked();
    destroyAllWindows();
    QString i;
    i = ui->lineEdit->text();

    QString o;
    o = ui->lineEdit_2->text();
    if(o.length() == 0 || i.length() == 0){
        cout<<"ERROR!: Output/Input Path Empty, Specify Path "<<endl;
    }
    else {
        searchzone = ui->horizontalSlider->value();
        intensity = ui->horizontalSlider_2->value();
        //loading and displaying orginal image
        string filepath = i.toStdString();
        Mat image = imread(filepath, IMREAD_GRAYSCALE);
        Mat image2 = imread(filepath, IMREAD_GRAYSCALE);
        if  (image.rows == 0 || image.cols == 0){
            cout<<"ERROR: Invalid Input Path!"<<endl;
        }
        else {
            ui->label_7->setText("loading image...");

        Mat image3 = imread(filepath, CV_LOAD_IMAGE_COLOR);
        Mat image4 = imread(filepath, CV_LOAD_IMAGE_COLOR);
        string filename = getFilename(filepath);

        //FImage contains star pixels highlighted in green
        Mat FImage(image.size(),CV_8UC3);
        Vec3b color;
        color[0] = 0.0; //blue
        color[1] = 255.0; //green
        color[2] = 0.0; //red

        //internal representation of big dipper
                                    //tary - currenty, tarx - currentx
        double distances[6];
        double angles[6];

        angles[0] = 360-(180*atan2(84.2271 - 36.5, 345.691 - 268.5))/PI;
        distances[0] = sqrt(pow((84.2271 - 36.5),2)+ pow((345.691 - 268.5),2));
        if (angles[0] >= 360) {
            angles[0] = angles[0] - 360;
        }

        angles[1] = 360-180*atan2(141.62 - 84.2271, 364.62 - 345.691)/PI;
        distances[1] = sqrt(pow((141.62 - 84.2271),2)+ pow((364.62 - 345.691),2));
        if (angles[1] >= 360) {
            angles[1] = angles[1] - 360;
        }

        angles[2] = 360-180*atan2(205.861 - 141.62, 392.861 - 364.62)/PI;
        distances[2] = sqrt(pow((205.861 - 141.62),2)+ pow((392.861 - 364.62),2));
        if (angles[2] >= 360) {
            angles[2] = angles[2] - 360;
        }

        angles[3] = 360-180*atan2(257 - 205.861, 367 - 392.861)/PI;
        distances[3] = sqrt(pow((257 - 205.861),2)+ pow((367 - 392.861),2));
        if (angles[3] >= 360) {
            angles[3] = angles[3] - 360;
        }

        angles[4] = 360-180*atan2(324 - 257, 437.5 - 367)/PI;
        distances[4] = sqrt(pow((324 - 257),2)+ pow((437.5 - 367),2));
        if (angles[4] >= 360) {
            angles[4] = angles[4] - 360;
        }

        angles[5] = 360-180*atan2(285.62 - 324, 493.62 - 437.5)/PI;
        distances[5] = sqrt(pow((285.62 - 324),2)+ pow((493.62 - 437.5),2));
        if (angles[5] >= 360) {
            angles[5] = angles[5] - 360;
        }

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

        //ui->progressBar->setValue(10);
        ui->label_7->setText("filtering stars...");

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

        //ui->progressBar->setValue(20);
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

        //center locations of each star
        double* locx = new double[keypoints.size()];
        double* locy = new double[keypoints.size()];
        int numstars = keypoints.size();

        //ui->progressBar->setValue(30);

        int r = 0;
        //moving points from keypoints vector to arrays for ease of use
        for(vector<KeyPoint>::iterator blobIt = keypoints.begin(); blobIt != keypoints.end(); blobIt++){
            locx[r] = blobIt->pt.x;
            locy[r] = blobIt->pt.y;
            r++;
        }

        //Variables for search algorithm
        int starcount  = 0; //how many stars are found in the constellation
        int constelx[7];    //contains x values of stars in constellation
        int constely[7];    //contains y values of stars in constellation
        int foundx;         //current found star x,y pos
        int foundy;
        bool hit = true;
        bool looking = true;
        int status = 0;

        //search algorithm
        for (int i = keypoints.size()-1; i >= 0; i--) {
            ui->label_7->setText("searching the galaxy...");

            if (looking == false) {
                break;
            }
            starcount = 0;
            constelx[starcount] = locx[i];
            constely[starcount] = locy[i];

            //looping through every star
            for (int f = keypoints.size()-1; f >= 0; f--) {

                status++;
                double status1 = (status/((double)keypoints.size()*keypoints.size()))*100;
                ui->progressBar->setValue(status1);

                image4.copyTo(image3);
                starcount = 1;
                constelx[starcount] = locx[f];
                constely[starcount] = locy[f];

                Point a1(constelx[starcount-1],constely[starcount-1]), b1(constelx[starcount],constely[starcount]);
                line(image3, a1, b1, color);
                if (visualmode == true) {
                    imshow("Searching..", image3);
                    waitKey(150);
                }

                if (constelx[starcount-1] == constelx[starcount] && constely[starcount-1] == constely[starcount]) {
                    //doing nothing because its checking the same star
                }

                else {

                double testd1 = sqrt(pow((constely[starcount] - constely[starcount-1]),2)+ pow((constelx[starcount] - constelx[starcount-1]),2));

                double scale = testd1 / distances[0];

                double orientation = -1 * (angles[0] - (360-180*atan2(constely[starcount] - constely[starcount-1], constelx[starcount] - constelx[starcount-1])/PI));

                double newdistance = scale * distances[1];
                double newangle = orientation + angles[1];

                double xcalc = locx[f] + cos(newangle*PI/180)*newdistance;
                double ycalc = locy[f]+ -1*sin(newangle*PI/180)*newdistance;

                    hit = CheckPoints( xcalc, ycalc, numstars, locx, locy, foundx, foundy);

                    for (int i = 2; i < 7; i++) {
                        if (hit) {

                            starcount = i;
                            constelx[i] = foundx;
                            constely[i] = foundy;

                            Point a1(constelx[i-1],constely[i-1]), b1(constelx[i],constely[i]);
                            line(image3, a1, b1, color);

                            if (visualmode == true) {
                                waitKey(150);
                                imshow("Searching..", image3);
                            }

                            CalcPoints(xcalc, ycalc, orientation, scale, angles[i], distances[i]);

                            hit = CheckPoints(xcalc, ycalc, numstars, locx, locy, foundx, foundy);

                            if (i == 6) {

                                Point a1(constelx[i],constely[i]), b1(constelx[i-3],constely[i-3]);
                                line(image3, a1, b1, color);

                                if (visualmode == true) {
                                    imshow("Searching..", image3);
                                }

                                looking = false;
                            }
                        }
                    }
                }

                if (looking  == false) {

                    break;
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
        ui->label_7->setText("saving image...");

        //displaying statistics of image
        cout<<"Constellation Analysis for image: "<<filename<<endl;
        cout<<"intensity filter value: "<<intensity<<endl;
        cout<<"Search zone size: "<<searchzone<<endl;
        cout<<"# of Stars: "<<numstars<<endl;

        if (testingmode == true) {
            imshow("filter stars", blobimage);
        }

        if(visualmode == true){
            if (looking == true) {
                cout<<"Unable to find Big Dipper constellation"<<endl;
                destroyWindow("Searching..");
            }
            else {
                cout<<"Big Dipper constellation found!"<<endl;
                destroyWindow("Searching..");
                imshow("Found", image3);
            }
        }

        //saving output
        string outputDir = string(o.toStdString());
        string outputFile = outputDir + "/" + filename;

        imwrite(outputFile, image3);
        //ui->progressBar->setValue(100);
        ui->progressBar->setValue(100);
        ui->label_7->setText("finished.");
        waitKey(-1);
        destroyAllWindows();
        }
}
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    ui->horizontalSlider_2->setValue(arg1);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    ui->spinBox_2->setValue(value);
}
