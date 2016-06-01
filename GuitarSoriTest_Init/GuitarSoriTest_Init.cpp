// GuitarSoriTest_Init.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GuitarSori.h"


int main()
{
	int *buffer;
	GuitarSori * gs = GuitarSori::getInstance();
	gs->init(1024, 2, 4, 0x00000002, 44100);
	gs->runThread();

	while (1)
	{
		buffer = (int *)GuitarSori::getInstance()->getSampleBuffer();
		if (buffer == NULL) continue;
		for (int i = 0; i < GuitarSori::getInstance()->getSampleSizeInBytes() / sizeof(int); i++)
		{
			printf("\t%d", buffer[i] / 1000);
			if (i % 10 == 0) printf("\n");
		}
	}
    return 0;
}

