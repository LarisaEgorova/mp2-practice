// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) throw "Negativ_len";
    BitLen = len;
    MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++){
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    if (pMem != nullptr) {
        delete[] pMem;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n/ (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n > BitLen) || (n < 0)) throw "No_correct_bit";
    return 1 << (n%(sizeof(TELEM)*8));

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n > BitLen) || (n < 0)) throw "No_correct_bit";
    int indx = GetMemIndex(n);
    pMem[indx] = pMem[indx] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n > BitLen) || (n < 0)) throw "No_correct_bit";
    int indx = GetMemIndex(n);
    pMem[indx] = pMem[indx] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
   if ((n > BitLen) || (n < 0)) throw "No_correct_bit";
   TELEM k = pMem[n / (sizeof(TELEM) * 8)];
   if ((k & GetMemMask(n)) == 0) return 0;
   return 1;
}

// битовые операции

const TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) return *this;
    if (MemLen != bf.MemLen)
    {
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
    }
    BitLen = bf.BitLen;
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if ((MemLen != bf.MemLen) || (BitLen != bf.BitLen)) {
        return 0;
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int minim = min(MemLen, bf.MemLen);
    TBitField res(max(BitLen, bf.BitLen));
    for (int i = 0; i < minim; i++) {
        res.pMem[i] = pMem[i] | bf.pMem[i];
    }
    if (MemLen > bf.MemLen) {
        for (int i = minim; i < MemLen; i++) {
            res.pMem[i] = pMem[i];
        }
    }
    else if (MemLen < bf.MemLen) {
        for (int i = minim; i < bf.MemLen; i++) {
            res.pMem[i] = bf.pMem[i];
        }
    }
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int minim = min(MemLen, bf.MemLen);
    TBitField res(max(BitLen, bf.BitLen));
    for (int i = 0; i < minim; i++) {
        res.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(*this);
    for (int i = 0; i < (MemLen - 1); i++) {
        res.pMem[i] = ~pMem[i];
    }
    for (int i = (sizeof(TELEM) * 8) * (MemLen - 1); i < BitLen; i++) {
        if (GetBit(i) == 0)
            res.SetBit(i);
        else
            res.ClrBit(i);
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    istr >> bf.BitLen;
    string bit;
    istr >> bit;
    for (int i = 0; i < bf.BitLen; i++) {
        if (int(bit[i] - '0') == 1) bf.SetBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 1; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
