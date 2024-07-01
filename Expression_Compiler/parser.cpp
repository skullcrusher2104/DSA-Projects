/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// #include<iostream> // remove before submission

//Write your code below this line

bool is_int(std::string s){
    if(s[0]=='-'){
        return true;
    }
    for(int i=0;i<s.size();i++){
        if(s[i]<'0' || s[i]>'9'){
            return false;
        }
    }
    return true;
}

ExprTreeNode* parse_tree_creator(std::vector<std::string> expression, SymbolTable* symtable){
    if(expression.size()==1){
        if(is_int(expression[0])){
            int value=std::stoi(expression[0]);
            ExprTreeNode* parse_tree = new ExprTreeNode("VAL",value);
            //delete value;
            return parse_tree;
        }
        else{
            //std::cout<<"variable called"<<"\n";
            ExprTreeNode* parse_tree = new ExprTreeNode("VAR",0/* symtable->search(expression[0]) */);
            parse_tree->id=expression[0];
            return parse_tree;
        }
    }
    else{
        std::vector<std::string> left_side;
        std::vector<std::string> right_side;
        int depth=0;
        int k=0;
        for(int i=0;i<expression.size();i++){
            if(expression[i]=="("){
                depth++;
                left_side.emplace_back(expression[i]);
            }
            else if((expression[i]=="+"||expression[i]=="-"||expression[i]=="*"||expression[i]=="/"||expression[i]=="%") && depth==1){
                break;
            }
            else if(expression[i]==")" && depth>=1){  /// strictly greater????
                depth--;
                left_side.emplace_back(expression[i]);
            }
            else{
                left_side.emplace_back(expression[i]);
            }
            k++;
        }
        //int v=0;
        std::string t;
        if(expression[k]=="+"){
            t="ADD";
        }
        if(expression[k]=="-"){
            t="SUB";
        }
        if(expression[k]=="*"){
            t="MUL";
        }
        if(expression[k]=="/"){
            t="DIV";
        }
        // if(expression[k]=="%"){
        //     t="MOD";
        // }
        ExprTreeNode* parse_tree = new ExprTreeNode(t,0);
        for(int i=k+1;i<expression.size();i++){
            right_side.emplace_back(expression[i]);
        }
        left_side.erase(left_side.begin());
        right_side.pop_back();
        parse_tree->left=parse_tree_creator(left_side,symtable);
        parse_tree->right=parse_tree_creator(right_side,symtable);
        //delete v;
        return parse_tree;
    }
}

Parser::Parser(){
    symtable = new SymbolTable();
    last_deleted=-1;
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* parse_tree = new ExprTreeNode();
    // ExprTreeNode* parse_tree_left = new ExprTreeNode();
    // ExprTreeNode* parse_tree_right = new ExprTreeNode();
    if(expression[0]=="del"){
        parse_tree->left = new ExprTreeNode("DEL",0);
        parse_tree->right = new ExprTreeNode("VAR",0/* symtable->search(expression[2]) */);
        parse_tree->right->id=expression[2];
        last_deleted=symtable->search(expression[2]);
        symtable->remove(expression[2]);
    }
    else if(expression[0]=="ret"){
        parse_tree->left = new ExprTreeNode("RET",0);
        std::vector<std::string> x;
        for(int i=2;i<expression.size();i++){
            x.emplace_back(expression[i]);
        }
        parse_tree->right=parse_tree_creator(x,symtable);
    }
    else{
        parse_tree->left = new ExprTreeNode("VAR",0);
        parse_tree->left->id=expression[0];
        std::vector<std::string> x;
        for(int i=2;i<expression.size();i++){
            x.emplace_back(expression[i]);
        }
        parse_tree->right=parse_tree_creator(x,symtable);
        symtable->insert(expression[0]);
    }
    expr_trees.emplace_back(parse_tree);
}

Parser::~Parser(){
  delete symtable;
  int x=expr_trees.size();
  for(int i=0;i<x;i++){
    delete expr_trees[i];
  }
}

// void inorder(ExprTreeNode* root){
//     if(root==NULL) return;
//     inorder(root->left);
//     cout << root->num << " ";
//     inorder(root->right);

// }

// int main(){
//     Parser* targ = new Parser;
//     std::vector<std::string> s1;
//     std::vector<std::string> s2;
//     s1.emplace_back("a");
//     s1.emplace_back(":=");
//     s1.emplace_back("(");
//     s1.emplace_back("(");
//     s1.emplace_back("6");
//     s1.emplace_back("/");
//     s1.emplace_back("3");
//     s1.emplace_back(")");
//     s1.emplace_back("+");
//     s1.emplace_back("-3");
//     s1.emplace_back(")");
//     targ->parse(s1);
//     s2.emplace_back("ret");
//     s2.emplace_back(":=");
//     s2.emplace_back("a");
//     targ->parse(s2);
//     // std::cout<<targ->expr_trees[1]->left->type<<"\n";
//     inorder(targ->expr_trees[0]);
// }