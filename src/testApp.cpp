#include "testApp.h"
#include "stdio.h"

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
        
        ofPushMatrix();
        // move it a bit more central
        ofTranslate(320, 240, 10);
        user.drawPointCloud();
        
        
        ofPopMatrix();
        
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // draw some info regarding frame counts etc
//	ofSetColor(0, 255, 0);
//	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
//    
//	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
    
    ofSetColor(255,0,0);
    ofSetLineWidth(4);
    
//    ofLine(leftHand.x, leftHand.y, head.x, head.y);
//    ofLine(head.x, head.y, rightHand.x, rightHand.y);
//    ofLine(rightHand.x, rightHand.y, rightFoot.x, rightFoot.y);
//    ofLine(rightFoot.x, rightFoot.y, leftFoot.x, leftFoot.y);
//    ofLine(leftFoot.x, leftFoot.y, leftHand.x, leftHand.y);
    
    
    ofBeginShape();
    ofVertex(head.x, head.y);
    ofVertex(leftHand.x, leftHand.y);
    ofVertex(leftFoot.x, leftFoot.y);
    ofVertex(rightFoot.x, rightFoot.y);
    ofVertex(rightHand.x, rightHand.y);
    ofEndShape(true);
    
//    bShape.addVertex(head);
//    bShape.addVertex(leftHand);
//    bShape.addVertex(rightHand);
//    bShape.addVertex(leftFoot);
//    bShape.addVertex(rightFoot);
//    bShape.close();
//    
////    ofFill();
//    bShape.draw();
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
//void testApp::onMessage( Spacebrew::Message & msg ){
////    if(msg.name == "SpaceAubio_pitch_receive") {
////        otherPitch = ofToInt(msg.value);
////        //cout << "other pitch is" << otherPitch << endl;
////    }
////    if(msg.name == "SpaceAubio_volume_receive") {
////        otherVol = ofToInt(msg.value);
////    }
//}
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