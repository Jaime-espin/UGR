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
		CNY70_=false;
		BUMPER_=false;
		he_estado_en_frontera=false;
		veces_en_Frontera = 0;
		int n_casillas = 0;
		girado = 0;
	}

	enum ActionType
	{
	    actFORWARD,
	    actTURN_L,
	    actTURN_R,
		actBACKWARD,
		actPUSH,
		actIDLE
	};

	void Perceive(const Environment &env);
	ActionType Think();

private:
	bool CNY70_;
	bool BUMPER_;
	//Variables extra
	bool he_estado_en_frontera; //true = estuve en la frontera
	int n_casillas;	//numero de casillas
	int girado; 	//para saber si a girado o no
	int veces_en_Frontera;
};

string ActionStr(Agent::ActionType);

#endif
