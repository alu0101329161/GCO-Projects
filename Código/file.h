#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class File {
    private:
    string name_;
    string path_;
    vector<string> content_;
    set<pair<string, int>> words_;
    public:
    File();
    ~File();
    string get_name();
    string get_path();
    vector<string> get_content();
    set<pair<string, int>> get_words();
    void set_name(string);
    void set_path(string);
    void set_content(vector<string>);
    void set_words(vector<string>);
    bool operator<(const File) const;

};