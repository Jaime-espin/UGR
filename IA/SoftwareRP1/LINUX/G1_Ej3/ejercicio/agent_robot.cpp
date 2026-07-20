#include "agent_robot.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	ActionType accion = actIDLE;
	
	/* ESCRIBA AQUI SUS REGLAS */
	/*if(girado){
		cout<<"Regla1: Terminando giro de 180º";
		accion = actTURN_R;
		girado=false;
	}else if(!he_estado_en_frontera && CNY70_){
		cout<< "Regla2: Primera vez en la frontera";
		accion = actTURN_R;
		girado=true;
		he_estado_en_frontera=true;
		n_casillas=1;
	}else if(he_estado_en_frontera && CNY70_){
		accion = actIDLE;
		cout << "Regla3: El tamaño de la zona interior es: "<< n_casillas<<'x'<<n_casillas<<endl;
	}else{
		cout<<"Regla4: Avanza";
		accion=actFORWARD;
		n_casillas++;
	}*/

	if(BUMPER_){
		cout<<"Regla1: Encontró obstaculo";
		accion=actIDLE;
	}else if(girado==2 && veces_en_Frontera%2==0){
		cout<<"Regla 4: Finalizar Giro en frontera par (derecha) y avanzar";
		accion=actTURN_R;
		girado=0;
		veces_en_Frontera++;
	}else if(girado==2 && veces_en_Frontera%2!=0){
		cout<<"Regla 6: Finalizar Giro en frontera impar (izq) y avanzar";
		accion=actTURN_L;
		girado=0;
		veces_en_Frontera++;
	}else if(girado==1 && CNY70_ && veces_en_Frontera%2!=0){
		cout<<"Regla 8: esquina en frontera impar";
		accion=actTURN_L;
		girado=0;
	}else if(girado==1 && CNY70_ && veces_en_Frontera%2==0){
		cout<<"Regla 9: esquina en frontera par";
		accion=actTURN_R;
		girado=0;
	}else if(girado==1){
		cout<<"Regla 3: Avance entre giros";
		accion=actFORWARD;
		girado=2;
	}else if(CNY70_ && veces_en_Frontera%2==0){
		cout<<"Regla 2: Giro en frontera par (derecha)";
		accion=actTURN_R;
		girado=1;
	}else if(CNY70_ && veces_en_Frontera%2!=0){
		cout<<"Regla 5: Giro en frontera impar (izq)";
		accion=actTURN_L;
		girado=1;
	}else{
		cout<<"Regla 7: Avanza";
		accion=actFORWARD;
	}

	return accion;

}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	CNY70_ = env.isFrontier();
	BUMPER_ = env.isBump();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actBACKWARD: return "BACKWARD";
	case Agent::actPUSH: return "PUSH";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
