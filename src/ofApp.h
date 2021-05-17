#pragma once
#include "ofMain.h"
#include "AudioVisualizer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void drawMode1(vector<float> amplitudes);
		void drawMode2(vector<float> amplitudes);
		void drawMode3(vector<float> amplitudes);
		void drawMode4(vector<float> amplitudes);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		
	private:
		ofSoundPlayer sound;
		AudioVisualizer visualizer;
		bool playing = false;
		char mode = '1';	

		//two random rectangle or triangle colors
		int Red=ofRandom(0,256);
        int Green=ofRandom(0,256);
        int Gary=ofRandom(0,256);

		int Red1=ofRandom(0,256);
        int Green2=ofRandom(0,256);
        int Gary3=ofRandom(0,256);

        //Moves the triangles the x or y points
		int xsize=ofGetWidth()/2-ofGetWidth()/4;
        int ysize=ofGetHeight()/2-ofGetHeight()/8;

		//handles pausing the visualizer
		bool pause = false;
		vector<float> currentAmp; 
		double volume = 1.0; 

		//recorded key presses
		vector<char> keys; 
		bool recording = false;
		void recordKey(char key);
		
		//song changes
		string songs[8]={"customers-creed.wav","Gary-Blue.wav", "hopesearching.wav","Mickey.wav","sanctuary.wav","Victory.wav", "whims.wav","Zelda-music.wav"};
		string song = songs[0];

		//replay variables
		size_t index = 0;
		bool replaying = false;
		long int timer = 0;
		void replayKeys();
};
