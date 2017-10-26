
#ifndef ENVIRONMENT__
#define ENVIRONMENT__

#include <fstream>
using std::ifstream;

#include "agent.h"
// -----------------------------------------------------------
//				class Environment
// -----------------------------------------------------------

class RandomNumberGenerator;

class Environment
{
public:
	static const int MAZE_SIZE = 10;

	Environment(ifstream &infile);
	void Show(int,int) const;
	void Change(const RandomNumberGenerator &rng);
	void AcceptAction(Agent::ActionType);
    int AgentPosX() const { return agentPosX_;}
    int AgentPosY() const { return agentPosY_;}
	int  RandomSeed() const { return randomSeed_; }
private:
	static const int OBSTACLE = -1, OBJETO = 1;
	static const char MAP_ROAD = '-', MAP_OBSTACLE = 'O', MAP_OBJETO = 'X';

	bool CNY70_, BUMPER_;
	int agentPosX_, agentPosY_, agentOriented_; // Orientacion: 0 Norte, 1 Este, 2 Sur, 3 Oeste.
	int maze_[MAZE_SIZE][MAZE_SIZE]; // -1: Obstacle, >=0: amount of dirt
	int randomSeed_;
	double dirtyProb_;

	/**/
	Agent::ActionType preAction_;
};
// -----------------------------------------------------------

#endif
