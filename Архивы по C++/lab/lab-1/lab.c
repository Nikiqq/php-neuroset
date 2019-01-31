//#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int min;
	double voulme;
	const double g = 400.01;
	min= -70;
	voulme= -22.43;
	printf("min=%d,  voulme=%.2lf, g=%.2lf",min,voulme,g);
	_getch();
	return EXIT_SUCCESS;
}