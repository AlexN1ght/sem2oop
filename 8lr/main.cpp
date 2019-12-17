/*
Студент: Цапков А.М.
Группа: М8О-207Б
Создать приложение, которое будет считывать из стандартного ввода данные фигур, согласно варианту
задания, выводить их характеристики на экран и записывать в файл. Фигуры могут задаваться как своими
вершинами, так и другими характеристиками (например, координата центра, количество точек и радиус).
Программа должна:
    1. Осуществлять ввод из стандартного ввода данных фигур, согласно варианту задания;
    2. Программа должна создавать классы, соответствующие введенным данных фигур;
    3. Программа должна содержать внутренний буфер, в который помещаются фигуры. Для создания
буфера допускается использовать стандартные контейнеры STL. Размер буфера задается параметром
командной строки. Например, для буфера размером 10 фигур: oop_exercise_08 10
    4. При накоплении буфера они должны запускаться на асинхронную обработку, после чего буфер
должен очищаться;
    5. Обработка должна производиться в отдельном потоке;
    6. Реализовать два обработчика, которые должны обрабатывать данные буфера:
        a. Вывод информации о фигурах в буфере на экран;

        b. Вывод информации о фигурах в буфере в файл. Для каждого буфера должен создаваться файл
        с уникальным именем.

    7. Оба обработчика должны обрабатывать каждый введенный буфер. Т.е. после каждого заполнения
буфера его содержимое должно выводиться как на экран, так и в файл.
    8. В программе должно быть ровно два потока (thread). Один основной (main) и второй для
обработчиков;
    9. В программе должен явно прослеживаться шаблон Publish-Subscribe. Каждый обработчик должен
быть реализован как отдельный подписчик.
    10. Реализовать в основном потоке (main) ожидание обработки буфера в потоке-обработчике. Т.е. после
отправки буфера на обработку основной поток должен ждать, пока поток обработчик выведет данные
на экран и запишет в файл.
*/

#include <iostream>
#include <future> 
#include <chrono>
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

void wait(std::future<int>& fut) {
    std::chrono::milliseconds span (100);

    while (fut.wait_for(span)==
        std::future_status::timeout)
    std::cout << '.' << std::flush;

    int x = fut.get();
    if (x) {
        std::cout << " Done\n\n";
    } 
}

template <class T>
void printCoorFE(T In) {
    printCoor(*In);
}

void help() {
    std::cout << "\nCommands: add, quit, help\n";
    std::cout << "Supported Figures: rectangle, trap, rhombus\n";
    std::cout << "For rectangle: 2 diagonal points (0 0 2 2)\n";
    std::cout << "For trap: 2 points of founding of a trap, angle and a length of a side ( 0 0 4 4 45 2)\n";
    std::cout << "For rhombus: 2 diagonal points and a length if a side ( 0 0 0 3 5)\n";
    std::cout << "\nexample:\n";
    std::cout << "add rec 0 0 2 2 \nadd trap 0 0 4 4 45 2 \nq\n\n";
}

int main (int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Error: no size of buffer entered" << '\n';
        exit(0);
    }
    using T = int;
    using Point = PairWIO<int,int>;

    int size = atoi(argv[1]);

    TVector<Figure<T>*> buf;
    // create one publisher
    Publisher<T> pub(buf, size);

    // create two subscribers
    char sout[] = "stdout";
    char fout[] = "out.txt";
    Subscriber<T> sub2(sout);
    Subscriber<T> sub1(fout);
    // add subscribers to publisher
    pub.Subscribe(sub1);
    pub.Subscribe(sub2);
    
    Point tmpP1, tmpP2;
    std::string comId, figType;
    //Rectangle* tmpV;
    int id;
    int area_key;
    double length, angle, overallArea;
    int status = 1;
    
    std::map <std::string, int> command;
    command["add"] = ADD;
    command["rec"] = REC;
    command["rectangle"] = REC;
    command["quit"] = EXIT;
    command["q"] = EXIT;
    command["trap"] = TRAP;
    command["rhomb"] = RHOMB;
    command["help"] = HELP;
    command["h"] = HELP;

    Figure<T>* fig;

    help();
    while (status) {
        
        std::cout << "Enter command: ";
        std::cin >> comId;
        std::future<int> fut;
        switch (command[comId]) {
            case ADD:
                std::cin >> figType;
                switch (command[figType]) {
                    case REC:
                        if (!( std::cin >> tmpP1 >> tmpP2)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        fig = new Rectangle<int>(tmpP1, tmpP2);
                        std::cout << "Rectangle added\n";
                        break;
                    case RHOMB:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        fig = new Rhombus<int>(tmpP1, tmpP2, length);
                        std::cout << "Rhombus added\n";
                        break;
                    case TRAP:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> angle >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        fig = new Trap<int>(tmpP1, tmpP2, angle, length);
                        std::cout << "Trap added\n";
                        break;
                    case ERR:
                        std::cout << "Unknown figure\n";
                        break;
                }
                fut = std::async(&Publisher<T>::Add,&pub,fig);
                wait(fut);

                break;
            case HELP:
                help();
                break;
            case ERR:
                std::cout << "Invalid command\n";
                break;
            case EXIT:
                for (int i = 0; i < buf.size(); i++) {
                    delete buf[i];
                }
                status = 0;
                break;
        }
        while(getchar() != '\n');
        std::cin.clear();
    }
    return 0;
}

