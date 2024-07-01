#include "Chaining.h"

void Chaining::createAccount(std::string id, int count){
    int hash_code=hash(id);
    Account account;
    account.id=id;
    account.balance=count;
    bankStorage2d[hash_code].emplace_back(account);
    account_created();
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> balances;
    std::vector<int> k_balances;
    for(int i=0;i<bankStorage2d.size();i++){
        for(int r=0;r<bankStorage2d[i].size();r++){
            balances.emplace_back(bankStorage2d[i][r].balance);
        }
    }
    
    if(balances.size()>=k){
        for(int j=0;j<k;j++){
            int max=get_max(balances);
            k_balances.push_back(max);
        }
        return k_balances;
    }
    else{
        int x=balances.size();
        for(int j=0;j<x;j++){
            int max=get_max(balances);
            k_balances.push_back(max);
        }
        return k_balances;
    }
}

int Chaining::getBalance(std::string id){
    int hash_code=hash(id);
    for(int i=0;i<bankStorage2d[hash_code].size();i++){
        if(bankStorage2d[hash_code][i].id==id){
            return bankStorage2d[hash_code][i].balance;
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    int hash_code=hash(id);
    bool transaction=false;
    for(int i=0;i<bankStorage2d[hash_code].size();i++){
        if(bankStorage2d[hash_code][i].id==id){
            bankStorage2d[hash_code][i].balance+=count;
            transaction=true;
            break;
        }
    }
    if(!transaction){
        createAccount(id,count);
    }
}

bool Chaining::doesExist(std::string id){
    int hash_code=hash(id);
    for(int i=0;i<bankStorage2d[hash_code].size();i++){
        if(bankStorage2d[hash_code][i].id==id){
            return true;
        }
    }
    return false;
}
bool Chaining::deleteAccount(std::string id) {
    int hash_code=hash(id);
    int index=-1;
    for(int i=0;i<bankStorage2d[hash_code].size();i++){
        if(bankStorage2d[hash_code][i].id==id){
            index=i;
            break;
        }
    }
    if(index>=0){
        bankStorage2d[hash_code].erase(bankStorage2d[hash_code].begin()+index);
        account_deleted();
        return true;
    }
    return false;
}

int Chaining::databaseSize() {
    return size;
}

int Chaining::hash(std::string id){
    long long t1=0,t2=0,t3=0;
    for(int i=0;i<id.size();i++){
        t1+=static_cast<int>((id[i])*(i+79)*(i+23))%213419;
        t2+=static_cast<int>((id[i]*id[i])*(i+179)*(i+213))%2325329;
        t3+=static_cast<int>((id[i]*id[i]*id[i])*(i+67)*(i+97))%232413;
    }
    return (t1+t2+t3)%100019;
} 

void Chaining::account_created(){
    size++;
}

void Chaining::account_deleted(){
    size--;
}

int Chaining::get_max(std::vector<int>& balances){
    int max=balances[0];
    int max_index=0;
    for(int i=0;i<balances.size();i++){
        if(balances[i]>max){
            max=balances[i];
            max_index=i;
        }
    }
    balances.erase(balances.begin()+max_index);
    return max;
}
