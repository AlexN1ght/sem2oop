/*
Студент: Цапков А.М.
Группа: М8О-207Б
Создать шаблон динамической коллекцию, согласно варианту задания:
1.       Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr). Опционально использование std::unique_ptr;
2.       В качестве параметра шаблона коллекция должна принимать тип данных;
3.       Реализовать forward_iterator по коллекции;
4.       Коллекция должны возвращать итераторы begin() и  end();
5.       Коллекция должна содержать метод вставки на позицию итератора insert(iterator);
6.       Коллекция должна содержать метод удаления из позиции итератора erase(iterator);
7.       При выполнении недопустимых операций (например выход аз границы коллекции или удаление не существующего элемента) необходимо генерировать исключения;
8.       Итератор должен быть совместим со стандартными алгоритмами (например, std::count_if)
9.       Коллекция должна содержать метод доступа: o Стек – pop, push, top; o Очередь – pop, push, top;
oСписок, Динамический массив – доступ к элементу по оператору [];
10.    Реализовать программу, которая: o Позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию;
oПозволяет удалять элемент из коллекции по номеру элемента; o Выводит на экран введенные фигуры c помощью std::for_each; o Выводит на экран количество объектов, у которых площадь меньше заданной (с помощью 
std::count_if);

*/

#include <iostream>
#include "Vector.hpp"
#include <map>
#include <stack>
#include "Figures.hpp"
#include <algorithm>

enum { 
    ERR, ADD,
    PRINT, DEL,
    REC, EXIT,
    UNDO,
    CENTR, AREA,
    LES_AREA,
    TRAP, RHOMB,
    SIZE, HELP
};

/*
template <class T>
void printCoorFE(T In) {
    printCoor(*In);
}
*/

template <class T>
struct Action {
    int type; // 0 is adding, 1 is delliting
    int position;
    Figure<T>* store;
    Action(int in, int pos, Figure<T>* inPo): type(in), position(pos), store(inPo){}
};

void help() {
    std::cout << "\nCommands: add, del, print, area, size, quit, help, centr, less_then and undo\n";
    std::cout << "Supported Figures: rectangle, trap, rhombus\n\n";
    std::cout << "For rectangle: 2 diagonal points (0 0 2 2)\n";
    std::cout << "For trap: 2 points of founding of a trap, angle and a length of a side ( 0 0 4 4 45 2)\n";
    std::cout << "For rhombus: 2 diagonal points and a length if a side ( 0 0 0 3 5)\n";
    std::cout << "Figure id can be number or target \"all\"\n\n";
    std::cout << "example:\n";
    std::cout << "add rec 0 0 2 2 \nadd trap 0 0 4 4 45 2 \nprint 0 \nprint all \narea all \nless 3\nq\n\n";
}

int main() {
    using Point = PairWIO<int,int>;
    using T = int;
    Point tmpP1, tmpP2;
    std::string comId, figType;
    //Rectangle* tmpV;
    int id;
    int area_key;
    double length, angle, overallArea;
    int status = 1;
    TVector<Figure<T>*> vec;
    std::stack<Action<T>> undo;
    std::map <std::string, int> command;

    command["add"] = ADD;       command["h"] = HELP;
    command["print"] = PRINT;   command["p"] = PRINT;
    command["del"] = DEL;       command["rec"] = REC;
    command["rectangle"] = REC; command["quit"] = EXIT;
    command["q"] = EXIT;        command["centr_of"] = CENTR;
    command["centr"] = CENTR;   command["area_of"] = AREA;
    command["area"] = AREA;     command["size_of"] = AREA;
    command["less_then"] = LES_AREA;    command["less"] = LES_AREA;
    command["size"] = SIZE;     command["trap"] = TRAP;
    command["rhomb"] = RHOMB;   command["undo"] = UNDO;
    command["u"] = UNDO;        command["help"] = HELP;
    



    help();
    while (status) {
        
        std::cout << "Enter command: ";
        std::cin >> comId;
        switch (command[comId]) {
            case ADD:
                std::cin >> figType;
                switch (command[figType]) {
                    case REC:
                        vec.push_back(Factory<T>::createFigure(Factory<T>::Rectangle));
                        undo.push(Action<T>(0, vec.size() - 1, vec[vec.size()]));
                        std::cout << "Rectangle added\n";
                        break;
                    case RHOMB:
                        vec.push_back(Factory<T>::createFigure(Factory<T>::Rhombus));
                        undo.push(Action<T>(0, vec.size() - 1, vec[vec.size()]));
                        std::cout << "Rhombus added\n";
                        break;
                    case TRAP:
                        vec.push_back(Factory<T>::createFigure(Factory<T>::Trap));
                        undo.push(Action<T>(0, vec.size() - 1, vec[vec.size()]));
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
                    int counter = 0;
                    std::for_each(vec.begin(), vec.end(), [&counter](auto& k){
                        std::cout << counter++ << ": \n";
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
                undo.push(Action<T>(1, id, vec[id]));
                //delete vec[id];
                vec.erase(vec.begin() + id);
                std::cout << "Deleted\n";
                break;
            case SIZE:
                std::cout << vec.size() << "\n";
                break;
            case UNDO:
                if (undo.empty()) {
                    std::cout << "Nothing to undo\n";
                    break;
                }
                if (undo.top().type == 0) {
                    delete vec[vec.size() - 1];
                    vec.erase(vec.end() - 1);
                    undo.pop();
                } else if (undo.top().type == 1) {
                    vec.insert(vec.begin() + undo.top().position, undo.top().store);
                    undo.pop();
                }
                std::cout << "Done\n";
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
                while(!undo.empty()) {
                    if (undo.top().type == 1) {
                        delete undo.top().store;
                        undo.pop();
                    }
                }
                //status = 0;
                return 0;
                break;
        }
        while(getchar() != '\n');
        std::cin.clear();
    }
    return 0;
}

