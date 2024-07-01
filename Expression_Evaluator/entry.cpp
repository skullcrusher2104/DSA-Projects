/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
    key="";
    val=new UnlimitedRational();
    left=nullptr;
    right=nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational* v){
    key=k;
    val=v;
    left=nullptr;
    right=nullptr;
}

SymEntry::~SymEntry(){
    key="";
    delete val;
    left=nullptr;
    right=nullptr;
}
