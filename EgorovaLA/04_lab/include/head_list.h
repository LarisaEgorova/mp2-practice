#pragma once

#include "list.h"

using namespace std;

template <typename T>
class THeadList : public TList<T> {
protected:
	TNode<T>* pHead;
public:
    THeadList() :TList(), pHead(nullptr){}

    THeadList(const T& data, const int key): TList(data, key) {
        if (key > 999 || key <= 0) {
            if (pHead == nullptr) pHead = new TNode<T>(data, -1);
            else pHead->Data = data;
        }
        else {
            pHead = new TNode<T>(0, -1);
        }
        pHead->pNext = pFirst;
        reset();
    }

    THeadList(const THeadList<T>& list) :TList(list) {
        if (list.pHead == nullptr) {
            pHead = nullptr;
            return;
        }
        pHead = new TNode<T>(list.pHead->Data, list.pHead->Key);
        pHead->pNext = pFirst;
    }

    ~THeadList() {
        if (pHead!= nullptr) delete pHead;
    }

    const THeadList<T>& operator=(const THeadList& list) {
        if (this == &list) {
            return *this;
        }

        if (pHead==nullptr) pHead = new TNode<T>(list.pHead->Data, list.pHead->Key);
        else {
            pHead->Data = list.pHead->Data;
            pHead->Key = list.pHead->Key;
        }
        TList<T>::operator=(list);
        return *this;
    }

    bool operator==(const THeadList<T>& list) const {
        if ((pHead->Data != list.pHead->Data)&&(pHead->Key != list.pHead->Key)) return 0;
        return (TList<T>::operator==(list));
    }

    virtual void pushFront(const T& data, const int key) override {
        TList<T>::pushFront(data, key);
        if (pHead == nullptr) pHead = new TNode<T>(0, -1);
        pHead->pNext = pFirst;
        return;
    }

   virtual void pushBack(const T& data, const int key) override {
       TList<T>::pushBack(data, key);
       if (pHead == nullptr) pHead = new TNode<T>(0, -1);
       pHead->pNext = pFirst;
       return;
    }

   virtual void PopBack() override {
       TList<T>::PopBack();
       if (pHead == nullptr) pHead = new TNode<T>(0, -1);
       pHead->pNext = pFirst;
       return;
   }

   virtual void PopFront() override {
       TList<T>::PopFront();
       if (pHead == nullptr) pHead = new TNode<T>(0, -1);
       pHead->pNext = pFirst;
       return;
   }

   virtual bool IsEmpty() const override {
       return ((pFirst == nullptr)&&(pHead==nullptr));
   }

   TNode<T>* getHead() {
       return pHead;
   }

   virtual void pushBefore(const T& data, const int key, const int place) override {
       TList<T>::pushBefore(data, key, place);
       if (pHead == nullptr) pHead = new TNode<T>(0, -1);
       pHead->pNext = pFirst;
       return;
   }

   virtual void pushAfter(const T& data, const int key, const int place) {
       TList<T>::pushAfter(data, key, place);
       if (pHead == nullptr) pHead = new TNode<T>(0, -1);
       pHead->pNext = pFirst;
       return;
   }

   virtual int size() const override{
       return TList<T>::size() + 1;
   }
};
