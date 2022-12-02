#include <iostream>
#include "sistema.h"

using namespace std;


int main(int argc, char *argv[]) {

  File_Control file_control;
  file_control.load_docs();
  file_control.remove_stop_words();
  file_control.lematizar();
  Sistema sistema(file_control.get_docs());
  sistema.mostrar_docs();
  sistema.mostrar_tabla_similitud();
  sistema.mostrar_mayor_similitud();
  return 0;
}