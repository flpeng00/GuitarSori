// GuitarSori.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "GuitarSori.h"


GuitarSori::GuitarSori()
{
	Pa_Initialize();

	printf("PortAudio version number = %d\nPortAudio version text = '%s'\n", Pa_GetVersion(), Pa_GetVersionText());
	numDevices = Pa_GetDeviceCount();

	if (numDevices < 0)
	{
		printf("ERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices);
		err = numDevices;
	}

	printf("Number of devices = %d\n", numDevices);
	for (long i = 0; i<numDevices; i++)
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		printf("--------------------------------------- device #%d\n", i);

		/* Mark global and API specific default devices */
		defaultDisplayed = 0;
		if (i == Pa_GetDefaultInputDevice())
		{
			printf("[ Default Input");
			defaultDisplayed = 1;
		}
		else if (i == Pa_GetHostApiInfo(deviceInfo->hostApi)->defaultInputDevice)
		{
			const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
			printf("[ Default %s Input", hostInfo->name);
			defaultDisplayed = 1;
		}

		if (i == Pa_GetDefaultOutputDevice())
		{
			printf((defaultDisplayed ? "," : "["));
			printf(" Default Output");
			defaultDisplayed = 1;
		}
		else if (i == Pa_GetHostApiInfo(deviceInfo->hostApi)->defaultOutputDevice)
		{
			const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
			printf((defaultDisplayed ? "," : "["));
			printf(" Default %s Output", hostInfo->name);
			defaultDisplayed = 1;
		}

		if (defaultDisplayed)
			printf(" ]\n");

		/* print device info fields */
		printf("Name                        = %s\n", deviceInfo->name);
		printf("Host API                    = %s\n", Pa_GetHostApiInfo(deviceInfo->hostApi)->name);
		printf("Max inputs = %d", deviceInfo->maxInputChannels);
		printf(", Max outputs = %d\n", deviceInfo->maxOutputChannels);

		printf("Default low input latency   = %8.4f\n", deviceInfo->defaultLowInputLatency);
		printf("Default low output latency  = %8.4f\n", deviceInfo->defaultLowOutputLatency);
		printf("Default high input latency  = %8.4f\n", deviceInfo->defaultHighInputLatency);
		printf("Default high output latency = %8.4f\n", deviceInfo->defaultHighOutputLatency);

#ifdef WIN32
#if PA_USE_ASIO
		/* ASIO specific latency information */
		if (Pa_GetHostApiInfo(deviceInfo->hostApi)->type == paASIO) {
			long minLatency, maxLatency, preferredLatency, granularity;

			err = PaAsio_GetAvailableLatencyValues(i,
				&minLatency, &maxLatency, &preferredLatency, &granularity);

			printf("ASIO minimum buffer size    = %ld\n", minLatency);
			printf("ASIO maximum buffer size    = %ld\n", maxLatency);
			printf("ASIO preferred buffer size  = %ld\n", preferredLatency);

			if (granularity == -1)
				printf("ASIO buffer granularity     = power of 2\n");
			else
				printf("ASIO buffer granularity     = %ld\n", granularity);
		}
#endif
#endif

		printf("Default sample rate         = %8.2f\n", deviceInfo->defaultSampleRate);

		/* poll for standard sample rates */
		inputParameters.device = i;
		inputParameters.channelCount = deviceInfo->maxInputChannels;
		inputParameters.sampleFormat = paInt16;
		inputParameters.suggestedLatency = 0; /* ignored by Pa_IsFormatSupported() */
		inputParameters.hostApiSpecificStreamInfo = NULL;

		outputParameters.device = i;
		outputParameters.channelCount = deviceInfo->maxOutputChannels;
		outputParameters.sampleFormat = paInt16;
		outputParameters.suggestedLatency = 0; /* ignored by Pa_IsFormatSupported() */
		outputParameters.hostApiSpecificStreamInfo = NULL;

		if (inputParameters.channelCount > 0)
		{
			printf("Supported standard sample rates\n for half-duplex 16 bit %d channel input = \n",
				inputParameters.channelCount);
			PrintSupportedStandardSampleRates(&inputParameters, NULL);
		}

		if (outputParameters.channelCount > 0)
		{
			printf("Supported standard sample rates\n for half-duplex 16 bit %d channel output = \n",
				outputParameters.channelCount);
			PrintSupportedStandardSampleRates(NULL, &outputParameters);
		}

		if (inputParameters.channelCount > 0 && outputParameters.channelCount > 0)
		{
			printf("Supported standard sample rates\n for full-duplex 16 bit %d channel input, %d channel output = \n",
				inputParameters.channelCount, outputParameters.channelCount);
			PrintSupportedStandardSampleRates(&inputParameters, &outputParameters);
		}
	}

	Pa_Terminate();

	printf("----------------------------------------------\n");

/*
error:
	Pa_Terminate();
	fprintf(stderr, "An error occured while using the portaudio stream\n");
	fprintf(stderr, "Error number: %d\n", err);
	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
*/
}

GuitarSori::~GuitarSori()
{
}

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
