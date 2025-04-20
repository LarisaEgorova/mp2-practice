#pragma once

#include "list.h"

using namespace std;

template <typename T>
class THeadList : public TList<T> {
protected:
    TNode<T>* pHead;
public:
    THeadList() :TList() {
        pHead = new TNode<T>();
        pLast = pHead;
    }

    THeadList(const T& data) : TList(data) {
        pHead = new TNode<T>();
        pHead->pNext = pFirst;
    }

    THeadList(const THeadList<T>& list) :TList(list) {
        pHead = new TNode<T>();
        pHead->pNext = pFirst;
    }

    const THeadList<T>& operator=(const THeadList& list) {
        TList<T>::operator=(list);
        pHead->pNext = pFirst;
        return *this;
    }

    bool operator==(const THeadList<T>& list) const {
        return (TList<T>::operator==(list));
    }

    virtual void pushFront(const T& data) override {
        TList<T>::pushFront(data);
        pHead->pNext = pFirst;
        return;
    }

    virtual void pushBack(const T& data) override {
        TList<T>::pushBack(data);
        return;
    }

    virtual void PopBack() override {
        TList<T>::PopBack();
        return;
    }

    virtual void PopFront() override {
        TList<T>::PopFront();
        pHead->pNext = pFirst;
        return;
    }

    virtual bool IsEmpty() const override {
        return TList<T>::IsEmpty();
    }

    virtual void pushBefore(const T& data, const T& place) override {
        TList<T>::pushBefore(data, place);
        pHead->pNext = pFirst;
        return;
    }

    virtual void pushAfter(const T& data, const T& place) {
        TList<T>::pushAfter(data, place);
        pHead->pNext = pFirst;
        return;
    }

    virtual int size() const override {
        return TList<T>::size() + 1;
    }
};