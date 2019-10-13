#include <iostream>
#include <vector>
#include <map>
#include "Figures.hpp"

enum { 
    ERR, ADD,
    PRINT, DEL,
    REC, EXIT,
    CENTR, AREA,
    TRAP, RHOMB,
    SIZE
};

int main() {
    Point tmpP1, tmpP2;
    std::string comId, figType;
    Rectangle* tmpV;
    int id;
    double length, angle, overallArea;
    int status = 1;
    std::vector<Figure*> vec;
    std::map <std::string, int> command;
    command["add"] = ADD;
    command["print"] = PRINT;
    command["del"] = DEL;
    command["rec"] = REC;
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
                        vec.push_back(dynamic_cast<Figure*>(new Rectangle(tmpP1, tmpP2)));
                        std::cout << "Added\n";
                        break;
                    case RHOMB:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        std::cin >> tmpP1 >> tmpP2 >> length;
                        vec.push_back(dynamic_cast<Figure*>(new Rhombus(tmpP1, tmpP2, length)));
                        std::cout << "Added\n";
                        break;
                    case TRAP:
                        if (!( std::cin >> tmpP1 >> tmpP2 >> angle >> length)) {
                            std::cout << "Invalid Params\n";
                            break;
                        }
                        vec.push_back(dynamic_cast<Figure*>(new Trap(tmpP1, tmpP2, angle, length)));
                        std::cout << "Added\n";
                        break;
                    case ERR:
                        std::cout << "Unknown figure\n";
                        break;
                }
                break;
            case PRINT:
                std::cin >> comId;
                if (comId == "all") {
                    for (int i = 0; i < vec.size(); i++) {
                        vec[id]->printCoor();
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
                    vec[id]->printCoor();
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
                std::cout << vec[id]->centr() << '\n';
                break;
            case AREA:
                std::cin >> comId;
                if (comId == "all") {
                    overallArea = 0;
                    for (int i = 0; i < vec.size(); i++) {
                        overallArea += vec[i]->area();
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
                    std::cout << vec[id]->area() << '\n';
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
                vec.erase(vec.begin() + id);
                std::cout << "Deleted\n";
                break;
            case SIZE:
                std::cout << vec.size() << "\n";
                break;
            case ERR:
                std::cout << "Invalid command\n";
                break;
            case EXIT:
                for (int i = 0; i < vec.size(); i++) {
                    delete [] vec[i];
                }
                status = 0;
                break;
        }
        while(getchar() != '\n');
        std::cin.clear();
    }
    return 0;
}
