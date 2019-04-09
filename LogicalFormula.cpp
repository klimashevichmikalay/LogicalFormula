#include "LogicalFormula.h"
#include "Algorithms.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Лабораторные работы 1-2 по дисциплине ЛОИС
// Выполнены студентом группы 621702 БГУИР Климашевичем Н. А.
//// Автор всех методов, структур - студент группы 621702 БГУИР Климашевич Н. А. 
// Файл содержит реализации методов структуры, описанной в файле "LogicalFormula.h"
// Изменения проводились паралельно с файлом "LogicalFormula.h", описание версий описано там.
// Ссылки на источники описаны в файле "LogicalFormula.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//вот если синтаксис не верен в предыдущих 3х функциях, то все, это не формула
bool LogicalFormula::isFormula() {
	return (checkBracketsForEachSubtree(this));
}

//конструктор с начальными значениями NULL, и проферкой формулы
//_mapOfFormuls для того, чтобы одни формулы встраивались в другие
//например, A = (1!0)
//B = (0->A)
//C = (A|B) - A и  B, кооторые мы создали только что
//D = ((0->C)~A) - C, A,B, которые мы создали раньше
//и тд
//вот эта _mapOfFormuls и содержит различные формулы и их имена, в тестах есть примеры
LogicalFormula::LogicalFormula(const std::string &_formula, symbol _name,
	std::map <symbol, LogicalFormula> *_mapOfFormuls) {

	if (_mapOfFormuls != NULL) {
		this->mapOfFormuls = new (std::map <symbol, LogicalFormula>);
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

	if (lf == NULL)
		return true;

	if (!isCorrectFormula || !lf->isCorrectFormula || (isLiteral(lf) && strchr(formula.c_str(), '!') && !strchr(formula.c_str(), ')')))
		return false;

	if (isLiteral(lf) || (lf->left == NULL && lf->right == NULL))
		return true;

	if (lf->value != BRACKETS || lf->left != NULL)
	{
		return false;
	}

	if ((lf->left != NULL && !(lf->left->isCorrectFormula)) || (lf->right != NULL && !lf->right->isCorrectFormula))
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
	right = new LogicalFormula(rightSubFormula, NO_NAME, this->mapOfFormuls);
	left = NULL;
	leftSubFormula = "";
	return;
}

//конструктор копирования
LogicalFormula::LogicalFormula(const LogicalFormula &obj) {

	if (obj.mapOfFormuls != NULL) {

		this->mapOfFormuls = new (std::map <symbol, LogicalFormula>);
		*(this->mapOfFormuls) = *(obj.mapOfFormuls);
	}
	this->formula = obj.formula;
	this->isCorrectFormula = obj.isCorrectFormula;
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
	symbol _name = symbol(alphabet.find(formula[0]));

	if (mapOfFormuls != NULL)
		*this = mapOfFormuls->find(_name)->second;

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
	else
	{
		//если в формуле только один один символ алфавита 
		splitSinglesValue(_formula);
		return;
	}
}
//создаются левое  и правое поддерево
void LogicalFormula::createChildred() {
	if (leftSubFormula != "")
		left = new LogicalFormula(leftSubFormula, NO_NAME, this->mapOfFormuls);

	if (rightSubFormula != "")
		right = new LogicalFormula(rightSubFormula, NO_NAME, this->mapOfFormuls);
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