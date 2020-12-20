//Como precondicion, supongo que el vector con los los programas está ordenado de
//menor a mayor tamaño de programa, de modo que la primera posición la ocupará el
//programa que tenga menor tamaño

//Así, mi función de selección se simplifica pues voy escogiendo por orden los
//programas más pequeños con lo cual el número de programas que almaceno en la
//cinta es mayor

vector<int> Cintas (int L, vector<int> n, vector<int> a){

int tam = n.size();
int contador = 0;
int tam_actual = 0;
vector<int> S; //Este va a ser mi vector solución

//Inicializo el vector solucion
for (int i = 0; i < n; i++)
	S[i] = 0;

//Mientras el programa quepa en la cinta y haya programas disponibles
while (tam_actual < L && contador < n.size()){
	//Si se puede almacenar, lo almaceno
	if (tam_actual + a[contador] <= L){
		S[contador] = 1; //Digo en el vector solucion que he cogido esa cinta
		tam_actual += a[contador] //Actualizo el tamaño ocupado de la cinta
	}
	contador++;
}

return S;
}
