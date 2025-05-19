#include "polinom.h"

//MONOMS

Monom:: Monom() : key(0), consts(0) {}

Monom:: Monom(const int Key, const double& Consts) :consts(Consts) {
    if ((Key < -1) || (Key > 999)) throw "No correct key";
    key = Key;
}

Monom:: Monom(const Monom& monom) :key(monom.key), consts(monom.consts) {}

Monom:: Monom(const string& str) : Monom() {
    int strlen = str.size();
    for (int i = 0; i < strlen; i++) {
        if (str[i] == '-') {
            if (consts == 0) consts = -1;
            else consts *= -1;
            continue;
        }

        if ((str[i] == 'x') || (str[i] == 'y') || (str[i] == 'z') || (str[i] == '*')) {
            if (consts == 0) consts = 1;
            switch (str[i]) {
            case'x':
                if (key / 100 == 0) key += 100;
                break;
            case'y':
                if ((key / 10) % 10 == 0) key += 10;
                break;
            case'z':
                if (key % 10 == 0)key += 1;
                break;
            default: break;
            }
            continue;
        }

        if (str[i] == '^') {
            int j = i + 1;
            string tmp;

            switch (str[i - 1]) {
            case'x':
                if (key / 100 == 1) key -= 100;
                break;
            case'y':
                if ((key / 10) % 10 == 1) key -= 10;
                break;
            case'z':
                if (key % 10 == 1)key -= 1;
                break;
            default: break;
            }

            while ((str[j] != '*') && (j < strlen)) {
                if (j > strlen) throw "No correct enter";
                tmp += str[j];
                j++;
            }
            if ((stoi(tmp) > 9) || (stoi(tmp) < 0)) throw "Big degree";
            if (str[i - 1] == 'x') {
                key += stoi(tmp) * 100;
                i = j;
                continue;
            }
            if (str[i - 1] == 'y') {
                key += stoi(tmp) * 10;
                i = j;
                continue;
            }
            if (str[i - 1] == 'z') {
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
            if ((key == 0) && (consts == 0)) consts += stod(tmp);
            else consts *= stod(tmp);
            continue;
        }
    }
}

Monom& Monom::operator=(const Monom& monom) {
    if (this != &monom) {
        consts = monom.consts;
        key = monom.key;
    }
    return *this;
}

bool Monom::operator==(const Monom& monom) const {
    return ((key == monom.key) && (consts == monom.consts));
}

bool Monom::operator!=(const Monom& monom) const {
    return (!(Monom::operator==(monom)));
}

bool Monom::operator <(const Monom& monom) const {//проверка по ключу
    return (key < monom.key);
}

bool Monom::operator >(const Monom& monom) const {
    return (key > monom.key);
}

Monom Monom::operator +(const Monom& monom)const {
    if (key != monom.key) throw "Can't sum";
    double c = consts + monom.consts;
    if (c == 0) {
        return Monom(-1, 0);//удаленный 
    }
    return Monom(key, c);
}

Monom& Monom:: operator +=(const Monom& monom) {
    return *this = *this + monom;
}

Monom Monom::operator -(const Monom& monom)const {
    if (key != monom.key) throw "Can't sum";
    double c = consts + monom.consts * (-1.0);
    return Monom(key, c);
}

Monom& Monom::operator -=(const Monom& monom) {
    return *this = *this - monom;
}

Monom Monom::operator *(const Monom& monom) const {
    if ((key + monom.key) > 999) throw "Big key";
    int k = key + monom.key;
    double c = consts * monom.consts;
    return Monom(k, c);
}

Monom& Monom::operator *=(const Monom& monom) {
    return *this = *this * monom;
}

Monom Monom::operator +(double C) const {
    return Monom(0, consts + C);
}

Monom Monom::operator -(double C) const {
    return Monom(0, consts - C);
}

Monom Monom::operator *(double C) const {
    return Monom(0, consts * C);
}


double Monom::operator()(double x, double y, double z) const
{
    double res = 0.0;
    res = consts * pow(x, (key / 100)) * pow(y, ((key / 10) % 10)) * pow(z, (key % 10));
    return res;
}


//POLINOMS

Polinom::Polinom() {}
Polinom::Polinom(const Monom& monom) : polinom() {
    polinom.pushFront(monom);
}
Polinom::Polinom(const string& str) : polinom() {
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
        if (str[i] == '-') tmp += str[i];
    }
}

Polinom::Polinom(const Polinom& pol) :polinom(pol.polinom) {}

TRingHeadList<Monom> Polinom::getPolinom() const {
    return polinom;
}

bool Polinom::operator==(const Polinom& P) const {
    return (polinom == P.polinom);
}

const Polinom& Polinom::operator=(const Polinom& pol) {
    if (this != &pol) {
        polinom = pol.polinom;
    }
    return *this;
}

void Polinom::insert_monom(const Monom& data) {
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
        //OK
        if (data.key == polinom.getPCurr()->Data.key) {
            polinom.getPCurr()->Data += data; // TODO: (x-1) and -x
            if (polinom.getPCurr()->Data.consts == 0) polinom.PopCurr();
            return;
        }
        polinom.next();
    }
    polinom.pushBack(data);
}

//This polinoms

Polinom Polinom::operator +(const Polinom& pol) const {
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
//OK
Polinom Polinom::operator -(const Polinom& pol) const { // TODO: p1+p2*(-1.0)
    Polinom result(*this);
    Polinom copypol = pol;
    result = result + copypol * (-1.0);
    return result;
}

Polinom Polinom::operator *(const Polinom& pol) const { // TODO: use while (p.monon) {+= polinom * monom}
    Polinom result;
    Polinom copypol(pol);
    Polinom copythis(*this);

    copypol.polinom.reset();

    while (!copypol.polinom.IsEnded()) {
        if (copypol.polinom.getPCurr()->Data.consts != 0) {
            Monom m = copypol.polinom.getPCurr()->Data;
            result = result + copythis * m;
            copypol.polinom.next();
        }
        else copypol.polinom.next();
    }

    return result;
}

//This monoms
//OK
Polinom Polinom::operator +(const Monom& monom) const { // TODO: use insert
    Polinom result(*this);
    result.insert_monom(monom);
    return result;
}
//OK
Polinom Polinom::operator -(const Monom& monom) const { // TODO: p+m*(-1.0)
    Polinom result(*this);
    result = result + monom * (-1.0);
    return result;
}
//OK
Polinom Polinom::operator *(const Monom& monom) {// TODO: while () умножение мононов на моном
    Polinom result;
    Polinom copypol(*this);

    copypol.polinom.reset();

    while (!copypol.polinom.IsEnded()) {
        if (copypol.polinom.getPCurr()->Data.consts != 0) {
            result.insert_monom(copypol.polinom.getPCurr()->Data * monom);
            copypol.polinom.next();
        }
        else copypol.polinom.next();
    }
    return result;
}

// TODO: polinom +-* const
//This consts
//OK
Polinom Polinom::operator +(double C) const {
    Polinom result(*this);
    Monom mon(0, C);
    result.insert_monom(mon);
    return result;
}
//OK
Polinom Polinom::operator -(double C) const {
    Polinom result(*this);
    Monom mon(0, C);
    result = result + mon * (-1.0);
    return result;
}
//OK
Polinom Polinom::operator *(double C) {
    Polinom result(*this);
    Monom mon(0, C);
    result = result * mon;
    return result;
}

double Polinom::operator() (double x, double y, double z) {
    double res = 0.0;
    polinom.reset();
    if (polinom.getPCurr() == nullptr) return res;
    while (!polinom.IsEnded()) {
        res += polinom.getPCurr()->Data(x, y, z);
        polinom.next();
    }
    return res;
}