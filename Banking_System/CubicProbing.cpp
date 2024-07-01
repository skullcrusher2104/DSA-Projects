#include "CubicProbing.h"

#include "CubicProbing.h"

void CubicProbing::createAccount(std::string id, int count) {
    int hash_code=hash(id);
    if(bankStorage1d[hash_code].id==""){
        bankStorage1d[hash_code].id=id;
        bankStorage1d[hash_code].balance=count;
        account_created();
    }
    else{
        int i=1;
        int new_hash_code=hash_code+1;
        bool resize_needed=false;
        while(new_hash_code<bankStorage1d.size() && bankStorage1d[new_hash_code].id!=""){
            i++;
            new_hash_code=hash_code+i*i*i;
        }
        if(new_hash_code>=bankStorage1d.size()){
            resize_needed=true;
        }
        if(resize_needed){
            bankStorage1d.resize(new_hash_code+1);
            bankStorage1d[new_hash_code].id=id;
            bankStorage1d[new_hash_code].balance=count;
            account_created();
        }
        else{
            bankStorage1d[new_hash_code].id=id;
            bankStorage1d[new_hash_code].balance=count;
            account_created();  
        }
    }
}

std::vector<int> CubicProbing::getTopK(int k) {
    std::vector<int> balances;
    std::vector<int> k_balances;
    for(int i=0;i<bankStorage1d.size();i++){
        if(bankStorage1d[i].id!=""){
            balances.emplace_back(bankStorage1d[i].balance);
        }
    }
    if(balances.size()>=k){
        for(int j=0;j<k;j++){
            int max=get_max(balances);
            k_balances.emplace_back(max);
        }
        return k_balances;
    }
    else{
        int x=balances.size();
        for(int j=0;j<x;j++){
            int max=get_max(balances);
            k_balances.emplace_back(max);
        }
        return k_balances;
    }
}

int CubicProbing::getBalance(std::string id) {
    int hash_code=hash(id);
    if(bankStorage1d[hash_code].id==id){
        return bankStorage1d[hash_code].balance;
    }
    else{
        int i=1;
        int new_hash_code=hash_code+1;
        bool end=false;
        while(new_hash_code<bankStorage1d.size() && bankStorage1d[new_hash_code].id!=id){
            i++;
            new_hash_code=hash_code+i*i*i;
        }
        if(new_hash_code>=bankStorage1d.size()){
            end=true;
        }
        if(end){
            return -1;
        }
        else{
            return bankStorage1d[new_hash_code].balance;
        }
    }
}

void CubicProbing::addTransaction(std::string id, int count) {
    int hash_code=hash(id);
    if(bankStorage1d[hash_code].id==id){
        bankStorage1d[hash_code].balance+=count;
    }
    else{
        int i=1;
        int new_hash_code=hash_code+1;
        bool end=false;
        while(new_hash_code<bankStorage1d.size() && bankStorage1d[new_hash_code].id!=id){
            i++;
            new_hash_code=hash_code+i*i*i;
        }
        if(new_hash_code>=bankStorage1d.size()){
            end=true;
        }
        if(!end){
            bankStorage1d[new_hash_code].balance+=count;
        }
        else{
            bankStorage1d.resize(new_hash_code+1);
            bankStorage1d[new_hash_code].id=id;
            bankStorage1d[new_hash_code].balance=count;
            account_created();
        }
    }
}

bool CubicProbing::doesExist(std::string id) {
    int hash_code=hash(id);
    if(bankStorage1d[hash_code].id==id){
        return true;
    }
    else{
        int i=1;
        int new_hash_code=hash_code+1;
        bool end=false;
        while(new_hash_code<bankStorage1d.size() && bankStorage1d[new_hash_code].id!=id){
            i++;
            new_hash_code=hash_code+i*i*i;
        }
        if(new_hash_code>=bankStorage1d.size()){
            return false;
        }
        else{
            return true;
        }
    }
}

bool CubicProbing::deleteAccount(std::string id) {
    int hash_code=hash(id);
    if(bankStorage1d[hash_code].id==id){
        bankStorage1d[hash_code].id="";
        bankStorage1d[hash_code].balance=-1;
        account_deleted();
        return true;
    }
    else{
        int i=1;
        int new_hash_code=hash_code+1;
        bool end=false;
        while(new_hash_code<bankStorage1d.size() && bankStorage1d[new_hash_code].id!=id){
            i++;
            new_hash_code=hash_code+i*i*i;
        }
        if(new_hash_code>=bankStorage1d.size()){
            return false;
        }
        else{
            bankStorage1d[new_hash_code].id="";
            bankStorage1d[new_hash_code].balance=-1;
            account_deleted();
            return true;
        } 
    }
}

int CubicProbing::databaseSize(){
    return size;
}

int CubicProbing::hash(std::string id){
    long long t1=0,t2=0,t3=0;
    for(int i=0;i<id.size();i++){
        t1+=static_cast<int>((id[i])*(i+79)*(i+23))%213419;
        t2+=static_cast<int>((id[i]*id[i])*(i+179)*(i+213))%2325329;
        t3+=static_cast<int>((id[i]*id[i]*id[i])*(i+67)*(i+97))%232413;
    }
    return (t1+t2+t3)%100019;
}

void CubicProbing::account_created(){
    size++;
}

void CubicProbing::account_deleted(){
    size--;
}

int CubicProbing::get_max(std::vector<int>& balances){
    int max=balances[0];
    int max_index=0;
    for(int i=1;i<balances.size();i++){
        if(balances[i]>max){
            max=balances[i];
            max_index=i;
        }
    }
    balances.erase(balances.begin()+max_index);
    return max;
}