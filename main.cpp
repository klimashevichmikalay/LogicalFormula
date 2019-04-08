/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� � ������ ����� � ���������-���������� �.�. 1-2 �� ���������� ����
// ������� ��������� ������ 621702 ����� ������������ �. �.
// ����� ���� - ������� ������ 621702 ����� ���������� �. �. 
// ���� �������� ������ ����-������ � ��������� ��� ������������ �������
// ���� ������ 07.02.2019 � ��������� ��� ������ ��������� ���������, ������� 
// ������� � �����  "LogicalFormula.h".
// ��������� ��������� - 27.03.2019.
// �������� ���������� - ���������� ����, ����� - ������� �. �.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������� �� ������ � ����
#include "tests.h"
#include <iostream>
#include <string>
#include <vector>
void testIsDNF();
void createPDNF();
void startTests();
void coutPDNF(string str);
int main() {
	using namespace std;
	startTests();
	//createPDNF();
	//testIsDNF();
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

	cout << "\n(\n";

	for (int i = 1; i < str.length() - 1; i++)
	{
		if (str[i] == '|')
			cout << "|\n";
		else cout << str[i];
	}
	cout << "\n)\n";
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
		cout << "\nInpute logical formula(q for quit): ";
		cin >> _formula;
		LogicalFormula formula(_formula);
		cout << endl << "\nPDNF:\n";
		LogicalFormula pdnf = formula.createPDNF();
		coutPDNF(pdnf.getFormula());
	} while (_formula != "q");
}

void testIsDNF()
{
	string _formula = "sss";
	while (_formula != "q")
	{
		cout << "\nInpute logical formula(q for quit): ";
		cin >> _formula;
		LogicalFormula formula(_formula);
		if (formula.isDNF(&formula))
			cout << endl << "It is DNF";
		else
			cout << endl << "It is not DNF";
	}

	/*string str = "m";
	while (str != "q")
	{
	cout << "\nEnter str for set brackets: \n";
	cin >> str;
	cout << "\nAfter set brackets: \n";
	cout << setBrackets(str);
	}*/
}


