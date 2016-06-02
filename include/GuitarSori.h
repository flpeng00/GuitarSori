#pragma once

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
	MATHFUNCSDLL_API static GuitarSori *instance;
	int     numDevices, defaultDisplayed;
	const   PaDeviceInfo *deviceInfo;
	PaStreamParameters inputParameters, outputParameters;
	PaStream *stream = NULL;
	char *sampleBlock;
	double *sampleBlockConverted;
	double *sampleBlockFFT;
	int framesPerBuffer;
	int numChannels;
	int sampleSize;
	PaSampleFormat sampleFormat;
	double sampleRate;
	PaError err;
	std::thread *pThread;
	MATHFUNCSDLL_API static double standardSampleRates[14];
	static bool isThreadRunning;
	GuitarSori();
	~GuitarSori();
	GuitarSori(const GuitarSori& other);

public:
	MATHFUNCSDLL_API inline static GuitarSori* getInstance() { return instance ? instance : (instance = new GuitarSori()); }
	MATHFUNCSDLL_API static void releaseInstance() { if (instance) delete instance; }
	MATHFUNCSDLL_API void init(const int framesPerBuffer, const int numChannels, const int sampleSize, PaSampleFormat sampleFormat, const double sampleRate);
	MATHFUNCSDLL_API void runThread();
	MATHFUNCSDLL_API void stopThread();
	MATHFUNCSDLL_API inline char* getSampleBuffer() { return isThreadRunning ? sampleBlock : NULL; }
	MATHFUNCSDLL_API inline double* getSampleBufferConverted() { return isThreadRunning ? sampleBlockConverted : NULL; }
	MATHFUNCSDLL_API inline double* getSampleBufferFFT() { return isThreadRunning ? sampleBlockFFT : NULL; }
	MATHFUNCSDLL_API inline int getSampleSizeInBytes() { return instance ? framesPerBuffer * numChannels * sampleSize : 0; }
	MATHFUNCSDLL_API inline int getConvertedSampleSizeInBytes() { return instance ? framesPerBuffer * numChannels * 8 : 0; }
	MATHFUNCSDLL_API static void callback(PaStream *stream, char *sampleBlock, double *sampleBlockConverted, double *sampleBlockFFT, const int framesPerBuffer);
	MATHFUNCSDLL_API void PrintSupportedStandardSampleRates(const PaStreamParameters *inputParameters, const PaStreamParameters *outputParameters);
};