#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void ComportamientoJugador::Reinicio(){
	brujula = nrotaciones = elemmochila = girosizq = girosder = 0;
	bien_situado = objizq = objder = objdel = objdetras = tengohueso = tengollave = tengobikini = tengozapatillas = kizq = kder = kdetras = kdel = doblegiro = sacarobjeto = false;
	rotar = true;
	fil = 99;
	col = 99;
	x = y = 99;
	ultimaAccion = actIDLE;
	for( int i = 0; i < 200; i++ ){
		for( int j = 0; j < 200; j++){
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
			if( mapaResultado[k][s] == '?' && mapaaux[i][j] != '?' )
      	mapaResultado[k][s] = mapaaux[i][j];
			if( mapaPasos[k][s] < mapaPasosaux[i][j] ){
				mapaPasos[k][s] = mapaPasosaux[i][j];
			}
    }
  }
}

void ComportamientoJugador::Actualizar_informacion(const Sensores &sensores, const Action &ultimaAccion){

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

	objdel = ((sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '3' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
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

Action ComportamientoJugador::Nueva_Accion(const Sensores &sensores){
	Action accion;

	if( kizq && !kdel ){
		accion = actTURN_L;
		kizq = false;
	}
	else if( (kdetras && !kdel) || doblegiro ){
		accion = actTURN_L;
		if( doblegiro ){
			doblegiro = false;
		}
		else{
			doblegiro = true;
		}
		kdetras = false;
	}
	else if( kder && !kdel ){
		accion = actTURN_R;
		kder = false;
	}
	else if( sacarobjeto ){
		accion = actPOP;
		elemmochila--;
		sacarobjeto = false;
	}
	else if( sensores.superficie[2] == '0' && !tengohueso && puedoCambiar(sensores) && elemmochila < 3 ){
		if( sensores.objetoActivo == '_' ){
			accion = actPICKUP;
			tengohueso = true;
			if( sensores.mochila != '_' ){
				elemmochila++;
			}
		}
		else{
			if( sensores.objetoActivo == '0' ){
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
	else if( (sensores.terreno[2] == 'A' && tengobikini && puedoCambiar(sensores) && sensores.objetoActivo != '1' ) && elemmochila < 4){
		elemmochila++;
		if( sensores.objetoActivo == '0' ){
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
			objder = ((sensores.superficie[3] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[3] == 'a' || (sensores.superficie[3] == '0' && tengohueso) || (sensores.superficie[3] == '1' && tengobikini) || (sensores.superficie[3] == '2' && tengozapatillas) || (sensores.superficie[3] == '3' && tengollave) || (sensores.superficie[3] >= '0' && sensores.superficie[3] <= '3' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
			objizq = ((sensores.superficie[1] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[1] == 'a' || (sensores.superficie[1] == '0' && tengohueso) || (sensores.superficie[1] == '1' && tengobikini) || (sensores.superficie[1] == '2' && tengozapatillas) || (sensores.superficie[1] == '3' && tengollave) || (sensores.superficie[1] >= '0' && sensores.superficie[2] <= '1' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
		break;
		case actTURN_L:
			objizq = objdetras;
			objdetras = objder;
			objder = ((sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '3' && (elemmochila > 2 || !puedoCambiar(sensores)) ))?true:false;
		break;
		case actTURN_R:
			objder = objdetras;
			objdetras = objizq;
			objizq = ((sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '3' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
		break;
	}
}

void ComportamientoJugador::rellenarMapa(){
	for( int i = 0; i < 3; i++ ){
		for( int j = 0; j < 100; j++){
			mapaResultado[i][j] = 'P';
		}
	}
	for( int i = 97; i < 100; i++ ){
		for( int j = 0; j < 100; j++){
			mapaResultado[i][j] = 'P';
		}
	}
	for( int i = 0; i < 100; i++ ){
		for( int j = 0; j < 3; j++){
			mapaResultado[i][j] = 'P';
		}
	}
	for( int i = 0; i < 100; i++ ){
		for( int j = 97; j < 100; j++){
			mapaResultado[i][j] = 'P';
		}
	}

	vector<int> n(7,0);
	int max,posmax;

	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			if( mapaResultado[i][j] == '?' ){
				for( int k = i-4; k <= i+4; k++ ){
					for( int l = j-4; l <= j+4; l++ ){
						if( (k != i || l != j) && k < 100 && k >= 0 && j < 100 && j >= 0){
							switch (mapaResultado[k][l]) {
								case 'B':
									n[0]++;
								break;
								case 'A':
									n[1]++;
								break;
								case 'P':
									n[2]++;
								break;
								case 'S':
									n[3]++;
								break;
								case 'T':
									n[4]++;
								break;
								case 'M':
									n[5]++;
								break;
								case 'D':
									n[6]++;
								break;
							}
						}
					}
				}
				max = n[0];
				posmax = 0;
				for( int i = 1; i < 7; i++ ){
					if( n[i] > max ){
						max = n[i];
						posmax = i;
					}
				}

				switch (posmax) {
					case 0:
						if( n[0] != 0 )
							mapaResultado[i][j] = 'B';
					break;
					case 1:
						mapaResultado[i][j] = 'A';
					break;
					case 2:
						mapaResultado[i][j] = 'P';
					break;
					case 3:
						mapaResultado[i][j] = 'S';
					break;
					case 4:
						mapaResultado[i][j] = 'T';
					break;
					case 5:
						mapaResultado[i][j] = 'M';
					break;
					case 6:
						mapaResultado[i][j] = 'D';
					break;
				}
				for( int i = 0; i < 7; i++){
					n[i] = 0;
				}
			}
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

void ComportamientoJugador::buscarK(const Sensores &sensores){
	for( int i = 0; i < 16; i++){
		if( sensores.terreno[i] == 'K' ){
			if( i == 9 || i == 10 ||i == 11 || i == 4 || i == 5 || i == 1 ){
				switch (brujula) {
					case 0:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil-1][col] = -2;
						}
						else if( izquierda(sensores) != 50000 ){
							mapaPasosaux[fil][col-1] = -2;
						}
						mapaPasosaux[fil-1][col-1] = -2;
					break;
					case 1:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil][col+1] = -2;
						}
						else if( izquierda(sensores) != 50000 ){
							mapaPasosaux[fil-1][col] = -2;
						}
						mapaPasosaux[fil-1][col+1] = -2;
					break;
					case 2:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil+1][col] = -2;
						}
						else if( izquierda(sensores) != 50000 ){
							mapaPasosaux[fil][col+1] = -2;
						}
						mapaPasosaux[fil+1][col+1] = -2;
					break;
					case 3:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil][col-1] = -2;
						}
						else if( izquierda(sensores) != 50000 ){
							mapaPasosaux[fil+1][col] = -2;
						}
						mapaPasosaux[fil+1][col-1] = -2;
					break;
				}
			}
			if( i == 2 || i == 6 || i == 12 ){
				switch (brujula) {
					case 0:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil-1][col] = -2;
						}
						else if( izquierda(sensores) != 50000 ){
							mapaPasosaux[fil][col-1] = -2;
							mapaPasosaux[fil-1][col-1] = -2;
						}
						else if( derecha(sensores) != 50000 ){
							mapaPasosaux[fil][col+1] = -2;
							mapaPasosaux[fil-1][col+1] = -2;
						}
					break;
					case 1:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil][col+1] = -2;
						}
						else if( izquierda(sensores) != 50000 ){
							mapaPasosaux[fil-1][col] = -2;
							mapaPasosaux[fil-1][col+1] = -2;
						}
						else if( derecha(sensores) != 50000 ){
							mapaPasosaux[fil+1][col] = -2;
							mapaPasosaux[fil+1][col+1] = -2;
						}
					break;
					case 2:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil+1][col] = -2;
						}
						else if( izquierda(sensores) != 50000 ){
							mapaPasosaux[fil][col+1] = -2;
							mapaPasosaux[fil+1][col+1] = -2;
						}
						else if( derecha(sensores) != 50000 ){
							mapaPasosaux[fil][col-1] = -2;
							mapaPasosaux[fil+1][col-1] = -2;
						}
					break;
					case 3:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil][col-1] = -2;
						}
						else if( izquierda(sensores) != 50000 ){
							mapaPasosaux[fil+1][col] = -2;
							mapaPasosaux[fil+1][col-1] = -2;
						}
						else if( derecha(sensores) != 50000 ){
							mapaPasosaux[fil-1][col] = -2;
							mapaPasosaux[fil-1][col-1] = -2;
						}
					break;
				}
			}
			else{
				switch (brujula) {
					case 0:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil-1][col] = -2;
						}
						else if( derecha(sensores) != 50000 ){
							mapaPasosaux[fil][col+1] = -2;
						}
						mapaPasosaux[fil-1][col+1] = -2;
					break;
					case 1:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil][col+1] = -2;
						}
						else if( derecha(sensores) != 50000 ){
							mapaPasosaux[fil+1][col] = -2;
						}
						mapaPasosaux[fil+1][col+1] = -2;
					break;
					case 2:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil+1][col] = -2;
						}
						else if( derecha(sensores) != 50000 ){
							mapaPasosaux[fil][col-1] = -2;
						}
						mapaPasosaux[fil+1][col-1] = -2;
					break;
					case 3:
						if( delante(sensores) != 50000 ){
							mapaPasosaux[fil][col-1] = -2;
						}
						else if( derecha(sensores) != 50000 ){
							mapaPasosaux[fil-1][col] = -2;
						}
						mapaPasosaux[fil-1][col-1] = -2;
					break;
				}
			}
			break;
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
		buscarK(sensores);
	}
}

Action ComportamientoJugador::calcularNuevaAccion(const Sensores &sensores){
	Action accion;

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
				objizq = ((sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '3' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
				if( tengoK(sensores) )
					kizq = true;
			break;
			case 3:
				objdetras = ((sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '3' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
				if( tengoK(sensores) )
					kdetras = true;
			break;
			case 4:
				objder = ((sensores.superficie[2] == 'l' && sensores.objetoActivo != '0') || sensores.superficie[2] == 'a' || (sensores.superficie[2] == '0' && tengohueso) || (sensores.superficie[2] == '1' && tengobikini) || (sensores.superficie[2] == '2' && tengozapatillas) || (sensores.superficie[2] == '3' && tengollave) || (sensores.superficie[2] >= '0' && sensores.superficie[2] <= '3' && (elemmochila > 2 || !puedoCambiar(sensores))))?true:false;
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
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << "Fila: " << sensores.mensajeF << endl;
	cout << "Columna: " << sensores.mensajeC << endl;
	cout << "objetoActivo: " << sensores.objetoActivo << endl;
	cout << endl;


	Actualizar_informacion(sensores,ultimaAccion);

	guardarPaso(sensores);

	//Decidir nueva accion

	accion = calcularNuevaAccion(sensores);

	actualizarSuperficie(accion,sensores);

	if(paso == 19999){
		rellenarMapa();
	}

	ultimaAccion = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
