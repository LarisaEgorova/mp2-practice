// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(1)
{
    this->MaxPower = mp;
    this->BitField = TBitField(mp);

}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(1)
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(1)
{
    this->MaxPower = bf.GetLength();
    this->BitField = bf;
}

TSet::operator TBitField()
{
    return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem >= this->MaxPower) return 0;
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

const TSet& TSet::operator=(const TSet &s) // присваивание
{
    this->MaxPower = s.GetMaxPower();
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (this->BitField == s.BitField) return 1;
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (this->BitField != s.BitField) return 1;
    return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    this->BitField = this->BitField | s.BitField;
    this->MaxPower = max(this->GetMaxPower(), s.GetMaxPower());
    return *this;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    this->InsElem(Elem);
    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    this->DelElem(Elem);
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet t1(max(this->GetMaxPower(), s.GetMaxPower()));
    t1.BitField =  this->BitField & s.BitField;
    cout << (this->BitField & s.BitField) << endl;
    //cout << this->BitField<<endl;
   // this->MaxPower = max(this->GetMaxPower(), s.GetMaxPower());
    return t1;
}

TSet TSet::operator~(void) // дополнение
{
   
    return ~this->BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int n;
    do {
        cout << "Enter an element of the set :" << endl;
        cin >> n;

    } while (s.GetMaxPower() <= n && n < 0);
    s.InsElem(n);
    istr >> s;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << "Data set: " << endl;
    ostr << "{ ";
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }
       

    }
    ostr<<"}" << endl;
    return ostr;
}
