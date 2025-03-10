#pragma once

#include "head_list.h"

using namespace std;

template <typename T>
class TRingHeadList:public THeadList<T>  {
public:
    TRingHeadList() :THeadList() {}

    TRingHeadList(const T& data, const int key) : THeadList(data, key) {
        if (pStop!=nullptr) pStop->pNext = pHead;
    }

    TRingHeadList(const THeadList<T>& list) :THeadList(list) {
        if (pStop != nullptr) pStop->pNext = pHead;
    }

    ~TRingHeadList() {
        if ((pStop!= nullptr)&&(pStop->pNext!=nullptr)) delete pStop->pNext;
        pHead = nullptr;
    }

    const TRingHeadList<T>& operator=(const TRingHeadList& list) {
        THeadList<T>::operator=(list);
        if (pStop != nullptr) pStop->pNext = pHead;
        return *this;
    }

    bool operator==(const TRingHeadList<T>& list) const {
        if ((list.pStop->pNext != list.pHead) && (pHead == pStop) ||
            (list.pStop->pNext == list.pHead) && (pHead != pStop)) return 0;
        return (THeadList<T>::operator==(list));
    }

    virtual void pushFront(const T& data, const int key) override {
        THeadList<T>::pushFront(data, key);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void pushBack(const T& data, const int key) override {
        THeadList<T>::pushBack(data, key);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void PopBack() override {
        THeadList<T>::PopBack();
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void PopFront() override {
        THeadList<T>::PopFront();
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void pushBefore(const T& data, const int key, const int place) override {
        THeadList<T>::pushBefore(data, key, place);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void pushAfter(const T& data, const int key, const int place) {
        THeadList<T>::pushAfter(data, key, place);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }
};