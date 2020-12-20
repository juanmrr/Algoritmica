#include <iostream>
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;

/**
  * @brief Función basada en DyV que devuelve el máximo y el mínimo de un vector
  * @param M Matriz sobre el que se aplica el algoritmo
  * @param inicioi Fila inicial de la matriz (>=0)
  * @param inicioj Columna inicial de la matriz (>=0)
  * @param n Número de files y/o columnas
  * @return Se devuelve un par<int, int> con el máximo en el primero y el mínimo en el segundo
  * @note La matriz debe ser cuadrada
  */
pair<int,int> Max_Min(int **M, int inicioi, int inicioj, int n);


/**
  * @brief Función basada en DyV que devuelve el máximo y el mínimo de un vector
  * @param v Vector sobre el que se aplica el algoritmo
  * @param n Número de elementos del vector
  * @return Se devuelve un par<int, int> con el máximo en el primero y el mínimo en el segundo
  */
pair<int,int> Max_Min(int *v, int n);

void sintaxis();
void imprimir(int **M, int nelem);

int main(int argc, char *argv[]) {
  if (argc == 1)
    sintaxis();

  int nelem=atoi(argv[1]);        // Tamaño de la matriz cuadrada
  int vmax=atoi(argv[2]);         // Valor máximo
  if (nelem<=0 || vmax<=0)
    sintaxis();

  int **M=new int *[nelem];       // Reserva de memoria
  for (int i=0; i<nelem; i++) 
    M[i]=new int [nelem];

  srand(time(0));       

  for (int i=0; i<nelem; i++)    // Recorrer filas de matriz
    for (int j=0; j<nelem; j++)  // Recorrer columnas
      M[i][j] = rand() % vmax;   // Generar aleatorio [0,vmax[


  //imprimir(M, nelem);
  high_resolution_clock::time_point start, end; 
  duration<double> tiempo_transcurrido;

  start = high_resolution_clock::now(); //iniciamos el punto de inicio

  pair<int,int> resultado = Max_Min(M, 0, 0, nelem);

  end = high_resolution_clock::now(); //anotamos el punto de de fin 
  //imprimir(M, nelem);

  tiempo_transcurrido = duration_cast<duration<double> >(end - start);

  // Mostramos resultados
  cout << nelem << "\t" <<tiempo_transcurrido.count() << endl;	
  //cout << "\tMax: " << resultado.first << "\tMin: " << resultado.second << endl;

  for (int i=0; i<nelem; i++) 
    delete[] M[i];
  delete[] M;
}

//----------------------------------------
pair<int,int> Max_Min(int **M, int inicioi, int inicioj, int n) {
  pair<int, int> max_min(M[inicioi][inicioj], M[inicioi][inicioj]);

  if (n == 1)
    return max_min;
  else {
    // M_M primera fila, M_M primera columna, M_M matriz (n-1)*(n-1)
    int *v = M[inicioi];
    pair<int, int> mmfila    = Max_Min (v, n);
    
    int *colum = new int[n];
    for (int i=0; i<n; i++)
      colum[i] = M[inicioi+i][inicioj];       

    pair<int, int> mmcolumna = Max_Min (colum, n);

    max_min = Max_Min (M, inicioi+1, inicioj+1, n-1);

    // Se comparan los máximos
    if (mmfila.first    > max_min.first)
      max_min.first = mmfila.first;
    if (mmcolumna.first > max_min.first)
      max_min.first = mmcolumna.first;

    // Se comparan los mínimos
    if (mmfila.second    < max_min.second)
      max_min.second = mmfila.second;
    if (mmcolumna.second < max_min.second)
      max_min.second = mmcolumna.second;

    // Borrando memoria dinámica
    delete[] colum;

    return max_min;
  }
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
  cerr << "  TAM: Tamaño de la matriz (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un matriz cuadrada TAM*TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

//----------------------------------------
void imprimir(int **M, int nelem) {
  for (int i=0; i<nelem; i++) {
    for (int j=0; j<nelem; j++)
      cout << M[i][j] << " ";

    cout << endl;
  }
  cout << endl; 
}
