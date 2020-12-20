#include <iostream>
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;

/**
  * @brief Función basada en DyV que devuelve el máximo y el mínimo de un vector
  * @param v Vector sobre el que se aplica el algoritmo
  * @param n Número de elementos del vector
  * @return Se devuelve un par<int, int> con el máximo en el primero y el mínimo en el segundo
  */
pair<int,int> Max_Min(int *v, int n);

void sintaxis();
void imprimir(int *v, int nelem);

int main(int argc, char *argv[]) {
  if (argc == 1)
    sintaxis();

  int nelem=atoi(argv[1]);     // Tamaño del vector
  int vmax=atoi(argv[2]);      // Valor máximo
  if (nelem<=0 || vmax<=0)
    sintaxis();

  int *v=new int[nelem];       // Reserva de memoria
  srand(time(0));       

  for (int i=0; i<nelem; i++)  // Recorrer vector
    v[i] = rand() % vmax;      // Generar aleatorio [0,vmax[


  //imprimir(v, nelem);
  high_resolution_clock::time_point start, end; 
  duration<double> tiempo_transcurrido;

  start = high_resolution_clock::now(); //iniciamos el punto de inicio

  pair<int,int> resultado = Max_Min(v, nelem);

  end = high_resolution_clock::now(); //anotamos el punto de de fin 
  //imprimir(v, nelem);

  tiempo_transcurrido = duration_cast<duration<double> >(end - start);

  // Mostramos resultados
  cout << nelem << "\t" <<tiempo_transcurrido.count() << endl;	
  //cout << "\tMax: " << resultado.first << "\tMin: " << resultado.second << endl;

  delete[] v;
}

//----------------------------------------
pair<int,int> Max_Min(int *v, int n) {
  pair<int, int> max_min(v[0], v[0]);

  if (n == 1)
    return max_min;
  else {
    pair<int, int> aux = Max_Min (v, n/2);
    max_min = Max_Min (v+n/2, (n+1)/2);

    if (aux.first > max_min.first)
      max_min.first = aux.first;

    if (aux.second < max_min.second)
      max_min.second = aux.second;

    return max_min;
  }
}

//----------------------------------------
void sintaxis() {
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

//----------------------------------------
void imprimir(int *v, int nelem) {
  for (int i=0; i<nelem; i++)
    cout << v[i] << " ";

  cout << endl; 
}
