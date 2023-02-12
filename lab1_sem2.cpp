// lab1_sem2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;

int DayWeek(int Day, int Month, int Year) {

	int DaysInYears, AllDays, DaysInMonths, Weeks, DayWeek;

	if (Month < 3) {
		Month += 12;
		Year -= 1;
	}
	Month += 1;
	DaysInMonths = Month * 30.6;
	DaysInYears = Year * 365.25;
	AllDays = DaysInMonths + DaysInYears + Day - 114;
	Weeks = AllDays / 7;
	DayWeek = AllDays - Weeks * 7;
	return DayWeek;
}




int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	
	const int week = 6 , days = 7;
	string list_mon{ , February, March, April, May, June, July, August, September, October, November, December }

	int calendar[week][days]{};

	for (int i = 0; i < week; i++) {
		for (int j = 0; j < days; j++) {
			calendar[i][j] = 0;

		}
	}

	for (int i = 0; i < week; i++) {
		if (i > 0) cout << endl;
		for (int j = 0; j < days; j++) {
			
			cout << calendar[i][j];

		}
	}

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
