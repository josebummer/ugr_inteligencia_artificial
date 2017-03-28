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
		contador = false;
		estoy_girando = false;
		tengo_tamanio = false;
		tamanio = 0;
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
	bool tengo_tamanio;
	int tamanio;
	bool contador;
	bool estoy_girando;

	ActionType Calcular_tamanio();

};

string ActionStr(Agent::ActionType);

#endif
