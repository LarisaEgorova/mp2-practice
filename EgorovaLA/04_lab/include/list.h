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
    TNode<T>* pStop;//в данном контексте указывает на последний узел
public:
    TList() : pFirst(nullptr), pCurr(nullptr), pPrev(nullptr), pStop(nullptr) {}

    TList(const T& data) :pPrev(nullptr) {
        pFirst = new TNode<T>(data);
        reset();
        pStop = pFirst;
    }

    TList(const TList<T>& list) : TList<T>() {
        if (list.pFirst == nullptr) {
            pFirst = nullptr;
            return;
        }

        pFirst = new TNode<T>(list.pFirst->Data);
        reset();
        pStop = pFirst;

        TNode<T>* listcurr = list.pFirst;

        while (listcurr != list.pStop) {
            listcurr = listcurr->pNext;
            next();
            pCurr = new TNode<T>(listcurr->Data);
            pStop = pCurr;
            pPrev->pNext = pCurr;
        }
        reset();
    }

    ~TList() {
        reset();
        if (pFirst == nullptr) {
            pStop = nullptr;
            return;
        }
        if (IsEnded()) {
            if (pFirst != nullptr) delete pFirst;
        }
        while (!IsEnded())
        {
            next();
            delete pFirst;
            pFirst = pCurr;
        }
        pFirst = nullptr;
    }

    const TList<T>& operator=(const TList& list) {
        if (this == &list) {
            return *this;
        }

        this->~TList();

        if (list.IsEmpty()) return *this;

        TNode<T>* listcurr = list.pFirst;
        if (list.pFirst == nullptr) return *this;
        while (listcurr != list.pStop->pNext) {
            pushBack(listcurr->Data);
            listcurr = listcurr->pNext;
        }
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
        TNode<T>* curr = pFirst;//не использую pCurr т.к. метод константный
        int n = 0;
        while (curr != pStop) {
            n++;
            curr = curr->pNext;
        }
        return n + 1;
    }

    virtual void pushFront(const T& data) {
        TNode<T>* node = new TNode<T>(data);
        if (pFirst == nullptr) {
            pFirst = node;
            pStop = pFirst;
            return;
        }
        if (node == nullptr) {
            throw "node is empty";
        }
        node->pNext = pFirst;
        pFirst = node;
    }

    virtual void pushBack(const T& data) {
        TNode<T>* node = new TNode<T>(data);
        if (pFirst == nullptr) {
            pFirst = node;
            pStop = pFirst;
            return;
        }
        if (node == nullptr) return;

        pStop->pNext = node;
        pStop = node;
    }

    virtual void PopBack() {
        if (IsEmpty()) throw "List is empty";
        reset();
        if (IsEnded()) {
            delete pFirst;
            pFirst = nullptr;
            pStop = nullptr;
            return;
        }
        while (!IsEnded()) {
            next();
        }
        delete pCurr;
        pPrev->pNext = nullptr;
        pStop = pPrev;
    }

    virtual void PopFront() {
        if (IsEmpty()) throw "List is empty";
        reset();
        if (IsEnded()) {
            delete pFirst;
            pFirst = nullptr;
            pStop = nullptr;
            return;
        }
        next();
        delete pPrev;
        pFirst = pCurr;
    }

    virtual bool IsEmpty() const {
        return pStop == nullptr;
    }

    TNode<T>* getPFirst() const {
        return pFirst;
    }

    TNode<T>* getPStop() const {
        return pStop;
    }

    TNode<T>* getPPrev() const {
        return pPrev;
    }

    TNode<T>* getPCurr() const {
        return pCurr;
    }

    void setPFirst(const T& data) {
        pFirst = new TNode<T>(data);
    }

    void setPStop(TNode<T>* node) {
        pStop = node;
    }

    void setPCurr(TNode<T>* node) {
        pCurr = node;
    }

    void next() {
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }

    virtual void reset() {//пригодится в кольцевых списках
        pCurr = pFirst;
        pPrev = nullptr;
    }

    bool IsEnded() {
        return(pCurr == pStop);
    }

    bool find_elem(const T& key) { //по первому вхождению
        reset(); 
        if (pCurr->Data == key) return 1;
        while (!IsEnded()) {
            if (pCurr->Data == key) return 1;
            next();
        }
        return 0;
    }

    virtual void pushBefore(const T& data, const T& place) {
        if (!find_elem(place)) throw "Not found key";

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
        find_elem(place);
        if (pCurr == nullptr) throw "Not found key";

        TNode<T>* node = new TNode<T>(data);
        next();

        pPrev->pNext = node;
        node->pNext = pCurr;
        pStop = pStop->pNext;
    }

    const T getData(const T& key) {
        find_elem(key);
        return pCurr->Data;
    }

    const int getKey() {
        find_elem(Data);
        return pCurr->Data;
    }
};
