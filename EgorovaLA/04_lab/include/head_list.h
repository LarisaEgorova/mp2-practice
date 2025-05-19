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
    }

    THeadList(const T& data) : TList(data) {
        pHead = new TNode<T>();
        pHead->pNext = pFirst;
    }

    THeadList(const THeadList<T>& list) :TList(list) {
        pHead = new TNode<T>();
        pHead->pNext = pFirst;
        if (pLast == nullptr) pLast = pHead;
    }
    virtual ~THeadList() {
        delete pHead;
    }

    const THeadList<T>& operator=(const THeadList& list) {
        TList<T>::operator=(list);
        pHead->pNext = pFirst;
        return *this;
    }

    virtual void pushFront(const T& data) override {
        TList<T>::pushFront(data);
        pHead->pNext = pFirst;
        return;
    }

    virtual void PopFront() override {
        TList<T>::PopFront();
        pHead->pNext = pFirst;
        return;
    }

    virtual void PopCurr() {
        TList<T>::PopCurr();
        pHead->pNext = pFirst;
        return;
    }

    virtual void pushBefore(const T& data, const T& place) override {
        TList<T>::pushBefore(data, place);
        pHead->pNext = pFirst;
        return;
    }
};