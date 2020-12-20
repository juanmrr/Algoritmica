#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos
using namespace std;
using namespace std::chrono;

void burbuja(int *v, int nelem);
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
		v[i] = nelem - i + 1;    // Generar aleatorio [0,vmax[

	
	// imprimir(v, nelem);

	high_resolution_clock::time_point start,//punto de inicio
				          end; //punto de fin
	duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end 						   // y start

	start = high_resolution_clock::now(); //iniciamos el punto de inicio

	burbuja(v, nelem);

	end = high_resolution_clock::now(); //anotamos el punto de de fin 

	// imprimir(v, nelem);

	//el tiempo transcurrido es
	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

	// Mostramos resultados
	cout << nelem << "\t" <<tiempo_transcurrido.count() << endl;	
}

void burbuja(int *v, int nelem) {
  int swap;

  for (int i=0; i < nelem-1; i++){
    for (int j=0; j < nelem-i; j++) {
      if (v[j] > v[j+1]) {
	swap = v[j];
	v[j] = v[j+1];
	v[j+1] = swap;	
      }  
    }
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
