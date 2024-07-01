/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

//#include<iostream> // remove before submission

int get_max(int a,int b){
    if(a>=b){
        return a;
    }
    return b;
}

int getheight(SymNode* root){
    if(root==NULL){
        return -1;
    }
    return root->height;
}

SymNode::SymNode(){
    key="";
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
    // left = new SymNode();
    // right = new SymNode();
    // left->par=this;
    // right->par=this;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* temp=this->right->left;
    SymNode* new_root=this->right;
    if(temp){
        this->right=temp;
        temp->par=this;
        this->height=get_max(getheight(this->left),getheight(this->right))+1;
        new_root->left=this;
        this->par=new_root;
        new_root->height=get_max(getheight(new_root->left),getheight(new_root->right))+1;
        return new_root;
    }
    else{
        this->right=temp;
        //temp->par=this;
        this->height=get_max(getheight(this->left),getheight(this->right))+1;
        new_root->left=this;
        this->par=new_root;
        new_root->height=get_max(getheight(new_root->left),getheight(new_root->right))+1;
        return new_root;
    }
}

SymNode* SymNode::RightRightRotation(){
    SymNode* temp=this->left->right;
    SymNode* new_root=this->left;
    if(temp){
        this->left=temp;
        temp->par=this;
        this->height=get_max(getheight(this->left),getheight(this->right))+1;
        new_root->right=this;
        this->par=new_root;
        new_root->height=get_max(getheight(new_root->left),getheight(new_root->right))+1;
        return new_root;
    }
    else{
        this->left=temp;
        //temp->par=this;
        this->height=get_max(getheight(this->left),getheight(this->right))+1;
        new_root->right=this;
        this->par=new_root;
        new_root->height=get_max(getheight(new_root->left),getheight(new_root->right))+1;
        return new_root;
    }
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* new_right=this->right->RightRightRotation();
    this->right=new_right;
    new_right->par=this;
    this->height=get_max(getheight(this->left),getheight(this->right))+1;
    return this->LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* new_left=this->left->LeftLeftRotation();
    this->left=new_left;
    new_left->par=this;
    this->height=get_max(getheight(this->left),getheight(this->right))+1;
    return this->RightRightRotation();
}

SymNode::~SymNode(){
    key="";
    height=-1;
    // delete left;
    // delete right;
}