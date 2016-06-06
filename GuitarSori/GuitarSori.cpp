// GuitarSori.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#define GUITARSORI_API_EXPORTS
#include <stdio.h>
#include <stdlib.h>
#include "../include/GuitarSori.h"
#include "Rvfft.h"

void GuitarSori::PrintSupportedStandardSampleRates(const PaStreamParameters * inputParameters, const PaStreamParameters * outputParameters)
{
	int     i, printCount;
	PaError err;

	printCount = 0;
	for (i = 0; standardSampleRates[i] > 0; i++)
	{
		err = Pa_IsFormatSupported(inputParameters, outputParameters, standardSampleRates[i]);
		if (err == paFormatIsSupported)
		{
			if (printCount == 0)
			{
				printf("\t%8.2f", standardSampleRates[i]);
				printCount = 1;
			}
			else if (printCount == 4)
			{
				printf(",\n\t%8.2f", standardSampleRates[i]);
				printCount = 1;
			}
			else
			{
				printf(", %8.2f", standardSampleRates[i]);
				++printCount;
			}
		}
	}
	if (!printCount)
		printf("None\n");
	else
		printf("\n");
}

GuitarSori::GuitarSori() :
	sampleBlock(NULL),
	sampleBlockConverted(NULL),
	sampleBlockFFT(NULL),
	pThread(NULL)
{
	isThreadRunning = false;
}

GuitarSori::~GuitarSori()
{
	stopThread();
	freeBuffers();
}

void GuitarSori::freeBuffers()
{
	if (sampleBlock)
	{
		free(sampleBlock);
		sampleBlock = NULL;
	}
	if (sampleBlockConverted)
	{
		free(sampleBlockConverted);
		sampleBlockConverted = NULL;
	}
	if (sampleBlockFFT)
	{
		free(sampleBlockFFT);
		sampleBlockFFT = NULL;
	}
}

void GuitarSori::init( const int mFramesPerBuffer, const int mNumChannels, const int mSampleSize, PaSampleFormat mSampleFormat, const double mSampleRate)
{
	int numBytes, numBytesConverted;

	framesPerBuffer = mFramesPerBuffer;
	numChannels = mNumChannels;
	sampleSize = mSampleSize;
	sampleFormat = mSampleFormat;
	sampleRate = mSampleRate;

	numBytes = mFramesPerBuffer * mNumChannels * mSampleSize;
	numBytesConverted = mFramesPerBuffer * mNumChannels * 8;

	freeBuffers();
	sampleBlock = (char *)malloc(numBytes);
	sampleBlockConverted = (double *)malloc(numBytesConverted);
	sampleBlockFFT = (double *)malloc(numBytesConverted / 2);

	if ( !isBuffersReady() )
	{
		printf("Cannot allocate sample block\n");
		return;
	}

	memset(sampleBlock, 0x00, numBytes);
	memset(sampleBlockConverted, 0x00, numBytesConverted);
	memset(sampleBlockFFT, 0x00, numBytesConverted / 2);

	err = Pa_Initialize();

	printf("──────────────────────────────\n");
	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
	inputParameters.device = 1;
	printf("Input device # %d. : %s\n", inputParameters.device, Pa_GetDeviceInfo(inputParameters.device)->name);
	printf("Input LL: %g s\n", Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency);
	printf("Input HL: %g s\n", Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency);
	printf("Input HL: %g s\n", Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency);
	printf("Input Channel(MAX.) : %d ", Pa_GetDeviceInfo(inputParameters.device)->maxInputChannels);
	inputParameters.channelCount = numChannels;
	inputParameters.sampleFormat = sampleFormat;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	printf("Output device # %d.\n", outputParameters.device);
	printf("Output LL: %g s\n", Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency);
	printf("Output HL: %g s\n", Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency);
	outputParameters.channelCount = numChannels;
	outputParameters.sampleFormat = sampleFormat;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, sampleRate, framesPerBuffer, paClipOff, NULL, NULL);
	err = Pa_StartStream(stream);
}

void GuitarSori::runThread()
{
	if( instance ) pThread = new std::thread(callback, stream, sampleBlock, sampleBlockConverted, sampleBlockFFT, framesPerBuffer);
	else return;
}

MATHFUNCSDLL_API void GuitarSori::stopThread()
{
	if (pThread)
	{
		isThreadRunning = false;
		pThread->join();
		pThread = NULL;
	}
}

void GuitarSori::callback(PaStream *stream, char *sampleBlock, double *sampleBlockConverted, double *sampleBlockFFT, const int framesPerBuffer)
{
	float *floatBuffer = (float*)sampleBlock;
	isThreadRunning = true;

	while (isThreadRunning)
	{
		Pa_ReadStream(stream, sampleBlock, framesPerBuffer);
		for (int i = 0; i < framesPerBuffer; i++)
		{
			sampleBlockConverted[i] = (double)floatBuffer[i];
		}

		
		realfft_packed(sampleBlockConverted, framesPerBuffer);
		for (int i = 0; i < framesPerBuffer / 2; i++)
		{
			sampleBlockFFT[i] = 1000 * (sampleBlockConverted[2 * i] * sampleBlockConverted[2 * i] 
								+ sampleBlockConverted[2 * i + 1] * sampleBlockConverted[2 * i + 1] );
		}
		Pa_WriteStream(stream, sampleBlock, framesPerBuffer);
	}

	isThreadRunning = false;

	Pa_Terminate();
}

GuitarSori* GuitarSori::instance = NULL;

double GuitarSori::standardSampleRates[14] = {
	8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0,
	44100.0, 48000.0, 88200.0, 96000.0, 192000.0, -1
};

bool GuitarSori::isThreadRunning = false;