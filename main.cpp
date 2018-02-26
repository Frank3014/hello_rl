#include "BirdAgent.h"

using namespace ReLearning;

int main(){

	BirdAgent bird;

	bird.Initialize();

	bird.QLearning(0);

	return 0;
}
