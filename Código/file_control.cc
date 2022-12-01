#include "file_control.h"

File_Control::File_Control(string file) {
  docs_file_ = file;
  char *tmp = get_current_dir_name();
  cout << "Current working directory: " << tmp << endl;
  working_dir_ = tmp;
  //Definimos los directorios de busqueda
  corpus_dir_ = working_dir_ + "/corpus";
  stop_words_dir_ = working_dir_ + "/stop-words";
  docs_dir_ =
      working_dir_ + "/docs";
  corpusdir_ = corpus_dir_.c_str();
  stopwordsdir_ = stop_words_dir_.c_str();
  docsdir_ = docs_dir_.c_str();
  //Obtenemos los nombres de los archivos de los directorios
  corpus_files_ = obtener_archivos(corpusdir_);
  stop_words_files_ = obtener_archivos(stopwordsdir_);
    //Imprimimos los nombres de los archivos
    cout << "\nCorpus files:\n" << endl;
  for (unsigned long int i = 0; i < corpus_files_.size(); i++) {
    cout << corpus_files_[i] << endl;
  }
    cout << "\nStop words files:\n" << endl;
  for (unsigned long int i = 0; i < stop_words_files_.size(); i++) {
    cout << stop_words_files_[i] << endl;
  }
    cout << "\nDocs file:\n" << file << "\n" << endl;
}

File_Control::~File_Control() {
  // TODO Auto-generated destructor stub
}

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

void File_Control::load_docs() {
  File newdoc;

  newdoc.set_name(docs_file_);
  newdoc.set_path(docs_dir_ + "/" + docs_file_);
  vector<string> contenido = readfile(newdoc.get_path());
  contenido = limpieza_doc(contenido);
  contenido = split(contenido);
  contenido = minusculas(contenido);
  newdoc.set_content(contenido);
  docs_.insert(newdoc);

}

vector<string> File_Control::readfile(string path) {
  vector<string> contenido;
  ifstream file(path);
  string line;
  while (getline(file, line)) {
    contenido.push_back(line);
  }

  return contenido;
}

void File_Control::remove_stop_words() {
  read_stop_words();
  set<File> newdocs;
  cout << "Stop words: " << stop_words_.size() << endl;
  for (File aux : docs_) {
    vector<string> aux_content = aux.get_content();
    for (unsigned long int i = 0; i < aux_content.size(); i++) {
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

  //mostrar contenido de docs
    for (File aux : docs_) {
        cout << "Nombre: " << aux.get_name() << endl;
        cout << "Path: " << aux.get_path() << endl;
        cout << "Contenido: " << endl;
        for (string aux2 : aux.get_content()) {
        cout << aux2 << "  ";
        }
        cout << endl;
    }
}

void File_Control::read_stop_words() {
  vector<string> contenido;
  for (unsigned long int i = 0; i < stop_words_files_.size(); i++) {
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

vector<string> File_Control::limpieza_doc(vector<string> contenido) {
  vector<string> limpio;
  string aux;
  for (unsigned long int i = 0; i < contenido.size(); i++) {
    for (unsigned long int j = 0; j < contenido[i].size(); j++) {
      char caracter = contenido[i][j];
      if (!(caracter == '.' || caracter == ',' || caracter == '!' || caracter == '?' || caracter == '('
          || caracter == ')'
          || caracter == ';' || caracter == ':' || caracter == '-' || caracter == '+' || caracter == '%'
          || caracter == '$'
          || caracter == '#' || caracter == '@' || caracter == '&' || caracter == '*' || caracter == '/'
          || caracter == '1' || caracter == '2' || caracter == '3' || caracter == '4' || caracter == '5'
          || caracter == '6' || caracter == '7' || caracter == '8' || caracter == '9' || caracter == '0'
          || caracter == '*' || caracter == '/' || caracter == '=' || caracter == '>' || caracter == '<')) {
        aux += contenido[i][j];

      }

    }
    limpio.push_back(aux);
    aux.clear();
  }

  return limpio;
}

vector<string> File_Control::split(vector<string> str) { //Guarda en un vector los elementos de una cadena separados por un espacio
  vector<string> lista;
  for (unsigned long int i = 0; i < str.size(); i++) {

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

vector<string> File_Control::minusculas(vector<string> str) { //Pasa a minusculas los elementos de un vector
  vector<string> lista;
  for (unsigned long int i = 0; i < str.size(); i++) {
    string aux;
    for (unsigned long int j = 0; j < str[i].size(); j++) {
      aux += tolower(str[i][j]);
    }
    lista.push_back(aux);
  }

  return lista;
}

vector<string> File_Control::quitarvacios(vector<string> str) {
  vector<string> lista;
  for (unsigned long int i = 0; i < str.size(); i++) {
    if (str[i] != "") {
      lista.push_back(str[i]);
    }
  }

  return lista;
}

void File_Control::lematizar() {
    read_corpus();
    set<File> newdocs;
    for (File aux : docs_) {
        vector<string> aux_content = aux.get_content();
        for (unsigned long int i = 0; i < aux_content.size(); i++) {
            for (unsigned long int j = 0; j < corpus_.size(); j++) {
              for (unsigned long int k = 0; k < corpus_[j].second.size(); k++) {
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

void File_Control::read_corpus() {
  vector<string> contenido;

  for (unsigned long int i = 0; i < corpus_files_.size(); i++) {
    ifstream file(corpus_dir_ + "/" + corpus_files_[i]);
    string line;
    while (getline(file, line)) {
      contenido.push_back(line);
    }
  }
    contenido = split_coma(contenido);
    contenido = eliminar_caracteres(contenido);
    //Añadir al corpus
    bool flag;
    string aux, aux2;
    for (unsigned long int j = 0; j < contenido.size(); j++) {
      flag = false;
      aux.clear();
      aux2.clear();
        for (unsigned long int k = 0; k < contenido[j].size(); k++) { //Diferencia verbo(aux) - conjugacion(aux2)
          if (contenido[j][k] == ':') {
            flag = true;
            k++;
          }
          if (!flag) {
            aux2.push_back(contenido[j][k]);
          }
          else {
            aux.push_back(contenido[j][k]);
          }
        }
        add_corpus(aux, aux2);
    }
  }

vector<string> File_Control::split_coma(vector<string> str) { //Guarda en un vector los elementos de una cadena separados por un espacio
  vector<string> lista;
  for (unsigned long int i = 0; i < str.size(); i++) {

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

vector<string> File_Control::eliminar_caracteres(vector<string> str) {
  vector<string> lista;
  for (unsigned long int i = 0; i < str.size(); i++) {
    string aux;
    for (unsigned long int j = 0; j < str[i].size(); j++) {
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

void File_Control::add_corpus(string raiz, string terminacion) {
  bool encontrado = false;
  for (unsigned long int i = 0; i < corpus_.size(); i++) {
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