#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetBackgroundAuto(false);
    array_size = 200;
    ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
    
    // set properties for all user masks and point clouds
    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    openNIDevice.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
    
    // you can alternatively create a 'base' user class
//    ofxOpenNIUser user;
//    user.setUseMaskTexture(true);
//    user.setUsePointCloud(true);
//    user.setPointCloudDrawSize(2);
//    user.setPointCloudResolution(2);
//    openNIDevice.setBaseUserClass(user);
      
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        
        // draw the mask texture for this user
        user.drawMask();
        
        // get joint position
        head = user.getJoint(JOINT_HEAD).getProjectivePosition();
        leftHand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
        rightHand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
        leftFoot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        rightFoot = user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
        torso = user.getJoint(JOINT_TORSO).getProjectivePosition();
        
//        array_head.push_back(head);
//        array_leftFoot.push_back(leftFoot);
//        array_leftHand.push_back(leftHand);
//        array_rightFoot.push_back(rightFoot);
//        array_rightHand.push_back(rightHand);
//        array_torso.push_back(torso);
//        
//        if(array_head.size() > array_size) {
//            array_head.erase(array_head.begin());
//        }
//        
//        if(array_leftHand.size() > array_size) {
//            array_leftHand.erase(array_leftHand.begin());
//        }
//        
//        if(array_leftFoot.size() > array_size) {
//            array_leftFoot.erase(array_leftFoot.begin());
//        }
//        
//        if(array_rightFoot.size() > array_size) {
//            array_rightFoot.erase(array_rightFoot.begin());
//        }
//        
//        if(array_rightHand.size() > array_size) {
//            array_rightHand.erase(array_rightHand.begin());
//        }
//        if(array_torso.size() > array_size) {
//            array_torso.erase(array_torso.begin());
//        }
        // you can also access the pixel and texture references individually:
        
        // TEXTURE REFERENCE
        //ofTexture & tex = user.getMaskTextureReference();
        // do something with texture...
        
        // PIXEL REFERENCE
        //ofPixels & pix = user.getMaskPixels();
        // do something with the pixels...
        
        // and point clouds:
        
        ofPushMatrix();
        // move it a bit more central
        ofTranslate(320, 240, 10);
        user.drawPointCloud();
        
        // you can also access the mesh:
        
        // MESH REFERENCE
        //ofMesh & mesh = user.getPointCloud();
        // do something with the point cloud mesh
        
        ofPopMatrix();
        
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
//	ofSetColor(0, 255, 0);
//	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
//    
//	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
    
    ofSetColor(255,0,0);
    ofSetLineWidth(4);
    ofLine(leftHand.x, leftHand.y, head.x, head.y);
    ofLine(head.x, head.y, rightHand.x, rightHand.y);
    ofLine(rightHand.x, rightHand.y, rightFoot.x, rightFoot.y);
    ofLine(rightFoot.x, rightFoot.y, leftFoot.x, leftFoot.y);
    ofLine(leftFoot.x, leftFoot.y, leftHand.x, leftHand.y);
    
    ofPolyline(bodyPoints);
    
//    for(int i=0; i<array_head.size();i++) {
//        if(i > 1) {
//            ofLine(array_head[i-1].x, array_head[i-1].y, array_head[i].x, array_head[i].y);
//        }
//    }
//    for(int i=0; i<array_leftFoot.size();i++) {
//        if(i > 1) {
//            ofLine(array_leftFoot[i-1].x, array_leftFoot[i-1].y, array_leftFoot[i].x, array_leftFoot[i].y);
//        }
//    }
//    for(int i=0; i<array_rightFoot.size();i++) {
//        if(i > 1) {
//            ofLine(array_rightFoot[i-1].x, array_rightFoot[i-1].y, array_rightFoot[i].x, array_rightFoot[i].y);
//        }
//    }
//    for(int i=0; i<array_leftHand.size();i++) {
//        if(i > 1) {
//            ofLine(array_leftHand[i-1].x, array_leftHand[i-1].y, array_leftHand[i].x, array_leftHand[i].y);
//        }
//    }
//    for(int i=0; i<array_rightHand.size();i++) {
//        if(i > 1) {
//            ofLine(array_rightHand[i-1].x, array_rightHand[i-1].y, array_rightHand[i].x, array_rightHand[i].y);
//        }
//    }
//    for(int i=0; i<array_torso.size();i++) {
//        if(i > 1) {
//            ofLine(array_torso[i-1].x, array_torso[i-1].y, array_torso[i].x, array_torso[i].y);
//        }
//    }
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}