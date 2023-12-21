//
// Created by root on 12/7/23.
//

#ifndef ALGO_BASICDATASTRUCTURE_H
#define ALGO_BASICDATASTRUCTURE_H

// Definition for binary tree.
template <class T=int>
struct TTreeNode {
    T val;
    TTreeNode* left;
    TTreeNode* right;

    explicit TTreeNode(const T& _x): val(_x), left(nullptr), right(nullptr) {}
    TTreeNode(const T& _x, TTreeNode* _left, TTreeNode* _right): val(_x), left(_left), right(_right) {}
};


// Definition for singly-linked list.
template <class T=int>
struct TListNode {
    T val;
    TListNode *next;
    TListNode() : val(0), next(nullptr) {}
    explicit TListNode(T x) : val(x), next(nullptr) {}
    TListNode(T x, TListNode *next) : val(x), next(next) {}
};


#endif //ALGO_BASICDATASTRUCTURE_H
