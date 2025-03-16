#pragma once

#include "head_list.h"
#include "polinom.h"
#include <vector>
#include <string>

using namespace std;

template <typename T>
class TRingHeadList:public THeadList<T>  {
public:
    TRingHeadList() :THeadList() {}

    TRingHeadList(const T& data) : THeadList(data) {
        if (pStop!=nullptr) pStop->pNext = pHead;
    }

    /*TRingHeadList(const string& str) {
        vector<Monom<T>> express = create_parts(str);
        for (int i = 0; i < express.size(); i++) {
            pushBack(express[i]);
        }
    }*/

    TRingHeadList(const TRingHeadList<T>& list) :THeadList(list) {
        if (pStop != nullptr) pStop->pNext = pHead;
    }

    ~TRingHeadList() {
        if ((pStop!= nullptr)&&(pStop->pNext!=nullptr)) delete pStop->pNext;
        pHead = nullptr;
    }

    const TRingHeadList<T>& operator=(const TRingHeadList& list) {
        THeadList<T>::operator=(list);
        if (pStop != nullptr) pStop->pNext = pHead;
        return *this;
    }

    bool operator==(const TRingHeadList<T>& list) const {
        return (THeadList<T>::operator==(list));
    }

    virtual void pushFront(const T& data) override {
        THeadList<T>::pushFront(data);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void pushBack(const T& data) override {
        THeadList<T>::pushBack(data);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void PopBack() override {
        THeadList<T>::PopBack();
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void PopFront() override {
        THeadList<T>::PopFront();
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void pushBefore(const T& data, const T& place) override {
        THeadList<T>::pushBefore(data, place);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    virtual void pushAfter(const T& data, const T& place) override {
        THeadList<T>::pushAfter(data, place);
        if (pStop != nullptr) pStop->pNext = pHead;
        return;
    }

    /*vector<Monom<T>> create_parts(const string& str) {

        vector<Monom<T>> express;
        Monom<T> monom;
        vector<string> parts;
        int i = 0; int len = str.size();
        string tmp;

        //делю выражение на кусочки до +/-
        while (i < len) {
            if (str[i]=="+"){
                parts.push_back(tmp);
                tmp.clear();
            }
            else if (str[i] == "-") {
                parts.push_back(tmp);
                tmp.clear();
                tmp += "-";
            }
            else {
                tmp += str[i];
            }
            i++;
        }

        tmp.clear();
        i = 0; int curr = 0;

        //заполняю вектор мономов
        while (i < parts.size()) {
            while (curr < parts[i].size()) {

                //начали с переменной
                if ((parts[i][curr] == "x")||(parts[i][curr] == "y")||(parts[i][curr] == "z")) {
                    int j = curr+1;
                    if (j > parts[i].size()) throw "ERROR"; 

                    //ситуация если возведение в степень
                    if (parts[i][j] == "^") {
                        j++;
                        if (j > parts[i].size()) throw "ERROR";
                        int key = (int)(parts[i][j]);
                        switch (parts[i][curr]) {
                        case "x":
                            monom.setKey(monom.GetKey()+key * 100);
                            break;
                        case "y":
                            monom.setKey(monom.GetKey() + key * 10);
                            break;
                        case "z":
                            monom.setKey(monom.GetKey() + key);
                            break;
                        default: 
                            throw "ERROR";
                        }
                        curr+=3;
                        continue;
                    }

                    //если дальше константа
                    if (parts[i][j] == "*") {
                        j++;
                        while( (j < parts[i].size()) || (parts[i][j]!="*")) {
                            tmp += parts[i][j];
                            j++;
                        }
                        monom.setConsts((T)(tmp));
                        curr += (j-curr) + 1;
                        tmp.clear();
                    }

                    //если дальше ничего нет
                    else curr++;
                }

                if (parts[i][j] == "*") {
                    curr++;
                    continue;
                }

                //начинаем с числа или умножение после переменной
                else {
                    int j = curr;
                    while ((j < parts[i].size()) || (parts[i][j] != "*")) {
                        tmp += parts[i][j];
                        j++;
                    }
                    monom.setConsts(monom.GetConsts() * (T)(tmp));
                    curr += (j - curr) + 1;
                    tmp.clear();
                    continue;
                }
            }
            express.push_back(monom);
        }

        return express;
    }*/
};