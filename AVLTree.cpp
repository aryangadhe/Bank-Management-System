#include "AVLTree.h"
#include <algorithm>
using namespace std;

// ================= Height & Balance =================
int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// ================= Rotations =================
AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// ================= Insert =================
AVLNode* AVLTree::insert(AVLNode* node, const Account& acc) {
    if (!node) return new AVLNode(acc);

    if (acc.getId() < node->data.getId())
        node->left = insert(node->left, acc);
    else if (acc.getId() > node->data.getId())
        node->right = insert(node->right, acc);
    else
        return node; // Duplicate not allowed

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && acc.getId() < node->left->data.getId())
        return rightRotate(node);

    if (balance < -1 && acc.getId() > node->right->data.getId())
        return leftRotate(node);

    if (balance > 1 && acc.getId() > node->left->data.getId()) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && acc.getId() < node->right->data.getId()) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const Account& acc) {
    root = insert(root, acc);
}

// ================= Search =================
AVLNode* AVLTree::search(AVLNode* node, int id) const {
    if (!node || node->data.getId() == id)
        return node;

    if (id < node->data.getId())
        return search(node->left, id);
    else
        return search(node->right, id);
}

Account* AVLTree::search(int id) {
    AVLNode* node = search(root, id);
    return node ? &node->data : nullptr;
}

const Account* AVLTree::search(int id) const {
    AVLNode* node = search(root, id);
    return node ? &node->data : nullptr;
}

// ================= Traversal =================
void AVLTree::inorderHelper(AVLNode* node, function<void(const Account&)> visit) const {
    if (!node) return;
    inorderHelper(node->left, visit);
    visit(node->data);
    inorderHelper(node->right, visit);
}

void AVLTree::inorderTraversal(function<void(const Account&)> visit) const {
    inorderHelper(root, visit);
}
