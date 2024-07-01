// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class Sentence{
public:
    int book_code=-1;
    int page=-1;
    int paragraph=-1;
    int sentence_no=-1;
    std::string sentence;

    Sentence(int _book_code, int _page, int _paragraph, int _sentence_no, string _sentence);
};

class SearchEngine {
private:
    std::vector<Sentence*> sentences;
    long size=0;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};