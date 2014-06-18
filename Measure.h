#pragma once

#include <time.h>

class Measure
{
public:
	Measure(void);
	~Measure(void);

	void start();
	void stop();
	clock_t getTicks();
	float getTime();
private:
	time_t ctime;
	time_t ntime;
	clock_t a;
};

