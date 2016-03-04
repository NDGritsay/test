#include <stdio.h>
#include <Windows.h>
#include "ndgstrings.h"
#include "book.h"

//Описание: вывод меню на экран
//Возврат: выбранный пункт меню
int menu(void);

//Описание: вывод справки на экран
void reference(void);

//Описание: освобождение памяти динамической сруктуры
//Возврат: nullptr
void **freeDs(void **ds, int firstIndexCt);

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title = ЛР1 Структуры языка С/С++");
	genresInitialization();

	int isProgEnd = 0;
	Book **books1 = nullptr, **books2 = nullptr;

	do
	{
		system("cls");
		switch (menu())
		{
		case 1: //Ввод исходных данных
			if(books2)
				books2 = (Book**)freeDs((void**)books2, getBooksCt(books2));
			if(books1)
				freeDs((void**)books1, getBooksCt(books1));
			books1 = inputBooks();
			break;
		case 2: //Вывод исходных данных
			if (books1)
				printBooks(books1);
			else
			{
				system("cls");
				printf("==Вывод исходных данных==\n"
					"\aСначала введите исходные данные.\n");
				waitForEnter();
			}
			break;
		case 3: //Формирование результирующих данных
			system("cls");
			if (books1 != nullptr)
			{
				if (books2 != nullptr)
					books2 = (Book**)freeDs((void**)books2, getBooksCt(books2));
				books2 = computeBooks(books1);
			}
			else
				printf("==Формирование результата==\n"
					"\aСначала введите исходные данные.\n");
			waitForEnter();
			break;
		case 4: //Вывод результата
			if (books2)
				if (getBooksCt(books2))
					printBooks(books2);
				else
				{
					system("cls");
					printf("==Вывод результата==\n"
						"В результирующих ланных нет книг.\n");
					waitForEnter();
				}
			else
			{
				system("cls");
				printf("==Вывод результата==\n"
					"\aДля начала сформируйте результат.\n");
				waitForEnter();
			}
			break;
		case 5: //Вывод справки
			system("cls");
			reference();
			waitForEnter();
			break;
		case 0: //Выход из программы
			system("cls");
			isProgEnd = 1;
			printf("До свидания!\n");
			waitForEnter();
			break;
		}
	} while (!isProgEnd);
	return 0;
}


//Описание: вывод меню на экран
//Возврат: выбранный пункт меню
int menu(void)
{
	int res, isInputCorrect;

	printf(
		"=Меню=\n"
		"1 - Ввод исходных данных\n"
		"2 - Вывод исходных данных\n"
		"3 - Формирование результата\n"
		"4 - Вывод результата\n"
		"5 - Справка\n"
		"0 - Выход");
	isInputCorrect = 0;
	do
	{
		printf("\n\nВведите пункт меню: ");
		if (scanf("%d", &res) != 1)
		{
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
			rewind(stdin);
		}
		else if (res < 0 || res > 5)
		{
			printf("\aОшибка! Такого пункта меню нет.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return res;
}


//Описание: вывод справки на экран
void reference(void)
{
	printf("made by NDg\n"
		"Программа предназначена для ввода данных о книгах и поиска в этих данных книг,\n"
		"  у которых автор и жанр совпадают с введенными пользователем.\n"
		"Данные о книгах состоят из 4 полей: название книги, имя автора, жанр и количество\n"
		"авторских листов(сокр. АЛ).\n"
		"При возниконовении вопросов и пожеланий, писать на адрес NikitaGritsay@icloud.com\n");
}


//Описание: освобождение памяти динамической сруктуры
//Возврат: nullptr
void **freeDs(void **ds, int firstIndexCt)
{
	for (int i = 0; i < firstIndexCt; i++)
		free(*(ds + i));
	free(ds);

	return nullptr;
}