#include <stdio.h>
#include <Windows.h>
#include "ndgstrings.h"
#include "book.h"

//��������: ����� ���� �� �����
//�������: ��������� ����� ����
int menu(void);

//��������: ����� ������� �� �����
void reference(void);

//��������: ������������ ������ ������������ ��������
//�������: nullptr
void **freeDs(void **ds, int firstIndexCt);

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title = ��1 ��������� ����� �/�++");
	genresInitialization();

	int isProgEnd = 0;
	Book **books1 = nullptr, **books2 = nullptr;

	do
	{
		system("cls");
		switch (menu())
		{
		case 1: //���� �������� ������
			if(books2)
				books2 = (Book**)freeDs((void**)books2, getBooksCt(books2));
			if(books1)
				freeDs((void**)books1, getBooksCt(books1));
			books1 = inputBooks();
			break;
		case 2: //����� �������� ������
			if (books1)
				printBooks(books1);
			else
			{
				system("cls");
				printf("==����� �������� ������==\n"
					"\a������� ������� �������� ������.\n");
				waitForEnter();
			}
			break;
		case 3: //������������ �������������� ������
			system("cls");
			if (books1 != nullptr)
			{
				if (books2 != nullptr)
					books2 = (Book**)freeDs((void**)books2, getBooksCt(books2));
				books2 = computeBooks(books1);
			}
			else
				printf("==������������ ����������==\n"
					"\a������� ������� �������� ������.\n");
			waitForEnter();
			break;
		case 4: //����� ����������
			if (books2)
				if (getBooksCt(books2))
					printBooks(books2);
				else
				{
					system("cls");
					printf("==����� ����������==\n"
						"� �������������� ������ ��� ����.\n");
					waitForEnter();
				}
			else
			{
				system("cls");
				printf("==����� ����������==\n"
					"\a��� ������ ����������� ���������.\n");
				waitForEnter();
			}
			break;
		case 5: //����� �������
			system("cls");
			reference();
			waitForEnter();
			break;
		case 0: //����� �� ���������
			system("cls");
			isProgEnd = 1;
			printf("�� ��������!\n");
			waitForEnter();
			break;
		}
	} while (!isProgEnd);
	return 0;
}


//��������: ����� ���� �� �����
//�������: ��������� ����� ����
int menu(void)
{
	int res, isInputCorrect;

	printf(
		"=����=\n"
		"1 - ���� �������� ������\n"
		"2 - ����� �������� ������\n"
		"3 - ������������ ����������\n"
		"4 - ����� ����������\n"
		"5 - �������\n"
		"0 - �����");
	isInputCorrect = 0;
	do
	{
		printf("\n\n������� ����� ����: ");
		if (scanf("%d", &res) != 1)
		{
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
			rewind(stdin);
		}
		else if (res < 0 || res > 5)
		{
			printf("\a������! ������ ������ ���� ���.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return res;
}


//��������: ����� ������� �� �����
void reference(void)
{
	printf("made by NDg\n"
		"��������� ������������� ��� ����� ������ � ������ � ������ � ���� ������ ����,\n"
		"  � ������� ����� � ���� ��������� � ���������� �������������.\n"
		"������ � ������ ������� �� 4 �����: �������� �����, ��� ������, ���� � ����������\n"
		"��������� ������(����. ��).\n"
		"��� �������������� �������� � ���������, ������ �� ����� NikitaGritsay@icloud.com\n");
}


//��������: ������������ ������ ������������ ��������
//�������: nullptr
void **freeDs(void **ds, int firstIndexCt)
{
	for (int i = 0; i < firstIndexCt; i++)
		free(*(ds + i));
	free(ds);

	return nullptr;
}