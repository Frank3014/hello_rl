/*
 * FlappyBird.h
 *
 *  Created on: Nov 15, 2017
 *      Author: user
 */

#ifndef FLAPPYBIRD_H_
#define FLAPPYBIRD_H_

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define JUMP		4
#define CRACK_SIZE	6
#define WAIT_BIG	140000
#define WAIT_LIT	110000
#define DOUBLE		2
#define TRUE		1
#define FALSE		0

typedef struct stBird{
	int row;
	int col;
}Bird;

typedef struct stPipe{
	int crack_start;
	int crack_finish;
	int col;
}Pipe;

typedef enum eState{
	StateLive = 0,
	StateDead
}State;

typedef enum eAction{
	ActionNone = 0,
	ActionFly
}Action;

class FlappyBird {
public:
	FlappyBird();
	virtual ~FlappyBird();

	int Initialize();
	int Finish();

	int GetModelSpace(int &stateCount, int &actionCount);

	int GameStart();
	int GameEnd();

	int GetState(int &state);
	int TakeAction(Action action, double &reward);

private:
	void DrawStarting(int row, int col);
	void DrawPipe(int begin, int end, int pipeCol, int row);
	void DrawWall(int row, int col);
	void GetNewPipeValue(int *crackStart, int *crackFinish, int row);
	int ControlCollision(int pipeCol, int birdCol, int birdRow, int crackStart, int crackFinish);

private:
	int m_row;
	int m_col;
	int m_pipe_counter;

	int m_cur_score;
	int m_max_score;

	Bird m_bird;
	Pipe m_pipe1;
	Pipe m_pipe2;


};

#endif /* FLAPPYBIRD_H_ */
