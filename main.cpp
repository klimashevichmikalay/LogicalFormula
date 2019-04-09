/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// файл с точкой входа в программу-реализацию л.р. 1-2 по дисциплине ЛОИС
// написан студентом группы 621702 БГУИР Климашевичем Н. А.
// автор идеи - студент группы 621702 БГУИР Климашевич Н. А. 
// файл содержит запуск юнит-тестов и интерфейс для тестирования вручную
// файл создан 07.02.2019 и изменялся при каждом изменении программы, которые 
// описаны в файле  "LogicalFormula.h".
// последнее изменение - 27.03.2019.
// источник информации - дисциплина ОАИП, автор - Гуревич А. В.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tests.h"
#include <iostream>
#include <string>
#include <vector>

void testIsDNF();
void createPDNF();
void startTests();
void coutPDNF(string str);

int main()
{
	using namespace std;
	
	startTests();
	//createPDNF();
	testIsDNF();
	std::cin.get();
	std::cin.get();
	return 0;
}

void coutPDNF(string str)
{
	if (str == "")
	{
		cout << "\nFormula has  not pdnf.";
		return;
	}
	for (int i = 0; i < str.length(); i++)
	{
		if (i == 1 || i == str.length() - 1)
			cout << "\n";

		if (str[i] == '|')
			cout << "|\n";
		else cout << str[i];
	}
}

void startTests()
{
	cout << "start tests:\n\n";
	int i = 0;
	while (tests[i] != NULL)
	{
		tests[i]();
		i++;
	}
	cout << "\nend tests";
}

void createPDNF()
{
	string _formula;
	do {
		cout << "\n\nInpute logical formula(q for quit): ";
		cin >> _formula;
		LogicalFormula formula(_formula);
		cout << endl << "\nPDNF:\n";
		LogicalFormula pdnf = createPDNF(formula);
		coutPDNF(pdnf.getFormula());
	} while (_formula != "q");
}

void testIsDNF()
{
	string _formula = "sss";
	while (_formula != "q")
	{

		cout << "\n\n\nInpute logical formula(q for quit): ";
		cin >> _formula;
		LogicalFormula formula(_formula);
		if (isDNF(&formula))
			cout << endl << "It is DNF";
		else
			cout << endl << "It is not DNF";
	}
}


