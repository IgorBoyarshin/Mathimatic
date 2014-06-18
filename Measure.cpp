#include "Measure.h"

Measure::Measure(void)
{
}
Measure::~Measure(void)
{
}

void Measure::start() {
	time(&ctime);
	a = clock();
}

void Measure::stop() {
	time(&ntime);
	a = clock() - a;
}

clock_t Measure::getTicks() {
	//return ntime - ctime;
	return a;
}

float Measure::getTime() {
	//return ((float)a)/CLOCKS_PER_SEC;
	return ((float)(a))/CLOCKS_PER_SEC;
}