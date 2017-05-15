#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Inicializar Variables de Estado
      fil = col = x = y = 99;
      paso = 0;
      nrotaciones = elemmochila = girosizq = girosder = 0;
      brujula = 0;  // 0 --> NORTE ;; 1 --> ESTE ;; 2 --> SUR ;; 3 --> OESTE ;;
      ultimaAccion = actIDLE;
      bien_situado = objizq = objder = objdel = objdetras = tengohueso = tengollave = tengobikini = tengozapatillas = kizq = kder = kdetras = kdel = doblegiro = sacarobjeto = false;
      rotar = true;
      for( int i = 0; i < 200; i++ ){
        for( int j = 0; j < 200; j++){
          if( i < 100 && j < 100 ){
            mapaPasos[i][j] = -1;
          }
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

    bool kizq, kder, kdetras, kdel, doblegiro;                         // Nos ayudara a la hora de buscar el punto PK
    bool tengobikini,tengohueso,tengollave,tengozapatillas;           // Nos van a indicar si tenemos tanto en la mano como en la mochila un objeto determinado
    int x,y,fil,col,brujula;                                          // Nos sirve para saber en la posicion del mapa que nos encontramos y la orientacion
    Action ultimaAccion;                                              // Para recordar la ultima accion que realizamos y actualizar la informacion
    bool bien_situado;                                                // Indica si estamos bien situados en el mapa respecto a la realidad
    bool rotar;                                                       // Nos sirve para rotar en cada inicio de la exploracion y conocer nuestros alrededores
    int nrotaciones;                                                  // Para llevar el conteo del giros que tenemos que dar en la rotacion
    char mapaaux[200][200];                                           // Mapa para guardar la informacion sobre el mapa cuando no conocemos nuestra ubicacion
    bool sacarobjeto;                                                 // Recuerda si en la siguiente iteracion debemos cojer un objeto de la mochila
    bool objizq, objder, objdel, objdetras;                           // Nos indica si tenemos un objeto alrededor nuestra en el mapa
    int paso;                                                         // Lleva el conteo de pasos durante toda la exploracion para priorizar hacia donde dirigirnos
    int mapaPasos[100][100];                                          // Mapa donde guardamos el valor de la variable paso para elegir la prioridad de donde movernos
    int mapaPasosaux[200][200];                                       // Igual que el anterior pero para cuando no estamos bien situados en el mapa
    int elemmochila;                                                  // Nos indica el numero de elementos que tenemos dentro de la mochila
    int girosizq, girosder;                                           // Nos ayuda a pone un limite de giros en el mismo sentido continuamente
};


#endif
