#pragma once

#include "ring_head_list.h"

struct Monom {
    double consts;
    int key;

    Monom();

    Monom(const int Key, const double& Consts);

    Monom(const Monom& monom);

    Monom(const string& str);

    Monom& operator=(const Monom& monom);

    bool operator==(const Monom& monom) const;

    bool operator!=(const Monom& monom) const;

    bool operator <(const Monom& monom) const;

    bool operator >(const Monom& monom) const;

    Monom operator +(const Monom& monom)const;

    Monom& operator +=(const Monom& monom);

    Monom operator - (const Monom& monom)const;

    Monom& operator -=(const Monom& monom);

    Monom operator *(const Monom& monom) const;

    Monom& operator *=(const Monom& monom);

    Monom operator +(double C) const;

    Monom operator -(double C) const;

    Monom operator *(double C) const;


    double operator()(double x, double y, double z) const;

    friend ostream& operator << (ostream& out, Monom& m) {
        if (&m == nullptr) {
            out << "0";
            return out;
        }
        if ((m.consts != 0) && (m.consts != 1)) {
            if (m.consts < 0) out << "(" << m.consts << ")";
            else out << m.consts;

        }
        if (m.consts != 0) {
            if ((m.key / 100) != 0) {
                out << "x^" << m.key / 100;
                if (((m.key / 10) % 10 != 0) || ((m.key % 10) != 0)) out << "*";
            }
            if ((m.key / 10) % 10 != 0) {
                out << "y^" << (m.key / 10) % 10;
                if ((m.key % 10) != 0) out << "*";
            }
            if ((m.key % 10) != 0) out << "z^" << (m.key % 10);
        }
        return out;
    }
};


class Polinom {
private:
    TRingHeadList<Monom> polinom;
public:
    Polinom();
    Polinom(const Monom& monom);
    Polinom(const string& str);

    Polinom(const Polinom& pol);

    TRingHeadList<Monom> getPolinom() const;

    bool operator==(const Polinom& P) const;

    const Polinom& operator=(const Polinom& pol);

    void insert_monom(const Monom& data);

    //This polinoms

    Polinom operator +(const Polinom& pol) const;
    Polinom operator -(const Polinom& pol) const;
    Polinom operator *(const Polinom& pol) const;

    //This monoms
    Polinom operator +(const Monom& monom) const;
    Polinom operator -(const Monom& monom) const;
    Polinom operator *(const Monom& monom);

    //This consts

    Polinom operator +(double C) const;
    Polinom operator -(double C) const;
    Polinom operator *(double C);

    friend istream& operator >> (istream& in, Polinom& p) {
        string str;
        in >> str;
        Polinom p1(str);
        p = p1;
        return in;
    }

    friend ostream& operator << (ostream& out, Polinom& p) {
        p.polinom.reset();
        if (p.getPolinom().getPCurr() == nullptr) {
            out << "0\n";
            return out;
        }
        while (!p.polinom.IsEnded()) {
            out << p.polinom.getPCurr()->Data;
            if ((!p.polinom.IsEnded())&&
                (p.polinom.getPCurr()->pNext->Data.consts!=0)) out << "+";
            p.polinom.next();
        }
        out << "\n";
        return out;
    }

    double Polinom::operator() (double x, double y, double z);
};
