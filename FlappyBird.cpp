/*
 * FlappyBird.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: user
 */

#include "FlappyBird.h"

FlappyBird::FlappyBird() :
	m_row(0), m_col(0), m_pipe_counter(0), 	m_cur_score(0), m_max_score(0)
	{
	// TODO Auto-generated constructor stub

}

FlappyBird::~FlappyBird() {
	// TODO Auto-generated destructor stub

}

int FlappyBird::Initialize(){

	initscr();
	curs_set(0);
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);

	getmaxyx(stdscr, this->m_row, this->m_col);

	return 0;
}

int FlappyBird::Finish(){
	clear();
	refresh();
	endwin();

	return 0;
}

int FlappyBird::GetModelSpace(int &stateCount, int &actionCount){

	stateCount = this->m_row * this->m_row * this->m_col * 2;
	actionCount = 2;

	return 0;
}

int FlappyBird::GameStart(){

	this->DrawStarting(this->m_row, this->m_col);

	this->m_bird.row = this->m_row / 2;
	this->m_bird.col = this->m_col / 2;

	this->m_pipe1.col = this->m_col;
	this->m_pipe2.col = this->m_col;

	this->m_pipe_counter = this->m_col;

	this->m_cur_score = 0;

	GetNewPipeValue(&(this->m_pipe1.crack_start), &(this->m_pipe1.crack_finish), this->m_row);
	GetNewPipeValue(&(this->m_pipe2.crack_start), &(this->m_pipe2.crack_finish), this->m_row);

	return 0;
}

int FlappyBird::GameEnd(){
	clear();
	mvprintw(this->m_row/2, (this->m_col - 20)/2, "GAME OVER. score is %d", this->m_cur_score);
	refresh();

	return 0;
}

int FlappyBird::GetState(int &state){

	Pipe pipe;
	if(this->m_pipe1.col < this->m_bird.col){
		pipe = this->m_pipe2;
	}
	else if((this->m_pipe2.col < this->m_bird.col)){
		pipe = this->m_pipe1;
	}
	else{
		if(this->m_pipe1.col < this->m_pipe2.col){
			pipe = this->m_pipe1;
		}
		else{
			pipe = this->m_pipe2;
		}
	}

	state = (this->m_row * 2 * this->m_col) * this->m_bird.row + this->m_row * 2 * (pipe.col - this->m_bird.col) + (pipe.crack_start - this->m_bird.row + this->m_row);

	return 0;
}

int FlappyBird::TakeAction(Action action, double &reward){

	int ret = 0;

	clear();
	noecho();

	mvprintw(1, this->m_col/3-20, "Score : %d", this->m_cur_score);
	mvprintw(1, this->m_col*3/3-20, "Action : %d", (ActionNone == action)?0:1);

	mvaddch(this->m_bird.row, this->m_bird.col, 'Q' | A_BOLD | COLOR_PAIR(2));

	attron(COLOR_PAIR(1));

	// draw wall
	DrawWall(this->m_row, this->m_col);

	// draw pipe 1
	DrawPipe(this->m_pipe1.crack_start, this->m_pipe1.crack_finish, this->m_pipe1.col, this->m_row);
	this->m_pipe1.col--;

	// draw pipe 2
	if(this->m_pipe_counter < this->m_col/2){
		DrawPipe(this->m_pipe2.crack_start, this->m_pipe2.crack_finish, this->m_pipe2.col, this->m_row);
		this->m_pipe2.col--;
	}

	attroff(COLOR_PAIR(1));

	if(this->m_bird.row < this->m_row - 1){
		this->m_bird.row++;
	}

	if(ActionFly == action){
		this->m_bird.row -= JUMP;
	}

	if(this->m_bird.row < 2){
		this->m_bird.row = 2;
	}

	reward = 0;

	if(this->m_bird.row > this->m_row - 2 || this->m_bird.row == 2)
	{
		reward = -100;
	}

	int collision = ControlCollision(this->m_bird.row, this->m_bird.col, this->m_pipe1.col, this->m_pipe1.crack_start, this->m_pipe1.crack_finish);
	if(2 == collision)
	{
		reward = -100;
	}

	collision = ControlCollision(this->m_bird.row, this->m_bird.col, this->m_pipe2.col, this->m_pipe2.crack_start, this->m_pipe2.crack_finish);
	if(2 == collision)
	{
		reward = -100;
	}

	if (this->m_pipe1.col == 0)
	{
		GetNewPipeValue(&this->m_pipe1.crack_start, &this->m_pipe1.crack_finish, this->m_row);
		this->m_pipe1.col = this->m_col;
	}

	if (this->m_pipe2.col == 0)
	{
		GetNewPipeValue(&this->m_pipe2.crack_start, &this->m_pipe2.crack_finish, this->m_row);
		this->m_pipe2.col = this->m_col;
		this->m_pipe_counter = this->m_col/2;
	}

	this->m_cur_score++;
	this->m_pipe_counter--;

	refresh();

	if(reward < 0){
		ret = -1;
	}

	return ret;
}


void FlappyBird::DrawStarting(int row, int col){
	mvprintw(row/2-5, (col-22)/2, "WELCOME TO FLAPPY BIRD");
	mvprintw(row/2-3, (col-48)/2, "If you touch the any RED line game will be over");
	mvprintw(row/2 -2, (col-26)/2, "Use \"UP ARROW\" for playing");

	int i, j;

	mvprintw(row/2+2, col/2, "|");
	mvprintw(row/2+2, col/2-10, "|");

	for(j=1; j< 10; j++)
	{
		for(i=0; i<j; i++){

			mvprintw(row/2+2, col/2-10+j, ">");
			refresh();
		}
		usleep(50000);
	}
}

void FlappyBird::DrawPipe(int begin, int end, int pipeCol, int row){
	int i;

	for(i=2; i < row; i++)
	{
		if(i < begin)
			mvprintw(i, pipeCol-2, "###");
		if(i > end)
			mvprintw(i, pipeCol-2, "###");
	}
}

void FlappyBird::DrawWall(int row, int col){

	for(int i=0; i < this->m_col; ++i)
	{
		mvprintw(this->m_row, i, "#");
		mvprintw(2, i, "#");
	}

}

void FlappyBird::GetNewPipeValue(int *crackStart, int *crackFinish, int row){
	*crackStart = rand() % row/2+3;
	*crackFinish = *crackStart + CRACK_SIZE;
}

int FlappyBird::ControlCollision(int birdRow, int birdCol, int pipeCol, int crackStart, int crackFinish){
	int status = 0;

	if(pipeCol -3 == birdCol || pipeCol -2 == birdCol || pipeCol -1 == birdCol)
	{
		status++;
		if(birdRow < crackStart || birdRow > crackFinish)
		{
			status++;
		}
	}

	return status;

}
