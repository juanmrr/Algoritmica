#include <iostream>
#include <utility>

using namespace std;


pair<int,int> MaxMin(int **v, int i, int j, int n){

    int maximo = 0;
    int minimo = 0;

    pair<int,int> salida;

    if(n == 1){
        maximo = v[i][j];
        minimo = v[i][j];
    }else{
        pair<int,int> vMax_min[4];
        vMax_min[0] = MaxMin( v, i, j, n/2);
        vMax_min[1] = MaxMin( v, i, j + (n/2), n/2);
        vMax_min[2] = MaxMin( v, i + (n/2), j, n/2);
        vMax_min[3] = MaxMin( v, i + (n/2), j + (n/2), n/2);

        maximo = vMax_min[0].first;
	minimo = vMax_min[0].first;
        for(int i = 0; i < 4; i++){
            if( maximo < vMax_min[i].first){
                maximo = vMax_min[i].first;
            }
            if( minimo > vMax_min[i].second){
                minimo = vMax_min[i].second;
            }
        }
    }

    salida.first = maximo;
    salida.second = minimo;

    return salida;
}

void imprimeVector(){


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

int main(int argc, char *argv[])
{
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


  imprimir(M, nelem);

  pair<int,int> resultado = MaxMin(M, 0, 0, nelem);

  imprimir(M, nelem);

  // Mostramos resultados
  cout << "\tMax: " << resultado.first << "\tMin: " << resultado.second << endl;

  for (int i=0; i<nelem; i++) 
    delete[] M[i];
  delete[] M;

   return 0;
}
