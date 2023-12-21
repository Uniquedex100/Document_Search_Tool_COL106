#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    // Other data members and functions specific to Linear Probing
    int toBeSize = 200013;
    int nearestPrime = 200007;
    int numberOfAccounts = 0;
    void sorter(int array[],int start,int end){
        if(end-start <= 0){
            return;
        }
        else{
            int res[end-start+1];
            int mid = (end + start)/2;
            sorter(array,start,mid);
            sorter(array,mid+1,end);
            int i = start,j= mid +1;int k = 0;
            while(i<mid+1 && j<end+1){
                if(array[i]>array[j]){res[k] = array[j];j++;k++;}
                else{res[k] = array[i];i++;k++;}
            }
            while(i<mid+1){res[k] = array[i];i++;k++;}
            while(j<end+1){res[k] = array[j];j++;k++;}
            for(int ii = start;ii<end+1;ii++){
                array[ii] = res[ii-start];
            }
        }
    }
    void initialize(){
        if(bankStorage1d.size() == 0){
            bankStorage1d.resize(toBeSize);
            Account dummy;dummy.id = "-1";dummy.balance = -1;
            for(int i = 0;i<toBeSize;i++){
                bankStorage1d[i] = dummy;
            }
        }
    }
};

#endif // LINEARPROBING_H
