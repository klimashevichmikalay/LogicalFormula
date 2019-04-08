/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ������������ ������ �1( ������� - f) � �2(������� -9)�� ���������� ����.
// ��������� ��������� ������ 621702 ����� ������������ �. �. 
// ����� ���� �������, �������� - ������� ������ 621702 ����� ���������� �. �. 
// � ����� ���������� �������� ��������� ������(�������� �������, ������������� � ������� ������) ��� �������� ��
// ����� ������ ���������, ����� � ��������� ���������� �������.
// ������ ��������� ���������(�������� ��������� - https://github.com/klimashevichmikalay/LogicalFormula/commits/master 
// (������ �� ����������� �� ������� �������� ������ 621702 ����� ����������� �. �. ).
// 07.02.2019 - �������� �������
// 08.02.2019 - � ������� ������ "LogicalFormula" ����������� �������� �������
// 09.02.2019 - ����������� ���������� �������� �������, ����������� ����������������� ����������
// 10.02.2019 - ����������� �������� ������� �� ���
// 11.02.2019 - �������� ���� � ���������� �������� �� ���������� ���� ������������� ������� 0 � 1
// �������� ��������, ����������� ���������� ������� ���������� � ���������� ����. ������ �������� ��
// ��������� �����������.
// 12.02.2019 ������� ��� ����������������� ��������� �������, ��������� 30 ������
// 13-14.02.2019 - ��������� ��� 60 ������, ����� ~ 97 ������ ��� ������ � ������ �.�.
// 26.03.2019 - ��������� ����������� � �������� ����� ������� ��� ������ ����� ���������� ���������� ���������
// ����� ���� ������������� ���������� - ���������� �. �., ������� ������  621702
// ��������� ����������:
// 1)������������ ������� �� �.�. �1 � �2 ����� ���� ������������� ��, �� �����. ����� - �������� �.�.
// 2)������ ��� ���������. ����� - ��������.
// 3)���� ������ �� ����. ����� - �������� �. �.
// 4)�.�. ���������, �.�. ��������: �������� ������ �� ���������� ����������
// 5)������������ ��������� � �.�. �� ����� ����. ����� - ������. �. �.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _LOGICAL_FORMULA_H_
#define _LOGICAL_FORMULA_H_

#include <iostream>
#include <string>
#include <vector>
#include <iterator>  
#include <algorithm>
#include <map>

std::string setBracketsConjunct(std::string str);
std::string setBrackets(std::string str);
namespace logics {
	//������� ���
	enum symbol { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, NO_NAME };

	class LogicalFormula {

	public:
		//������ ������� ����� ����� ���, ��� ����, ����� ��� ����� ������ ������ �������
		//��������, A = ((1&0)->0) - ��� ������� A
		//����� ������� B = (A->(1|0))
		//�� ��������� ������� �� ����� ����� � ������� �� 1 � 0, � ������ &,!,->, ~ � ��
		LogicalFormula(const std::string &_formula,//+
			symbol _name = logics::NO_NAME,
			std::map <symbol, LogicalFormula> *_mapOfFormuls = NULL);
		//����������� �����������
		LogicalFormula(const LogicalFormula &obj);
		//�������� ������� ��� ������
		std::string getFormula() { return formula; }
		//�������� ���������� ��� �������� �������
		bool getResult();
		//�������� �� ������� ���
		bool isDNF(const LogicalFormula* const _formula);//+
		//�������� �� ������� ����������
		bool is�onjunct(const LogicalFormula* const _formula);//+
		//�������� �� ���������
		bool isLiteral(const LogicalFormula* const _formula);//+
		//������� ����
		LogicalFormula createPDNF();//+
		//��� �������� ������������ ���������� �� 1 � 0 � ���, ����� ��� ������ ��������� k ��� �� 1 � 0
		std::vector<std::string> createBoolSample(size_t k);//+
		//�������� ���������� �� ���������� �������� �� �� �������� � ��������� �
		//�� ������������ �������� ������
		bool isFormula();

	private:

		bool isCorrectFormula;
		//��� ������� A, B,C � ��. ��� ���� ����� �������� �� � ������ �������
		logics::symbol name;
		//���� �������, �������� "((1->0)~0)"
		std::string formula;
		//������� ����������� �� �������� �������������� ����
		//��� ����� ����������
		LogicalFormula* left = NULL;
		//��� ������
		/*
		�������� ����� �������  (A~(B|(A->0)))
		����� ����� � left A, � � right (B|(A->0)).
		� ���� �� right ���� ����� ����� ���������� � ������.
		� ����� ����� B, � ������ ((A->0))
		� �.�. ���� �� ���������� ��������, ����� ��� ������� ��������
		������ ����� �������� ����� ��������
		*/
		LogicalFormula* right = NULL;
		//�� ��� ������ ����� � ������ ���������� ��� ������
		std::string rightSubFormula;
		std::string leftSubFormula;

		//������� ��� ���
		std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ01";//define
		//��� ���������� ������� ����������, ������ ����� ���������
		std::map <logics::symbol, LogicalFormula> *mapOfFormuls = NULL;

		//��� ����
		//LIE -  ���� ��� ���������
		//TRUTH - ������ ��� ���������
		//BRACKETS - ������, ��� ��� ����� ��������
		//��������� - ��������
		enum type { LIE = 0, TRUTH, CONJUNCTION, DISJUNCTION, IMPLICATION, EQUIVALENT, NEGATION, BRACKETS };
		type value;

		//��� ��� ��������� ���������� ��������� �������� � ������� ����� ���������� ������� ����������
		std::string getUniqueNames();//+

		//�������� ��� ��������� ���� ��������� ������� ������� �� 1 � 0
		//����� ��� ������� ����������
		void recSample(std::vector<std::string> &_sample, std::string str, size_t end, size_t k);//+
		std::vector<std::string>  LogicalFormula::createTruthTable();//+
		//������ ��� ������ ��������� ������-�������
		void splitNegation(const std::string &_formula);
		void splitWithBrackets(const std::string &_formula);
		void splitSinglesValue(const std::string &_formula);
		int checkConstants(const std::string &_formula);
		int checkBrackets(const std::string &_formula);
		void splitIntoSubFormulas(const std::string &_formula);
		int getPosForSplit(const std::string &_formula);
		void splitWithBracketsWithNegation(const std::string &_formula, int &pos);
		void splitWithBracketsWithoutNegation(const std::string &_formula, int &pos);
		void createChildred();
		bool checkForVariables(const std::string &_formula);
		bool checkForUnknownVariables(const std::string &_formula);
		void setType(const std::string &_formula, const int &pos);
		void splitPropositionalVariable();
		bool checkBracketsForEachSubtree(LogicalFormula* lf);
	};
}
#endif 

