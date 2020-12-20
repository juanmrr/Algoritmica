#include <iostream>
#include "permutacion.h"
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos

using namespace std;
using namespace std::chrono;


bool estaOrdenada (int *v, int n){
	for (int i = 1; i < n; i++){
		if (v[i-1]>v[i]){
			return false;
		}
	}
	return true;
}

void imprimir(int *v, int nelem) {
  for (int i=0; i<nelem; i++)
    cout << v[i] << " ";

  cout << endl; 
}


void Ordenar(int *v, Permutacion P, int n){ 
	int p[n], i;
	Permutacion::iterator it;
	vector<unsigned int>::const_iterator it2;

	do {
		it = P.begin();
		i = 0;
		const vector<unsigned int> vit = (*it);

		for(it2 = vit.cbegin(); it2 != vit.cend(); ++it2){
			int pos = *it2 - 1;
			p[pos] = v[i];
			i++;
		}
		
		if (estaOrdenada(p, n)) {
			for (int i = 0; i < n; i++) {
				v[i] = p[i];
			} 
			return;
		}
	} while (P.GeneraSiguiente());
}			

int main(int argc, char * argv[]){
	if (argc < 2) {
		cout << "Numero incorrecto de argumentos" << endl;
		return 1;
	}
		
	int nelem=atoi(argv[1]);     // Tamaño del vector
	int vmax=atoi(argv[2]);    // Valor máximo

	// Generación del vector aleatorio
	int *v=new int[nelem];       // Reserva de memoria
	srand(time(0));            // Inicialización del generador de números pseudoaleatorios
	for (int i=0; i<nelem; i++)  // Recorrer vector
	   v[i] = nelem - i;    // Generar aleatorio [0,vmax[

//	imprimir(v, nelem);

	Permutacion P(nelem,1);

	high_resolution_clock::time_point start,//punto de inicio
				          end; //punto de fin
	duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end 						   // y start

	start = high_resolution_clock::now(); //iniciamos el punto de inicio

	Ordenar(v, P, nelem);

	end = high_resolution_clock::now(); //anotamos el punto de de fin 


	//el tiempo transcurrido es
	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

	// Mostramos resultados
	cout << nelem << "\t" <<tiempo_transcurrido.count() << endl;	

//	imprimir(v, nelem);
}  
