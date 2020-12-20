SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -pg  -I$(INC) -c -std=c++11


all:  $(BIN)/voraz $(BIN)/backtracking $(BIN)/branch-bound

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************

$(BIN)/voraz: $(OBJ)/Apermutacion.o $(OBJ)/voraz.o
	$(CXX) -o $(BIN)/voraz  $(OBJ)/voraz.o $(OBJ)/Apermutacion.o

$(OBJ)/voraz.o: $(SRC)/voraz.cpp $(INC)/Apermutacion.h
	$(CXX) $(CPPFLAGS) $(SRC)/voraz.cpp -o $(OBJ)/voraz.o	


$(BIN)/backtracking: $(OBJ)/Apermutacion.o $(OBJ)/backtracking.o
	$(CXX) -o $(BIN)/backtracking  $(OBJ)/backtracking.o $(OBJ)/Apermutacion.o

$(OBJ)/backtracking.o: $(SRC)/backtracking.cpp $(INC)/Apermutacion.h
	$(CXX) $(CPPFLAGS) $(SRC)/backtracking.cpp -o $(OBJ)/backtracking.o	


$(BIN)/branch-bound: $(OBJ)/Apermutacion.o $(OBJ)/branch-bound.o
	$(CXX) -o $(BIN)/branch-bound  $(OBJ)/branch-bound.o $(OBJ)/Apermutacion.o

$(OBJ)/branch-bound.o: $(SRC)/branch-bound.cpp $(INC)/Apermutacion.h
	$(CXX) $(CPPFLAGS) $(SRC)/branch-bound.cpp -o $(OBJ)/branch-bound.o	

$(OBJ)/Apermutacion.o: $(SRC)/Apermutacion.cpp $(INC)/Apermutacion.h
	$(CXX) $(CPPFLAGS) $(SRC)/Apermutacion.cpp -o $(OBJ)/Apermutacion.o

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* 
