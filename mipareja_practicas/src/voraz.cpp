#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

int Calculo_discrepancia (int indice1, int indice2, int caracteristicas, int **M){

	int discrepancia = 0;

	for (int i = 0; i < caracteristicas; i++)
		discrepancia += abs (M[indice1][i] - M[indice2][i]);

	return discrepancia;
}

vector<pair<int,int> > Voraz (int **Discrepancias, int num_alumnos){
  vector<pair<int,int> > parejas(num_alumnos/2);
  vector<bool> aux;
  int k, pos = 0;

  for (int i = 0; i < num_alumnos; i++)
    aux.push_back(true);

  int dtotal = 0;

  for (int i = 0; i < num_alumnos; i++){
    int dif_min = numeric_limits<int>::max();
    bool escrito = false;
    for (int j = 0; j < num_alumnos; j++)
      if (dif_min > Discrepancias[i][j] && aux[i] == true && aux[j] == true){
	dif_min = Discrepancias[i][j];
	parejas[pos].first = i + 1;
	parejas[pos].second = j + 1;
	k = j;
	escrito = true;
			}
    if (escrito) {
      pos++;
	dtotal += Discrepancias[i][k];
    }
		aux[i] = false;
		aux[k] = false;
	}

  cout << "Discrep: " << 2*dtotal << endl;

	return parejas;
}


int main (int argc, char * argv[]){

	struct timespec cgt1,cgt2; float ncgt; 

	//Se lee el archivo de entrada

	ifstream f (argv[1]);

	if (!f){
		cerr << "el fichero no se puede abrir" << argv[1] << endl;
		return 0;
	}

	string linea;
	getline (f,linea);
	int na, ncar;
	f >> na >> ncar;

	//Se genera la matriz que contiene los datos de entrada

	int **M = new int* [na];
	for (int i = 0; i < na; i++)
		M[i] = new int [ncar];

	//Se escriben los datos en la matriz

	for (int i = 0; i < na; i++)
		for (int j = 0; j < ncar; j++)
			f >> M[i][j];

	//Se genera la matriz que contiene los cálculos de las discrepancias entre alumnos

	int **Discrepancias = new int* [na];
	for (int i = 0; i < na; i++)
		Discrepancias[i] = new int [na];

	//Se calcula la matriz de discrepancias

	for (int i = 0; i < na; i++)
		for (int j = 0; j < na; j++){
			if (i != j){
				Discrepancias[i][j] = Calculo_discrepancia(i, j, ncar, M);
				Discrepancias[j][i] = Calculo_discrepancia(i, j, ncar, M);
			}
			else 
				Discrepancias[i][j] = numeric_limits<int>::max();
		}


	//Mostramos la matriz de discrepancias resultante

	for (int i = 0; i < na; i++){
		cout << endl;
		for (int j = 0; j < na; j++)
			cout << Discrepancias[i][j] << "\t";
	}

	cout << endl;

	vector<pair<int,int> > parejas;

  	clock_gettime(CLOCK_REALTIME,&cgt1);

	parejas = Voraz(Discrepancias, na);

	clock_gettime(CLOCK_REALTIME,&cgt2);

	//Mostramos los resultados de los emparejamientos

	for (int i = 0; i < na/2; i++)
		cout << "Persona " << parejas[i].first << " con Persona " << parejas[i].second << endl;

	cout << "Tiempo: " << ncgt << endl;


	//Liberamos memoria
	for (int i = 0; i < na; i++){
		delete Discrepancias[i];
		delete M[i];
	}
	delete Discrepancias;
	delete M;


	

}
