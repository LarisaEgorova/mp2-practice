#pragma once

#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct TNode {
    T Data; //будет содержать моном
    TNode<T>* pNext;

    TNode() : Data(), pNext(nullptr) {}
    TNode(const T& data) : Data(data), pNext(nullptr) {}
};

template <typename T>//обновленный TList
class TList {
protected:
    TNode<T>* pFirst;
    TNode<T>* pCurr;
    TNode<T>* pPrev;
    TNode<T>* pLast;//в данном контексте указывает на последний узел
    TNode<T>* pStop;//следующий после pLast
public:
    TList() : pFirst(nullptr), pCurr(nullptr), pPrev(nullptr), pStop(nullptr), pLast(nullptr) {}

    TList(const T& data) :TList<T>() {
        pFirst = new TNode<T>(data);
        reset();
        pLast = pFirst;
    }

    TList(const TList<T>& list) : TList<T>() {        
        copy(list);
    }

    virtual ~TList() {        
        clear();
    }

    void copy(const TList<T>& list)
    {
        if (list.pFirst == nullptr) {
            pFirst = nullptr;
            return;
        }
        pFirst = new TNode<T>(list.pFirst->Data);
        pCurr = pFirst;
        TNode<T>* listcurr = list.pFirst->pNext;
        while (listcurr != list.pStop) {            
            pCurr->pNext = new TNode<T>(listcurr->Data);
            pCurr = pCurr->pNext;
            listcurr = listcurr->pNext;
        }
        pLast = pCurr;
        pLast->pNext = pStop;
    }

    void clear() {
        reset();
        if (pCurr == nullptr) return;
        while (!IsEnded())
        {
            next();
            delete pPrev;
        }
        pFirst = nullptr;
        //pLast->pNext = pStop;
    }

    void next() {
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }

    virtual void reset() {
        pCurr = pFirst;
        pPrev = nullptr;
    }

    virtual bool IsEnded() const {
        return (pCurr == pStop);
    }

    const TList<T>& operator=(const TList& list) {
        if (this == &list) {
            return *this;
        }
        clear();
        copy(list);
        return *this;
    }

    bool operator==(const TList<T>& list) const {
        TNode<T>* curr = pFirst;
        TNode<T>* listcurr = list.pFirst;

        if (curr == nullptr && listcurr == nullptr) return true;

        while (curr != pStop && listcurr != list.pStop) {
            if (curr->Data != listcurr->Data) {
                return false;
            }
            curr = curr->pNext;
            listcurr = listcurr->pNext;
        }
        return (curr == pStop) && (listcurr == list.pStop);
    }

    virtual int size() const {
        TNode<T>* curr = pFirst;
        int n = 0;
        while (curr != pStop) {
            n++;
            curr = curr->pNext;
        }
        return n;
    }

    virtual void pushFront(const T& data) {
        if (pFirst == nullptr) {
            pFirst = new TNode<T>(data);
            pFirst->pNext = pStop;
            pLast = pFirst;
            return;
        }

        TNode<T>* node = new TNode<T>(data);
        node->pNext = pFirst;
        pFirst = node;
    }

    virtual void pushBack(const T& data) {
        if (pFirst == nullptr) {
            pushFront(data);
            return;
        }

        TNode<T>* node = new TNode<T>(data);
        node->pNext = pStop;
        pLast->pNext = node;
        pLast = node;
    }

    virtual void PopBack() {
        if (IsEmpty()) throw "List is empty";
        reset();
        while (pCurr != pLast) {
            next();
        }
        delete pCurr;
        pPrev->pNext = pStop;
        pLast = pPrev;
    }

    virtual void PopFront() {
        if (IsEmpty()) throw "List is empty";
        reset();
        next();
        delete pPrev;
        pFirst = pCurr;
        if (pCurr == pStop) {
            pFirst = pLast = nullptr;
            pPrev = pCurr = nullptr;
        }        
    }

    virtual void PopCurr() {
        if (IsEmpty()) throw "List is empty";
        if (pCurr == pFirst) {
            PopFront();
            return;
        }
        if (pCurr == pLast) {
            PopBack();
            return;
        }
        TNode<T>* tmp = pCurr;
        reset();
        while (pCurr != tmp) next();
        tmp = tmp->pNext;
        pPrev->pNext = tmp;
        delete pCurr;
    }

    virtual bool IsEmpty() const {
        return pFirst == nullptr;
    }

    TNode<T>* getPFirst() const {
        return pFirst;
    }

    TNode<T>* getPCurr() const {
        return pCurr;
    }

    TNode<T>* find_elem(const T& key) { //по первому вхождению
        pPrev = nullptr;
        pCurr = pFirst;
        while (pCurr != pStop) {
            if (pCurr->Data == key) return pCurr;
            pPrev = pCurr;
            pCurr = pCurr->pNext;
        }
        return nullptr;
    }

    virtual void pushBefore(const T& data, const T& place) {
        find_elem(place);
        if (pCurr == nullptr) throw "Not found key";

        TNode<T>* node = new TNode<T>(data);

        if (pCurr == pFirst) {
            pushFront(data);
            return;
        }
        pPrev->pNext = node;
        node->pNext = pCurr;
        return;
    }

    virtual void pushAfter(const T& data, const T& place) {
        find_elem(place);
        if (pCurr == nullptr) throw "Not found key";

        if (pCurr == pLast) {
            pushBack(data);
            return;
        }

        TNode<T>* node = new TNode<T>(data);
        node->pNext = pCurr->pNext;
        pCurr->pNext = node;
    }
};
