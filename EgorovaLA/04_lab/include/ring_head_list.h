#pragma once

#include "head_list.h"

using namespace std;

template <typename T>
class TRingHeadList :public THeadList<T> {
public:
    TRingHeadList() :THeadList<T>() {        
        pStop = pHead;
        pHead->pNext = pStop;        
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
        if (pFirst == nullptr) {
            pLast = pHead;
        }
        pLast->pNext = pHead;
        pStop = pHead;
        return *this;
    }

    virtual void pushFront(const T& data) override {
        THeadList<T>::pushFront(data);
        pLast->pNext = pStop;
        return;
    }

    virtual void pushBack(const T& data) override {
        THeadList<T>::pushBack(data);
        pLast->pNext = pStop;
        return;
    }

    virtual void PopBack() override {
        THeadList<T>::PopBack();
        pLast->pNext = pStop;
        return;
    }

    virtual void PopFront() override {
        THeadList<T>::PopFront();
        if (pFirst == nullptr) {
            pHead->pNext = pStop;
        }
        return;
    }

    virtual void PopCurr() {
        THeadList<T>::PopCurr();
        if (pFirst == nullptr) {
            pHead->pNext = pStop;
            pLast = pHead;
        }
        pLast->pNext = pStop;
        return;
    }

    virtual void pushAfter(const T& data, const T& place) {
        THeadList<T>::pushAfter(data, place);
        pLast->pNext = pStop;
        return;
    }
};