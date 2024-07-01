// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    for(int i=0; i<1000000; i++){
        Tree* to_be_inserted= new Tree();
        hashvector.push_back(to_be_inserted);
    }
}

Dict::~Dict(){
    for(Tree* tree_pointer: hashvector){
        delete tree_pointer;
    }
}

bool is_punctuation(char x){
    std::string punctuation=".,-:!\'\"()?—[]“”‘’˙;@";
    for(int i=0;i<punctuation.size();i++){
        if(punctuation[i]==x){
            return true;
        }
    }
    return false;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    std::string word="";
    for(char ch:sentence){
        if(ch==' '){
            if(word!=""){
                insert_word(book_code, page, paragraph, sentence_no, word);
                word="";
            }
        }
        else if(is_punctuation(ch)){
            if(word!=""){
                insert_word(book_code, page, paragraph, sentence_no, word);
                word="";
            }
        }
        else{
            word+=tolower(ch);
        }
    }
    
    if(word!=""){
        insert_word(book_code, page, paragraph, sentence_no, word);
        word="";
    }
    return;
}

int Dict::get_word_count(string word){
    int hash= hashfunction(word);
    return hashvector[hash]->get_word_cnt(word);
}

void write_to_file(std::ofstream &output,TreeNode* root){
    if(!root){
        return;
    }
    write_to_file(output,root->left);
    output<<root->word<<", "<<std::to_string(root->count)<<"\n";
    write_to_file(output,root->right);
}

void Dict::dump_dictionary(string filename){ 
    std::ofstream output(filename);
    for (int i=0;i<1000000;i++){
        if(hashvector[i]->get_size()>0){
            write_to_file(output,hashvector[i]->get_root());
        }
    }
    output.close();
}

void Dict::insert_word(int book_code, int page, int paragraph, int sentence_no, string word){
    int hash= hashfunction(word);
    hashvector[hash]->insert(book_code, page, paragraph, sentence_no, word);
    return;
}

int Dict:: hashfunction(string word){
    int hash=7;
    for(char ch: word){
        hash=(hash*19 + (int)ch) % 1000000;
    }
    return hash;
}

int get_height(TreeNode* root){
    if(root==nullptr){
        return -1;
    }
    return root->height;
}

TreeNode::TreeNode(){
    word="";
    height=0;
    par=nullptr;
    left=nullptr;
    right=nullptr;
}

TreeNode::TreeNode(string k){
    word=k;
    height=0;
    par=nullptr;
    left=nullptr;
    right=nullptr;
}

TreeNode* TreeNode::LeftLeftRotation(){
    TreeNode* temp=this->right->left;
    TreeNode* new_root=this->right;
    if(temp){
        this->right=temp;
        temp->par=this;
        this->height=std::max(get_height(this->left),get_height(this->right))+1;
        new_root->left=this;
        this->par=new_root;
        new_root->height=std::max(get_height(new_root->left),get_height(new_root->right))+1;
        return new_root;
    }
    else{
        this->right=temp;
        this->height=std::max(get_height(this->left),get_height(this->right))+1;
        new_root->left=this;
        this->par=new_root;
        new_root->height=std::max(get_height(new_root->left),get_height(new_root->right))+1;
        return new_root;
    }
}

TreeNode* TreeNode::RightRightRotation(){
    TreeNode* temp=this->left->right;
    TreeNode* new_root=this->left;
    if(temp){
        this->left=temp;
        temp->par=this;
        this->height=std::max(get_height(this->left),get_height(this->right))+1;
        new_root->right=this;
        this->par=new_root;
        new_root->height=std::max(get_height(new_root->left),get_height(new_root->right))+1;
        return new_root;
    }
    else{
        this->left=temp;
        this->height=std::max(get_height(this->left),get_height(this->right))+1;
        new_root->right=this;
        this->par=new_root;
        new_root->height=std::max(get_height(new_root->left),get_height(new_root->right))+1;
        return new_root;
    }
}

TreeNode* TreeNode::LeftRightRotation(){
    TreeNode* new_right=this->right->RightRightRotation();
    this->right=new_right;
    new_right->par=this;
    this->height=std::max(get_height(this->left),get_height(this->right))+1;
    return this->LeftLeftRotation();
}

TreeNode* TreeNode::RightLeftRotation(){
    TreeNode* new_left=this->left->LeftLeftRotation();
    this->left=new_left;
    new_left->par=this;
    this->height=std::max(get_height(this->left),get_height(this->right))+1;
    return this->RightRightRotation();
}

TreeNode::~TreeNode(){
}

Tree::Tree(){
    size=0;
    root = new TreeNode();
}

bool is_left_heavy(TreeNode* root){
    if(get_height(root->left)-get_height(root->right)>1){
        return true;
    }
    return false;
}

bool is_balancedd(TreeNode* root){
    if(get_height(root->left)-get_height(root->right)<=1 && get_height(root->right)-get_height(root->left)<=1){
        return true;
    }
    return false;
}

TreeNode* balance_tree(TreeNode* root){
    while(root->par!=nullptr){
        if(!is_balancedd(root)){
            bool left_child=false;
            TreeNode* parent=root->par;
            if(parent->left==root){
                left_child=true;
            }
            TreeNode* child;
            if(is_left_heavy(root)){
                if(get_height(root->left->left)>=get_height(root->left->right)){
                    child=root->RightRightRotation();
                }
                else{
                    child=root->RightLeftRotation();
                }
            }
            else{
                if(get_height(root->right->left)<=get_height(root->right->right)){
                    child=root->LeftLeftRotation();
                }
                else{
                    child=root->LeftRightRotation();
                }
            }
            child->par=parent;
            if(left_child){
                parent->left=child;
            }
            else{
                parent->right=child;
            }
            root=parent;
            root->height=std::max(get_height(root->left),get_height(root->right))+1;
        }
        else{
            root=root->par;
            root->height=std::max(get_height(root->left),get_height(root->right))+1;
        }
    }
    if(root->par==nullptr){
        if(is_balancedd(root)){
            return root;
        }
        if(is_left_heavy(root)){
            if(get_height(root->left->left)>=get_height(root->left->right)){
                root=root->RightRightRotation();
            }
            else{
                root=root->RightLeftRotation();
            }
        }
        else{
            if(get_height(root->right->left)<=get_height(root->right->right)){
                root=root->LeftLeftRotation();
            }
            else{
                root=root->LeftRightRotation();
            }
        }
        root->par=nullptr;
        return root;
    }
    while(root->par!=nullptr){
        root=root->par;                     
    }
    return root;
}

void Tree::insert(int _book_code, int _page, int _paragraph, int _sentence_no, std::string k){
    if(size==0){
        delete root;
        root = new TreeNode(k);
        root->book_code=_book_code;
        root->page=_page;
        root->paragraph=_paragraph;
        root->sentence_no=_sentence_no;
        root->count++;
        size++;
        return;
    }
    TreeNode* current_node=root;
    while(current_node->word!=k && get_height(current_node)>=0){
        if(current_node->word<k){
            if(!current_node->right){
                break;
            }
            current_node=current_node->right;
        }
        else{
            if(!current_node->left){
                break;
            }
            current_node=current_node->left;
        }
    }
    if(current_node->word==k){
        current_node->count++;
        return;
    }
    TreeNode* current_parent=current_node->par;
    TreeNode* child = new TreeNode(k);
    child->book_code=_book_code;
    child->page=_page;
    child->paragraph=_paragraph;
    child->sentence_no=_sentence_no;
    child->count++;
    if(k>current_node->word){
        current_node->right=child;
        child->par=current_node;
        current_node=current_node->right;
    }
    else{
        current_node->left=child;
        child->par=current_node;
        current_node=current_node->left;
    }
    size++;
    while(current_node->par!=nullptr){
        current_node=current_node->par;
        current_node->height=1+std::max(get_height(current_node->left),get_height(current_node->right));
    }
    if(!current_parent){
        return;
    }
    while(is_balancedd(current_parent) && current_parent->par!=nullptr){
        current_parent=current_parent->par;
    }

    root=balance_tree(current_parent);
}

int Tree::get_word_cnt(string k){
    TreeNode* current_node=root;
    if(!root){
        return -2;
    }
    while(current_node->word!=k && get_height(current_node)>=0){
        if(current_node->word<k){
            if(!current_node->right){
                break;
            }
            current_node=current_node->right;
        }
        else{
            if(!current_node->left){
                break;
            }
            current_node=current_node->left;
        }
    }
    if(current_node->word!=k){
        return -2;
    }
    return current_node->count;
}

int Tree::get_size(){
    return size;
}

TreeNode* Tree::get_root(){
    return root;
}

void destruct(TreeNode* root){
    if(!root){
        return;
    }
    destruct(root->left);
    destruct(root->right);
    delete root;
}

Tree::~Tree(){
    size=0;
    destruct(root);
}
