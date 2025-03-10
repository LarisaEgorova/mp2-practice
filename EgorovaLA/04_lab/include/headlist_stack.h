#pragma once

#include <iostream>
#include "stack.h"
#include "head_list.h"
#include "polinom.h"

template <typename T>
class THeadListStack : public TStack<T> {
private:
    THeadList<T> stack;
public:
    THeadListStack() :stack() {}

    THeadListStack(const THeadListStack<T>& s) : stack(s.stack) {}

    ~THeadListStack() {
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
        stack.pushFront(data);
    }

    void Pop() {
        stack.PopFront();
    }

    Monom<T> Top() const {
        THeadList<T> stack1(stack);
        Monom<T> tmp;
        while (stack1.getHead() != nullptr) {
            tmp.setKey(stack1.getHead()->key);
            tmp.setConsts(stack1.getHead()->Data);
            stack1.PopBack();
        }
        return tmp;
    }

    const THeadListStack<T>& operator=(const THeadListStack<T>& s) {
        stack = s.stack;
        return *this;
    }

    size_t size() const {
        return stack.size();
    }

    bool operator==(const THeadListStack<T>& s) const {
        return (stack == s.stack);
    }
};