/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Лабораторные работы №1( вариант - f) и №2(вариант -9)по дисциплине ЛОИС.
// Выполнены студентом группы 621702 БГУИР Климашевичем Н. А. 
// Автор всех методов, структур - студент группы 621702 БГУИР Климашевич Н. А. 
// В файле содержится описание структуры данных(двоичное деревое, реализованное с помощью класса) для хранения во
// время работы программы, ввода и обработки логической формулы.
// Версии изменения программы(источник изменений - https://github.com/klimashevichmikalay/LogicalFormula/commits/master 
// (ссылка на репозиторий на гитхабе студента группы 621702 БГУИР Климашевича Н. А. ).
// 07.02.2019 - создание проекта
// 08.02.2019 - с помощью класса "LogicalFormula" реализовано хранение формулы
// 09.02.2019 - реализовано вычисление значения формулы, реализованы пропозициональные переменные
// 10.02.2019 - реализована проверка формулы на ДНФ
// 11.02.2019 - придуман мною и реализован алгоритм по нахождению всех упорядоченных выборок 0 и 1
// заданной мощности, реализовано построение таблицы истинности и построение СДНФ. Проект загружен на
// удаленный репозиторий.
// 12.02.2019 удалены или подкорректированы некоторые функции, добавлено 30 тестов
// 13-14.02.2019 - добавлено еще 60 тестов, итого ~ 97 тестов для первой и второй л.р.
// 26.03.2019 - добавлены комментарии и добалнен более удобный для чтения вывод результата выполнения программы
// Автор всех реализованных алгоритмов - Климашевич Н. А., студент группы  621702
// Источники литературы:
// 1)Методические пособия по л.р. №1 и №2 курса ЛОИС специальности ИИ, УО БГУИР. Автор - Ивашенко В.П.
// 2)Логика для студентов. Автор - Малыхина.
// 3)Курс лекций по ЛОИС. Автор - Ивашенко В. П.
// 4)Ю.И. Галушкина, А.Н. Марьямов: Конспект лекций по дискретной математике
// 5)Методические материалы к л.р. по курсу АОИС. Автор - Качков. В. П.
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

const std::string  alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ01";
//алфавит наш
enum symbol { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, NO_NAME };
//это типы
//LIE -  ложь для конъюнкта
//TRUTH - правла для конъюнкта
//BRACKETS - скобки, без них можно обойтись
//остальное - операции
enum type { LIE = 0, TRUTH, CONJUNCTION, DISJUNCTION, IMPLICATION, EQUIVALENT, NEGATION, BRACKETS };

class LogicalFormula {

public:
	//каждая формула может иметь имя, для того, чтобы она стала частью другой формулы
	//например, A = ((1&0)->0) - это формула A
	//затем формула B = (A->(1|0))
	//по умолчанию формула не имеет имени и состоит из 1 и 0, и разных &,!,->, ~ и тд
	LogicalFormula(const std::string &_formula,//+
		symbol _name = NO_NAME,
		std::map <symbol, LogicalFormula> *_mapOfFormuls = NULL);
	//конструктор копирования
	LogicalFormula(const LogicalFormula &obj);
	//получить формулу как строку
	std::string getFormula() { return formula; };
	//почитать истинность или ложность формулы
	bool getResult();	
	//проверка синтаксиса на отсутствие символов не из алфавита и кванторов и
	//на симметричное закрытие скобок
	bool isFormula();
	type getType() { return value; };
	LogicalFormula* getLeft() { return left; };
	LogicalFormula* getRight() { return right; };

private:
	bool isCorrectFormula;
	//имя формулы A, B,C и тд. для того чтобы вставить ее в другую формулу
	symbol name;
	//сама формула, например "((1->0)~0)"
	std::string formula;
	//формула разбивается на двоичный информационный граф
	//это левая подформула
	LogicalFormula* left = NULL;
	//это правая
	/*
	например такая формула  (A~(B|(A->0)))
	будет иметь в left A, а в right (B|(A->0)).
	В этом же right тоже будет левая подформула и правая.
	В левой будет B, в правой ((A->0))
	и т.д. пока не остануться литералы, потом при расчета значений
	просто берем значение этого литерала
	*/
	LogicalFormula* right = NULL;
	//ну это запись левая и правая подформулы как строки
	std::string rightSubFormula;
	std::string leftSubFormula;
	//для построения таблицы истинности, дальше будет подробнее
	std::map <symbol, LogicalFormula> *mapOfFormuls = NULL;
	type value;	
	//дальше это разбор созданной строки-формулы
	void splitNegation(const std::string &_formula);
	void splitWithBrackets(const std::string &_formula);
	void splitSinglesValue(const std::string &_formula);
	void splitIntoSubFormulas(const std::string &_formula);
	void splitWithBracketsWithNegation(const std::string &_formula, int &pos);
	void splitWithBracketsWithoutNegation(const std::string &_formula, int &pos);
	void createChildred();
	void setType(const std::string &_formula, const int &pos);
	void splitPropositionalVariable();
	bool checkBracketsForEachSubtree(LogicalFormula* lf);
};
#endif 

