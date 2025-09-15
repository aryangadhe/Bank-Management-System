#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "AVLTree.h"
#include <bits/stdc++.h>
using namespace std;

class FileManager {
public:
    static void saveAccounts(const AVLTree &accounts, const string &filename);
    static void loadAccounts(AVLTree &accounts, const string &filename);

    static void saveTransactions(const AVLTree &accounts, const string &filename);
    static void loadTransactions(AVLTree &accounts, const string &filename);
};

#endif
