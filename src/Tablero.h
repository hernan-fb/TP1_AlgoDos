// Tablero.h
#ifndef TABLERO_CUATROENLINEA_H
#define TABLERO_CUATROENLINEA_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
enum ResumenJuego {CUATROENLINEAVERTICALES,
				   CUATROENLINEAHORIZONTALES,
				   CUATROENLINEADIAGONALES,
				   TABLEROLLENO,
				   AUNSINGANADOR};
#define WIDTH 	10
#define HEIGHT 	10

namespace std {
class Tablero {
private:
	int  tokenParaJugar; //el valor del token indica el jugador que elije la ficha a ingresar en el tablero.
	char fichaJugador;	 //la ficha está directamente relacionada con el jugador, no pueden ser cambiadas.
	int  contadorJuegos;
	char tableritoPantalla[WIDTH][HEIGHT] =
	{ {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} };
	int  contadorGruposVerticales[WIDTH]; 			   // Contador que registra los grupos Verticales de fichas.
public:
	Tablero();
	void nuevoJuego();
	template <typename T> void setToValue(T *array, int longitud, T value);
	char tablero(int x, int y);
	void imprimeTablero();
	int estableceTurnoJugador();
	int colocaFicha (int &columnaIngresoFicha);
	int colocaFicha(int x, int y, char value);
	ResumenJuego estadoDelJuego(int columnaIngresoFicha, int filaIngresoFicha);
	int calculaGruposVerticales(int columnaIngresoFicha);
	int calculaGruposHorizontales(int columnaIngresoFicha, int filaIngresoFicha);
	int calculaGruposDiagonales(int columnaIngresoFicha, int filaIngresoFicha);
};
}

#endif //TABLERO_CUATROENLINEA_H
