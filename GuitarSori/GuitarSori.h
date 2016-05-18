#pragma once

// PortAudio Library
#include "../Portaudio/portaudio.h"
#if PA_USE_ASIO
#include "../Portaudio/pa_asio.h"
#endif

class GuitarSori
{
private:
	int     numDevices, defaultDisplayed;
	const   PaDeviceInfo *deviceInfo;
	PaStreamParameters inputParameters, outputParameters;
	PaError err;
	static double standardSampleRates[14];

public:
	GuitarSori();
	~GuitarSori();

	void PrintSupportedStandardSampleRates(const PaStreamParameters *inputParameters, const PaStreamParameters *outputParameters);
};

double GuitarSori::standardSampleRates[14] = {
	8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0,
	44100.0, 48000.0, 88200.0, 96000.0, 192000.0, -1 
};

