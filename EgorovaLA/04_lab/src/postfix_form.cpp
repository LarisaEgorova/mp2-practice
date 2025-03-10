#include "postfix_form.h"

void menu() {
	string str;
	cout << "Введите арифметическое выражение\n";
	cin >> str;
	vector<string> consts = fill_const(str);

	map<string, double>var;
	for (int i = 0; i < consts.size(); i++) {
		var[consts[i]] = 0;
	}

	fill_var(var);
	manipulateList(str, var);
	return;
}

void fill_var(map<string, double>& var) {
	cout << "Введите значения для заданных констант\n";
	map<string, double>::iterator it = var.begin();
	for (int i = 0; i < var.size(); i++, it++) {
		cout << it->first << " - ";
		cin >> it->second;
		cout << "\n";
	}
}

vector<string> fill_const(const string& str) {
	int lenstr = str.length();
	int i = 0, curr = 0;
	string elem;
	vector<string> consts;
	while (i < lenstr) {
		elem = str[i];
		if ((elem != "+") && (elem != "-") && (elem != "*")
			&& (elem != "/") && (elem != "(") && (elem != ")")) {
			if (consts.size() != curr + 1) {
				consts.push_back(elem);
			}
			else consts[curr] += elem;
			i++;
			continue;
		}
		if ((elem == "(") || (elem == ")")) {
			i++;
			continue;
		}
		curr++;
		i++;
	}
	return consts;
}

bool priority(const string& elem1, const string& elem2) {
	int res1 = 0, res2 = 0;
	if ((elem1 == "(") || (elem1 == ")"))  res1 = 1;
	if ((elem2 == "(") || (elem2 == ")"))  res2 = 1;
	if ((elem1 == "+") || (elem1 == "-"))  res1 = 2;
	if ((elem2 == "+") || (elem2 == "-"))  res2 = 2;
	if ((elem1 == "*") || (elem1 == "/"))  res1 = 3;
	if ((elem2 == "*") || (elem2 == "/"))  res2 = 3;
	return (res1 > res2);
}

void expression(TStack<string>*& st1, TStack<string>*& st2, const vector<string>& express) {
	int lenexp = express.size();
	string elem;

	for(int i=0; i<lenexp;i++) {
		elem = express[i];
		if ((elem != "+") && (elem != "-") && (elem != "*")//блок для букв
			&& (elem != "/") && (elem != "(") && (elem != ")")) {
			st1->Push(elem);
			continue;
		}
		else{//операции
			if (st2->IsEmpty()) {//если начало
				st2->Push(elem);
				continue;
			}
			if ((elem == "(")) {
				st2->Push(elem);
				continue;
			}
			if ((elem == ")")) {
				while (st2->Top() != "(") {
					st1->Push(st2->Top());
					st2->Pop();
				}
				st2->Pop();
				continue;
			}
			if (priority(elem, st2->Top())) {//проверка приоритета, если низ меньше работаем
				st2->Push(elem);
				continue;
			}
			else {
				while (priority(elem, st2->Top()) != 1) {
					st1->Push(st2->Top());//если нет то кладем в стек1
					st2->Pop();
					if (st2->IsEmpty()) break;
				}
				st2->Push(elem);
				continue;
			}
		}
	}
	while (st1->IsEmpty()!=1) {
		st2->Push(st1->Top());//итоговый вид хранится в ст2
		st1->Pop();
	}
}

void print_stack(TStack<string>*& st1, TStack<string>*& st2) {
	while (st2->IsEmpty()!=1) {//сохранение стека в другом
		cout << st2->Top();
		st1->Push(st2->Top());
		st2->Pop();
	}
	cout << "\n";
	while (st1->IsEmpty() != 1) {//обратно для счета
		st2->Push(st1->Top());
		st1->Pop();
	}
}

vector<string> read(const string& str) {
	int lenstr = str.length();
	vector<string> express;
	int i = 0;
	int curr = 0;
	string elem;
	while (i < lenstr) {
		elem = str[i];
		if ((elem != "+") && (elem != "-") && (elem != "*")
			&& (elem != "/") && (elem != "(") && (elem != ")")) {
			add_elem(express, curr, elem);
			i++;
			continue;
		}
		if ((elem == "(")) {
			add_elem(express, curr, elem);
			curr++;
			i++;
			continue;
		}
		if ((elem == ")")) {
			curr++;
			add_elem(express, curr, elem);
			i++;
			continue;
		}
		curr++;
		express.push_back(elem);
		curr++;
		i++;
	}
	return express;
}

void add_elem(vector<string>& express, int curr, const string& elem) {
	if (express.size() != curr + 1) {
		express.push_back(elem);
	}
	else express[curr] += elem;
}

double calculate(TStack<double>*& st1, TStack<string>*& st2, map<string, double>& var) {
	double res = 0, x = 0, y = 0;
	if (var.size() == 1) return var[st2->Top()];
	while (st2->IsEmpty() != 1) {
		string elem = st2->Top();
		if ((elem != "+") && (elem != "-") && (elem != "*")
			&& (elem != "/")) {
			st1->Push(var[elem]);
			st2->Pop();
		}
		else {
			x = st1->Top();
			st1->Pop();
			y= st1->Top();
			st1->Pop();
			if (elem == "+") res = y+x;
			else if(elem == "-") res = y - x;
			else if(elem == "*") res = y * x;
			else if(elem == "/") res = y / x;
			st2->Pop();
			st1->Push(res);
			var[to_string(res)] = res;
		}
	}
	return res;
}

//Для списков

void manipulateList(const string& str1, map<string, double>&var) {
	TStack<string>* stack1;//операнды
	TStack<string>* stack2;//операции->хранится выражение
	TStack<double>* stack3;

	

	vector<string> ex = read(str1);

	expression(stack1, stack2, ex);
	cout << "Выражение в постфиксной форме: ";
	print_stack(stack1, stack2);

	cout << "Ответ с введенными значениями: "<< calculate(stack3, stack2, var) << "\n";
}


