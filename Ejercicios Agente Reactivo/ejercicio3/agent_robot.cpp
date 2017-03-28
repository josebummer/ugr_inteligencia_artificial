#include "agent_robot.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

//------------------------------------------------------------

Agent::ActionType Agent::Calcular_tamanio(){
	ActionType accion;

	if( estoy_girando ){
		accion = actTURN_L;
		estoy_girando = false;
		contador = true;
		tamanio++;
	}
	else if(contador && !CNY70_ ){
		tamanio++;
		accion = actFORWARD;
	}
	else if(contador && CNY70_){
		accion = actIDLE;
		contador = false;
		tengo_tamanio = true;
	}
	else if( CNY70_ ){
		accion = actTURN_L;
		estoy_girando = true;
	}
	else{
		accion = actFORWARD;
	}

	return accion;
}

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	ActionType accion;

	if(!tengo_tamanio){
		accion = Calcular_tamanio();
	}
	else{
		accion = actIDLE;
	}

	cout << endl << "El tamanio es: " << tamanio << endl;

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
