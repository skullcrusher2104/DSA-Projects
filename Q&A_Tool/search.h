// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

class SNode {
public: 
    SNode* next;
    int s_book_code;
    int s_page;
    int s_paragraph;
    int s_sentence_no;
    string s_sentence;
    SNode(int b_code, int pg, int para, int s_no, string s);
};

class SearchEngine {
private:
    SNode* head;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern,long int& n_matches);

    /* -----------------------------------------*/
};