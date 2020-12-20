int indice (int *v, int inicio, int fin){

  //Primero miro que la comprobación va a ser válida
  if (fin < inicio)
    return -1;

  //Divido en dos el vector
  
  int mitad = (inicio + fin)/2;

  //Miro si coincidise que he encontrado en la mitad exacta mi índice

  if(v[mitad]==mitad)
    return mitad;

  //Sino, si la mitad inferior es menor que que mi indice mitad, llamo a la función de nuevo con la mitad inferior del vector

  else if(v[mitad] < mitad)
    return indice (v, inicio, mitad);

  //En otro caso, llamo a la función con la mitad superior del vector
  else
    return indice (v, mitad + 1, fin);
}

//Si no encontrase el índice, devolvería -1, pues se cruzarían el índice fin con inicio sin haberlo encontrado
//Voy llamando a la función de manera recursiva, bien con la mitad superior o bien con la mitad inferior, en función del valor del índice
//Realizo una especie de búsqueda binaria, con lo cual sé que el orden es O(log(n))
//La recurrencia sería T(n) = 2T(n/2) + 1, que realizando los cálculos pertinentes nos da el log(n) que mencionamos anteriormente
//No nos influye que hubiera repeticiones en el vector
