//
// Created by root on 10/31/23.
//

#ifndef ALGO_SOLUTION_H
#define ALGO_SOLUTION_H

#include <algorithm>
#include <utility>
#include <bits/stdc++.h>

#include "BasicDataStructure.h"

using namespace std;

/**
 * @problem: <problem source>: <problem name>
 * @site: all function should be scripted like this;
 * @methods: template function
 * **/
[[maybe_unused]] void template_function() {}

template <class T=int>
TListNode<T>* create_from_array(vector<T> source) {
    TListNode<T> *root = nullptr, *s = nullptr;
    for (auto element: source) {
        if (!root) {
            root = new TListNode<T>(element);
            s = root;
        } else {
            s->next = new TListNode<T>(element);
            s = s->next;
        }
    }
    return root;
}

#endif //ALGO_SOLUTION_H
