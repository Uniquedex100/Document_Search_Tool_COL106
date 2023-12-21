#include "LinearProbing.h"

#define advance hk = (hk+1) % nearestPrime


void LinearProbing::createAccount(std::string id, int count) {
    initialize();
    if(bankStorage1d.size() == 0){
        bankStorage1d.resize(toBeSize);
        Account dummy;dummy.id = "-1";dummy.balance = -1;
        for(int i = 0;i<toBeSize;i++){
            bankStorage1d[i] = dummy;
        }
    }
    int hk = hash(id);// hashkey
    Account person;person.balance = count;person.id = id;
    while (bankStorage1d[hk].balance != -1){
        advance;
    }
    bankStorage1d[hk] = person;
    numberOfAccounts++;
}

std::vector<int> LinearProbing::getTopK(int k) {
    initialize();
    int array[numberOfAccounts];
    std::vector<int> result;
    int i = 0;
    int j = 0;

    while(i<numberOfAccounts){
        if(bankStorage1d[j].balance>=0){
            array[i] = bankStorage1d[j].balance;i++;
        }
        j++;
    }
    sorter(array,0,numberOfAccounts-1);
    for(int i = 0;i<std::min(k,numberOfAccounts);i++){
        result.push_back(array[numberOfAccounts-1-i]);
    }
    return result;
    return std::vector<int>(); // Placeholder return value
}

int LinearProbing::getBalance(std::string id) {
    initialize();
    int hk = hash(id);
    while(bankStorage1d[hk].balance != -1){
        if(bankStorage1d[hk].id == id){
            return bankStorage1d[hk].balance;
        }
        advance;
    }
    return -1;
}

void LinearProbing::addTransaction(std::string id, int count) {
    initialize();
    int hk = hash(id);
    while(bankStorage1d[hk].balance != -1){
        if(bankStorage1d[hk].id == id){
            bankStorage1d[hk].balance += count;
            return;
        }
        advance;
    }
    Account person;person.balance = count;person.id = id;
    bankStorage1d[hk] = person;
    numberOfAccounts++;
}

bool LinearProbing::doesExist(std::string id) {
    initialize();
    int hk = hash(id);
    while(bankStorage1d[hk].balance != -1){
        if(bankStorage1d[hk].id == id){
            return true;
        }
        advance;
    }
    return false; // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    initialize();
    int hk = hash(id);
    while(bankStorage1d[hk].balance != -1){
        if(bankStorage1d[hk].id == id){
            bankStorage1d[hk].id = "-2";
            bankStorage1d[hk].balance = -2;
            numberOfAccounts--;
            return true;
        }
        advance;
    }
    return false; // Placeholder return value
}
int LinearProbing::databaseSize() {
    initialize();
    return numberOfAccounts; // Placeholder return value
}

int LinearProbing::hash(std::string id) {
    initialize();
    long long hk = 0;
    for(int i = 0;i<id.length();i++){
        long long value = id[i];
        long long value2 = id[id.length()-1-i];
        hk += (value*1069)^(hk*13)^(value2*143);
        hk %= nearestPrime;
    }
    // cout<<hk<<endl;
    return (hk % nearestPrime); // Placeholder return value
}

//126