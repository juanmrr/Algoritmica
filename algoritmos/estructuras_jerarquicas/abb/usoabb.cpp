#include "abb.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos
using namespace std;
using namespace std::chrono;

void ordenarConABB(int *v, int nelem);
void ListarAbb(ABB<int> &ab_bus);
void imprimir(int *v, int nelem);
void sintaxis();

int main(int argc, char * argv[]){
	int nelem=atoi(argv[1]);     // Tamaño del vector
	int vmax=atoi(argv[2]);    // Valor máximo
	if (nelem<=0 || vmax<=0)
		sintaxis();

	// Generación del vector aleatorio
	int *v=new int[nelem];       // Reserva de memoria
	srand(time(0));            // Inicialización del generador de números pseudoaleatorios
	for (int i=0; i<nelem; i++)  // Recorrer vector
		v[i] = i + 1;    // Generar aleatorio [0,vmax[

	
	// imprimir(v, nelem);

	high_resolution_clock::time_point start,//punto de inicio
				          end; //punto de fin
	duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end 						   // y start

	start = high_resolution_clock::now(); //iniciamos el punto de inicio

	ordenarConABB(v, nelem);

	end = high_resolution_clock::now(); //anotamos el punto de de fin 

	//imprimir(v, nelem);

	//el tiempo transcurrido es
	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

	// Mostramos resultados
	cout << nelem << "\t" <<tiempo_transcurrido.count() << endl;	
}

void ordenarConABB(int *v, int nelem) {
	ABB<int>arbol;
	ABB<int>::nodo n;
	int i;

	for (i = 0; i < nelem; i++) {
		arbol.Insertar(v[i]);
	}


	for (n = arbol.begin(), i = 0; n != arbol.end(); ++n, i++){
		v[i] = *n;
	}
}

void ListarAbb(ABB<int> &ab_bus){
	ABB<int>::nodo n;
	cout<<endl<<"Elementos ordenados: ";

	for (n=ab_bus.begin();n!=ab_bus.end();++n){
		cout<<*n<<" ";
	}
}

void imprimir(int *v, int nelem) {
  for (int i=0; i<nelem; i++)
    cout << v[i] << " ";

  cout << endl; 
}

void sintaxis() {
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}
