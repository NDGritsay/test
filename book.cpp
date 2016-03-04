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

//��������: ���� �������� �����
//�������: ��������� �� ������ ������ ������
char *setTitleOfBook(void)
{
	char *title = 0;

	printf("=���� �������� �����=\n"
		"�������� ����� ������ �������� �� ����� 1 � �� ����� %d ��������.\n"
		"��� ���������� ������� ������ � ����� �� �������� ����� �� �����������\n"
		"  � ����� �������.", TITLE_MAX_SIZE);
	do
	{
		free(title);
		printf("\n\n������� �������� �����: ");
		title = getStr(TITLE_MAX_SIZE);
		if (strlen(title) == TITLE_MAX_SIZE)
			printf("\a��������! ���������� �������� �������� ���������.\n");
		title = deleteSpace(title);
		if (!strlen(title))
		{
			printf("\a������! �������� ����� ������ �������� ���� �� �� ������ �������.\n");
			waitForEnter();
		}
	} while (!strlen(title));
	printf("���� �������� ��������!\n");
	waitForEnter();

	return title;
}


//��������: ���� ���������� �� ������ �����
//�������: ��������� �� ������ ������ ������
char *setAuthorOfBook(void)
{
	int authorCt, isAuthorHasName, isInputCorrect;
	char *author = 0, *name = 0;

	printf("=���� ������ �����=\n"
		"�������/��������� � ��� ������ ������ �������� �� ���� �������� �\n"
		"  ���������, � �� ����� ��������� %d ������%s.\n"
		"�������/��������� � ��� ������ ���������� � ��������� �����, � ���\n"
		"  ��������� ������� �������� ���������.\n"
		"��� ������ ������ ���� �� ����� 2 ��������, � ��� �������/��������� - 1��.\n"
		"��� ���������� ������� � ����� � �������/���������� ��\n"
		"  ����������� � ����� �������.\n"
		"���� � ����� ��������� �������, �� �������� ���������� ������ � �������,\n"
		"  ��� ���� ������ ���, � ������ ������ � ������������������ �������.", AUTHOR_NAME_MAX_SIZE,
		(AUTHOR_NAME_MAX_SIZE % 10) > 4 ? "��" : ((AUTHOR_NAME_MAX_SIZE % 10) == 1 ? "" : "�"));

	isInputCorrect = 0;  //���� ���-�� �������
	do
	{
		printf("\n\n� ����� ���� �����?(��-1/���-0): ");
		if (scanf("%d", &authorCt) != 1)
		{
			rewind(stdin);
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
		}
		else if (authorCt != 1 && authorCt != 0)
		{
			printf("\a������! ������� 1 ��� 0.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	if (authorCt)
	{
		do  //���� �������/����������
		{
			free(author);
			printf("\n������� �������/��������� ������: ");
			author = getName(AUTHOR_NAME_MAX_SIZE);
			if (!strlen(author))
			{
				printf("\a������! �������/��������� ������ ������ �������� ���� �� �� ������ �������.\n");
				waitForEnter();
			}
			else if (strlen(author) == AUTHOR_NAME_MAX_SIZE)
			{
				printf("\a��������! ���������� �������� �������� ���������.\n");
			}
		} while (!strlen(author));

		*author = toUpper(*author);  //������������� �������/����������
		for (int i = 1; *(author + i) != '\0'; i++)
			*(author + i) = toLower(*(author + i));

		printf("���� �������/���������� ������ ��������!\n");
		waitForEnter();

		isInputCorrect = 0;  //�������� ������� �����
		do
		{
			printf("\n\n� ������ ���� ���?(��-1/���-0): ");
			if (scanf("%d", &isAuthorHasName) != 1)
			{
				rewind(stdin);
				printf("\a������! �� ����� �� �����.\n");
				waitForEnter();
				isAuthorHasName = -1;
			}
			else if (isAuthorHasName != 1 && isAuthorHasName != 0)
			{
				printf("\a������! ������� 1 ��� 0.\n");
				waitForEnter();
			}
			else isInputCorrect = 1;
		} while (!isInputCorrect);

		if (isAuthorHasName)
		{
			do  //���� �����
			{
				free(name);
				printf("\n������� ��� ������: ");
				name = getName(AUTHOR_NAME_MAX_SIZE);
				if (strlen(name) < 2)
				{
					printf("\a������! ��� ������ ������ �������� ���� �� �� ���� ��������.\n");
					waitForEnter();
				}
				else if (strlen(name) == AUTHOR_NAME_MAX_SIZE)
				{
					printf("\a��������! ���������� �������� �������� ���������.\n");
				}
			} while (strlen(name) < 2);

			*name = toUpper(*name); //������������� �����
			for (int i = 1; *(name + i) != '\0'; i++)
				*(name + i) = toLower(*(name + i));

			author = strAddition(author, " ");  //������������ �������/���������� � �����
			author = strAddition(author, name);
			free(name);
		}
	}
	else
		author = "��� ������";
	printf("���� ������ ��������!\n");
	waitForEnter();
	return author;
}


//��������: ���� ���������� ��������� ������ �����
//�������: ���������� ��������� ������ �����
int setPageCtOfBook(void)
{
	int pageCt, isInputCorrect;

	printf("=���� ���������� ��������� ������ �����=\n"
		"���������� ��������� ������ ������ ���� �� ����� %d � �� ����� %d.", PAGE_CT_MIN, PAGE_CT_MAX);
	isInputCorrect = 0;
	do
	{
		printf("\n\n������� ���������� ��������� ������: ");
		if (scanf("%d", &pageCt) != 1)
		{
			rewind(stdin);
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
			pageCt = -1;
		}
		else if (pageCt < PAGE_CT_MIN)
		{
			printf("\a������! ���������� ��������� ������ �� ����� ���� ������ %d.\n", PAGE_CT_MIN);
			waitForEnter();
		}
		else if (pageCt > PAGE_CT_MAX)
		{
			printf("\a������! ���������� ��������� ������ �� ����� ���� ������ %d.\n", PAGE_CT_MAX);
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	printf("���� ��������!\n");
	waitForEnter();
	return pageCt;
}


//��������: ���� ����� �����
//�������: ��������� �� ������ ������ ������
char *setGenreOfBook(void)
{
	int isBookHasGenre, genreId, isInputCorrect;
	char *genre;

	printf("=���� ����� �����=\n");
	
	isInputCorrect = 0;
	do
	{
		printf("� ����� ���� ����?(1-��/0-���): ");
		if (scanf("%d", &isBookHasGenre) != 1)
		{
			rewind(stdin);
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
			isBookHasGenre = -1;
		}
		else if (isBookHasGenre != 0 && isBookHasGenre != 1)
		{
			printf("\a������! ������� 1 ��� 0.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	if (isBookHasGenre)
	{
		printf("\n"); //����� ������ ������
		for (int i = 0; i < genresCt(); i++)
			printf("%d-%s  %c", i+1, *(genres + i), i % 5 == 4 ? '\n' : ' ');
		
		isInputCorrect = 0;
		do //���� ������ ����� �� ������
		{
			printf("\n\n������� ����� ����� �� ������ ��� 0, ���� ������ ������ ����� ����: ");
			if (scanf("%d", &genreId) != 1)
			{
				rewind(stdin);
				printf("\a������! �� ����� �� �����.\n");
				waitForEnter();
				genreId = -1;
			}
			else if (genreId < 0 || genreId > genresCt())
			{
				printf("\a������! ������ ������ ����� ���.\n");
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
		genre = "��� �����";

	printf("���� ����� ��������!\n");
	waitForEnter();

	return genre;
}

//��������: ����� ���������� ������ � ������� ������
//�������: ���������� ������
int genresCt(void)
{
	int res;
	for (res = 0; strlen(*(genres + res)); res++);
	return res;
}


//��������: �������������� ������ ������
void genresInitialization(void)
{
	//����������� ��������� ������� ������ ��� ����������� ����� �������
	char *genres2[] = { "��������", "�������� ����������", "������� �������", "������-����������", "�������",
		"������������ ����������", "������������ ����������", "��������", "�������", "�����", "������",
		"������������ ����������", "�����", "������", "�������", "������", "��������", "���������", "����������",
		"�����", "������", "����", "����", ""};
	int gCt = 0;

	while (strlen(*(genres2 + gCt)))  //����� ���������� ������
		gCt++;
	
	genres = (char**)malloc(sizeof(char*) * (gCt + 1));
	
	for (int i = 0; i < gCt; i++)
		*(genres + i) = genres2[i];
	*(genres + gCt) = "";
}


//��������: ���� ������ ����� �����
//�������: ��������� �� ������ ������ ������
char *inputGenre(void)
{
	char *genre = 0;
	int hyphenCt, spaceCt, isHyphenNeareSpace, isInputFit, isInputCorrect;

	printf("�������� ����� ����� �������� �� �������� ���������, ������\n"
		"  ������ � ������ �������. ����� � ������ �� ����� ������ �����.\n"
		"�������� ����� ������ �������� �� ����� 2 � �� ����� %d ��������.\n"
		"��� ��������� ������� ����� ������������� � ��������.", GENRE_MAX_SIZE);

	do
	{
		free(genre);
		hyphenCt = 0, spaceCt = 0, isHyphenNeareSpace = 0, isInputFit = 1;

		printf("\n\n������� �������� �����: ");
		genre = getStr(GENRE_MAX_SIZE);

		if (strlen(genre) == GENRE_MAX_SIZE)
			printf("\a��������! ���������� �������� �������� ���������.\n");

		genre = deleteSpace(genre);
		for (int i = 0; *(genre + i) != '\0'; )  //�������������� ����� ������� �������� � ����
			if (*(genre + i) == ' ' && *(genre + i + 1) == ' ')
				deleteChar(genre, i);
			else
				i++;
		for (int i = 0; *(genre + i) != '\0'; i++)  //������� ���������� ������� � ��������
			if (*(genre + i) == ' ')
				spaceCt++;
			else if (*(genre + i) == '-')
				hyphenCt++;
		for (int i = 0; *(genre + i) != '\0'; i++)  //��������, ����� �� ����� ������ � �����
			if ((*(genre + i) == ' ' && *(genre + i + 1) == '-') || (*(genre + i) == '-' && *(genre + i + 1) == ' '))
				isHyphenNeareSpace = 1;
		for (int i = 0; *(genre + i) != '\0'; i++) //��������, ������������� �� ��� ������� �������
			if (!((*(genre + i) >= '�' && *(genre + i) <= '�') || *(genre + i) == ' ' || *(genre + i) == '-'))
				isInputFit = 0;

		for (int i = 0; *(genre + i) != '\0'; i++)  //������������� �������� �����
			*(genre + i) = toLower(*(genre + i));

		isInputCorrect = 0;
		if (strlen(genre) < 2)
		{
			printf("\a������! ���������� �������� ������ ���� �� ����� ����.\n");
			waitForEnter();
		}
		else if (!isInputFit)
		{
			printf("\a������! �������� ����� ����� �������� ������ �� �������� ���������,\n"
				"  ������� ��� ������.\n");
			waitForEnter();
		}
		else if (hyphenCt > 1)
		{
			printf("\a������! � �������� ����� ����� ���� ������ ���� �����.\n");
			waitForEnter();
		}
		else if (spaceCt > 1)
		{
			printf("\a������! � �������� ����� ����� ���� ������ ���� ������.\n");
			waitForEnter();
		}
		else if (isHyphenNeareSpace)
		{
			printf("\a������! ����� � ������ �� ����� ������ �����.\n");
			waitForEnter();
		}
		else if (*(genre) == '-' || *(genre + strlen(genre) - 1) == '-')
		{
			printf("\a������! ����� ������ ������ ����� �������.\n");
			waitForEnter();
		}
		else if (!strcmp(genre, "��� �����"))
		{
			printf("\a������! ������� �������, �� ��� ������.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	/*printf("���� ��������!\n");
	waitForEnter();*/

	return genre;
}


//��������: ���������� ����� � ������ ������
void addGenres(char *genre)
{
	int genrCt = genresCt() + 1;
	genres = (char**)realloc(genres, sizeof(char*) * (genrCt + 1));
	*(genres + genrCt - 1) = genre;
	*(genres + genrCt) = "";
}


//��������: ���� ������ ����� �����
//�������: ��������� �� �����
Book *inputBook(void)
{
	Book *book = (Book*)malloc(sizeof(Book));

	printf("==���� ������ � ����� �����==\n");
	book->title = setTitleOfBook();
	system("cls");
	printf("==���� ������ � ����� �����==\n");
	book->author = setAuthorOfBook();
	system("cls");
	printf("==���� ������ � ����� �����==\n");
	book->genre = setGenreOfBook();
	system("cls");
	printf("==���� ������ � ����� �����==\n");
	book->pageCt = setPageCtOfBook();
	system("cls");
	printf("==���� ������ � ����� �����==\n"
		"���� ������ � ����� ����� ��������!\n");
	waitForEnter();

	return book;
}


//��������: ����� ������� ���������� �� ����� �� �����
void printBooks(Book **books)
{
	int bookPrintCt, pageCt = PAGE_CT_MAX, pageCtRank = 0, bookCt = getBooksCt(books);
	while (pageCt) //������� ������������ ����������� ���������� ��������� ������
		pageCt /= 10, pageCtRank++;

	system("cls");
	printf("==����� ���������� � ������==");
	do
	{
		printf("\n\n������� ���� �� ���� ����� �� ������ ������?: ");
		if (scanf("%d", &bookPrintCt) != 1)
		{
			rewind(stdin);
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
			bookPrintCt = -1;
		}
		else if (bookPrintCt <= 0)
		{
			printf("\a������! ����� ������ ���� ������ 0.\n");
			waitForEnter();
		}
	} while (bookPrintCt <= 0);

	system("cls");
	printf("==����� ������==\n"
		"����� ����� ���������� �� %d �� ���. ��� ����������� ������ ���������\n"
		"  ������� space.\n\n", bookPrintCt);

	printHeadOfTable();
	for (int i = 0; i < bookCt; i++)
	{
		printf("|%-*s|%-*s|%-*s|%-*d|\n", TITLE_MAX_SIZE, (*(books + i))->title, AUTHOR_NAME_MAX_SIZE * 2 + 1, (*(books + i))->author,
			GENRE_MAX_SIZE, (*(books + i))->genre, pageCtRank, (*(books + i))->pageCt);
		if (i % bookPrintCt == bookPrintCt - 1)
			while (_getch() != ' ');
	}
	endPrintOfTable();
	printf("����� ������ ��������!\n");
	waitForEnter();
}


//��������: ����� ����� ������� �� �����
void printHeadOfTable(void)
{
	int pageCt = PAGE_CT_MAX, pageCtRank = 0;
	while (pageCt) //������� ������������ ����������� ���������� ��������� ������
		pageCt /= 10, pageCtRank++;

	printf(" ");  //������� ������
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

	printf("|%-*s|%-*s|%-*s|%-*s|\n", TITLE_MAX_SIZE, "��������", AUTHOR_NAME_MAX_SIZE * 2 + 1, "�����",
		GENRE_MAX_SIZE, "����", pageCtRank, "��");

	printf("|");  //������ ������
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


//��������: ��������� �������
void endPrintOfTable(void)
{
	int pageCt = PAGE_CT_MAX, pageCtRank = 0;
	while (pageCt) //������� ������������ ����������� ���������� ��������� ������
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

//��������: ���� ������� ���������� �� �����
//�������: ��������� �� ����� ������ �����
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
		printf("==���� ������ ����==\n"
			"�� ����� %d ����%c.\n"
			"���������� ���� - Enter | ��������� ���� - Esc", i, i % 10 > 4 ? ' ' : (i % 10 == 1 ? '�' : '�'));
		while ((c = _getch()) != '\r' && c != 27); //27 - ecsape
	} while (c == '\r');
	*(books + i) = nullptr;

	printf("\n���� ��������!\n");
	waitForEnter();

	return books;
}


//��������: ����� ���������� ���� � ������� ���������� �� �����
//�������: ���������� ���� � ������� ���������� �� �����
int getBooksCt(Book **books)
{
	int ct;
	for (ct = 0; *(books + ct) != nullptr; ct++);
	return ct;
}


//��������: ������������ ��������������� ������� ���������� �� �����
//�������: ��������� �� ����� ������ ����� ��������������� �������
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


//��������: ��������, ������������� �� ����� ��������� ������
//�������: (1/0)
int isBookCorrect(Book *book, char *genre, char *author)
{
	return(!strcmp(book->genre, genre) && !strcmp(book->author, author));
}


//��������: ������������ �������������� ������
//�������: ��������� �� ����� ������ ����� ��������������� ������ ����
Book **computeBooks(Book **books1)
{
	Book** books2;

	printf("==������������ �������������� ������==\n"
		"����� ������ ����������� �� ����, � ������� ��������� ����� � ����,\n"
		"  ��������� �������������");
	char *genre = setGenreOfBook();
	char *author = setAuthorOfBook();
	books2 = findBooks(books1, genre, author);
	system("cls");
	printf("==������������ �������������� ������==\n"
		"������ ������������! ������� %d ����%c.\n", getBooksCt(books2), getBooksCt(books2) % 10 > 4 ? ' ' : (getBooksCt(books2) % 10 == 1 ? '�' : '�'));
	return books2;
}