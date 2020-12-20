vector<Edificio> skyline(vector<Edificio> skyline){ //La funcion recibe como parámetro un vector de skyline
							//Edificio es un struct que contiene las coordenadas básicas de cada edificio
//Parto de que el vector de edificios está previamente ordenado por la coordenada de la izquieda del edificio

	//Si el número de skyline es 1, devuelvo directamente el edificio
	if(skyline == 1){
	  return skyline;

	//Si el número de skyline es 2, intento concatenarlos
	}else if(skyline == 2){
	  if(skyline[0].xmax > skyline[1].xmin){ //Si se supornen
	    //Compruebo cuál es más alto de los dos
	    if(skyline[0].altura > skyline[1].altura){
	      //Modifico en cada caso las nuevas coordenadas
	      skyline[1].xmin = skyline[0].xmax;
	    }else{
	      skyline[0].xmax = skyline[1].xmin; 
	    }
	  }
	  return skyline;
	//Si el número de skyline es mayor que 2, sigo operando y diviendo el vector
	}else{
	  //Divido el vector en dos subvectores [izquierda, derecha]
	  vector<Edificio> izquierda(skyline /2);
	  vector<Edificio> derecha  (skyline - skyline) /2);

	  //Copio los dos subvectores en "izquierda" y en "derecha"


	  //Llamo recursivamente a la función para cada mitad del vector original
	  izquierda = skyline(izquierda);
	  derecha   = skyline(derecha);

	  //Miro en los laterales de los edificios
	  if(izquierda[izquierda - 1].xmax > derecha[0].xmin){ //Si el último de la izquierda es mayor que el primero de la derecha...
	    if(izquierda[izquierda - 1].altura > derecha[0].altura){
	      derecha[0].xmin = izquierda[izquierda - 1].xmax;
	    }else{
	      izquierda[izquierda - 1].xmax = derecha[0].xmin; 
	    }
	  }

	  return izquierda;

	}
}
//El orden de esta función es de n*log(n).
//Se parte en dos recursivamente el vector de edificios y se hacen las comprobaciones pertinentes para fusionar los edificios en caso de que se den las condiciones
//Obtendriamos una recurrencia tal que T(n) = n + 2T(n/2) que haciendo cálculos nos sale el n*log(n) que comentamos anteriormente
//La n sería porque reescribo el vector con los edificios concatenados (2*n/2) y el T(n/2) porque lo voy diviendo en dos recursivamente, llamando a la función con la mitad del tamaño del vector, el resto de operaciones asumimos coste constante pues son comprobaciones

