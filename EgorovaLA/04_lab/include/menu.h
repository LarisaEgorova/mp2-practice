#pragma once

#include <iostream>
#include <string>
#include "polinom.h"


void menu() {
	while (true) {
		Polinom polinom1;
		Polinom polinom2;
		Polinom P;
		double x, y, z;
		double res;
		char choice;
		cout << "Полином должен быть в виде: C1*x^a*y^b*z^c+...\n"
			<<"Используйте:\n-'^' при возведении в степень\n- Отрицательные константы в виде -C1" 
			<<"\n- Ввод переменных 1ой в виде степени x^1, y^1, z^1\n\n";
		cout << "Посчитать значение полинома (1)\nСложить 2 полинома и посчитать значение(2)\n" <<
			"Вычесть 2 полинома и посчитать значение(3)\nУмножить 2 полинома и посчитать значение(4)\nВыйти(5)\n";

		cin >> choice;

		switch (choice) {
		case '1':
			cout << "Введите полином: \n";
			cin >> polinom1;
			cout << "Введите значения x, y, z: \n";
			cin >> x >> y >> z; 
			res = polinom1(x, y, z);
			cout << "Значение полинома: " << res <<"\n\n\n";
			break;
		case '2':
			cout << "Введите полином 1: \n";
			cin >> polinom1;
			cout << "Введите полином 2: \n";
			cin >> polinom2;
			P = polinom1 + polinom2;
			cout << "Полученный полином: " << P;
			cout << "Введите значения x, y, z: \n";
			cin >> x >> y >> z;
			res = P(x, y, z);
			cout << "Значение полинома: " << res << "\n\n\n";
			break;
		case '3':
			cout << "Введите полином 1: \n";
			cin >> polinom1;
			cout << "Введите полином 2: \n";
			cin >> polinom2;
			P = polinom1 - polinom2;
			cout << "Полученный полином: " << P;
			cout << "Введите значения x, y, z: \n";
			cin >> x >> y >> z;
			res = P(x, y, z);
			cout << "Значение полинома: " << res << "\n\n\n";
			break;
		case '4':
			cout << "Введите полином 1: \n";
			cin >> polinom1;
			cout << "Введите полином 2: \n";
			cin >> polinom2;
			P = polinom1 * polinom2;
			cout << "Полученный полином: " << P;
			cout << "Введите значения x, y, z: \n";
			cin >> x >> y >> z;
			res = P(x, y, z);
			cout << "Значение полинома: " << res << "\n\n\n";
		case '5':
			return;
		default:
			cout << "Не верный ввод\n\n";
			cin.clear();
			cin.ignore(32767, '\n');
			break;
		}
	}
}
