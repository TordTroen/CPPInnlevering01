#pragma once
#include <chrono>

// Class for keeping track of the deltaTime
class Time
{
public:
	~Time();
	static void Init();
	static void Update(); // Used to calculate the deltatime each frame
	static float DeltaTime(); // Returns the deltatime
private:
	static float deltaTime;
};

