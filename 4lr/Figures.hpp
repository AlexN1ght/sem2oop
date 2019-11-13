#include <iostream>
#include <iomanip>
#include <cmath>

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

class Figure {
    public:
        using Point = PairWIO<double,double>;
        virtual void printCoor() {
            std::cout << "CoorTest\n";
        }
        virtual double area() {
            return 0;
        }
        virtual Point centr() {
            return Point();
        }
};

template <class T> 
class Rectangle : public Figure {
    public:
        using Point = PairWIO<T,T>;
        Point points[4];
        Rectangle(){}
        void restruct(Point ldI, Point ruI) {
            points[3] = ldI;
            points[1] = ruI;
            points[2].first = points[1].first;
            points[2].second = points[3].second;
            points[0].first = points[3].first;
            points[0].second = points[1].second;
        }
};

template <class T> 
class Rhombus : public Figure {
    public:
        using Point = PairWIO<T,T>;
        Point points[4];
        Rhombus(){}
        void restruct(Point in1, Point in2, int length) {
            points[3] = in1;
            points[1] = in2;
            double tgA = abs(points[3].second - points[1].second) / abs(points[3].first - points[1].first);
            Point mid((points[3].first +points[1].first) / 2, (points[3].second +points[1].second) / 2);
            double midLen = sqrt(length*length - pow(distance(mid, in1), 2));
            if (points[3].first > points[1].first) {
                points[0].first = mid.first + midLen * cos(90 * M_PI / 180 - atan(tgA));
                points[2].first = mid.first - midLen * cos(90 * M_PI / 180 - atan(tgA));
            } else {
                points[0].first = mid.first - midLen * cos(90 * M_PI / 180 - atan(tgA));
                points[2].first = mid.first + midLen * cos(90 * M_PI / 180 - atan(tgA));
            }
            if (points[3].second > points[1].second) {
                points[0].second = mid.second - midLen * sin(90 * M_PI / 180 - atan(tgA));
                points[2].second = mid.first + midLen * sin(90 * M_PI / 180 - atan(tgA));
            } else {
                points[0].second = mid.second + midLen * sin(90 * M_PI / 180 - atan(tgA));
                points[2].second = mid.second - midLen * sin(90 * M_PI / 180 - atan(tgA));
            }
        }
};

template <class T> 
class Trap : public Figure {
    public:
        using Point = PairWIO<T,T>;
        Point points[4];
        Trap(){}
        void restruct(Point in1, Point in2, double angle, double length) {
            points[3] = in1;
            points[2] = in2;
            double A = atan(abs(points[3].second - points[2].second) / abs(points[3].first - points[2].first));
            if (points[3].first < points[2].first) {
                if (points[3].second < points[2].second) {
                    points[0].first = points[3].first + length * cos(angle * M_PI / 180 + A);
                    points[0].second = points[3].second + length * sin(angle * M_PI / 180 + A);
                    points[1].first = points[2].first + length * cos(M_PI + A - angle * M_PI / 180);
                    points[1].second = points[2].second + length * sin(M_PI + A - angle * M_PI / 180);
                } else {
                    points[0].first = points[3].first + length * cos(angle * M_PI / 180 - A);
                    points[0].second = points[3].second + length * sin(angle * M_PI / 180 - A);
                    points[1].first = points[2].first + length * cos(M_PI - A - angle * M_PI / 180);
                    points[1].second = points[2].second + length * sin(M_PI - A - angle * M_PI / 180);
                }
            } else {
                if (points[3].second > points[2].second) {
                    points[0].first = points[3].first + length * cos(M_PI + angle * M_PI / 180 + A);
                    points[0].second = points[3].second + length * sin(M_PI + angle * M_PI / 180 + A);
                    points[1].first = points[2].first + length * cos(A - angle * M_PI / 180);
                    points[1].second = points[2].second + length * sin(A - angle * M_PI / 180);
                } else {
                    points[0].first = points[3].first + length * cos(M_PI - A + angle * M_PI / 180);
                    points[0].second = points[3].second + length * sin(M_PI - A + angle * M_PI / 180);
                    points[1].first = points[2].first + length * cos(- angle * M_PI / 180 - A);
                    points[1].second = points[2].second + length * sin(- angle * M_PI / 180 - A);
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
void printCoor(T figure) {
    std::cout << "1st = " << figure.points[0] << "\t2nd = " << figure.points[1] << "\n4rd = " << figure.points[3] << "\t3th = " << figure.points[2] << '\n';
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
