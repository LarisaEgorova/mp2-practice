#pragma once

#include "head_list.h"

using namespace std;

template <typename T>
class TRingHeadList :public THeadList<T> {
public:
    TRingHeadList() :THeadList() {}

    TRingHeadList(const T& data) : THeadList(data) {
        if (pStop != nullptr) pStop->pNext = pHead;
    }

    TRingHeadList(const TRingHeadList<T>& list) :THeadList(list) {
        if (pStop != nullptr) pStop->pNext = pHead;
    }

    ~TRingHeadList() {
        if ((pStop != nullptr) && (pStop->pNext != nullptr)) delete pStop->pNext;
        pHead = nullptr;
    }

    const TRingHeadList<T>& operator=(const TRingHeadList& list) {
        THeadList<T>::operator=(list);
        if (pStop != nullptr) pStop->pNext = pHead;
        return *this;
    }

    bool operator==(const TRingHeadList<T>& list) const {
        if ((pStop->pNext->Data)!=(list.getPStop()->pNext->Data)) return 0;
        return (THeadList<T>::operator==(list));
    }

    virtual void pushFront(const T& data) override {
        THeadList<T>::pushFront(data);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void pushBack(const T& data) override {
        THeadList<T>::pushBack(data);
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

    virtual void pushBefore(const T& data, const T& place) override {
        THeadList<T>::pushBefore(data, place);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void pushAfter(const T& data, const T& place) {
        THeadList<T>::pushAfter(data, place);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void reset() override {//пригодится в кольцевых списках
        THeadList<T>::reset();
        return;
    }

    virtual void setHead(const T& data) override {
        THeadList::setHead(data);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }
};