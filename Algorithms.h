/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// файл с прототипами функций для обработки строк и алгоритмов с ЛФ для л.р. 1-2 по дисциплине ЛОИС
// написан студентом группы 621702 БГУИР Климашевичем Н. А.
// автор идей - студент группы 621702 БГУИР Климашевич Н. А. 
// файл содержит прототипы алгоритмов функций, используемых при обработке строк и для нахождения СДНФ и проверки ДНФ
// файл создан 09.04.2019
// последнее изменение - 09.04.2019
// источник информации - дисциплина ОАИП, автор - Гуревич А. В.; дисциплина ППВИС, автор - Романов В. И.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_
#include <sstream>
#include "LogicalFormula.h"
//создать СДНФ
LogicalFormula createPDNF(LogicalFormula lf);
//это создание всевозможных комбинаций из 1 и 0 к раз, вроде как массив сочетаний k раз из 1 и 0
std::vector<std::string> createBoolSample(size_t k);
//рекурсия при вычислени всех сочетаний нужного размера из 1 и 0
//нужно для таблицы истинности
void recSample(std::vector<std::string> &_sample, std::string str, size_t end, size_t k);
std::vector<std::string>  createTruthTable(std::string formula);
bool isDNF(LogicalFormula*  _formula, bool flag = false);
bool isСonjunct(LogicalFormula* _formula);
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