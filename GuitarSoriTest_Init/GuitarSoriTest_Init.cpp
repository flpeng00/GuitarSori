// GuitarSoriTest_Init.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GuitarSori.h"


int main()
{
	int *buffer;
	GuitarSori * gs = GuitarSori::getInstance();
	gs->init(2048, 1, 4, paFloat32, 44100);
	gs->runThread();

	while (1)
	{
	}
    return 0;
}

