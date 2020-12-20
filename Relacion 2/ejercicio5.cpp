void secuencia (vector<int> v, int inicio, int final, vector<int> resultadoado) {
	int tam =  final - inicio;
	
	//Si tengo un elemento, lo meto en el vector
	if (tam == 1)
		resultado.push_back (v[inicio]);
	//Si tengo dos elementos, compruebo el ganador y lo inserto en ese orden
	else if (tam == 2) {
		if (v [inicio] < v [inicio + 1])
			resultado.push_back (v[inicio]);
			resultado.push_back (v [inicio + 1]);
	} else { //Si no ocurre lo anterior, divido el vector en 2 partes, izquierda y derecha
		vector<int> izquierda;
		vector<int> derecha;
		vector<int> intermedio;
		
		//Llamo recursivamente a la función con las dos mitades del vector
		secuencia (v, mitad, final, derecha);
		secuencia (v, inicio, mitad, izquierda);

		//Compruebo si el primero de la derecha es mayor que el último de la izquierda		
		if (derecha.front() >= izquierda.back()) {
			int pos = izquierda - 2;

		while (pos > 0 && seaCreciente) //Mientras la posición sea válida y la secuencia sea creciente
			//En cuyo caso lo inserto en el vector
			intermedio.push_back (izquierda.back ());
		}
		
		//Si el vector izquierda es mayor que el vector derecha y que el intermedio, me quedo con el de la izquierda
		if (izquierda > derecha && izquierda > intermedio)
			resultado = izquierda;
		//Si el vector derecha es mayor que el intermedio, me quedo con el de la derecha
		else if (derecha > intermedio)
			resultado = derecha;
		//En caso contrario, me quedo con el intermedio
		else
			resultado = intermedio;
	}
}
//En el peor de los casos, tenemos que la función secuencia es de orden n²
//Nos quedaría la recurrencia T(n) = 2*T(n/2) + n
//En el peor caso, llamamos dos veces a la función recursivamente (2*T(n/2)) y puede que la secuencia sea todo el vector, en cuyo caso finalmente lo recorro entero
