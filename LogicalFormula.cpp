#include "LogicalFormula.h"
#include <sstream>

using namespace logics;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������������ ������ 1-2 �� ���������� ����
// ��������� ��������� ������ 621702 ����� ������������ �. �.
//// ����� ���� �������, �������� - ������� ������ 621702 ����� ���������� �. �. 
// ���� �������� ���������� ������� ���������, ��������� � ����� "LogicalFormula.h"
// ��������� ����������� ���������� � ������ "LogicalFormula.h", �������� ������ ������� ���.
// ������ �� ��������� ������� � ����� "LogicalFormula.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//�������� �� ��, ��� ������� ����� � �������� �������
int LogicalFormula::checkConstants(const std::string &_formula) {
	size_t sz = _formula.length();
	switch (sz) {
	case 0:
		return 1;
		break;

	case 1:
		if (!strchr(alphabet.c_str(), _formula[0]))
			return 1;
		break;

	case 2:
		if (strchr(alphabet.c_str(), _formula[0]) && strchr(alphabet.c_str(), _formula[1]))
			return 1;
		break;

	default:
		for (size_t i = 0; i < _formula.length() - 2; i++)
			if ((strchr(alphabet.c_str(), _formula[i]) &&
				strchr(alphabet.c_str(), _formula[i + 2]) && _formula[i + 1] == '!') ||
				strchr(alphabet.c_str(), _formula[i]) && strchr(alphabet.c_str(), _formula[i + 1]))
				return 1;

		if (!checkForVariables(_formula) || !checkForUnknownVariables(_formula))
			return 1;
		break;
	}
	return 0;
}

//���� ����������� �������, �� ��������� �������
bool LogicalFormula::checkForUnknownVariables(const std::string &_formula) {
	for (size_t i = 0; i < _formula.length(); i++)
		if (!strchr("01ABCDEFGHIJKLMNOPQRSTUVWXYZ()->|&!~\n", _formula[i]))
			return false;
	return true;
}


bool LogicalFormula::checkForVariables(const std::string &_formula) {
	for (size_t i = 0; i < alphabet.length(); i++)
		if (strchr(_formula.c_str(), alphabet[i]))
			return true;
	return false;
}

//��������, ����� �� ������ ����������� �����������
int LogicalFormula::checkBrackets(const std::string &_formula) {
	int count = 0;
	for (size_t i = 0; i < _formula.length(); i++) {
		if (_formula[i] == '(')
			count++;
		else if (_formula[i] == ')')
			count--;
	}
	if (count != 0)
		return 1;
	return 0;
}

//��� ���� ��������� �� ����� � ���������� 3� ��������, �� ���, ��� �� �������
bool LogicalFormula::isFormula() {
	return checkBracketsForEachSubtree(this);
}

//����������� � ���������� ���������� NULL, � ��������� �������
//_mapOfFormuls ��� ����, ����� ���� ������� ������������ � ������
//��������, A = (1!0)
//B = (0->A)
//C = (A|B) - A �  B, �������� �� ������� ������ ���
//D = ((0->C)~A) - C, A,B, ������� �� ������� ������
//� ��
//��� ��� _mapOfFormuls � �������� ��������� ������� � �� �����, � ������ ���� �������
LogicalFormula::LogicalFormula(const std::string &_formula, logics::symbol _name,
	std::map <logics::symbol, LogicalFormula> *_mapOfFormuls) {

	if (_mapOfFormuls != NULL) {
		this->mapOfFormuls = new (std::map <logics::symbol, LogicalFormula>);
		*(this->mapOfFormuls) = *(_mapOfFormuls);
	}
	//������� ����� ��� ������
	formula = _formula;
	//��������� �� ���������?
	isCorrectFormula = (checkConstants(formula) == 0 && checkBrackets(formula) == 0);
	//��� ��� �������, ���� �� ������� �� �������� � ������ �������
	name = _name;
	left = NULL;
	right = NULL;
	if (isCorrectFormula)
		//���� ������� ���������, �� ��������� �� �������� ������
		splitIntoSubFormulas(formula);

}

bool LogicalFormula::checkBracketsForEachSubtree(LogicalFormula* lf) {

	if (!isCorrectFormula)
		return false;

	if (lf == NULL)
		return true;

	if (isLiteral(lf) || (lf->left == NULL && lf->right == NULL))
		return true;

	if (lf->value != BRACKETS || lf->left != NULL)
	{
		return false;
	}

	if (lf->right != NULL & lf->right->value == BRACKETS)
	{
		return false;
	}
	return (checkBracketsForEachSubtree(lf->right->left) && checkBracketsForEachSubtree(lf->right->right));
}
// 
//��� ��������� ���������, ����� ���������� ��������� �� ����� ����
//���� ���������, �� ����� ��������� �������� NULL,
//� ������ ����� ��������� ��� ���������(NEGATION � ������������)
void LogicalFormula::splitNegation(const std::string &_formula) {
	value = NEGATION;
	rightSubFormula = _formula.substr(1, _formula.length() - 1);
	right = new LogicalFormula(rightSubFormula, logics::NO_NAME, this->mapOfFormuls);
	left = NULL;
	leftSubFormula = "";
	return;
}

//��� �� ���� ����������
//������ ����� ����� ��� ������� ������������� ������, ��� � ���� ����������, �� ������
int LogicalFormula::getPosForSplit(const std::string &_formula) {
	int count = 0;
	for (size_t i = _formula.length() - 1; i >= 0; i--) {
		if (_formula[i] == ')')
			count++;
		else if (_formula[i] == '(')
			count--;

		if (count == 0)
			return i;
	}
	return _formula.length() + 10;
}


//����������� �����������
LogicalFormula::LogicalFormula(const LogicalFormula &obj) {

	if (obj.mapOfFormuls != NULL) {

		this->mapOfFormuls = new (std::map <logics::symbol, LogicalFormula>);
		*(this->mapOfFormuls) = *(obj.mapOfFormuls);
	}
	this->formula = obj.formula;
	this->rightSubFormula = obj.rightSubFormula;
	this->leftSubFormula = obj.leftSubFormula;
	this->value = obj.value;
	this->name = obj.name;

	if (obj.left != NULL) {
		left = new LogicalFormula(obj.left->formula, obj.left->name, obj.left->mapOfFormuls);
	}

	if (obj.right != NULL) {
		right = new LogicalFormula(obj.right->formula, obj.right->name, obj.right->mapOfFormuls);
	}
}



void LogicalFormula::splitPropositionalVariable() {
	logics::symbol _name = logics::symbol(alphabet.find(formula[0]));

	if (mapOfFormuls != NULL)
		*this = mapOfFormuls->find(_name)->second;
	//	else isCorrectFormula = false;

	this->name = _name;
}


//��������� �� ����������, �� ������ ��������
//������� ����� ��� ���������� ����������, ��
//������ ��� �������� ����� ���������� � �������� �������� � ���� ����� �����������
//����� ��� �� �� �������,   � ��� ������ �� 1 ��� 0, �� ��� �����, � �� ����� �������� ����� �����
//������: ������ ��� ����
void LogicalFormula::splitIntoSubFormulas(const std::string &_formula) {

	//���� � ������� ������� ���� ������ �� 1 ��� 0, �� ��� ���������� ������ ��� ����
	if (_formula.length() == 1) {
		_formula[0] == '0' ? value = LIE : value = TRUTH;

		//���� ��� ������ �����, �� ������ ��� ��� 
		//������ ������� �������� ���������� ���� �������, ��� ������ ������� ���� ��������� �� ����������
		if (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", _formula[0]))
			splitPropositionalVariable();
		return;
	}
	//���� ���������, ��� ���������� - ��������� , � ������������ - NEGATION, 
	//����������� ������ ! � ��������� ������
	if (_formula[0] == '!') {
		splitNegation(_formula);
		return;
	}

	//���� ������, ������ ������� ��, ������ ��� "������"(� ������������ ��� BRACETS)
	//� ��������� ����������, ������� ����� ��, �� ��� ������
	if (_formula[_formula.length() - 1] == ')') {
		splitWithBrackets(_formula);
		return;
	}
	else {
		//���� � ������� ������ ���� ���� ������ �������� 
		splitSinglesValue(_formula);
		return;
	}
}


//��������� �����  � ������ ���������
void LogicalFormula::createChildred() {
	if (leftSubFormula != "")
		left = new LogicalFormula(leftSubFormula, logics::NO_NAME, this->mapOfFormuls);

	if (rightSubFormula != "")
		right = new LogicalFormula(rightSubFormula, logics::NO_NAME, this->mapOfFormuls);
}

//��������� ������,������ ������� ���� � LogicalFormula::splitIntoSubFormulas(const std::string &_formula) 
void LogicalFormula::splitWithBracketsWithNegation(const std::string &_formula, int &pos) {
	pos--;
	rightSubFormula = _formula.substr(pos);

	if (pos > 2 && _formula[pos - 1] == '>' && _formula[pos - 2] == '-')
		leftSubFormula = _formula.substr(0, pos - 2);

	else if (pos > 1) {
		leftSubFormula = _formula.substr(0, pos - 1);
	}
	setType(_formula, pos);
	//������� �� ����������, �����
	//������ ����� ������  LOgicalFormula ��� ������  ��������� � �������
	//� createChildred() ���������� ������������� ��� ����� ������,
	//� ����� ������� ����� ��� �� ����������� �� ����������-�������,
	//���� � ����������� �� ������� 1 ��� 0, ��� ����� ����� ��������
	createChildred();
	return;
}

//��������� ������ ,������ ������� ���� � LogicalFormula::splitIntoSubFormulas(const std::string &_formula) 
void LogicalFormula::splitWithBracketsWithoutNegation(const std::string &_formula, int &pos) {

	if (pos != 0)
	{
		rightSubFormula = _formula.substr(pos, _formula.length() - pos);
	}

	else
	{
		rightSubFormula = _formula.substr(pos + 1, _formula.length() - 2 - pos);
	}
	if (pos > 1 && _formula[pos - 1] == '>')
		leftSubFormula = _formula.substr(0, pos - 2);
	else if (pos > 0)
		leftSubFormula = _formula.substr(0, pos - 1);

	setType(_formula, pos);
	createChildred();
	return;
}

//��������� ������ ����� �������� ���������,
//������ ������� ���� � LogicalFormula::splitIntoSubFormulas(const std::string &_formula) 

void LogicalFormula::splitWithBrackets(const std::string &_formula) {
	int pos = getPosForSplit(_formula);

	if (pos > 0 && _formula[pos - 1] == '!')
		splitWithBracketsWithNegation(_formula, pos);
	else
		splitWithBracketsWithoutNegation(_formula, pos);
	return;
}

//��� �������� �������  ��������� ���, ����������, ��������� ��� � ��.
void LogicalFormula::setType(const std::string &_formula, const int &pos) {
	if (pos > 0) {
		if ((_formula[pos - 1]) == '&')
			value = CONJUNCTION;
		if ((_formula[pos - 1]) == '|')
			value = DISJUNCTION;
		if ((_formula[pos - 1]) == '>')
			value = IMPLICATION;
		if ((_formula[pos - 1]) == '~')
			value = EQUIVALENT;
	}
	else  value = BRACKETS;
}

//����� � ����������� ������ ������� �� ������ �������
void LogicalFormula::splitSinglesValue(const std::string &_formula) {
	rightSubFormula = _formula[_formula.length() - 1];
	if (_formula[_formula.length() - 2] == '>')
		leftSubFormula = _formula.substr(0, _formula.length() - 3);
	else
		leftSubFormula = _formula.substr(0, _formula.length() - 2);

	setType(_formula, _formula.length() - 1);
	createChildred();
	return;
}


//��� ������� �������� �������
//���� ���� ������� ������
//������ �� ���������� ��� ������� ���������, LEFT � RIGHT �������� ����� ����������
//� ����� �� ����������� �� TRUTH �� ������ ������ � ����������� ������
//��� ������ ������, ���-�� ������� � ��� ���� �� ������ ��  ����������� ����������
//��������, ������� ������� ��� �������
bool LogicalFormula::getResult() {
	switch (value)
	{
		//���� ��� ������� ������ - ������ ������� �����
	case TRUTH:	return true;
		break;

	case CONJUNCTION:
		//���� ����������,
		//�� ����� � ������ ���������� ������  ���� �����
		if (left->getResult() && right->getResult()) return true;
		break;

	case DISJUNCTION:
		//���� ����������� � ���� ��� ����� ���������� ���������� ������� ���, ��� ������, //
		//����� ������� ��� � ��.�
		if (left->getResult() || right->getResult()) return true;
		break;

	case IMPLICATION:
		if (!(left->getResult() && !(right->getResult()))) 	return true;
		break;

	case EQUIVALENT:
		if (left->getResult() == right->getResult()) return true;
		break;

	case NEGATION:
		return !(right->getResult());
		break;

	case BRACKETS:
		return (right->getResult());
		break;
	}
	return false;
}


//����������� �������� �� ��, ��� ������� �������
//�������� �� ��� ���,
//���� �� ����������� �� ������� ��� ����� ������(NULL)
bool LogicalFormula::is�onjunct(const LogicalFormula* const _formula) {
	if (_formula == NULL || isLiteral(_formula))
		return true;
	if (_formula->value != BRACKETS && _formula->value != CONJUNCTION)
		return false;

	return (is�onjunct(_formula->left) && is�onjunct(_formula->right));
}

//������ ��������, �������� �� ��� ��������� - ����� ������ �� ��������
//
bool LogicalFormula::isLiteral(const LogicalFormula* const _formula) {
	switch (_formula->formula.length()) {
	case 1://�������� ��������
		if (strchr(_formula->alphabet.c_str(), _formula->formula[0]))
			return true;
		break;
	case 2:
		if (strchr(_formula->alphabet.c_str(), _formula->formula[1]) &&
			_formula->formula[0] == '!')
			return true;
		break;
	}
	return false;
}


//�������� �� ���
//���������� ���������, ������� �� ���������� �� ���������� ��� ���������
bool  LogicalFormula::isDNF(const LogicalFormula* const _formula)
{
	if (!isFormula())
		return false;

	if (_formula == NULL || is�onjunct(_formula))
		return true;

	if (_formula->value != BRACKETS && _formula->value != DISJUNCTION)
		return false;

	return (isDNF(_formula->left) && isDNF(_formula->right));
}


//���� �� ����� �������� ����, � � ������� ����� ���-
//������� ��������, �� ������� ���������
//��������
//��� ������� ((A|B)->A) ������ ������ "AB"
std::string LogicalFormula::getUniqueNames() {
	std::string result;
	for (size_t i = 0; i < formula.length(); i++)
		if (!strchr("01", formula[i]) && strchr(alphabet.c_str(), formula[i]) && (!strchr(result.c_str(), formula[i])))
			result += formula[i];

	return result;
}

//��� �������� ������� ����������
//����� ��������� ��������� �������
//��� ���� ��������� ��������� �� ����������
//� �������� �������� ���������� ���� ����  ��������� �� 1 � 0 ������� �������
//�������� ��� ����� 4 createBoolSample ������:
/*
0000
0001
0011
0111
1111
1101
0111
0101
 � �.�.
*/
void  LogicalFormula::recSample(std::vector<std::string> &_sample, std::string str, size_t end, size_t k) {
	for (size_t j = 1; j <= k; j++)
		for (size_t i = 0; i <= end - j + 1; i++) {
			std::string curStr = str;
			curStr = std::string(curStr.replace(i, j, std::string(j, '1')));
			_sample.push_back(curStr);
			recSample(_sample, curStr, i - 1, i);
		}
}

std::vector<std::string>  LogicalFormula::createBoolSample(size_t k) {
	std::vector<std::string> sample(1, std::string(k, '0'));
	recSample(sample, std::string(k, '0'), k - 1, k);
	sort(sample.begin(), sample.end());
	sample.erase(unique(sample.begin(), sample.end()), sample.end());
	return sample;
}

//��� �������� ������� �����������,
//��� ��� ������ ������
//� �������� ������ �� ��������, ��� ������� ������� �������
//�������� ���� ������� (A->B)
//����� � ������ ������ ������������� ��������
//������ ������ ����� 1 ��� 0 - ��� �������� �������� �
//������ ����� ���� 1 ��� 0 - ������� �������� B
std::vector<std::string>  LogicalFormula::createTruthTable() {
	std::string uniqueNames = getUniqueNames();
	std::vector<std::string> samples = createBoolSample(uniqueNames.size());
	std::vector<std::string> truthTable;
	new std::string((samples[0].size() + 1), ' ');
	for (size_t i = 0; i < samples.size(); i++) {
		std::string curStr = formula;
		for (size_t j = 0; j < samples[0].size(); j++)
			replace(curStr.begin(), curStr.end(), uniqueNames[j], samples[i][j]);

		LogicalFormula temp = LogicalFormula(curStr);
		if (temp.getResult())
			truthTable.push_back(samples[i] + "1");
	}
	return truthTable;
}


std::string setBracketsConjunct(std::string str)
{
	int countConjunct = 0;
	std::string res = "";
	int n = std::count(str.begin(), str.end(), '&');

	if (n == 0)
		return str;

	for (int i = 0; i < n; i++)
	{
		res += '(';
	}

	for (int i = 0; i < str.length(); i++)
	{
		res += str[i];

		if (str[i] == '&')
			countConjunct++;

		if (((i+1 < str.length() && str[i+1]=='&' )) && countConjunct > 0 && (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ01)", str[i])))
			res += ')';
	}
	res += ')';
	return res;
}


std::string setBrackets(std::string str)
{
	if (str == "")
		return str;

	std::stringstream ss(str);
	std::vector<std::string> conjuncts;
	for (std::string conjunct; std::getline(ss, conjunct, '|'); conjuncts.push_back(conjunct));

	if (conjuncts.size() < 2)
		return	setBracketsConjunct(str);

	for (int i = 0; i < conjuncts.size(); i++)
		conjuncts[i] = setBracketsConjunct(conjuncts[i]);


	std::string res = "";
	for (int i = 0; i < conjuncts.size() - 1; i++)
	{
		res += '(';
	}

	for (int i = 0; i < conjuncts.size(); i++)
	{
		res += conjuncts[i];

		if (i != 0)
			res += ')';

		if (i != conjuncts.size() - 1)
			res += "|";
	}
	return res;
}

//����� ��������� ������� ����������
//�� ����� �� ��� ��������, ����� ������� �������,
//� ������ ���, ���� � ������� ���������� ����� 0, � ��������� ������� ������, �� ������
//���� ���� ������� � ���������� � ��
LogicalFormula LogicalFormula::createPDNF() {


	if (!isFormula())
	{
		LogicalFormula result("\nFormula has syntax error.");
		return result;
	}

	std::vector<std::string> truthTable = createTruthTable();
	std::string uniqueNames = getUniqueNames();
	std::string str = "";

	for (size_t i = 0; i < truthTable.size(); i++) {
		for (size_t j = 0; j < truthTable[0].size() - 1; j++) {
			if (truthTable[i][j] == '0') {
				str.push_back('(');
				str.push_back('!');
				str.push_back(uniqueNames[j]);
				str.push_back(')');
			}
			else
			{
				str.push_back(uniqueNames[j]);
			}

			if (j < truthTable[0].size() - 2)
				str.push_back('&');
		}
		if (i < (truthTable.size() - 1))
			str.push_back('|');
	}

	LogicalFormula result(setBrackets(str));
	return result;
}