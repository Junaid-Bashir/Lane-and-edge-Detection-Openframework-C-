#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(edgeThreshold.setup("Edge Threshold", 50, 0, 100));
    gui.add(lineThreshold.setup("Line Threshold", 150, 0, 200));
    
    vid.load("solidWhiteRight.mp4");
    width = vid.getWidth();
    height = vid.getHeight();
    mask = Mat::zeros(cv::Size(width, height), CV_8U);
    vid.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
    vid.getCurrentFrame();
    if(vid.isFrameNew()){
        ofPixels pixs = vid.getPixels();
        vidFrame.setFromPixels(pixs);
        vidMat = toCv(vidFrame);
        //split(vidMat, rgb);
        cvtColor(vidMat, vidMatGray, CV_BGR2GRAY);
        GaussianBlur(vidMatGray, vidMatGray, 3);
        Canny(vidMatGray, frameMat, edgeThreshold, edgeThreshold*2);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255, 255, 255);
    drawMat(vidMat, 0, 0);
    
    //    Setting the dots for ROI
    for(int i = 0; i < keyPoints.size(); i++){
        ofSetColor(255, 0, 0);
        ofDrawCircle(keyPoints[i].x, keyPoints[i].y, 5);
    }
    
    if(keyPoints.size()>=3){
        fillConvexPoly(mask, keyPoints.data(), keyPoints.size(), Scalar(255,255,255));
        bitwise_and(frameMat, mask, frameMat);
    }
    
    vector<Vec4i> lines;
HoughLinesP(frameMat, lines, 2, CV_PI / 180, lineThreshold, 15, 20);
    ofSetColor(255, 0, 0);
    for (int i=0; i<lines.size(); i++) {
        float x1 = lines[i][0];
        float y1 = lines[i][1];
        float x2 = lines[i][2];
        float y2 = lines[i][3];
        ofPolyline l;
        l.addVertex(x1, y1);
        l.addVertex(x2, y2);
        
        l.draw();
    }
    
    gui.draw();
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(x>=0 && x<(int)vid.getWidth() && y>=0 && y<(int)vid.getHeight()){
        cv::Point p(x,y);
        keyPoints.push_back(p);
    }
}
