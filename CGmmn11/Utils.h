#pragma once
#include <chrono>

class AnimationTimer
{
private:
	float _AnimationStartValue;
	float _AnimationEndValue;
	float _AnimationSpeed;//(Delta animationValue)/sec
	std::chrono::steady_clock::time_point StartTime;
	AnimationTimer();

public:
	AnimationTimer(float Speed, float StartValue, float EndValue);
	void StartTimer();
	float GetCurrentAnimationValue();
};