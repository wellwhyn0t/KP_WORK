#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/*
������� � ������� ������� ���� � ��������� ����, ������������� ���������� ������ ��������
���������� 1 ��� ���������� ��������� ���������
*/
int main();

/*
������������ ���� � �������
lvl_array - �������, size - ������ �������
���������� 1 ��� �������� ��������� ����
*/
int pitch(int**, unsigned int);

/*
������������ ����� ������������� ������� � �������
size_lines - ������ �������������� �����
���������� 1 ���� ��������� ����� ������ �������
*/
int draw_lines(int);

/*
������ � ������� �������� �� ����������� ������� [�����\�����] �� ����� ��������
lvl_array - �������, letter - ����� ����������, digit - ����� ����������, value - ����� ��������
���������� 1 ��� �������� ����� ������
*/
int change_cell(int**, char, int, int);

/*
������� � ������� ���� ������ ������, ���� ������������ ������� ����� ������ �� ��� ������
���������� ��������� �� ������, ���������� ������� ����� � ������� ������
*/
int choice_level(char*, int*);

/*
������� ����, ��������� �� �������� ����, ���������� �������� ��� ��������� �������
lvl_array - �������, size - ������ �������
���������� 1 ��� ��������� ���� �������������
*/
int play_menu(int**, int);

/*
��������� �������, � ������ � ����� �� ���� (���� �� ������� ������ ��� ����������)
lvl_array - ������� � ������� ������������ �������� �� �����, size - ������ �������, path - ���� � �����
���������� 1 ��� �������� �������� � �����
*/
int load_game(int***, unsigned int*, char[]);

/*
������� ��������� ����� �� �������
lvl_array - �������, size - ������ �������, difficult - ���������� ��� ������� ���������
���������� 1 ��� �������� �������� �����
*/
int delete_digits(int**, unsigned int, int);

/*
���������� ��������� ����� �� 0 �� max
max - ������������ ������������ �����
���������� ��������� �����
*/
int random_number(int);

/*
��������� ������ �� ������������ � ������ ����-���� (��\���)
���������� 1 - ���� ��, 0 - ���� ���
*/
int request_choice();

/*
���������� � ������������ ���������� ������(�������[����� / �����]) �, �������� ������������ ��������� ������,
����������� ��� ���������� ��������� �� ����
lvl_array - �������, size - ������ �������, choice_digit - ��������� ����� ����������, choice_letter - ��������� ����� ����������
���������� 1 ��� �������� ������ ��������� �������������
*/
int choice_cell(int**, int, int*, int*);

/*
���������� � ������������ ����� ��� ���������� ������ �, �������� ������������ ���������� �����,
����������� ��� ���������� ����� �� ����
lvl_array - �������, size - ������ �������, new_value - ����� ��������, �������� �������������)
���������� 1 ��� �������� ������ ������ ��������
*/
int choice_value(int**, unsigned int, int*);

/*
���������� � ������������ ��������� �� ���� �, ��� �������������� ������, ��������� � ���� ��������� ������� � � ������
lvl_array - �������, size - ������ �������
���������� 1 ��� ������� ������������ ���������� ����
*/
int choice_exit(int**, unsigned int);

/*
���� ������ ��������� (�����, ������, ������)
difficult - ���������� ���������
���������� 1 ��� �������� ����� ���������
*/
int choice_difficult(int*);

/*
��������� ������� � � ������ �� ���������� ����
lvl_array - �������, size - ������ �������, path - ���� � ����� ��� ����������
���������� 1 ��� �������� ���������� � ����
*/
int save_game(int**, unsigned int, char[]);

int main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "ru");
    puts("��������� (�Numbrix�) - ��� ���������� �����������.\n������������ ����� ������������� �����, � ��������� ������� ������� ����� �����. \n��������� ��������� ������ ������ ����� �������, ����� ��� ����� ���� ��������� ���������������,\n�� ����������� ��� ���������.\n����������� �� ��������� �� �����������.");
    int level_number = 1;                       /* ����� ������������ ������ (������� - 1) */
    int user_choice = -1;                       /* ����� ������, ���������� ������������� */
    int difficult = 2;                          /* ����������� ��������� */
    int** level_choice = NULL;                  /* ������� ����� ��� ���� */
    unsigned int size;                          /* ������ ������� */
    char level_path[20] = "level_1.txt\0";      /* ���� � ������ (������� � ������ 1) */
    static char save_path[] = "saves.txt\0";    /* ���� � ����� � ����������� */
    srand(time(NULL));                          /* �������������� ��������� ��������� ����� */
    /* ���� ������ */
    while (1)
    {
        puts("�������� ��������: ");
        puts("1)������\n2)������� �������\n3)��������� ����������\n4)������� ��������� ����\n5)����� �� ����\nV");
        scanf("%d", &user_choice);
        switch (user_choice)
        {
        case 1:
            /* ������� "������" */
            printf("\n������� - %d", level_number);
            if (level_number > 0)
            {
                load_game(&level_choice, &size, level_path);
                delete_digits(level_choice, size, difficult);
            }
            play_menu(level_choice, size);
            return 1;
        case 2:
            /* ������� "������� �������" */
            puts("...����� ������...");
            choice_level(level_path, &level_number);
            printf("������ �������: %d\n", level_number);
            break;
        case 3:
            /* ������� "��������� ����������" */
            puts("...�������� ����������...");
            load_game(&level_choice, &size, save_path);
            level_number = 0;
            puts("...���������� ���������...");
            break;
        case 4:
            /* ������� "������� ��������� ����" */
            choice_difficult(&difficult);
            break;
        case 5:
            /* ������� "����� �� ����" */
            puts("...���������� ����...");
            return 1;
        default:
            /* ������ ������ ������ */
            puts("������ �������� �����, ���������� ��� ���");
            break;
        }
    }
}

// ������� ��� ������ � ��������
int delete_digits(int** lvl_array, unsigned int size, int difficult)
{
    double difficult_parametr = (double)(size * size - 1) / 8. + 1;
    int max = difficult_parametr * difficult; // ������������ ����� ������ ����� � �������
    for (int counter = 0; counter < max; counter++)
        lvl_array[random_number(size - 1)][random_number(size - 1)] = 0;
    return 1;
}

int random_number(int max)
{
    return (rand() % max) + 1;
}

int change_cell(int** lvl_array, int letter, int digit, int value)
{
    digit -= 1; // ����� ���������� �� 1 ��� ��������� ������ ������� �������
    lvl_array[letter][digit] = value;
    return 1;
}

int play_menu(int** lvl_array, int size)
{
    while (1)
    {
        int choice_digit, choice_letter, new_value;
        puts("\n...������ ����...");
        /* ��������� ���� */
        pitch(lvl_array, size);
        /* ����� ������ */
        choice_cell(lvl_array, size, &choice_digit, &choice_letter);
        /* ���� �������� */
        choice_value(lvl_array, size, &new_value);
        /* ��������� �������� � ������ */
        change_cell(lvl_array, choice_letter, choice_digit, new_value);
        /* ��������� ���������� ���� */
        pitch(lvl_array, size);
        /* ���������� � ����� ��� ������� */
        if (choice_exit(lvl_array, size) == 1)
            return 1;
    }
}

// ������� ��� �������������� � �������������

int choice_level(char* level_path, int* level_number)
{
    int level_choice = -1;
    while (1) {
        puts("�������� �������\n1) ������� 1 (������ 6�6)\n2) ������� 2 (������ 5�5)\n3) ������� 3 (������ 4�4)\n������� ����� ������\nV");
        scanf("%d", &level_choice);
        /* ��������� ������������ ���������� ������ ������ */
        if (level_choice > 0 && level_choice < 4) {
            printf("��� ����� ������� %d\n�� �������?\n", level_choice);
            if (request_choice() == 1) {
                sprintf(level_path, "level_%d.txt\0", level_choice); // ��������� ���� � ����� ������
                *level_number = level_choice; // ��������� ����� ������
                return 1;
            }
            else puts("\n�������� ��� ���!");
        }
        else puts("\n������������ ����� ������, ���������� ��� ���!");
    }
}

int choice_cell(int** lvl_array, int size, int* choice_digit, int* choice_letter)
{
    char letter; // ����� ���������� ����
    int digit;   // ����� ���������� ����
    while (1)
    {
        puts("\n�������� ������\n�����\nV");
        getchar();
        scanf("%c", &letter);
        puts("\n�����\nV");
        scanf("%d", &digit);

        // �������� ������������ ��������� ��������� ������
        if (letter - 'A' < 0 || letter - 'A' >= size || digit < 1 || digit > size || lvl_array[letter - 'A'][digit - 1] < 0)
            puts("\n������������ ����� ������!\n���������� ��� ���");
        else
        {
            printf("��� ����� --> [%c%d]\n�� �������?[y/n]\nV\n", letter, digit);
            if (request_choice() == 1)
            {
                *choice_digit = digit;
                *choice_letter = letter - 'A';
                return 1;
            }
        }
    }
}

int choice_value(int** lvl_array, unsigned int size, int* new_value)
{
    int value;
    int exist; /* ���������� ����������� ���� �� �������� ��� �� ����(1 - ��; 0 - ���) */
    while (1)
    {
        puts("������� ��������\nV");
        scanf("%d", &value);
        if (value > 0)
        {
            /* �������� ���� �� ��� �������� � ������� */
            exist = 0;
            for (int letter = 0; letter < size; letter++)
            {
                for (int digit = 0; digit < size; digit++)
                {
                    if ((int)fabs(lvl_array[letter][digit]) == value)
                    {
                        printf("�������� ��� ���� �� ����!\n");
                        exist = 1;
                        break;
                    }
                    if (exist == 1) break;
                }
                if (exist == 1) break;
            }
            if (exist == 0)
            {
                printf("��� ����� ��������--> [%d]\n�� �������?[y/n]\nV\n", value);
                if (request_choice() == 1)
                    *new_value = value;
                return 1;
            }
        }
        printf("������� ������!\n");
    }
}

int choice_exit(int** lvl_array, unsigned int size)
{
    puts("\n��������� � ��������� ���� � ����?[y/n]");
    char save_path[] = "saves.txt\0";
    if (request_choice() == 1)
    {
        save_game(lvl_array, size, save_path);
        return 1;
    }
}

int choice_difficult(int* difficult)
{
    puts("...����� ���������...");
    int dif_choice; // �������� �������� ���������, ������������ ��� �������� �������
    puts("\n��������� ���������:\n1)�����\n2)������\n3)������");
    while (1)
    {
        puts("������� ����� ������\nV");
        scanf("%d", &dif_choice);

        if (1 <= dif_choice && dif_choice <= 3)
        {
            // �������� ������������ ������ ������
            printf("�� ������� � ������ ���������?\n");
            if (request_choice() == 1)
            {
                *difficult = 1 + dif_choice;
                return 1;
            }
        }
        puts("\n����� ������������ ����� ������, ���������� ��� ���");
    }
}

int request_choice()
{
    char request;
    while (1)
    {
        getchar();
        scanf("%c", &request);
        request = tolower(request);
        if (request == 'y')
            return 1;
        if (request == 'n')
            return 0;
        puts("���, ������ [y/n]");
    }
}

// ������� ��� ��������� ����
int draw_lines(int size_lines)
{
    for (int i = 0; i < size_lines; i++)
    {
        if (i == 0) printf("%2c", ' ');
        printf("%c", '-');
    }
    printf("\n");
    return 1;
}

int pitch(int** lvl_array, unsigned int size)
{
    int size_lines = size * 5 + 1; // ���������� �������������� ����� ��� ��������� ����� ("---")
    printf("%4c", ' ');
    for (int cell = 0; cell < size; cell++)
        printf("%3d  ", cell + 1);
    printf("\n");
    draw_lines(size_lines);
    for (int letter = 0; letter < size; letter++)
    {
        printf("%c ", 'A' + letter);
        for (int digit = 0; digit < size; digit++)
        {
            if (lvl_array[letter][digit] != 0)
                printf("|%3d ", (int)fabs(lvl_array[letter][digit]));
            else
                printf("|%4c", ' ');
        }
        printf("|\n");
        draw_lines(size_lines);
    }
    return 1;
}

// ������� ��� ������ � �������
int save_game(int** lvl_array, unsigned int size, char path[])
{
    FILE* file;
    file = fopen(path, "w");
    if (file == NULL)
    {
        perror("������ �������� ����� ��� ������");
        return 0;
    }

    fprintf(file, "%u\n", size);
    for (int letter = 0; letter < size; letter++)
    {
        for (int digit = 0; digit < size; digit++)
        {
            fprintf(file, "%d ", lvl_array[letter][digit]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("��������� � %s\n", path);
    puts("...���������...");
    return 1;
}

int load_game(int*** lvl_array, unsigned int* size, char path[])
{
    FILE* file;
    file = fopen(path, "r");
    if (file == NULL)
    {
        perror("������ �������� ����� ��� ������");
        return 0;
    }
    fscanf(file, "%u", size);
    *lvl_array = (int**)malloc(*size * sizeof(int*));
    if (*lvl_array == NULL)
    {
        perror("������ ��������� ������ ��� �������");
        fclose(file);
        return 0;
    }
    for (int letter = 0; letter < *size; letter++)
    {
        (*lvl_array)[letter] = (int*)malloc(*size * sizeof(int));
        if ((*lvl_array)[letter] == NULL) {
            perror("������ ��������� ������ ��� ������");
            fclose(file);
            return 0;
        }

        for (int digit = 0; digit < *size; digit++)
        {
            fscanf(file, "%d", &(*lvl_array)[letter][digit]);
        }
    }
    fclose(file);
    return 1;
}