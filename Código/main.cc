#include <iostream>
#include "file_control.h"

using namespace std;

int main(int argc, char *argv[]) {
  string file;

  if (argc < 2) {
    cout << "Nombre del fichero a analizar: ";
    cin >> file;
  }
  else {
    file = argv[1];
  }
  File_Control file_control(file);
  file_control.load_docs();
  file_control.remove_stop_words();
  file_control.lematizar();
  
  Recommender system;

  return 0;
}