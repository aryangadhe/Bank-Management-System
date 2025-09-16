#ifndef AVLTREE_H
#define AVLTREE_H

#include "Account.h"
#include <functional>  

struct AVLNode {
    Account data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Account& acc) : data(acc), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, const Account& acc);
    AVLNode* search(AVLNode* node, int id) const;

    void inorderHelper(AVLNode* node, std::function<void(const Account&)> visit) const;

public:
    AVLTree() : root(nullptr) {}

    void insert(const Account& acc);
    Account* search(int id);
    const Account* search(int id) const;

    void inorderTraversal(std::function<void(const Account&)> visit) const;
    void searchByBalance(AVLNode* node, double minBalance, vector<Account>& result) const;
    void searchByName(AVLNode* node, const string& name, vector<Account>& result) const;

    vector<Account> searchByBalance(double minBalance) const;
    vector<Account> searchByName(const string& name) const;

};

#endif
