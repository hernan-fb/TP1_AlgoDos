/*
 * TP1CuatroEnLinea.cpp
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>

#include "Tablero.h"
using namespace std;

#define WIDTH 	10
#define HEIGHT 	10
#define cIF columnaIngresoFicha
#define fIF	filaIngresoFicha

#define ASCII_ESC 27
#define ASCII_F1 80

std::string ResumenJuegoStr[] = {"Hay 4-en-linea (Vertical)",
					   	    	 "Hay 4-en-linea (Horizontal)",
								 "Hay 4-en-linea (Diagonal)",
								 "Tablero Lleno, no hubo ni un ganador :'(. Esto es un empate.",
								 "Juego en marcha, para salir la tecla \"Esc\" "};

int main() {
	int columnaIngresoFicha,filaIngresoFicha;
	int jugadorActual = 0, tecla; // 0 := sin jugadores definidos.
	Tablero tablero1;
	ResumenJuego estadoDelJuego; //metas a futuro podrían ser un histórico de los grupos verticales, diagonales y horizontales de cada jugador.
	std::string ficha;

	cout << "¡Bienvenido al juego 4-en-linea!" << endl << endl;
	do {		// este es el bucle para reiniciar la partida.
		do {	// este es el bucle que es repetido para colocar una nueva ficha.
			//tablero1.nuevoJuego();
			tablero1.imprimeTablero();
			jugadorActual = tablero1.estableceTurnoJugador(); // al establecer el jugador, establece la ficha que será ingresada en tablero.

			cout <<"Ingrese el número de la columna, del 1 al 10, para ingresar la ficha del jugador "<<jugadorActual<<": "<<endl;

			do {
				cin >> columnaIngresoFicha;

				filaIngresoFicha = tablero1.colocaFicha(columnaIngresoFicha);

				switch (filaIngresoFicha) {
					case -1:
						cout<<"La columna "<<columnaIngresoFicha<<" está completa, intente en otra columna."<<endl;
						break;
					case -2:
						cout<<"Ingrese un número válido"<<endl;
						cin.clear(); 			 // reseteo el cin para evitar bucle indefinido
						cin.ignore(10000, '\n'); // fuente: http://www.cplusplus.com/forum/general/207458/
						break;
				}

			} while (filaIngresoFicha <= -1);

			estadoDelJuego = tablero1.estadoDelJuego(columnaIngresoFicha,filaIngresoFicha); // Chequea primero los grupos verticales,
																		   // luego diagonales. Finaliza con los horizontales.
		} while ( estadoDelJuego == AUNSINGANADOR );

		tablero1.imprimeTablero();

		ficha = (jugadorActual==1)?"O":"X";

		cout<<ResumenJuegoStr[estadoDelJuego];

		if (estadoDelJuego != TABLEROLLENO){
			cout<<" y, el ganador, ha sido el jugador "<<jugadorActual<<" (ficha '"<<ficha<<"')."<<endl;
		}
		cout<< "¡El juego ha finalizado!"<<endl<<endl;

		cout<< "Para reinciar el juego presione una tecla, para salir Esc."<<endl;
		system ("/bin/stty raw"); 	 // https://es.stackoverflow.com/questions/132540/c%C3%B3mo-saber-si-presion%C3%B3-una-tecla-sin-enter-en-c-con-linux
		cin.ignore(1, '\n');	  	 // ignoro el último '\n' ingresado por console.
		tecla = getchar();
		system ("/bin/stty cooked"); // restablezco el modo normal de consola.
		switch (tecla) {			 // bifurcación para iniciar un nuevo juego.
			case ASCII_ESC:		     // 13 = ASCII_INTRO; 97 = ASCII_a; 27 = ASCII_ESC;
				cout<<endl<<"Ha presionado Esc. Ha decidido salir. ¡De a cuerdo!."<<endl;
				break;
			default:
				cout<<endl<<"Un nuevo 4-en-linea está por comenzar..."<<endl;
				tablero1.nuevoJuego();
				break;
		}

	} while ( tecla != ASCII_ESC );

	return 0;
}
