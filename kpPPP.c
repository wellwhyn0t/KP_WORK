#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/*
выводит в консоль главное меню с описанием игры, предоставляет функционал выбора действий
возвращает 1 при корректной отработке программы
*/
int main();

/*
отрисовывает поле в консоли
lvl_array - матрица, size - размер матрицы
возвращает 1 при успешной отрисовки поля
*/
int pitch(int**, unsigned int);

/*
отрисовывает линии определенного размера в консоли
size_lines - размер горизонтальной линии
возвращает 1 если отрисовка линии прошла успешно
*/
int draw_lines(int);

/*
меняет в матрице значение по координатам формата [БУКВА\ЦИФРА] на новое значение
lvl_array - матрица, letter - буква координаты, digit - число координаты, value - новое значение
возвращает 1 при успешной смене ячейки
*/
int change_cell(int**, char, int, int);

/*
выводит в консоль меню выбора уровня, дает пользователю сделать выбор уровня по его номеру
возвращает указатель на строку, являющуюся адресом файла с текстом уровня
*/
int choice_level(char*, int*);

/*
игровое меню, вызванное из главного меню, проводящее действия для изменения матрицы
lvl_array - матрица, size - размер матрицы
возвращает 1 при окончании игры пользователем
*/
int play_menu(int**, int);

/*
загружает матрицу, её размер с файла по пути (будь то матрица уровня или сохранения)
lvl_array - матрица в которую записываются значения из файла, size - размер матрицы, path - путь к файлу
возвращает 1 при успешной загрузки с файла
*/
int load_game(int***, unsigned int*, char[]);

/*
удаляет случайные числа из матрицы
lvl_array - матрица, size - размер матрицы, difficult - коэффицент для расчёта сложности
возвращает 1 при успешном удалении чисел
*/
int delete_digits(int**, unsigned int, int);

/*
генерирует случайное число от 0 до max
max - максимальное генерируемое число
возвращает случайное число
*/
int random_number(int);

/*
проверяет уверен ли пользователь в выборе чего-либо (да\нет)
возвращает 1 - если да, 0 - если нет
*/
int request_choice();

/*
спрашивает у пользователя координаты ячейки(формата[БУКВА / ЦИФРА]) и, проверив корректность выбранной ячейки,
присваивает его переменным координат из меню
lvl_array - матрица, size - размер матрицы, choice_digit - выбранная цифра координаты, choice_letter - выбранная буква координаты
возвращает 1 при успешном выборе координат пользователем
*/
int choice_cell(int**, int, int*, int*);

/*
спрашивает у пользователя число для заполнения ячейки и, проверив корректность выбранного числа,
присваивает его переменной числа из меню
lvl_array - матрица, size - размер матрицы, new_value - новое значение, вводимое пользователем)
возвращает 1 при успешном выборе нового значения
*/
int choice_value(int**, unsigned int, int*);

/*
спрашивает у пользователя закончить ли игру и, при утвердительном ответе, сохраняет в файл сыгранную матрицу и её размер
lvl_array - матрица, size - размер матрицы
возвращает 1 при желании пользователя продолжить игру
*/
int choice_exit(int**, unsigned int);

/*
меню выбора сложности (Легко, Средне, Сложно)
difficult - коэффицент сложности
возвращает 1 при успешной смене сложности
*/
int choice_difficult(int*);

/*
сохраняет матрицу и её размер по указанному пути
lvl_array - матрица, size - размер матрицы, path - путь к файлу для сохранения
возвращает 1 при успешном сохранении в файл
*/
int save_game(int**, unsigned int, char[]);

int main()
{
    system("chcp 1251");
    setlocale(LC_ALL, "ru");
    puts("Нумератор («Numbrix») - вид логической головоломки.\nПредставляет собой прямоугольную сетку, в некоторых клетках которой стоят числа. \nТребуется заполнить пустые клетки таким образом, чтобы все числа были соединены последовательно,\nпо горизонтали или вертикали.\nПеремещение по диагонали не допускается.");
    int level_number = 1;                       /* номер запускаемого уровня (исходно - 1) */
    int user_choice = -1;                       /* номер пункта, выбираемый пользователем */
    int difficult = 2;                          /* коэффициент сложности */
    int** level_choice = NULL;                  /* матрица чисел для игры */
    unsigned int size;                          /* размер матрицы */
    char level_path[20] = "level_1.txt\0";      /* путь к уровню (исходно к уровню 1) */
    static char save_path[] = "saves.txt\0";    /* путь к файлу с сохранением */
    srand(time(NULL));                          /* инициализирует генератор случайных чисел */
    /* меню выбора */
    while (1)
    {
        puts("Выберите действие: ");
        puts("1)Играть\n2)Выбрать уровень\n3)Загрузить сохранение\n4)Сменить сложность игры\n5)Выйти из игры\nV");
        scanf("%d", &user_choice);
        switch (user_choice)
        {
        case 1:
            /* выбрано "Играть" */
            printf("\nУровень - %d", level_number);
            if (level_number > 0)
            {
                load_game(&level_choice, &size, level_path);
                delete_digits(level_choice, size, difficult);
            }
            play_menu(level_choice, size);
            return 1;
        case 2:
            /* выбрано "Выбрать уровень" */
            puts("...выбор уровня...");
            choice_level(level_path, &level_number);
            printf("Выбран уровень: %d\n", level_number);
            break;
        case 3:
            /* выбрано "Загрузить сохранение" */
            puts("...загрузка сохранения...");
            load_game(&level_choice, &size, save_path);
            level_number = 0;
            puts("...сохранение загружено...");
            break;
        case 4:
            /* выбрано "Сменить сложность игры" */
            choice_difficult(&difficult);
            break;
        case 5:
            /* выбрано "Выйти из игры" */
            puts("...выключение игры...");
            return 1;
        default:
            /* ошибка выбора пункта */
            puts("Выбран неверный пункт, попробуйте ещё раз");
            break;
        }
    }
}

// Функции для работы с матрицей
int delete_digits(int** lvl_array, unsigned int size, int difficult)
{
    double difficult_parametr = (double)(size * size - 1) / 8. + 1;
    int max = difficult_parametr * difficult; // максимальное число пустых полей в матрице
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
    digit -= 1; // число понижается на 1 для получения именно индекса матрицы
    lvl_array[letter][digit] = value;
    return 1;
}

int play_menu(int** lvl_array, int size)
{
    while (1)
    {
        int choice_digit, choice_letter, new_value;
        puts("\n...запуск игры...");
        /* отрисовка поля */
        pitch(lvl_array, size);
        /* выбор ячейки */
        choice_cell(lvl_array, size, &choice_digit, &choice_letter);
        /* ввод значения */
        choice_value(lvl_array, size, &new_value);
        /* изменения значения в ячейке */
        change_cell(lvl_array, choice_letter, choice_digit, new_value);
        /* отрисовка изменённого поля */
        pitch(lvl_array, size);
        /* сохранение и выход при желании */
        if (choice_exit(lvl_array, size) == 1)
            return 1;
    }
}

// Функции для взаимодействия с пользователем

int choice_level(char* level_path, int* level_number)
{
    int level_choice = -1;
    while (1) {
        puts("Выберите уровень\n1) Уровень 1 (размер 6х6)\n2) Уровень 2 (размер 5х5)\n3) Уровень 3 (размер 4х4)\nВведите номер уровня\nV");
        scanf("%d", &level_choice);
        /* проверяем корректность введенного номера уровня */
        if (level_choice > 0 && level_choice < 4) {
            printf("Ваш выбор уровень %d\nВы уверены?\n", level_choice);
            if (request_choice() == 1) {
                sprintf(level_path, "level_%d.txt\0", level_choice); // Формируем путь к файлу уровня
                *level_number = level_choice; // Обновляем номер уровня
                return 1;
            }
            else puts("\nВыберите ещё раз!");
        }
        else puts("\nНекорректный номер уровня, попробуйте ещё раз!");
    }
}

int choice_cell(int** lvl_array, int size, int* choice_digit, int* choice_letter)
{
    char letter; // буква координаты поля
    int digit;   // число координаты поля
    while (1)
    {
        puts("\nВыберите ячейку\nБуква\nV");
        getchar();
        scanf("%c", &letter);
        puts("\nЧисло\nV");
        scanf("%d", &digit);

        // проверка корректности выбранных координат ячейки
        if (letter - 'A' < 0 || letter - 'A' >= size || digit < 1 || digit > size || lvl_array[letter - 'A'][digit - 1] < 0)
            puts("\nНекорректный выбор ячейки!\nПопробуйте ещё раз");
        else
        {
            printf("Ваш выбор --> [%c%d]\nВы уверены?[y/n]\nV\n", letter, digit);
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
    int exist; /* переменная указывающая есть ли значение уже на поле(1 - да; 0 - нет) */
    while (1)
    {
        puts("Введите значение\nV");
        scanf("%d", &value);
        if (value > 0)
        {
            /* проверка есть ли уже значение в матрице */
            exist = 0;
            for (int letter = 0; letter < size; letter++)
            {
                for (int digit = 0; digit < size; digit++)
                {
                    if ((int)fabs(lvl_array[letter][digit]) == value)
                    {
                        printf("Значение уже есть на поле!\n");
                        exist = 1;
                        break;
                    }
                    if (exist == 1) break;
                }
                if (exist == 1) break;
            }
            if (exist == 0)
            {
                printf("Ваш выбор значения--> [%d]\nВы уверены?[y/n]\nV\n", value);
                if (request_choice() == 1)
                    *new_value = value;
                return 1;
            }
        }
        printf("Введите заново!\n");
    }
}

int choice_exit(int** lvl_array, unsigned int size)
{
    puts("\nЗакончить и сохранить поле в файл?[y/n]");
    char save_path[] = "saves.txt\0";
    if (request_choice() == 1)
    {
        save_game(lvl_array, size, save_path);
        return 1;
    }
}

int choice_difficult(int* difficult)
{
    puts("...смена сложности...");
    int dif_choice; // вводимое значение сложности, используемое для проверки условия
    puts("\nДоступные сложности:\n1)Легко\n2)Средне\n3)Сложно");
    while (1)
    {
        puts("Введите номер уровня\nV");
        scanf("%d", &dif_choice);

        if (1 <= dif_choice && dif_choice <= 3)
        {
            // проверка корректности выбора уровня
            printf("Вы уверены в выборе сложности?\n");
            if (request_choice() == 1)
            {
                *difficult = 1 + dif_choice;
                return 1;
            }
        }
        puts("\nВведён некорректный номер уровня, попробуйте ещё раз");
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
        puts("Нет, выбери [y/n]");
    }
}

// Функции для отрисовки поля
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
    int size_lines = size * 5 + 1; // количество горизонтальных линий для отделения строк ("---")
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

// Функции для работы с файлами
int save_game(int** lvl_array, unsigned int size, char path[])
{
    FILE* file;
    file = fopen(path, "w");
    if (file == NULL)
    {
        perror("Ошибка открытия файла для записи");
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
    printf("Сохранено в %s\n", path);
    puts("...сохранено...");
    return 1;
}

int load_game(int*** lvl_array, unsigned int* size, char path[])
{
    FILE* file;
    file = fopen(path, "r");
    if (file == NULL)
    {
        perror("Ошибка открытия файла для чтения");
        return 0;
    }
    fscanf(file, "%u", size);
    *lvl_array = (int**)malloc(*size * sizeof(int*));
    if (*lvl_array == NULL)
    {
        perror("Ошибка выделения памяти для матрицы");
        fclose(file);
        return 0;
    }
    for (int letter = 0; letter < *size; letter++)
    {
        (*lvl_array)[letter] = (int*)malloc(*size * sizeof(int));
        if ((*lvl_array)[letter] == NULL) {
            perror("Ошибка выделения памяти для списка");
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