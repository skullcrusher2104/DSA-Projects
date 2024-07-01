// Do NOT add any other includes
#include "dict.h"

Node2::Node2(int _book_code, int _page, int _paragraph, int _word_count){
    book_code=_book_code;
    page=_page;
    paragraph=_paragraph;
    word_count=_word_count;
    left=NULL;
    right=NULL;
}



Dict::Dict(){
    for(int i=0; i<1000000; i++){
        Tree1* to_be_inserted= new Tree1();
        hashvector.push_back(to_be_inserted);
    }
}

Dict::~Dict(){
    for(Tree1* tree_pointer: hashvector){
        delete tree_pointer;
    }
}

int get_height(TreeNode1* root){
    if(root==NULL){
        return -1;
    }
    return root->height;
}

Node2* Dict::get_head(string s){
    int hash= hashfunction(s);
    Tree1* tree=hashvector[hash];
    TreeNode1* current_node=tree->get_root();
    if(!current_node){
        return NULL;
    }
    while(current_node->word!=s && get_height(current_node)>=0){
        if(current_node->word<s){
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
    if(current_node->word!=s){
        return NULL;
    }
    return current_node->head;
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



void write_to_file(std::ofstream &output,TreeNode1* root){
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

TreeNode1::TreeNode1(){
    word="";
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
    head=NULL;
}

TreeNode1::TreeNode1(string k){
    word=k;
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
    head=NULL;
}

TreeNode1* TreeNode1::LeftLeftRotation(){
    TreeNode1* temp=this->right->left;
    TreeNode1* new_root=this->right;
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

TreeNode1* TreeNode1::RightRightRotation(){
    TreeNode1* temp=this->left->right;
    TreeNode1* new_root=this->left;
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

TreeNode1* TreeNode1::LeftRightRotation(){
    TreeNode1* new_right=this->right->RightRightRotation();
    this->right=new_right;
    new_right->par=this;
    this->height=std::max(get_height(this->left),get_height(this->right))+1;
    return this->LeftLeftRotation();
}

TreeNode1* TreeNode1::RightLeftRotation(){
    TreeNode1* new_left=this->left->LeftLeftRotation();
    this->left=new_left;
    new_left->par=this;
    this->height=std::max(get_height(this->left),get_height(this->right))+1;
    return this->RightRightRotation();
}

TreeNode1::~TreeNode1(){
}

void TreeNode1::update_para_word_count(int bk_code, int pg_nmbr, int para_nmbr){
    if(head==NULL){
        head=new Node2(bk_code, pg_nmbr, para_nmbr, 1);
        return;
    }
    Node2* newhead= new Node2(bk_code, pg_nmbr, para_nmbr, 1);
    newhead->right=head;
    head=newhead;
}

Tree1::Tree1(){
    size=0;
    root = new TreeNode1();
}

bool is_left_heavy(TreeNode1* root){
    if(get_height(root->left)-get_height(root->right)>1){
        return true;
    }
    return false;
}

bool is_balancedd(TreeNode1* root){
    if(get_height(root->left)-get_height(root->right)<=1 && get_height(root->right)-get_height(root->left)<=1){
        return true;
    }
    return false;
}

TreeNode1* balance_tree(TreeNode1* root){
    while(root->par!=NULL){
        if(!is_balancedd(root)){
            bool left_child=false;
            TreeNode1* parent=root->par;
            if(parent->left==root){
                left_child=true;
            }
            TreeNode1* child;
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
    if(root->par==NULL){
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
        root->par=NULL;
        return root;
    }
    while(root->par!=NULL){
        root=root->par;                     
    }
    return root;
}

void Tree1::insert(int _book_code, int _page, int _paragraph, int _sentence_no, std::string k){
    if(size==0){
        delete root;
        root = new TreeNode1(k);
        root->book_code=_book_code;
        root->page=_page;
        root->paragraph=_paragraph;
        root->sentence_no=_sentence_no;
        root->count++;
        root->update_para_word_count(_book_code, _page, _paragraph);
        size++;
        return;
    }
    TreeNode1* current_node=root;
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
        current_node->update_para_word_count(_book_code, _page, _paragraph);
        return;
    }
    TreeNode1* current_parent=current_node->par;
    TreeNode1* child = new TreeNode1(k);
    child->book_code=_book_code;
    child->page=_page;
    child->paragraph=_paragraph;
    child->sentence_no=_sentence_no;
    child->count++;
    child->update_para_word_count(_book_code, _page, _paragraph);
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
    while(current_node->par!=NULL){
        current_node=current_node->par;
        current_node->height=1+std::max(get_height(current_node->left),get_height(current_node->right));
    }
    if(!current_parent){
        return;
    }
    while(is_balancedd(current_parent) && current_parent->par!=NULL){
        current_parent=current_parent->par;
    }

    root=balance_tree(current_parent);
}

int Tree1::get_word_cnt(string k){
    TreeNode1* current_node=root;
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

int Tree1::get_size(){
    return size;
}

TreeNode1* Tree1::get_root(){
    return root;
}

void destroyll(Node2* head){
    if(head==NULL) return;
    Node2* temp = head->right;
    while(temp!=NULL){
        temp->left = NULL;
        delete head;
        head = temp;
        temp = head->right;
    }
    delete head;
}

void destruct(TreeNode1* root){
    if(!root){
        return;
    }
    destroyll(root->head);
    destruct(root->left);
    destruct(root->right);
    delete root;
}

Tree1::~Tree1(){
    size=0;
    destruct(root);
}