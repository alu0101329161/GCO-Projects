#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class File {
 private:
  string name_;
  string path_;
  vector<string> content_;
  set<pair<string, pair<int, int>>> words_;          // Palabra, frecuencia en el doc, docs en los que aparece la palabra
  vector<pair<string, double>> tf_;                  // Frecuencia de la palabra en el documento 1 + log10(frecuencia)
  vector<pair<string, double>> idf_;                 // log10(total_docs_/frecuencia_total)
  double longitud_;                                  // longitud del documento
  vector<pair<string, double>> tf_idf_;              // vector normalizado de tf e idf
  vector<pair<string, double>> similitud_;           // similitud coseno entre documentos
  vector<pair<double, string>> similitud_ordenada_;  // similitud coseno entre documentos ordenada
 public:
  File();
  ~File();
  string get_name();
  string get_path();
  set<pair<string, pair<int, int>>> get_words();
  vector<string> get_content();
  vector<pair<string, double>> get_tf();
  vector<pair<string, double>> get_tf_idf();
  vector<pair<string, double>> get_idf();
  vector<pair<string, double>> get_similitud();
  vector<pair<double, string>> get_similitud_ordenada();
  double get_longitud();
  void set_name(string);
  void set_path(string);
  void set_content(vector<string>);
  void set_longitud(double);
  void set_words(set<pair<string, pair<int, int>>>);
  void set_tf(vector<pair<string, double>>);
  void set_idf(vector<pair<string, double>>);
  void set_tf_idf(vector<pair<string, double>>);
  void set_similitud(vector<pair<string, double>>);
  void set_similitud_ordenada(vector<pair<double, string>>);
  bool operator<(const File) const;
};