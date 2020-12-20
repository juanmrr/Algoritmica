#include <iostream>
#include <cstdlib>  // Para generación de números pseudoaleatorios
#include <chrono>// Recursos para medir tiempos
using namespace std;
using namespace std::chrono;

int buscar(const int *v, int n, int x);
void insercion(int *v, int nelem);
void sintaxis();
void imprimir(int *v, int nelem);

int main(int argc, char * argv[]) {
  // Lectura de parámetros
  if (argc!=3)
    sintaxis();

  int tam=atoi(argv[1]);     // Tamaño del vector
  int vmax=atoi(argv[2]);    // Valor máximo
  if (tam<=0 || vmax<=0)
    sintaxis();
  
  // Generación del vector aleatorio
  int *v=new int[tam];       // Reserva de memoria
  srand(time(0));            // Inicialización del generador de números pseudoaleatorios
  for (int i=0; i<tam; i++)  // Recorrer vector
    v[i] = tam - i + 1;    // Generar aleatorio [0,vmax[

  //imprimir(v, tam);
  
 high_resolution_clock::time_point start,//punto de inicio
                                  end; //punto de fin
 duration<double> tiempo_transcurrido;  //objeto para medir la duracion de end 						   // y start
  
 start = high_resolution_clock::now(); //iniciamos el punto de inicio
 
//  int x = vmax+1;  // Buscamos un valor que no está en el vector
//  buscar(v,tam,x); // de esta forma forzamos el peor caso
  insercion(v, tam);
  
 end = high_resolution_clock::now(); //anotamos el punto de de fin 
 //el tiempo transcurrido es
 tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

  // Mostramos resultados
  cout << tam << "\t" <<tiempo_transcurrido.count() << endl;
  
  //imprimir(v, tam);

  delete [] v;     // Liberamos memoria dinámica
}

int buscar(const int *v, int n, int x) {
  int i=0;
  while (i<n && v[i]!=x) 
    i=i+1;
  if (i<n) 
    return i;
  else
    return -1;
}

void insercion(int *v, int nelem) {
  int swap, valor, j;
  bool fin;

  for (int i=1; i < nelem; i++) {
    valor = v[i];
    j = i;

    while (valor < v[j-1] && j>0) {
      swap = v[j-1];
      v[j-1] = v[j];
      v[j] = swap;

      j--;
    }
  }
}

void sintaxis() {
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

void imprimir(int *v, int nelem) {
  for (int i=0; i<nelem; i++)
    cout << v[i] << " ";

  cout << endl; 
}
