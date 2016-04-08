#pragma once
#include "Component.h"
#include "BallMovement.h"
#include <memory>
class PlayerController :
	public Component
{
public:
	PlayerController();
	~PlayerController();
	void Reset();
	//void Stop();
	//void Start();
	int GetCurrentLivesCount() const { return _curLives; }
	void LoseLife();
	void SetStartingLives(int count) { _startingLives = count; }
	void ChangeScore(int amount) { _score += amount; }
	int GetScore() const { return _score; }
	void Awake() override;
private:
	BallMovement* _ballMovement;
	int _curLives;
	int _startingLives;
	int _score;
};

