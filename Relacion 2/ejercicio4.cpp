//Similar al ejercicio 3 de la práctica 2
//Se plantea con la posibilidad de que pueda haber números repetidos, y por eso se devuelve un pair con las posiciones primera y última que compartan el mismo número
//Función para intercambiar
void swap(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}
//Función para ordenar los vectores
void Quicktornillos (int *tuercas, int *tornillos, int i, int j) {
  if (i<j) {
    //Se obtiene la posición de pivote en ambos vectores
    pair<int,int> pTor = Pivote (tuercas, i, j, tornillos[i]);
    pair<int,int> pZTue = Pivote (tornillos, i, j, tuercas[pTor.second]);
    //Se llama a la función recursivamente con el vector dividido en dos partes, la inferior al pivote y la superior al pivote
    Quicktornillos(tuercas, tornillos, i, pTue.first-1);
    Quicktornillos(tuercas, tornillos, pTue.second+1, j);
  }
}
//Función que ordena según el pivote
pair<int, int> Pivote (int *v, int i, int j, int piv) {
  int k, l;
  k = i;
  l = j+1;
  do {
    k += 1;
  } while (v[k] <= piv && k < j); //avanzamos por la izquierda mientras v[k] sea menor que pivote
  do {
    l -= 1;
  } while (v[l] > piv); //retrocedemos desde la derecha mientras v[l] sea mayor que pivote
  while (k < l) { //Mientras no se cruzen los índices, intercambiamos las posiciones y avanzamos
    swap(v+k, v+l);
    do {
      k += 1;
    } while (v[k] <= piv);
    do {
      l -= 1;
    } while (v[l] > piv);
  } 
  //Antes de intercambiar pivote por su posición definitiva, se busca su posición real en el vector
  //En este código se da por sentado que pivote siempre está en la posición i
  swap(v+i, v+l);

  pair<int,int> pivotes = OrdenarPivotes(v, i, l); // Devuelve el piv en la posición más baja y en la más alta (su posición)

  return pivotes;
}
//En el peor de los casos, el orden de esta función es de O(n²)
//En el peor de los casos, pivote se situaría en la primera posición del vector, y la recurrencia sería T(n) = 2*n + T(n-1), que haciendo los cálculos pertinentes, resulta un n²
//Tenemos que la función pivote sería de orden n en ese peor de los casos, recorrería todo el vector; y la función OrdenarPivotes que no aparece implementada, sería también de orden n pues simplemente se ocupa de agrupar los valores iguales a pivote
