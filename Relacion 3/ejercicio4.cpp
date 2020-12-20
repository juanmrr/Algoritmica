//Suponemos que el vector de cintas está ordenado según su núero de movimientos, de menor a mayor
//Con esto conseguimos que la función de selección sea una simple asignación
//Al tener el vector ordenado de menor a mayor número de movimientos, tenemos siempre el menor número combinación de ambas cintas, y obteniendo siempre el mínimo, la suma esos mínimos nos va a dar el mínimo número total de movimientos una vez combinadas

//Las cintas ordenadas debidamente se almacenan en el vector S que es la solución

void asignar_voraz (int vector<int> cintas, int vector<int> movimientos, int vector<int> S){

	int n = cintas.size();

	for (int i = 0; i < n; i++)
		S[i] = cintas[i];
}
