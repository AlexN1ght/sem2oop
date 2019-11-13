#include <iostream>
#include <iomanip>
#include <cmath>

class Point {
    public:
        double x;
        double y;
        Point() : x(0), y(0) {}
        Point(double xI, double yI) {
            x = xI;
            y = yI;
        }
        friend std::ostream& operator<< (std::ostream &out, const Point &point) {
            out << std::fixed << std::setprecision(2) << '(' << point.x << ", " << point.y << ')';
            return out;
        }
        friend std::istream& operator>> (std::istream &in, Point &point){
            in >> point.x;
            in >> point.y;
            return in;
        } 
};

double distance(Point one, Point two) {
    return sqrt((one.x - two.x) * (one.x - two.x) + (one.y - two.y) * (one.y - two.y));
}

class Figure {
    public:
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

class Rectangle : public Figure {
    public:
        Rectangle(Point ldI, Point ruI) {
            points[3] = ldI;
            points[1] = ruI;
            points[2].x = points[1].x;
            points[2].y = points[3].y;
            points[0].x = points[3].x;
            points[0].y = points[1].y;
        }

        void printCoor() {
            std::cout << "1st = " << points[0] << "\t2nd = " << points[1] << "\n3rd = " << points[3] << "\t4th = " << points[2] << '\n';
        }

        double area() {
            return (points[1].x - points[0].x) * (points[0].y - points[3].y);
        }

        Point centr() {
            Point out;
            for (int i = 0; i < 4; i++) {
                out.x += points[i].x;
                out.y += points[i].x;
            }
            out.x /= 4;
            out.y /= 4;
            return out;
        }
    private:
        Point points[4];
};

class Rhombus : public Figure {
    public:
        Rhombus(Point in1, Point in2, int length) {
            points[3] = in1;
            points[1] = in2;
            double tgA = abs(points[3].y - points[1].y) / abs(points[3].x - points[1].x);
            Point mid((points[3].x +points[1].x) / 2, (points[3].y +points[1].y) / 2);
            double midLen = sqrt(length*length - pow(distance(mid, in1), 2));
            if (points[3].x > points[1].x) {
                points[0].x = mid.x + midLen * cos(90 * M_PI / 180 - atan(tgA));
                points[2].x = mid.x - midLen * cos(90 * M_PI / 180 - atan(tgA));
            } else {
                points[0].x = mid.x - midLen * cos(90 * M_PI / 180 - atan(tgA));
                points[2].x = mid.x + midLen * cos(90 * M_PI / 180 - atan(tgA));
            }
            if (points[3].y > points[1].y) {
                points[0].y = mid.y - midLen * sin(90 * M_PI / 180 - atan(tgA));
                points[2].y = mid.x + midLen * sin(90 * M_PI / 180 - atan(tgA));
            } else {
                points[0].y = mid.y + midLen * sin(90 * M_PI / 180 - atan(tgA));
                points[2].y = mid.y - midLen * sin(90 * M_PI / 180 - atan(tgA));
            }
        }

        void printCoor() {
            std::cout << "1st = " << points[0] << "\t2nd = " << points[1] << "\n4rd = " << points[3] << "\t3th = " << points[2] << '\n';
        }

        double area() {
            return (distance(points[1], points[3]) * distance(points[0], points[2])) / 2;
        }

        Point centr() {
            Point out;
            for (int i = 0; i < 4; i++) {
                out.x += points[i].x;
                out.y += points[i].x;
            }
            out.x /= 4;
            out.y /= 4;
            return out;
        }
    private:
        Point points[4];
};

class Trap : public Figure {
    public:
        Trap(Point in1, Point in2, double angle, double length) {
            points[3] = in1;
            points[2] = in2;
            double A = atan(abs(points[3].y - points[2].y) / abs(points[3].x - points[2].x));
            if (points[3].x < points[2].x) {
                if (points[3].y < points[2].y) {
                    points[0].x = points[3].x + length * cos(angle * M_PI / 180 + A);
                    points[0].y = points[3].y + length * sin(angle * M_PI / 180 + A);
                    points[1].x = points[2].x + length * cos(M_PI + A - angle * M_PI / 180);
                    points[1].y = points[2].y + length * sin(M_PI + A - angle * M_PI / 180);
                } else {
                    points[0].x = points[3].x + length * cos(angle * M_PI / 180 - A);
                    points[0].y = points[3].y + length * sin(angle * M_PI / 180 - A);
                    points[1].x = points[2].x + length * cos(M_PI - A - angle * M_PI / 180);
                    points[1].y = points[2].y + length * sin(M_PI - A - angle * M_PI / 180);
                }
            } else {
                if (points[3].y > points[2].y) {
                    points[0].x = points[3].x + length * cos(M_PI + angle * M_PI / 180 + A);
                    points[0].y = points[3].y + length * sin(M_PI + angle * M_PI / 180 + A);
                    points[1].x = points[2].x + length * cos(A - angle * M_PI / 180);
                    points[1].y = points[2].y + length * sin(A - angle * M_PI / 180);
                } else {
                    points[0].x = points[3].x + length * cos(M_PI - A + angle * M_PI / 180);
                    points[0].y = points[3].y + length * sin(M_PI - A + angle * M_PI / 180);
                    points[1].x = points[2].x + length * cos(- angle * M_PI / 180 - A);
                    points[1].y = points[2].y + length * sin(- angle * M_PI / 180 - A);
                }
            }
        }

        void printCoor() {
            std::cout << "1st = " << points[0] << "\t2nd = " << points[1] << "\n4rd = " << points[3] << "\t3th = " << points[2] << '\n';
        }

        double area() {
            return (distance(points[0], points[1]) + distance(points[2], points[3])) / 2 * 
                    distance(Point((points[0].x + points[1].x) / 2, (points[0].y + points[1].y) / 2),
                              Point((points[2].x + points[3].x) / 2, (points[2].y + points[3].y) / 2) );
        }

        Point centr() {
            Point out;
            for (int i = 0; i < 4; i++) {
                out.x += points[i].x;
                out.y += points[i].x;
            }
            out.x /= 4;
            out.y /= 4;
            return out;
        }
    private:
        Point points[4];
};

