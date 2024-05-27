#pragma once
#include "stdafx.h"

class AnimationTimer
{
private:
	float _AnimationStartValue;
	float _AnimationEndValue;
	float _AnimationSpeed;//(Delta animationValue)/sec
	std::chrono::steady_clock::time_point StartTime;
	std::chrono::steady_clock::time_point SamplePoint;

public:
	AnimationTimer();
	AnimationTimer(float Speed, float StartValue, float EndValue);
	void StartTimer();
	float GetCurrentAnimationValue();
	void SampleNow();
	float TimeLapseFromLastSampleMillis();
	float TimeLapseFromLastSampleMicros();
	float TimeLapseFromLastSampleNanos();
	void SetSpeed(float new_Speed);
};