/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

// #include<iostream> // remove before submission

//Write your code below this line

int get_max1(int a,int b){
    if(a>=b){
        return a;
    }
    return b;
}

int get_height1(SymNode* root){
    if(root==NULL){
        return -1;
    }
    return root->height;
}

bool is_left_heavy(SymNode* root){
    if(get_height1(root->left)-get_height1(root->right)>1){
        return true;
    }
    return false;
}

// bool is_right_heavy(SymNode* root){
//     if(root->right->height-root->left->height>1){
//         return true;
//     }
//     return false;
// }

bool is_balancedd(SymNode* root){
    if(get_height1(root->left)-get_height1(root->right)<=1 && get_height1(root->right)-get_height1(root->left)<=1){
        return true;
    }
    return false;
}

SymNode* balance_tree(SymNode* root){
    while(root->par!=NULL){
        //std::cout<<"while1 ";
        if(!is_balancedd(root)){
            bool left_child=false;
            SymNode* parent=root->par;
            if(parent->left==root){
                left_child=true;
            }
            SymNode* child;
            if(is_left_heavy(root)){
                if(get_height1(root->left->left)>=get_height1(root->left->right)){
                    child=root->RightRightRotation();
                    // parent->left=child;
                    // parent->height=get_max1(parent->left->height,parent->right->height)+1;
                    //std::cout<<"RR"<<"\n";
                }
                else{
                    child=root->RightLeftRotation();
                    //std::cout<<"root after rotation: "<<child->key<<"\n";
                    // parent->left=child;
                    // parent->height=get_max1(parent->left->height,parent->right->height)+1;
                    //std::cout<<"RL"<<"\n";
                }
            }
            else{
                if(get_height1(root->right->left)<=get_height1(root->right->right)){
                    child=root->LeftLeftRotation();
                    // parent->right=child;
                    // parent->height=get_max1(parent->left->height,parent->right->height)+1;
                    //std::cout<<"LL"<<"\n";
                }
                else{
                    child=root->LeftRightRotation();
                    // parent->right=child;
                    // parent->height=get_max1(parent->left->height,parent->right->height)+1;
                    //std::cout<<"LR"<<"\n";
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
            root->height=get_max1(get_height1(root->left),get_height1(root->right))+1;
        }
        else{
            root=root->par;
            root->height=get_max1(get_height1(root->left),get_height1(root->right))+1;
        }
    }
    if(root->par==NULL){
        if(is_balancedd(root)){
            return root;
        }
        if(is_left_heavy(root)){
            if(get_height1(root->left->left)>=get_height1(root->left->right)){
                root=root->RightRightRotation();
                //std::cout<<"RR root"<<"\n";
            }
            else{
                root=root->RightLeftRotation();
                //std::cout<<"RL root"<<"\n";
            }
        }
        else{
            if(get_height1(root->right->left)<=get_height1(root->right->right)){
                root=root->LeftLeftRotation();
                //std::cout<<"LL root"<<"\n";
            }
            else{
                root=root->LeftRightRotation();
                //std::cout<<"LR root"<<"\n";
            }
        }
        root->par=NULL;
        return root;
    }
    while(root->par!=NULL){
        //std::cout<<"while2 ";
        root=root->par;                     // error is probably here only;
    }
    return root;
}

SymNode* get_successor(SymNode* root){
    SymNode* successor=root->right;
    while(get_height1(successor->left)>=0 && successor->left){
        //std::cout<<"while3 ";
        successor=successor->left;
    }
    return successor;
}

SymbolTable::SymbolTable(){
    size=0;
    root = new SymNode();
}

void SymbolTable::insert(string k){
    if(size==0){
        // std::cout<<"yay"<<"\n";
        delete root;
        root = new SymNode(k);
        size++;
        return;
    }
    SymNode* current_node=root;
    while(current_node->key!=k && get_height1(current_node)>=0){
        //std::cout<<"while4 ";
        if(current_node->key<k){
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
    if(current_node->key==k){
        return;
    }
    SymNode* current_parent=current_node->par;
    SymNode* child = new SymNode(k);
    if(k>current_node->key){
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
        //std::cout<<"while5 ";
        //std::cout<<current_node->key<<"\n";
        current_node=current_node->par;
        current_node->height=1+get_max1(get_height1(current_node->left),get_height1(current_node->right));
    }
    if(!current_parent){
        return;
    }
    while(is_balancedd(current_parent) && current_parent->par!=NULL){
        //std::cout<<"while6 ";
        current_parent=current_parent->par;
    }


    if(!is_balancedd(current_parent)){
        //std::cout<<"unbalanced node: "<<current_parent->key<<"\n";
    }

    root=balance_tree(current_parent);
}

void SymbolTable::remove(string k){
    bool single_child=false;
    SymNode* current_node=root;
    SymNode* node_to_be_deleted;
    while(current_node->key!=k && get_height1(current_node)>=0){
        //std::cout<<"while7 ";
        if(current_node->key<k){
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
    // if(get_height1(current_node)==-1){
    //     //std::cout<<"didnt get"<<"\n";
    //     return;
    // }
    if(current_node->key!=k){
        return;
    }
    if(size==1){
        delete root;
        root=NULL;
        size--;
        return;
    }
    if(get_height1(current_node->left)==-1 && get_height1(current_node->right)==-1){
        // delete current_node->left;
        // delete current_node->right;
        // current_node->left=NULL;
        // current_node->right=NULL;
        // current_node->key="";
        // current_node->height=-1;
        if(current_node->par->right==current_node){
            current_node->par->right=NULL;
            //current_node->par=NULL;
            node_to_be_deleted=current_node;
            //delete current_node;
        }
        else{
            current_node->par->left=NULL;
            //current_node->par=NULL;
            node_to_be_deleted=current_node;
            //delete current_node;
        }
    }
    else if(get_height1(current_node->left)==-1 && get_height1(current_node->right)!=-1){
        //std::cout<<"hi  "<<"\n";
        single_child=true;
        //std::cout<<":"<<current_node->key<<"\n";
        if(current_node->par==NULL){
            current_node->right->par=NULL;
            root=current_node->right;
            current_node->par=NULL;
            current_node->left=NULL;
            current_node->right=NULL;
            delete current_node;
            size--;
            return;
        }
        if(current_node->par->right==current_node){
            current_node->par->right=current_node->right;
            current_node->right->par=current_node->par;
            current_node->right=NULL;
        }
        else{
            current_node->par->left=current_node->right;
            current_node->right->par=current_node->par;
            current_node->right=NULL;
        }
        //std::cout<<"new child: "<<current_node->par->right->key<<"\n";
        //current_node->par->height=1+get_max1(current_node->par->left->height,current_node->par->right->height);
        node_to_be_deleted=current_node;
    }
    else if(get_height1(current_node->left)!=-1 && get_height1(current_node->right)==-1){
        single_child=true;
        if(current_node->par==NULL){
            current_node->left->par=NULL;
            root=current_node->left;
            current_node->par=NULL;
            current_node->left=NULL;
            current_node->right=NULL;
            delete current_node;
            size--;
            return;
        }
        if(current_node->par->right==current_node){
            current_node->par->right=current_node->left;
            current_node->left->par=current_node->par;
            current_node->left=NULL;
        }
        else{
            current_node->par->left=current_node->left;
            current_node->left->par=current_node->par;
            current_node->left=NULL;
        }
        //current_node->par->height=1+get_max1(current_node->par->left->height,current_node->par->right->height);
        node_to_be_deleted=current_node;
    }
    else{
        SymNode* successor=get_successor(current_node);
        std::string x=successor->key;
        int m_address=successor->address;
        remove(x);
        current_node->key=x;
        current_node->address=m_address;
        return;
    }
    SymNode* current_parent=current_node->par;
    // if(!current_parent){
    //     size--;
    //     return;
    // }
    while(current_node->par!=NULL){
        //std::cout<<"while8 ";
        current_node=current_node->par;
        current_node->height=1+get_max1(get_height1(current_node->left),get_height1(current_node->right));
    }
    while(is_balancedd(current_parent) && current_parent->par!=NULL){
        //std::cout<<"while9 ";
        current_parent=current_parent->par;
    }
    
    node_to_be_deleted->par=NULL;
    node_to_be_deleted->left=NULL;
    node_to_be_deleted->right=NULL;
    delete node_to_be_deleted;


    if(!is_balancedd(current_parent)){
        // std::cout<<"unbalanced node: "<<current_parent->key<<"\n";
    }

    root=balance_tree(current_parent);
    size--;
}

int SymbolTable::search(string k){
    SymNode* current_node=root;
    if(!root){
        return -2;
    }
    while(current_node->key!=k && get_height1(current_node)>=0){
        //std::cout<<"while7 ";
        if(current_node->key<k){
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
    if(current_node->key!=k){
        //std::cout<<"couldnt find\n";
        return -2;
    }
    return current_node->address;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* current_node=root;
    while(current_node->key!=k && get_height1(current_node)>=0){
        //std::cout<<"while7 ";
        if(current_node->key<k){
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
    current_node->address=idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

void destruct(SymNode* root){
    if(!root){
        return;
    }
    destruct(root->left);
    destruct(root->right);
    delete root;
}

SymbolTable::~SymbolTable(){
    size=0;
    destruct(root);
    // delete root->left;
    // delete root->right;
    // delete root;
}

// int main(){
//     SymbolTable* s = new SymbolTable();
//     // s->insert("t");
//     // s->insert("p");
//     // s->insert("o");
//     // s->insert("f");
//     // s->insert("r");
//     // s->insert("a");
//     // s->insert("s");
//     // s->insert("m");
//     // s->insert("p");
//     // s->insert("o");

//     // s->insert("j");
//     // s->insert("r");
//     // s->insert("l");
//     // s->insert("q");
//     // s->insert("x");
//     // s->insert("m");
//     // s->insert("p");
//     // s->insert("n");
//     // s->insert("k");
//     // s->insert("f");

//     // s->insert("a");
//     // s->insert("b");
//     // s->insert("c");
//     // s->insert("d");

//     //std::cout<<"successor: "<<get_successor(s->get_root())->key<<"\n";
//     // s->insert("s");
//     // s->assign_address("s",0);
//     // s->insert("m");
//     // s->assign_address("m",1);
//     // s->insert("rx");
//     // s->assign_address("rx",2);

//     // s->remove("m");
//     // s->remove("s");
//     // s->remove("rx");
//     // std::cout<<(s->get_root()==NULL)<<"\n";
//     // s->insert("p");
//     // std::cout<<"size: "<<s->get_size()<<"\n";
//     // std::cout<<"y: "<<s->get_root()->key<<"\n";
//     // std::cout<<"s++ "<<s->search("p")<<"\n";

//     s->insert("717");
//     s->insert("814");
//     s->insert("368");
//     s->insert("200");
//     s->insert("658");
//     s->remove("717");
//     std::cout<<s->get_root()->key<<"\n";
//     //std::cout<<s->search("q")<<"\n";
//     // std::cout<<"x: "<<is_balancedd(s->get_root())<<"\n";
// }