#pragma once

#include "ring_head_list.h"


template <typename T>
class Monom{
private:
	T consts;
	int key;
public:
	Monom() : key(0), consts(1) {}
	Monom(const int Key, const T& Consts):consts(Consts) {
        if ((Key<0)||(Key>999)) throw "No correct key";
        key = Key;
    }
	Monom(const Monom<T>& monom) :key(monom.key), consts(monom.consts) {}

    const Monom<T>& operator=(const Monom<T>& monom) {
        if (this != &monom) { 
            consts = monom.consts;
            key = monom.key;
        }
        return *this;
    }

    bool operator==(const Monom<T>& monom) const {
        return ((key == monom.key) && (consts == monom.consts));
    }

    bool operator!=(const Monom<T>& monom) const {
        return (!(Monom<T>::operator==(monom)));
    }

    bool operator <(const Monom<T>& monom) const {//проверка по ключу
        return (key < monom.key);
    }

    bool operator >(const Monom<T>& monom) const {
        return (key > monom.key);
    }

    Monom<T> operator +(const Monom<T>& monom)const {
        if (key != monom.key) throw "Can't sum";
        T c = consts + monom.consts;
        return Monom(key, c);
    }

    Monom<T> operator -(const Monom<T>& monom)const {
        if (key != monom.key) throw "Can't sum";
        T c = consts - monom.consts;
        return Monom(key, c);
    }

    Monom<T> operator *(const Monom<T>& monom) const{
        if ((key+monom.key)>999) throw "Big key";
        int k =key + monom.key;
        T c = consts * monom.consts;
        return Monom(k, c);
    }

    //только для узлов с одинаковым ключом
    Monom<T> operator+(const T& value) const {
        int c = consts + value;
        return Monom(key, c);
    }
    //только для узлов с одинаковым ключом
    Monom<T> operator-(const T& value) const {
        int c = consts - value;
        return Monom(key, c);
    }

    Monom<T> operator*(const T& value) const{
        int c = consts * value;
        return Monom(key, c);
    }

    T GetConsts() {
        return this->consts;
    }

    int GetKey() {
        return this->key;
    }

    void setKey(const int Key) {
        key = Key;
    }

    void setConsts(const T& Consts) {
        consts = Consts;
    }
};

template <typename T>
class Polinom {
protected:
    TRingHeadList<T> polinom;
public:
    Polinom() {}

    Polinom(const TRingHeadList<T>& list) {//создание упорядоченного полинома из цикл. списка

        if (list.IsEmpty()) return;

        polinom.setPHead(list.getHead()->Data);

        TNode<T>* listcurr = list.getPFirst();

        if (listcurr != nullptr) polinom.pushBack(listcurr->Data);

        polinom.reset();

        while (listcurr != list.getPStop())
        {
            if (listcurr->Data < polinom.getPCurr()->Data)
                polinom.pushAfter(listcurr->Data, polinom.getPCurr()->Data);
            else if (listcurr->Data > polinom.getPCurr()->Data)
                polinom.pushBefore(listcurr->Data, polinom.getPCurr()->Data);
            else
                polinom.getPCurr()->Data = polinom.getPCurr()->Data + listcurr->Data;
            polinom.next();
            listcurr = listcurr->pNext;
        }
    }

    //Polinom(const string& str): polinom(str) {}

    Polinom(const Polinom<T>& pol) :polinom(pol.polinom) {}

    TRingHeadList<T> getPolinom() const {
        return polinom;
    }

    bool operator==(const Polinom<T>& P) const {
        return (polinom == P.polinom);
    }

    const Polinom<T>& operator=(const Polinom<T>& pol) {
        if (this != &pol) {
            polinom = pol.polinom;
        }
        return *this;
    }

    Polinom<T> operator +(const Polinom<T>& pol) const {
        Polinom<T> result(*this);
        result.polinom.getHead()->Data =
            result.polinom.getHead()->Data + pol.polinom.getHead()->Data;

        result.polinom.reset();

        TNode<T>* listcurr = pol.polinom.getPFirst();

        while (listcurr != pol.polinom.getPStop()->pNext)
        {
            result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data + listcurr->Data;
            result.polinom.next();
            listcurr = listcurr->pNext;
        }

        return result;
    }

    Polinom<T> operator -(const Polinom<T>& pol)const {
        Polinom<T> result(*this);
        result.polinom.getHead()->Data =
            result.polinom.getHead()->Data - pol.polinom.getHead()->Data;

        result.polinom.reset();

        TNode<T>* listcurr = pol.polinom.getPFirst();

        while (listcurr != pol.polinom.getPStop()->pNext)
        {
            result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data - listcurr->Data;
            result.polinom.next();
            listcurr = listcurr->pNext;
        }

        return result;
    }

    Polinom<T> operator *(const Polinom<T>& pol) const {
        Polinom<T> result(*this);
        result.polinom.getHead()->Data =
            result.polinom.getHead()->Data * pol.polinom.getHead()->Data;

        result.polinom.reset();

        TNode<T>* listcurr = pol.polinom.getPFirst();

        while (listcurr != pol.polinom.getPStop()->pNext)
        {
            result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data * listcurr->Data;
            result.polinom.next();
            listcurr = listcurr->pNext;
        }

        return result;
    }


    Polinom<T> operator+(const T& value) const {
        Polinom<T> result(*this);
        result.polinom.getHead()->Data = result.polinom.getHead()->Data + value;
        return result;
    }

    Polinom<T> operator-(const T& value) const {
        Polinom<T> result(*this);
        result.polinom.getHead()->Data = result.polinom.getHead()->Data - value;
        return result;
    }

    Polinom<T> operator*(const T& value) const {
        Polinom<T> result(*this);
        result.polinom.getHead()->Data = result.polinom.getHead()->Data * value;
        result.polinom.reset();

        while (result.polinom.getPCurr() != result.polinom.getPStop()->pNext)
        {
            result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data * value;
            result.polinom.next();
        }

        return result;
    }
};