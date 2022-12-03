#include <dirent.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "file.h"
using namespace std;

class File_Control {
 private:
  string working_dir_;
  string corpus_dir_;
  string stop_words_dir_;
  string docs_dir_;
  vector<string> corpus_files_;
  vector<string> stop_words_files_;
  vector<string> docs_files_;
  const char *corpusdir_;
  const char *stopwordsdir_;
  const char *docsdir_;
  set<File> docs_;
  set<string> stop_words_;
  vector<pair<string, vector<string>>> corpus_;

 public:
  File_Control();
  ~File_Control();
  set<File> get_docs();
  void get_files();
  void print_files();
  // Lectura de archivos
  vector<string> obtener_archivos(const char *);
  void load_docs();
  vector<string> readfile(string);
  // Stop-words
  void remove_stop_words();
  void read_stop_words();
  // Limpieza de documentos
  vector<string> limpieza_doc(vector<string>);
  vector<string> split(vector<string>);
  vector<string> split_coma(vector<string>);
  vector<string> minusculas(vector<string>);
  vector<string> quitarvacios(vector<string>);
  vector<string> eliminar_caracteres(vector<string>);
  // Lematizar
  void lematizar();
  void read_corpus();
  void add_corpus(string, string);
};