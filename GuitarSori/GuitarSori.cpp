// GuitarSori.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#define GUITARSORI_API_EXPORTS
#include <stdio.h>
#include <stdlib.h>
#include "GuitarSori.h"

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

void GuitarSori::init( const int mFramesPerBuffer, const int mNumChannels, const int mSampleSize, PaSampleFormat mSampleFormat, const double mSampleRate)
{
	int numBytes;

	framesPerBuffer = mFramesPerBuffer;
	numChannels = mNumChannels;
	sampleSize = mSampleSize;
	sampleFormat = mSampleFormat;
	sampleRate = mSampleRate;

	numBytes = framesPerBuffer * numChannels * sampleSize;
	sampleBlock = (char *)malloc(numBytes);

	if (sampleBlock == NULL)
	{
		printf("Cannot allocate sample block\n");
		return;
	}

	memset(sampleBlock, 0x00, numBytes);

	err = Pa_Initialize();

	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
	printf("Input device # %d.\n", inputParameters.device);
	printf("Input LL: %g s\n", Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency);
	printf("Input HL: %g s\n", Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency);
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
	pThread = new std::thread(callback, stream, sampleBlock, framesPerBuffer);
}

