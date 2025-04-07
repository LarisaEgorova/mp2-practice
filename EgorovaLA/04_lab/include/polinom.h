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
                if (consts==0) consts = 1;
                continue;
            }

            if (str[i] == '^') {
                int j = i+1;
                string tmp;
                while ((str[j] != '*')&&(j<strlen)) {
                    if (j > strlen) throw "No correct enter";
                    tmp += str[j];
                    j++;
                }
                if ((stoi(tmp) > 9) || (stoi(tmp) <0)) throw "Big degree";
                if ((str[i-1] == 'x') || (str[i-1] == 'X')){
                    key += stoi(tmp)*100;
                    i = j;
                    continue;
                }
                if ((str[i-1] == 'y') || (str[i-1] == 'Y')) {
                    key += stoi(tmp)*10;
                    i = j;
                    continue;
                }
                if ((str[i-1] == 'z') || (str[i-1] == 'Z')) {
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
                if (consts == 0) consts = consts + stod(tmp);
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

    Monom operator -(const Monom& monom)const {
        if (key != monom.key) throw "Can't sum";
        double c = consts - monom.consts;
        return Monom(key, c);
    }

    Monom operator *(const Monom& monom) const {
        if ((key + monom.key) > 999) throw "Big key";
        int k = key + monom.key;
        double c = consts * monom.consts;
        return Monom(k, c);
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

    double Monom::operator()(double x, double y, double z)const
    {
        double res = 0.0;
        res = consts * pow(x, (key / 100)) * pow(y, ((key / 10) % 10)) * pow(z, (key % 10));
        return res;
    }

    friend ostream& operator << (ostream& out, Monom& m) {
        if ((m.consts != 0) && (m.consts != 1)) {
            if (m.consts < 0) out << "(" << m.consts << ")";
            else out << m.consts;

        }
        if (m.consts != 0) {
            if ((m.key / 100) != 0) {
                out << "x^" << m.key / 100;
                if (((m.key / 10) % 10 != 0)||((m.key % 10) != 0)) out << "*";
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
        if (monom.GetKey() == 0) {
            polinom.setHead(monom);
            polinom.setPStop(polinom.getHead());
        }
        else polinom.pushFront(monom);
    }
    Polinom(const string& str) : polinom() {//добавить по повторы
        int strlen = str.size();
        for (int i = 0; i < strlen; i++) {
            string tmp;
            if (str[i] == '-') {
                tmp += str[i];
                i++;
                while ((str[i] != '-') && (str[i] != '+') && (i < strlen)) {
                    if ((str[i] == '(') || (str[i] == ')')) {
                        i++;
                        tmp += str[i];
                        i++;
                    }
                    tmp += str[i];
                    i++;
                }
                Monom m(tmp);
                if (m.GetKey() != 0) polinom.pushBack(m);
                else polinom.setHead(m);
                tmp.clear();
                continue;
            }
            while ((str[i] != '-') && (str[i] != '+') && (i < strlen)) {
                if (str[i] == '(') {
                    i++;//обязательно -
                    tmp += str[i];
                    i++;
                }
                if (str[i] == ')') {
                    i++;
                    continue;
                }
                tmp += str[i];
                i++;
            }
            Monom m(tmp);
            if (find_monom(m.GetKey())) polinom.getPCurr()->Data = polinom.getPCurr()->Data + m;
            else if (m.GetKey() != 0) polinom.pushBack(m);
            else polinom.setHead(m);
            if (str[i] == '-') i -= 1;
            tmp.clear();
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

    bool find_monom(const int key) {
        polinom.setPCurr(polinom.getHead());
        if (polinom.getPCurr() == nullptr) return 0;
        if (polinom.getPCurr()->Data.GetKey() == key) return 1;
        while (!polinom.IsEnded()) {
            if (polinom.getPCurr()->Data.GetKey() == key) return 1;
            polinom.next();
        }
        if (polinom.getPStop()->Data.GetKey() == key) return 1;
        return 0;
    }

    //This polinoms

    Polinom operator +(const Polinom& pol) const {
        Polinom result(*this);
        result.polinom.reset();

        TNode<Monom>* listcurr = pol.polinom.getHead();

        //обход головы, чтобы не терять pStop
        if (listcurr->Data.GetConsts() != 0)
            result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data + listcurr->Data;

        listcurr = listcurr->pNext;

        while (listcurr != pol.polinom.getPStop()->pNext)
        {
            if (result.find_monom(listcurr->Data.GetKey())) {
                result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data + listcurr->Data;
            }
            else result.polinom.pushFront(listcurr->Data);
            listcurr = listcurr->pNext;
        }

        return result;
    }

    Polinom operator -(const Polinom& pol) const {
        Polinom result(*this);
        result.polinom.reset();

        TNode<Monom>* listcurr = pol.polinom.getHead();
        
        //обход головы, чтобы не терять pStop
        if (listcurr->Data.GetConsts() != 0)
            result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data - listcurr->Data;

        listcurr = listcurr->pNext;

        while (listcurr != pol.polinom.getPStop()->pNext)
        {
            if (result.find_monom(listcurr->Data.GetKey()))
                result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data - listcurr->Data;
            else result.polinom.pushFront(Monom(listcurr->Data.GetKey(), -listcurr->Data.GetConsts()));
            listcurr = listcurr->pNext;
        }

        return result;
    }

    Polinom operator *(const Polinom& pol)  {
        Polinom result;
        polinom.setPCurr(polinom.getHead());

        TNode<Monom>* listcurr = pol.polinom.getHead();

        while (!(polinom.IsEnded())) {
            if (polinom.getPCurr()->Data.GetConsts() != 0) {
                while (listcurr != pol.polinom.getPStop())
                {
                    Monom m = polinom.getPCurr()->Data * listcurr->Data;
                    if (m.GetKey()==0)
                        result.polinom.setHead(m);
                    result.polinom.pushFront(m);
                    listcurr = listcurr->pNext;
                }
                polinom.next();
                //for pStop
                if (listcurr == pol.polinom.getPStop()) {
                    result.polinom.pushFront(polinom.getPCurr()->Data * listcurr->Data);
                }
            }
            else polinom.next();
        }

        //for pStop
        listcurr = pol.polinom.getHead();
        if (polinom.IsEnded()) {
            while (listcurr != pol.polinom.getPStop())
            {
                Monom m = polinom.getPCurr()->Data * listcurr->Data;
                if (m.GetKey() == 0)
                    result.polinom.setHead(m);
                result.polinom.pushFront(m);
                listcurr = listcurr->pNext;
            }
            if (listcurr == pol.polinom.getPStop()) {
                result.polinom.pushFront(polinom.getPCurr()->Data * listcurr->Data);
            }
        }

        return result;
    }

    //This monoms or consts

    Polinom operator +(const Monom& monom) const {
        Polinom result(*this);
        if (result.polinom.getHead()->Data.GetConsts() != 0)
            result.polinom.getHead()->Data = result.polinom.getHead()->Data + monom;
        else
            result.polinom.getHead()->Data = monom;
        return result;
    }

    Polinom operator -(const Monom& monom) const {
        Polinom result(*this);
        if (result.polinom.getHead()->Data.GetConsts() != 0)
            result.polinom.getHead()->Data = result.polinom.getHead()->Data - monom;
        else
            result.polinom.getHead()->Data = Monom(0,-monom.GetConsts());
        return result;
    }

    Polinom operator *(const Monom& monom)  {
        Polinom result(*this);
        result.polinom.reset();

        while (!(result.polinom.IsEnded())) {
            result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data * monom;

        }
        //for pStop
        if (result.polinom.IsEnded()) {
            result.polinom.getPCurr()->Data = result.polinom.getPCurr()->Data * monom;
        }

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
        p.polinom.setPCurr(p.polinom.getHead());
        while (!p.polinom.IsEnded()) {
            out << p.polinom.getPCurr()->Data;
            if ((p.polinom.getPCurr() != p.polinom.getHead())&&
                (p.polinom.getPCurr()->pNext->Data.GetConsts()!=0)) out << "+";
            p.polinom.next();
        }
        if (p.polinom.IsEnded()) out << p.polinom.getPCurr()->Data;
        out << "\n";
        return out;
    }

    double Polinom::operator() (double x, double y, double z) {
        double res = 0.0;
        polinom.setPCurr(polinom.getHead());
        while (!polinom.IsEnded()) {
            res += polinom.getPCurr()->Data(x, y, z);
            polinom.next();
        }
        if (polinom.IsEnded()) 
            res += polinom.getPCurr()->Data(x, y, z);
        return res;
    }
};