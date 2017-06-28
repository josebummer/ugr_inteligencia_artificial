/*
Practica 2: Agentes deliberativos.

Realizada por: Jose Antonio Ruiz Millan

Inteligencia Artificial 2016/2017
*/

#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void PintaPlan(const list<Action> &plan){
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}

void ComportamientoJugador::Reinicio(){
	brujula = nrotaciones = elemmochila = girosizq = girosder = 0;
	bien_situado = deliberativo = tengoregalo = objizq = objder = objdel = objdetras = tengohueso = tengollave = tengobikini = tengozapatillas = kizq = kder = kdetras = kdel = doblegiro = sacarobjeto = false;
	rotar = buscarrey = buscarbikini = buscarzapatillas = busquedadeliberativa = buscarllave = buscarregalo = true;
	fil = 99;
	col = 99;
	x = y = 99;
	ultimaAccion = actIDLE;
	for( int i = 0; i < 200; i++ ){
		for( int j = 0; j < 200; j++){
			mapaauxsuperficie[i][j] = '?';
			mapaaux[i][j] = '?';
			mapaPasosaux[i][j] = -1;
		}
	}
}

void ComportamientoJugador::cambiarMapa(){
	int k = 0,s;

	for( int i = x-fil ; i < (x-fil)+100 ; i++,k++ ){
    s = 0;
    for(int j = y-col; j < (y-col)+100 ; j++,s++){
			if( mapaResultado[k][s] == '?' && mapaaux[i][j] != '?' ){
				mapaResultado[k][s] = mapaaux[i][j];
			}
			if( mapaPasos[k][s] < mapaPasosaux[i][j] ){
				mapaPasos[k][s] = mapaPasosaux[i][j];
			}
			if(mapasuperficie[k][s] == '?' && mapaauxsuperficie[i][j] != '?'){
				mapasuperficie[k][s] = mapaauxsuperficie[i][j];
			}
    }
  }
}

void ComportamientoJugador::Actualizar_informacion(const Sensores &sensores, const Action &ultimaAccion){

	if( !buscarregalo ){
		siguientebusquedaregalo--;
	}
	if(!busquedadeliberativa){
		siguientebusquedadelib--;
	}
	if( parobuscar ){
		siguientecomprobacion--;
	}
	if( siguientebusquedaregalo == 0 ){
		siguientebusquedaregalo = 500;
		buscarregalo = true;
		deliberativo = false;
	}
	if( siguientebusquedadelib == 0 ){
		siguientebusquedadelib = 400;
		busquedadeliberativa = true;
	}
	if( siguientecomprobacion == 0 ){
		siguientecomprobacion = 20;
		parobuscar = false;
		deliberativo = false;
	}

	if(bien_situado){
		if( fil > max ){
			max = fil;
		}
		if( col > max ){
			max = col;
		}
	}

	if( sensores.reset ){
		Reinicio();
	}

	switch (ultimaAccion){
		case actFORWARD:
		if( !sensores.colision )
			switch (brujula){
				case 0: // Norte
					fil--;
				break;
				case 1: // Este
					col++;
				break;
				case 2: // Sur
					fil++;
				break;
				case 3: // Oeste
					col--;
				break;
			}
		break;
		case actTURN_L:
			brujula = (brujula+3)%4;
		break;
		case actTURN_R:
			brujula = (brujula+1)%4;
		break;
		case actPICKUP:
			if(bien_situado){
				switch (brujula) {
					case 0:
						mapasuperficie[fil-1][col] = '_';
					break;
					case 1:
						mapasuperficie[fil][col+1] = '_';
					break;
					case 2:
						mapasuperficie[fil+1][col] = '_';
					break;
					case 3:
						mapasuperficie[fil][col-1] = '_';
					break;
				}
			}
			else{
				switch (brujula) {
					case 0:
						mapaauxsuperficie[fil-1][col] = '_';
					break;
					case 1:
						mapaauxsuperficie[fil][col+1] = '_';
					break;
					case 2:
						mapaauxsuperficie[fil+1][col] = '_';
					break;
					case 3:
						mapaauxsuperficie[fil][col-1] = '_';
					break;
				}
			}
		break;
	}

	if (bien_situado){
		mapaResultado[fil][col]=sensores.terreno[0];

		switch (brujula) {
			case 0:
				mapaResultado[fil-1][col-1] = sensores.terreno[1];
				mapaResultado[fil-1][col] = sensores.terreno[2];
				mapaResultado[fil-1][col+1] = sensores.terreno[3];
				mapaResultado[fil-2][col-2] = sensores.terreno[4];
				mapaResultado[fil-2][col-1] = sensores.terreno[5];
				mapaResultado[fil-2][col] = sensores.terreno[6];
				mapaResultado[fil-2][col+1] = sensores.terreno[7];
				mapaResultado[fil-2][col+2] = sensores.terreno[8];
				mapaResultado[fil-3][col-3] = sensores.terreno[9];
				mapaResultado[fil-3][col-2] = sensores.terreno[10];
				mapaResultado[fil-3][col-1] = sensores.terreno[11];
				mapaResultado[fil-3][col] = sensores.terreno[12];
				mapaResultado[fil-3][col+1] = sensores.terreno[13];
				mapaResultado[fil-3][col+2] = sensores.terreno[14];
				mapaResultado[fil-3][col+3] = sensores.terreno[15];

				mapasuperficie[fil-1][col-1] = sensores.superficie[1];
				mapasuperficie[fil-1][col] = sensores.superficie[2];
				mapasuperficie[fil-1][col+1] = sensores.superficie[3];
				mapasuperficie[fil-2][col-2] = sensores.superficie[4];
				mapasuperficie[fil-2][col-1] = sensores.superficie[5];
				mapasuperficie[fil-2][col] = sensores.superficie[6];
				mapasuperficie[fil-2][col+1] = sensores.superficie[7];
				mapasuperficie[fil-2][col+2] = sensores.superficie[8];
				mapasuperficie[fil-3][col-3] = sensores.superficie[9];
				mapasuperficie[fil-3][col-2] = sensores.superficie[10];
				mapasuperficie[fil-3][col-1] = sensores.superficie[11];
				mapasuperficie[fil-3][col] = sensores.superficie[12];
				mapasuperficie[fil-3][col+1] = sensores.superficie[13];
				mapasuperficie[fil-3][col+2] = sensores.superficie[14];
				mapasuperficie[fil-3][col+3] = sensores.superficie[15];
			break;
			case 1:
				mapaResultado[fil-1][col+1] = sensores.terreno[1];
				mapaResultado[fil][col+1] = sensores.terreno[2];
				mapaResultado[fil+1][col+1] = sensores.terreno[3];
				mapaResultado[fil-2][col+2] = sensores.terreno[4];
				mapaResultado[fil-1][col+2] = sensores.terreno[5];
				mapaResultado[fil][col+2] = sensores.terreno[6];
				mapaResultado[fil+1][col+2] = sensores.terreno[7];
				mapaResultado[fil+2][col+2] = sensores.terreno[8];
				mapaResultado[fil-3][col+3] = sensores.terreno[9];
				mapaResultado[fil-2][col+3] = sensores.terreno[10];
				mapaResultado[fil-1][col+3] = sensores.terreno[11];
				mapaResultado[fil][col+3] = sensores.terreno[12];
				mapaResultado[fil+1][col+3] = sensores.terreno[13];
				mapaResultado[fil+2][col+3] = sensores.terreno[14];
				mapaResultado[fil+3][col+3] = sensores.terreno[15];

				mapasuperficie[fil-1][col+1] = sensores.superficie[1];
				mapasuperficie[fil][col+1] = sensores.superficie[2];
				mapasuperficie[fil+1][col+1] = sensores.superficie[3];
				mapasuperficie[fil-2][col+2] = sensores.superficie[4];
				mapasuperficie[fil-1][col+2] = sensores.superficie[5];
				mapasuperficie[fil][col+2] = sensores.superficie[6];
				mapasuperficie[fil+1][col+2] = sensores.superficie[7];
				mapasuperficie[fil+2][col+2] = sensores.superficie[8];
				mapasuperficie[fil-3][col+3] = sensores.superficie[9];
				mapasuperficie[fil-2][col+3] = sensores.superficie[10];
				mapasuperficie[fil-1][col+3] = sensores.superficie[11];
				mapasuperficie[fil][col+3] = sensores.superficie[12];
				mapasuperficie[fil+1][col+3] = sensores.superficie[13];
				mapasuperficie[fil+2][col+3] = sensores.superficie[14];
				mapasuperficie[fil+3][col+3] = sensores.superficie[15];
			break;
			case 2:
				mapaResultado[fil+1][col+1] = sensores.terreno[1];
				mapaResultado[fil+1][col] = sensores.terreno[2];
				mapaResultado[fil+1][col-1] = sensores.terreno[3];
				mapaResultado[fil+2][col+2] = sensores.terreno[4];
				mapaResultado[fil+2][col+1] = sensores.terreno[5];
				mapaResultado[fil+2][col] = sensores.terreno[6];
				mapaResultado[fil+2][col-1] = sensores.terreno[7];
				mapaResultado[fil+2][col-2] = sensores.terreno[8];
				mapaResultado[fil+3][col+3] = sensores.terreno[9];
				mapaResultado[fil+3][col+2] = sensores.terreno[10];
				mapaResultado[fil+3][col+1] = sensores.terreno[11];
				mapaResultado[fil+3][col] = sensores.terreno[12];
				mapaResultado[fil+3][col-1] = sensores.terreno[13];
				mapaResultado[fil+3][col-2] = sensores.terreno[14];
				mapaResultado[fil+3][col-3] = sensores.terreno[15];

				mapasuperficie[fil+1][col+1] = sensores.superficie[1];
				mapasuperficie[fil+1][col] = sensores.superficie[2];
				mapasuperficie[fil+1][col-1] = sensores.superficie[3];
				mapasuperficie[fil+2][col+2] = sensores.superficie[4];
				mapasuperficie[fil+2][col+1] = sensores.superficie[5];
				mapasuperficie[fil+2][col] = sensores.superficie[6];
				mapasuperficie[fil+2][col-1] = sensores.superficie[7];
				mapasuperficie[fil+2][col-2] = sensores.superficie[8];
				mapasuperficie[fil+3][col+3] = sensores.superficie[9];
				mapasuperficie[fil+3][col+2] = sensores.superficie[10];
				mapasuperficie[fil+3][col+1] = sensores.superficie[11];
				mapasuperficie[fil+3][col] = sensores.superficie[12];
				mapasuperficie[fil+3][col-1] = sensores.superficie[13];
				mapasuperficie[fil+3][col-2] = sensores.superficie[14];
				mapasuperficie[fil+3][col-3] = sensores.superficie[15];
			break;
			case 3:
				mapaResultado[fil+1][col-1] = sensores.terreno[1];
				mapaResultado[fil][col-1] = sensores.terreno[2];
				mapaResultado[fil-1][col-1] = sensores.terreno[3];
				mapaResultado[fil+2][col-2] = sensores.terreno[4];
				mapaResultado[fil+1][col-2] = sensores.terreno[5];
				mapaResultado[fil][col-2] = sensores.terreno[6];
				mapaResultado[fil-1][col-2] = sensores.terreno[7];
				mapaResultado[fil-2][col-2] = sensores.terreno[8];
				mapaResultado[fil+3][col-3] = sensores.terreno[9];
				mapaResultado[fil+2][col-3] = sensores.terreno[10];
				mapaResultado[fil+1][col-3] = sensores.terreno[11];
				mapaResultado[fil][col-3] = sensores.terreno[12];
				mapaResultado[fil-1][col-3] = sensores.terreno[13];
				mapaResultado[fil-2][col-3] = sensores.terreno[14];
				mapaResultado[fil-3][col-3] = sensores.terreno[15];

				mapasuperficie[fil+1][col-1] = sensores.superficie[1];
				mapasuperficie[fil][col-1] = sensores.superficie[2];
				mapasuperficie[fil-1][col-1] = sensores.superficie[3];
				mapasuperficie[fil+2][col-2] = sensores.superficie[4];
				mapasuperficie[fil+1][col-2] = sensores.superficie[5];
				mapasuperficie[fil][col-2] = sensores.superficie[6];
				mapasuperficie[fil-1][col-2] = sensores.superficie[7];
				mapasuperficie[fil-2][col-2] = sensores.superficie[8];
				mapasuperficie[fil+3][col-3] = sensores.superficie[9];
				mapasuperficie[fil+2][col-3] = sensores.superficie[10];
				mapasuperficie[fil+1][col-3] = sensores.superficie[11];
				mapasuperficie[fil][col-3] = sensores.superficie[12];
				mapasuperficie[fil-1][col-3] = sensores.superficie[13];
				mapasuperficie[fil-2][col-3] = sensores.superficie[14];
				mapasuperficie[fil-3][col-3] = sensores.superficie[15];
			break;
		}
	}
	else{
		mapaaux[fil][col]=sensores.terreno[0];

		switch (brujula) {
			case 0:
				mapaaux[fil-1][col-1] = sensores.terreno[1];
				mapaaux[fil-1][col] = sensores.terreno[2];
				mapaaux[fil-1][col+1] = sensores.terreno[3];
				mapaaux[fil-2][col-2] = sensores.terreno[4];
				mapaaux[fil-2][col-1] = sensores.terreno[5];
				mapaaux[fil-2][col] = sensores.terreno[6];
				mapaaux[fil-2][col+1] = sensores.terreno[7];
				mapaaux[fil-2][col+2] = sensores.terreno[8];
				mapaaux[fil-3][col-3] = sensores.terreno[9];
				mapaaux[fil-3][col-2] = sensores.terreno[10];
				mapaaux[fil-3][col-1] = sensores.terreno[11];
				mapaaux[fil-3][col] = sensores.terreno[12];
				mapaaux[fil-3][col+1] = sensores.terreno[13];
				mapaaux[fil-3][col+2] = sensores.terreno[14];
				mapaaux[fil-3][col+3] = sensores.terreno[15];

				mapaauxsuperficie[fil-1][col-1] = sensores.superficie[1];
				mapaauxsuperficie[fil-1][col] = sensores.superficie[2];
				mapaauxsuperficie[fil-1][col+1] = sensores.superficie[3];
				mapaauxsuperficie[fil-2][col-2] = sensores.superficie[4];
				mapaauxsuperficie[fil-2][col-1] = sensores.superficie[5];
				mapaauxsuperficie[fil-2][col] = sensores.superficie[6];
				mapaauxsuperficie[fil-2][col+1] = sensores.superficie[7];
				mapaauxsuperficie[fil-2][col+2] = sensores.superficie[8];
				mapaauxsuperficie[fil-3][col-3] = sensores.superficie[9];
				mapaauxsuperficie[fil-3][col-2] = sensores.superficie[10];
				mapaauxsuperficie[fil-3][col-1] = sensores.superficie[11];
				mapaauxsuperficie[fil-3][col] = sensores.superficie[12];
				mapaauxsuperficie[fil-3][col+1] = sensores.superficie[13];
				mapaauxsuperficie[fil-3][col+2] = sensores.superficie[14];
				mapaauxsuperficie[fil-3][col+3] = sensores.superficie[15];
			break;
			case 1:
				mapaaux[fil-1][col+1] = sensores.terreno[1];
				mapaaux[fil][col+1] = sensores.terreno[2];
				mapaaux[fil+1][col+1] = sensores.terreno[3];
				mapaaux[fil-2][col+2] = sensores.terreno[4];
				mapaaux[fil-1][col+2] = sensores.terreno[5];
				mapaaux[fil][col+2] = sensores.terreno[6];
				mapaaux[fil+1][col+2] = sensores.terreno[7];
				mapaaux[fil+2][col+2] = sensores.terreno[8];
				mapaaux[fil-3][col+3] = sensores.terreno[9];
				mapaaux[fil-2][col+3] = sensores.terreno[10];
				mapaaux[fil-1][col+3] = sensores.terreno[11];
				mapaaux[fil][col+3] = sensores.terreno[12];
				mapaaux[fil+1][col+3] = sensores.terreno[13];
				mapaaux[fil+2][col+3] = sensores.terreno[14];
				mapaaux[fil+3][col+3] = sensores.terreno[15];

				mapaauxsuperficie[fil-1][col+1] = sensores.superficie[1];
				mapaauxsuperficie[fil][col+1] = sensores.superficie[2];
				mapaauxsuperficie[fil+1][col+1] = sensores.superficie[3];
				mapaauxsuperficie[fil-2][col+2] = sensores.superficie[4];
				mapaauxsuperficie[fil-1][col+2] = sensores.superficie[5];
				mapaauxsuperficie[fil][col+2] = sensores.superficie[6];
				mapaauxsuperficie[fil+1][col+2] = sensores.superficie[7];
				mapaauxsuperficie[fil+2][col+2] = sensores.superficie[8];
				mapaauxsuperficie[fil-3][col+3] = sensores.superficie[9];
				mapaauxsuperficie[fil-2][col+3] = sensores.superficie[10];
				mapaauxsuperficie[fil-1][col+3] = sensores.superficie[11];
				mapaauxsuperficie[fil][col+3] = sensores.superficie[12];
				mapaauxsuperficie[fil+1][col+3] = sensores.superficie[13];
				mapaauxsuperficie[fil+2][col+3] = sensores.superficie[14];
				mapaauxsuperficie[fil+3][col+3] = sensores.superficie[15];
			break;
			case 2:
				mapaaux[fil+1][col+1] = sensores.terreno[1];
				mapaaux[fil+1][col] = sensores.terreno[2];
				mapaaux[fil+1][col-1] = sensores.terreno[3];
				mapaaux[fil+2][col+2] = sensores.terreno[4];
				mapaaux[fil+2][col+1] = sensores.terreno[5];
				mapaaux[fil+2][col] = sensores.terreno[6];
				mapaaux[fil+2][col-1] = sensores.terreno[7];
				mapaaux[fil+2][col-2] = sensores.terreno[8];
				mapaaux[fil+3][col+3] = sensores.terreno[9];
				mapaaux[fil+3][col+2] = sensores.terreno[10];
				mapaaux[fil+3][col+1] = sensores.terreno[11];
				mapaaux[fil+3][col] = sensores.terreno[12];
				mapaaux[fil+3][col-1] = sensores.terreno[13];
				mapaaux[fil+3][col-2] = sensores.terreno[14];
				mapaaux[fil+3][col-3] = sensores.terreno[15];

				mapaauxsuperficie[fil+1][col+1] = sensores.superficie[1];
				mapaauxsuperficie[fil+1][col] = sensores.superficie[2];
				mapaauxsuperficie[fil+1][col-1] = sensores.superficie[3];
				mapaauxsuperficie[fil+2][col+2] = sensores.superficie[4];
				mapaauxsuperficie[fil+2][col+1] = sensores.superficie[5];
				mapaauxsuperficie[fil+2][col] = sensores.superficie[6];
				mapaauxsuperficie[fil+2][col-1] = sensores.superficie[7];
				mapaauxsuperficie[fil+2][col-2] = sensores.superficie[8];
				mapaauxsuperficie[fil+3][col+3] = sensores.superficie[9];
				mapaauxsuperficie[fil+3][col+2] = sensores.superficie[10];
				mapaauxsuperficie[fil+3][col+1] = sensores.superficie[11];
				mapaauxsuperficie[fil+3][col] = sensores.superficie[12];
				mapaauxsuperficie[fil+3][col-1] = sensores.superficie[13];
				mapaauxsuperficie[fil+3][col-2] = sensores.superficie[14];
				mapaauxsuperficie[fil+3][col-3] = sensores.superficie[15];
			break;
			case 3:
				mapaaux[fil+1][col-1] = sensores.terreno[1];
				mapaaux[fil][col-1] = sensores.terreno[2];
				mapaaux[fil-1][col-1] = sensores.terreno[3];
				mapaaux[fil+2][col-2] = sensores.terreno[4];
				mapaaux[fil+1][col-2] = sensores.terreno[5];
				mapaaux[fil][col-2] = sensores.terreno[6];
				mapaaux[fil-1][col-2] = sensores.terreno[7];
				mapaaux[fil-2][col-2] = sensores.terreno[8];
				mapaaux[fil+3][col-3] = sensores.terreno[9];
				mapaaux[fil+2][col-3] = sensores.terreno[10];
				mapaaux[fil+1][col-3] = sensores.terreno[11];
				mapaaux[fil][col-3] = sensores.terreno[12];
				mapaaux[fil-1][col-3] = sensores.terreno[13];
				mapaaux[fil-2][col-3] = sensores.terreno[14];
				mapaaux[fil-3][col-3] = sensores.terreno[15];

				mapaauxsuperficie[fil+1][col-1] = sensores.superficie[1];
				mapaauxsuperficie[fil][col-1] = sensores.superficie[2];
				mapaauxsuperficie[fil-1][col-1] = sensores.superficie[3];
				mapaauxsuperficie[fil+2][col-2] = sensores.superficie[4];
				mapaauxsuperficie[fil+1][col-2] = sensores.superficie[5];
				mapaauxsuperficie[fil][col-2] = sensores.superficie[6];
				mapaauxsuperficie[fil-1][col-2] = sensores.superficie[7];
				mapaauxsuperficie[fil-2][col-2] = sensores.superficie[8];
				mapaauxsuperficie[fil+3][col-3] = sensores.superficie[9];
				mapaauxsuperficie[fil+2][col-3] = sensores.superficie[10];
				mapaauxsuperficie[fil+1][col-3] = sensores.superficie[11];
				mapaauxsuperficie[fil][col-3] = sensores.superficie[12];
				mapaauxsuperficie[fil-1][col-3] = sensores.superficie[13];
				mapaauxsuperficie[fil-2][col-3] = sensores.superficie[14];
				mapaauxsuperficie[fil-3][col-3] = sensores.superficie[15];
			break;
		}
	}

	if (sensores.terreno[0]=='K' && !bien_situado){
		x = fil;
		y = col;
		fil = sensores.mensajeF;
		col= sensores.mensajeC;
		cambiarMapa();
		bien_situado = true;
	}

	objdel = ( (sensores.superficie[2] == '0' && (deliberativo || cumplirmisiones)) || (sensores.superficie[2] == '4' && tengoregalo) || (sensores.superficie[2] == '4' && !cumplirmisiones) || (sensores.superficie[2] == 'r' && !tengoregalo) || (sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '4' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
}

bool ComportamientoJugador::tengoObjeto(int fila, int colum){
	if(bien_situado){
		if( (mapasuperficie[fila][colum] == '4' && !cumplirmisiones) || (mapasuperficie[fila][colum] == '4' && tengoregalo) || (mapasuperficie[fila][colum] == 'r' && !tengoregalo) || (mapasuperficie[fila][colum] == '0' ) || (mapasuperficie[fila][colum] == '1' && tengobikini) || (mapasuperficie[fila][colum] == '2' && tengozapatillas) || (mapasuperficie[fila][colum] == '3' && tengollave) || ((mapasuperficie[fila][colum] >= '0' && mapasuperficie[fila][colum] <= '4') && elemmochila > 2)){
			return true;
		}
	}
	else{
		if( (mapaauxsuperficie[fila][colum] == '4' && !cumplirmisiones) || (mapaauxsuperficie[fila][colum] == '4' && tengoregalo) || (mapaauxsuperficie[fila][colum] == 'r' && !tengoregalo) || (mapaauxsuperficie[fila][colum] == '0' ) || (mapaauxsuperficie[fila][colum] == '1' && tengobikini) || (mapaauxsuperficie[fila][colum] == '2' && tengozapatillas) || (mapaauxsuperficie[fila][colum] == '3' && tengollave) || ((mapaauxsuperficie[fila][colum] >= '0' && mapaauxsuperficie[fila][colum] <= '4') && elemmochila > 2)){
			return true;
		}
	}
	return false;
}

bool ComportamientoJugador::puedoPasar(int fila , int colum){
	if(bien_situado){
		if ( (mapaResultado[fila][colum] =='?' && !tengoregalo) || mapaResultado[fila][colum]=='T' || mapaResultado[fila][colum]=='S' || mapaResultado[fila][colum]=='K' || (tengollave && mapaResultado[fila][colum] == 'D') || (tengobikini && mapaResultado[fila][colum] == 'A') || (tengozapatillas && mapaResultado[fila][colum] == 'B')){
			return true;
		}
	}
	else{
		if ( (mapaaux[fila][colum] =='?' && !tengoregalo) || mapaaux[fila][colum]=='T' || mapaaux[fila][colum]=='S' || mapaaux[fila][colum]=='K' || (tengollave && mapaaux[fila][colum] == 'D') || (tengobikini && mapaaux[fila][colum] == 'A')|| (tengozapatillas && mapaaux[fila][colum] == 'B')){
			return true;
		}
	}
	return false;
}

bool ComportamientoJugador::puedoPasar(int fila , int colum, const Sensores &sensores){
	if(bien_situado){
		if (mapaResultado[fila][colum]=='T' || mapaResultado[fila][colum]=='S' || mapaResultado[fila][colum]=='K' || (tengollave && mapaResultado[fila][colum] == 'D') || (tengobikini && mapaResultado[fila][colum] == 'A' && sensores.terreno[0] != 'B') || (tengozapatillas && mapaResultado[fila][colum] == 'B' && sensores.terreno[0] != 'A')){
			return true;
		}
	}
	else{
		if (mapaaux[fila][colum]=='T' || mapaaux[fila][colum]=='S' || mapaaux[fila][colum]=='K' || (tengollave && mapaaux[fila][colum] == 'D') || (tengobikini && mapaaux[fila][colum] == 'A' && sensores.terreno[0] != 'B')|| (tengozapatillas && mapaaux[fila][colum] == 'B' && sensores.terreno[0] != 'A')){
			return true;
		}
	}
	return false;
}

int ComportamientoJugador::derecha(const Sensores &sensores){

	switch (brujula) {
		case 0:
			if( puedoPasar(fil,col+1,sensores) && !objder ){
				if( bien_situado )
					return mapaPasos[fil][col+1];
				return mapaPasosaux[fil][col+1];
			}
			return 50000;
		break;
		case 1:
			if( puedoPasar(fil+1,col,sensores) && !objder ){
				if( bien_situado )
					return mapaPasos[fil+1][col];
				return mapaPasosaux[fil+1][col];
			}
			return 50000;
		break;
		case 2:
			if( puedoPasar(fil,col-1,sensores) && !objder ){
				if( bien_situado )
					return mapaPasos[fil][col-1];
				return mapaPasosaux[fil][col-1];
			}
			return 50000;
		break;
		case 3:
			if( puedoPasar(fil-1,col,sensores) && !objder ){
				if( bien_situado )
					return mapaPasos[fil-1][col];
				return mapaPasosaux[fil-1][col];
			}
			return 50000;
		break;
	}
}

int ComportamientoJugador::izquierda(const Sensores &sensores){

	switch (brujula) {
		case 0:
			if( puedoPasar(fil,col-1,sensores) && !objizq ){
				if( bien_situado )
					return mapaPasos[fil][col-1];
				return mapaPasosaux[fil][col-1];
			}
			return 50000;
		break;
		case 1:
			if( puedoPasar(fil-1,col,sensores) && !objizq ){
				if( bien_situado )
					return mapaPasos[fil-1][col];
				return mapaPasosaux[fil-1][col];
			}
			return 50000;
		break;
		case 2:
			if( puedoPasar(fil,col+1,sensores) && !objizq){
				if( bien_situado )
					return mapaPasos[fil][col+1];
				return mapaPasosaux[fil][col+1];
			}
			return 50000;
		break;
		case 3:
			if( puedoPasar(fil+1,col,sensores) && !objizq){
				if( bien_situado )
					return mapaPasos[fil+1][col];
				return mapaPasosaux[fil+1][col];
			}
			return 50000;
		break;
	}
}

int ComportamientoJugador::delante(const Sensores &sensores){

	switch (brujula) {
		case 0:
			if( puedoPasar(fil-1,col,sensores) && !objdel ){
				if( bien_situado )
					return mapaPasos[fil-1][col];
				return mapaPasosaux[fil-1][col];
			}
			return 50000;
		break;
		case 1:
			if( puedoPasar(fil,col+1,sensores) && !objdel){
				if( bien_situado )
					return mapaPasos[fil][col+1];
				return mapaPasosaux[fil][col+1];
			}
			return 50000;
		break;
		case 2:
			if( puedoPasar(fil+1,col,sensores) && !objdel){
				if( bien_situado )
					return mapaPasos[fil+1][col];
				return mapaPasosaux[fil+1][col];
			}
			return 50000;
		break;
		case 3:
			if( puedoPasar(fil,col-1,sensores) && !objdel){
				if( bien_situado )
					return mapaPasos[fil][col-1];
				return mapaPasosaux[fil][col-1];
			}
			return 50000;
		break;
	}
}

bool ComportamientoJugador::puedoCambiar(const Sensores &sensores){
		if( sensores.terreno[0] == 'A' || sensores.terreno[0] == 'B'){
			return false;
		}
		return true;
}

void ComportamientoJugador::prioridadPuertas(const Sensores &sensores){
	if( sensores.terreno[1] == 'D' && tengollave){
		switch (brujula) {
			case 0:
				if(bien_situado){
					if( mapaPasos[fil-1][col-1] == -1 ){
						mapaPasos[fil-1][col-1] = -2;
					}
				}
				else{
					if( mapaPasosaux[fil-1][col-1] == -1 ){
						mapaPasosaux[fil-1][col-1] = -2;
					}
				}
			break;
			case 3:
				if(bien_situado){
					if( mapaPasos[fil+1][col-1] == -1 ){
						mapaPasos[fil+1][col-1] = -2;
					}
				}
				else{
					if( mapaPasosaux[fil+1][col-1] == -1 ){
						mapaPasosaux[fil+1][col-1] = -2;
					}
				}
			break;
			case 1:
				if(bien_situado){
					if( mapaPasos[fil-1][col+1] == -1 ){
						mapaPasos[fil-1][col+1] = -2;
					}
				}
				else{
					if( mapaPasosaux[fil-1][col+1] == -1 ){
						mapaPasosaux[fil-1][col+1] = -2;
					}
				}
			break;
			case 2:
				if(bien_situado){
					if( mapaPasos[fil+1][col+1] == -1 ){
						mapaPasos[fil+1][col+1] = -2;
					}
				}
				else{
					if( mapaPasosaux[fil+1][col+1] == -1 ){
						mapaPasosaux[fil+1][col+1] = -2;
					}
				}
			break;
		}
	}

	if( sensores.terreno[3] == 'D' && tengollave){
		switch (brujula) {
			case 0:
				if(bien_situado){
					if( mapaPasos[fil-1][col+1] == -1 ){
						mapaPasos[fil-1][col+1] = -2;
					}
				}
				else{
					if( mapaPasosaux[fil-1][col+1] == -1 ){
						mapaPasosaux[fil-1][col+1] = -2;
					}
				}
			break;
			case 3:
				if(bien_situado){
					if( mapaPasos[fil-1][col-1] == -1 ){
						mapaPasos[fil-1][col-1] = -2;
					}
				}
				else{
					if( mapaPasosaux[fil-1][col-1] == -1 ){
						mapaPasosaux[fil-1][col-1] = -2;
					}
				}
			break;
			case 1:
				if(bien_situado){
					if( mapaPasos[fil+1][col+1] == -1 ){
						mapaPasos[fil+1][col+1] = -2;
					}
				}
				else{
					if( mapaPasosaux[fil+1][col+1] == -1 ){
						mapaPasosaux[fil+1][col+1] = -2;
					}
				}
			break;
			case 2:
				if(bien_situado){
					if( mapaPasos[fil+1][col-1] == -1 ){
						mapaPasos[fil+1][col-1] = -2;
					}
				}
				else{
					if( mapaPasosaux[fil+1][col-1] == -1 ){
						mapaPasosaux[fil+1][col-1] = -2;
					}
				}
			break;
		}
	}
}

Action ComportamientoJugador::Nueva_Accion(const Sensores &sensores){
	Action accion;

	if( kizq && !kdel ){
		accion = actTURN_L;
		kizq = kdel = kdetras = kder = false;
	}
	else if( (kdetras && !kdel) || doblegiro ){
		accion = actTURN_L;
		if( doblegiro ){
			doblegiro = false;
		}
		else{
			doblegiro = true;
		}
		kizq = kdel = kdetras = kder = false;
	}
	else if( kder && !kdel ){
		accion = actTURN_R;
		kizq = kdel = kdetras = kder = false;
	}
	else if( sacarobjeto ){
		accion = actPOP;
		elemmochila--;
		sacarobjeto = false;
	}
	else if( girosizq == 12 && izquierda(sensores) != 50000){
		accion = actTURN_L;
		doblegiro = true;
		girosizq = 0;
	}
	else if( girosder == 12 && izquierda(sensores) != 50000){
		accion = actTURN_L;
		doblegiro = true;
		girosder= 0;
	}
	else if( sensores.superficie[2] == '4' && !tengoregalo && cumplirmisiones && puedoCambiar(sensores) && elemmochila < 3){
		if( sensores.objetoActivo == '_' ){
			accion = actPICKUP;
			tengoregalo = true;
			if( sensores.mochila != '_' ){
				elemmochila++;
			}
		}
		else{
			if( sensores.objetoActivo == '0' ){
				elemmochila--;
				accion = actTHROW;
				tengohueso = false;
			}
			else{
					accion = actPUSH;
			}
		}
	}
	else if( sensores.superficie[2] == '0' && !tengohueso && !deliberativo && !cumplirmisiones && puedoCambiar(sensores) && elemmochila < 3 ){
		if( sensores.objetoActivo == '_' ){
			accion = actPICKUP;
			tengohueso = true;
			if( sensores.mochila != '_' ){
				elemmochila++;
			}
		}
		else{
			if( sensores.objetoActivo == '0' ){
				elemmochila--;
				accion = actTHROW;
				tengohueso = false;
			}
			else{
					accion = actPUSH;
			}
		}
	}
	else if( sensores.superficie[2] == '1' && !tengobikini && puedoCambiar(sensores) && elemmochila < 3){
			if( sensores.objetoActivo == '_' ){
				accion = actPICKUP;
				tengobikini = true;
				if( sensores.mochila != '_' ){
					elemmochila++;
				}
			}
			else{
				if( sensores.objetoActivo == '0' ){
					elemmochila--;
					accion = actTHROW;
					tengohueso = false;
				}
				else{
						accion = actPUSH;
				}
			}
	}
	else if( sensores.superficie[2] == '2'  && !tengozapatillas && puedoCambiar(sensores) && elemmochila < 3){
			if( sensores.objetoActivo == '_' ){
				accion = actPICKUP;
				tengozapatillas = true;
				if( sensores.mochila != '_' ){
					elemmochila++;
				}
			}
			else{
				if( sensores.objetoActivo == '0' ){
					elemmochila--;
					accion = actTHROW;
					tengohueso = false;
				}
				else{
						accion = actPUSH;
				}
			}
	}
	else if( sensores.superficie[2] == '3' && !tengollave && puedoCambiar(sensores) && elemmochila < 3){
		if( sensores.objetoActivo == '_' ){
			accion = actPICKUP;
			tengollave = true;
			if( sensores.mochila != '_' ){
				elemmochila++;
			}
		}
		else{
			if( sensores.objetoActivo == '0' ){
				elemmochila--;
				accion = actTHROW;
				tengohueso = false;
			}
			else{
					accion = actPUSH;
			}
		}
	}
	else if( sensores.superficie[2] == 'd' && tengollave && puedoCambiar(sensores) && elemmochila < 4 ){
		if( sensores.objetoActivo != '3' ){
			if( sensores.objetoActivo == '0' ){
				elemmochila--;
				accion = actTHROW;
				tengohueso = false;
			}
			else{
					accion = actPUSH;
			}
			sacarobjeto = true;
			if( sensores.mochila != '_' ){
				elemmochila++;
			}
		}
		else{
			accion = actGIVE;
		}
	}
	else if( sensores.superficie[2] == 'r' && tengoregalo && puedoCambiar(sensores) && elemmochila < 4 ){
		if( sensores.objetoActivo != '4' ){
			if( sensores.objetoActivo == '0' ){
				elemmochila--;
				accion = actTHROW;
				tengohueso = false;
			}
			else{
					accion = actPUSH;
			}
			sacarobjeto = true;
			if( sensores.mochila != '_' ){
				elemmochila++;
			}
		}
		else{
			plan.clear();
			if( elemmochila > 0 ){
				plan.push_back(actPOP);
				deliberativo = true;
				elemmochila--;
			}
			accion = actGIVE;
			tengoregalo = false;
			reubicar = true;
		}
	}
	else if( (sensores.terreno[2] == 'A' && tengobikini && puedoCambiar(sensores) && sensores.objetoActivo != '1' ) && elemmochila < 4){
		elemmochila++;
		if( sensores.objetoActivo == '0' ){
			elemmochila--;
			accion = actTHROW;
			tengohueso = false;
		}
		else{
				accion = actPUSH;
		}
		sacarobjeto = true;
	}
	else if( sensores.terreno[2] == 'B' && tengozapatillas && puedoCambiar(sensores) && sensores.objetoActivo != '2' && elemmochila < 4 ){
		elemmochila++;
		if( sensores.objetoActivo == '0' ){
			elemmochila--;
			accion = actTHROW;
			tengohueso = false;
		}
		else{
				accion = actPUSH;
		}
		sacarobjeto = true;
	}
	else if( sensores.superficie[2] == 'l' && tengohueso && sensores.objetoActivo == '0'){
			accion = actGIVE;
			if( elemmochila > 0 ){
				sacarobjeto = true;
			}
			tengohueso = false;
	}
	else if( delante(sensores) < derecha(sensores) && delante(sensores) < izquierda(sensores) ){
		accion = actFORWARD;
	}
	else if( izquierda(sensores) < derecha(sensores) && izquierda(sensores) < delante(sensores) ){
		accion = actTURN_L;
		girosizq++;
		if(girosder != 0) girosder = 0;
	}
	else if( derecha(sensores) < izquierda(sensores) && derecha(sensores) < delante(sensores) ){
		accion = actTURN_R;
		girosder++;
		if(girosizq != 0) girosizq = 0;
	}
	else if( delante(sensores) == -2 ){										//PRIMERO DAMOS PRIORIDAD AL -2;
		accion = actFORWARD;
	}
	else if( izquierda(sensores) == -2 ){
		accion = actTURN_L;
		girosizq++;
		if(girosder != 0) girosder = 0;
	}
	else if( derecha(sensores) == -2 ){
		accion = actTURN_R;
		girosder++;
		if(girosizq != 0) girosizq = 0;
	}
	else if( delante(sensores) == -1  ){
		accion = actFORWARD;
	}
	else if( izquierda(sensores) == -1 ){
		accion = actTURN_L;
		girosizq++;
		if(girosder != 0) girosder = 0;
	}
	else if( derecha(sensores) == -1 ){
		accion = actTURN_R;
		girosder++;
		if(girosizq != 0) girosizq = 0;
	}
	else{
		accion = (rand()%2==0)?actTURN_R:actTURN_L;
	}

	return accion;
}

void ComportamientoJugador::actualizarSuperficie(const Action &accionactual,const Sensores &sensores){
	switch (accionactual){
		case actFORWARD:
			objdetras = false;
			objder = ( (sensores.superficie[3] == '0' && (deliberativo || cumplirmisiones)) || (sensores.superficie[3] == '4' && tengoregalo) || (sensores.superficie[3] == '4' && !cumplirmisiones) || (sensores.superficie[3] == 'r' && !tengoregalo) || (sensores.superficie[3] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[3] == 'a' || (sensores.superficie[3] == '0' && tengohueso) || (sensores.superficie[3] == '1' && tengobikini) || (sensores.superficie[3] == '2' && tengozapatillas) || (sensores.superficie[3] == '3' && tengollave) || (sensores.superficie[3] >= '0' && sensores.superficie[3] <= '4' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
			objizq = ( (sensores.superficie[1] == '0' && (deliberativo || cumplirmisiones)) || (sensores.superficie[1] == '4' && tengoregalo) || (sensores.superficie[1] == '4' && !cumplirmisiones) || (sensores.superficie[1] == 'r' && !tengoregalo) || (sensores.superficie[1] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[1] == 'a' || (sensores.superficie[1] == '0' && tengohueso) || (sensores.superficie[1] == '1' && tengobikini) || (sensores.superficie[1] == '2' && tengozapatillas) || (sensores.superficie[1] == '3' && tengollave) || (sensores.superficie[1] >= '0' && sensores.superficie[1] <= '4' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
		break;
		case actTURN_L:
			objizq = objdetras;
			objdetras = objder;
			objder = ( (sensores.superficie[2] == '0' && (deliberativo || cumplirmisiones)) || (sensores.superficie[2] == '4' && tengoregalo) || (sensores.superficie[2] == '4' && !cumplirmisiones) || (sensores.superficie[2] == 'r' && !tengoregalo) || (sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '4' && (elemmochila > 2 || !puedoCambiar(sensores)) ))?true:false;
		break;
		case actTURN_R:
			objder = objdetras;
			objdetras = objizq;
			objizq = ( (sensores.superficie[2] == '0' && (deliberativo || cumplirmisiones)) || (sensores.superficie[2] == '4' && tengoregalo) || (sensores.superficie[2] == '4' && !cumplirmisiones) || (sensores.superficie[2] == 'r' && !tengoregalo) || (sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '4' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
		break;
	}
}

void ComportamientoJugador::rellenarMapa(){
	for( int i = 0; i < 3; i++ ){
		for( int j = 0; j <= max+3; j++){
			mapaResultado[i][j] = 'P';
		}
	}
	for( int i = max+1; i <= max+3; i++ ){
		for( int j = 0; j <= max+3; j++){
			mapaResultado[i][j] = 'P';
		}
	}
	for( int i = 0; i <= max+3; i++ ){
		for( int j = 0; j < 3; j++){
			mapaResultado[i][j] = 'P';
		}
	}
	for( int i = 0; i <= max+3; i++ ){
		for( int j = max+1; j <= max+3; j++){
			mapaResultado[i][j] = 'P';
		}
	}

}

bool ComportamientoJugador::tengoK(const Sensores &sensores){
	for( int i = 0; i < 16; i++){
		if( sensores.terreno[i] == 'K' )
			return true;
	}
	return false;
}

int ComportamientoJugador::distanciaPuntos(const estado &origen, const estado &destino){
	int co = abs(origen.columna-destino.columna);
	int fi = abs(origen.fila-destino.fila);

 	return (fi+co+1);
}

bool ComportamientoJugador::pathFinding(const estado &origen, const estado &destino, const Sensores &sensores){
	bool encontrado = false;
	bool estacerrados = false;
	bool estaabiertos = false;
	bool inserta = false;
	bool seguir = true;
	int gc;
	list<Nodo>::iterator it2;
	Nodo n;
	estado o,e;
	plan.clear();
	abiertos.clear();
	cerrados.clear();

	Nodo ori(origen,NULL,0,distanciaPuntos(origen,destino));
	abiertos.push_back(ori);
	while( !abiertos.empty() && !encontrado){
		cerrados.push_back(abiertos.back());
		abiertos.pop_back();

		if( cerrados.back() == destino){
			encontrado = true;
		}
		else if( bien_situado && mapaResultado[cerrados.back().getEstado().fila][cerrados.back().getEstado().columna] == '?' && !tengoregalo ){
			encontrado = true;
		}
		else if( cerrados.size() > 2500 ){
			return false;
		}
		else{
			if( puedoPasar(cerrados.back().getEstado().fila+1,cerrados.back().getEstado().columna) && !tengoObjeto(cerrados.back().getEstado().fila+1,cerrados.back().getEstado().columna) ){
				estacerrados = estaabiertos = inserta = false;
				seguir = true;
				e.fila = cerrados.back().getEstado().fila+1;
				e.columna = cerrados.back().getEstado().columna;
				e.orientacion = 2;
				if( cerrados.back().getEstado().orientacion == 2 ) gc = 1;
				if( cerrados.back().getEstado().orientacion == 0 ) gc = 3;
				if( cerrados.back().getEstado().orientacion == 1 || cerrados.back().getEstado().orientacion == 3 ) gc = 2;
				n.crear(e,&cerrados.back(),cerrados.back().getG()+gc,distanciaPuntos(e,destino));
				for(auto it = cerrados.begin(); it != cerrados.end(); ++it){
					if( *it == n ){
						estacerrados = true;
					}
				}
				for(auto it = abiertos.begin(); it != abiertos.end(); ++it){
					if( *it == n ){
						estaabiertos = true;
						it2 = it;
					}
				}

				if(!estacerrados){
					if(estaabiertos){
						if( n.getG() < it2->getG() ){
							abiertos.erase(it2);
							inserta = true;
						}
						else{
							inserta = false;
						}
					}
					else{
						inserta = true;
					}
					if(bien_situado){
						if((mapaResultado[n.getEstado().fila][n.getEstado().columna] == 'B' && mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A') || (mapaResultado[n.getEstado().fila][n.getEstado().columna] == 'A' && mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B') || (((mapasuperficie[n.getEstado().fila][n.getEstado().columna] >= '0' && mapasuperficie[n.getEstado().fila][n.getEstado().columna] <= '4') || (mapasuperficie[n.getEstado().fila][n.getEstado().columna] == 'r')) && (mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B' || mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A'))){
							seguir = false;
						}
					}
					else if( !bien_situado){
						if((mapaaux[n.getEstado().fila][n.getEstado().columna] == 'B' && mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A') || (mapaaux[n.getEstado().fila][n.getEstado().columna] == 'A' && mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B') || (((mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] >= '0' && mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] <= '4') || (mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] == 'r')) && (mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B' || mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A'))){
							seguir = false;
						}
					}
					if(inserta && seguir){
						if(abiertos.empty()){
							abiertos.push_back(n);
						}
						else{
							if( (abiertos.front().getG()+abiertos.front().getH()) <= (n.getG()+n.getH()) ){
								if(abiertos.size() == 1 && (abiertos.front().getG()+abiertos.front().getH()) == (n.getG()+n.getH())){
									abiertos.push_back(n);
								}
								else{
									abiertos.push_front(n);
								}
							}
							else if((abiertos.back().getG()+abiertos.back().getH()) >= (n.getG()+n.getH())){
								abiertos.push_back(n);
							}
							else{
								bool insertado = false;
								for(auto it = abiertos.begin(); it != abiertos.end() && !insertado; ++it){
									if((n.getG()+n.getH()) == (it->getG()+it->getH())){
										if(n.getG() > it->getG()){
											abiertos.insert(it,n);
											insertado = true;
										}
									}
									else if((n.getG()+n.getH()) > (it->getG()+it->getH())){
										abiertos.insert(it,n);
										insertado = true;
									}
								}
							}
						}
					}
				}
			}
			if( puedoPasar(cerrados.back().getEstado().fila,cerrados.back().getEstado().columna+1) && !tengoObjeto(cerrados.back().getEstado().fila,cerrados.back().getEstado().columna+1) ){
				estacerrados = estaabiertos = inserta = false;
				seguir = true;
				e.fila = cerrados.back().getEstado().fila;
				e.columna = cerrados.back().getEstado().columna+1;
				e.orientacion = 1;
				if( cerrados.back().getEstado().orientacion == 1 ) gc = 1;
				if( cerrados.back().getEstado().orientacion == 3 ) gc = 3;
				if( cerrados.back().getEstado().orientacion == 0 || cerrados.back().getEstado().orientacion == 2 ) gc = 2;
				n.crear(e,&cerrados.back(),cerrados.back().getG()+gc,distanciaPuntos(e,destino));

				for(auto it = cerrados.begin(); it != cerrados.end(); ++it){
					if( *it == n ){
						estacerrados = true;
					}
				}
				for(auto it = abiertos.begin(); it != abiertos.end(); ++it){
					if( *it == n ){
						estaabiertos = true;
						it2 = it;
					}
				}
				if(!estacerrados){
					if(estaabiertos){
						if( n.getG() < it2->getG() ){
							abiertos.erase(it2);
							inserta = true;
						}
						else{
							inserta = false;
						}
					}
					else{
						inserta = true;
					}
					if(bien_situado){
						if((mapaResultado[n.getEstado().fila][n.getEstado().columna] == 'B' && mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A') || (mapaResultado[n.getEstado().fila][n.getEstado().columna] == 'A' && mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B') || (((mapasuperficie[n.getEstado().fila][n.getEstado().columna] >= '0' && mapasuperficie[n.getEstado().fila][n.getEstado().columna] <= '4') || (mapasuperficie[n.getEstado().fila][n.getEstado().columna] == 'r')) && (mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B' || mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A'))){
							seguir = false;
						}
					}
					else{
						if((mapaaux[n.getEstado().fila][n.getEstado().columna] == 'B' && mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A') || (mapaaux[n.getEstado().fila][n.getEstado().columna] == 'A' && mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B') || (((mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] >= '0' && mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] <= '4') || (mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] == 'r')) && (mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B' || mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A'))){
							seguir = false;
						}
					}
					if(inserta && seguir){
						if(abiertos.empty()){
							abiertos.push_back(n);
						}
						else{
							if( (abiertos.front().getG()+abiertos.front().getH()) <= (n.getG()+n.getH()) ){
								if(abiertos.size() == 1 && (abiertos.front().getG()+abiertos.front().getH()) == (n.getG()+n.getH())){
									abiertos.push_back(n);
								}
								else{
									abiertos.push_front(n);
								}
							}
							else if((abiertos.back().getG()+abiertos.back().getH()) >= (n.getG()+n.getH())){
								abiertos.push_back(n);
							}
							else{
								bool insertado = false;
								for(auto it = abiertos.begin(); it != abiertos.end() && !insertado; ++it){
									if((n.getG()+n.getH()) == (it->getG()+it->getH())){
										if(n.getG() > it->getG()){
											abiertos.insert(it,n);
											insertado = true;
										}
									}
									else if((n.getG()+n.getH()) > (it->getG()+it->getH())){
										abiertos.insert(it,n);
										insertado = true;
									}
								}
							}
						}
					}
				}
			}
			if( puedoPasar(cerrados.back().getEstado().fila,cerrados.back().getEstado().columna-1) && !tengoObjeto(cerrados.back().getEstado().fila,cerrados.back().getEstado().columna-1) ){
				estacerrados = estaabiertos = inserta = false;
				seguir = true;
				e.fila = cerrados.back().getEstado().fila;
				e.columna = cerrados.back().getEstado().columna-1;
				e.orientacion = 3;
				if( cerrados.back().getEstado().orientacion == 3 ) gc = 1;
				if( cerrados.back().getEstado().orientacion == 1 ) gc = 3;
				if( cerrados.back().getEstado().orientacion == 0 || cerrados.back().getEstado().orientacion == 2 ) gc = 2;
				n.crear(e,&cerrados.back(),cerrados.back().getG()+gc,distanciaPuntos(e,destino));

				for(auto it = cerrados.begin(); it != cerrados.end(); ++it){
					if( *it == n ){
						estacerrados = true;
					}
				}
				for(auto it = abiertos.begin(); it != abiertos.end(); ++it){
					if( *it == n ){
						estaabiertos = true;
						it2 = it;
					}
				}

				if(!estacerrados){
					if(estaabiertos){
						if( n.getG() < it2->getG() ){
							abiertos.erase(it2);
							inserta = true;
						}
						else{
							inserta = false;
						}
					}
					else{
						inserta = true;
					}
					if(bien_situado){
						if((mapaResultado[n.getEstado().fila][n.getEstado().columna] == 'B' && mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A') || (mapaResultado[n.getEstado().fila][n.getEstado().columna] == 'A' && mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B') || (((mapasuperficie[n.getEstado().fila][n.getEstado().columna] >= '0' && mapasuperficie[n.getEstado().fila][n.getEstado().columna] <= '4') || (mapasuperficie[n.getEstado().fila][n.getEstado().columna] == 'r')) && (mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B' || mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A'))){
							seguir = false;
						}
					}
					else{
						if((mapaaux[n.getEstado().fila][n.getEstado().columna] == 'B' && mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A') || (mapaaux[n.getEstado().fila][n.getEstado().columna] == 'A' && mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B') || (((mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] >= '0' && mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] <= '4') || (mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] == 'r')) && (mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B' || mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A'))){
							seguir = false;
						}
					}
					if(inserta && seguir){
						if(abiertos.empty()){
							abiertos.push_back(n);
						}
						else{
							if( (abiertos.front().getG()+abiertos.front().getH()) <= (n.getG()+n.getH()) ){
								if(abiertos.size() == 1 && (abiertos.front().getG()+abiertos.front().getH()) == (n.getG()+n.getH())){
									abiertos.push_back(n);
								}
								else{
									abiertos.push_front(n);
								}
							}
							else if((abiertos.back().getG()+abiertos.back().getH()) >= (n.getG()+n.getH())){
								abiertos.push_back(n);
							}
							else{
								bool insertado = false;
								for(auto it = abiertos.begin(); it != abiertos.end() && !insertado; ++it){
									if((n.getG()+n.getH()) == (it->getG()+it->getH())){
										if(n.getG() > it->getG()){
											abiertos.insert(it,n);
											insertado = true;
										}
									}
									else if((n.getG()+n.getH()) > (it->getG()+it->getH())){
										abiertos.insert(it,n);
										insertado = true;
									}
								}
							}
						}
					}
				}
			}
			if( puedoPasar(cerrados.back().getEstado().fila-1,cerrados.back().getEstado().columna) && !tengoObjeto(cerrados.back().getEstado().fila-1,cerrados.back().getEstado().columna)){
				estacerrados = estaabiertos = inserta = false;
				seguir = true;
				e.fila = cerrados.back().getEstado().fila-1;
				e.columna = cerrados.back().getEstado().columna;
				e.orientacion = 0;
				if( cerrados.back().getEstado().orientacion == 0 ) gc = 1;
				if( cerrados.back().getEstado().orientacion == 2 ) gc = 3;
				if( cerrados.back().getEstado().orientacion == 1 || cerrados.back().getEstado().orientacion == 3 ) gc = 2;
				n.crear(e,&cerrados.back(),cerrados.back().getG()+gc,distanciaPuntos(e,destino));
				for(auto it = cerrados.begin(); it != cerrados.end(); ++it){
					if( *it == n ){
						estacerrados = true;
					}
				}
				for(auto it = abiertos.begin(); it != abiertos.end(); ++it){
					if( *it == n ){
						estaabiertos = true;
						it2 = it;
					}
				}
				if(!estacerrados){
					if(estaabiertos){
						if( n.getG() < it2->getG() ){
							abiertos.erase(it2);
							inserta = true;
						}
						else{
							inserta = false;
						}
					}
					else{
						inserta = true;
					}
					if(bien_situado){
						if((mapaResultado[n.getEstado().fila][n.getEstado().columna] == 'B' && mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A') || (mapaResultado[n.getEstado().fila][n.getEstado().columna] == 'A' && mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B') || (((mapasuperficie[n.getEstado().fila][n.getEstado().columna] >= '0' && mapasuperficie[n.getEstado().fila][n.getEstado().columna] <= '4') || (mapasuperficie[n.getEstado().fila][n.getEstado().columna] == 'r')) && (mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B' || mapaResultado[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A'))){
							seguir = false;
						}
					}
					else{
						if((mapaaux[n.getEstado().fila][n.getEstado().columna] == 'B' && mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A') || (mapaaux[n.getEstado().fila][n.getEstado().columna] == 'A' && mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B') || (((mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] >= '0' && mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] <= '4') || (mapaauxsuperficie[n.getEstado().fila][n.getEstado().columna] == 'r')) && (mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'B' || mapaaux[n.getPadre()->getEstado().fila][n.getPadre()->getEstado().columna] == 'A'))){
							seguir = false;
						}
					}
					if(inserta && seguir){
						if(abiertos.empty()){
							abiertos.push_back(n);
						}
						else{
							if( (abiertos.front().getG()+abiertos.front().getH()) <= (n.getG()+n.getH()) ){
								if(abiertos.size() == 1 && (abiertos.front().getG()+abiertos.front().getH()) == (n.getG()+n.getH())){
									abiertos.push_back(n);
								}
								else{
									abiertos.push_front(n);
								}
							}
							else if((abiertos.back().getG()+abiertos.back().getH()) >= (n.getG()+n.getH())){
								abiertos.push_back(n);
							}
							else{
								bool insertado = false;
								for(auto it = abiertos.begin(); it != abiertos.end() && !insertado; ++it){
									if((n.getG()+n.getH()) == (it->getG()+it->getH())){
										if(n.getG() > it->getG()){
											abiertos.insert(it,n);
											insertado = true;
										}
									}
									else if((n.getG()+n.getH()) > (it->getG()+it->getH())){
										abiertos.insert(it,n);
										insertado = true;
									}
								}
							}
						}
					}
				}
			}
		}
		// if(n.getEstado().fila == 10 and n.getEstado().columna == 19){
		// 	cout << endl << n.getEstado().orientacion << endl;
		// 	cin.get();
		// }
		// if(paso > 1000){
		// 	cout << "ABIERTOS:" << endl;
		// 	for(auto it = abiertos.begin(); it != abiertos.end();++it){
		// 		cout << it->getEstado().fila << "," << it->getEstado().columna << " " << it->getG()+it->getH() << " " << it->getEstado().orientacion << endl;
		// 	}
		// 	cout << endl << "CERRADOS" << endl;
		// 	for(auto it = cerrados.begin(); it != cerrados.end();++it){
		// 		cout << it->getEstado().fila << "," << it->getEstado().columna << " " << it->getG()+it->getH() << " " << it->getEstado().orientacion << endl;
		// 	}
		// 	cout << "-----------------------" << endl;
		// 	cin.get();
		// }
	}
	if( !encontrado ){
		return false;
	}
	Nodo aux = cerrados.back();
	while(aux.getPadre() != 0){
		Nodo *p = aux.getPadre();

		switch (aux.getEstado().orientacion) {
			case 0:
				switch (p->getEstado().orientacion) {
					case 0:
						plan.push_back(actFORWARD);
					break;
					case 1:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_L);
					break;
					case 2:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_L);
						plan.push_back(actTURN_L);
					break;
					case 3:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_R);
					break;
				}
			break;
			case 1:
				switch (p->getEstado().orientacion) {
					case 0:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_R);
					break;
					case 1:
						plan.push_back(actFORWARD);
					break;
					case 2:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_L);
					break;
					case 3:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_L);
						plan.push_back(actTURN_L);
					break;
				}
			break;
			case 2:
				switch (p->getEstado().orientacion) {
					case 0:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_L);
						plan.push_back(actTURN_L);
					break;
					case 1:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_R);
					break;
					case 2:
						plan.push_back(actFORWARD);
					break;
					case 3:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_L);
					break;
				}
			break;
			case 3:
				switch (p->getEstado().orientacion) {
					case 0:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_L);
					break;
					case 1:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_L);
						plan.push_back(actTURN_L);
					break;
					case 2:
						plan.push_back(actFORWARD);
						plan.push_back(actTURN_R);
					break;
					case 3:
						plan.push_back(actFORWARD);
					break;
				}
			break;
		}
		aux = *p;
	}

	return true;
}

void ComportamientoJugador::buscarK(const Sensores &sensores){
	estado ori,dest;
	for(int i = 0; i < sensores.terreno.size(); i++){
		if( sensores.terreno[i] == 'K' ){
			switch (i) {
				case 1:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-1,col-1);
						break;
						case 1:
							dest.crear(fil-1,col+1);
						break;
						case 2:
							dest.crear(fil+1,col+1);
						break;
						case 3:
							dest.crear(fil+1,col-1);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 2:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-1,col);
						break;
						case 1:
							dest.crear(fil,col+1);
						break;
						case 2:
							dest.crear(fil+1,col);
						break;
						case 3:
							dest.crear(fil,col-1);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 3:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-1,col+1);
						break;
						case 1:
							dest.crear(fil+1,col+1);
						break;
						case 2:
							dest.crear(fil+1,col-1);
						break;
						case 3:
							dest.crear(fil-1,col-1);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 4:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-2,col-2);
						break;
						case 1:
							dest.crear(fil-2,col+2);
						break;
						case 2:
							dest.crear(fil+2,col+2);
						break;
						case 3:
							dest.crear(fil+2,col-2);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 5:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-2,col-1);
						break;
						case 1:
							dest.crear(fil-1,col+2);
						break;
						case 2:
							dest.crear(fil+2,col+1);
						break;
						case 3:
							dest.crear(fil+1,col-2);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 6:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-2,col);
						break;
						case 1:
							dest.crear(fil,col+2);
						break;
						case 2:
							dest.crear(fil+2,col);
						break;
						case 3:
							dest.crear(fil,col-2);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 7:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-2,col+1);
						break;
						case 1:
							dest.crear(fil+1,col+2);
						break;
						case 2:
							dest.crear(fil+2,col-1);
						break;
						case 3:
							dest.crear(fil-1,col-2);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 8:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-2,col+2);
						break;
						case 1:
							dest.crear(fil+2,col+2);
						break;
						case 2:
							dest.crear(fil+2,col-2);
						break;
						case 3:
							dest.crear(fil-2,col-2);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 9:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-3,col-3);
						break;
						case 1:
							dest.crear(fil-3,col+3);
						break;
						case 2:
							dest.crear(fil+3,col+3);
						break;
						case 3:
							dest.crear(fil+3,col-3);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 10:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-3,col-2);
						break;
						case 1:
							dest.crear(fil-2,col+3);
						break;
						case 2:
							dest.crear(fil+3,col+2);
						break;
						case 3:
							dest.crear(fil+2,col-3);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 11:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-3,col-1);
						break;
						case 1:
							dest.crear(fil-1,col+3);
						break;
						case 2:
							dest.crear(fil+3,col+1);
						break;
						case 3:
							dest.crear(fil+1,col-3);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 12:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-3,col);
						break;
						case 1:
							dest.crear(fil,col+3);
						break;
						case 2:
							dest.crear(fil+3,col);
						break;
						case 3:
							dest.crear(fil,col-3);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 13:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-3,col+1);
						break;
						case 1:
							dest.crear(fil+1,col+3);
						break;
						case 2:
							dest.crear(fil+3,col-1);
						break;
						case 3:
							dest.crear(fil-1,col-3);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 14:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-3,col+2);
						break;
						case 1:
							dest.crear(fil+2,col+3);
						break;
						case 2:
							dest.crear(fil+3,col-2);
						break;
						case 3:
							dest.crear(fil-2,col-3);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
				case 15:
					ori.crear(fil,col,brujula);
					switch (brujula) {
						case 0:
							dest.crear(fil-3,col+3);
						break;
						case 1:
							dest.crear(fil+3,col+3);
						break;
						case 2:
							dest.crear(fil+3,col-3);
						break;
						case 3:
							dest.crear(fil-3,col-3);
						break;
					}
					deliberativo = pathFinding(ori,dest,sensores);
				break;
			}
		}
	}
}

void ComportamientoJugador::guardarPaso(const Sensores &sensores){
	paso++;
	if(bien_situado){
		mapaPasos[fil][col] = paso;
	}
	else{
		mapaPasosaux[fil][col] = paso;
	}
}

Action ComportamientoJugador::calcularNuevaAccion(const Sensores &sensores){
	Action accion;

	prioridadPuertas(sensores);

	if( rotar ){
		accion = actTURN_L;
		switch (nrotaciones) {
			case 0:
				accion = actIDLE;
			break;
			case 1:
			if( tengoK(sensores) )
				kdel = true;
			break;
			case 2:
				objizq = ( (sensores.superficie[2] == '0' && (deliberativo || cumplirmisiones)) || (sensores.superficie[2] == '4' && tengoregalo) || (sensores.superficie[2] == '4' && !cumplirmisiones) || (sensores.superficie[2] == 'r' && !tengoregalo) || (sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '4' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
				if( tengoK(sensores) )
					kizq = true;
			break;
			case 3:
				objdetras = ( (sensores.superficie[2] == '0' && (deliberativo || cumplirmisiones)) || (sensores.superficie[2] == '4' && tengoregalo) || (sensores.superficie[2] == '4' && !cumplirmisiones) || (sensores.superficie[2] == 'r' && !tengoregalo) || (sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '4' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
				if( tengoK(sensores) )
					kdetras = true;
			break;
			case 4:
				objder = ( (sensores.superficie[2] == '0' && (deliberativo || cumplirmisiones)) || (sensores.superficie[2] == '4' && tengoregalo) || (sensores.superficie[2] == '4' && !cumplirmisiones) || (sensores.superficie[2] == 'r' && !tengoregalo) || (sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '4' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
				rotar = false;
				brujula = 1;
				if( tengoK(sensores) )
					kder = true;
			break;
		}
		nrotaciones++;
	}
	else{
		accion = Nueva_Accion(sensores);
	}

	return accion;
}

bool ComportamientoJugador::errorDelibNuevoMovimiento(const Sensores &sensores){
	if(plan.back() == actFORWARD && ( (sensores.superficie[2] == 'l' && sensores.objetoActivo == '0') || sensores.superficie[2] == 'd' || (sensores.terreno[2] == 'B' && sensores.objetoActivo != '2') || (sensores.terreno[2] == 'A' && sensores.objetoActivo != '1') || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '4') || sensores.superficie[2] == 'r')){
		return true;
	}
	else if( plan.back() == actFORWARD && (sensores.terreno[2] == 'M' || sensores.terreno[2] == 'P') ){
		plan.clear();
		deliberativo = false;
		return true;
	}
	return false;
}

bool ComportamientoJugador::errorDelibEspera(const Sensores &sensores){
	if(plan.back() == actFORWARD && (sensores.superficie[2] == 'a'  || sensores.superficie[2] == 'l' && sensores.objetoActivo != '0')){
		return true;
	}
	return false;
}

bool ComportamientoJugador::posMasCercano(const vector<pair<int,int> > &v, const Sensores &sensores){
	priority_queue<pair<int,int> , vector<pair<int,int> > , funtor> ord,aux;
	estado o,d;
	plan.clear();
	deliberativo = false;

	o.crear(fil,col,brujula);

	for(int i = 0; i < v.size(); i++){
		d.crear(v[i].first,v[i].second);
		int dist = distanciaPuntos(o,d);
		ord.push(pair<int,int>(dist,i));
	}
	bool salir = false;
	while(!ord.empty() && !salir){
		d.crear(v[ord.top().second].first,v[ord.top().second].second);
		// if( paso > 19000 ){
		// 	aux = ord;
		// 	cout << endl << fil << "," << col << endl;
		// 	while(!aux.empty()){
		// 		cout << aux.top().first << "-" << v[aux.top().second].first << "," << v[aux.top().second].second << " ";
		// 		aux.pop();
		// 	}
		// 	cout << endl << elemmochila << endl;
		// 	cin.get();
		// }
		deliberativo = pathFinding(o,d,sensores);
		if(deliberativo) salir = true;
		else ord.pop();
	}
	return deliberativo;
}

void ComportamientoJugador::reubicarRegalos(const vector<pair<int,int> > &regalos){
	for(int i = 0; i < regalos.size(); i++){
		mapasuperficie[regalos[i].first][regalos[i].second] = '4';
	}
	reubicar = false;
}

void ComportamientoJugador::buscarObjeto(char objeto, const Sensores &sensores){
	vector<pair<int,int> > v;
	bool c;
	if(objeto != '4'){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 100; j++){
				if( mapasuperficie[i][j] == objeto ) v.push_back(pair<int,int>(i,j));
			}
		}
	}

	if(!v.empty() || (objeto == '4' && sensores.regalos.size() > 0)){
		if( objeto == '4' ){
			c = posMasCercano(sensores.regalos,sensores);
		}
		else{
			c = posMasCercano(v,sensores);
		}
		if(!c){
			switch (objeto) {
				case 'r':
					buscarrey = false;
				break;
				case '1':
					buscarbikini = false;
				break;
				case '2':
					buscarzapatillas = false;
				break;
				case '3':
					buscarllave = false;
				break;
				case '4':
					buscarregalo = false;
				break;
			}
		}
	}
}

void ComportamientoJugador::buscarTodos(const Sensores &sensores){
	vector<pair<int,int> > v;
	bool c;

	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			if( mapasuperficie[i][j] == '1' || mapasuperficie[i][j] == '2' || mapasuperficie[i][j] == '3' ) v.push_back(pair<int,int>(i,j));
		}
	}
	if(!v.empty()){
		c = posMasCercano(v,sensores);
	}
	if(!c){
		buscarbikini = false;
		buscarzapatillas = false;
		buscarllave = false;
	}
}

void ComportamientoJugador::buscarDos(char uno, char dos, const Sensores &sensores){
	vector<pair<int,int> > v;
	bool c;

	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			if( mapasuperficie[i][j] == uno || mapasuperficie[i][j] == dos ) v.push_back(pair<int,int>(i,j));
		}
	}
	if(!v.empty()){
		c = posMasCercano(v,sensores);
	}
	if(!c){
		switch (uno) {
			case '1':
				buscarbikini = false;
			break;
			case '2':
				buscarzapatillas = false;
			break;
			case '3':
				buscarllave = false;
			break;
		}
		switch (dos) {
			case '1':
				buscarbikini = false;
			break;
			case '2':
				buscarzapatillas = false;
			break;
			case '3':
				buscarllave = false;
			break;
		}
	}
}

void ComportamientoJugador::soltarObjetos(const Sensores &sensores){
	if( puedoCambiar(sensores) && sensores.superficie[2] == '_' && (sensores.terreno[2] != 'B' && sensores.terreno[2] != 'A' && sensores.terreno[2] != 'P' && sensores.terreno[2] != 'M' && sensores.terreno[2] != 'D')){
		plan.clear();
		if(elemmochila > 0){
			plan.push_back(actPOP);
		}
		if( sensores.objetoActivo != '_' ){
			plan.push_back(actPUTDOWN);
			switch (sensores.objetoActivo) {
				case '0':
					tengohueso = false;
				break;
				case '1':
					tengobikini = false;
				break;
				case '2':
					tengozapatillas = false;
				break;
				case '3':
					tengollave = false;
				break;
				case '4':
					tengoregalo = false;
				break;
			}
		}
		if(plan.size() > 0){
			deliberativo = true;
			elemmochila = 3;
		}
	}
}

void ComportamientoJugador::LlenarMochila(const Sensores &sensores){
	if(!tengollave && !tengobikini && !tengozapatillas && buscarbikini && buscarzapatillas && buscarllave){
		buscarTodos(sensores);
	}
	else if(!tengollave && !tengobikini && buscarbikini && buscarllave){
		buscarDos('1','3', sensores);
	}
	else if(!tengollave && !tengozapatillas && buscarzapatillas && buscarllave){
		buscarDos('2','3', sensores);
	}
	else if(!tengozapatillas && !tengobikini && buscarbikini && buscarzapatillas){
		buscarDos('1','2', sensores);
	}
	else if(!tengozapatillas && buscarzapatillas){
		buscarObjeto('2', sensores);
	}
	else if(!tengollave && buscarllave){
		buscarObjeto('3', sensores);
	}
	else if(!tengobikini && buscarbikini){
		buscarObjeto('1', sensores);
	}
}

void ComportamientoJugador::estimarPorcetaje(const Sensores &sensores){
	double casillas = 0.0;
	double descubiertas = 0.0;
	bool encuentra = false;

	for(int i = 3; i <= max; i++){
		for(int j = 3; j <= max; j++){
			if( mapaResultado[i][j] != '?' ){
				descubiertas++;
			}
			casillas++;
		}
	}
	double porcentaje = ((descubiertas/casillas)*100.0);

	if( porcentaje > 95 || paso > 11000){
		cumplirmisiones = true;
	}
	else if( porcentaje > 20 && porcentaje <= 95){
		if( sensores.vida > 800 && porcentaje > 50 && (!tengollave || !tengobikini || !tengozapatillas) ){
			LlenarMochila(sensores);
		}
		else if(busquedadeliberativa){
			busquedadeliberativa = busquedaDeliberativa(sensores);
		}
	}
}

bool ComportamientoJugador::busquedaDeliberativa(const Sensores &sensores){
	srand (time(NULL));
	bool salir = false	;
	estado o,d;
	int mucho = 0;
	int filamax = fil, columnamax = col;
	int filamin = fil, columnamin = col;
	int i = 0;
	o.crear(fil,col,brujula);

	while(!salir && i < 100){
		i++;
		if( i%25 == 0 || i == 1 || mucho == 10){
			mucho = 0;
			filamax = ((max) <= (filamax+20))?(max):(filamax+20);
			columnamax = ((max) <= (columnamax+20))?(max):(columnamax+20);
			filamin = (3 >= (filamin-20))?3:(filamin-20);
			columnamin = (3 >= (columnamin-20))?3:(columnamin-20);
		}
		int f = (rand() % (filamax-filamin))+filamin;
		int c = (rand() % (columnamax-columnamin))+columnamin;

		if( mapaResultado[f][c] == '?' ){
			mucho++;
			d.crear(f,c);
			deliberativo = pathFinding(o,d,sensores);
			salir = deliberativo;
		}
	}
	return salir;
}

void PintarAccion(const Action &a){
	switch (a) {
		case actFORWARD:
			cout << "UltimaAccion: actFORWARD" << endl;
		break;
		case actIDLE:
			cout << "UltimaAccion: actIDLE" << endl;
		break;
		case actTURN_R:
			cout << "UltimaAccion: actTURN_R" << endl;
		break;
		case actTURN_L:
			cout << "UltimaAccion: actTURN_L" << endl;
		break;
		case actPUTDOWN:
			cout << "UltimaAccion: actPUTDOWN" << endl;
		break;
		case actPICKUP:
			cout << "UltimaAccion: actPICKUP" << endl;
		break;
		case actPUSH:
			cout << "UltimaAccion: actPUSH" << endl;
		break;
		case actPOP:
			cout << "UltimaAccion: actPOP" << endl;
		break;
	}
}

void ComportamientoJugador::comprobarPosiblesErrores(const Sensores &sensores){
	if(deliberativo && plan.size() == 0) deliberativo = false;
	if(sensores.tiempo > 200) deliberativo = cumplirmisiones = false;
	if(cumplirmisiones && sensores.objetoActivo == '0'){
		if( sensores.mochila != '_' ){
			elemmochila--;
			plan.push_back(actPOP);
		}
		plan.push_back(actTHROW);
		deliberativo = true;
	}
}

Action ComportamientoJugador::decidirMovimiento(const Sensores &sensores){
	Action accion;

	if(deliberativo && !plan.empty() && !parobuscar){
		accion = plan.back();
		if(errorDelibEspera(sensores)){
			parobuscar = true;
			accion = calcularNuevaAccion(sensores);
			plan.clear();
			deliberativo = false;
		}
		else if(errorDelibNuevoMovimiento(sensores)){
			accion = calcularNuevaAccion(sensores);
		}
		else
			plan.pop_back();
		if(plan.empty()){
			deliberativo = false;
		}
	}
	else{
		deliberativo = false;
		accion = calcularNuevaAccion(sensores);
	}

	return accion;
}

Action ComportamientoJugador::think(Sensores sensores){
	Action accion = actIDLE;

	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Mochila: " << sensores.mochila << endl;
	// cout << "ElemMochila: " << elemmochila << endl;
	// PintarAccion(ultimaAccion);
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << "Fila: " << sensores.mensajeF << endl;
	cout << "Columna: " << sensores.mensajeC << endl;
	cout << "objetoActivo: " << sensores.objetoActivo << endl;
	cout << endl;


	Actualizar_informacion(sensores,ultimaAccion);

	guardarPaso(sensores);

	//Decidir nueva accion

	if(!rotar && tengoK(sensores) && !deliberativo && !bien_situado){
		buscarK(sensores);
	}
	// PintaPlan(plan);

	if( paso > 1500 && max > 0 && sensores.tiempo < 200 && bien_situado && !deliberativo && !cumplirmisiones && sensores.vida > 30 && !parobuscar){
		estimarPorcetaje(sensores);
	}

	if(reubicar){
		reubicarRegalos(sensores.regalos);
	}

	if( sensores.vida <= 30){
		if((sensores.objetoActivo != '_' || sensores.mochila != '_'))
			soltarObjetos(sensores);
	}

	if( !parobuscar && sensores.vida > 800 && cumplirmisiones && !deliberativo && bien_situado && !tengoregalo && ((!tengollave && buscarllave) || (!tengobikini && buscarbikini) || (!tengozapatillas && buscarzapatillas)) ){
		LlenarMochila(sensores);
	}

	if(!parobuscar && bien_situado && cumplirmisiones && !deliberativo && sensores.regalos.size() > 0 && !tengoregalo && buscarregalo && sensores.vida > 30){
		buscarObjeto('4',sensores);
	}

	if( !parobuscar && cumplirmisiones && tengoregalo && buscarrey && !deliberativo && sensores.vida > 30){
		buscarObjeto('r',sensores);
	}

	comprobarPosiblesErrores(sensores);

	accion = decidirMovimiento(sensores);

	actualizarSuperficie(accion,sensores);

	if(paso == 19999){
		rellenarMapa();
	}

	ultimaAccion = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return true;
}
