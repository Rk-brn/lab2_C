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


int main() {
    setlocale(LC_ALL, "Rus");
    printf("Добро пожаловаться в программное обеспечение по учёту финансов!\nДля успешной работы следуйте инструкциям ниже.");
    int count; //Количество пользователей программы
    User* currentUser = (User*)malloc(sizeof(User));
    count = getUser();
    if (count == 0) {
        FILE* file = fopen("User.txt", "w");
    }
    int choise; //Выбор действия
    do {
        printf("\nВыберите действие:\n1 - Войти в аккаунт\n2 - Создать аккаунт\n");
        scanf("%d", &choise);
        if (count == 0 && choise == 1) {
            printf("Пользователь нет! Войти в аккаунт нельзя!"); choise = 0;
        }
    } while (choise != 1 && choise != 2);
    if (choise == 1){}
    else if (choise == 2) {
        User NewUser = creat(count + 1);
    }
   
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
