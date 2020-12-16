#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "ofxCv.h"

using namespace cv;
using namespace ofxCv;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);
    
//    Create gui
    ofxPanel gui;

//    Load video
    ofVideoPlayer vid;
    ofImage vidFrame;
    Mat vidMat;
    Mat vidMatGray;
    Mat edgeMat;
    Mat frameMat;
    
//    Canny Edge Detection
    Mat vidMatEdge;
    ofxIntSlider edgeThreshold;
    
//    Hough Transform Lines
    ofxIntSlider lineThreshold;
    ofxIntSlider lowThreshold;
    
//    Region of Interest
    Mat mask;
    vector<cv::Point> keyPoints;
    
    
    float width;
    float height;
		
};
