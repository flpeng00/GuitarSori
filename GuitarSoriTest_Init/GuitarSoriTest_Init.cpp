// GuitarSoriTest_Init.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GuitarSori.h"


int main()
{
	GuitarSori * gs = GuitarSori::getInstance();
	gs->init(1024, 2, 3, 0x00000004, 44100);
	gs->runThread();

	while (1)
	{

	}
    return 0;
}

