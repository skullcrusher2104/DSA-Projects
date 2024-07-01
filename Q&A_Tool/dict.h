// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Node2{
    public:
        Node2(int _book_code, int _page, int _paragraph, int _word_count);

        Node2* left;
        Node2* right;

        int book_code;
        int page;
        int paragraph;
        int word_count;
};


class TreeNode1{
public:
    std::string word;
    int height;
    int count=0;
    int book_code=-1;
    int page=-1;
    int paragraph=-1;
    int sentence_no=-1;
    Node2* head;

    TreeNode1* par = NULL;
    TreeNode1* left = NULL;
    TreeNode1* right = NULL;

    TreeNode1();
    TreeNode1(std::string k);

    TreeNode1* LeftLeftRotation(); 
    TreeNode1* RightRightRotation(); 
    TreeNode1* LeftRightRotation(); 
    TreeNode1* RightLeftRotation(); 
    void update_para_word_count(int bk_code, int pg_nmbr, int para_nmbr);
    ~TreeNode1();
};

class Tree1{
    private:
    int size = 0;
    TreeNode1* root = NULL;

public: 

    Tree1();
    ~Tree1();

    void insert(int book_code, int page, int paragraph, int sentence_no, std::string word);
 
    int get_word_cnt(std::string k);

    int get_size();

    TreeNode1* get_root();
};

class Dict {
    // You can add attributes/helper functions here
    vector<Tree1*> hashvector;
    int hashfunction(std::string word);
    void insert_word(int book_code, int page, int paragraph, int sentence_no, std::string word);


public: 
    Node2* get_head(string s);
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, std::string sentence);

    int get_word_count(std::string word);

    void dump_dictionary(std::string filename);

    /* -----------------------------------------*/
};