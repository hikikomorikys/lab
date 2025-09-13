// Вариант 4

#include <iostream>

int main()
{
    int a[10];
    int sum = 0;
    int mx;
    
    // Заполнение массива числами, введёнными пользователем
    std::cout << "Введите 10 целых чисел:" << std::endl;
    for (int i = 0; i < 10; i++){
        std::cin >> a[i];
    }
    
    // Вывод элементов массива
    std::cout << "Элементы массива: ";
    for (int i = 0; i < 10; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    
    // Вычисление суммы всех элементов
    for (int i = 0; i < 10; i++){
        sum += a[i];
    }
    std::cout << "Сумма всех элементов: " << sum << std::endl;
    
    // Поиск максимального элемента
    mx = a[0];
    for (int i = 1; i < 10; i++){
        if (a[i] > mx){
            mx = a[i];
        }
    }
    std::cout << "Максимальный элемент: " << mx << std::endl;
    
    // Сортировка вставками в порядке убывания
    for (int i = 1; i < 10; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] < key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    
    // Вывод отсортированного массива
    std::cout << "Отсортированный по убыванию массив: ";
    for (int i = 0; i < 10; i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}