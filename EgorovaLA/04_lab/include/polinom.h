#pragma once

#include "ring_head_list.h"

class Monom {
private:
    double consts;
    int key;
public:
    Monom() : key(0), consts(0) {}

    Monom(const int Key, const double& Consts) :consts(Consts) {
        if ((Key < 0) || (Key > 999)) throw "No correct key";
        key = Key;
    }

    Monom(const Monom& monom) :key(monom.key), consts(monom.consts) {}

    Monom(const string& str) : Monom() {
        int strlen = str.size();
        for (int i = 0; i < strlen; i++) {
            if (str[i] == '-') {
                if (consts == 0) consts = -1;
                else consts *= -1;
                continue;
            }

            if ((str[i] == 'x') || (str[i] == 'X') || (str[i] == 'y') ||
                (str[i] == 'Y') || (str[i] == 'z') || (str[i] == 'Z') ||
                (str[i] == '*')) {
                if (consts == 0) consts = 1;
                continue;
            }

            if (str[i] == '^') {
                int j = i + 1;
                string tmp;
                while ((str[j] != '*') && (j < strlen)) {
                    if (j > strlen) throw "No correct enter";
                    tmp += str[j];
                    j++;
                }
                if ((stoi(tmp) > 9) || (stoi(tmp) < 0)) throw "Big degree";
                if ((str[i - 1] == 'x') || (str[i - 1] == 'X')) {
                    key += stoi(tmp) * 100;
                    i = j;
                    continue;
                }
                if ((str[i - 1] == 'y') || (str[i - 1] == 'Y')) {
                    key += stoi(tmp) * 10;
                    i = j;
                    continue;
                }
                if ((str[i - 1] == 'z') || (str[i - 1] == 'Z')) {
                    key += stoi(tmp);
                    i = j;
                    continue;
                }
            }

            if (str[i] == '*') continue;

            if ((str[i] == '0') || (str[i] == '1') || (str[i] == '2') ||
                (str[i] == '3') || (str[i] == '4') || (str[i] == '5') ||
                (str[i] == '6') || (str[i] == '7') || (str[i] == '8') ||
                (str[i] == '9')) {

                string tmp;
                while ((str[i] != '*') && (i < strlen)) {
                    if (i > strlen) throw "No correct enter";
                    tmp += str[i];
                    i++;
                }
                if ((key==0)&&(consts==0)) consts+= stod(tmp);
                else consts *= stod(tmp);
                continue;
            }
        }
    }

    const Monom& operator=(const Monom& monom) {
        if (this != &monom) {
            consts = monom.consts;
            key = monom.key;
        }
        return *this;
    }

    bool operator==(const Monom& monom) const {
        return ((key == monom.key) && (consts == monom.consts));
    }

    bool operator!=(const Monom& monom) const {
        return (!(Monom::operator==(monom)));
    }

    bool operator <(const Monom& monom) const {//проверка по ключу
        return (key < monom.key);
    }

    bool operator >(const Monom& monom) const {
        return (key > monom.key);
    }

    Monom operator +(const Monom& monom)const {
        if (key != monom.key) throw "Can't sum";
        double c = consts + monom.consts;
        return Monom(key, c);
    }

    Monom operator +=(const Monom& monom)  {
        return *this = *this  + monom;
    }

    Monom operator -(const Monom& monom)const {
        if (key != monom.key) throw "Can't sum";
        double c = consts - monom.consts;
        return Monom(key, c);
    }

    Monom operator -=(const Monom& monom) {
        return *this = *this - monom;
    }

    Monom operator *(const Monom& monom) const {
        if ((key + monom.key) > 999) throw "Big key";
        int k = key + monom.key;
        double c = consts * monom.consts;
        return Monom(k, c);
    }

    Monom operator *=(const Monom& monom) {
        return *this = *this * monom;
    }

    double GetConsts() const {
        return this->consts;
    }

    int GetKey() const {
        return this->key;
    }

    void setKey(const int Key) {
        key = Key;
    }

    void setConsts(const double Consts) {
        consts = Consts;
    }

    double Monom::operator()(double x, double y, double z) const
    {
        double res = 0.0;
        res = consts * pow(x, (key / 100)) * pow(y, ((key / 10) % 10)) * pow(z, (key % 10));
        return res;
    }

    friend ostream& operator << (ostream& out, Monom& m) {
        if ((m.consts != 0) && (m.consts != 1)) {
            if (m.consts < 0) out << "(" << m.consts << ")";
            else out << m.consts<< "*";

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
    Polinom() {}
    Polinom(const TRingHeadList<Monom>& list) : polinom(list) {}
    Polinom(const Monom& monom) : polinom() {
        polinom.pushFront(monom);
    }
    Polinom(const string& str) : polinom() {
        int strlen = str.size();
        string tmp;
        for (int i = 0; i < strlen; i++) {
            if (str[i] == '-') {
                tmp += str[i];
                i++;
            }
            while ((str[i] != '-') && (str[i] != '+') && (i < strlen)) {
                if ((str[i] == '*') && (str[i + 1] == '-')) {
                    tmp += str[i];
                    i++;
                }
                tmp += str[i];
                i++;
            }
            Monom m(tmp);
            insert_monom(m);
            tmp.clear();
            if (str[i]=='-') tmp += str[i];
        }
    }

    Polinom(const Polinom& pol) :polinom(pol.polinom) {}

    TRingHeadList<Monom> getPolinom() const {
        return polinom;
    }

    bool operator==(const Polinom& P) const {
        return (polinom == P.polinom);
    }

    const Polinom& operator=(const Polinom& pol) {
        if (this != &pol) {
            polinom = pol.polinom;
        }
        return *this;
    }

    void insert_monom(const Monom& data) {
        polinom.reset();
        if (polinom.IsEmpty()) {
            polinom.pushBack(data);
            return;
        }
        while (!polinom.IsEnded()) {
            if (data > polinom.getPCurr()->Data) {
                polinom.pushBefore(data, polinom.getPCurr()->Data);
                return;
            }
            if (data.GetKey() == polinom.getPCurr()->Data.GetKey()) {
                polinom.getPCurr()->Data += data;
                return;
            }
            polinom.next();
        }
        polinom.pushBack(data);
    }

    //This polinoms

   Polinom operator +(const Polinom& pol) const {
        Polinom result(*this);
        Polinom copypol = pol;

        copypol.polinom.reset();

        while (!copypol.polinom.IsEnded())
        {
            result.insert_monom(copypol.polinom.getPCurr()->Data);
            copypol.polinom.next();
        }
        return result;
    }

    Polinom operator -(const Polinom& pol) const {
        Polinom result(*this);
        Polinom copypol = pol;

        copypol.polinom.reset();

        while (!copypol.polinom.IsEnded())
        {
            Monom mcopy(copypol.polinom.getPCurr()->Data.GetKey(),
                -copypol.polinom.getPCurr()->Data.GetConsts());
            result.insert_monom(mcopy);
            copypol.polinom.next();
        }
        return result;
    }

    Polinom operator *(const Polinom& pol) const {
        Polinom result;
        Polinom copypol(pol);
        Polinom copythis(*this);

        copythis.polinom.reset();
        copypol.polinom.reset();

        while (!copythis.polinom.IsEnded()) {
            if (copythis.polinom.getPCurr()->Data.GetConsts() != 0) {
                while (!copypol.polinom.IsEnded()) {
                    Monom m = copythis.polinom.getPCurr()->Data 
                        * copypol.polinom.getPCurr()->Data;
                    result.insert_monom(m);
                    copypol.polinom.next();
                }
                copythis.polinom.next();
            }
            else result.polinom.next();
        }

        return result;
    }

    //This monoms or consts

   Polinom operator +(const Monom& monom) const {
       Polinom result(*this);
       Polinom mon(monom);
       result = result + mon;
       return result;
    }

    Polinom operator -(const Monom& monom) const {
        Polinom result(*this);
        Polinom mon(monom);
        result = result - mon;
        return result;
    }

    Polinom operator *(const Monom& monom)  {
        Polinom result(*this);
        Polinom mon(monom);
        result = result * mon;
        return result;
    }

    friend istream& operator >> (istream& in, Polinom& p) {
        string str;
        in >> str;
        Polinom p1(str);
        p = p1;
        return in;
    }

    friend ostream& operator << (ostream& out, Polinom& p) {
        p.polinom.reset();
        while (!p.polinom.IsEnded()) {
            out << p.polinom.getPCurr()->Data;
            if ((p.polinom.getPCurr() -> pNext != p.polinom.getPStop())&&
                (p.polinom.getPCurr()->pNext->Data.GetConsts()!=0)) out << "+";
            p.polinom.next();
        }
        out << "\n";
        return out;
    }

    double Polinom::operator() (double x, double y, double z) {
        double res = 0.0;
        polinom.reset();
        while (!polinom.IsEnded()) {
            res += polinom.getPCurr()->Data(x, y, z);
            polinom.next();
        }
        return res;
    }
};
