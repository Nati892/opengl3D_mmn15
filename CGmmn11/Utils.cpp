#include "Utils.h"
#include <cmath>
#define SECONDS_TO_MILLISECONDS_RATIO 1000
AnimationTimer::AnimationTimer(float Speed, float StartValue, float EndValue)
{
	this->_AnimationEndValue = EndValue;
	this->_AnimationStartValue = StartValue;
	this->_AnimationSpeed = Speed;
}

void AnimationTimer::StartTimer()
{
	auto sample = (std::chrono::steady_clock::now());
	this->StartTime = sample;
}

float AnimationTimer::GetCurrentAnimationValue()
{
	float res = 0.0f;
	auto sample = (std::chrono::steady_clock::now());
	auto TimeLapse = ((float)std::chrono::duration_cast<std::chrono::milliseconds>(sample - this->StartTime).count()) * SECONDS_TO_MILLISECONDS_RATIO;
	TimeLapse = TimeLapse / this->_AnimationSpeed;
	float AnimationPercentage = TimeLapse - (int)TimeLapse;//remove integer component
	res = this->_AnimationStartValue + (AnimationPercentage * (this->_AnimationEndValue - this->_AnimationStartValue));
	return res;
}
