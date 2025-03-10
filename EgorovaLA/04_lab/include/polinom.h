#pragma once

#include "head_list.h"
#include "postfix_form.h"


template <typename T>
class Monom{
private:
	T consts;
	int key;
public:
	Monom() : key(0), consts(0) {}
	Monom(const int Key, const T Consts):key(Key), consts(Consts) {}
	Monom(const Monom<T>& monom) :key(monom.key), consts(monom.consts) {}

    const Monom<T>& operator=(const Monom<T>& monom) {
        if (this != &monom) { 
            consts = monom.consts;
            key = monom.key;
        }
        return *this;
    }

    bool operator==(const Monom<T>& list) const {
        return ((key == list.key) && (consts == list.consts));
    }

    Monom operator +(const Monom& monom) {
        if (key != monom.key) throw "Can't sum";
        consts += monom.consts;
        return *this;
    }

    Monom operator -(const Monom& monom) {
        if (key != monom.key) throw "Can't sum";
        consts -= monom.consts;
        return *this;
    }

    Monom operator *(const Monom& monom) {
        key += monom.key;
        consts *= monom.consts;
        return *this;
    }

    //только для pHead
    Monom operator+(const T& value) const {
        return Monom(key, consts + value);
    }
    //только для pHead
    Monom operator-(const T& value) const {
        return Monom(key, consts - value);
    }

    Monom operator*(const T& value) const {
        return Monom(key, consts * value);
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

    void setConsts(const T Consts) {
        consts = Consts;
    }
};

template <typename T>
class Polinom {
private:
public:

};
