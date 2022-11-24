#include <iostream>
#include "file_control.h"

using namespace std;
void help();

int main(int argc, char *argv[]) {

  File_Control file_control;
  file_control.load_docs();
  file_control.remove_stop_words();
  file_control.lematizar();

  Sistemarecomendador sistema;

  return 0;
}

void help() {
  cout << "Este programa permite generar una gramatica a partir de un automata finito.\n";
  cout << "Para ejecutar usar: ./main [Fichero.fa] [Fichero.gr]\n";
  cout << "Formato del fichero del automata, ejemplo:\n";
  cout << "0 1\n"
          "4\n"
          "0\n"
          "0 0 2 0 2 1 1\n"
          "1 1 2 0 1 1 1\n"
          "2 0 2 0 1 1 3\n"
          "3 0 2 0 2 1 3";
  cout << "Linea 1: Alfabeto del automata.\n";
  cout << "Linea 2: Numero de estados\n";
  cout << "Linea 3: Estado inicial\n";
  cout << "Lineas [4 - 3 + numero de estados]:\n";
  cout << "Campo 1:[Nombre_Estado] Campo 2:[Bit de aceptacion] Campo 3:[Numero de transiciones]\n";
  cout << "Campo n%2:[Simbolo] Campo !n%2:[Estado de llegada] n > 3\n";
}