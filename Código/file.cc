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

set<pair<string, int>> File::get_words() {
    return words_;
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

bool File::operator<(const File file) const { //Sobrecarga del operador <
    return name_ < file.name_;
}

void File::set_words(vector<string> words) {
    for (int i = 0; i < words.size(); i++) {
        pair<string, int> newpair;
        newpair.first = words[i];
        newpair.second = 1;
        words_.insert(newpair);
    }
}