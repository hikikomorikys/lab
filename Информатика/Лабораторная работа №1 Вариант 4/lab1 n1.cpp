// Вариант 4

#include <iostream>

int main()
{
    double speed;
    std::cout << "Введите скорость автомобиля: ";
    std::cin >> speed;
    if (speed < 60){
        std::cout << "Скорость в пределах нормы" << std::endl;
    }
    else if (speed >= 60 && speed <= 80){
        std::cout << "Вы приближаетесь к превышению скорости" << std::endl;
    }
    else{
        std::cout << "Превышение скорости!" << std::endl;
    }
    return 0;
}