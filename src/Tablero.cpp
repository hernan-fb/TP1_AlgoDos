/*
 * Tablero.cpp
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>

#include "Tablero.h"
#define cIF columnaIngresoFicha
#define fIF	filaIngresoFicha

#ifdef _WIN32
#define CLEAR  "cls"
#else
#define CLEAR  "clear"
#endif


namespace std {
Tablero::Tablero() {
	this->nuevoJuego();
	return;	//PREGUNTA: hace falta?, es decir, es 'obligatorio' poner return como buena práctica de programación?.
};
void Tablero::nuevoJuego() {
	this->contadorJuegos = 0;
	setToValue<int>(contadorGruposVerticales, WIDTH, (int) 0);
	setToValue<char>(*tableritoPantalla, WIDTH * HEIGHT, ' ');	 //PREGUNTA: cuándo usar this y cuándo no? cuál es una buena práctica de programación? cuando quiero hacer referencia al puntero cómo usar this?
	return;	//PREGUNTA: hace falta?, es decir, es 'obligatorio' poner return como buena práctica de programación?.
}
template <typename T> void Tablero::setToValue(T *array, int longitud, T value) {
	for (int i = 0; i<longitud; i++) {
		*(array + i) = value;
	}
	return;
}
char Tablero::tablero(int x, int y) {
	if (x<0 || x> (WIDTH-1) ){
		return 0;
	}
	if (y<0 || y> (HEIGHT-1) ) {
		return 0;
	} // VER TABLA ASCII PARA CERO.
	return (this->tableritoPantalla[x][y]);
}
void Tablero::imprimeTablero() {
	system(CLEAR); //cout << "\x1B[2J";// cout << "\f"<<endl; // std::system ("clear");
	cout<<endl;
	for (int i = 0; i< HEIGHT; i++){
		cout << "|";
		for (int j=0; j<WIDTH; j++) {
			cout << " " << tablero(j, i) << " |";
		}
		cout << '\n';
	}
	return;
}
int Tablero::estableceTurnoJugador() {
	this->tokenParaJugar = (this->contadorJuegos % 2) +1;
	//es un número interno del programa, no obstante valido datos para clasificar la ficha a ingresar
	if (this->tokenParaJugar == 2) {
		this->fichaJugador = 'X';
	}
	else if (this->tokenParaJugar == 1) {
		this->fichaJugador = 'O';
	}
	else {
		this->fichaJugador = ' ';
	}

	return tokenParaJugar;
}
int Tablero::colocaFicha (int &columnaIngresoFicha) {
	int i = HEIGHT; //HEIGHT-1 corresponde al valor extremo del rango de las columnas en tablero[][]
	columnaIngresoFicha--; // adapto al rango de tablero[][]
	if ( columnaIngresoFicha >= 0 && columnaIngresoFicha <= 9 ) { //valido el ingreso por stdout
		do {i--;
		//cout << "i: "<<i<<"columnaIngresoFicha+1: "<<columnaIngresoFicha+1<<endl;
		//obs. el cout dentro del 'do while' si que imprime todas las iteraciones en pantalla.
		} while ( tablero(columnaIngresoFicha,i) != ' ' && i>=0);

		/*for (i= HEIGHT-1; this->tablerito[columnaIngresoFicha][i] != ' ' && i>=0 ; i--);	{
						cout << "i: "<<i<<"columnaIngresoFicha+1: "<<columnaIngresoFicha+1<<endl;
					} */ // pregunta al docente corrector: utilizar el código comentado no imprime
		// todas las iteraciones del for en pantalla... ¿a qué podria deberse?.

		if (i>=0) {
			colocaFicha(columnaIngresoFicha, i, this->fichaJugador);
			this->contadorJuegos++;
		}
	}
	else {
		i = -2; // valido datos que ingreso.
	}
	return (i); //devuelve la cantidad de lugares vacios existentes en la columnaIngresoFicha
	//si la columna esta completa el valor retornado es -1,
	//para ser analizado por el programa.
}
int Tablero::colocaFicha(int x, int y, char value) {
	if (x<0 || x> (WIDTH-1) ){
		return 0;
	}
	if (y<0 || y> (HEIGHT-1) ) {
		return 0;
	}
	this->tableritoPantalla[x][y] = value;
	return 0;
}
ResumenJuego Tablero::estadoDelJuego(int columnaIngresoFicha, int filaIngresoFicha) {
	// desconozco un poco sobre la temática de posibles interrupciones que puedan hacerse en el programa para
	// ser más eficiente en el algoritmo, o de otra estrategía más apropiada, pero con estructuras if-else
	// puede ser realizado sin mayores complicaciones, y entiendo que la meta del tp es conseguir manejar
	// estructuras simples.

	if (calculaGruposVerticales(columnaIngresoFicha) > 3 ) {
		return CUATROENLINEAVERTICALES;
	}
	if (calculaGruposHorizontales(columnaIngresoFicha, filaIngresoFicha) > 3) {
		return CUATROENLINEAHORIZONTALES;
	}
	if (calculaGruposDiagonales(columnaIngresoFicha, filaIngresoFicha) > 3 ) {
		return CUATROENLINEADIAGONALES;
	}
	if (this->contadorJuegos >= WIDTH * HEIGHT) {
		return TABLEROLLENO;
	}
	return AUNSINGANADOR;
}
int Tablero::calculaGruposVerticales(int columnaIngresoFicha) {
	int tokenParaAgrupar = (this->tokenParaJugar);
	tokenParaAgrupar = ((tokenParaAgrupar - 1 )*2)-1;
	// decido hacer un cambio de variables para separar los grupos de las fichas del jugador 1 de las del 2
	// con la variable tokenParaAgrupar, que puede valer +1 o -1, según el turno sea para el jugador 2 o
	// para el jugador 1.
	if (contadorGruposVerticales[columnaIngresoFicha]>0 ) { // el último grupo apilado en la columnaIngresoFicha
		// es del jugador 2, fichas 'X'.
		contadorGruposVerticales[columnaIngresoFicha] =
				(tokenParaAgrupar==1)?contadorGruposVerticales[columnaIngresoFicha]+tokenParaAgrupar:tokenParaAgrupar;
	}
	else if (contadorGruposVerticales[columnaIngresoFicha]<0 ) { //el último grupo apilado en la columnaIngresoFicha
		// es del jugador 1, fichas 'O'.
		contadorGruposVerticales[columnaIngresoFicha] =
				(tokenParaAgrupar==-1)?contadorGruposVerticales[columnaIngresoFicha]+tokenParaAgrupar:tokenParaAgrupar;
	}
	else { // (contadorGruposVerticales[columnaIngresoFicha]==0 ) // significa que es la primer ficha de la columna
		contadorGruposVerticales[columnaIngresoFicha] = tokenParaAgrupar;
		// hay una nueva ficha que no forma aún un grupo de 4 en linea vertical
	}
	if (contadorGruposVerticales[columnaIngresoFicha] == tokenParaAgrupar * 4) { //utilizo el signo de tokenParaAgrupar
		return 4;
	}

	return 0;
}
int Tablero::calculaGruposHorizontales(int columnaIngresoFicha, int filaIngresoFicha) {
	int i = 0, j = 0;
	int calculaGruposHorizontales = 0;
	// ABREVIACION PARA columnaIngresoFicha "cIF"
	// ABREVIACION PARA filaIngresoFicha "fIF"

	// 1er for, avanza con la variable 'i' hacia la derecha.
	for (i=cIF+1; tablero(i,fIF)==tablero(cIF,fIF); i++) {	} //cGH(der) = i - cIF;
	i--;
	// 2do for, avanza con la variable 'j' hacia la izquierda.
	for (j=cIF-1; tablero(j, fIF)==tablero(cIF, fIF); j--) {  } //cGH(izq) = cIF - j + 1;
	j++;

	calculaGruposHorizontales = abs(i - j + 1);

	return calculaGruposHorizontales;
}
int Tablero::calculaGruposDiagonales(int columnaIngresoFicha, int filaIngresoFicha) {
	int i = 0, j = 0, l = 0, m = 0;
	int dUpStairs = 0, dDownStairs = 0; //alias gráfico para los 2 grupos diagonales de fichas en el tablero.
	// ABREVIACION PARA columnaIngresoFicha "cIF"
	// ABREVIACION PARA filaIngresoFicha "fIF"

	// 1er for para adelante y abajo:
	for (i = 1; tablero(cIF+i,fIF+i)==tablero(cIF, fIF); i++){ }
	// 2do for para atras y abajo:
	for (j = 1; tablero(cIF-j,fIF+j)==tablero(cIF, fIF);j++){ }
	// 3er for para adelante y arriba:
	for (l = 1; tablero(cIF+l,fIF-l)==tablero(cIF , fIF);l++){ }
	// 4to for para atras y arriba:
	for (m = 1; tablero(cIF-m,fIF-m)==tablero(cIF, fIF); m++){ }

	//	cout<<"i: "<<i<<"; j: "<<j<<"; l: "<<l<<"; m: "<<m<<"m+i: "<<m+i-1<<"; j+l: "<<j+l-1<<". "<<endl;

	dUpStairs = j + l -1;
	dDownStairs = m + i -1;

	return (dUpStairs>dDownStairs?dUpStairs:dDownStairs);
}
}
