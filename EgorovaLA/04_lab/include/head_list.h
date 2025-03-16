#pragma once

#include "list.h"

using namespace std;

template <typename T>
class THeadList : public TList<T> {
protected:
	TNode<T>* pHead;
public:
    THeadList() :TList(), pHead(nullptr){}

    THeadList(const T& data): TList(data), pHead(nullptr) { 
        if (pHead == nullptr) pHead = new TNode<T>();
        pHead->pNext = pFirst;
        if (pFirst == nullptr) pStop = pHead;
        reset();
    }

    THeadList(const THeadList<T>& list) :TList(list) {
        if (list.pHead == nullptr) {
            pHead = nullptr;
            return;
        }
        pHead = new TNode<T>(list.pHead->Data);
        pHead->pNext = pFirst;
    }

    ~THeadList() {
        if (pHead!= nullptr) delete pHead;
    }

    const THeadList<T>& operator=(const THeadList& list) {
        if (this == &list) {
            return *this;
        }

        if (pHead == nullptr) pHead = new TNode<T>(list.pHead->Data);
        else {
            pHead->Data = list.pHead->Data;
        }

        TList<T>::operator=(list);

        pHead->pNext = pFirst;

        return *this;
    }

    bool operator==(const THeadList<T>& list) const {
        if (pHead->Data != list.pHead->Data) return 0;
        return (TList<T>::operator==(list));
    }

    virtual void pushFront(const T& data) override {
        TList<T>::pushFront(data);
        if (pHead == nullptr) pHead = new TNode<T>();
        pHead->pNext = pFirst;
        return;
    }

   virtual void pushBack(const T& data) override {
       TList<T>::pushBack(data);
       if (pHead == nullptr) pHead = new TNode<T>();
       pHead->pNext = pFirst;
       return;
    }

   virtual void PopBack() override {
       TList<T>::PopBack();
       if (pHead == nullptr) pHead = new TNode<T>();
       pHead->pNext = pFirst;
       return;
   }

   virtual void PopFront() override {
       TList<T>::PopFront();
       if (pHead == nullptr) pHead = new TNode<T>();
       pHead->pNext = pFirst;
       return;
   }

   virtual bool IsEmpty() const override {
       return (TList<T>::IsEmpty());
   }

   TNode<T>* getHead() const {
       return pHead;
   }

   virtual void pushBefore(const T& data, const T& place) override {
       TList<T>::pushBefore(data, place);
       if (pHead == nullptr) pHead = new TNode<T>();
       pHead->pNext = pFirst;
       return;
   }

   virtual void pushAfter(const T& data, const T& place) {
       TList<T>::pushAfter(data, place);
       if (pHead == nullptr) pHead = new TNode<T>();
       pHead->pNext = pFirst;
       return;
   }

   virtual int size() const override{
       return TList<T>::size() + 1;
   }

   void setPHead(const T& data) {
       pHead = new TNode<T>(data);
       pHead->pNext = pFirst;
   }
};
