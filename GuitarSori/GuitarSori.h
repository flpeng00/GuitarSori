#pragma once

#ifdef __cplusplus
extern "C"
#endif

#ifdef GUITARSORI_API_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include <thread>

// PortAudio Library
#include "../Portaudio/portaudio.h"
#if PA_USE_ASIO
#include "../Portaudio/pa_asio.h"
#endif

class GuitarSori
{
private:
	static GuitarSori *instance;

	int     numDevices, defaultDisplayed;
	const   PaDeviceInfo *deviceInfo;
	PaStreamParameters inputParameters, outputParameters;
	PaStream *stream = NULL;
	char *sampleBlock;
	int framesPerBuffer;
	int numChannels;
	int sampleSize;
	PaSampleFormat sampleFormat;
	double sampleRate;
	PaError err;
	std::thread *pThread;
	static double standardSampleRates[14];
	GuitarSori() {};
	~GuitarSori() {};
	GuitarSori(const GuitarSori& other);

public:
	MATHFUNCSDLL_API static GuitarSori* getInstance() { return instance ? instance : (instance = new GuitarSori()); }
	MATHFUNCSDLL_API static void releaseInstance() { if (instance) delete instance; }
	MATHFUNCSDLL_API void init(const int framesPerBuffer, const int numChannels, const int sampleSize, PaSampleFormat sampleFormat, const double sampleRate);
	MATHFUNCSDLL_API void runThread();
	MATHFUNCSDLL_API static void callback(PaStream *stream, char *sampleBlock, const int framesPerBuffer)
	{
		while (1)
		{
			Pa_WriteStream(stream, sampleBlock, framesPerBuffer);
			Pa_ReadStream(stream, sampleBlock, framesPerBuffer);
		}

		free(sampleBlock);

		Pa_Terminate();
	}
	MATHFUNCSDLL_API void PrintSupportedStandardSampleRates(const PaStreamParameters *inputParameters, const PaStreamParameters *outputParameters);
};

GuitarSori* GuitarSori::instance = NULL;

double GuitarSori::standardSampleRates[14] = {
	8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0,
	44100.0, 48000.0, 88200.0, 96000.0, 192000.0, -1 
};
