#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <time.h>

#include "Apermutacion.h"
#include <queue>

#define PRINT // Descomentar para ver solo tiempos

vector<pair<int,int> > getParejas(Apermutacion &solucion, int numAlum);
int DiscrepanciaActual(Apermutacion &A, int **Discrepancias, int numAlum);
int Calculo_discrepancia (int indice1, int indice2, int caracteristicas, int **M);
int Branch_Bound(int **Discrepancias, Apermutacion &solucion, int numAlum); 
vector<pair<int,int> > Voraz (int **Discrepancias, int num_alumnos);
int CotaInferior(Apermutacion &A, int **Discrepancias, int numAlum);


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

  clock_gettime(CLOCK_REALTIME,&cgt1);

  discrepanciaSP = Branch_Bound(Discrepancias, solucionSP, numAlum);

  clock_gettime(CLOCK_REALTIME,&cgt2);

  // Calculo de tiempos
  ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
       (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

  //-----------

  #ifdef PRINT	// No nos interesa si solo queremos los tiempos

  // Recuperar la solucion
  vector<pair<int,int> > parejas = getParejas(solucionSP, numAlum);


  //Mostramos los resultados de los emparejamientos
  cout << "Discrepancia total: " << discrepanciaSP << endl;
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

//------------------------------------------------------------------------------

int DiscrepanciaActual(Apermutacion &A, int **Discrepancias, int numAlum) {
  vector<int> solucion = A.GetSecuencia();

  for (unsigned int j=0; j<solucion.size(); j++) {
    if (solucion[j] > 0)
      solucion[solucion[j]-1] = j+1;
  }
  
  int i = 0,
      dactual = 0;

  for (i = 0; i < numAlum; i++){
    if (solucion[i] != 0)
      dactual += Discrepancias[i][solucion[i]-1];
  }

  return dactual;
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

int Voraz (int **Discrepancias, vector<bool> aux, int num_alumnos){
  vector<pair<int,int> > parejas(num_alumnos/2);
  int k = -1, pos = 0,
      dtotal = 0;

  for (int i = 0; i < num_alumnos; i++){ k = -1;
    if (aux[i] == true){
      int dif_min = numeric_limits<int>::max();
      bool escrito = false;

      for (int j = 0; j < num_alumnos; j++) {
        if (dif_min > Discrepancias[i][j] && aux[j] == true){
	  dif_min = Discrepancias[i][j];
  	  parejas[pos].first = i + 1;
	  parejas[pos].second = j + 1;
	  k = j;
	  escrito = true;
        }
      }

      if (escrito) {
        pos++;
        dtotal += Discrepancias[i][k];
      }
      
      if (k != -1) {
        aux[i] = false;
        aux[k] = false;
      }
    }
  }

   return 2*dtotal; // El doble pues este voraz calcula la discrepancia de la
		    // pareja, no de cada alumno
}

//------------------------------------------------------------------------------

struct nodo {
  Apermutacion P;
  int CI, DE, CS, dactual;

  nodo() :P(5) {}

  nodo(Apermutacion A, int i, int d, int s, int da):P(A) { 
   CI = i;
   DE = d;
   CS = s;
   dactual = da;
  }
};

struct Comparator{
  bool operator() (const nodo &n1, const nodo &n2) {
    return (n1.DE < n2.DE);
  }
};

//------------------------------------------------------------------------------

int Branch_Bound(int **Discrepancias, Apermutacion &solucion, int numAlum) {
  Apermutacion P(numAlum, false);	// Generar arbol de tamaño máximo numAlum
  priority_queue<nodo, vector<nodo>, Comparator> pq;

  vector<bool> aux;

  for (int i = 0; i < numAlum; i++)
    aux.push_back(true);

  int dactual = 0, 
      dmejor = numeric_limits<int>::max(),
      nodos_generados = 0,
      CI = CotaInferior(solucion, Discrepancias, numAlum),
      CS = Voraz(Discrepancias, aux, numAlum),
      DE = (CI + CS) / 2,
      C = CS;

  nodo n;
  n.CS = CS;
  n.CI = CI;
  n.DE = DE;
  n.dactual = 0;
  n.P  = P;

  pq.push(n);

  do {
    nodos_generados++;

    n = pq.top(); pq.pop();

    if (n.CI < C) {
      vector<vector<int> > hijos = n.P.GeneraHijos();

      for (int i=0; i<(int)hijos.size(); i++) { 
        Apermutacion H (hijos[i], n.P.GetLevel()+1);

        for (int k = 0; k < numAlum; k++)
          aux[k] = true;

	vector<int> parejas = H.GetSecuencia();
	for (unsigned int j=0; j<parejas.size(); j++) {
	  if (parejas[j] > 0) {
 	    aux[parejas[j]-1] = false;
 	    aux[j] = false;
	  }
	}

	dactual = DiscrepanciaActual(H, Discrepancias, numAlum);
	CI = dactual + CotaInferior(H, Discrepancias, numAlum);
	CS = dactual + Voraz(Discrepancias, aux, numAlum);
	DE = (CS+CI) / 2;

//	  cout << "Dmejor: " << dmejor << " Dactual: " << dactual << " Level: " << H.GetLevel() << endl;
	if (H.GetLevel() == (numAlum-1) && dactual < dmejor) {
	  dmejor = dactual;
	  if (C > dactual)
	    C = dactual;
	  solucion = H;
	}
	else { //cout << "CI: " << CI << " CS: " << CS << endl;
	  if (CI <= C) { 
	    nodo nuevo(H, CI, DE, CS, dactual);
	    pq.push(nuevo);
	    if (C > CS)
	      C = CS;
	  }
	}
      }
    }

  } while(!pq.empty());

  #ifdef PRINT

  cout << "Nodos generados: " << nodos_generados << " de " 
	<< P.NumeroSecuenciasPosibles() << " posibles" << endl;

  #endif

  return dmejor;
}

//------------------------------------------------------------------------------

int CotaInferior(Apermutacion &A, int **Discrepancias, int numAlum) {
  int destimado = 0, min;
  bool valido;
  int level = A.GetLevel();

  vector<int> secuencia = A.GetSecuencia();

  // Se rellena el vector secuencia con todos los alumnos ya fijados
  for (unsigned int i=0; i<secuencia.size(); i++) {
    if (secuencia[i] > 0)
      secuencia[secuencia[i]-1] = i+1;
  }

  // j=level porque los superiores ya están seleccionados
  for (int i=level; i<numAlum; i++) {
    min = numeric_limits<int>::max();

    if (secuencia[i] <= 0) { // Se comprueba si no está seleccionado

      for (int j=level; j<numAlum; j++) {
        // Ver si este j ha sido seleccionado previamente
        valido = true;

        for (unsigned int k=0; k<secuencia.size(); k++)
          if (secuencia[k] == j+1)	// j+1 porque secuencia empieza en 1
	    valido = false;

        if (valido && Discrepancias[i][j] < min) 
  	  min = Discrepancias[i][j];      
      }
    }

    destimado += min;
  }

  return destimado;
}

//------------------------------------------------------------------------------
