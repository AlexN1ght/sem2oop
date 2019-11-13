/*
Студент: Цапков А.М.
Группа: М8О-207Б
Разработать классы прямоугольника, ромба и трапеции. Классы должны наследоваться от базового класса Figure. Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов:
1.       Вычисление геометрического центра фигуры;
2.       Вывод в стандартный поток вывода std::cout координат вершин фигуры; 
3.       Вычисление площади фигуры;
 
Создать программу, которая позволяет:
•       Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
•       Сохранять созданные фигуры в динамический массив std::vector<Figure*>
•       Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
•       Необходимо уметь вычислять общую площадь фигур в массиве.
•       Удалять из массива фигуру по индексу;
*/

#include <iostream>
#include "Vector.hpp"
#include <map>
#include "Figures.hpp"

enum { 
    ERR, ADD,
    PRINT, DEL,
    REC, EXIT,
    CENTR, AREA,
    TRAP, RHOMB,
    SIZE, HELP
};

void help() {
    std::cout << "Commands: add, del, print, area, size, quit, help, centr\n";
    std::cout << "Supported Figures: rectangle, trap, rhombus\n";
    std::cout << "Figure id can be number or target \"all\"\n";
}

int main() {
    using Point = PairWIO<int,int>;
    Point tmpP1, tmpP2;
    std::string comId, figType;
    //Rectangle* tmpV;
    int id;
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
                    std::for_each(vec.begin(), vec.end(), printCoor); 
                    for (int i = 0; i < vec.size(); i++) {
                        //vec[i]->printCoor();
                        putchar('\n');
                    }
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

