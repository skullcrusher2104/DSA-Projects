#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    Comp(){
        size=0;
        bankStorage2d.resize(100020);
    }
    
private:
    int size;
    std::vector<int>account_hash_codes;
    void account_created();
    void account_deleted();
    int hash_code_exist(int hash_code);
    int get_max(std::vector<int>& balances);
};

#endif // COMP_H
