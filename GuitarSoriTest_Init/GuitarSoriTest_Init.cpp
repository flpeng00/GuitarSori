// GuitarSoriTest_Init.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

