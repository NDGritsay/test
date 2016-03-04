#include <stdio.h>
#include <malloc.h>
#include <conio.h>

//Описание: ввод символа в режиме реального времени
//Возврат: символ, введенный пользователем
void waitForEnter()
{
	printf_s("Для продолжения нажмите клавишу Enter");
	rewind(stdin);
	for (; _getch() != '\r';); //'\r' == '\t'
}


//Описание: проверка, является ли первая строка "меньше" второй в лексикографическом смысле
//Возврат: (1/0)
int isStrFirst(const char *str1, const char *str2)
{
	int i = 0;
	while (*(str1 + i) != '\0' && *(str2 + i) != '\0' && tolower(*(str1 + i)) == tolower(*(str2 + i)))
		i++;
	if (*(str1 + i) == '\0')
		return 1;
	else
		if (*(str2 + i) == '\0')
			return 0;
		else
			return tolower(*(str1 + i)) < tolower(*(str2 + i));
}


//Описание: проверка, состоит ли слово только из латинских символов
//Возврат: (1/0)
int isStrEn(const char *str)
{
	while (*str != '\0' && *str >= 'a' && *(str++) <= 'z');
	return (*str == '\0');
}


//Описание: проверка, состоит ли слово только из символов кириллицы
//Возврат: (1/0)
int isStrRu(const char *str)
{
	while (*str != '\0' && *str >= 'а' && *(str++) <= 'я');
	return (*str == '\0');
}


//Описание: ввод символа в режиме раельного времени
//Возврат: символ, введенный пользователем
char _getchar()
{
	char c;

	c = _getch();
	if (c == '\r')//'\r' == '\n' в функции _getch()
		c = '\n';
	printf_s("%c", c);
	return c;
}


//Описание: ввод строки
//Возврат: указатель на первый элемент строки
char *getStr(int maxsize)
{
	char *str = (char*)malloc(sizeof(char));
	short count = 0;
	while ((count < maxsize) && ((*(str + count) = _getchar()) != '\n'))
	{
		if (*(str + count) == '\b')
		{
			if (count)
			{
				printf_s(" \b");
				count--;
			}
			else
				printf(" ");
		}
		else
		{
			count++;
		}
		str = (char*)realloc(str, sizeof(char) * (count + 1));
	}
	if (count == maxsize)
		printf("\n");
	*(str + count) = '\0';
	return str;
}

char *getStr()
{
	char *str = (char*)malloc(sizeof(char));
	short count = 0;
	while ((*(str + count) = _getchar()) != '\n')
	{
		if (*(str + count) == '\b')
		{
			if (count)
			{
				printf_s(" \b");
				count--;
			}
			else
				printf(" ");
		}
		else
		{
			count++;
		}
		str = (char*)realloc(str, sizeof(char) * (count + 1));
	}
	*(str + count) = '\0';
	return str;
}


//Описание: удаляет все пробельные символы справа и слева от строки
//Возврат: указатель на адрес первого символа результирующей строки
char *deleteSpace(char *str)
{
	char *str2;
	int i = 0, j;

	while (isspace((unsigned char)*(str + i)))	//удаление слева
		i++;
	str2 = (char*)malloc(sizeof(char) * (strlen(str) - i + 1));
	for (j = 0; *(str + i) != '\0'; i++, j++)
		*(str2 + j) = *(str + i);
	if (j)	//удаление справа
	{
		while (isspace((unsigned char)*(str2 + --j)));
		str2 = (char*)realloc(str2, sizeof(char) * (j + 2));
		j++;
	}
	*(str2 + j) = '\0';
	return str2;
}


//Описание: удаляет все пробельные символы из строки
//Возврат: указатель на первый символ строки
char *deleteSpaceEverywhere(char *str)
{
	char *str2 = (char*)malloc(sizeof(char));
	int i, j;

	for (i = 0, j = 0; *(str + i) != '\0'; i++)
	{
		if (!isspace(*(str + i)))
		{
			str2 = (char*)realloc(str2, sizeof(char)*(j + 2));
			*(str2 + j) = *(str + i);
			j++;
		}
	}
	*(str2 + j) = '\0';
	return str2;
}


//Описание: ввод символа латиницы или кириллицы в режиме раельного времени
//Возврат: символ, введенный пользователем
char _getnamechar()
{
	char c;

	do
	{
		c = _getch();
		if (c == '\r')//'\r' == '\n' в функции _getch()
			c = '\n';
	} while (!((c >= 'А' && c <= 'я') || (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') || c == '\n' || c == '\b'));
	printf_s("%c", c);
	return c;
}


//Описание: ввод имени
//Возврат: указатель на первый элемент строки
char *getName(int maxsize)
{
	char *str = (char*)malloc(sizeof(char));
	short count = 0;
	while ((count < maxsize) && ((*(str + count) = _getnamechar()) != '\n'))
	{
		if (*(str + count) == '\b')
		{
			if (count)
			{
				printf_s(" \b");
				count--;
			}
			else
				printf(" ");
		}
		else
		{
			count++;
		}
		str = (char*)realloc(str, sizeof(char) * (count + 1));
	}
	if (count == maxsize)
		printf("\n");
	*(str + count) = '\0';
	return str;
}


//Описание: преобразует строчный символ в прописной
//Возврат: символ
int toUpper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 'b' - 'B';
	if (c >= 'а' && c <= 'я')
		c -= 'б' - 'Б';
	return c;
}


//Описание: преобразует прописной символ в строчный
//Возврат: символ
int toLower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 'b' - 'B';
	if (c >= 'А' && c <= 'Я')
		c += 'б' - 'Б';
	return c;
}


//Описание: конкатенирует 2 строки
//Возврат: указатель на первый символ строки-результата
char *strAddition(char *str1, char *str2)
{
	int i = strlen(str1);
	str1 = (char*)realloc(str1, sizeof(char) * (i + strlen(str2) + 1));
	for (int j = 0; *(str2 + j) != '\0'; j++, i++)
		*(str1 + i) = *(str2 + j);
	*(str1 + i) = '\0';
	return str1;
}


//Описание: удаляет символ с индексом i из строки
//Возврат: указатель на первый символ строки
char *deleteChar(char *str, int i)
{
	do
	{ 
		*(str + i) = *(str + i + 1);
	} while (*(str + i++) != '\0');
	str = (char*)realloc(str, sizeof(char) * i);
	return str;
}