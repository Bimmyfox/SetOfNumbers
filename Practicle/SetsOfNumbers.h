/*
* Класс для представления массива множеств из n числа элементов
* содержит функции:
* добавления множества в массив
* вывода массива на экран
* сортировки массива по количеству элементов в множествах
* нахождения числа одинаковых(равных) множеств
*/
#pragma once
#include "SetOfNumbers.h"

class SetsOfNumbers {

private:
	//хранит количество созданных множеств
	int numSet = 0;
	//массив множеств
	SetOfNumbers *arrayS;

public:
	void addSetOfNumbers(SetOfNumbers&); //добавление множества в массив
	void outputMonitor(); //вывод на экран
						  //быстрая сортировка по количеству элементов в множествах
	void sortByNumberElements(int left, int righ);
	int numberEqualArrays(); // число равных множеств
	void unionSets(); //сумма всех элементов массива

					  //конструкторы и деструктор
	SetsOfNumbers();
	SetsOfNumbers(int);
	~SetsOfNumbers();
};


//====конструкторы и деструктор====
/*
* по умолчанию
* содаёт пустой массив
*/
SetsOfNumbers::SetsOfNumbers() {
	arrayS = new SetOfNumbers[0];
}

/*
* создаёт массив с заданным числом элементов
* аргумент number - число элементов
*/
SetsOfNumbers::SetsOfNumbers(int number) {
	arrayS = new SetOfNumbers[number];
}

SetsOfNumbers::~SetsOfNumbers() {
	delete[] arrayS;
}




//====функции====
/*
* Функция добавляет множестство в массив
* аргумент: экземпляр класса SetOfNumbers
*/
void SetsOfNumbers::addSetOfNumbers(SetOfNumbers &setOfNum) {
	setOfNum.getSetOfNumbers();
	arrayS[numSet].setSetOfNumbers(setOfNum);
	arrayS[numSet].setNumberElements(setOfNum.getNumberElements());
	//увеличиваем количество элементов в массиве
	numSet++;
}

/*
* Функция выводит на экран весь массив
*/
void SetsOfNumbers::outputMonitor() {
	cout << "\n";
	for (int i = 0; i < numSet; i++) {
		if (arrayS[i].getNumberElements() != 0) 
			arrayS[i].outputMonitor();
	}
	cout << endl;
}

/*
* Функция сортирует массив по количеству элементов в множествах
* методом быстрой сортировки по возрастанию
* аргументы: left - левый элемент массива, rigth - правый
*/
void SetsOfNumbers::sortByNumberElements(int left, int right) {

	int i = left, j = right;
	//середина
	int x = arrayS[(left + right) / 2].getNumberElements();

	while (i <= j) {
		while (arrayS[i].getNumberElements() < x) i++;
		while (arrayS[j].getNumberElements() > x) j--;

		if (i <= j) {
			//хранит размер множества, которое будем менять
			int size = arrayS[i].getNumberElements();
			int *tmp = new int[size];
			//хранит множество
			tmp = arrayS[i].getSetOfNumbers();
			arrayS[i].setSetOfNumbers(arrayS[j].getSetOfNumbers(), arrayS[j].getNumberElements());
			arrayS[j].setSetOfNumbers(tmp, size);
			//поменяли, освобождаем Добби и обнуляем size
			delete[] tmp;
			size = 0;
			i++;
			j--;
		}
	}
	//рекурсия
	if (i < right) sortByNumberElements(i, right);
	if (left < j) sortByNumberElements(left, j);
}

/*
* Функция вычисляет количество равных множеств
* возвращает найденное значение
*/
int SetsOfNumbers::numberEqualArrays() {
	// число одинаковых = 1, потому что
	int numberEqual = 1;

	// если множество является подмножеством и число элементов
	// в них совпадает, то они равны
	for (int i = 0; i < numSet - 1; i++) {
		for (int j = numSet; j > i; j--) {
			if (arrayS[i].chekSubset(arrayS[j]) &&
				arrayS[i].getNumberElements() == arrayS[j].getNumberElements()) {
				numberEqual++;
			}
		}
	}
	return numberEqual;
}

/*
* Функция считает сумму элементов массива
* возвращает вычисленное значение
*/
void SetsOfNumbers::unionSets() {
	int sum = 0;
	for (int i = 0; i < numSet - 1; i++) {
		arrayS[i + 1].unionMas(arrayS[i]);
		arrayS[i].setSetOfNumbers(NULL, NULL);
	}
	arrayS[0].setSetOfNumbers(arrayS[numSet - 1].getSetOfNumbers(), arrayS[numSet - 1].getNumberElements());
	arrayS[numSet - 1].setSetOfNumbers(NULL, NULL);
}