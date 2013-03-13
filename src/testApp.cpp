#include "testApp.h"
bool bSnap = false;
//--------------------------------------------------------------
void testApp::setup(){

	ofEnableSmoothing();
	center.set(0,0);
	float SIZE = (ofGetWidth()/GRID_WIDTH*1.0f)*0.5;
	space      = sin((1/6.0f)*2*M_PI)*SIZE*2;
	float minX = center.x - (GRID_WIDTH * space)*0.5;
	float minY = center.y - (GRID_HEIGHT * space)*0.5;
	float maxWidth = (GRID_WIDTH * space+((GRID_HEIGHT%2)*0.5)*space) + center.x - (GRID_WIDTH * space)*0.5 - minX;
	float maxHeight = (GRID_HEIGHT * space) + center.y - (GRID_HEIGHT * space)*0.5  - minY;
	for (int j=0; j<GRID_HEIGHT; j++) {
		for (int i=0; i<GRID_WIDTH; i++) {
			int x	  = (i * space+((j%2)*0.5)*space) + center.x - (GRID_WIDTH * space)*0.5;//
			int y     = (j * space) + center.y - (GRID_HEIGHT * space)*0.5;
			int z     = 0;
			int index = (j*GRID_WIDTH+i) * LENGTH;
			
			// now we are at each line
			int hex_index = 0;
			
			float rdnSize = 1;//abs( ofRandomf());
			float hue = 1;//ofRandom(0.5,1.0);
			for (int k=0; k<LENGTH; k++) {

					
					pos[index +k].x = x+sin((hex_index/6.0f)*2*M_PI)*SIZE*rdnSize;
					pos[index +k].y = y+cos((hex_index/6.0f)*2*M_PI)*SIZE*rdnSize;
				tex_coord[index +k].x = ofMap(pos[index +k].x,minX , maxWidth , 0,640);
											  
				tex_coord[index +k].y = ofMap(pos[index +k].y,minY , maxHeight, 0,480);
					hex_index++;
				pos[index +k].z = z;
				color[index + k] = ofFloatColor::fromHsb(hue,1,1);
			}
			
			
		}
	}
	total = GRID_WIDTH*GRID_HEIGHT*LENGTH;
	vbo.setVertexData(pos, total, GL_DYNAMIC_DRAW);
	vbo.setColorData(color, total, GL_DYNAMIC_DRAW);
	vbo.setTexCoordData(tex_coord, total, GL_DYNAMIC_DRAW);
	//	for(int i = 0; i < 6; ++i) {
	//		glVertex2d(sin(i/6.0*2*M_PI),
	//				   cos(i/6.0*2*M_PI));
	//	}
	glEnable(GL_DEPTH_TEST);
	bUseGrabber = false;
	grabber.initGrabber(640,480);
}

//--------------------------------------------------------------
void testApp::update(){
	if(bUseGrabber)
		grabber.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0);
	//	grabber.draw(0, 0);
	cam.begin();
	//	ofDrawAxis(100);
//	ofDrawGrid(100,10,false,true,true,true);
	ofPushMatrix();
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255);
	

	vbo.bind();
	vbo.updateVertexData(pos, total);
	vbo.updateColorData(color, total);
	vbo.updateTexCoordData(tex_coord, total);
	if(bUseGrabber)grabber.getTextureReference().bind();
	for (int i=0; i<GRID_WIDTH; i++) {
		for (int j=0; j<GRID_HEIGHT; j++) {
			int index = (j*GRID_WIDTH+i) * LENGTH;
//			for(int k = 0; k < LENGTH ; k++)
			{
//				vbo.draw(GL_LINES, index,LENGTH);
				vbo.draw(GL_TRIANGLE_FAN, index,LENGTH);
			}
		}
	}
	if(bUseGrabber)grabber.getTextureReference().unbind();
	vbo.unbind();
	
	ofPopMatrix();
	cam.end();
	if (bSnap) {
		string hr;
		ofImage img;
		img.grabScreen(0,0,ofGetWidth(), ofGetHeight());
		if(ofGetHours() < 12)
		{
			hr = " AM";
		}
		else
		{
			hr = " PM";
		}
		img.saveImage(ofToString(ofGetYear())+"-"+ofToString(ofGetMonth())+"-"+ofToString(ofGetDay())+" at "+ofToString(ofGetHours(),2)+"."+ofToString(ofGetMinutes(),2)+"."+ofToString(ofGetSeconds(),2) +hr +".png");
		bSnap = false;
	}
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 20,20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='`')
	{
		bSnap = true;
		
	}
	if(key==OF_KEY_RETURN)
	{
		bUseGrabber = !bUseGrabber;
	}
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
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}