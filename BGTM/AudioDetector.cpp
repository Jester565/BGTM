#include "AudioDetector.h"


AudioDetector::AudioDetector()
{
}

IAudioMeterInformation* AudioDetector::aInfo = NULL;

void AudioDetector::initializeAudioAnalyzer()
{
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator = NULL;
	IMMDevice *pDevice = NULL;
	IAudioMeterInformation *pMeterInfo = NULL;
	CoInitialize(NULL);
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
	checkError(hr);
	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	checkError(hr);
	hr = pDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&pMeterInfo);
	checkError(hr);
	aInfo = pMeterInfo;
}

bool AudioDetector::soundPlaying()
{
	float peak;
	aInfo->GetPeakValue(&peak);
	return peak > 0;
}

void AudioDetector::checkError(HRESULT hr)
{
	if (FAILED(hr))
	{
		std::cout << "Error";
		system("pause");
	}
}

AudioDetector::~AudioDetector()
{
}
