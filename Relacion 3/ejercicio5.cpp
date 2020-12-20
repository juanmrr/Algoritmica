//El algoritmo se basa en ir viendo hasta donde puedo llegar antes de repostar, teniendo como arco de autonomía X, que es lo que dura el depósito
//Así pues, mientras pueda llegar a la siguiente gasolinera, avanzo
//En este caso, no tiene sentido ordenar el vector de gasolineras pues es algo estático (no pueden cambiar de posición las gasolineras a antojo), X es lo que dura un depósito lleno y A y B son los puntos de origen y destino. S es el vector que contiene la solución, con las gasolineras donde se ha repostado a true y el resto a false

//Sí presupongo que mi vector gasolineras contiene la distancia en kilómetros ENTRE cada gasolinera y la anterior, de modo que iterar sobre el vector signifique avanzar en el trayecto

void repostaje_Voraz (vector<int> gasolineras, int X, int A, int B, vector<bool> S){

	int n = gasolineras.size();

	//Inicializo el vector solución a false, se pondrá a true cuando reposte en esa gasolinera

	for (int i = 0; i < n; i++)
		S.push_bach(false);

	int trayecto_recorrido;
	int trayecto_total = B - A;
	int contador = 0;


	//Mientras no haya llegado a destino (lo que llevo recorrido es menor que lo que tengo que recorrer)

	while (trayecto_recorrido < trayecto_total){
		trayecto_recorrido = 0;
		//Si no puedo llegar a la gasolinera siguiente, reposto
		if (gasolineras[contador + 1] > Y){
			trayecto_recorrido = gasolineras[contador];
			S[contador] = true;
			Y = X; //Lleno el depósitov
			
		}
		//Sino, digo que puedo avanzar hasta la siguiente
		else{
			trayecto_recorrido = gasolineras[contador+1];
			Y -= gasolineras[contador+1]; //Vacío el depósito de acuerdo al kilometraje
		
		contador++;
	}

}
		
