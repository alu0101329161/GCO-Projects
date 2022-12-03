#include "sistema.h"

Sistema::Sistema(set<File> docs) {
  set<pair<string, pair<int, int>>> words;
  File file;
  total_docs_ = docs.size();
  total_words_ = 0;
  for (File aux : docs) {
    total_words_ += aux.get_content().size();
  }
  // Conteo de palabras
  // Cada documento
  for (File aux : docs) {
    int frecuencia = 0, frecuencia_total = 0;
    // Cada palabra del documento
    for (int i = 0; i < aux.get_content().size(); i++) {
      frecuencia = 0;
      // Busqueda en el documento
      for (int j = 0; j < aux.get_content().size(); j++) {
        if (aux.get_content()[i] == aux.get_content()[j]) {
          frecuencia++;
        }
      }
      // Busqueda en todos los documentos
      frecuencia_total = 0;
      bool encontrado = false;
      for (File aux2 : docs) {
        for (int k = 0; k < aux2.get_content().size(); k++) {
          if (aux.get_content()[i] == aux2.get_content()[k]) {
            encontrado = true;
          }
        }
        if (encontrado) {
          frecuencia_total++;
          encontrado = false;
        }
      }
      words.insert(make_pair(aux.get_content()[i], make_pair(frecuencia, frecuencia_total)));
    }
    file.set_name(aux.get_name());
    file.set_path(aux.get_path());
    file.set_content(aux.get_content());
    file.set_words(words);
    docs_.insert(file);
    words.clear();
  }
  // Calculo de tf e idf
  calcular_tf();
  // Calculo de tf-idf
  // Longitud del vector (raiz cuadrada de la suma de los cuadrado de los terminos de cada documento)
  calcular_longitud();
  // Normalizacion de tf-idf
  calcular_tf_idf();
  // Calcular similitud coseno entre documentos
  calcular_similitud();

  ordenar_similitud();
}

Sistema::~Sistema() {
  // TODO Auto-generated destructor stub
}

void Sistema::calcular_tf() {
  set<File> docs2;
  for (File aux : docs_) {
    vector<pair<string, double>> tf;  // tf = 1 + log10(frecuencia)
    for (pair<string, pair<int, int>> aux2 : aux.get_words()) {
      tf.push_back(make_pair(aux2.first, 1 + log10(aux2.second.first)));
    }
    vector<pair<string, double>> idf;  // idf = log10(total_docs_/frecuencia_total)
    for (pair<string, pair<int, int>> aux2 : aux.get_words()) {
      double aux3 = (total_docs_ / aux2.second.second);
      idf.push_back(make_pair(aux2.first, (log10(aux3))));
    }
    aux.set_tf(tf);
    aux.set_idf(idf);
    docs2.insert(aux);
  }
  docs_ = docs2;
}

void Sistema::calcular_longitud() {
  set<File> docs2;
  for (File aux : docs_) {
    double longitud = 0;

    for (pair<string, double> aux2 : aux.get_tf()) {
      longitud += pow(aux2.second, 2);
    }
    longitud = sqrt(longitud);
    aux.set_longitud(longitud);
    docs2.insert(aux);
  }
  docs_ = docs2;
}

void Sistema::calcular_tf_idf() {
  set<File> docs2;
  for (File aux : docs_) {
    vector<pair<string, double>> tf_idf;
    for (int i = 0; i < aux.get_tf().size(); i++) {
      double aux2 = (aux.get_tf()[i].second / aux.get_longitud());
      tf_idf.push_back(make_pair(aux.get_tf()[i].first, aux2));
    }
    aux.set_tf_idf(tf_idf);
    docs2.insert(aux);
  }
  docs_ = docs2;
}

void Sistema::calcular_similitud() {
  set<File> docs2;
  for (File aux : docs_) {
    vector<pair<string, double>> similitud;
    for (File aux2 : docs_) {
      double aux3 = 0;
      for (int i = 0; i < aux.get_tf_idf().size(); i++) {
        for (int j = 0; j < aux2.get_tf_idf().size(); j++) {
          if (aux.get_tf_idf()[i].first == aux2.get_tf_idf()[j].first) {
            aux3 += (aux.get_tf_idf()[i].second * aux2.get_tf_idf()[j].second);
          }
        }
      }
      similitud.push_back(make_pair(aux2.get_name(), aux3));
    }
    aux.set_similitud(similitud);
    docs2.insert(aux);
  }
  docs_ = docs2;
}

void Sistema::ordenar_similitud() {
  set<File> docs2;
  vector<pair<double, string>> similitud_ordenada;
  for (File aux : docs_) {
    for (pair<string, double> aux2 : aux.get_similitud()) {
      similitud_ordenada.push_back(make_pair(aux2.second, aux2.first));
    }
    sort(similitud_ordenada.begin(), similitud_ordenada.end());
    reverse(similitud_ordenada.begin(), similitud_ordenada.end());
    aux.set_similitud_ordenada(similitud_ordenada);
    docs2.insert(aux);
    similitud_ordenada.clear();
  }
  docs_ = docs2;
}

void Sistema::mostrar_docs() {
  bool flag = false;
  for (File aux : docs_) {
    cout << "Nombre: " << aux.get_name() << endl;

    cout << "Ruta: " << aux.get_path() << "\n"
         << endl;

    int it = 0, aux3 = 10;
    flag = false;
    while (it <= aux.get_tf().size()) {
      cout << "Palabra: ";
      for (int i = it; i < aux3; i++) {
        string aux2 = aux.get_tf()[i].first;
        printf("%15s ", aux2.c_str());
      }

      cout << endl
           << "TF:      ";

      for (int i = it; i < aux3; i++) {
        printf("%15f ", aux.get_tf()[i].second);
      }
      cout << endl;
      cout << "IDF:     ";
      for (int i = it; i < aux3; i++) {
        printf("%15f ", aux.get_idf()[i].second);
      }
      cout << endl;
      cout << "TF-IDF:  ";
      for (int i = it; i < aux3; i++) {
        printf("%15f ", aux.get_tf_idf()[i].second);
      }
      cout << endl;
      cout << endl;

      it += 10;
      aux3 += 10;
      if (flag) {
        break;
      }
      if (aux3 > aux.get_tf().size()) {
        aux3 = aux.get_tf().size();
        flag = true;
      }
    }
    cout << "Longitud: " << aux.get_longitud() << "\n"
         << endl;
  }
}

void Sistema::mostrar_tabla_similitud() {
  cout << "Tabla de similitud\n";
  printf("%14s ", "DOCUMENTOS");

  for (File aux : docs_) {
    printf("%14s ", aux.get_name().c_str());
  }
  cout << endl;
  for (File aux : docs_) {
    printf("%14s ", aux.get_name().c_str());
    for (pair<string, double> aux2 : aux.get_similitud()) {
      printf("%14f ", aux2.second);
    }
    cout << endl;
  }
}

void Sistema::mostrar_mayor_similitud() {
  cout << "\nMayor similitud:" << endl;
  for (File aux : docs_) {
    cout << aux.get_name() << " / ";
    cout << aux.get_similitud_ordenada()[1].second << " Similitud: " << aux.get_similitud_ordenada()[1].first * 100
         << "%" << endl;
    cout << endl;
  }
}