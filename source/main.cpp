/**
 * This is the main file for the audio-server.
 * It contains methods for running the audio-server main loop, etc.
 * The following figure illustrates the overall architecture.
 * \image latex classes.png "audio-server architecture draft" width=14cm
 *
 */

#include "core/core.h"

using namespace aserver;
using namespace std;

Core core;

int main () {

    //********** No Operation processor example
//    core.setProcessor(processor::types::NO_OPERATION);

    //********** Distance Attenuation processor example
//    processor::ProcessorInput procInput;
//    generatePositions();
//    procInput.inputListenerPositions = readPositions("data/input/listenerLocations.txt");
//    procInput.motionSamplingRate = 240; //Hertz
//    procInput.periodSize = 2048;
//    processor::DistanceAttenuationConfigData distanceAtProcData;
//    distanceAtProcData.flags = processor::distanceAttenuationConfigFlags::DISTANCEATTENUATION_ALL;
//    distanceAtProcData.distanceExp = 1;
//    distanceAtProcData.withInputPositions = true;
//    distanceAtProcData.input = procInput;
//    core.setProcessor(processor::types::DISTANCE_ATTENUATION);//, &procData);

    //********** Acousticave processor example
    #ifdef WITH_AAVE
//    processor::AcousticaveConfigData aaveConfigData;
//    aaveConfigData.flags = processor::acousticaveConfigFlags::ACOUSTICAVE_ALL;
//    aaveConfigData.gain = 10;
//    aaveConfigData.hrtf = 1;
//    aaveConfigData.modelFilePath = "geometries/model.obj";
//    aaveConfigData.reflections = 0;
//    aaveConfigData.reverbActive = 1;
//    aaveConfigData.area = 3000;
//    aaveConfigData.volume = 3000;
//    aaveConfigData.rt60 = 4000;
    core.setProcessor(processor::types::ACOUSTICAVE);//, &aaveConfigData);
    #endif

    //********** Memory output example
//    core.setOutput(output::types::MEMORY);

    //********** File output example
    output::FileOutputConfigData fileData;
    fileData.flags = output::fileConfigFlags::NORMALISE;
    fileData.normalise_audio = false;
    core.setOutput(output::types::FILE, &fileData);

    //********** Alsa output example
//    output::AlsaOutputConfigData alsaData;
//    alsaData.flags = output::alsaConfigFlags::ALSA_ALL;
//    alsaData.samplingRate = 44100;
//    alsaData.nChannels = 2;
//    alsaData.withPulseAudio = true;
//    core.setOutput(output::types::ALSA, &alsaData);

    //********** Primitive generator example
//    core.addGenerator(generator::types::PRIMITIVE);
//    core.addSource();

    //********** Test generator example
//    generator::TestConfigData testData;
//    testData.flags = generator::primitiveConfigFlags::WAVEFORM;
//    testData.waveform = generator::waveformType::SQUARE;
//    core.addGenerator(generator::types::TEST, &testData);
//    core.addSource();

    //********** Noise generator example
//    generator::NoiseConfigData noiseData;
//    noiseData.flags = generator::noiseConfigFlags::NOISE_ALL;
//    noiseData.amplitude = SHRT_MAX * 0.02;
//    noiseData.distType = generator::distributionType::NORMAL;
//    core.addGenerator(generator::types::NOISE, &noiseData);
//    core.addSource();

    //********** Wave generator example
//    generator::WaveConfigData waveData;
//    waveData.flags = generator::waveConfigFlags::WAVE_ALL;
//    waveData.waveIndex = core.getWaveIndex("audio/input/espiral.wav"); // input wav filepath must be fully set
//    waveData.frequencyRatio = 1.;
//    waveData.wavePosition = 0;
//    processor::SourceConfigData srcData1;
//    srcData1.loc = Location(0., 5., 0.);
//    core.addGenerator(generator::types::WAVE, &waveData);
//    core.addSource(&srcData1);

    //********** Script generator example
    core.addGenerator(generator::types::SCRIPT);
    core.addSource();

    for (int i = 0; i < 1000; i++) {

        if (i == 55) {
            core.setPeriodSize(666);
        }
        if (i == 200) {
            core.setPeriodSize(6666);
            core.setProcessor(processor::types::DISTANCE_ATTENUATION);
        }
        #ifdef WITH_AAVE
        if (i == 500) {
            core.setPeriodSize(4096);
            core.setProcessor(processor::types::ACOUSTICAVE);//, &aaveConfigData);
        }
        #endif
        core.render();
    }

    core.shutdown();
}

/*
float f = 0;
for (int i=0, vector::iterator it=p.begin(); it!=p.end();)  {
while (it!=p.end() && i * 1. / 240 < f + 2048. / 44100) {
core.processor->listenerPositions[(int)((i * 1. / 240 - f) * 44100)] = *it;
++it; ++i;
}
f += 2048. / 44100;
core.render();
}*/
