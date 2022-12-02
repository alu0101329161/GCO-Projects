#include "file.h"

File::File() {
  // TODO Auto-generated constructor stub

}

File::~File() {
  // TODO Auto-generated destructor stub
}

string File::get_name() {
  return name_;
}

string File::get_path() {
  return path_;
}

vector<string> File::get_content() {
  return content_;
}

vector<pair<string, double>> File::get_tf() {
  return tf_;
}

vector<pair<string, double>> File::get_idf() {
  return idf_;
}

set<pair<string, pair<int, int>>> File::get_words() {
  return words_;
}

vector<pair<string, double>> File::get_tf_idf() {
  return tf_idf_;
}

double File::get_longitud() {
  return longitud_;
}

vector<pair<string, double>> File::get_similitud() {
  return similitud_;
}

vector<pair<double, string>> File::get_similitud_ordenada() {
  return similitud_ordenada_;
}

void File::set_name(string name) {
  name_ = name;
}

void File::set_path(string path) {
  path_ = path;
}

void File::set_content(vector<string> content) {
  content_ = content;
}

void File::set_longitud(double longitud) {
  longitud_ = longitud;
}

void File::set_words(set<pair<string, pair<int, int>>> words) {
  words_ = words;
}

void File::set_tf(vector<pair<string, double>> tf) {
  tf_ = tf;
}

void File::set_idf(vector<pair<string, double>> idf) {
  idf_ = idf;
}

void File::set_tf_idf(vector<pair<string, double>> tf_idf) {
  tf_idf_ = tf_idf;
}

void File::set_similitud(vector<pair<string, double>> similitud) {
  similitud_ = similitud;
}

void File::set_similitud_ordenada(vector<pair<double, string>> similitud_ordenada) {
  similitud_ordenada_ = similitud_ordenada;
}

bool File::operator<(const File file) const { //Sobrecarga del operador <
  return name_ < file.name_;
}