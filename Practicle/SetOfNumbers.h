/*
* Класс для представления множества из n числа элементов
* содержит функции:
* заполнения множества с клавиатуры и случайными числами
* вывод множества на экран
* объединения множеств
* проверки принадлежности числа множеству
* проверки: является ли множество под(над)множеством другого
*/
#pragma once
#include <iostream>
#include <ctime>
#include <malloc.h>

using namespace std;

class SetOfNumbers {

private:
	//число элементов в множестве
	int numberElements;
	//множество
	int *setOfNumbers;

public:
	//====функции====
	void inputRandom(); //заполнение "случайными" числами
	void inputKeyboard(); //ввод с клавиатуры
	void outputMonitor(); //вывод множества на экран
	void unionMas(SetOfNumbers&); //объединение множеств
	bool chekBelonging(int); //проверка принадлежности числа множеству
	bool chekSubset(SetOfNumbers&); //проверка: является ли множество под(над)множеством другого


	//=====гетторы и сетторы====
	//для количетва элементов
	int getNumberElements();
	void setNumberElements(int);

	//для элементов множества
	int* getSetOfNumbers();
	void setSetOfNumbers(SetOfNumbers&);
	void setSetOfNumbers(int*, int);


	//====конструкторы и деструктор====
	SetOfNumbers(); //по умолчанию
	SetOfNumbers(int); //с заданным числом элементов 
	~SetOfNumbers();
};




//=======================конструкторы и деструктор===============
/*
* конструктор по умолчанию
* задаёт число эелементов = 0
* создаёт пустое множество
*/
SetOfNumbers::SetOfNumbers() {
	numberElements = 0;
	setOfNumbers = (int*)malloc(0);
}

/*
* конструктор с заданным числом элементов:
* задаёт число эелементов = number
* создаёт множество c количеством элементов number
*/
SetOfNumbers::SetOfNumbers(int number) {
	numberElements = number;
	setOfNumbers = (int*)malloc(numberElements * sizeof(int));
}


SetOfNumbers::~SetOfNumbers() {
	free(setOfNumbers);
}




//==========================гетторы и сетторы====================
int SetOfNumbers::getNumberElements() {
	return numberElements;
}

void SetOfNumbers::setNumberElements(int number) {
	numberElements = number;
}

int* SetOfNumbers::getSetOfNumbers() {
	return setOfNumbers;
}

/*
* аргумент - экземпляр класса SetOfNumbers
*/
void SetOfNumbers::setSetOfNumbers(SetOfNumbers& setOfNum) {
	numberElements = setOfNum.numberElements;
	setOfNumbers = (int*)malloc(numberElements * sizeof(int));
	//заполняем множество элементами
	for (int i = 0; i < numberElements; i++)
		setOfNumbers[i] = setOfNum.setOfNumbers[i];
}

/*
* аргументы:
* *setOfNum - динамический массив с числами
* numElements - количество элементов в массиве
*/
void SetOfNumbers::setSetOfNumbers(int *setOfNum, int numElements) {
	numberElements = numElements;
	setOfNumbers = (int*)malloc(numberElements * sizeof(int));
	for (int i = 0; i < numberElements; i++) {
		setOfNumbers[i] = setOfNum[i];
	}
}




//==================функции======================
/*
* Функция заполняет множество случайными числами
*/
void SetOfNumbers::inputRandom() {
	srand(time_t(NULL));
	for (int i = 0; i < numberElements; i++) {
		setOfNumbers[i] = rand() % 100;
	}
}

/*
* Функция заполняет множество числами, введёнными с клавиатуры
*/
void SetOfNumbers::inputKeyboard() {
	cout << "Введите элементы множества: ";

	for (int i = 0; i < numberElements; i++) {
		cin >> setOfNumbers[i];
	}
	cout << endl;
}

/*
* Функция выводит на экран все элементы множества
*/
void SetOfNumbers::outputMonitor() {
	for (int i = 0; i < numberElements; i++) {
		cout << setOfNumbers[i] << " ";
	}
	cout << "\n";
}

/*
* Функция объединяет множество с переданным в аргумент множеством
* при объединении повторяющиеся элементы не записываются
*/
void SetOfNumbers::unionMas(SetOfNumbers &setOfNum) {
	int *setOfNumbers2;
	int a;
	int b;
	int c = 0;

	//копируем аргумент в setOfNumbers2
	int numberElements2 = setOfNum.numberElements;
	setOfNumbers2 = (int*)malloc(numberElements2 * sizeof(int));
	for (int i = 0; i < numberElements2; i++) {
		setOfNumbers2[i] = setOfNum.setOfNumbers[i];
	}

	//число элементов в новом множестве и его создание
	int size = numberElements + numberElements2;
	int *arrayTmp;
	arrayTmp = (int*)malloc(size * sizeof(int));

	if (numberElements2 > numberElements) {
		a = numberElements2;
		b = numberElements;
	}
	else {
		c = 1;
		a = numberElements;
		b = numberElements2;
	}
	//количество совпадений
	int numberCoincidence = 0;
	//флажок: если элементы равны, то истина(поднят), иначе ложь(опущен)
	bool flag = false;

	//элементы из первого множества в новый массив c удалением повторяющихся
	for (int i = 0; i < a; i++) {
		for (int j = b; j > i; j--) {
			if (setOfNumbers[j] == setOfNumbers[i]) {
				numberCoincidence++;
				flag = true;
			}
		}
		if (!flag) arrayTmp[i - numberCoincidence] = setOfNumbers[i];
		flag = false;
	}

	//элементы из второго множества во временный массив с удалением повторяющихся
	for (int i = 0; i < numberElements2; i++) {
		if (chekBelonging(setOfNumbers2[i]))
			numberCoincidence++;
		else {
			if (c == 0) arrayTmp[i + b - numberCoincidence] = setOfNumbers2[i];
			else arrayTmp[i + a - numberCoincidence] = setOfNumbers2[i];
		}
	}

	//новый размер массива
	numberElements = size - numberCoincidence;

	//перераспределение памяти
	setOfNumbers = (int*)realloc(setOfNumbers, numberElements * sizeof(int));


	//заполнение нового множества числами
	for (int i = 0; i < numberElements; i++) {
		setOfNumbers[i] = arrayTmp[i];
	}

	free(arrayTmp);
	free(setOfNumbers2);
}


/*
* Функция определяет принадлежность числа множеству
* аргументы: num - число
* если число принадлежит множеству, то функция вернёт истину
* в противном случае возвращает ложь
*/
bool SetOfNumbers::chekBelonging(int num) {
	//если будет совпадение - флаг поднимется
	bool flag = false;
	for (int i = 0; i < numberElements; i++) {
		if (setOfNumbers[i] == num) {
			flag = true;
		}
	}
	if (flag) return true;
	else return false;
}

/*
* Функция проверяет: является ли множество под(над)множеством другого
* аргументы: множество
* если да - возвращает истину
* иначе - ложь
*/
bool SetOfNumbers::chekSubset(SetOfNumbers &setOfNum) {
	//число совпадений
	int numberCoincidence = 0;
	//число элементов в множестве
	int numberElements2 = setOfNum.numberElements;

	//копируем переданное множество в массив setOfNumbers2,
	//число элементов в numberElements2
	int *setOfNumbers2 = (int*)malloc(numberElements2 * sizeof(int));
	for (int i = 0; i < numberElements2; i++)
		setOfNumbers2[i] = setOfNum.setOfNumbers[i];


	//считаем число совпавших элементов в множествах
	for (int i = 0; i < numberElements2; i++) {
		for (int j = 0; j < numberElements; j++) {
			if (setOfNumbers[j] == setOfNumbers2[i]) {
				numberCoincidence++;
			}
		}
	}
	//если чило совпадений = числу элементов одного из множеств, то оно является его над(под)множеством
	if ((numberCoincidence == numberElements) || (numberCoincidence == numberElements2))
		return true;
	else return false;
}