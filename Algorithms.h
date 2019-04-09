#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_
#include <sstream>
#include "LogicalFormula.h"
//������� ����
LogicalFormula createPDNF(LogicalFormula lf);
//��� �������� ������������ ���������� �� 1 � 0 � ���, ����� ��� ������ ��������� k ��� �� 1 � 0
std::vector<std::string> createBoolSample(size_t k);
//�������� ��� ��������� ���� ��������� ������� ������� �� 1 � 0
//����� ��� ������� ����������
void recSample(std::vector<std::string> &_sample, std::string str, size_t end, size_t k);
std::vector<std::string>  createTruthTable(std::string formula);
bool isDNF(LogicalFormula*  _formula, bool flag = false);
bool is�onjunct(LogicalFormula* _formula);
bool isLiteral(LogicalFormula*  _formula);
int checkConstants(const std::string &_formula);
int checkBrackets(const std::string &_formula);
bool checkForVariables(const std::string &_formula);
bool checkForUnknownVariables(const std::string &_formula);
std::string setBracketsConjunct(std::string str);
std::string setBrackets(std::string str);
int getPosForSplit(const std::string &_formula);
std::string getUniqueNames(std::string formula);
#endif 