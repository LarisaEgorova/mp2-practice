#pragma once

#include <iostream>

using namespace std;

template <typename T>
class TStack {
public:
    virtual void Push(const T& elem) = 0;
    virtual void Pop() = 0;
    virtual T Top() const = 0;
    virtual bool IsEmpty() const = 0;
};