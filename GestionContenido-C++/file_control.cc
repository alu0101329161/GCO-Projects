#include "file_control.h"

File_Control::File_Control() {
  char *tmp = get_current_dir_name();
  cout << "Current working directory: " << tmp << endl;
  working_dir_ = tmp;
  // Definimos los directorios de busqueda
  corpus_dir_ = working_dir_ + "/corpus";
  stop_words_dir_ = working_dir_ + "/stop-words";
  docs_dir_ = working_dir_ + "/docs";
  corpusdir_ = corpus_dir_.c_str();
  stopwordsdir_ = stop_words_dir_.c_str();
  docsdir_ = docs_dir_.c_str();
  // Obtenemos los nombres de los archivos de los directorios
  corpus_files_ = obtener_archivos(corpusdir_);
  stop_words_files_ = obtener_archivos(stopwordsdir_);
  docs_files_ = obtener_archivos(docsdir_);
  // Imprimimos los nombres de los archivos
  cout << "\nCorpus files: ";
  for (int i = 0; i < corpus_files_.size(); i++) {
    cout << corpus_files_[i] << ", ";
  }
  cout << "\nStop words files: ";
  for (int i = 0; i < stop_words_files_.size(); i++) {
    cout << stop_words_files_[i] << ", ";
  }
  cout << "\nDocs files: ";
  for (int i = 0; i < docs_files_.size(); i++) {
    cout << docs_files_[i] << ", ";
  }
  cout << endl;
}

// El destructor de la clase.
File_Control::~File_Control() {
  docs_.clear();
  stop_words_.clear();
  corpus_.clear();
}

// Devolviendo el conjunto de documentos.
set<File> File_Control::get_docs() {
  return docs_;
}

// Obtener los archivos del directorio.
vector<string> File_Control::obtener_archivos(const char *dir) {
  vector<string> archivos;

  if (DIR *pDIR = opendir(dir)) {
    while (dirent *entry = readdir(pDIR)) {
      std::string fileName = entry->d_name;

      if (fileName != "." && fileName != "..") {
        archivos.push_back(fileName);
      }
    }
    closedir(pDIR);
  }

  return archivos;
}

// Cargando los documentos.
void File_Control::load_docs() {
  File newdoc;
  int it = 0;
  for (int i = 0; i < docs_files_.size(); i++) {
    newdoc.set_path(docs_dir_ + "/" + docs_files_[i]);
    vector<string> contenido = readfile(newdoc.get_path());

    for (int j = 0; j < contenido.size(); j++) {
      vector<string> aux;
      aux.push_back(contenido[j]);
      aux = limpieza_doc(aux);
      aux = split(aux);
      aux = minusculas(aux);

      newdoc.set_name("doc" + to_string(it));
      newdoc.set_content(aux);
      docs_.insert(newdoc);
      it = 1 + it;
    }
  }
}

// Leer el archivo y devolver el contenido del archivo.
vector<string> File_Control::readfile(string path) {
  vector<string> contenido;
  int iterador = 0;
  ifstream file(path);
  string line;
  while (getline(file, line)) {
    contenido.push_back(line);
  }

  return contenido;
}
// Remover las palabras claves
void File_Control::remove_stop_words() {
  read_stop_words();
  set<File> newdocs;
  for (File aux : docs_) {
    vector<string> aux_content = aux.get_content();
    for (int i = 0; i < aux_content.size(); i++) {
      for (string aux_stop : stop_words_) {
        if (aux_content[i] == aux_stop) {
          aux_content[i].clear();
        }
      }
    }
    aux_content = quitarvacios(aux_content);
    aux.set_content(aux_content);
    newdocs.insert(aux);
  }
  docs_ = newdocs;
}

// Leer las palabras claves
void File_Control::read_stop_words() {
  vector<string> contenido;
  for (int i = 0; i < stop_words_files_.size(); i++) {
    ifstream file(stop_words_dir_ + "/" + stop_words_files_[i]);
    string line;
    while (getline(file, line)) {
      contenido.push_back(line);
    }
  }
  contenido = split(contenido);
  contenido = minusculas(contenido);
  for (string aux : contenido) {
    stop_words_.insert(aux);
  }
}

// Eliminar los signos de puntuación del documento.
vector<string> File_Control::limpieza_doc(vector<string> contenido) {
  vector<string> limpio;
  string aux;
  for (int i = 0; i < contenido.size(); i++) {
    for (int j = 0; j < contenido[i].size(); j++) {
      char caracter = contenido[i][j];
      if (!(caracter == '.' || caracter == ',' || caracter == '!' || caracter == '?' || caracter == '(' || caracter == ')' || caracter == ';' || caracter == ':' || caracter == '-' || caracter == '+' || caracter == '%' || caracter == '$' || caracter == '#' || caracter == '@' || caracter == '&' || caracter == '*' || caracter == '/' || caracter == '1' || caracter == '2' || caracter == '3' || caracter == '4' || caracter == '5' || caracter == '6' || caracter == '7' || caracter == '8' || caracter == '9' || caracter == '0' || caracter == '*' || caracter == '/' || caracter == '=' || caracter == '>' || caracter == '<')) {
        aux += contenido[i][j];
      }
      if (caracter == '-') {
        aux += ' ';
      }
    }
    limpio.push_back(aux);
    aux.clear();
  }

  return limpio;
}

// Dividir la cadena por espacio.
vector<string> File_Control::split(vector<string> str) {  // Guarda en un vector los elementos de una cadena separados por un espacio
  vector<string> lista;
  for (int i = 0; i < str.size(); i++) {
    string splitted;
    stringstream linea(str[i]);
    string aux;

    while (getline(linea, splitted, ' ')) {
      lista.push_back(splitted);
    }
    linea.clear();
    linea.str(lista[lista.size() - 1]);
    while (getline(linea, splitted, '\r')) {
      lista[lista.size() - 1] = splitted;
    }
  }

  return lista;
}

// Convertir todos los caracteres del vector a minúsculas.
vector<string> File_Control::minusculas(vector<string> str) {  // Pasa a minusculas los elementos de un vector
  vector<string> lista;
  for (int i = 0; i < str.size(); i++) {
    string aux;
    for (int j = 0; j < str[i].size(); j++) {
      aux += tolower(str[i][j]);
    }
    lista.push_back(aux);
  }

  return lista;
}

/// Eliminando cadenas vacías del vector.
vector<string> File_Control::quitarvacios(vector<string> str) {
  vector<string> lista;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] != "") {
      lista.push_back(str[i]);
    }
  }

  return lista;
}

// Función lematizar
void File_Control::lematizar() {
  read_corpus();
  set<File> newdocs;
  for (File aux : docs_) {
    vector<string> aux_content = aux.get_content();
    for (int i = 0; i < aux_content.size(); i++) {
      for (int j = 0; j < corpus_.size(); j++) {
        for (int k = 0; k < corpus_[j].second.size(); k++) {
          if (aux_content[i] == corpus_[j].second[k]) {
            aux_content[i] = corpus_[j].first;
          }
        }
      }
    }
    aux.set_content(aux_content);
    newdocs.insert(aux);
  }
  docs_ = newdocs;
}

// Funcion de lectura corpus
void File_Control::read_corpus() {
  vector<string> contenido;

  for (int i = 0; i < corpus_files_.size(); i++) {
    ifstream file(corpus_dir_ + "/" + corpus_files_[i]);
    string line;
    while (getline(file, line)) {
      contenido.push_back(line);
    }
  }
  contenido = split_coma(contenido);
  contenido = eliminar_caracteres(contenido);
  // Añadir al corpus
  bool flag;
  string aux, aux2;
  for (int j = 0; j < contenido.size(); j++) {
    flag = false;
    aux.clear();
    aux2.clear();
    for (int k = 0; k < contenido[j].size(); k++) {  // Diferencia verbo(aux) - conjugacion(aux2)
      if (contenido[j][k] == ':') {
        flag = true;
        k++;
      }
      if (!flag) {
        aux2.push_back(contenido[j][k]);
      } else {
        aux.push_back(contenido[j][k]);
      }
    }
    add_corpus(aux, aux2);
  }
}

// Guarda en un vector los elementos de una cadena separados por un espacio
vector<string> File_Control::split_coma(vector<string> str) {  
  vector<string> lista; 
  for (int i = 0; i < str.size(); i++) {
    string splitted;
    stringstream linea(str[i]);
    string aux;

    while (getline(linea, splitted, ',')) {
      lista.push_back(splitted);
    }
    linea.clear();
    linea.str(lista[lista.size() - 1]);
    while (getline(linea, splitted, '\r')) {
      lista[lista.size() - 1] = splitted;
    }
  }

  return lista;
}

//Eliminando los caracteres `\`, `"`, `{` y `}` de la cadena.
vector<string> File_Control::eliminar_caracteres(vector<string> str) {
  vector<string> lista;
  for (int i = 0; i < str.size(); i++) {
    string aux;
    for (int j = 0; j < str[i].size(); j++) {
      char caracter = str[i][j];
      if (!(caracter == '\\' || caracter == '"' || caracter == '{' || caracter == '}')) {
        aux += str[i][j];
      }
    }
    lista.push_back(aux);
    aux.clear();
  }

  return lista;
}

// Añadir de la raíz y la terminación de la palabra al corpus.
void File_Control::add_corpus(string raiz, string terminacion) {
  bool encontrado = false;
  for (int i = 0; i < corpus_.size(); i++) {
    if (corpus_[i].first == raiz) {
      encontrado = true;
      corpus_[i].second.push_back(terminacion);
      return;
    }
  }
  if (!encontrado) {
    vector<string> aux;
    aux.push_back(terminacion);
    corpus_.push_back(make_pair(raiz, aux));
  }
}