#pragma once
#include <chrono>
/// Class for keeping track of the deltaTime
class Time
{
public:
	Time();
	~Time();
	void Update(); // Used to calculate the deltatime each frame
	float DeltaTime() const; // Returns the deltatime
private:
	float deltaTime;
};

