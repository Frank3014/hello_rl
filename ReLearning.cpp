/*
 * ReLearning.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: user
 */

#include "ReLearning.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <vector>
using namespace std;

const double epsilon = 0.99;
const double alpha = 0.1;
const double gamma = 0.9;

namespace ReLearning {

ReLearning::ReLearning()
	: m_stateCount(0), m_actionCount(0), m_qMatrix(NULL){
	// TODO Auto-generated constructor stub

}

ReLearning::~ReLearning() {
	// TODO Auto-generated destructor stub

	if(NULL != this->m_qMatrix){
		for(int i = 0; i < this->m_stateCount; ++i){
			if(NULL != this->m_qMatrix[i]){
				delete [] this->m_qMatrix[i];
				this->m_qMatrix[i] = NULL;
			}
		}

		delete [] this->m_qMatrix;
		this->m_qMatrix = NULL;
	}

}

int ReLearning::Initialize(const int stateCount, const int actionCount){

	int ret = 0;

	srand((unsigned)time(NULL));

	if((stateCount < 0) || (actionCount < 0)){
		return -1;
	}

	this->m_stateCount = stateCount;
	this->m_actionCount = actionCount;

	this->m_qMatrix = new double*[stateCount];
	if(NULL != m_qMatrix){
		for(int i = 0; i < stateCount; ++i){
			this->m_qMatrix[i] = new double[actionCount];
			if(NULL != m_qMatrix[i]){
				for(int j = 0; j < actionCount; ++j){
					this->m_qMatrix[i][j] = 0;
				}
			}
			else{
				ret = -1;
			}
		}
	}
	else{
		ret = -1;
	}

	return ret;
}


int ReLearning::QLearning(const int trainCount){

	int count = trainCount;

	while(true){
		int state = 0;
		GetInitializeState(state);

		while(true){
			int action = ChooseAction(state);

			double reward = 0;
			int ret = TakeAction(action, reward);

			int nextState = 0;
			GetCurrentState(nextState);

			int maxAction = CalculateMaxAction(nextState);

			UpdateQTable(state, action, reward, nextState, maxAction);

			if(0 != ret){
				break;
			}

			state = nextState;
		}

		if(trainCount > 0){
			count--;
			if(count <= 0){
				break;
			}
		}
	}

	return 0;
}


int ReLearning::SarsaLearning(const int trainCount){

	int count = trainCount;

	while(true){
		int state = 0;
		GetInitializeState(state);
		int action = ChooseAction(state);

		while(true){
			int nextState = 0;
			GetCurrentState(nextState);

			double reward = 0;
			TakeAction(action, reward);

			int nextAction = ChooseAction(nextState);

			UpdateQTable(state, action, reward, nextState, nextAction);

			if(reward < 0){
				break;
			}

			state = nextState;
			action = nextAction;
		}

		if(trainCount > 0){
			count--;
			if(0 <= count){
				break;
			}
		}
	}

	return 0;
}


int ReLearning::CalculateMaxAction(int state){
	int ret_action = 0;
	double max_reward = -1000000;
	vector<int> action;
	for(int i = 0; i < this->m_actionCount; ++i){
		if(this->m_qMatrix[state][i] - max_reward > 0.000001){
			max_reward = this->m_qMatrix[state][i];
			action.clear();
			action.push_back(i);
		}
		else if(this->m_qMatrix[state][i] - max_reward > -0.000001){
			action.push_back(i);
		}
	}

	if(false == action.empty()){
		ret_action = action[rand()%action.size()];
	}

	return ret_action;
}

int ReLearning::ChooseAction(int state){
	int action;
	int p = rand() % 100 / 100.0;

	if (p < epsilon){
		action = CalculateMaxAction(state);
	}
	else{
		action = rand() % this->m_actionCount;
	}

	return action;
}

int ReLearning::UpdateQTable(int state, int action, double reward, int nextState, int nextAction){
	if((state >= 0) && (state < this->m_stateCount) && (action >= 0) && (action < this->m_actionCount)){
		this->m_qMatrix[state][action] = this->m_qMatrix[state][action] + alpha * (reward + gamma*this->m_qMatrix[nextState][nextAction] - this->m_qMatrix[state][action]);
	}

	return 0;
}


} /* namespace ReLearning */


