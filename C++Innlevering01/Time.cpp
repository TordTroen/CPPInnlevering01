#include "Time.h"

typedef std::chrono::high_resolution_clock hr_clock;
typedef hr_clock::time_point time_point;
typedef hr_clock::duration duration;
time_point currentFrame = hr_clock::now();
duration timeSpan;
float Time::deltaTime = 0;

Time::~Time()
{
}

void Time::Init()
{
	deltaTime = 0;
}

void Time::Update()
{
	time_point lastFrame = currentFrame;
	currentFrame = hr_clock::now();
	timeSpan = currentFrame - lastFrame;
	deltaTime = static_cast<float>(timeSpan.count()) / 10000000.0f;
}

float Time::DeltaTime()
{
	return deltaTime;
}
