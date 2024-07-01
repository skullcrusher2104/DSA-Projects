/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

//#include<iostream>   // dont forget to remove it later;

bool is_int(std::string s){
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
            UnlimitedInt* value = new UnlimitedInt(expression[0]);
            ExprTreeNode* parse_tree = new ExprTreeNode("VAL",value);
            //delete value;
            return parse_tree;
        }
        else{
            //std::cout<<"variable called"<<"\n";
            ExprTreeNode* parse_tree = new ExprTreeNode("VAR",symtable->search(expression[0]));
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
        if(k==expression.size()){
            expression.pop_back();
            expression.erase(expression.begin());
            return parse_tree_creator(expression,symtable);
        }
        UnlimitedInt* v = new UnlimitedInt(0);
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
        if(expression[k]=="%"){
            t="MOD";
        }
        ExprTreeNode* parse_tree = new ExprTreeNode(t,v);
        for(int i=k+1;i<expression.size();i++){
            right_side.emplace_back(expression[i]);
        }
        left_side.erase(left_side.begin());
        right_side.pop_back();
        parse_tree->left=parse_tree_creator(left_side,symtable);
        parse_tree->right=parse_tree_creator(right_side,symtable);
        delete v;
        return parse_tree;
    }
}

UnlimitedRational* parse_tree_evaluator(ExprTreeNode* root, SymbolTable* symtable){
    std::string t=root->type;
    if(t=="VAL"){
        return root->val;
    }
    else if(t=="VAR"){
        return symtable->search(root->id);
    }
    else if(t=="ADD"){
        UnlimitedRational* u = new UnlimitedRational();
        UnlimitedRational* left = parse_tree_evaluator(root->left,symtable);
        UnlimitedRational* right = parse_tree_evaluator(root->right,symtable);
        root->left->evaluated_value=left;
        root->right->evaluated_value=right;
        UnlimitedRational* v=u->add(left,right);
        //root->evaluated_value=v;
        delete u;
        // delete left;
        // delete right;
        return v;
    }
    else if(t=="SUB"){
        UnlimitedRational* u = new UnlimitedRational();
        UnlimitedRational* left = parse_tree_evaluator(root->left,symtable);
        UnlimitedRational* right = parse_tree_evaluator(root->right,symtable);
        root->left->evaluated_value=left;
        root->right->evaluated_value=right;
        UnlimitedRational* v=u->sub(left,right);
        //root->evaluated_value=v;
        delete u;
        // delete left;
        // delete right;
        return v;
    }
    else if(t=="MUL"){
        UnlimitedRational* u = new UnlimitedRational();
        UnlimitedRational* left = parse_tree_evaluator(root->left,symtable);
        UnlimitedRational* right = parse_tree_evaluator(root->right,symtable);
        root->left->evaluated_value=left;
        root->right->evaluated_value=right;
        UnlimitedRational* v=u->mul(left,right);
        //root->evaluated_value=v;
        delete u;
        // delete left;
        // delete right;
        return v;
    }
    else if(t=="DIV"){
        UnlimitedRational* u = new UnlimitedRational();
        UnlimitedRational* left = parse_tree_evaluator(root->left,symtable);
        UnlimitedRational* right = parse_tree_evaluator(root->right,symtable);
        root->left->evaluated_value=left;
        root->right->evaluated_value=right;
        UnlimitedRational* v=u->div(left,right);
        //root->evaluated_value=v;
        delete u;
        // delete left;
        // delete right;
        return v;
    }
    else if(t=="MOD"){
        UnlimitedInt* u = new UnlimitedInt();
        UnlimitedRational* left = parse_tree_evaluator(root->left,symtable);
        UnlimitedRational* right = parse_tree_evaluator(root->right,symtable);
        root->left->evaluated_value=left;
        root->right->evaluated_value=right;
        UnlimitedInt* num = u->mod(left->get_p(),right->get_p());
        UnlimitedInt* den = new UnlimitedInt(1);
        UnlimitedRational* v = new UnlimitedRational(num,den);
        //root->evaluated_value=v;
        delete u;
        // delete left;
        // delete right;
        // delete num;
        // delete den;
        return v;
    }
    else{
        UnlimitedRational* v = new UnlimitedRational();
        //root->evaluated_value=v;
        return v;
    }
}

Evaluator::Evaluator(){
    symtable = new SymbolTable();
}

Evaluator::~Evaluator(){
    delete symtable;
    int x=0;
    for(int i=0;i<expr_trees.size();i++){
        x++;
    }
    for(int i=0;i<x;i++){
        expr_trees.erase(expr_trees.begin());
    }
}

void Evaluator::parse(std::vector<std::string> code){
    std::vector<std::string> expression;
    ExprTreeNode* parse_tree = new ExprTreeNode();
    UnlimitedInt* v = new UnlimitedInt(0);
    ExprTreeNode* variable = new ExprTreeNode("VAR",v);
    parse_tree->left=variable;
    parse_tree->left->id=code[0];
    //delete variable;
    delete v;
    for(int i=2;i<code.size();i++){
        expression.emplace_back(code[i]);
    }
    parse_tree->right=parse_tree_creator(expression,symtable);
    expr_trees.emplace_back(parse_tree);

    /* if(code.size()==1){
        UnlimitedInt* value = new UnlimitedInt(code[0]);
        ExprTreeNode* x = new ExprTreeNode("VAL",value);
        parse_tree->right = x;
        delete value;
        delete x;
    }
    if(code.size()==3){
        UnlimitedInt* v = new UnlimitedInt(0);
        ExprTreeNode* variable = new ExprTreeNode("VAR",v);
        parse_tree->left=variable;
        delete variable;
        delete v;
        UnlimitedInt* value = new UnlimitedInt(code[2]);
        ExprTreeNode* x = new ExprTreeNode("VAL",value);
        parse_tree->right = x;
        delete value;
        delete x;
    }
    else{
        std::vector<ExprTreeNode*> left_side;
        std::vector<ExprTreeNode*> right_side;
        int depth=0;
        int i=0;
        for(i=0;i<code.size();i++){
            if(code[i]=="("){
                depth++;
                left_side.emplace_back(code[i]);
            }
            else if((code[i]=="+"||code[i]=="-"||code[i]=="*"||code[i]=="/"||code[i]=="%") && depth==1){
                break;
            }
            else if(code[i]==")" && depth>=1){
                depth--;
                left_side.emplace_back(code[i]);
            }
            else{
                left_side.emplace_back(code[i]);
            }
        }
        UnlimitedInt* v = new UnlimitedInt(0);
        ExprTreeNode* x = new ExprTreeNode("VAR",v);
        for(i+1;i<code.size();i++){

        }
    } */
}

void Evaluator::eval(){
    ExprTreeNode* parse_tree=expr_trees.back();
    UnlimitedRational* v=parse_tree_evaluator(parse_tree->right,symtable);
    parse_tree->right->val=v;
    parse_tree->right->evaluated_value=v;
    symtable->insert(parse_tree->left->id,v);
}

// int main(){

//     Evaluator *e= new Evaluator();
//     std::vector<std::string> expression1;
//     std::vector<std::string> expression2;
//     std::vector<std::string> expression3;
//     std::vector<std::string> expression4;
//     std::vector<std::string> expression5;
//     std::vector<std::string> expression6;
//     std::vector<std::string> expression7;
//     std::vector<std::string> expression8;
//     std::vector<std::string> expression9;
//     std::vector<std::string> expression10;
//     // expression1.emplace_back("v");
//     // expression1.emplace_back(":=");
//     // expression1.emplace_back("(");
//     // expression1.emplace_back("3");
//     // expression1.emplace_back("+");
//     // expression1.emplace_back("9");
//     // expression1.emplace_back(")");
//     // e->parse(expression1);
//     // e->eval();
//     // expression1.emplace_back("v");
//     // expression1.emplace_back(":=");
//     // expression1.emplace_back("(");
//     // expression1.emplace_back("13");
//     // expression1.emplace_back("+");
//     // expression1.emplace_back("(");
//     // expression1.emplace_back("2");
//     // expression1.emplace_back("/");
//     // expression1.emplace_back("51");
//     // expression1.emplace_back(")");
//     // expression1.emplace_back(")");
//     // e->parse(expression1);
//     // e->eval();

//     expression4.emplace_back("ap1");
//     expression4.emplace_back(":=");
//     expression4.emplace_back("4");
//     e->parse(expression4);
//     e->eval();

//     expression1.emplace_back("ap2");
//     expression1.emplace_back(":=");
//     expression1.emplace_back("(");
//     expression1.emplace_back("(");
//     expression1.emplace_back("ap1");
//     expression1.emplace_back("-");
//     expression1.emplace_back("(");
//     expression1.emplace_back("4");
//     expression1.emplace_back("/");
//     expression1.emplace_back("3");
//     expression1.emplace_back(")");
//     expression1.emplace_back(")");
//     expression1.emplace_back(")");
//     e->parse(expression1);
//     e->eval();

//     expression2.emplace_back("ap3");
//     expression2.emplace_back(":=");
//     expression2.emplace_back("(");
//     expression2.emplace_back("ap2");
//     expression2.emplace_back("+");
//     expression2.emplace_back("(");
//     expression2.emplace_back("4");
//     expression2.emplace_back("/");
//     expression2.emplace_back("5");
//     expression2.emplace_back(")");
//     expression2.emplace_back(")");
//     e->parse(expression2);
//     e->eval();

//     expression3.emplace_back("ap4");
//     expression3.emplace_back(":=");
//     expression3.emplace_back("(");
//     expression3.emplace_back("ap3");
//     expression3.emplace_back("-");
//     expression3.emplace_back("(");
//     expression3.emplace_back("4");
//     expression3.emplace_back("/");
//     expression3.emplace_back("7");
//     expression3.emplace_back(")");
//     expression3.emplace_back(")");
//     e->parse(expression3);
//     e->eval();

//     // expression5.emplace_back("ap5");
//     // expression5.emplace_back(":=");
//     // expression5.emplace_back("(");
//     // expression5.emplace_back("ap4");
//     // expression5.emplace_back("+");
//     // expression5.emplace_back("(");
//     // expression5.emplace_back("4");
//     // expression5.emplace_back("/");
//     // expression5.emplace_back("9");
//     // expression5.emplace_back(")");
//     // expression5.emplace_back(")");
//     // e->parse(expression5);
//     // e->eval();

//     // expression6.emplace_back("ap6");
//     // expression6.emplace_back(":=");
//     // expression6.emplace_back("(");
//     // expression6.emplace_back("ap5");
//     // expression6.emplace_back("-");
//     // expression6.emplace_back("(");
//     // expression6.emplace_back("4");
//     // expression6.emplace_back("/");
//     // expression6.emplace_back("11");
//     // expression6.emplace_back(")");
//     // expression6.emplace_back(")");
//     // e->parse(expression6);
//     // e->eval();

//     // expression7.emplace_back("ap7");
//     // expression7.emplace_back(":=");
//     // expression7.emplace_back("(");
//     // expression7.emplace_back("ap6");
//     // expression7.emplace_back("+");
//     // expression7.emplace_back("(");
//     // expression7.emplace_back("4");
//     // expression7.emplace_back("/");
//     // expression7.emplace_back("13");
//     // expression7.emplace_back(")");
//     // expression7.emplace_back(")");
//     // e->parse(expression7);
//     // e->eval();

//     // expression2.emplace_back("g");
//     // expression2.emplace_back(":=");
//     // expression2.emplace_back("(");
//     // expression2.emplace_back("2");
//     // expression2.emplace_back("*");
//     // expression2.emplace_back("v");
//     // expression2.emplace_back(")");
//     // e->parse(expression2);
//     // e->eval();

//     // expression3.emplace_back("x");
//     // expression3.emplace_back(":=");
//     // expression3.emplace_back("(");
//     // expression3.emplace_back("g");
//     // expression3.emplace_back("+");
//     // expression3.emplace_back("6");
//     // expression3.emplace_back(")");
//     // e->parse(expression3);
//     // e->eval();

//     // expression4.emplace_back("y");
//     // expression4.emplace_back(":=");
//     // expression4.emplace_back("x");
//     // e->parse(expression4);
//     // e->eval();

//     // expression5.emplace_back("a");
//     // expression5.emplace_back(":=");
//     // expression5.emplace_back("x");
//     // e->parse(expression5);
//     // e->eval();

//     // expression6.emplace_back("b");
//     // expression6.emplace_back(":=");
//     // expression6.emplace_back("a");
//     // e->parse(expression6);
//     // e->eval();

//     // expression7.emplace_back("c");
//     // expression7.emplace_back(":=");
//     // expression7.emplace_back("b");
//     // e->parse(expression7);
//     // e->eval();

//     // expression8.emplace_back("d");
//     // expression8.emplace_back(":=");
//     // expression8.emplace_back("c");
//     // e->parse(expression8);
//     // e->eval();

//     // expression9.emplace_back("e");
//     // expression9.emplace_back(":=");
//     // expression9.emplace_back("d");
//     // e->parse(expression9);
//     // e->eval();

//     // expression10.emplace_back("f");
//     // expression10.emplace_back(":=");
//     // expression10.emplace_back("e");
//     // e->parse(expression10);
//     // e->eval();
    
// //     expression4.emplace_back("(");
// //     expression4.emplace_back("(");
// //     expression4.emplace_back("g");
// //     expression4.emplace_back("/");
// //     expression4.emplace_back("2");
// //     expression4.emplace_back(")");
// //     expression4.emplace_back("*");
// //     expression4.emplace_back("(");
// //     expression4.emplace_back("2");
// //     expression4.emplace_back("/");
// //     expression4.emplace_back("51");
// //     expression4.emplace_back(")");
// //     expression4.emplace_back(")");
// //     e->parse(expression4);
// //     e->eval();

//     std::string s=e->symtable->search("ap4")->get_frac_str();
//     for(int i=0;i<s.size();i++){
//         std::cout<<s[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"HELLO!"<<"\n";
//     // std::string s4=e->expr_trees[6]->right->evaluated_value->get_frac_str();
//     // for(int i=0;i<s4.size();i++){
//     //     std::cout<<s4[i];
//     // }
//     delete e;
//     return 0;
// }
