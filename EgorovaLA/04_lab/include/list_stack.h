#pragma once

#include <iostream>
#include "stack.h"
#include "list.h"

template <typename T>
class TListStack : public TStack<T> {
private:
    TList<T> stack;
public:
    TListStack() :stack() {}

    TListStack(const TListStack<T>& s) : stack(s.stack) {}

    ~TListStack() {
        while (!stack.IsEmpty()) {
            stack.PopBack();
        }
    }

    bool IsEmpty() const {
        return (stack.IsEmpty());
    }

    bool IsFull() const {
        return ~(stack.IsEmpty());
    }

    void Push(const T& data) {
        stack.pushBack(data);
    }

    void Pop() {
        stack.PopBack();
    }

    TNode<T>* Top() const {
        TNode<T>* tmp(stack.getPStop());
        return tmp;
    }

    const TListStack<T>& operator=(const TListStack<T>& s) {
        stack = s.stack;
        return *this;
    }

    size_t size() const {
        return stack.size();
    }

    bool operator==(const TListStack<T>& s) const {
        return (stack == s.stack);
    }
};