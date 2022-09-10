#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MIN_N 0
#define MAX_N 10

template<typename T>
T** createArray(T **is, int sizei, int sizej);
template<typename T>
void printArray(T *ar, int size);
template<typename T>
void printArray(T **ar, int sizei, int sizej);
template<typename T>
void deleteArray(T **ar, int sizei);
template<typename T>
void deleteArray(T *ar);
template<typename T>
void fillArray(T *ar, int size);
template<typename T>
void fillArray(T **ar, int sizei, int sizej);
template<typename T>
void swap(T *p1, T *p2);
template<typename T>
void exchangeRows(T **ar, int a, int b);
template<typename T>
void exchangeCols(T *ar, int a, int b);
template<typename T>
void exchangeCols(T **ar, int sizei, int a, int b);

/*
 * На поле для игры в сапер клеточки с минами обозначаются символом “*”, а в каждой пустой клеточке записано число
 * от 0 до 8, равное количеству мин в 8 клетках, соседних с данной.

 Дан список мин на поле. Постройте по данному списку изображение поля.

 Программа получает на вход числа N и M - количество строк и столбцов на поле, а также количество мин на поле K.
 Далее идет K пар чисел - координат мин. Первое число - номер строки, второе число - номер столбца.
 */

char** createMinesweeperField(int n, int m) {
	char **r { };
	r = createArray(r, n, m);
	return r;
}

void putMines(char **field, int n, int m, int mines) {
	while (mines) {
		int ncoord = rand() / (double) RAND_MAX * n;
		int mcoord = rand() / (double) RAND_MAX * m;
		if (field[ncoord][mcoord] == 0) {
			field[ncoord][mcoord] = '*';
			mines--;
		}
	}
}

int neighborhoodMines(char **field, int n, int m, int nc, int mc) {
	int r { };
	if (mc + 1 < m && field[nc][mc + 1] == '*')
		r++;
	if (nc + 1 < n && field[nc + 1][mc] == '*')
		r++;
	if (mc - 1 >= 0 && field[nc][mc - 1] == '*')
		r++;
	if (nc - 1 >= 0 && field[nc - 1][mc] == '*')
		r++;
	if (mc + 1 < m && nc + 1 < n && field[nc + 1][mc + 1] == '*')
		r++;
	if (mc - 1 >= 0 && nc - 1 >= 0 && field[nc - 1][mc - 1] == '*')
		r++;
	if (mc - 1 >= 0 && nc + 1 < n && field[nc + 1][mc - 1] == '*')
		r++;
	if (mc + 1 < m && nc - 1 >= 0 && field[nc - 1][mc + 1] == '*')
		r++;
	return r;
}

void putNumbers(char **field, int n, int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (field[i][j] != '*')
				field[i][j] = neighborhoodMines(field, n, m, i, j) + 48;
}

/*
 * Создать динамические массивы, используя указатели. Дан двумерный массив a, размером (n×n)
 * (или квадратная матрица а). Найти произведение элементов, расположенных в верхней треугольной
 * матрице, расположенной выше побочной диагонали, включая саму побочную диагональ.
 */

long long productOverSecDiag(int **ar, int n) {
	long long r { 1 };
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i + j <= n - 1)
				r *= ar[i][j];
	return r;
}

double f1(int i, double d, char c) {
	int ch { c - 48 };
	return (i + ch) * (double) d;
}

int main() {

	srand(time(NULL));
	//Перестановки строк и колонок массива
	/*int **ar { };
	 ar = createArray(ar, 10, 10);
	 fillArray(ar, 10, 10);
	 printArray(ar, 10, 10);
	 cout << endl << endl;
	 exchangeRows(ar, 1, 2);
	 printArray(ar, 10, 10);
	 cout << endl << endl;
	 exchangeCols(ar, 10, 1, 2);
	 printArray(ar, 10, 10);
	 deleteArray(ar, 10);*/

	//Произведение над главной диаганалью
	/*int **ar { };
	 int n { 5 };
	 ar = createArray(ar, n, n);
	 fillArray(ar, n, n);
	 printArray(ar, n, n);
	 long long prod = productOverSecDiag(ar, n);
	 cout << prod << endl;*/

	// Указатели на массивы
	typedef double (*func)(int, double, char);
	func ptr { f1 };
	cout << ptr(9, 0.5, '5') << endl;
	void (*ptr2)(int, double);

	//"Сапёр"
	/*int n { 10 }, m { 12 }, mines { 24 };
	 char **f { };
	 f = createMinesweeperField(n, m);
	 putMines(f, n, m, mines);
	 putNumbers(f, n, m);
	 printArray(f, n, m);*/

	return 0;
}

//Создание массива
template<typename T>
T** createArray(T **is, int sizei, int sizej) {
	is = new T*[sizei] { };
	for (int i = 0; i < sizei; i++) {
		*(is + i) = new T[sizej] { };
	}
	return is;
}

//Вывод массива
template<typename T>
void printArray(T *ar, int size) {
	for (int i = 0; i < size; i++) {
		cout << *(ar + i) << " ";
	}
	cout << endl;
}

template<typename T>
void printArray(T **ar, int sizei, int sizej) {
	for (int i = 0; i < sizei; i++) {
		printArray(*(ar + i), sizej);
	}

}

//Удаление массива
template<typename T>
void deleteArray(T **ar, int sizei) {
	for (int i = 0; i < sizei; i++) {
		delete[] *(ar + i);
	}
	delete[] ar;
}

template<typename T>
void deleteArray(T *ar) {
	delete[] ar;
}

//Заполнение массива случайными числами
template<typename T>
void fillArray(T *ar, int size) {
	for (int i = 0; i < size; i++) {
		*(ar + i) = MIN_N + rand() / (double) RAND_MAX * (MAX_N - MIN_N);
	}
}

template<typename T>
void fillArray(T **ar, int sizei, int sizej) {
	for (int i = 0; i < sizei; i++) {
		fillArray(*(ar + i), sizej);
	}
}

template<typename T>
void swap(T *p1, T *p2) {
	T t { };
	t = *p1;
	*p1 = *p2;
	*p2 = t;
}

template<typename T>
void exchangeRows(T **ar, int a, int b) {
	swap(ar[a], ar[b]);
}

template<typename T>
void exchangeCols(T *ar, int a, int b) {
	swap(ar[a], ar[b]);
}

template<typename T>
void exchangeCols(T **ar, int sizei, int a, int b) {
	for (int i = 0; i < sizei; i++) {
		exchangeCols(ar[i], a, b);
	}
}
