#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() { m_bezierCurve = ofxBezierCurve(); }

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() { m_bezierCurve.draw(0.1f); }

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) { m_bezierCurve.drag(x, y); }

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
  if (button == 0) {
    m_bezierCurve.touch(x, y);
  } else {
    m_bezierCurve.remove(x, y);
  }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
