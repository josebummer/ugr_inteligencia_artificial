/*
Practica 2: Agentes deliberativos.

Realizada por: Jose Antonio Ruiz Millan

Inteligencia Artificial 2016/2017
*/

#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <list>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

class funtor{
public:
	bool operator()(const pair<int,int> &uno , const pair<int,int> &dos){
		return (uno.first >= dos.first);
	}
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Inicializar Variables de Estado
      fil = col = x = y = 99;
      paso = max = 0;
			siguientebusquedaregalo = 500;
			siguientebusquedadelib = 400;
			siguientecomprobacion = 20;
      nrotaciones = elemmochila = girosizq = girosder = 0;
      brujula = 0;  // 0 --> NORTE ;; 1 --> ESTE ;; 2 --> SUR ;; 3 --> OESTE ;;
      ultimaAccion = actIDLE;
      bien_situado = cumplirmisiones = parobuscar = deliberativo = tengoregalo = objizq = objder = objdel = objdetras = tengohueso = tengollave = tengobikini = tengozapatillas = kizq = kder = kdetras = kdel = doblegiro = sacarobjeto = false;
      rotar = reubicar = buscarrey = busquedadeliberativa = buscarbikini = buscarzapatillas = buscarllave = buscarregalo = true;
      for( int i = 0; i < 200; i++ ){
        for( int j = 0; j < 200; j++){
          if( i < 100 && j < 100 ){
            mapasuperficie[i][j] = '?';
            mapaPasos[i][j] = -1;
          }
          mapaauxsuperficie[i][j] = '?';
          mapaaux[i][j] = '?';
          mapaPasosaux[i][j] = -1;
        }
      }
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);

    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:

    struct estado{
      int fila;
      int columna;
      int orientacion;

      void crear(int f, int c, int o){
        fila = f;
        columna = c;
        orientacion = o;
      }
      estado(){
        fila = columna = orientacion = 0;
      }
      void crear(int f, int c){
        fila = f;
        columna = c;
        orientacion = 0;
      }
    };

    class Nodo{
    public:
      Nodo(): padre(NULL),g(0),h(0){}

      Nodo(const estado &e, Nodo *p, int pg, int ph): est(e), padre(p), g(pg), h(ph){}

      Nodo(const Nodo &otro){
        this->crear(otro.est,otro.padre,otro.g,otro.h);
      }
      void crear(const estado &e, Nodo *p, int pg, int ph){
        est = e;
        padre = p;
        g = pg;
        h = ph;
      }
      estado getEstado() const{
        return est;
      }
      int getG() const{
        return g;
      }
      int getH() const{
        return h;
      }
      Nodo* getPadre() const{
        return padre;
      }
      bool operator <(const Nodo &otro)const {
        return ((this->g+this->h)<(otro.g+otro.h));
      }
      bool operator ==(const Nodo &otro) const{
        return ((this->getEstado().fila == otro.getEstado().fila) && (this->getEstado().columna == otro.getEstado().columna));
      }
      bool operator ==(const estado &otro) const{
        return ((this->getEstado().fila == otro.fila) && (this->getEstado().columna == otro.columna));
      }
      Nodo& operator=(const Nodo &otro){
        if(&otro!=this){
          this->crear(otro.getEstado(),otro.getPadre(),otro.getG(),otro.getH());
        }
        return *this;
      }
    private:
      estado est;
      Nodo *padre;
      int g,h;
    };

    /**
    @brief Reinicia el comportamiento para volver a empezar a explorar cuando morimos.
    */
    void Reinicio();
    /**
    @brief Actualiza la informacion del mapa dependiendo de la accion anterior que hemos realizado
    @param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
    @param ultimaAccion: contiene la ultima accion que hemos realizado
    */
    void Actualizar_informacion(const Sensores &sensores, const Action &ultimaAccion);
    /**
    @brief Calcula el valor de la celda de la derecha para establecer prioridad
    @return Devuelve el numero contenido en mapaPasos en la casilla determinada o un numero muy elevado en caso de no poder pasar por esa casilla
    */
    int derecha(const Sensores &sensores);
    /**
    @brief Calcula el valor de la celda de la izquierda para establecer prioridad
    @return Devuelve el numero contenido en mapaPasos en la casilla determinada o un numero muy elevado en caso de no poder pasar por esa casilla
    */
    int izquierda(const Sensores &sensores);
    /**
    @brief Calcula el valor de la celda de delante para establecer prioridad
    @return Devuelve el numero contenido en mapaPasos en la casilla determinada o un numero muy elevado en caso de no poder pasar por esa casilla
    */
    int delante(const Sensores &sensores);
    /**
    @brief Indica si se puede pasar o no por una casilla determinada
    @param fila: valor de la fila en la matriz
    @param colum: valor de la columna en la matriz
    @return Devuelve true si se puede pasar por la casilla y false en caso contrario
    */
    bool puedoPasar(int fila, int colum, const Sensores &sensores);
    bool puedoPasar(int fila , int colum);
    /**
    @brief Calcula la siguiente accion ha realizar
    @param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
    @return Devuelve la accion ha realizar
    */
    Action Nueva_Accion(const Sensores &sensores);
    /**
    @brief Busca si en nuestro campo de vision tenemos un punto PK para ubicarnos en el mapa, en caso de encontrarlo modifica el
    * mapaPasos para acercarnos hacia el.
    @param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
    */
    void buscarK(const Sensores &sensores);
    bool tengoK(const Sensores &sensores);
    /**
    @brief Pasa la informacion del mapa cuando no estamos ubicados al mapa en el que ya estamos bien ubicados
    */
    void cambiarMapa();
    /**
    @brief Actualiza si tenemos objetos en nuestro alrededor
    @param accionactual: accion que vamos a realizar en ese paso
    @param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
    */
    void actualizarSuperficie(const Action &accionactual,const Sensores &sensores);
    /**
    @brief Rellena el mapa cuando vamos a morir realizando una estimacion
    */
    void rellenarMapa();
    /**
    @brief Guarda los pasos que llevamos en el mapa adecuado dependiendo de si estamos ubicados o no
    @param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
    */
    void guardarPaso(const Sensores &sensores);
    /**
    @brief Calcula la siguiente accion en cualquier situacion de la partida
    @param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
    @return Devuelve la sieguiente accion a ejecutar
    */
    Action calcularNuevaAccion(const Sensores &sensores);
    /**
    @brief Indica si podemos cambiar un objeto por otro teniendo en cuenta donde nos entramos
    @param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
    @return Devuelve true si podemos cambiar de objeto sin que esto afecte al agente y false en caso contrario
    */
    bool puedoCambiar(const Sensores &sensores);
    /**
    @brief Va a establecer una prioridad para entrar a las salas cuando tengamos llave y pasemos por la puerta
    @param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
    */
    void prioridadPuertas(const Sensores &sensores);
		/**
		@brief Crear el camino deliberativo entre un origen y un destino del mapa
		@param origen: estado origen del camino.
		@param destino: estado destino del camino.
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		@return Devuelve true en caso de que el camino de origen a destino sea posible y false en caso contrario.
		*/
    bool pathFinding(const estado &origen, const estado &destino, const Sensores &sensores);
		/**
		@brief Calcula la distancia manhattan entre dos puntos en el mapa.
		@param origen: estado origen
		@param destino: estado destino.
		@return Devuelve la distancia manhattan entre origen y destino.
		*/
    int distanciaPuntos(const estado &origen, const estado &destino);
		/**
		@brief Comprueba si cuando vamos a realizar un plan, el siguiente movimiento puede llevar a error que se soluciona con un movimiento reactivo.
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		@return Devuelve true si comprueba que hay algun error y false en caso contrario
		*/
    bool errorDelibNuevoMovimiento(const Sensores &sensores);
		/**
		@brief Comprueba si cuando vamos a realizar un plan, el siguiente movimiento puede llevar a error que se soluciona esperando quieto.
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		@return Devuelve true si comprueba que hay algun error y false en caso contrario
		*/
    bool errorDelibEspera(const Sensores &sensores);
		/**
		@brief Comprueba si hay un objeto que no nos permite pasar por la casilla especificada como parametro.
		@param fila: entero que indica el numero de fila en el mapa.
		@param colum: entero que indica el numero de columna en el mapa
		@return Devuelve true si hay un objeto que no nos permite pasar y false en caso contrario
		*/
    bool tengoObjeto(int fila, int colum);
		/**
		@brief Calcula el objeto mas cercano que tenemos respecto a la poscion en la que nos encontramos y calcula el camino hacia él,
		* si no es posible, calcula camino hacia el segundo mas cercano y asi sucesivamente.
		@param v: Vector de pair donde el primer entero indica la fila y el segundo la columna del objeto que nos interesa
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		@return Devuelve true si encuentra camino para un objeto y true en caso contrario.
		*/
    bool posMasCercano(const vector<pair<int,int> > &v, const Sensores &sensores);
		/**
		@brief Cuando se entrega a un rey un regalo y aparece en otra posicion, reubica los regalos que tenemos en el sensor en nuestro mapa superficie
		@param regalos: vector con las posiciones del los regalos en el mapa.
		*/
    void reubicarRegalos(const vector<pair<int,int> > &regalos);
		/**
		@brief Busca un objeto concreto en el mapa y crea el camino hacia el objeto mas cercano del tipo indicado
		@param objeto: tipo de objeto que necesitamos
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		*/
    void buscarObjeto(char objeto, const Sensores &sensores);
		/**
		@brief Busca objetos de tipo llave, bikini y zapatillas y nos crear el camino hacia el mas corto.
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		*/
    void buscarTodos(const Sensores &sensores);
		/**
		@brief Busca objetos de dos tipo y crear el camino al objeto mas cercano de cualquiera de los 2 tipos
		@param uno: Indica el valor de un tipo de objeto
		@param dos: Indica el valor de otro tipo de objeto
		*/
    void buscarDos(char uno, char dos, const Sensores &sensores);
		/**
		@brief Suelta los objetos que llevamos tanto en la mano como en la mochila en el mapa.
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		*/
    void soltarObjetos(const Sensores &sensores);
		/**
		@brief Comprueba los objetos que nos faltan en la mochila para llenarla con los objetos que nos falten
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		*/
    void LlenarMochila(const Sensores &sensores);
		/**
		@brief Estima el porcentaje que lleva el agente explorado estimando tambien el tamaño del mapa ayudandonos de la variable privada max.
		* Una vez estimado, segun el resultado que nos devuelva, cambia a busqueda deliberativa o activa la variable para cumplir misiones
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		*/
		void estimarPorcetaje(const Sensores &sensores);
		/**
		@brief Realiza una busqueda deliberativa para explorar el mapa buscando '?' lo mas cerca posible de nuestro agente y va ampliando el rango de busqueda
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		@return True si ha sido posible encontrar un espacio sin explorar, false en caso contrario.
		*/
		bool busquedaDeliberativa(const Sensores &sensores);
		/**
		@brief Comprueba errores antes de la eleccion de la accion por si tenemos el plan vacio y la variable de deliberativo activada entre otros posibles errores
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		*/
		void comprobarPosiblesErrores(const Sensores &sensores);
		/**
		@brief Decide el siguiente movimiento a ejecutar dependiendo de si tenemos las variables de deliberativo activadas o no.
		@param sensores: sensores de los cuales tenemos informacion sobre lo que el agente percibe
		@return Devuelve la siguiente accion a ejecutar.
		*/
		Action decidirMovimiento(const Sensores &sensores);

    list<Action> plan;																													// Lista de acciones para llevar cualquier plan deliberativo
		bool busquedadeliberativa;																									// Nos indica si no podemos realizar busqueda deliberativa.
		bool parobuscar;																														// Si hay algun error en un plan paramos unos pasos de buscar.
    bool deliberativo;																													// Indica si estamos realizando un plan
    bool reubicar;																															// Nos indica si hemos entregado un regalo para reubicar el nuevo que aparece en el mapa
    bool buscarbikini,buscarzapatillas,buscarllave,buscarregalo,buscarrey;			// Variables que se ponen a false si hemos buscado todos los objetos y no hemos podido llegar a ninguno para evitar volver a buscarlo
    int max;																																		// Guarda el valor maximo que el agente a llegado de fila o columna real para hacer una estimacion del tamnaño del mapa
		int siguientebusquedaregalo;																								// En el caso de no poder llegar a ningun regalo, utilizamos esta variable para indicar cada cuantos pasos volveremos a buscar el regalo
		int siguientecomprobacion;																									// En el caso de no poder llegar a ningun destino por error, utilizamos esta variable para indicar cada cuantos pasos volveremos a buscar
		int siguientebusquedadelib;																									// En el caso de no poder realizar busqueda deliberativa, utilizamos esta variable para indicar cada cuantos pasos volveremos a buscar
    bool cumplirmisiones;																												// Indica el momento el cual vamos a empezar a buscar regalos y dejar de explorar
    list<Nodo> abiertos;																												// Lista en la que guardaremos los nodos abiertos del algoritmo A*
    list<Nodo> cerrados;																												// Lista en la que guardaremos los nodos cerrados del algoritmo A*
    bool kizq, kder, kdetras, kdel, doblegiro;                         					// Nos ayudara a la hora de buscar el punto PK
    bool tengobikini,tengohueso,tengollave,tengozapatillas,tengoregalo;         // Nos van a indicar si tenemos tanto en la mano como en la mochila un objeto determinado
    int x,y,fil,col,brujula;                                          					// Nos sirve para saber en la posicion del mapa que nos encontramos y la orientacion
    Action ultimaAccion;                                             					 	// Para recordar la ultima accion que realizamos y actualizar la informacion
    bool bien_situado;                                                					// Indica si estamos bien situados en el mapa respecto a la realidad
    bool rotar;                                                       					// Nos sirve para rotar en cada inicio de la exploracion y conocer nuestros alrededores
    int nrotaciones;                                                  					// Para llevar el conteo del giros que tenemos que dar en la rotacion
    char mapaaux[200][200];                                           					// Mapa para guardar la informacion sobre el mapa cuando no conocemos nuestra ubicacion
    char mapaauxsuperficie[200][200];																						// Mapa donde guardaremos los objetos de la superficie que vamos viendo por los sensores (no situados)
    bool sacarobjeto;                                                 					// Recuerda si en la siguiente iteracion debemos cojer un objeto de la mochila
    bool objizq, objder, objdel, objdetras;                           					// Nos indica si tenemos un objeto alrededor nuestra en el mapa
    int paso;                                                         					// Lleva el conteo de pasos durante toda la exploracion para priorizar hacia donde dirigirnos
    int mapaPasos[100][100];                                          					// Mapa donde guardamos el valor de la variable paso para elegir la prioridad de donde movernos
    char mapasuperficie[100][100];																							// Mapa donde guardaremos los objetos de la superficie que vamos viendo por los sensores (situados)
    int mapaPasosaux[200][200];                                       					// Igual que el anterior pero para cuando no estamos bien situados en el mapa
    int elemmochila;                                                  					// Nos indica el numero de elementos que tenemos dentro de la mochila
    int girosizq, girosder;                                           					// Nos ayuda a pone un limite de giros en el mismo sentido continuamente
};


#endif
