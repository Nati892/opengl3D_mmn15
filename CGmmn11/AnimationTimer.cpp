#include "AnimationTimer.h"
#define SECONDS_TO_MILLISECONDS_RATIO 1000

AnimationTimer::AnimationTimer()
{
}
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
	this->SamplePoint = sample;
}

float AnimationTimer::GetCurrentAnimationValue()
{
	float res = 0.0f;
	auto sample = (std::chrono::steady_clock::now());
	auto TimeLapse = ((float)std::chrono::duration_cast<std::chrono::milliseconds>(sample - this->StartTime).count()) / SECONDS_TO_MILLISECONDS_RATIO;
	TimeLapse = TimeLapse / this->_AnimationSpeed;
	float AnimationPercentage = TimeLapse - (int)TimeLapse;//remove integer component
	res = this->_AnimationStartValue + (AnimationPercentage * (this->_AnimationEndValue - this->_AnimationStartValue));
	return res;
}

void AnimationTimer::SampleNow()
{
	this->SamplePoint = std::chrono::steady_clock::now();
}

float AnimationTimer::TimeLapseFromLastSampleMillis()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->SamplePoint).count();
}

float AnimationTimer::TimeLapseFromLastSampleMicros()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - this->SamplePoint).count();
}

float AnimationTimer::TimeLapseFromLastSampleNanos()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - this->SamplePoint).count();
}

void AnimationTimer::SetSpeed(float new_Speed)
{
	this->_AnimationSpeed = new_Speed;
}
