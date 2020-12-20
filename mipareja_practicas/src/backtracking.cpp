#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <time.h>

#include "Apermutacion.h"

#define PRINT // Descomentar para ver solo tiempos

/*
 Arbol permutacional
 [x1, x2, xn] indicando para cada i el alumno seleccionado (1..n)
*/

int CotaInferior(Apermutacion &A, int **Discrepancias, int numAlum);
int DiscrepanciaActual(Apermutacion &A, int **Discrepancias, int numAlum);
int BacktrackingSP(int **Discrepancias, Apermutacion &solucion, int numAlum); // Sin Poda
int BacktrackingCP(int **Discrepancias, Apermutacion &solucion, int numAlum); // Con Poda
int Calculo_discrepancia (int indice1, int indice2, int caracteristicas, int **M);
vector<pair<int,int> > getParejas(Apermutacion &solucion, int numAlum);


int main (int argc, char * argv[]) {
  //Se lee el archivo de entrada
  ifstream f (argv[1]);

  if (!f){
    cerr << "El fichero no se puede abrir" << argv[1] << endl;
    return 0;
  }

  string linea;
  getline (f,linea);
  int numAlum, numCarac;
  f >> numAlum >> numCarac;

  //Se genera la matriz que contiene los datos de entrada
  int **M = new int* [numAlum];
  for (int i = 0; i < numAlum; i++)
    M[i] = new int [numCarac];


  //Se escriben los datos en la matriz
  for (int i = 0; i < numAlum; i++)
    for (int j = 0; j < numCarac; j++)
      f >> M[i][j];

  //Se genera la matriz que contiene los cálculos de las discrepancias entre alumnos
  int **Discrepancias = new int* [numAlum];
  for (int i = 0; i < numAlum; i++)
    Discrepancias[i] = new int [numAlum];

  //Se calcula la matriz de discrepancias
  for (int i = 0; i < numAlum; i++)
    for (int j = 0; j < numAlum; j++){
      if (i != j){
	Discrepancias[i][j] = Calculo_discrepancia(i, j, numCarac, M);
	Discrepancias[j][i] = Calculo_discrepancia(i, j, numCarac, M);
      }
      else 
	Discrepancias[i][j] = numeric_limits<int>::max();
    }

  #ifdef PRINT

  //Mostramos la matriz de discrepancias resultante
  for (int i = 0; i < numAlum; i++){
    cout << endl;
    for (int j = 0; j < numAlum; j++)
      cout << Discrepancias[i][j] << "\t";
  }

  cout << endl << endl;

  #endif

  //----------------------------------------------------------------------------
  Apermutacion solucionSP(numAlum);
  int discrepanciaSP;
  struct timespec cgt1,cgt2; double ncgt; 


  //-----------

  #ifdef PRINT
  cout << "Backtracking SIN poda" << endl;
  #endif

  clock_gettime(CLOCK_REALTIME,&cgt1);

  discrepanciaSP = BacktrackingSP(Discrepancias, solucionSP, numAlum);

  clock_gettime(CLOCK_REALTIME,&cgt2);

  // Calculo de tiempos
  ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
       (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

  //-----------

  #ifdef PRINT

  // Recuperar la solucion
  vector<pair<int,int> > parejas = getParejas(solucionSP, numAlum);


  //Mostramos los resultados de los emparejamientos
  cout << "Discrepancia total: " << discrepanciaSP << endl;
  for (int i = 0; i < numAlum; i++)	
    cout << "PersonumAlum " << parejas[i].first 
         << " con PersonumAlum " << parejas[i].second << endl;

  #endif

  cout << "Tiempo: " << ncgt << endl;

  #ifdef PRINT

  cout << "-------------------------" << endl;

  //----------------------------------------------------------------------------
  Apermutacion solucionCP(numAlum);
  int discrepanciaCP;

  //-----------
  cout << "Backtracking CON poda" << endl;

  clock_gettime(CLOCK_REALTIME,&cgt1);

  discrepanciaCP = BacktrackingCP(Discrepancias, solucionCP, numAlum);

  clock_gettime(CLOCK_REALTIME,&cgt2);

  //-----------

  // Calculo de tiempos
  ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
       (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

  // Recuperar la solucion
  parejas = getParejas(solucionCP, numAlum);

  cout << "Discrepancia total: " << discrepanciaCP << endl;
  for (int i = 0; i < numAlum; i++)
    cout << "PersonumAlum " << parejas[i].first 
         << " con PersonumAlum " << parejas[i].second << endl;

  #endif

  cout << "Tiempo: " << ncgt << endl;

  //----------------------------------------------------------------------------

  //Liberamos memoria
  for (int i = 0; i < numAlum; i++){
    delete Discrepancias[i];
    delete M[i];
  }  

  delete Discrepancias;
  delete M;
}

// Coger el menor de los libres
int CotaInferior(Apermutacion &A, int **Discrepancias, int numAlum) {
  int destimado = 0,
      level = A.GetLevel(), 
      min;
  bool valido;

  vector<int> secuencia = A.GetSecuencia();
 
  // j=level porque los superiores ya están seleccionados
  for (int i=level; i<numAlum; i++) {
    min = numeric_limits<int>::max();

    for (int j=level; j<numAlum; j++) {
      // Ver si este j ha sido seleccionado previamente
      valido = true;

      for (unsigned int k=0; k<secuencia.size(); k++)
        if (secuencia[k] == j+1)	// j+1 porque secuencia empieza en 1
	  valido = false;

      if (valido && Discrepancias[i][j] < min) 
	min = Discrepancias[i][j];      
    }

    destimado += min;
  }

  return destimado;
}

//------------------------------------------------------------------------------

int DiscrepanciaActual(Apermutacion &A, int **Discrepancias, int numAlum) {
  vector<int> solucion = A.GetSecuencia();
  int i = 0,
      dactual = 0;

  while(i < numAlum && solucion[i] != 0) {
    dactual += Discrepancias[i][solucion[i]-1];
    i++;
  }

  return dactual;
}

//------------------------------------------------------------------------------

// Sin poda
int BacktrackingSP(int **Discrepancias, Apermutacion &solucion, int numAlum) {
  Apermutacion A(numAlum);		// Generar arbol de tamaño máximo numAlum
  int dactual = 0, 
      fila, 
      nodos_generados = 0,
      best = numeric_limits<int>::max(); 
  bool seguir;

  do {
    nodos_generados++;
    fila = A.GetLevel();
    dactual = DiscrepanciaActual(A, Discrepancias, numAlum);
 
    // Si es solucion hacer backtracking, comprobar mejor solucion
    if (fila == numAlum-1) {
      if (dactual < best) {
	best = dactual;
        solucion = A;
        seguir = A.Backtracking();
      }
      else
        seguir = A.GeneraSiguienteProfundidad();	
    }
    // En caso contrario seguir
    else
      seguir = A.GeneraSiguienteProfundidad();
    
  } while(seguir);

  #ifdef PRINT

  cout << "Nodos generados: " << nodos_generados << " de " 
	<< A.NumeroSecuenciasPosibles() << " posibles" << endl;

  #endif
 
  return best;
}

//------------------------------------------------------------------------------

// Con poda
int BacktrackingCP(int **Discrepancias, Apermutacion &solucion, int numAlum) {
  Apermutacion A(numAlum);		// Generar arbol de tamaño máximo numAlum
  int dactual = 0, 
      fila, 
      nodos_generados = 0,
      best = numeric_limits<int>::max(); 
  bool seguir;

  do {
    nodos_generados++;
    fila = A.GetLevel();
    dactual = DiscrepanciaActual(A, Discrepancias, numAlum);
 
    // Si es solucion hacer backtracking, comprobar mejor solucion
    if (fila == numAlum-1) {
      if (dactual < best) {
	best = dactual;
        solucion = A;
        seguir = A.Backtracking();
      }
      else
        seguir = A.GeneraSiguienteProfundidad();	
    }
    // En caso contrario estimar y seguir
    else {
      int destimado = dactual + CotaInferior(A, Discrepancias, numAlum);
   
      if (destimado <= best)
        seguir = A.GeneraSiguienteProfundidad();
      else
	seguir = A.Backtracking();
    }    
  } while(seguir);

  cout << "Nodos generados: " << nodos_generados << " de " 
	<< A.NumeroSecuenciasPosibles() << " posibles" << endl;

  return best;
}

//------------------------------------------------------------------------------

int Calculo_discrepancia(int indice1, int indice2, int caracteristicas, int **M){
  int discrepancia = 0;

  for (int i = 0; i < caracteristicas; i++)
    discrepancia += abs (M[indice1][i] - M[indice2][i]);

  return discrepancia;
}

//------------------------------------------------------------------------------

vector<pair<int,int> > getParejas(Apermutacion &solucion, int numAlum) {
  vector<int> secuencia = solucion.GetSecuencia();
  vector<pair<int,int> > parejas;

  for (int i=0; i<numAlum; i++) {
    pair<int,int> nuevaPareja;
    nuevaPareja.first = i+1;
    nuevaPareja.second = secuencia[i];

    parejas.push_back(nuevaPareja);
  }

  return parejas;
}

//------------------------------------------------------------------------------
