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

//Структура для хранения информации о пользователе
struct User {
    int id; //Уникальный id пользователей
    char username[MAX_USERNAME_LEN + 1]; //Имя пользователя 
    char password[MAX_PASSWORD_LEN + 1]; //Пароль пользователя
    int balance; //Баланс пользователя (в копейках)
    struct Account* primaryAccount;  // Основной счет пользователя
    struct Goal* goal;
    struct Contribution* contribution;
    struct Loan* loan;
};


// Структура для хранения информации о счете
struct Account {
    char name[50];     // Название счета
    struct User* user;    // Указатель на владельца счета
    struct Transaction* transactions; // Список транзакций на счете
    struct Account* next;  // Указатель на следующий счет в списке
};

// Структура для хранения информации о цели
struct Goal {
    char name[50];            // Название цели (например, "Отпуск", "Автомобиль")
    float targetAmount;       // Целевая сумма 
    float savedAmount;        // Сумма, накопленная на данный момент
    struct User* user;        // Указатель на владельца цели
    struct Goal* next;        // Указатель на следующую цель в списке
};


struct Transaction {
    char description[100]; // Описание транзакции
    float amount;          // Сумма транзакции
    char date[11];        // Дата транзакции (DD-MM-YYYY)
    char type[10];        // Тип транзакции (доход/расход)
    struct Account* Account; // Счет, к которому относится транзакция
    struct Category* category; // Категория, к которой относится транзакция
    struct Transaction* next;  // Указатель на следующую транзакцию в списке
};

struct Contribution {
    int percent; //годовые проценты
    int minimum_deposit; //минимальный взнос на вклад  
    struct User* user; //Указатель на пользователя
    struct Contribution* next;
};
//Структура для конвертации баланс в три основные валюты 
struct Conversion {
    int USD; //доллар (цент)
    int EUR; //евро (евроцент)
    int CNY; //юань (фынь)
    struct User* user;
};


// Структура для хранения информации о категории
struct Category {
    char name[50];         // Название категории (например, "Продукты", "Транспорт")
    struct Category* next;  // Указатель на следующую категорию в списке
};


// Структура для кредитов 
struct Loan {
    int amount;              // Сумма кредита
    int interestRate;        // Процентная ставка
    struct User* user;         // Указатель на главную структуру User
    struct Loan* next;         // Указатель на следующий кредит
} Loan;

struct Analytics {
    int totalIncome;
    int totalExpense;
    struct User* user;
    struct Account* Account;
};

// Функция для создания нового пользователя
struct User* createUser(int id, char* username, char* password) {
    struct User* newUser = (User*)malloc(sizeof(struct User));
    if (newUser == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    newUser->id = id;
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->balance = 0;
    newUser->primaryAccount = NULL; // Пока нет счета
    return newUser;
}

// Функция для добавления нового счета
struct Account* createAccount(char* name, struct User* user) {
    struct Account* newAccount = (Account*)malloc(sizeof(struct Account));
    if (newAccount == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    strcpy(newAccount->name, name);
    newAccount->user = user;
    newAccount->transactions = NULL; // Пока нет транзакций
    newAccount->next = NULL;
    return newAccount;
}

// Функция для добавления новой транзакции
struct Transaction* createTransaction(char* description, float amount, char* date, char* type, struct Account* account, struct Category* category) {
    struct Transaction* newTransaction = (Transaction*)malloc(sizeof(struct Transaction));
    if (newTransaction == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    strcpy(newTransaction->description, description);
    newTransaction->amount = amount;
    strcpy(newTransaction->date, date);
    strcpy(newTransaction->type, type);
    newTransaction->Account = account;
    newTransaction->category = category;
    newTransaction->next = NULL;
    return newTransaction;
}

// Функция для добавления новой цели
struct Goal* createGoal(char* name, int targetAmount, int savedAmount, struct User* user) {
    struct Goal* newGoal = (Goal*)malloc(sizeof(struct Goal));
    if (newGoal == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    strcpy(newGoal->name, name);
    newGoal->targetAmount = targetAmount;
    newGoal->savedAmount = savedAmount;
    newGoal->user = user;
    newGoal->next = NULL;
    return newGoal;
}

// Функция для добавления нового вклада
struct Contribution* createContribution(int percent, int minimum_deposit, struct User* user) {
    struct Contribution* newContribution = (Contribution*)malloc(sizeof(struct Contribution));
    if (newContribution == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    newContribution->percent = percent;
    newContribution->minimum_deposit = minimum_deposit;
    newContribution->user = user;
    return newContribution;
}

// Функция для добавления новой конвертации 
struct Conversion* createConversion(int USD, int EUR, int CNY, struct User* user) {
    struct Conversion* newConversion = (Conversion*)malloc(sizeof(struct Conversion));
    if (newConversion == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    newConversion->USD = USD;
    newConversion->EUR = EUR;
    newConversion->CNY = CNY;
    newConversion->user = user;
    return newConversion;
}

// Функция для добавления новой категории
struct Category* createCategory(char* name) {
    struct Category* newCategory = (Category*)malloc(sizeof(struct Category));
    if (newCategory == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    strcpy(newCategory->name, name);
    newCategory->next = NULL;
    return newCategory;
}

struct Loan* createLoan(int amount, int interestRate, struct User* user) {
    struct Loan* newLoan = (Loan*)malloc(sizeof(struct Loan));
    if (newLoan == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    newLoan->amount = amount;
    newLoan->interestRate = interestRate;
    newLoan->user = user;
    newLoan->next = NULL;
    return newLoan;
}

// Функция для добавления новой аналитики
struct Analytics* createAccountAnalytics(struct User* user) {
    struct Analytics* analytics = (Analytics*)malloc(sizeof(struct Analytics));
    if (analytics == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    analytics->totalIncome = 0;
    analytics->totalExpense = 0;
    analytics->user = user;
    return analytics;
}

// Функция для добавления транзакции в список транзакций
void addTransactionToAccount(struct Transaction* transaction, struct Account* account) {
    if (account->transactions == NULL) {
        account->transactions = transaction;
    }
    else {
        struct Transaction* current = account->transactions;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = transaction;
    }
}

// Функция для обновления аналитики счета
void updateAccountAnalytics(struct Analytics* analytics, char* type, int amount) {
    if (strcmp(type, "income") == 0) {
        analytics->totalIncome += amount;
    }
    else if (strcmp(type, "expense") == 0) {
        analytics->totalExpense += amount;
    }
}

// Функция для добавления цели в список целей
void addGoalToUser(struct Goal* goal, struct User* user) {
    if (user->goal == NULL) {
        user->goal = goal;
    }
    else {
        struct Goal* current = user->goal;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = goal;
    }
}

// Функция для добавления вклада в список вкладов
void addContributionToUser(struct Contribution* contribution, struct User* user) {
    if (user->contribution == NULL) {
        user->contribution = contribution;
    }
    else {
        struct Contribution* current = user->contribution;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = contribution;
    }
}


// Функция для добавления кредита в список кредитов
void addLoanToUser(struct Loan* loan, struct User* user) {
    if (user->loan == NULL) {
        user->loan = loan;
    }
    else {
        struct Loan* current = user->loan;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = loan;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Добро пожаловаться в программное обеспечение по учёту финансов!\nДля успешной работы следуйте инструкциям ниже.");
    
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
