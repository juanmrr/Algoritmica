#include "imagen.h"
#include <fstream>

int ContarBlancos (Imagen &fb) {
  int fil = fb.num_filas(),
      col = fb.num_cols(),
      contador = 0;

  //cout << "cuento blancos" << "\n";

  for (int i=0; i<fil; i++)
    for (int j=0; j<col; j++)
      if (fb(i,j) == 255)
        contador++;

  return contador;
}


// Devuelve 1 si la ha encontrado
int ComprobarForma (Imagen &If, Imagen &fb, int inicioi, int inicioj) {
  int blancos = ContarBlancos(fb);
  int contador = 0;

  //cout << "compruebo forma" << "\n";

  for (int i=0; i<fb.num_filas() && i+inicioi<If.num_filas(); i++)
    for (int j=0; j<fb.num_cols() && j+inicioj<If.num_cols(); j++){
      //cout << inicioi << " " << inicioj << "\n";
      if (((inicioi+i) > 0) && ((inicioj+j) > 0) && (If(inicioi+i, inicioj+j) == 255))
        contador++; 
    }
  if (contador == blancos){
      int fil = fb.num_filas(),
      col = fb.num_cols();

      for (int i=0; i<fil; i++)
        for (int j=0; j<col; j++)
          If(i+inicioi,j+inicioj) = 0;

      return 1;
  }
  else
    return 0;
}


int Barrido_Vertical (Imagen &If, Imagen &fb, int fila, int columna, int tam_filas, int tam_cols){
    //cout << "barro vertical" << "\n";
    int contador = 0, i = 0, j = 0;

    while (i < tam_filas){
      for (j = 0; j <= (tam_cols-(fb.num_cols()+1)); j++){
        if(ComprobarForma (If, fb, (fila + i), (j + columna))) {
          contador++;
          i += fb.num_filas();
        }
        else 
          i++;
      }
    }

    return contador;
}

int Barrido_Horizontal (Imagen &If, Imagen &fb, int fila, int columna, int tam_filas, int tam_cols){
    //cout << "barro horizontal" << "\n";
    int contador = 0, i = 0, j = 0;

    while (i < tam_cols){
      for (j = 0; j <= (tam_filas-(fb.num_filas()+1)); j++){
        if(ComprobarForma (If, fb, (fila + i), (j + columna))) {
          contador++;
          i += fb.num_cols();
        }
        else 
          i++;
      }
    }

    return contador;
}


int Formas(Imagen &If, Imagen &fb, int i, int j, int n){

    //cout << "divido" << "\n";

    int contador = 0;

    if(n < fb.num_filas() || n < fb.num_cols())
        return 0;
    else if (n == fb.num_filas() && n == fb.num_cols())
        return ComprobarForma (If, fb, i, j);
    else{
        contador += Formas( If, fb, i, j, n/2);
        contador += Formas( If, fb, i, j + (n/2), n/2);
        contador += Formas( If, fb, i + (n/2), j, n/2);
        contador += Formas( If, fb, i + (n/2), j + (n/2), n/2);
    }

    contador += Barrido_Horizontal (If, fb, (i+(n/2))-fb.num_filas()+2, j, 2*fb.num_filas(), n); 
    contador += Barrido_Vertical (If, fb, i, (j+(n/2))-fb.num_cols()+2, n, 2*fb.num_cols());

    return contador;
}


int main(int argc, char * argv[]){
  if (argc!=3){
      cout<<"Los parametros son: ";
     cout<<"1.-Dime el nombre de una imagen"<<endl;
     cout<<"2.-Dime el nombre de una forma"<<endl;
     return 0;
  }   
  
  Imagen I,forma;
  I.LeerImagen(argv[1]);
  forma.LeerImagen(argv[2]);
  
  //Vuestro codigo para implementar la funcion que busca la forma en I
  
  int n = 0;

  n = Formas(I, forma, 0, 0, I.num_cols());

  cout << n << "\n" << I.num_cols() << forma.num_cols();
  
}
