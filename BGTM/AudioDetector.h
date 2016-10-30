#pragma once
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>

class AudioDetector
{
public:

	AudioDetector();
	static IAudioMeterInformation* aInfo;
	static void initializeAudioAnalyzer();
	static bool soundPlaying();
	~AudioDetector();
private:
	static void checkError(HRESULT hr);
};

