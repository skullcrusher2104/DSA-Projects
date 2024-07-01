#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "dict.h"
#include "search.h"
using namespace std;

class TreeNode{
public:
    std::string word;
    int height;
    
    TreeNode* par = NULL;
    TreeNode* left = NULL;
    TreeNode* right = NULL;

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
    TreeNode* root = NULL;

public: 

    Tree();
    ~Tree();

    void insert(std::string word);
 
    bool search(std::string k);

    int get_size();

    TreeNode* get_root();
};

class QNA_tool {

private:

    // You are free to change the implementation of this function
    Tree* t;
    

    void query_llm(string filename, Node* root, int k, string API_KEY, string question);
    // filename is the python file which will call ChatGPT API
    // root is the head of the linked list of paragraphs
    // k is the number of paragraphs (or the number of nodes in linked list)
    // API_KEY is the API key for ChatGPT
    // question is the question asked by the user

    // You can add attributes/helper functions here

public:
    //SearchEngine* s;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    std::string get_paragraph(int book_code, int page, int paragraph);
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */

    // You can add attributes/helper functions here
    Dict* dictionary;
};

class maxHeap{
public:
    int size;
    std::vector<std::pair<double,vector<int>>> heap;
    int get_parent(int x);
    int get_left(int x);
    int get_right(int x);
    void heapifyUp(int index);
    void heapifyDown(int index);
    std::pair<double,vector<int>> top();
    void push(std::pair<double,vector<int>> element);
    void pop();
    bool empty();
    maxHeap();
};