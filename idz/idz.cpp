#include <iostream>
#include <clocale>
#include <string>

using namespace std;

enum RESULT {
	FALSE,
	TRUE_AND_CONTINUE,
	TRUE_AND_STOP
};

RESULT ProcessExpression();
RESULT ProcessMember();
RESULT ProcessSign();


int main() {
	setlocale(LC_CTYPE, "rus");

	system("cls");
	cout << "Бесскобочные выражения с функциями, переменными и арифметическими операциями.\n";
	cout << "Пример: f(x)+g(f(a+b))*c\n";
	char c = ' ';
	cout << "Введите выражение: ";
	bool belongs = ProcessExpression();
	if (belongs)
		cout << "Выражение принадлежит языку\n";
	else cout << "Выражение не принадлежит языку\n";

	system("pause");
	return 0;
}

RESULT ProcessExpression() {
	char cur = ' ';
	RESULT res = ProcessMember();
	if (res) {
		res = ProcessSign();
		if (res == TRUE_AND_CONTINUE)
			res = ProcessExpression();
	}
	return res;
}

RESULT ProcessSign() {
	char cur = ' ';
	cin.get(cur);
	if (cur == '+' || cur == '-' || cur == '*' || cur == '/')
		return TRUE_AND_CONTINUE;
	else if (cur == '\n' || cur == ')')
		return TRUE_AND_STOP;
	else return FALSE;
}

RESULT ProcessMember() {
	RESULT res = FALSE;
	char cur = ' ';
	cin.get(cur);
	if (cur == 'f' || cur == 'g' || cur == 'h') {
		cin.get(cur);
		if (cur == '(') {
			res = ProcessExpression();
			if (res == TRUE_AND_CONTINUE) {
				cin >> cur;
				if (cur != ')')
					res = FALSE;
				else res = TRUE_AND_CONTINUE;
			}
		}
		else
			res = FALSE;
	}
	else {
		if (cur >= 'a' && cur <= 'z')
			res = TRUE_AND_CONTINUE;
		else res = FALSE;
	}

	return res;
}
