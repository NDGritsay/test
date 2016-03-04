#include <stdio.h>

#include "ndgstrings.h"

#define TITLE_MAX_SIZE 35
#define AUTHOR_NAME_MAX_SIZE 15
#define PAGE_CT_MIN 10
#define PAGE_CT_MAX 500
#define GENRE_MAX_SIZE 30

struct Book {
	char *title;
	char *author;
	char *genre;
	int pageCt;
};

char **genres;

//Описание: ввод названия книги
//Возврат: указатель на первый символ строки
char *setTitleOfBook(void)
{
	char *title = 0;

	printf("=Ввод названия книги=\n"
		"Название книги должно включать не менее 1 и не более %d символов.\n"
		"Все пробельные символы справа и слева от названия книги не учитываются\n"
		"  и будут удалены.", TITLE_MAX_SIZE);
	do
	{
		free(title);
		printf("\n\nВведите название книги: ");
		title = getStr(TITLE_MAX_SIZE);
		if (strlen(title) == TITLE_MAX_SIZE)
			printf("\aВнимание! Количество символов достигло максимума.\n");
		title = deleteSpace(title);
		if (!strlen(title))
		{
			printf("\aОшибка! Название книги должно состоять хотя бы из одного символа.\n");
			waitForEnter();
		}
	} while (!strlen(title));
	printf("Ввод названия завершен!\n");
	waitForEnter();

	return title;
}


//Описание: ввод информации об авторе книги
//Возврат: указатель на первый символ строки
char *setAuthorOfBook(void)
{
	int authorCt, isAuthorHasName, isInputCorrect;
	char *author = 0, *name = 0;

	printf("=Ввод автора книги=\n"
		"Фамилия/псевдоним и имя автора должны состоять из букв латиницы и\n"
		"  кириллицы, и не могут превышать %d символ%s.\n"
		"Фамилия/псевдоним и имя автора начинаются с прописной буквы, а все\n"
		"  остальные символы являются строчными.\n"
		"Имя автора должно быть не менее 2 символов, а его фамилия/псевдоним - 1го.\n"
		"Все пробельные символы в имени и фамилии/псевдониме не\n"
		"  учитываются и будут удалены.\n"
		"Если у книги несколько авторов, то вводится информация только о главном,\n"
		"  или если такого нет, о первом авторе в лексикографическом порядке.", AUTHOR_NAME_MAX_SIZE,
		(AUTHOR_NAME_MAX_SIZE % 10) > 4 ? "ов" : ((AUTHOR_NAME_MAX_SIZE % 10) == 1 ? "" : "а"));

	isInputCorrect = 0;  //ввод кол-ва авторов
	do
	{
		printf("\n\nУ книги есть автор?(Да-1/Нет-0): ");
		if (scanf("%d", &authorCt) != 1)
		{
			rewind(stdin);
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (authorCt != 1 && authorCt != 0)
		{
			printf("\aОшибка! Введите 1 или 0.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	if (authorCt)
	{
		do  //ввод фамилии/псевдонима
		{
			free(author);
			printf("\nВведите фамилию/псевдоним автора: ");
			author = getName(AUTHOR_NAME_MAX_SIZE);
			if (!strlen(author))
			{
				printf("\aОшибка! Фамилия/псевдоним автора должны состоять хотя бы из одного символа.\n");
				waitForEnter();
			}
			else if (strlen(author) == AUTHOR_NAME_MAX_SIZE)
			{
				printf("\aВнимание! Количество символов достигло максимума.\n");
			}
		} while (!strlen(author));

		*author = toUpper(*author);  //экранирование фамилии/псевдонима
		for (int i = 1; *(author + i) != '\0'; i++)
			*(author + i) = toLower(*(author + i));

		printf("Ввод фамилии/псевдонима автора завершен!\n");
		waitForEnter();

		isInputCorrect = 0;  //проверка наличия имени
		do
		{
			printf("\n\nУ автора есть имя?(Да-1/Нет-0): ");
			if (scanf("%d", &isAuthorHasName) != 1)
			{
				rewind(stdin);
				printf("\aОшибка! Вы ввели не число.\n");
				waitForEnter();
				isAuthorHasName = -1;
			}
			else if (isAuthorHasName != 1 && isAuthorHasName != 0)
			{
				printf("\aОшибка! Введите 1 или 0.\n");
				waitForEnter();
			}
			else isInputCorrect = 1;
		} while (!isInputCorrect);

		if (isAuthorHasName)
		{
			do  //ввод имени
			{
				free(name);
				printf("\nВведите имя автора: ");
				name = getName(AUTHOR_NAME_MAX_SIZE);
				if (strlen(name) < 2)
				{
					printf("\aОшибка! Имя автора должно состоять хотя бы из двух символов.\n");
					waitForEnter();
				}
				else if (strlen(name) == AUTHOR_NAME_MAX_SIZE)
				{
					printf("\aВнимание! Количество символов достигло максимума.\n");
				}
			} while (strlen(name) < 2);

			*name = toUpper(*name); //экранирование имени
			for (int i = 1; *(name + i) != '\0'; i++)
				*(name + i) = toLower(*(name + i));

			author = strAddition(author, " ");  //конкатенация фамилии/псевдонима и имени
			author = strAddition(author, name);
			free(name);
		}
	}
	else
		author = "нет автора";
	printf("Ввод автора завершен!\n");
	waitForEnter();
	return author;
}


//Описание: ввод количества авторских листов книги
//Возврат: количество авторских листов книги
int setPageCtOfBook(void)
{
	int pageCt, isInputCorrect;

	printf("=Ввод количества авторских листов книги=\n"
		"Количество авторских листов должно быть не менее %d и не более %d.", PAGE_CT_MIN, PAGE_CT_MAX);
	isInputCorrect = 0;
	do
	{
		printf("\n\nВведите количество авторских листов: ");
		if (scanf("%d", &pageCt) != 1)
		{
			rewind(stdin);
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
			pageCt = -1;
		}
		else if (pageCt < PAGE_CT_MIN)
		{
			printf("\aОшибка! Количество авторских листов не может быть меньше %d.\n", PAGE_CT_MIN);
			waitForEnter();
		}
		else if (pageCt > PAGE_CT_MAX)
		{
			printf("\aОшибка! Количество авторских листов не может быть больше %d.\n", PAGE_CT_MAX);
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	printf("Ввод завершен!\n");
	waitForEnter();
	return pageCt;
}


//Описание: ввод жанра книги
//Возврат: указатель на первый символ строки
char *setGenreOfBook(void)
{
	int isBookHasGenre, genreId, isInputCorrect;
	char *genre;

	printf("=Ввод жанра книги=\n");
	
	isInputCorrect = 0;
	do
	{
		printf("У книги есть жанр?(1-Да/0-Нет): ");
		if (scanf("%d", &isBookHasGenre) != 1)
		{
			rewind(stdin);
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
			isBookHasGenre = -1;
		}
		else if (isBookHasGenre != 0 && isBookHasGenre != 1)
		{
			printf("\aОшибка! Введите 1 или 0.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	if (isBookHasGenre)
	{
		printf("\n"); //Вывод списка жанров
		for (int i = 0; i < genresCt(); i++)
			printf("%d-%s  %c", i+1, *(genres + i), i % 5 == 4 ? '\n' : ' ');
		
		isInputCorrect = 0;
		do //Ввод номера жанра из списка
		{
			printf("\n\nВведите номер жанра из списка или 0, если хотите ввести новый жанр: ");
			if (scanf("%d", &genreId) != 1)
			{
				rewind(stdin);
				printf("\aОшибка! Вы ввели не число.\n");
				waitForEnter();
				genreId = -1;
			}
			else if (genreId < 0 || genreId > genresCt())
			{
				printf("\aОшибка! Такого номера жанра нет.\n");
				waitForEnter();
			}
			else
				isInputCorrect = 1;
		} while (!isInputCorrect);

		if (genreId)
			genre = *(genres + genreId - 1);
		else
			addGenres(genre = inputGenre());
	}
	else
		genre = "нет жанра";

	printf("Ввод жанра завершен!\n");
	waitForEnter();

	return genre;
}

//Описание: поиск количества жанров в массиве жанров
//Возврат: количество жанров
int genresCt(void)
{
	int res;
	for (res = 0; strlen(*(genres + res)); res++);
	return res;
}


//Описание: инициализирует массив жанров
void genresInitialization(void)
{
	//Обязательно оставлять нулевую строку для обозначения конца массива
	char *genres2[] = { "анекдоты", "античная литература", "военная история", "бизнес-литература", "история",
		"классическая литература", "компьютерная литература", "детектив", "рассказ", "роман", "лирика",
		"политическая литература", "проза", "сказки", "словарь", "поэзия", "обучение", "философия", "фантастика",
		"скетч", "эпопея", "эпос", "эссе", ""};
	int gCt = 0;

	while (strlen(*(genres2 + gCt)))  //поиск количества жанров
		gCt++;
	
	genres = (char**)malloc(sizeof(char*) * (gCt + 1));
	
	for (int i = 0; i < gCt; i++)
		*(genres + i) = genres2[i];
	*(genres + gCt) = "";
}


//Описание: ввод нового жанра книги
//Возврат: указатель на первый символ строки
char *inputGenre(void)
{
	char *genre = 0;
	int hyphenCt, spaceCt, isHyphenNeareSpace, isInputFit, isInputCorrect;

	printf("Название жанра может состоять из символов кириллицы, одного\n"
		"  дефиса и одного пробела. Дефис и пробел не могут стоять рядом.\n"
		"Название жанра должно включать не менее 2 и не более %d символов.\n"
		"Все прописные символы будут преобразованы в строчные.", GENRE_MAX_SIZE);

	do
	{
		free(genre);
		hyphenCt = 0, spaceCt = 0, isHyphenNeareSpace = 0, isInputFit = 1;

		printf("\n\nВведите название жанра: ");
		genre = getStr(GENRE_MAX_SIZE);

		if (strlen(genre) == GENRE_MAX_SIZE)
			printf("\aВнимание! Количество символов достигло максимума.\n");

		genre = deleteSpace(genre);
		for (int i = 0; *(genre + i) != '\0'; )  //Преобразование рядом стоящих пробелов в один
			if (*(genre + i) == ' ' && *(genre + i + 1) == ' ')
				deleteChar(genre, i);
			else
				i++;
		for (int i = 0; *(genre + i) != '\0'; i++)  //Подсчет количества дефисов и пробелов
			if (*(genre + i) == ' ')
				spaceCt++;
			else if (*(genre + i) == '-')
				hyphenCt++;
		for (int i = 0; *(genre + i) != '\0'; i++)  //Проверка, стоят ли рядом пробел и дефис
			if ((*(genre + i) == ' ' && *(genre + i + 1) == '-') || (*(genre + i) == '-' && *(genre + i + 1) == ' '))
				isHyphenNeareSpace = 1;
		for (int i = 0; *(genre + i) != '\0'; i++) //Проверка, удовлетворяют ли все символы условию
			if (!((*(genre + i) >= 'А' && *(genre + i) <= 'я') || *(genre + i) == ' ' || *(genre + i) == '-'))
				isInputFit = 0;

		for (int i = 0; *(genre + i) != '\0'; i++)  //экранирование названия жанра
			*(genre + i) = toLower(*(genre + i));

		isInputCorrect = 0;
		if (strlen(genre) < 2)
		{
			printf("\aОшибка! Количество символов должно быть не менее двух.\n");
			waitForEnter();
		}
		else if (!isInputFit)
		{
			printf("\aОшибка! Название жанра может состоять только из символов кириллицы,\n"
				"  пробела или дефиса.\n");
			waitForEnter();
		}
		else if (hyphenCt > 1)
		{
			printf("\aОшибка! В названии жанра может быть только один дефис.\n");
			waitForEnter();
		}
		else if (spaceCt > 1)
		{
			printf("\aОшибка! В названии жанра может быть только один пробел.\n");
			waitForEnter();
		}
		else if (isHyphenNeareSpace)
		{
			printf("\aОшибка! Дефис и пробел не могут стоять рядом.\n");
			waitForEnter();
		}
		else if (*(genre) == '-' || *(genre + strlen(genre) - 1) == '-')
		{
			printf("\aОшибка! Дефис должен стоять между буквами.\n");
			waitForEnter();
		}
		else if (!strcmp(genre, "нет жанра"))
		{
			printf("\aОшибка! Хорошая попытка, но так нельзя.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	/*printf("Ввод завершен!\n");
	waitForEnter();*/

	return genre;
}


//Описание: добавление жанра в массив жанров
void addGenres(char *genre)
{
	int genrCt = genresCt() + 1;
	genres = (char**)realloc(genres, sizeof(char*) * (genrCt + 1));
	*(genres + genrCt - 1) = genre;
	*(genres + genrCt) = "";
}


//Описание: ввод данных новой книги
//Возврат: указатель на книгу
Book *inputBook(void)
{
	Book *book = (Book*)malloc(sizeof(Book));

	printf("==Ввод данных о новой книге==\n");
	book->title = setTitleOfBook();
	system("cls");
	printf("==Ввод данных о новой книге==\n");
	book->author = setAuthorOfBook();
	system("cls");
	printf("==Ввод данных о новой книге==\n");
	book->genre = setGenreOfBook();
	system("cls");
	printf("==Ввод данных о новой книге==\n");
	book->pageCt = setPageCtOfBook();
	system("cls");
	printf("==Ввод данных о новой книге==\n"
		"Ввод данных о новой книге завершен!\n");
	waitForEnter();

	return book;
}


//Описание: вывод массива указателей на книги на экран
void printBooks(Book **books)
{
	int bookPrintCt, pageCt = PAGE_CT_MAX, pageCtRank = 0, bookCt = getBooksCt(books);
	while (pageCt) //подсчет максимальной разрядности количества авторских листов
		pageCt /= 10, pageCtRank++;

	system("cls");
	printf("==Вывод информации о книгах==");
	do
	{
		printf("\n\nСколько книг за один вывод вы хотите видеть?: ");
		if (scanf("%d", &bookPrintCt) != 1)
		{
			rewind(stdin);
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
			bookPrintCt = -1;
		}
		else if (bookPrintCt <= 0)
		{
			printf("\aОшибка! Число должно быть больше 0.\n");
			waitForEnter();
		}
	} while (bookPrintCt <= 0);

	system("cls");
	printf("==Вывод данных==\n"
		"Книги будут выводиться по %d за раз. Для продолжения вывода нажимайте\n"
		"  клавишу space.\n\n", bookPrintCt);

	printHeadOfTable();
	for (int i = 0; i < bookCt; i++)
	{
		printf("|%-*s|%-*s|%-*s|%-*d|\n", TITLE_MAX_SIZE, (*(books + i))->title, AUTHOR_NAME_MAX_SIZE * 2 + 1, (*(books + i))->author,
			GENRE_MAX_SIZE, (*(books + i))->genre, pageCtRank, (*(books + i))->pageCt);
		if (i % bookPrintCt == bookPrintCt - 1)
			while (_getch() != ' ');
	}
	endPrintOfTable();
	printf("Вывод данных завершен!\n");
	waitForEnter();
}


//Описание: вывод шапки таблицы на экран
void printHeadOfTable(void)
{
	int pageCt = PAGE_CT_MAX, pageCtRank = 0;
	while (pageCt) //подсчет максимальной разрядности количества авторских листов
		pageCt /= 10, pageCtRank++;

	printf(" ");  //верхняя строка
	for (int i = 0; i < TITLE_MAX_SIZE; i++)
		printf("_");
	printf(" ");
	for (int i = 0; i < AUTHOR_NAME_MAX_SIZE * 2 + 1; i++)
		printf("_");
	printf(" ");
	for (int i = 0; i < GENRE_MAX_SIZE; i++)
		printf("_");
	printf(" ");
	for (int i = 0; i < pageCtRank; i++)
		printf("_");
	printf("\n");

	printf("|%-*s|%-*s|%-*s|%-*s|\n", TITLE_MAX_SIZE, "Название", AUTHOR_NAME_MAX_SIZE * 2 + 1, "Автор",
		GENRE_MAX_SIZE, "Жанр", pageCtRank, "АЛ");

	printf("|");  //нижняя строка
	for (int i = 0; i < TITLE_MAX_SIZE; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < AUTHOR_NAME_MAX_SIZE * 2 + 1; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < GENRE_MAX_SIZE; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < pageCtRank; i++)
		printf("_");
	printf("|\n");
}


//Описание: закрывает таблицу
void endPrintOfTable(void)
{
	int pageCt = PAGE_CT_MAX, pageCtRank = 0;
	while (pageCt) //подсчет максимальной разрядности количества авторских листов
		pageCt /= 10, pageCtRank++;

	printf("|");
	for (int i = 0; i < TITLE_MAX_SIZE; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < AUTHOR_NAME_MAX_SIZE * 2 + 1; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < GENRE_MAX_SIZE; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < pageCtRank; i++)
		printf("_");
	printf("|\n");
}

//Описание: ввод массива указателей на книги
//Возврат: указатель на адрес первой книги
Book **inputBooks()
{
	Book **books = 0;
	int i = 0;
	char c;

	do
	{
		books = (Book**)realloc(books, sizeof(Book) * (i + 2));
		system("cls");
		*(books + i++) = inputBook();
		system("cls");
		printf("==Ввод списка книг==\n"
			"Вы ввели %d книг%c.\n"
			"Продолжить ввод - Enter | Завершить ввод - Esc", i, i % 10 > 4 ? ' ' : (i % 10 == 1 ? 'у' : 'и'));
		while ((c = _getch()) != '\r' && c != 27); //27 - ecsape
	} while (c == '\r');
	*(books + i) = nullptr;

	printf("\nВвод завершен!\n");
	waitForEnter();

	return books;
}


//Описание: поиск количества книг в массиве указателей на книги
//Возврат: количество книг в массиве указателей на книги
int getBooksCt(Book **books)
{
	int ct;
	for (ct = 0; *(books + ct) != nullptr; ct++);
	return ct;
}


//Описание: формирование результирующего массива указателей на книги
//Возврат: указатель на адрес первой книги результирующего массива
Book **findBooks(Book **books1, char* genre, char* author)
{
	Book **books2 = (Book**)malloc(sizeof(Book*));
	int i = 0;

	for (int j = 0; j < getBooksCt(books1); j++)
		if (isBookCorrect(*(books1 + j), genre, author))
		{
			books2 = (Book**)realloc(books2, sizeof(Book*) * (i + 1));
			*(books2 + i++) = *(books1 + j);
		}
	*(books2 + i) = nullptr;

	return books2;
}


//Описание: проверка, удовлетворяет ли книга критериям поиска
//Возврат: (1/0)
int isBookCorrect(Book *book, char *genre, char *author)
{
	return(!strcmp(book->genre, genre) && !strcmp(book->author, author));
}


//Описание: формирование результирующих данных
//Возврат: указатель на адрес первой книги результирующего списка книг
Book **computeBooks(Book **books1)
{
	Book** books2;

	printf("==Формирование результирующих данных==\n"
		"Новые данные формируются из книг, у которых совпадают автор и жанр,\n"
		"  введенные пользователем");
	char *genre = setGenreOfBook();
	char *author = setAuthorOfBook();
	books2 = findBooks(books1, genre, author);
	system("cls");
	printf("==Формирование результирующих данных==\n"
		"Данные сформированы! Найдено %d книг%c.\n", getBooksCt(books2), getBooksCt(books2) % 10 > 4 ? ' ' : (getBooksCt(books2) % 10 == 1 ? 'а' : 'и'));
	return books2;
}