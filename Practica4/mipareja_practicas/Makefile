SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -pg  -I$(INC) -c


all:  $(BIN)/prueba_APermutacion

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************



	
$(BIN)/prueba_APermutacion: $(OBJ)/Apermutacion.o $(OBJ)/prueba_APermutacion.o
	$(CXX) -o $(BIN)/prueba_Apermutacion  $(OBJ)/prueba_APermutacion.o $(OBJ)/Apermutacion.o

$(OBJ)/prueba_APermutacion.o: $(SRC)/prueba_APermutacion.cpp $(INC)/Apermutacion.h
	$(CXX) $(CPPFLAGS) $(SRC)/prueba_APermutacion.cpp -o $(OBJ)/prueba_APermutacion.o	
$(OBJ)/Apermutacion.o: $(SRC)/Apermutacion.cpp $(INC)/Apermutacion.h
	$(CXX) $(CPPFLAGS) $(SRC)/Apermutacion.cpp -o $(OBJ)/Apermutacion.o

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
