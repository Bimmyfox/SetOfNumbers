/*
* Демонстрирует работоспособность проектика
*/
#include "SetOfNumbers.h"
#include "SetsOfNumbers.h"
#include <iostream>


using namespace std;

void main() {
	system("chcp 1251");

	int sizeSet = 0;
	int size = 0;
	cout << "Введите число множеств: ";
	cin >> size;
	cout << "\n\n";

	SetsOfNumbers sets(size);
	
	//создаём множества и заполняем массив множеств
	for (int i = 0; i < size; i++) {
		cout << "Размер множества " << i + 1 << ": ";
		cin >> sizeSet;
		SetOfNumbers set(sizeSet);
		set.inputKeyboard();
		cout << "set" << i + 1 << ": ";
		set.outputMonitor();
		cout << "\n";
		sets.addSetOfNumbers(set);
	}

	cout << "\nМножество";
	sets.outputMonitor();

	sets.sortByNumberElements(0, size - 1);
	cout << "После сортировки: ";
	sets.outputMonitor();

	if (sets.numberEqualArrays() == 1) 
		cout << "\nЧисло одинаковых множеств: 0" << endl;
	else 	cout << "\nЧисло одинаковых множеств: " << sets.numberEqualArrays() << endl;

	sets.unionSets();
	cout << "\nОбъединение: ";
	sets.outputMonitor();
	system("pause");
}