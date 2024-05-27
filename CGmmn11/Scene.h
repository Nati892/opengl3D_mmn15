#pragma once
#include "stdafx.h"

#include "AnimationTimer.h"
#include "SceneObjects.h"

//The main func to run my beautiful scene
void RunScene(int argc, char** argv);


struct UserPref
{
	SceneObj currentObj;
	float AnimationSpeed;
	bool IsOrtho;
};
