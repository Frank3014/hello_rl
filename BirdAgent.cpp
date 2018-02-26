/*
 * BirdAgent.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: user
 */

#include "BirdAgent.h"

namespace ReLearning {

BirdAgent::BirdAgent() {
	// TODO Auto-generated constructor stub

}

BirdAgent::~BirdAgent() {
	// TODO Auto-generated destructor stub
}

int BirdAgent::Initialize(){

	flappy.Initialize();

	int stateCount = 0;
	int actionCount = 0;

	flappy.GetModelSpace(stateCount, actionCount);

	ReLearning::Initialize(stateCount, actionCount);

	return 0;
}


int BirdAgent::GetInitializeState(int &state){

	flappy.GameStart();
	flappy.GetState(state);

	return 0;
}

int BirdAgent::GetCurrentState(int &state){

	flappy.GetState(state);

	return 0;
}

int BirdAgent::TakeAction(const int action, double &reward){

	Action birdAction;

	if(0 == action){
		birdAction = ActionNone;
	}
	else{
		birdAction = ActionFly;
	}

	int ret = flappy.TakeAction(birdAction, reward);

	if(0 != ret){
		flappy.GameEnd();
	}

	usleep(100000);

	return ret;
}

} /* namespace ReLearning */
