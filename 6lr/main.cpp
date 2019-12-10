/*
Студент: Цапков А.М.
Группа: М8О-207Б
Создать шаблон динамической коллекцию, согласно варианту задания:
1.       Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr). Опционально использование std::unique_ptr.
2.       В качестве параметра шаблона коллекция должна принимать тип данных.
3. Реализовать аллокатор, который выделяет фиксированный размер памяти (количество блоков памяти – является параметром шаблона аллокатора). Внутри аллокатор должен хранить указатель на используемый блок памяти и динамическую коллекцию указателей на свободные блоки. Динамическая коллекция должна соответствовать варианту задания (Динамический массив, Список, Стек, Очередь).
4. Коллекция должна использовать аллокатор для выделеления и освобождения памяти для своих элементов.
5. Аллокатор должен быть совместим с контейнерами std::map и std::list (опционально – vector).
6.       Коллекция должна содержать метод доступа: o Стек – pop, push, top; o Очередь – pop, push, top; Список, Динамический массив – доступ к элементу по оператору [].
7.    Реализовать программу, которая: o Позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию;Позволяет удалять элемент из коллекции по номеру элемента; o Выводит на экран введенные фигуры c помощью std::for_each; o Выводит на экран количество объектов, у которых площадь меньше заданной (с помощью std::count_if).
Вариант—динамический массив.

*/

#include <iostream>
#include "Vector.hpp" 
#include <map>
#include "Figures.hpp"
#include <algorithm>

enum { 
    ERR, ADD,
    PRINT, DEL,
    REC, EXIT,
    CENTR, AREA,
    LES_AREA,
    TRAP, RHOMB,
    SIZE, HELP
};

template <class T>
void printCoorFE(T In) {
    printCoor(*In);
}

void help() {
    std::cout << "Commands: add, del, print, area, size, quit, help, centr, less_then\n";
    std::cout << "Supported Figures: rectangle, trap, rhombus\n\n";
    std::cout << "Foe rectangle: 2 diagonal points (0 0 2 2)\n";
    std::cout << "For trap: 2 points of fouting of a trap, angle and a length of a side ( 0 0 4 4 45 2)\n";
    std::cout << "For rhombus: 2 diagonal points and a length if a side ( 0 0 0 3 5)\n";
    std::cout << "Figure id can be number or target \"all\"\n\n";
    std::cout << "example:\n";
    std::cout << "add rec 0 0 2 2 \nadd trap 0 0 4 4 45 2 \nprint 0 \nprint all \narea all \nless 3\nq\n";
}

int main() {
    using Point = PairWIO<int,int>;
    Point tmpP1, tmpP2;
    std::string comId, figType;
    //Rectangle* tmpV;
    int id;
    int area_key;
    double length, angle, overallArea;
    int status = 1;
    TVector<Figure<int>*> vec;
    std::map <std::string, int> command;
    command["add"] = ADD;
    command["print"] = PRINT;
    command["del"] = DEL;
    command["rec"] = REC;
    command["rectangle"] = REC;
    command["quit"] = EXIT;
    command["q"] = EXIT;
    command["centr_of"] = CENTR;
    command["centr"] = CENTR;
    command["area_of"] = AREA;
    command["area"] = AREA;
    command["size_of"] = AREA;
    command["less_then"] = LES_AREA;
    command["less"] = LES_AREA;
    command["size"] = SIZE;
    command["trap"] = TRAP;
    command["rhomb"] = RHOMB;
    command["help"] = HELP;
    command["h"] = HELP;

    help();
    while (status) {
        
        std::cout << "Enter command: ";
        std::cin >> comId;
        switch (command[comId]) {
            case ADD:
                std::cin >> figType;
                switch (command[figType]) {
                    case REC:
                        if (!( std::cin >> tmpP1 >> tmpP2)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        vec.push_back(dynamic_cast<Figure<int>*>(new Rectangle<int>(tmpP1, tmpP2)));
                        std::cout << "Rectangle added\n";
                        break;
                    case RHOMB:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        vec.push_back(dynamic_cast<Figure<int>*>(new Rhombus<int>(tmpP1, tmpP2, length)));
                        std::cout << "Rhombus added\n";
                        break;
                    case TRAP:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> angle >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        vec.push_back(dynamic_cast<Figure<int>*>(new Trap<int>(tmpP1, tmpP2, angle, length)));
                        std::cout << "Trap added\n";
                        break;
                    case ERR:
                        std::cout << "Unknown figure\n";
                        break;
                }
                break;
            case PRINT:
                std::cin >> comId;
                if (comId == "all") {
                    std::for_each(vec.begin(), vec.end(), [](auto& k){
                        printCoor(*k);
                        putchar('\n');
                    });
                } else {
                    try {
                        id = std::stoi(comId);
                    } catch (std::invalid_argument) {
                        std::cout << "Invalid figure ID\n";
                        break;
                    }
                    if (id > ((int)vec.size() - 1) || id < 0) {
                        std::cout << "Invalid figure ID\n";
                        break;
                    }
                    printCoor(*(vec[id]));
                }
                break;
                
            case CENTR:
                if (!(std::cin >> id)) {
                    std::cout << "Invalid figure ID\n";
                    break;
                }
                if (id > ((int)vec.size() - 1) || id < 0) {
                    std::cout << "Invalid figure ID\n";
                    break;
                }
                std::cout << centr(*(vec[id])) << '\n';
                break;
            case AREA:
                std::cin >> comId;
                if (comId == "all") {
                    overallArea = 0;
                    for (int i = 0; i < vec.size(); i++) {
                        overallArea += area(*vec[i]);
                    }
                    std::cout << overallArea << '\n';
                } else {
                    try {
                        id = std::stoi(comId);
                    } catch (std::invalid_argument) {
                        std::cout << "Invalid figure ID\n";
                        break;
                    }
                    if (id > ((int)vec.size() - 1) || id < 0) {
                        std::cout << "Invalid figure ID\n";
                        break;
                    }
                    std::cout << area(*vec[id]) << '\n';
                }
                break;
            case LES_AREA:
                std::cin >> area_key;
                std::cout << std::count_if(vec.begin(), vec.end(), [area_key](auto& k) {
                    return area_key > area(*k);
                    }) << '\n';
                break;
            case DEL:
                if (!(std::cin >> id)) {
                    std::cout << "Invalid figure ID\n";
                    break;
                }
                if (id > ((int)vec.size() - 1) || id < 0) {
                    std::cout << "Invalid figure ID\n";
                    break;
                }
                delete vec[id];
                vec.erase(vec.begin() + id);
                std::cout << "Deleted\n";
                break;
            case SIZE:
                std::cout << vec.size() << "\n";
                break;
            case HELP:
                help();
                break;
            case ERR:
                std::cout << "Invalid command\n";
                break;
            case EXIT:
                for (int i = 0; i < vec.size(); i++) {
                    delete vec[i];
                }
                status = 0;
                break;
        }
        while(getchar() != '\n');
        std::cin.clear();
    }
    return 0;
}

