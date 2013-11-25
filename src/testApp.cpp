#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    stream.setup(this, 2, 0, 44100, 512, 4);
    soundBuffer = new float[512];
    sinWave.setup(44100);
//    sinWave.setFrequency(440);
    sinWave.setVolume(1);
    
    ofSetBackgroundAuto(false); // must have
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
    ofSetColor(0);
    ofRect(0,0,ofGetScreenWidth(),ofGetScreenHeight());
    ofSetColor(255, 255, 255);
    
    // draw debug (ie., image, depth, skeleton)
//    openNIDevice.drawDebug();
    
//    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    sinWave.setVolume(0);
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        
        // draw the mask texture for this user
        ofSetLineWidth(4);
        user.drawMask();
        
        // get joint position
        head = user.getJoint(JOINT_HEAD).getProjectivePosition();
        leftHand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
        rightHand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
        leftFoot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        rightFoot = user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
        torso = user.getJoint(JOINT_TORSO).getProjectivePosition();
        sinWave.setVolume(0.7);
    }
    
//    ofDisableBlendMode();
//    ofPopMatrix();
    openNIDevice.drawDepth(ofGetScreenWidth() - 320, ofGetScreenHeight() - 240, 320,240);
}

//--------------------------------------------------------------
void testApp::draw(){
    bShape.clear();
    // draw some info regarding frame counts etc
//	ofSetColor(0, 255, 0);
//	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
//
    ofSetColor(255,0,0);
    ofSetLineWidth(4);
    ofFill();
    
    bShape.addVertex(head.x, head.y);
    bShape.addVertex(leftHand.x, leftHand.y);
    bShape.addVertex(leftFoot.x, leftFoot.y);
    bShape.addVertex(rightFoot.x, rightFoot.y);
    bShape.addVertex(rightHand.x, rightHand.y);
    bShape.close();
    
    bShape.draw();
    
    bShape_area = abs(bShape.getArea()/1000);
    sinWave.setFrequency(bShape_area * 15);
    verdana.drawString(ofToString(bShape_area), 100, 100);
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
//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
    
	for (int i = 0; i < bufferSize; i++){
        
        float sample = sinWave.getSample(); //ofRandom(-1,1);
        
        output[i*nChannels    ] = sample;
        output[i*nChannels + 1] = sample;
        
        soundBuffer[i] = sample;
	}
}