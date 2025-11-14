#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// функция сохранения результатов операций в файл output.txt
void save(string text)
{
    ofstream f("output.txt"); // создаём и открываем файл
    if (f.is_open()){ // проверяем успешное открытие файла
        f << text << endl; // записываем текст
        f.close(); // закрываем файл
    }
}

// создание и заполнение данными файла books.txt
void addBooks()
{
    ofstream f("books.txt");
    string t, a; // переменные для названия и автора
    int y; // переменная для года
    while (cout << "Название: ", getline(cin, t), !t.empty()) // цикл ввода данных до пустой строки
    {
        cout << "Автор: "; getline(cin, a); // ввод автора
        cout << "Год: "; cin >> y; cin.ignore(); // ввод года
        f << t << "|" << a << "|" << y << endl; // запись книги в файл
        save("Добавлена: " + t); // сохранение результата в файл output.txt
    }
    f.close();
}

// поиск книги по названию
void search()
{
    string n, l; // n - название для поиска, l - строка из файла
    cout << "Поиск: "; getline(cin, n);
    ifstream f("books.txt");
    if (!f.is_open()) return; // если файл не открылся - выходим
    while (getline(f, l)) // построчное чтение файла
    {
        if (l.substr(0, l.find('|')) == n) // сравниваем название из файла с искомым
        {
            cout << "Найдено: " << l << endl;
            save("Найдено: " + l);
            f.close();
            return;
        }
    }
    cout << "Не найдено" << endl;
    f.close();
}

// сортировка книг по автору или году
void sortBooks()
{
    string d[100]; // массив для хранения книг
    int c = 0; // счётчик книг
    ifstream in("books.txt");
    if (!in.is_open()) return;
    while (getline(in, d[c]) && c < 100) c++; // чтение всех книг в массив
    in.close();
    int ch; // переменная для выбора критерия сортировки
    cout << "1 - автор, 2 - год: "; cin >> ch; cin.ignore();
    // сортировка пузырьком
    for (int i = 0; i < c-1; i++)
    {
        for (int j = i+1; j < c; j++)
        {
            string a1 = d[i].substr(d[i].find('|')+1, d[i].find('|', d[i].find('|')+1) - d[i].find('|')-1);
            string a2 = d[j].substr(d[j].find('|')+1, d[j].find('|', d[j].find('|')+1) - d[j].find('|')-1);
            int y1 = stoi(d[i].substr(d[i].rfind('|')+1));
            int y2 = stoi(d[j].substr(d[j].rfind('|')+1));
            if ((ch == 1 && a1 > a2) || (ch == 2 && y1 > y2)){
                swap(d[i], d[j]);
            }
        }
    }
    ofstream out("books.txt");
    for (int i = 0; i < c; i++) out << d[i] << endl; // записываем отсортированные книги
    out.close();
    save("Сортировка завершена");
}

// добавление одной книги в конец файла
void addOne()
{
    string d[100]; // массив для хранения существующих книг
    int c = 0; // счётчик книг
    ifstream in("books.txt");
    if (in.is_open()){
        while (getline(in, d[c]) && c < 100) c++; // читаем все существующие книги
        in.close();
    }
    string t, a; // переменные для новой книги
    int y;
    cout << "Название: "; getline(cin, t);
    cout << "Автор: "; getline(cin, a);
    cout << "Год: "; cin >> y; cin.ignore();
    ofstream out("books.txt");
    for (int i = 0; i < c; i++) out << d[i] << endl; // записываем все старые книги
    out << t << "|" << a << "|" << y << endl; // добавляем новую книгу в конец
    out.close();
    save("Добавлена: " + t);
}

// вывод книг по году выпуска не позднее указанного
void byYear()
{
    int y; // максимальный год
    string l; // строка из файла
    cout << "Максимальный год: "; cin >> y; cin.ignore();
    ifstream f("books.txt");
    if (!f.is_open()) return;
    while (getline(f, l)) // построчное чтение файла
    {
        if (stoi(l.substr(l.rfind('|')+1)) <= y){ // проверяем год книги
            cout << l << endl;
            save("Вывод: " + l);
        }
    }
    f.close();
}

int main()
{
    ofstream clear("output.txt");  // очистка файла при запуске
    clear.close();
    int ch; // переменная для выбора пункта меню
    do {
        cout << "1 - Создать\n2 - Поиск\n3 - Сортировка\n4 - Добавить\n5 - По году\n0 - Выход\n: ";
        cin >> ch; cin.ignore();
        // обработка пользовательского выбора
        if (ch == 1) addBooks();
        else if (ch == 2) search();
        else if (ch == 3) sortBooks();
        else if (ch == 4) addOne();
        else if (ch == 5) byYear();
    } while (ch != 0);
    return 0;
}