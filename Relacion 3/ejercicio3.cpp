//Supongo que el vector de tareas ha sido ordenado de menor a mayor tiempo de deadline
//Así, en mi función de selección siempre voy a coger la tarea que tenga un plazo para finalizar más próximo
//En caso de no poder asignar la tarea por estar fuera de tiempo, no tendría sentido analizarla más adelante ni tampoco antes, pues ya presupones que las anteriores tienen un límite de tiempo aún más estricto
//Con lo cual, el algoritmo es una asignación simple donde únicamente se necesita comprobar que se puede asignar en plazo la tarea

void asigna_voraz (vector<int> tareas, vector<double> duracion, vector<double> terminacion, vector<int> S){

	int n = tareas.size();
	double tiempo = 0.0;

	
	//Para cada tarea
	for (int i = 0; i < n; i++){
		//Si el tiempo a partir de donde estamos más la duración de la tarea i no supera el límite establecido, lo asignamos
		if (tiempo + duracion[i] < terminacion[i])
			S[i] = 1;
		else
			S[i] = 0; //En caso contrario, no se pudo asignar la tarea
	}
	
}
