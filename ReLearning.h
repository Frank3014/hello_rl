/*
 * ReLearning.h
 *
 *  Created on: Nov 17, 2017
 *      Author: user
 */

#ifndef RELEARNING_H_
#define RELEARNING_H_

namespace ReLearning {

class ReLearning {
public:
	ReLearning();
	virtual ~ReLearning();

	int Initialize(const int stateNum, const int actionNum);
	int QLearning(const int trainCount);
	int SarsaLearning(const int trainCount);

	int CalculateMaxAction(int state);

private:
	int ChooseAction(int state);
	int UpdateQTable(int state, int action, double reward, int nextState, int nextAction);

protected:
	virtual int GetInitializeState(int &state) = 0;
	virtual int GetCurrentState(int &state) = 0;
	virtual int TakeAction(const int action, double &reward) = 0;

private:
	int m_stateCount;
	int m_actionCount;

	double **m_qMatrix;
};

} /* namespace ReLearning */

#endif /* RELEARNING_H_ */
