#pragma once

#include "ofMain.h"

class AudioVisualizer {

    public:
        AudioVisualizer();

        void setBands(int);
        
        vector<float> getAmplitudes();
        int getBands();

        void updateAmplitudes();

    private:
        vector<float> fftSmooth;
        int bands;


};