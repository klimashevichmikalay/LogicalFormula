/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Тесты к лабораторным работам 1-2 по дисциплине ЛОИС
// Написаны студентом группы 621702 БГУИР Климашевичем Н. А.
// Автор всех тестов - студент группы 621702 БГУИР Климашевич Н. А. 
// Файл содержит тесты к лабораторным работам 1-2 по ЛОИС
// Изменения описаны в файле "LogicalFormula.h"
// Источник идеи: статья на хабре "Юнит-тестирование для чайников"
// ссылка статьи: https://habr.com/ru/post/169381/
// автор статьи: Максим Аршинов.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <cassert>
#include "LogicalFormula.h"
using namespace std;
using namespace logics;


void testResult1() {
	cout << "testResult1\n";
	LogicalFormula formula("1");
	assert(formula.getResult() == true);
}

void testResult2() {
	cout << "testResult2\n";
	LogicalFormula formula("0");
	assert(formula.getResult() == false);
}

void testResult3() {
	cout << "testResult3\n";
	LogicalFormula formula("(!1)");
	assert(formula.getResult() == false);
}

void testResult4() {
	cout << "testResult4\n";
	LogicalFormula formula("(!0)");
	assert(formula.getResult() == true);
}

void testResult5() {
	cout << "testResult5\n";
	LogicalFormula formula("(0|1)");
	assert(formula.getResult() == true);
}

void testResult6() {
	cout << "testResult6\n";
	LogicalFormula formula("(0&1)");
	assert(formula.getResult() == false);
}

void testResult7() {
	cout << "testResult7\n";
	LogicalFormula formula("(1~1)");
	assert(formula.getResult() == true);
}

void testResult8() {
	cout << "testResult8\n";
	LogicalFormula formula("(0~0)");
	assert(formula.getResult() == true);
}

void testResult9() {
	cout << "testResult9\n";
	LogicalFormula formula("(1->1)");
	assert(formula.getResult() == true);
}

void testResult10() {
	cout << "testResult10\n";
	LogicalFormula formula("(0->0)");
	assert(formula.getResult() == true);
}

void testResult11() {
	cout << "testResult11\n";
	LogicalFormula formula("(0->1)");
	assert(formula.getResult() == true);
}

void testResult12() {
	cout << "testResult12\n";
	LogicalFormula formula("(1~0)");
	assert(formula.getResult() == false);
}

void testResult13() {
	cout << "testResult13\n";
	LogicalFormula formula("((!1)~0)");
	assert(formula.getResult() == true);
}

void testResult14() {
	cout << "testResult14\n";
	LogicalFormula formula("(((1~1)&0)~1)");
	assert(formula.getResult() == false);
}

void testResult15() {
	cout << "testResult15\n";
	LogicalFormula formula("((1|0)->0)");
	assert(formula.getResult() == false);
}

void testResult16() {
	cout << "testResult16\n";
	LogicalFormula formula1("(1|0)");//true
	LogicalFormula formula2("(1->0)");//false	

	map <logics::symbol, LogicalFormula> _mapOfFormuls = { { logics::A , formula1 },{ logics::B, formula2 } };
	LogicalFormula formula("(A&B)", logics::NO_NAME, &_mapOfFormuls);
	assert(formula.getResult() == false);
}

void testResult17() {
	cout << "testResult17\n";
	LogicalFormula formula1("(1|0)");//true
	LogicalFormula formula2("(1->0)");//false

	map <logics::symbol, LogicalFormula> _mapOfFormuls =
	{ { logics::A , formula1 },{ logics::B, formula2 } };
	LogicalFormula formula("(A~B)", logics::NO_NAME, &_mapOfFormuls);

	assert(formula.getResult() == false);
}

void testResult18() {
	cout << "testResult18\n";

	LogicalFormula formula1("(1|0)");//true
	LogicalFormula formula2("(1->0)");//false
	map <logics::symbol, LogicalFormula> _mapOfFormuls1 =
	{ { logics::A , formula1 },{ logics::B, formula2 } };
	LogicalFormula formula3("(A&B)", logics::NO_NAME, &_mapOfFormuls1);//false

	LogicalFormula formula21("(1|0)");//true
	LogicalFormula formula22("(1->0)");//false
	map <logics::symbol, LogicalFormula> _mapOfFormuls2 =
	{ { logics::D, formula21 },{ logics::C, formula22 } };
	LogicalFormula formula23("(C->D)", logics::NO_NAME, &_mapOfFormuls2);//true

	map <logics::symbol, LogicalFormula> _mapOfFormuls =
	{ { logics::F, formula3 },{ logics::E, formula23 } };
	LogicalFormula formula("(F->E)", logics::NO_NAME, &_mapOfFormuls);//true
	assert(formula.getResult() == true);
}

void testResult19() {
	cout << "testResult19\n";

	LogicalFormula formula1("(1|0)");//true
	LogicalFormula formula2("(1->0)");//false
	map <logics::symbol, LogicalFormula> _mapOfFormuls1 =
	{ { logics::A , formula1 },{ logics::B, formula2 } };
	LogicalFormula formula3("(A~B)", logics::NO_NAME, &_mapOfFormuls1);//false

	LogicalFormula formula21("(1|0)");//true
	LogicalFormula formula22("(1&0)");//false
	map <logics::symbol, LogicalFormula> _mapOfFormuls2 =
	{ { logics::D, formula21 },{ logics::C, formula22 } };
	LogicalFormula formula23("(C->D)", logics::NO_NAME, &_mapOfFormuls2);//true

	//A - false, B - true
	map <logics::symbol, LogicalFormula> _mapOfFormuls =
	{ { logics::A, formula3 },{ logics::B, formula23 } };
	LogicalFormula formula("(((!A)~B)->1)", logics::NO_NAME, &_mapOfFormuls);//
	assert(formula.getResult() == true);
}

void testResult20() {
	cout << "testResult20\n";

	LogicalFormula formula1("(1&1)");//true
	LogicalFormula formula2("(!(1|0))");//false
	map <logics::symbol, LogicalFormula> _mapOfFormuls1 =
	{ { logics::A , formula1 },{ logics::B, formula2 } };
	LogicalFormula formula3("(A~B)", logics::NO_NAME, &_mapOfFormuls1);//false

	LogicalFormula formula21("(0->0)");//true
	LogicalFormula formula22("(1->0)");//false
	map <logics::symbol, LogicalFormula> _mapOfFormuls2 =
	{ { logics::D, formula21 },{ logics::C, formula22 } };
	LogicalFormula formula23("(C->D)", logics::NO_NAME, &_mapOfFormuls2);//true
																			   //A - false, B - true
	map <logics::symbol, LogicalFormula> _mapOfFormuls =
	{ { logics::A, formula3 },{ logics::B, formula23 } };
	LogicalFormula formula("((((!A)~B)->1)&0)", logics::NO_NAME, &_mapOfFormuls);//
	assert(formula.getResult() == false);
}



void testSyntax1() {
	cout << "\ntestSyntax1\n";
	LogicalFormula formula("((1|0)->0)");
	assert(formula.isFormula() == true);
}

void testSyntax2() {
	cout << "testSyntax2\n";
	LogicalFormula formula("((1|0)->0))");
	assert(formula.isFormula() == false);
}

void testSyntax3() {
	cout << "testSyntax3\n";
	LogicalFormula formula("(0)");
	assert(formula.isFormula() == true);
}

void testSyntax4() {
	cout << "testSyntax4\n";
	LogicalFormula formula("(10)");
	assert(formula.isFormula() == false);
}

void testSyntax5() {
	cout << "testSyntax5\n";
	LogicalFormula formula("(1!0)");
	assert(formula.isFormula() == false);
}

void testSyntax6() {
	cout << "testSyntax6\n";
	LogicalFormula formula("(A->B)");
	assert(formula.isFormula() == true);
}

void testSyntax7() {
	cout << "testSyntax7\n";
	LogicalFormula formula("(A!C)");
	assert(formula.isFormula() == false);
}

void testSyntax8() {
	cout << "testSyntax8\n";
	LogicalFormula formula("(A->B))");
	assert(formula.isFormula() == false);
}

void testSyntax9() {
	cout << "testSyntax9\n";
	LogicalFormula formula("A->B");
	assert(formula.isFormula() == false);
}

void testSyntax10() {
	cout << "testSyntax10\n";
	LogicalFormula formula("(A->B|C)");
	assert(formula.isFormula() == false);
}

void testSyntax11() {
	cout << "testSyntax11\n";
	LogicalFormula formula("(A->B|C)");
	assert(formula.isFormula() == false);
}

void testSyntax12() {
	cout << "testSyntax12\n";
	LogicalFormula formula("(A&C&E)");
	assert(formula.isFormula() == false);
}

void testSyntax13() {
	cout << "testSyntax13\n";
	LogicalFormula formula("(A&(C&E))");
	assert(formula.isFormula() == true);
}

void testSyntax14() {
	cout << "testSyntax14\n";
	LogicalFormula formula("!(A&(C&E))");
	assert(formula.isFormula() == false);
}

void testSyntax15() {
	cout << "testSyntax15\n";
	LogicalFormula formula("(!(A&(C&E)))");
	assert(formula.isFormula() == true);
}

void testSyntax16() {
	cout << "testSyntax16\n";
	LogicalFormula formula("(0)");
	assert(formula.isFormula() == true);
}

void testSyntax17() {
	cout << "testSyntax17\n";
	LogicalFormula formula("0");
	assert(formula.isFormula() == true);
}

void testSyntax18() {
	cout << "testSyntax18\n";
	LogicalFormula formula("!!(!(0&A))");
	assert(formula.isFormula() == false);
}

void testSyntax19() {
	cout << "testSyntax19\n";
	LogicalFormula formula("(!(!(!(0&A))))");
	assert(formula.isFormula() == true);
}

void testSyntax20() {
	cout << "testSyntax20\n";
	LogicalFormula formula("(A|B)");
	assert(formula.isFormula() == true);
}

void testSyntax21() {
	cout << "testSyntax21\n";
	LogicalFormula formula("(A|*)");
	assert(formula.isFormula() == false);
}

void testSyntax22() {
	cout << "testSyntax22\n";
	LogicalFormula formula("((A|C)&(0->1))");
	assert(formula.isFormula() == true);
}

void testSyntax23() {
	cout << "testSyntax23\n";
	LogicalFormula formula("!((A|C)&(0->1))");
	assert(formula.isFormula() == false);
}


void testSyntax24() {
	cout << "testSyntax24\n";
	LogicalFormula formula("((!(!((A|C)&(0->1))))->(K|(!(M->C))))");
	assert(formula.isFormula() == true);
}

void testSyntax25() {
	cout << "testSyntax25\n";
	LogicalFormula formula("((!(!((A|C)&(0->1))))->K|M->C)");
	assert(formula.isFormula() == false);
}

void testSyntax26() {
	cout << "testSyntax26\n";
	LogicalFormula formula("((((!A)&(!B))|((!A)&B))|(A&B))");
	assert(formula.isFormula() == true);
}

void testSyntax27() {
	cout << "testSyntax27\n";
	LogicalFormula formula("((!A)|A)");
	assert(formula.isFormula() == true);
}

void testSyntax28() {
	cout << "testSyntax28\n";
	LogicalFormula formula("((A->0)&0)");
	assert(formula.isFormula() == true);
}

void testSyntax29() {
	cout << "testSyntax29\n";
	LogicalFormula formula("(A->0)&0");
	assert(formula.isFormula() == false);
}

void testSyntax30() {
	cout << "testSyntax30\n";
	LogicalFormula formula("(((!A)&(!B))|((!A)&B))");
	assert(formula.isFormula() == true);
}

void testSyntax31() {
	cout << "testSyntax31\n";
	LogicalFormula formula("(((!A)&(!B))|(!A&B))");
	assert(formula.isFormula() == false);
}

void testSyntax32() {	
	cout << "testSyntax32\n";
	LogicalFormula formula("(!(!(!(!(!(!(!(!(!(!(!A)))))))))))");
	assert(formula.isFormula() == true);
}

void testSyntax33() {
	cout << "testSyntax33\n";
	LogicalFormula formula("     ");
	assert(formula.isFormula() == false);
}


void testSyntax34() {
	cout << "testSyntax34\n";
	LogicalFormula formula("");
	assert(formula.isFormula() == false);
}

void testSyntax35() {
	cout << "testSyntax35\n";
	LogicalFormula formula("(!(1&0))");
	assert(formula.isFormula() == true);
}


void testIsLiteral1() {
	cout << "\ntestIsLiteral1\n";
	LogicalFormula formula("A");
	assert(formula.isLiteral(&formula) == true);
}

void testIsLiteral2() {
	cout << "testIsLiteral2\n";
	LogicalFormula formula("0");
	assert(formula.isLiteral(&formula) == true);
}

void testIsLiteral3() {
	cout << "testIsLiteral3\n";
	LogicalFormula formula("!B");
	assert(formula.isLiteral(&formula) == true);
}

void testIsLiteral4() {
	cout << "testIsLiteral4\n";
	LogicalFormula formula("!1");
	assert(formula.isLiteral(&formula) == true);
}

void testIsLiteral5() {
	cout << "testIsLiteral5\n";
	LogicalFormula formula("(!1)");
	assert(formula.isLiteral(&formula) == false);
}

void testIsLiteral6() {
	cout << "testIsLiteral6\n";
	LogicalFormula formula("(A)");
	assert(formula.isLiteral(&formula) == false);
}

void testIsLiteral7() {
	cout << "testIsLiteral7\n";
	LogicalFormula formula("(A&B)");
	assert(formula.isLiteral(&formula) == false);
}

void testIsLiteral8() {
	cout << "testIsLiteral8\n";
	LogicalFormula formula("A&B");
	assert(formula.isLiteral(&formula) == false);
}

void testIsConjunct1() {
	cout << "\ntestIsConjunct1\n";
	LogicalFormula formula("A");
	assert(formula.isСonjunct(&formula) == true);
}

void testIsConjunct2() {
	cout << "testIsConjunct2\n";
	LogicalFormula formula("(A&B)");
	assert(formula.isСonjunct(&formula) == true);
}

void testIsConjunct3() {
	cout << "testIsConjunct3\n";
	LogicalFormula formula("(A&1)");
	assert(formula.isСonjunct(&formula) == true);
}

void testIsConjunct4() {
	cout << "testIsConjunct4\n";
	LogicalFormula formula("0&1");
	assert(formula.isСonjunct(&formula) == true);
}

void testIsConjunct5() {
	cout << "testIsConjunct5\n";
	LogicalFormula formula("1");
	assert(formula.isСonjunct(&formula) == true);
}

void testIsConjunct6() {
	cout << "testIsConjunct6\n";
	LogicalFormula formula("(1&((1&A)&0))");
	assert(formula.isСonjunct(&formula) == true);
}

void testIsConjunct7() {
	cout << "testIsConjunct7\n";
	LogicalFormula formula("(1&((1&A)|0))");
	assert(formula.isСonjunct(&formula) == false);
}

void testIsConjunct8() {
	cout << "testIsConjunct8\n";
	LogicalFormula formula("(1&((1->A)&0))");
	assert(formula.isСonjunct(&formula) == false);
}

void testSample1() {
	cout << "\ntestSample1\n";
	LogicalFormula formula("(1)");
	vector<string> test = formula.createBoolSample(4);
	assert(test.size() == 16);
}

void testSample2() {
	cout << "testSample2\n";
	LogicalFormula formula("(1)");
	vector<string> test = formula.createBoolSample(5);

	assert(test.size() == 32);
}

void testSample3() {
	cout << "testSample3\n";
	LogicalFormula formula("(1)");
	vector<string> test = formula.createBoolSample(9);

	assert(test.size() == 512);
}

void testSample4() {
	cout << "testSample4\n";
	LogicalFormula formula("(1)");
	vector<string> test = formula.createBoolSample(7);

	assert(test.size() == 128);
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////                                                    //////
//////      Тесты для:                                    //////
//////      Лабораторная работа №1,                       //////
//////      Вариант F: проверить является ли формула ДНФ  //////
//////                                                    //////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void testIsDNF1() {
	cout << "\ntestIsDNF1\n";
	LogicalFormula formula("A");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF2() {
	cout << "testIsDNF2\n";
	LogicalFormula formula("1");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF3() {
	cout << "testIsDNF3\n";
	LogicalFormula formula("(A|B)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF4() {
	cout << "testIsDNF4\n";
	LogicalFormula formula("(A~B)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF5() {
	cout << "testIsDNF5\n";
	LogicalFormula formula("(A->B)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF6() {
	cout << "testIsDNF6\n";
	LogicalFormula formula("(A&B)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF7() {
	cout << "testIsDNF7\n";
	LogicalFormula formula("(!A)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF8() {
	cout << "testIsDNF8\n";
	LogicalFormula formula("(!(A&B))");
	assert(formula.isDNF(&formula) == false);
}



void testIsDNF9() {
	cout << "testIsDNF9\n";
	LogicalFormula formula("((A|B)|C)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF10() {
	cout << "testIsDNF10\n";
	//                     (   ( (!A)|(!B) ) |  (!C)   )
	LogicalFormula formula("(((!A)|(!B))|(!C))");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF11() {
	cout << "testIsDNF11\n";
	//                      (   !( (A|B)|C )   )
	LogicalFormula formula("(!((A|B)|C))");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF12() {
	cout << "testIsDNF12\n";
	//                     (   !(A|B)   )
	LogicalFormula formula("(!(A|B))");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF13() {
	cout << "testIsDNF13\n";
	//                      ( (A->B)&C )
	LogicalFormula formula("((A->B)&C)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF14() {
	cout << "testIsDNF14\n";
	//                      (   (A&B) | (!A)   )
	LogicalFormula formula("((A&B)|(!A))");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF15() {
	cout << "testIsDNF15\n";
	//                      (   (!A)~(!B)   )
	LogicalFormula formula("((!A)~(!B))");
	assert(formula.isDNF(&formula) == false);
}



void testIsDNF16() {
	cout << "testIsDNF16\n";
	//                      (    (  A&( B&(!C) )  ) | (  ((!D)&(E&F)  ) | B)    )
	LogicalFormula formula("((A&(B&(!C)))|(((!D)&(E&F))|B))");
	assert(formula.isDNF(&formula) == true);
}



void testIsDNF17() {
	cout << "testIsDNF17\n";
	//                     (   A | (B & (C|D)  )   )
	LogicalFormula formula("(A|(B&(C|D)))");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF18() {
	cout << "testIsDNF18\n";
	//                      (   D | (A->(B&C) )  )
	LogicalFormula formula("(D|(A->(B&C)))");
	assert(formula.isDNF(&formula) == false);
}



void testIsDNF19() {
	cout << "testIsDNF19\n";
	//                      (   (A | (B&C)) | (B&D)    )
	LogicalFormula formula("((A|(B&C))|(B&D))");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF20() {
	cout << "testIsDNF20\n";
	//                      (  (A | (B&C)) | (!B)   )
	LogicalFormula formula("((A|(B&C))|(!B))");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF21() {
	cout << "testIsDNF21\n";
	LogicalFormula formula("((A|(B&C))|(!B)|M)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF22() {
	cout << "testIsDNF22\n";
	LogicalFormula formula("(A|C|D)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF23() {
	cout << "testIsDNF23\n";
	LogicalFormula formula("((A|C)|D)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF24() {
	cout << "testIsDNF24\n";
	LogicalFormula formula("(1&0&A|C|0&M)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF25() {
	cout << "testIsDNF25\n";
	LogicalFormula formula("((1&(0&A))|(C|(0&M)))");
	assert(formula.isDNF(&formula) == true);
}

/////////////////////////////////////////////////////
///Тесты для:                                     ///
///Лабораторная работа №2,                        ///
///Вариант F: построить СДНФ для заданной формулы ///
///                                               ///
/////////////////////////////////////////////////////
void testCreatePDNF1() {
	cout << "\ntestCreatePDNF1\n";
	LogicalFormula formula("(A|B)");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (  ( ((!A)&B) | (A&(!B))) | (A&B)   )
	assert(!(pdnf.getFormula().compare("((((!A)&B)|(A&(!B)))|(A&B))")));
}

void testCreatePDNF2() {
	cout << "testCreatePDNF2\n";
	LogicalFormula formula("(!(A|B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                 (  (!A)&(!B)  )
	assert(!(pdnf.getFormula().compare("((!A)&(!B))")));
}

void testCreatePDNF3() {
	cout << "testCreatePDNF3\n";
	LogicalFormula formula("(A|(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  ( ( ((!A)&(!B)) | (A&(!B))) | (A&B)   )
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|(A&(!B)))|(A&B))")));
}

void testCreatePDNF4() {
	cout << "testCreatePDNF4\n";
	LogicalFormula formula("((!A)|B)");
	LogicalFormula pdnf = formula.createPDNF();
	//                                 (  ( ((!A)&(!B)) | ((!A)&B)) | (A&B)   )
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|((!A)&B))|(A&B))")));
}

void testCreatePDNF5() {
	cout << "testCreatePDNF5\n";
	LogicalFormula formula("((!A)|(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (  ( ((!A)&(!B)) | ((!A)&B)) | (A&(!B))   )
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|((!A)&B))|(A&(!B)))")));
}

void testCreatePDNF6() {
	cout << "testCreatePDNF6\n";
	LogicalFormula formula("(A~B)");
	LogicalFormula pdnf = formula.createPDNF();
	//                                 (   ( (!A)&(!B) ) | (A&B)   )
	assert(!(pdnf.getFormula().compare("(((!A)&(!B))|(A&B))")));
}

void testCreatePDNF7() {
	cout << "testCreatePDNF7\n";
	LogicalFormula formula("(!(A~B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (   ((!A)&B) | (A&(!B))   )
	assert(!(pdnf.getFormula().compare("(((!A)&B)|(A&(!B)))")));
}

void testCreatePDNF8() {
	cout << "testCreatePDNF8\n";
	LogicalFormula formula("(A~(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (   ( (!A)&B ) | ( A&(!B) )   )
	assert(!(pdnf.getFormula().compare("(((!A)&B)|(A&(!B)))")));
}

void testCreatePDNF9() {
	cout << "testCreatePDNF9\n";
	LogicalFormula formula("((!A)~B)");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (   ((!A)&B) | (A&(!B))   )
	assert(!(pdnf.getFormula().compare("(((!A)&B)|(A&(!B)))")));
}

void testCreatePDNF10() {
	cout << "testCreatePDNF10\n";
	LogicalFormula formula("((!A)~(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (   ((!A)&(!B)) | (A&B)   )
	assert(!(pdnf.getFormula().compare("(((!A)&(!B))|(A&B))")));
}

void testCreatePDNF11() {
	cout << "testCreatePDNF11\n";
	LogicalFormula formula("(A->B)");
	LogicalFormula pdnf = formula.createPDNF();
	//                                 (   (((!A)&(!B)) | ((!A)&B)) | (A&B)   )
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|((!A)&B))|(A&B))")));
}

void testCreatePDNF12() {
	cout << "testCreatePDNF12\n";
	LogicalFormula formula("(!(A->B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  ( A&(!B) )
	assert(!(pdnf.getFormula().compare("(A&(!B))")));
}

void testCreatePDNF13() {
	cout << "testCreatePDNF13\n";
	LogicalFormula formula("(A->(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (  (((!A)&(!B)) | ((!A)&B)) | (A&(!B))   )
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|((!A)&B))|(A&(!B)))")));
}

void testCreatePDNF14() {
	cout << "testCreatePDNF14\n";
	LogicalFormula formula("((!A)->B)");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (   (((!A)&B) | (A&(!B))) | (A&B)   )
	assert(!(pdnf.getFormula().compare("((((!A)&B)|(A&(!B)))|(A&B))")));
}

void testCreatePDNF15() {
	cout << "testCreatePDNF15\n";
	LogicalFormula formula("((!A)->(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (   (((!A)&(!B)) | (A&(!B))) | (A&B)   )
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|(A&(!B)))|(A&B))")));
}

void testCreatePDNF16() {
	cout << "testCreatePDNF16\n";
	LogicalFormula formula("(A&B)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("(A&B)")));
}

void testCreatePDNF17() {
	cout << "testCreatePDNF17\n";
	LogicalFormula formula("(A&(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("(A&(!B))")));
}

void testCreatePDNF18() {
	cout << "testCreatePDNF18\n";
	LogicalFormula formula("((!A)&B)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("((!A)&B)")));
}

void testCreatePDNF19() {
	cout << "testCreatePDNF19\n";
	LogicalFormula formula("((!A)&(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("((!A)&(!B))")));
}

void testCreatePDNF20() {
	cout << "testCreatePDNF20\n";
	LogicalFormula formula("(!(A&B))");
	LogicalFormula pdnf = formula.createPDNF();
	//                                  (   (((!A)&(!B)) | ((!A)&B)) | (A&(!B))   )
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|((!A)&B))|(A&(!B)))")));
}

void testCreatePDNF21() {
	cout << "testCreatePDNF21\n";
	LogicalFormula formula("(!(!(!(!(A&B)))))");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("(A&B)")));
}

void testCreatePDNF22() {
	cout << "testCreatePDNF22\n";
	LogicalFormula formula("(!(!(!(!(!(A&B))))))");
	LogicalFormula pdnf = formula.createPDNF();
	//	((((!A)&(!B)) | ((!A)&B)) | (A&(!B)));
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|((!A)&B))|(A&(!B)))")));
}

void testCreatePDNF23() {
	cout << "testCreatePDNF23\n";
	LogicalFormula formula("((A->B)->C)");
	LogicalFormula pdnf = formula.createPDNF();   
	//(((((((!A)&(!B))&C) | (((!A)&B)&C)) | ((A&(!B))&(!C))) | ((A&(!B))&C)) | ((A&B)&C));
    assert(!(pdnf.getFormula().compare("(((((((!A)&(!B))&C)|(((!A)&B)&C))|((A&(!B))&(!C)))|((A&(!B))&C))|((A&B)&C))")));
}

void testCreatePDNF24() {
	cout << "testCreatePDNF24\n";
	LogicalFormula formula("((A->B)->(!C))");
	LogicalFormula pdnf = formula.createPDNF();	
	//(((((((!A)&(!B))&(!C)) | (((!A)&B)&(!C))) | ((A&(!B))&(!C))) | ((A&(!B))&C)) | ((A&B)&(!C)))
	assert(!(pdnf.getFormula().compare("(((((((!A)&(!B))&(!C))|(((!A)&B)&(!C)))|((A&(!B))&(!C)))|((A&(!B))&C))|((A&B)&(!C)))")));
}


void testCreatePDNF25() {
	cout << "testCreatePDNF25\n";
	LogicalFormula formula("((A&B)~C)");
	LogicalFormula pdnf = formula.createPDNF();
	//((((((!A)&(!B))&(!C)) | (((!A)&B)&(!C))) | ((A&(!B))&(!C))) | ((A&B)&C));
	assert(!(pdnf.getFormula().compare("((((((!A)&(!B))&(!C))|(((!A)&B)&(!C)))|((A&(!B))&(!C)))|((A&B)&C))")));
}

void testCreatePDNF26() {
	cout << "testCreatePDNF26\n";
	LogicalFormula formula("((A&C)~(!B))");
	LogicalFormula pdnf = formula.createPDNF();
	//((((((!A)&(!C))&B) | (((!A)&C)&B)) | ((A&(!C))&B)) | ((A&C)&(!B)));
	assert(!(pdnf.getFormula().compare("((((((!A)&(!C))&B)|(((!A)&C)&B))|((A&(!C))&B))|((A&C)&(!B)))")));
}

void testCreatePDNF27() {
	cout << "testCreatePDNF27\n";
	LogicalFormula formula("A|B&C)");
	LogicalFormula pdnf = formula.createPDNF();

	assert(!(pdnf.getFormula().compare("\nFormula has syntax error.")));
}

/////////////////////////////////////////////////////
///Тесты для:                                     ///
///Поиска ошибки  с 0 и 1                         /// 
/////////////////////////////////////////////////////

void testCreatePDNF28() {
	cout << "testCreatePDNF28\n";
	LogicalFormula formula("(A&0)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("")));
}

void testCreatePDNF29() {
	cout << "testCreatePDNF29\n";
	LogicalFormula formula("(A|0)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("A")));
}

void testCreatePDNF30() {
	cout << "testCreatePDNF30\n";
	LogicalFormula formula("((!A)&0)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("")));
}

void testCreatePDNF31() {
	cout << "testCreatePDNF31\n";
	LogicalFormula formula("((!A)&1)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("(!A)")));
}

void testCreatePDNF32() {
	cout << "testCreatePDNF32\n";
	LogicalFormula formula("((!A)|1)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("((!A)|A)")));
}

void testCreatePDNF33() {
	cout << "testCreatePDNF33\n";
	LogicalFormula formula("((!A)->1)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("((!A)|A)")));
}

void testCreatePDNF34() {
	cout << "testCreatePDNF34\n";
	LogicalFormula formula("(A~1)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("A")));
}

void testCreatePDNF35() {
	cout << "testCreatePDNF35\n";
	LogicalFormula formula("((A->0)~(B->1))");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("(((!A)&(!B))|((!A)&B))")));
}

void testCreatePDNF36() {
	cout << "testCreatePDNF36\n";
	LogicalFormula formula("((A->0)&0)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("")));
}


void testCreatePDNF37() {
	cout << "testCreatePDNF37\n";
	LogicalFormula formula("(A|1)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("((!A)|A)")));
}

void testCreatePDNF38() {
	cout << "testCreatePDNF38\n";
	LogicalFormula formula("(A~0)");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("(!A)")));
}

void testCreatePDNF39() {
	cout << "testCreatePDNF39\n";
	LogicalFormula formula("(!(A~0))");
	LogicalFormula pdnf = formula.createPDNF();
	assert(!(pdnf.getFormula().compare("A")));
}

void testCreatePDNF40() {
	cout << "testCreatePDNF40\n";
	LogicalFormula formula("((!(A~0))->B)");
	LogicalFormula pdnf = formula.createPDNF();
	//((((!A)&(!B)) | ((!A)&B)) | (A&B));
	assert(!(pdnf.getFormula().compare("((((!A)&(!B))|((!A)&B))|(A&B))")));
}

void testIsDNF26() {
	cout << "testIsDNF26\n";
	LogicalFormula formula("(1&A)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF27() {
	cout << "testIsDNF27\n";
	LogicalFormula formula("(1->A)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF28() {
	cout << "testIsDNF28\n";
	LogicalFormula formula("!(1->A)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF29() {
	cout << "testIsDNF29\n";
	LogicalFormula formula("((!A))");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF30() {
	cout << "testIsDNF30\n";
	LogicalFormula formula("(!A)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF31() {
	cout << "testIsDNF31\n";
	LogicalFormula formula("((!A)&0)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF32() {
	cout << "testIsDNF32\n";
	LogicalFormula formula("((A&0)|1)");
	assert(formula.isDNF(&formula) == true);
}

void testIsDNF33() {
	cout << "testIsDNF33\n";
	LogicalFormula formula("((A&0)->1)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF34() {
	cout << "testIsDNF34\n";
	LogicalFormula formula("(A&B&C|E)");
	assert(formula.isDNF(&formula) == false);
}

void testIsDNF35() {
	cout << "testIsDNF35\n";
	LogicalFormula formula("(((A&B)&C)|E)");
	assert(formula.isDNF(&formula) == true);
}

void(*tests[])() = {
testSyntax1,
testSyntax2,
testSyntax3,
testSyntax4,
testSyntax5,
testSyntax6,
testSyntax7,
testSyntax8,
testSyntax9,
testSyntax10,
testSyntax11,
testSyntax12,
testSyntax13,
testSyntax14,
testSyntax15,
testSyntax16,
testSyntax17,
testSyntax18,
testSyntax19,
testSyntax20,
testSyntax21,
testSyntax22,
testSyntax23,
testSyntax24,
testSyntax25,
testSyntax26,
testSyntax27,
testSyntax28,
testSyntax29,
testSyntax30,
testSyntax31,
testSyntax32,
testSyntax33,
testSyntax34,
testSyntax35,

testResult1,
testResult2,
testResult3,
testResult4,
testResult5,
testResult6,
testResult7,
testResult8,
testResult9,
testResult10,
testResult11,
testResult12,
testResult13,
testResult14,
testResult15,
testResult16,
testResult17,
testResult18,
testResult19,
testResult20,

testIsLiteral1,
testIsLiteral2,
testIsLiteral3,
testIsLiteral4,
testIsLiteral5,
testIsLiteral6,
testIsLiteral7,
testIsLiteral8,

testIsConjunct1,
testIsConjunct2,
testIsConjunct3,
testIsConjunct4,
testIsConjunct5,
testIsConjunct6,
testIsConjunct7,
testIsConjunct8,
testSample1,
testSample2,
testSample3,
testSample4,
//////////////////////////////////////////////
//////////////////////////////////////////////
///////////////////////////////////////////////
//тесты для лабораторной работа №1, вариант - F
///////////////////////////////////////////////
testIsDNF1,
testIsDNF2,
testIsDNF3,
testIsDNF4,
testIsDNF5,
testIsDNF6,
testIsDNF7,
testIsDNF8,
testIsDNF9,
testIsDNF10,
testIsDNF11,
testIsDNF12,
testIsDNF13,
testIsDNF14,
testIsDNF15,
testIsDNF16,
testIsDNF17,
testIsDNF18,
testIsDNF19,
testIsDNF20,
testIsDNF21,
testIsDNF22,
testIsDNF23,
testIsDNF24,
testIsDNF25,
testIsDNF26,
testIsDNF27,
testIsDNF28,
testIsDNF29,
testIsDNF30,
testIsDNF31,
testIsDNF32,
testIsDNF33,
testIsDNF34,
testIsDNF35,

//////////////////////////////////////////////
//конец тестов для лабораторной работы №1
//////////////////////////////////////////////


/////////////////////////////////////////////
/////////////////////////////////////////////
//тесты для лабораторной работа №2, вариант - 9
////////////////////////////////////////////
testCreatePDNF1,
testCreatePDNF2,
testCreatePDNF3,
testCreatePDNF4,
testCreatePDNF5,
testCreatePDNF6,
testCreatePDNF7,
testCreatePDNF8,
testCreatePDNF9,
testCreatePDNF10,
testCreatePDNF11,
testCreatePDNF12,
testCreatePDNF13,
testCreatePDNF14,
testCreatePDNF15,
testCreatePDNF16,
testCreatePDNF17,
testCreatePDNF18,
testCreatePDNF19,
testCreatePDNF20,
testCreatePDNF21,
testCreatePDNF22,
testCreatePDNF23,
testCreatePDNF24,
testCreatePDNF25,
testCreatePDNF26,
testCreatePDNF27,
testCreatePDNF28,
testCreatePDNF29,
testCreatePDNF30,
testCreatePDNF31,
testCreatePDNF32,
testCreatePDNF33,
testCreatePDNF34,
testCreatePDNF35,
testCreatePDNF36,
testCreatePDNF37,
testCreatePDNF38,
testCreatePDNF39,
testCreatePDNF40,

//конец тестов для лабораторной работы №2
NULL
};
