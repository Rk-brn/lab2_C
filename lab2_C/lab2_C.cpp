// lab2_C.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 30 //Максимальная длина имени
#define MAX_PASSWORD_LEN 30 //Максимальная длина пароля

// Структура для хранения информации о пользователе
struct User {
    int id;
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
    float balance;
};

// Структура для хранения информации о финансовой операции
struct Finance {
    int user_id;
    float income;
    float expense;
};

//Подсчёт количества пользователей
int getUser() {
    FILE* file = fopen("User.txt", "r");
    if (file == NULL) {
        return 0;
    }
    int countUser = 0;
    fprintf(file, "%d\n", countUser);
    fclose(file);
    return countUser;
}
//Создание нового пользователя
User creat(int id) {
    User newUser;
    newUser.id = id;
    printf("\nВведите имя: ");
    scanf("%s", &newUser.username);
    printf("\nВведите пароль: ");
    scanf("%s", &newUser.password);
    newUser.balance = 0.0f;
    return newUser;
}

// Функция для чтения аккаунтов из файла
void loadAccounts(User accounts[], int* accountCount) {
    FILE* file = fopen("User.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла User.txt\n");
        return;
    }
    fscanf(file, "%d", accountCount); // Считываем количество пользователей
    for (int i = 0; i < *accountCount; i++) {
        fscanf(file, "%d %s %s %f", &accounts[i].id,
            accounts[i].username,
            accounts[i].password,
            &accounts[i].balance);
    }
    fclose(file);
}

// Функция для сохранения аккаунтов в файл
void saveAccounts(User accounts[], int accountCount) {
    FILE* file = fopen("User.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла User.txt\n");
        return;
    }
    fprintf(file, "%d\n", accountCount); // Сохраняем количество пользователей
    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%d %s %s %.2f\n", accounts[i].id,
            accounts[i].username,
            accounts[i].password,
            accounts[i].balance);
    }
    fclose(file);
}

// Функция входа в систему
User* login(User accounts[], int accountCount) {
    char nickname[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int flag = 0;
    int j = 3;
    do {
        printf(" У вас есть количетсво попыток: %d", j);
        printf("\nВведите никнейм: ");
        scanf("%s", nickname);
        printf("Введите пароль: ");
        scanf("%s", password);

        for (int i = 0; i < accountCount; i++) {
            if (strcmp(accounts[i].username, nickname) == 0 &&
                strcmp(accounts[i].password, password) == 0) {
                flag = 3;
                printf("Вход выполнен! Ваш баланс: %.2f\n", accounts[i].balance);
                return &accounts[i];
            }
        }
        flag++;
        j = 3 - flag;
        if (flag <= 2) printf("Неправильный никнейм или пароль.\nПовторите попытку заново.");

    } while (flag <= 2);
    printf("Вы ввели три раза неправильно данные, поэтому системой будет предложен создать новый аккаунт.\n");
    return NULL;
}

// Функция для добавления дохода/расхода
void addFinanceEntry(int userId, float income, float expense) {
    FILE* file = fopen("Finance.txt", "a");
    if (file == NULL) {
        printf("Ошибка при открытии файла Finance.txt\n");
        return;
    }
    fprintf(file, "%d %.2f %.2f\n", userId, income, expense);
    fclose(file);
}

// Функция для отображения финансового отчета
void viewFinanceReport(int userId) {
    FILE* file = fopen("Finance.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла Finance.txt\n");
        return;
    }
    
    float totalIncome = 0.0f, totalExpense = 0.0f;
    int found = 0;
    Finance entry;

    while (fscanf(file, "%d %f %f", &entry.user_id, &entry.income, &entry.expense) != EOF) {
        if (entry.user_id == userId) {
            totalIncome += entry.income;
            totalExpense += entry.expense;
            found = 1;
        }
    }

    if (found) {
        
        printf("Общий доход: %.2f, Общий расход: %.2f\n", totalIncome, totalExpense);
    }
    else {
        printf("Не найдено финансовых записей для этого пользователя.\n");
    }

    fclose(file);
}

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Добро пожаловаться в программное обеспечение по учёту финансов!\nДля успешной работы следуйте инструкциям ниже.");
    int count; //Количество пользователей программы
    
    count = getUser();
   
    User* accounts = (User*)calloc(count, sizeof(User));
    loadAccounts(accounts, &count);
    int choise; //Выбор действия
    do {
        printf("\nВыберите действие:\n1 - Войти в аккаунт\n2 - Создать аккаунт\n");
        scanf("%d", &choise);
        if (count == 0 && choise == 1) {
            printf("Пользователь нет! Войти в аккаунт нельзя!"); choise = 0;
        }
    } while (choise != 1 && choise != 2);
    User* currentUser = NULL;
    if (choise == 1){
        currentUser = login(accounts, count);
    }
    if (choise == 2 || currentUser == NULL) {
        User NewUser = creat(count + 1);
        accounts[count] = NewUser; // Добавляем нового пользователя в массив
        count++; // Увеличиваем счетчик пользователей
        saveAccounts(accounts, count); // Сохраняем изменённые данные в файл
        currentUser = &accounts[count - 1]; // Указываем на нового пользователя
        printf("Аккаунт создан! Ваш баланс: %.2f\n", currentUser->balance);
    }
    // Если пользователь вошел в систему
    if (currentUser != NULL) {
        char action;
        do {
            printf("Введите 'I' для добавления дохода, 'E' для добавления расхода, 'R' для просмотра отчета, 'Q' для выхода: ");
            scanf(" %c", &action);

            switch (action) {
            case 'I':
            {
                float income;
                printf("Введите сумму дохода: ");
                scanf("%f", &income);
                addFinanceEntry(currentUser->id, income, 0);
                currentUser->balance += income;
                printf("Доход добавлен! Ваш новый баланс: %.2f\n", currentUser->balance);
                break;
            }
            case 'E':
            {
                float expense;
                printf("Введите сумму расхода: ");
                scanf("%f", &expense);
                addFinanceEntry(currentUser->id, 0, expense);
                currentUser->balance -= expense;
                printf("Расход добавлен! Ваш новый баланс: %.2f\n", currentUser->balance);
                break;
            }
            case 'R':
                viewFinanceReport(currentUser->id);
                break;
            case 'Q':
                saveAccounts(accounts, count);
                printf("Вы вышли из системы.\n");
                break;
            default:
                printf("Неверный ввод.\n");
                break;
            }
        } while (action != 'Q');
    }

    return 0;
   
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
