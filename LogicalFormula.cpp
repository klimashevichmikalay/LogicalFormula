#include "LogicalFormula.h"
#include <sstream>

using namespace logics;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Лабораторные работы 1-2 по дисциплине ЛОИС
// Выполнены студентом группы 621702 БГУИР Климашевичем Н. А.
//// Автор всех методов, структур - студент группы 621702 БГУИР Климашевич Н. А. 
// Файл содержит реализации методов структуры, описанной в файле "LogicalFormula.h"
// Изменения проводились паралельно с файлом "LogicalFormula.h", описание версий описано там.
// Ссылки на источники описаны в файле "LogicalFormula.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//проферка на то, что алфавит верен в веденной формуле
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

//если неизвестные символы, то синтаксис неверен
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

//проверка, чтобы ве скобки симметрично закрывались
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

//вот если синтаксис не верен в предыдущих 3х функциях, то все, это не формула
bool LogicalFormula::isFormula() {
	return checkBracketsForEachSubtree(this);
}

//конструктор с начальными значениями NULL, и проферкой формулы
//_mapOfFormuls для того, чтобы одни формулы встраивались в другие
//например, A = (1!0)
//B = (0->A)
//C = (A|B) - A и  B, кооторые мы создали только что
//D = ((0->C)~A) - C, A,B, которые мы создали раньше
//и тд
//вот эта _mapOfFormuls и содержит различные формулы и их имена, в тестах есть примеры
LogicalFormula::LogicalFormula(const std::string &_formula, logics::symbol _name,
	std::map <logics::symbol, LogicalFormula> *_mapOfFormuls) {

	if (_mapOfFormuls != NULL) {
		this->mapOfFormuls = new (std::map <logics::symbol, LogicalFormula>);
		*(this->mapOfFormuls) = *(_mapOfFormuls);
	}
	//записть имени как строки
	formula = _formula;
	//корректен ли синтаксис?
	isCorrectFormula = (checkConstants(formula) == 0 && checkBrackets(formula) == 0);
	//это имя формулы, если мы заходим ее вставить в другую формулу
	name = _name;
	left = NULL;
	right = NULL;
	if (isCorrectFormula)
		//если формула корректна, то разбиваем на двоичное дерево
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
//это разбиение отрицания, нужно регулярное выражение на самом деле
//если отрицание, то левое поддерево отсается NULL,
//а правое будет содержать тип отрицание(NEGATION в перечислении)
void LogicalFormula::splitNegation(const std::string &_formula) {
	value = NEGATION;
	rightSubFormula = _formula.substr(1, _formula.length() - 1);
	right = new LogicalFormula(rightSubFormula, logics::NO_NAME, this->mapOfFormuls);
	left = NULL;
	leftSubFormula = "";
	return;
}

//это мы ищем подформулу
//просто когда нашли две вовремя закрывающиеся скобки, это и есть подформула, ее начало
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


//конструктор копирования
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


//разбиение на подформулы, на дерево двоичное
//функция много раз рекурсивно вызывается, ка
//каждый раз получает новую подформулу и начинает работать с этой новой подформулой
//когда уже мы ее вызвали,   и она состои из 1 или 0, то это конец, и мы можем записать самый конец
//дерева: правду или ложь
void LogicalFormula::splitIntoSubFormulas(const std::string &_formula) {

	//если в формуле остался один символ из 1 или 0, то тип подформулы правда или ложь
	if (_formula.length() == 1) {
		_formula[0] == '0' ? value = LIE : value = TRUTH;

		//если там другая буква, то значит что это 
		//другая формула является переменной этой формулы, эту другую формулу тоже разбиваем на подформулы
		if (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", _formula[0]))
			splitPropositionalVariable();
		return;
	}
	//если отрицание, тип подформулы - отрицание , в перечислении - NEGATION, 
	//отюрасываем значек ! и разбиваем дальше
	if (_formula[0] == '!') {
		splitNegation(_formula);
		return;
	}

	//если скобки, просто убираем их, стивим тип "скобки"(в перечислении это BRACETS)
	//и разбиваем подформулу, которая такая же, но без скобок
	if (_formula[_formula.length() - 1] == ')') {
		splitWithBrackets(_formula);
		return;
	}
	else {
		//если в формуле только один один символ алфавита 
		splitSinglesValue(_formula);
		return;
	}
}


//создаются левое  и правое поддерево
void LogicalFormula::createChildred() {
	if (leftSubFormula != "")
		left = new LogicalFormula(leftSubFormula, logics::NO_NAME, this->mapOfFormuls);

	if (rightSubFormula != "")
		right = new LogicalFormula(rightSubFormula, logics::NO_NAME, this->mapOfFormuls);
}

//разбиение скобок,кратко описано выше в LogicalFormula::splitIntoSubFormulas(const std::string &_formula) 
void LogicalFormula::splitWithBracketsWithNegation(const std::string &_formula, int &pos) {
	pos--;
	rightSubFormula = _formula.substr(pos);

	if (pos > 2 && _formula[pos - 1] == '>' && _formula[pos - 2] == '-')
		leftSubFormula = _formula.substr(0, pos - 2);

	else if (pos > 1) {
		leftSubFormula = _formula.substr(0, pos - 1);
	}
	setType(_formula, pos);
	//разбили на подформулы, потом
	//содаем новые классы  LOgicalFormula для левого  поддерева и правого
	//в createChildred() вызываются конструктроры для новых формул,
	//и новые формулы точно так же разбиваются на подформулы-деревья,
	//пока в конструктор не попадет 1 или 0, это будет конец рекурсии
	createChildred();
	return;
}

//разбиение скобок ,кратко описано выше в LogicalFormula::splitIntoSubFormulas(const std::string &_formula) 
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

//разбиение скобок перед которыми отрицание,
//кратко описано выше в LogicalFormula::splitIntoSubFormulas(const std::string &_formula) 

void LogicalFormula::splitWithBrackets(const std::string &_formula) {
	int pos = getPosForSplit(_formula);

	if (pos > 0 && _formula[pos - 1] == '!')
		splitWithBracketsWithNegation(_formula, pos);
	else
		splitWithBracketsWithoutNegation(_formula, pos);
	return;
}

//при создании формулы  указываем тип, конъюнкция, отрицание или и тд.
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

//когда в конструктор попала формула из одного символа
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


//вот подсчет значения формулы
//выше было создано дерево
//сейчас мы рекурсивно для каждого поддерева, LEFT и RIGHT вызываем взять результать
//и когда мы натолкнемся на TRUTH мы вернем правду в вышестоящее дерево
//оно вернет дальше, как-то сравнит и так выше по дереву до  возвращения результата
//формулой, которая вызвала эту функцию
bool LogicalFormula::getResult() {
	switch (value)
	{
		//если тип формулы правда - просто возврат прады
	case TRUTH:	return true;
		break;

	case CONJUNCTION:
		//если конъюнкция,
		//то девая и правая подформула должны  быть равны
		if (left->getResult() && right->getResult()) return true;
		break;

	case DISJUNCTION:
		//если дизнъюнкция и если или левая подформула рекурсивна вернула тру, или травая, //
		//тогда возврат тру и тд.д
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


//рекурсивная проверка на то, что формулы конъюкт
//рекурсия до тех пор,
//пока не натолкнемся на литерал или конец дерева(NULL)
bool LogicalFormula::isСonjunct(const LogicalFormula* const _formula) {
	if (_formula == NULL || isLiteral(_formula))
		return true;
	if (_formula->value != BRACKETS && _formula->value != CONJUNCTION)
		return false;

	return (isСonjunct(_formula->left) && isСonjunct(_formula->right));
}

//просто проверка, является ли это литералом - одним знаком из алфавита
//
bool LogicalFormula::isLiteral(const LogicalFormula* const _formula) {
	switch (_formula->formula.length()) {
	case 1://добавить комменты
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


//проверка на днф
//рекурсивно проверяем, состоят ли поддеревья из конъюнктов или литератов
bool  LogicalFormula::isDNF(const LogicalFormula* const _formula)
{
	if (!isFormula())
		return false;

	if (_formula == NULL || isСonjunct(_formula))
		return true;

	if (_formula->value != BRACKETS && _formula->value != DISJUNCTION)
		return false;

	return (isDNF(_formula->left) && isDNF(_formula->right));
}


//если мы хотим построит СДНФ, и в формуле много оди-
//наковых символов, то убираем дубликаты
//например
//для формулы ((A|B)->A) вернет строку "AB"
std::string LogicalFormula::getUniqueNames() {
	std::string result;
	for (size_t i = 0; i < formula.length(); i++)
		if (!strchr("01", formula[i]) && strchr(alphabet.c_str(), formula[i]) && (!strchr(result.c_str(), formula[i])))
			result += formula[i];

	return result;
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

//это создание таблицы изстинности,
//она как вектор стринг
//и содержит только те значения, при которых формула истинна
//например была формула (A->B)
//тогда в каждой строке возвращаемого верктора
//первый символ будет 1 или 0 - это варианты значения А
//второй будет тоже 1 или 0 - варинты значения B
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

//после получения таблицы истинности
//мы берем из нее значения, когда формула истинна,
//и строим днф, если в таблице переменная равна 0, а результат формулы истина, то записы
//ваем этот элемент с отрицанием и тд
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