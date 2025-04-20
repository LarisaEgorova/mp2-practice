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
        if (list.pFirst == nullptr) {
            pFirst = nullptr;
            return;
        }
        copy(list);
    }

    ~TList() {
        if (pFirst == nullptr) {
            pStop = nullptr;
            return;
        }
        clear();
    }


    void copy(const TList<T>& list)
    {
        pFirst = new TNode<T>(list.pFirst->Data);

        TNode<T>* listcurr = list.pFirst->pNext;

        reset();
        while (listcurr != list.pStop) {
            next();
            pCurr = new TNode<T>(listcurr->Data);
            pPrev->pNext = pCurr;
            listcurr = listcurr->pNext;
        }
        pLast = pCurr;
    }

    void clear() {
        reset();
        if (pCurr == nullptr) return;
        while (!IsEnded())
        {
            next();
            delete pPrev;
            pPrev = pCurr;
        }
        pFirst = nullptr;
    }

    void next() {
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }

    virtual void reset() {
        pCurr = pFirst;
        pPrev = nullptr;
    }

    bool IsEnded() {
        return(pCurr == pStop);
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

        while (listcurr != list.pStop) {
            if (curr->Data != listcurr->Data) {
                return 0;
            }
            curr = curr->pNext;
            listcurr = listcurr->pNext;
        }
        return 1;
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
            *this = TList<T>(data);
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
        pPrev->pNext = nullptr;
        pLast = pPrev;
    }

    virtual void PopFront() {
        if (IsEmpty()) throw "List is empty";
        reset();
        next();
        delete pPrev;
        pFirst = pCurr;
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

    TNode<T>* getPStop() const {
        return pStop;
    }

    void setPFirst(const T& data) {
        pFirst = new TNode<T>(data);
    }

    TNode<T>* find_elem(const T& key) const { //по первому вхождению
        TNode<T>* curr = pFirst;
        while (curr != pStop) {
            if (curr->Data == key) return curr;
            curr = curr->pNext;
        }
        return nullptr;
    }

    virtual void pushBefore(const T& data, const T& place) {
        pCurr = find_elem(place);
        if (pCurr == nullptr) throw "Not found key";

        TNode<T>* node = new TNode<T>(data);

        if (pCurr == pFirst) {
            pFirst = node;
            pFirst->pNext = pCurr;
            return;
        }
        pPrev->pNext = node;
        node->pNext = pCurr;
        return;
    }

    virtual void pushAfter(const T& data, const T& place) {
        pCurr = find_elem(place);
        if (pCurr == nullptr) throw "Not found key";

        TNode<T>* node = new TNode<T>(data);
        next();

        pPrev->pNext = node;
        node->pNext = pCurr;
        if (pLast == pPrev) pLast = node;
    }
};
