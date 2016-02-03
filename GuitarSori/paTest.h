#include <stdio.h>
#include <math.h>
#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"

#ifdef WIN32
#pragma warning(disable:4996)

#if PA_USE_ASIO
#include "pa_asio.h"
#endif
#endif

#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SIZE (4)
#define SAMPLE_SILENCE  (0)
#define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
#define PRINTF_S_FORMAT "%.8f"

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (1024)
#define NUM_CHANNELS (1)
#define NUM_SECONDS (3)
#define DITHER_FLAG (0)

class paSample
{
public:
	paSample();
	~paSample();
	char *dataout();
	const PaDeviceInfo *deviceInfo;
private:
	int i, deviceNum, bytesNum;
	float sample[10];
	PaStreamParameters inputParameters, outputParameters;
	PaStream *inputStream = NULL;
	PaError err;
	char *sampleBlock;
	void stream_start();
	void stream_close();
};
