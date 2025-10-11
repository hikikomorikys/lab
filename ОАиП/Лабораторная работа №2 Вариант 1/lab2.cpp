#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>
using namespace std;

int main()
{
    string input; // переменная для хранения введенной строки
    cout << "Введите строку из 10 слов на латинице: ";
    getline(cin, input);

    vector<string> words; // вектор для хранения отдельных слов
    stringstream ss(input); // строковый поток для разбиения строки на слова
    string word; // временная переменная для хранения каждого слова
    // разбиваем строку на слова и добавляем каждое слово в вектор
    while (ss >> word){
        words.push_back(word);
    }
    

    // №1 Найти количество слов, начинающихся с буквы "a"
    int k1 = 0;
    for (const string& w : words){
        if (!w.empty() && (w[0] == 'a' || w[0] == 'A')){
            k1++;
        }
    }
    cout << "№1 - Слов, начинающихся с буквы 'a': " << k1 << endl;
    

    // №2 Найти длину самого короткого слова
    int mn = INT_MAX;
    for (const string& w : words){
        if (w.length() < mn){
            mn = w.length();
        }
    }
    cout << "№2 - Длина самого короткого слова: " << mn << endl;
    

    // №3 Подсчитать количество букв "a" в последнем слове данной строки
    string s3 = words.back(); // получаем последнее слово из вектора
    int k3 = 0;
    for (char c : s3){
        if (c == 'a' || c == 'A'){
            k3++;
        }
    }
    cout << "№3 - Букв 'a' в последнем слове: " << k3 << endl;
    

    // №4 Заменить все буквы в верхнем регистре на строчные
    string s4 = input; // копируем исходную строку
    transform(s4.begin(), s4.end(), s4.begin(), ::tolower);
    cout << "№4 - Строка в нижнем регистре: " << s4 << endl;
    

    // №5 Найти количество слов, у которых первый и последний символы совпадают между собой
    int k5 = 0;
    for (const string& w : words){
        if (!w.empty() && w[0] == w[w.length() - 1]){
            k5++;
        }
    }
    cout << "№5 - Слов с одинаковым первым и последним символом: " << k5 << endl;
    

    // 6. Самая короткая общая подстрока между двумя словами
    string s6 = "";
    // перебираем все пары слов
    for (int i = 0; i < words.size(); i++)
    {
        for (int j = i + 1; j < words.size(); j++)
        {
            string word1 = words[i];
            string word2 = words[j];
            // ищем общие подстроки
            for (int k = 0; k < word1.length(); k++)
            {
                for (int l = k; l < word1.length(); l++)
                {
                    string sub = word1.substr(k, l - k + 1); // извлекаем подстроку из первого слова
                    if (word2.find(sub) != string::npos) // проверяем наличие этой подстроки во втором слове
                    {
                        // если нашли общую подстроку и она короче текущей самой короткой
                        if (s6.empty() || sub.length() < s6.length()){
                            s6 = sub; // обновляем самую короткую общую подстроку
                        }
                    }
                }
            }
        }
    }
    if (!s6.empty()){
        cout << "№6 - Самая короткая общая подстрока: " << s6 << endl;
    }
    else{
        cout << "№6 - Общих подстрок не найдено" << endl;
    }
    return 0;
}