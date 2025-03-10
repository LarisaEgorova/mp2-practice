#pragma once// нет вставки до, вставки после, поиск элемента

#include <iostream>

using namespace std;

template <typename T>
struct TNode {
    T Data;
    TNode* pNext;
    int Key;

    TNode() : Data(-1), pNext(nullptr), key(0) {}
    TNode(const T& data) : Data(data), pNext(nullptr), Key(0) {}
    TNode(const T& data, const int key) : Data(data), pNext(nullptr), Key(key) {}
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

    TList(const T& data, const int key):pPrev(nullptr){
        pFirst = new TNode<T>(data, key);
        reset();
        pStop = pFirst;
    }

    TList(const TList<T>& list) : TList<T>() {
        if (list.pFirst == nullptr) {
            pFirst = nullptr;
            return;
        }

        pFirst = new TNode<T>(list.pFirst->Data, list.pFirst->Key);
        reset();
        pStop = pFirst;

        TNode<T>* listcurr = list.pFirst;

        while (listcurr != list.pStop) {
            next();
            pCurr = new TNode<T>(listcurr->Data, listcurr->Key);
            pStop = pCurr;
            listcurr = listcurr->pNext;
        }
        reset();
    }

    ~TList() {
        reset();
        if (IsEnded()) {
            if (pFirst!= nullptr) delete pFirst;
        }
        while (!IsEnded())
        {
            next();
            delete pFirst;
            pFirst = pCurr;
        }
    }

    const TList<T>& operator=(const TList& list) {
        if (this == &list) {
            return *this;
        }

        this->~TList();

        TNode<T>* listcurr = list.pFirst;

        while (listcurr != list.pStop) {
            pushFront(listcurr->Data, listcurr->Key);
            listcurr = listcurr->pNext;
        }
        return *this;
    }

    bool operator==(const TList<T>& list) const {
        if (size() != list.size()) return 0;
        TNode<T>* curr = pFirst;
        TNode<T>* listcurr = list.pFirst;
        while (listcurr!=list.pStop) {
            if ((curr->Data != listcurr->Data)||(curr->Key != listcurr->Key)) {
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
        return n+1;//+1 за pStop
    }

    virtual void pushFront(const T& data, const int key) {
        TNode<T>* node = new TNode<T>(data,key);
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
        pStop = pFirst->pNext;
    }

    virtual void pushBack(const T& data, const int key) {
        TNode<T>* node = new TNode<T>(data, key);
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
        pCurr = pFirst->pNext;
        pPrev = pFirst;
        delete pPrev;
        pFirst = pCurr;
    }

    virtual bool IsEmpty() const {
        return pFirst == nullptr;
    }

    TNode<T>* getPFirst() const {
        return pFirst;
    }

    void next() {
        pPrev = pCurr;
        pCurr = pCurr->pNext;
    }

    void reset() {//пригодится в кольцевых списках
        pCurr = pFirst;
        pPrev = nullptr;
    }
    bool IsEnded() {
        return(pCurr == pStop);
    }

    void find_elem(int key) {
        reset();
        if (pFirst->Key == key) return;
        while (!IsEnded()){
            if (pCurr->Key == key) return;
            next();
        }
        return;
    }

    virtual void pushBefore(const T& data, const int key, const int place) {
        find_elem(place);
        if (pCurr == nullptr) throw "Not found key";

        TNode<T>* node = new TNode<T>(data, key);
        if (pPrev == nullptr) {
            pFirst = node;
            pFirst->pNext = pCurr;
            return;
        }
        pPrev->pNext = node;
        node->pNext = pCurr;
        return;
    }

    virtual void pushAfter(const T& data, const int key, const int place) {
        find_elem(place);
        if (pCurr == nullptr) throw "Not found key";

        TNode<T>* node = new TNode<T>(data, key);
        next();

        pPrev->pNext = node;
        node->pNext = pCurr;
        pStop = pStop->pNext;
    }

    T getData(int key) {
        find_elem(key);
        return pCurr->Data;
    }
};
