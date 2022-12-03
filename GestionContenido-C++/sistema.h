#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_control.h"

using namespace std;

class Sistema {
 private:
  double total_words_;  // Numero total de palabras en todos los documentos
  double total_docs_;   // Numero total de documentos
  set<File> docs_;      // Conjunto de documentos

 public:
  Sistema(set<File>);
  ~Sistema();
  void calcular_tf();
  void calcular_longitud();
  void calcular_tf_idf();
  void calcular_similitud();
  void ordenar_similitud();
  void mostrar_docs();
  void mostrar_tabla_similitud();
  void mostrar_mayor_similitud();
};