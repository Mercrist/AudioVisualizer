#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    sound.loadSound(songs[0]); //Loads a sound file (in bin/data/)
    sound.setLoop(true); // Makes the song loop indefinitely
    sound.setVolume(1); // Sets the song volume
    ofSetBackgroundColor(255,99,71);   // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update(){ //called 60 times a second
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate(); // Updates all sound players
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    if (replaying)
    {
        timer++;
        replayKeys();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */
    if(!playing){
        ofSetColor(256);
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
        ofDrawBitmapString("Press 'd' or 'f' to change the music!", ofGetWidth()/2 - 50, (ofGetHeight()/2)+30);
        ofDrawBitmapString("Press 'k' to randomly replay recorded keys!", ofGetWidth()/2 - 50, (ofGetHeight()/2)+60);
    }


    if (recording) //placing the recording text on the bottom right
    {   
        ofSetColor(256);
        ofDrawBitmapString("Key presses are now being recorded!", ofGetWidth()-280, ofGetHeight()-10); 
    }

    if (replaying) //placing the recording text on the bottom right
    {   
        ofSetColor(256);
        ofDrawBitmapString("Stored keys are now being replayed!", ofGetWidth()-280, ofGetHeight()-10); 
    }
    
    vector<float> amplitudes = visualizer.getAmplitudes();

    if(pause)
        {amplitudes = currentAmp;}
        
    if(mode == '1'){
        drawMode1(amplitudes);
    }else if(mode == '2'){
        drawMode2(amplitudes);
    }else if(mode == '3'){
        drawMode3(amplitudes);
    }else if(mode == '4'){
        drawMode4(amplitudes);
    }
}
void ofApp::drawMode1(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
        int bands = amplitudes.size(); //theres 64 rectangles
        int width = (int)((double)ofGetWidth()/amplitudes.size()); //adjusts rectangles depending on the screens size, recasts a double value to an integer
        for(int i=0; i< bands; i++) 
        {   
            ofSetColor(Red, Green, Gary);                             
            ofDrawRectangle(i*width, ofGetHeight() - 100, width,  10*amplitudes[i]); //(x, y, width, height)
        }
        
}
void ofApp::drawMode2(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %256,18,144); // Color varies between frequencies
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[0]/(i +1));
        }
}

void ofApp::drawMode3(vector<float> amplitudes){
        ofFill(); 
        ofSetColor(256);
        ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
        int bands = amplitudes.size(); //theres 64 rectangles
        int width = (int)((double)ofGetWidth()/amplitudes.size()); 
        for(int i=0; i< bands; i++) 
        {   
            ofSetColor(Red1, Green2, Gary3);                             
            ofDrawRectangle(0, i*width, -10*amplitudes[i], width);
        }
    
}
void ofApp::drawMode4(vector<float> amplitudes){
    ofFill(); 
    ofSetColor(256); 
    ofDrawBitmapString("TriForce Visualizer", 0, 15);
    int bands = amplitudes.size();
    for(int i=0; i< bands; i++)
    {
        ofSetColor((bands - i)*32 %256,Green2,Gary3); // Drawn Shapes will be filled in with color
        if(playing){ //Draws the "Triforce Visualizer" if playing
            ofDrawTriangle( ofGetWidth()/2,ofGetHeight()/8, ofGetWidth()/4, ofGetHeight()/2,ofGetWidth()*0.75, ofGetHeight()/2);
            ofDrawTriangle( ofGetWidth()/2+xsize,ofGetHeight()/8+ysize, ofGetWidth()/4+xsize, ofGetHeight()/2+amplitudes[0]/(i +1)+ysize,ofGetWidth()*0.75+xsize, ofGetHeight()/2+ysize);
            ofDrawTriangle( ofGetWidth()/2-xsize,ofGetHeight()/8+ysize, ofGetWidth()/4-xsize, ofGetHeight()/2+ysize,ofGetWidth()*0.75-xsize, ofGetHeight()/2+amplitudes[0]/(i +1)+ysize);
            }
    }       
}

void ofApp::recordKey(char key)
{
    //only want to register keys that switch or do something in the program, not just any key
    if (key == 'p' || key == 'a' || key == '1' || key == '2' || key == '3' || key == '4' || key == '=' || key == '-' || key == 'd' || key == 'f')
        keys.push_back(key);
}

void ofApp::replayKeys()
{
    char value; 
    if(index == keys.size()) //quit record function and reset everything if we reached the last element in the vector array
    {
        replaying = false;
        index = 0;
        timer = 0;
        keys.clear();
    }

    else if (index == 0 || timer >= 300) //update is called 60 times a second, want to delay for 5s 
    {
        value = keys[index]; 
        switch(value){
            case 'p': //start or stops the visualizer
                if(playing)
                    sound.stop();
                else
                    sound.play();

                playing = !playing;
                break;

            case 'a': //pauses the visualizer
                if (pause) {pause = false;}
                else
                {
                    currentAmp = visualizer.getAmplitudes();
                    pause = true;
                }
                break;
            
            case '1':
                mode = '1';
                ofSetBackgroundColor(255,99,71);//orange
                break;

            case '2':
                mode = '2';
                ofSetBackgroundColor(107,142,35); //olive drab
                break;

            case '3':
                mode = '3';
                ofSetBackgroundColor(219,112,147); //pale violet red
                break;

            case '4':
                mode = '4';
                ofSetBackgroundColor(204,204,0); //gold
                break;

            case '=': //raises the volume
                if (volume < 1.0)
                {
                    volume += 0.1;
                    sound.setVolume(volume);
                }
                break;

            case '-': //lowers the volume
                if (volume > 0.0)
                {
                    volume -= 0.1;
                    sound.setVolume(volume);
                }
                break;
            
            case 'd': //goes backwards in the song list
                if(songIndex <= 0)
                    songIndex = 4;
            
                songIndex -=1;
                sound.loadSound(songs[songIndex]);
                sound.play();
                break;

            case 'f': //goes forwards in the song list
                if(songIndex >= 3)
                    songIndex = -1;
            
                songIndex += 1;
                sound.loadSound(songs[songIndex]);
                sound.play();
                break;

            }
        //reset timer at the end of each iteration
        timer = 0; 
        index++;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // This method is called automatically when any key is pressed
    if (replaying)
        {
            if (key == 't') //cancels replaying and resets variables
                {
                    replaying = false;
                    index = 0;
                    timer = 0;
                    keys.clear();
                }
            return; //prevents other keys from doing anything when pressed
        } 

    if (recording) //record ONLY VALID MODE key presses, must be recasted to a character 
        {recordKey((char) key);}

    switch(key){
        case 'p': 
            if(playing)
                sound.stop();
            else 
                sound.play();
            
            playing = !playing;
            break;

        case 'a':
            if (pause) {pause = false;}
            else
            {
                currentAmp = visualizer.getAmplitudes();
                pause = true;
            }
            break;
            
        case '1':
            mode = '1';
            ofSetBackgroundColor(255,99,71);
            break;

        case '2':
            mode = '2';
            ofSetBackgroundColor(107,142,35); //olive drab
            break;

        case '3':
            mode = '3';
            ofSetBackgroundColor(219,112,147); //pale violet red
            break;

        case '4':
            mode = '4';
            ofSetBackgroundColor(204,204,0); //peru
            break;

        case '=': //raises the volume
            if (volume < 1.0)
            {
                volume += 0.1;
                sound.setVolume(volume);
            }
            break;

        case '-': //lowers the volume
            if (volume > 0.0)
            {
                volume -= 0.1;
                sound.setVolume(volume);
            }
            break;

        case 'r': 
            recording = !recording; 
            break;
        
        case 'd': //goes backwards in the song list
            if(songIndex <= 0)
                songIndex = 4;
            
            songIndex -=1;
            sound.loadSound(songs[songIndex]);
            sound.play();
            break;

        case 'f': 
            if(songIndex >= 3)
                songIndex = -1;
            
            songIndex += 1;
            sound.loadSound(songs[songIndex]);
            sound.play();
            break;
            
        case 't':
            if (keys.size() != 0) //can't replay keys if there are no keys stored
            {
                recording = false; //stops recording if user pressed t before finishing their recording
                replaying = true;
            }
            break;

        case 'k': //random replay sequence shuffles the vector array and replays the recorded keys
            if(keys.size() != 0)
            {
                random_shuffle(keys.begin(), keys.end()); 
                recording = false; 
                replaying = true;
            }
            break; 
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}