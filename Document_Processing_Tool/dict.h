// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class TreeNode{
public:
    std::string word;
    int height;
    int count=0;
    int book_code=-1;
    int page=-1;
    int paragraph=-1;
    int sentence_no=-1;
    
    TreeNode* par = nullptr;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode();
    TreeNode(std::string k);

    TreeNode* LeftLeftRotation(); 
    TreeNode* RightRightRotation(); 
    TreeNode* LeftRightRotation(); 
    TreeNode* RightLeftRotation(); 

    ~TreeNode();
};

class Tree{
    private:
    int size = 0;
    TreeNode* root = nullptr;

public: 

    Tree();
    ~Tree();

    void insert(int book_code, int page, int paragraph, int sentence_no, std::string word);
 
    int get_word_cnt(std::string k);

    int get_size();

    TreeNode* get_root();
};

class Dict {
    // You can add attributes/helper functions here
    vector<Tree*> hashvector;
    int hashfunction(std::string word);
    void insert_word(int book_code, int page, int paragraph, int sentence_no, std::string word);

public: 
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