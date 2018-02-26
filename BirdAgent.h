/*
 * BirdAgent.h
 *
 *  Created on: Nov 17, 2017
 *      Author: user
 */

#ifndef BIRDAGENT_H_
#define BIRDAGENT_H_

#include "ReLearning.h"
#include "FlappyBird.h"

namespace ReLearning {

class BirdAgent: public ReLearning {
public:
	BirdAgent();
	virtual ~BirdAgent();

	int Initialize();

private:
	int GetInitializeState(int &state);
	int GetCurrentState(int &state);
	int TakeAction(const int action, double &reward);

private:
	FlappyBird flappy;
};

} /* namespace ReLearning */

#endif /* BIRDAGENT_H_ */
