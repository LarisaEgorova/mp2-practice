#pragma once

#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
class TStack {
public:
    virtual void Push(const T& elem) = 0;
    virtual void Pop() = 0;
    virtual TNode<T>* Top() const = 0;
    virtual bool IsEmpty() const = 0;
};