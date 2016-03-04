#include <stdio.h>
#include <malloc.h>
#include <conio.h>

//��������: ���� ������� � ������ ��������� �������
//�������: ������, ��������� �������������
void waitForEnter()
{
	printf_s("��� ����������� ������� ������� Enter");
	rewind(stdin);
	for (; _getch() != '\r';); //'\r' == '\t'
}


//��������: ��������, �������� �� ������ ������ "������" ������ � ������������������ ������
//�������: (1/0)
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


//��������: ��������, ������� �� ����� ������ �� ��������� ��������
//�������: (1/0)
int isStrEn(const char *str)
{
	while (*str != '\0' && *str >= 'a' && *(str++) <= 'z');
	return (*str == '\0');
}


//��������: ��������, ������� �� ����� ������ �� �������� ���������
//�������: (1/0)
int isStrRu(const char *str)
{
	while (*str != '\0' && *str >= '�' && *(str++) <= '�');
	return (*str == '\0');
}


//��������: ���� ������� � ������ ��������� �������
//�������: ������, ��������� �������������
char _getchar()
{
	char c;

	c = _getch();
	if (c == '\r')//'\r' == '\n' � ������� _getch()
		c = '\n';
	printf_s("%c", c);
	return c;
}


//��������: ���� ������
//�������: ��������� �� ������ ������� ������
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


//��������: ������� ��� ���������� ������� ������ � ����� �� ������
//�������: ��������� �� ����� ������� ������� �������������� ������
char *deleteSpace(char *str)
{
	char *str2;
	int i = 0, j;

	while (isspace((unsigned char)*(str + i)))	//�������� �����
		i++;
	str2 = (char*)malloc(sizeof(char) * (strlen(str) - i + 1));
	for (j = 0; *(str + i) != '\0'; i++, j++)
		*(str2 + j) = *(str + i);
	if (j)	//�������� ������
	{
		while (isspace((unsigned char)*(str2 + --j)));
		str2 = (char*)realloc(str2, sizeof(char) * (j + 2));
		j++;
	}
	*(str2 + j) = '\0';
	return str2;
}


//��������: ������� ��� ���������� ������� �� ������
//�������: ��������� �� ������ ������ ������
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


//��������: ���� ������� �������� ��� ��������� � ������ ��������� �������
//�������: ������, ��������� �������������
char _getnamechar()
{
	char c;

	do
	{
		c = _getch();
		if (c == '\r')//'\r' == '\n' � ������� _getch()
			c = '\n';
	} while (!((c >= '�' && c <= '�') || (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') || c == '\n' || c == '\b'));
	printf_s("%c", c);
	return c;
}


//��������: ���� �����
//�������: ��������� �� ������ ������� ������
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


//��������: ����������� �������� ������ � ���������
//�������: ������
int toUpper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 'b' - 'B';
	if (c >= '�' && c <= '�')
		c -= '�' - '�';
	return c;
}


//��������: ����������� ��������� ������ � ��������
//�������: ������
int toLower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 'b' - 'B';
	if (c >= '�' && c <= '�')
		c += '�' - '�';
	return c;
}


//��������: ������������� 2 ������
//�������: ��������� �� ������ ������ ������-����������
char *strAddition(char *str1, char *str2)
{
	int i = strlen(str1);
	str1 = (char*)realloc(str1, sizeof(char) * (i + strlen(str2) + 1));
	for (int j = 0; *(str2 + j) != '\0'; j++, i++)
		*(str1 + i) = *(str2 + j);
	*(str1 + i) = '\0';
	return str1;
}


//��������: ������� ������ � �������� i �� ������
//�������: ��������� �� ������ ������ ������
char *deleteChar(char *str, int i)
{
	do
	{ 
		*(str + i) = *(str + i + 1);
	} while (*(str + i++) != '\0');
	str = (char*)realloc(str, sizeof(char) * i);
	return str;
}