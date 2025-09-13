// Вариант 4

#include <iostream>

int main()
{
    int n;
    unsigned long long res = 1;
    std::cout << "Введите количество машин: ";
    std::cin >> n;
    int i = 1;
    while (i <= n){
        res *= i;
        i++;
    }
    std::cout << res << std::endl;
    return 0;
}