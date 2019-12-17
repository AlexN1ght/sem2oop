#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std::chrono_literals;

template <class A, class B> 
class PairWIO : public std::pair<A, B> {
    public:
        PairWIO() : std::pair<A, B>() {
            this->first = 0;
            this->second = 0; 
        }
        PairWIO(A firstI, B secondI) : std::pair<A, B>() {
            this->first = firstI;
            this->second = secondI; 
        }
        friend std::ostream& operator<< (std::ostream &out, const PairWIO<A,B> &point) {
            out << std::fixed << std::setprecision(2) << '(' << point.first << ", " << point.second << ')';
            return out;
        }
        friend std::istream& operator>> (std::istream &in, PairWIO<A,B> &point) {
            in >> point.first;
            in >> point.second;
            return in;
        } 
};
//*
template <class T>
double distance(PairWIO<T,T> one, PairWIO<T,T> two) {
    return sqrt((one.first - two.first) * (one.first - two.first) + (one.second - two.second) * (one.second - two.second));
}

template <class T> 
class Figure {
    public:
        using Point = PairWIO<int,int>;
        Point points[4]; 
};

template <class T> 
class Rectangle : public Figure<T> {
    public:
        using Point = PairWIO<int,int>;
        Rectangle(Point ldI, Point ruI) {
            Figure<T>::points[3] = ldI;
            Figure<T>::points[1] = ruI;
            Figure<T>::points[2].first = Figure<T>::points[1].first;
            Figure<T>::points[2].second = Figure<T>::points[3].second;
            Figure<T>::points[0].first = Figure<T>::points[3].first;
            Figure<T>::points[0].second = Figure<T>::points[1].second;
        }
    
};

template <class T> 
class Rhombus : public Figure<T> {
    public:
        using Point = PairWIO<T,T>;
        Rhombus(Point in1, Point in2, int length) {
            Figure<T>::points[3] = in1;
            Figure<T>::points[1] = in2;
            double tgA = abs(Figure<T>::points[3].second - Figure<T>::points[1].second) / abs(Figure<T>::points[3].first - Figure<T>::points[1].first);
            Point mid((Figure<T>::points[3].first +Figure<T>::points[1].first) / 2, (Figure<T>::points[3].second +Figure<T>::points[1].second) / 2);
            double midLen = sqrt(length*length - pow(distance(mid, in1), 2));
            if (Figure<T>::points[3].first > Figure<T>::points[1].first) {
                Figure<T>::points[0].first = mid.first + midLen * cos(90 * M_PI / 180 - atan(tgA));
                Figure<T>::points[2].first = mid.first - midLen * cos(90 * M_PI / 180 - atan(tgA));
            } else {
                Figure<T>::points[0].first = mid.first - midLen * cos(90 * M_PI / 180 - atan(tgA));
                Figure<T>::points[2].first = mid.first + midLen * cos(90 * M_PI / 180 - atan(tgA));
            }
            if (Figure<T>::points[3].second > Figure<T>::points[1].second) {
                Figure<T>::points[0].second = mid.second - midLen * sin(90 * M_PI / 180 - atan(tgA));
                Figure<T>::points[2].second = mid.first + midLen * sin(90 * M_PI / 180 - atan(tgA));
            } else {
                Figure<T>::points[0].second = mid.second + midLen * sin(90 * M_PI / 180 - atan(tgA));
                Figure<T>::points[2].second = mid.second - midLen * sin(90 * M_PI / 180 - atan(tgA));
            }
        }
};

template <class T> 
class Trap : public Figure<T> {
    public:
        using Point = PairWIO<T,T>;
        Trap(Point in1, Point in2, double angle, double length) {
            Figure<T>::points[3] = in1;
            Figure<T>::points[2] = in2;
            double A = atan(abs(Figure<T>::points[3].second - Figure<T>::points[2].second) / abs(Figure<T>::points[3].first - Figure<T>::points[2].first));
            if (Figure<T>::points[3].first < Figure<T>::points[2].first) {
                if (Figure<T>::points[3].second < Figure<T>::points[2].second) {
                    Figure<T>::points[0].first = Figure<T>::points[3].first + length * cos(angle * M_PI / 180 + A);
                    Figure<T>::points[0].second = Figure<T>::points[3].second + length * sin(angle * M_PI / 180 + A);
                    Figure<T>::points[1].first = Figure<T>::points[2].first + length * cos(M_PI + A - angle * M_PI / 180);
                    Figure<T>::points[1].second = Figure<T>::points[2].second + length * sin(M_PI + A - angle * M_PI / 180);
                } else {
                    Figure<T>::points[0].first = Figure<T>::points[3].first + length * cos(angle * M_PI / 180 - A);
                    Figure<T>::points[0].second = Figure<T>::points[3].second + length * sin(angle * M_PI / 180 - A);
                    Figure<T>::points[1].first = Figure<T>::points[2].first + length * cos(M_PI - A - angle * M_PI / 180);
                    Figure<T>::points[1].second = Figure<T>::points[2].second + length * sin(M_PI - A - angle * M_PI / 180);
                }
            } else {
                if (Figure<T>::points[3].second > Figure<T>::points[2].second) {
                    Figure<T>::points[0].first = Figure<T>::points[3].first + length * cos(M_PI + angle * M_PI / 180 + A);
                    Figure<T>::points[0].second = Figure<T>::points[3].second + length * sin(M_PI + angle * M_PI / 180 + A);
                    Figure<T>::points[1].first = Figure<T>::points[2].first + length * cos(A - angle * M_PI / 180);
                    Figure<T>::points[1].second = Figure<T>::points[2].second + length * sin(A - angle * M_PI / 180);
                } else {
                    Figure<T>::points[0].first = Figure<T>::points[3].first + length * cos(M_PI - A + angle * M_PI / 180);
                    Figure<T>::points[0].second = Figure<T>::points[3].second + length * sin(M_PI - A + angle * M_PI / 180);
                    Figure<T>::points[1].first = Figure<T>::points[2].first + length * cos(- angle * M_PI / 180 - A);
                    Figure<T>::points[1].second = Figure<T>::points[2].second + length * sin(- angle * M_PI / 180 - A);
                }
            }
        }
};

template <typename T>
constexpr bool IsTuple = false;
template<typename ... types>
constexpr bool IsTuple<std::tuple<types...>>   = true;

template <class T, 
typename  std::enable_if<std::tuple_size<T>::value == 4>::type* = nullptr> 
void printCoor(T figure) {
    std::cout << "1st = " << std::get<0>(figure) << "\t2nd = " << std::get<1>(figure) << "\n4rd = " << std::get<3>(figure) << "\t3th = " << std::get<2>(figure) << '\n';
}

template <class T, 
typename  std::enable_if<!(IsTuple<T>)>::type* = nullptr> 
std::ostream& printCoor(std::ostream& out, T figure) {
    out << "1st = " << figure.points[0] << "\t2nd = " << figure.points[1] << "\n4rd = " << figure.points[3] << "\t3th = " << figure.points[2] << '\n';
    return out;
}

template <class T, 
typename  std::enable_if<!(IsTuple<T>)>::type* = nullptr> 
std::ofstream& printCoor(std::ofstream& out, T figure) {
    out << "1st = " << figure.points[0] << "\t2nd = " << figure.points[1] << "\n4rd = " << figure.points[3] << "\t3th = " << figure.points[2] << '\n';
    return out;
}

template <class T, 
typename  std::enable_if<std::tuple_size<T>::value == 4>::type* = nullptr>
auto centr(T figure) {
    PairWIO<double,double> out;
   
    out.first += std::get<0>(figure).first;
    out.second += std::get<0>(figure).second;
    out.first += std::get<1>(figure).first;
    out.second += std::get<1>(figure).second;
    out.first += std::get<2>(figure).first;
    out.second += std::get<2>(figure).second;
    out.first += std::get<3>(figure).first;
    out.second += std::get<3>(figure).second;
    
    out.first /= 4;
    out.second /= 4;
    return out;
}

template <class T, 
typename  std::enable_if<!(IsTuple<T>)>::type* = nullptr>
auto centr(T figure) {
    PairWIO<double,double> out;
    for (int i = 0; i < 4; i++) {
        out.first += figure.points[i].first;
        out.second += figure.points[i].second;
    }
    out.first /= 4;
    out.second /= 4;
    return out;
}

template <class T>
double geron(PairWIO<T,T> one, PairWIO<T,T> two, PairWIO<T,T> three) {
    double a = distance(one, two);
    double b = distance(two, three);
    double c = distance(one, three);
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

template <class T, 
typename  std::enable_if<!(IsTuple<T>)>::type* = nullptr>
double area(T figure) { 
    return geron(figure.points[0], figure.points[1], figure.points[2]) + geron(figure.points[0], figure.points[3], figure.points[2]);
}

template <class T, 
typename  std::enable_if<std::tuple_size<T>::value == 4>::type* = nullptr>
double area(T figure) {
    return geron(std::get<0>(figure), std::get<1>(figure), std::get<2>(figure)) + geron(std::get<0>(figure), std::get<3>(figure), std::get<2>(figure));
}



template <class T>
class Subscriber {
    char* out_file;
    
    public:
        Subscriber() = default;
        Subscriber(char* out_file) : out_file(out_file) {
            if (strcmp(out_file, "stdout") != 0) {
                std::ofstream fl (out_file, std::ofstream::out);
                fl.close();
            }
        }

        int Process(TVector<Figure<T>*>& figs, int size) {
            //FILE* fl;
            
            if (strcmp(out_file, "stdout") != 0) {
                std::ofstream fl (out_file, std::ofstream::app);
                fl << size << '\n';
                for (int i = 0; i < size; i++) {
                    printCoor(fl, *figs[i]);
                    fl << "Central point: " << centr(*figs[i]) << '\n';
                    fl << "Area: " << area(*figs[i]) << "\n";
                }
                
                fl.close();

            } else {
                std::cout << size << '\n';
                for (int i = 0; i < size; i++) {
                    printCoor(std::cout, *figs[i]);
                    std::cout << "Central point: " << centr(*figs[i]) << '\n';
                    std::cout << "Area: " << area(*figs[i]) << "\n";
                }
            }
            
            return true;
        }
};

template <class T>
class Publisher {
    int size;
    int max_size;
    TVector<Figure<T>*>& figs;
    TVector<Subscriber<T>> subs;

    public:
        Publisher(TVector<Figure<T>*>& figs, int max_size):
            size(0), max_size(max_size), figs(figs), subs() {}

        // returns true if writen to file
        int Add(Figure<T>* fig) {
            figs.push_back(fig);   // append new figure
            size++;
            if (size == max_size) {             // if array is full
                for (Subscriber<T>& sub : subs) {  // notify subscribers
                    sub.Process(figs, max_size);
                }
                this->size = 0;   // clear array

                std::this_thread::sleep_for(1000ms);
                for (int i = figs.size() - 1; i >= 0; i--) {
                    delete figs[i];
                    figs.erase(figs.begin() + i);
                }
                return true;
            }
            return false;
        }

        void Subscribe(Subscriber<T>& sub) {
            subs.push_back(sub);
        } 
};

