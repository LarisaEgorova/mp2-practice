#pragma once

#include "head_list.h"

using namespace std;

template <typename T>
class TRingHeadList :public THeadList<T> {
public:
    TRingHeadList() :THeadList<T>() {
        pLast = pHead;
        pHead->pNext = pLast;
        pStop = pHead;
    }

    TRingHeadList(const T& data) : THeadList<T>(data) {
        pLast->pNext = pHead;
        pStop = pHead;
    }

    TRingHeadList(const TRingHeadList<T>& list) :THeadList<T>(list) {
        pLast->pNext = pHead;
        pStop = pHead;
    }

    const TRingHeadList<T>& operator=(const TRingHeadList<T>& list) {
        THeadList<T>::operator=(list);
        pLast->pNext = pHead;
        pStop = pHead;
        return *this;
    }

    bool operator==(const TRingHeadList<T>& list) const {
        return (THeadList<T>::operator==(list));
    }

    virtual void pushFront(const T& data) override {
        THeadList<T>::pushFront(data);
        pLast->pNext = pHead;
        pStop = pHead;
        return;
    }

    virtual void pushBack(const T& data) override {
        THeadList<T>::pushBack(data);
        pLast->pNext = pHead;
        pStop = pHead;
        return;
    }

    virtual void PopBack() override {
        THeadList<T>::PopBack();
        pLast->pNext = pHead;
        pStop = pHead;
        return;
    }

    virtual void PopFront() override {
        THeadList<T>::PopFront();
        pLast->pNext = pHead;
        pStop = pHead;
        return;
    }

    virtual void pushBefore(const T& data, const T& place) override {
        THeadList<T>::pushBefore(data, place);
        pLast->pNext = pHead;
        pStop = pHead;
        return;
    }

    virtual void pushAfter(const T& data, const T& place) {
        THeadList<T>::pushAfter(data, place);
        pLast->pNext = pHead;
        pStop = pHead;
        return;
    }

};