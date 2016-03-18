#pragma once
#include <chrono>

class Time
{
public:
	Time();
	~Time();
	void Update();
	float DeltaTime();
};

