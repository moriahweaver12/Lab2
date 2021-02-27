#include <set>
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void CreateVector(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    vector<string> tokens;
    set<string> unique;
    string next_line;  // Each data line
    string filename = argv[1];
    ifstream in(filename);
    
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        
        while (iss >> token) {
            string nopunct = "";
            for (auto &c : token) { // Remove Punctuation
                if (isalpha(c)) {
                    nopunct += c;
                }
            }
            tokens.push_back(nopunct);
            unique.insert(nopunct);
            // cout << token<<endl;
        }
    }
    cout << "Number of words " << tokens.size() << endl;
    cout << "Number of unique words " << unique.size() << endl;
    ofstream setfile(filename + "_set.txt");
    for (set<string>::iterator it=unique.begin(); it != unique.end(); ++it) {
        //cout << ' ' << *it;
        setfile << ' ' << *it;
    }
    cout << endl;

    const int M = 3;

    //put the vector values into a map
    map<list<string>, vector<string>> wordmap;
    //set up a list with just empty strings
    list<string> state;
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }
   
    for(vector<string>::iterator it=tokens.begin(); it !=tokens.end(); it++) {
        wordmap[state].push_back(*it);
        state.push_back(*it);
        state.pop_front();
    }
    srand(time(NULL)); // this line initializes the random number generated
    // so you dont get the same thing every time
    state.clear();

    for (int i = 0; i < M; i++) {
       state.push_back("");
    }

    for (int i = 0; i < 100; i++) {
        int ind = rand() % wordmap[state].size();
        cout << wordmap[state][ind]<<" ";
        state.push_back(wordmap[state][ind]);
        state.pop_front();
    }
}