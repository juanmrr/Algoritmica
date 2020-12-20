//Aquí, supongo que previamente el vector l que almacena la longitud de los
//programas ha sido ordenado de menor a mayor, pues para minimizar el tiempo entre
//lecturas es lógico que los programas que más tiempo emplean se dejen para el 
//final

//De este modo, el algoritmo voraz es simplemente una asignacion del vector ya ordenado al vector que devolveremos como solución (almacenado)

//"almacenado" es un vector que representa el estado final de los programas en la cinta
void Almacena (vector<int> l, int N, vector<int> almacenado){

	int tam = l.size();

	for (int i = 0; i < tam; i++)
		almacenado[i] = l[i]; //Realizamos la asignacion, recordemos que 
					//el vector está previamente ordenado

}
