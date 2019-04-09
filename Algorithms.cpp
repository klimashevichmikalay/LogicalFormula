#include "Algorithms.h"

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

		if (((i + 1 < str.length() && str[i + 1] == '&')) && countConjunct > 0 && (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ01)", str[i])))
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

//после получения таблицы истинности
//мы берем из нее значения, когда формула истинна,
//и строим днф, если в таблице переменная равна 0, а результат формулы истина, то записы
//ваем этот элемент с отрицанием и тд
LogicalFormula createPDNF(LogicalFormula lf) {


	if (!lf.isFormula())
	{
		LogicalFormula result("\nFormula has syntax error. ");
		return result;
	}

	std::vector<std::string> truthTable = createTruthTable(lf.getFormula());
	std::string uniqueNames = getUniqueNames(lf.getFormula());
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

//проферка на то, что алфавит верен в веденной формуле
int checkConstants(const std::string &_formula) {
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

//если неизвестные символы, то синтаксис неверен
bool checkForUnknownVariables(const std::string &_formula) {
	for (size_t i = 0; i < _formula.length(); i++)
		if (!strchr("01ABCDEFGHIJKLMNOPQRSTUVWXYZ()->|&!~\n", _formula[i]))
			return false;
	return true;
}


bool checkForVariables(const std::string &_formula) {
	for (size_t i = 0; i < alphabet.length(); i++)
		if (strchr(_formula.c_str(), alphabet[i]))
			return true;
	return false;
}

//проверка, чтобы ве скобки симметрично закрывались
int checkBrackets(const std::string &_formula) {
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

//это мы ищем подформулу
//просто когда нашли две вовремя закрывающиеся скобки, это и есть подформула, ее начало
int getPosForSplit(const std::string &_formula) {
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

//если мы хотим построит СДНФ, и в формуле много оди-
//наковых символов, то убираем дубликаты
//например
//для формулы ((A|B)->A) вернет строку "AB"
std::string getUniqueNames(std::string formula) {
	std::string result;
	for (size_t i = 0; i < formula.length(); i++)
		if (!strchr("01", formula[i]) && strchr(alphabet.c_str(), formula[i]) && (!strchr(result.c_str(), formula[i])))
			result += formula[i];

	return result;
}

//рекурсивная проверка на то, что формулы конъюкт
//рекурсия до тех пор,
//пока не натолкнемся на литерал или конец дерева(NULL)
bool isСonjunct(LogicalFormula* _formula) {
	if (isLiteral(_formula))
		return true;
	if (_formula->getType() != BRACKETS && _formula->getType() != CONJUNCTION)
		return false;

	return (isСonjunct(_formula->getLeft()) && isСonjunct(_formula->getRight()));
}

//просто проверка, является ли это литералом - одним знаком из алфавита
//
bool isLiteral(LogicalFormula* _formula) {

	if (_formula == NULL)
		return true;

	std::string  _alphabet = alphabet;
	switch (_formula->getFormula().length()) {
	case 1://добавить комменты
		if (strchr(alphabet.c_str(), _formula->getFormula()[0]))
			return true;
		break;
	case 2:
		if (strchr(_alphabet.c_str(), _formula->getFormula()[1]) &&
			_formula->getFormula()[0] == '!')
			return true;
		break;
	}
	return false;
}


//проверка на днф
//рекурсивно проверяем, состоят ли поддеревья из конъюнктов или литератов
bool  isDNF(LogicalFormula*  _formula, bool flag)
{
	if (_formula == NULL)
		return true;

	if (!flag && !_formula->isFormula())
		return false;

	if ((strchr(_formula->getFormula().c_str(), '0') || strchr(_formula->getFormula().c_str(), '1')))
		return false;

	if (_formula == NULL || isСonjunct(_formula))
		return true;

	if (_formula->getType() != BRACKETS && _formula->getType() != DISJUNCTION)
		return false;

	return (isDNF(_formula->getLeft(), true) && isDNF(_formula->getRight(), true));
}

//при создании таблицы истинности
//нужно проверить результат формулы
//при всех фозможных значениях ее переменных
//в слудущих функциях происходит поск всех  сочетаний из 1 и 0 нужного размера
//например для числа 4 createBoolSample вернет:
/*
0000
0001
0011
0111
1111
1101
0111
0101
и т.д.
*/
void  recSample(std::vector<std::string> &_sample, std::string str, size_t end, size_t k) {
	for (size_t j = 1; j <= k; j++)
		for (size_t i = 0; i <= end - j + 1; i++) {
			std::string curStr = str;
			curStr = std::string(curStr.replace(i, j, std::string(j, '1')));
			_sample.push_back(curStr);
			recSample(_sample, curStr, i - 1, i);
		}
}


std::vector<std::string>  createBoolSample(size_t k) {
	std::vector<std::string> sample(1, std::string(k, '0'));
	recSample(sample, std::string(k, '0'), k - 1, k);
	sort(sample.begin(), sample.end());
	sample.erase(unique(sample.begin(), sample.end()), sample.end());
	return sample;
}

//это создание таблицы изстинности,
//она как вектор стринг
//и содержит только те значения, при которых формула истинна
//например была формула (A->B)
//тогда в каждой строке возвращаемого верктора
//первый символ будет 1 или 0 - это варианты значения А
//второй будет тоже 1 или 0 - варинты значения B
std::vector<std::string>  createTruthTable(std::string formula) {
	std::string uniqueNames = getUniqueNames(formula);
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