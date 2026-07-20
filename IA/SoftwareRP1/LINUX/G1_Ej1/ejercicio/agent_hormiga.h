#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
	    FEROMONA_=false;
		n_giros = 0;
		instante = 0;
		mtiempo = vector<vector<int>>();
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
		actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();

private:
	bool FEROMONA_;
	int n_giros;
	int instante;
	vector<vector<int>> mtiempo;
};

string ActionStr(Agent::ActionType);

#endif
