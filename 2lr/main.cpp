/*
Цапков А.М.
￼￼￼Вариант №7. Создать класс BitString для работы с 128-битовыми строками. Битовая строка должна быть представлена двумя полями типа unsigned long long. 
Должны быть реализованы все традиционные операции для работы с битами: and, or, xor, not. Реализовать сдвиг влево shiftLeft и сдвиг вправо shiftRight на заданное количество битов. 
Реализовать операцию вычисления количества единичных битов, операции сравнения по количеству единичных битов. Реализовать операцию проверки включения.
Операции and, or, xor, not, >>, << , сравнения (на равенство, больше и меньше) должны быть выполнены в виде перегрузки операторов.
*/

#include <iostream>

using namespace std;

class BitString {
    private:
        unsigned long long hf1;
        unsigned long long hf2;
    public:
        BitString() {
            hf1 = 0;
            hf2 = 0;
        }
        BitString operator = ( const unsigned long long val) {
            hf1 = 0;
            hf2 = val;
            return *this;
        }
        BitString operator & (const BitString& right) {
            BitString out; 
            out.hf1 = hf1 & right.hf1;
            out.hf2 = hf2 & right.hf2;
            return out;
        }
        BitString operator | (const BitString& right) {
            BitString out; 
            out.hf1 = hf1 | right.hf1;
            out.hf2 = hf2 | right.hf2;
            return out;
        }
        BitString operator ~ () {
            BitString out; 
            out.hf1 = ~hf1;
            out.hf2 = ~hf2;
            return out;
        }
        BitString operator ^ (const BitString& right) {
            BitString out; 
            out.hf1 = hf1 ^ right.hf1;
            out.hf2 = hf2 ^ right.hf2;
            return out;
        }
        BitString operator  << (const int right) {
            BitString out;
            if (right == 0) {
                return *this;
            }
            if (right < 64){
                out.hf1 = (hf1 << right) | (hf2 >> (64 - right));
                out.hf2 = hf2 << right;
            } else if (right < 128) {
                out.hf1 = hf2 << (right - 64) ;
                out.hf2 = 0;
            } else {
                out.hf1 = 0;
                out.hf2 = 0;
            }
            return out;
        }
        BitString operator >> (const int right) {
            BitString out; 
            if (right == 0) {
                return *this;
            }
            if (right < 64){
                out.hf2 = (hf2 >> right) | (hf1 << (64 - right));
                out.hf1 = hf1 >> right;
            } else if (right < 128) {
                out.hf2 = hf1 >> (right - 64);
                out.hf1 = 0;
            } else {
                out.hf1 = 0;
                out.hf2 = 0;
            }
            return out;
        }

        int oneCount(){
            int counter = 0;
            for(int i = 63; i >= 0; --i){
                counter += (hf1 >> i)&1;
            }
            for(int i = 63; i >= 0; --i){
                counter += (hf2 >> i)&1;
            }
            return counter;
        }

        bool operator == (BitString& right) {
            return oneCount() == right.oneCount();
        }
        bool operator < (BitString& right) {
            return oneCount() < right.oneCount();
        }
        bool operator > (BitString& right) {
            return oneCount() > right.oneCount();
        }
        bool operator >= (BitString& right) {
            return oneCount() >= right.oneCount();
        }
        bool operator <= (BitString& right) {
            return oneCount() <= right.oneCount();
        }
        
        BitString e() {
            BitString out;
            out = 1;
            return out;
        }
        void print(const string type) {
            if(type == "bin") {
                for(int i = 63; i >= 0; --i){
                    printf("%llu", (hf1 >> i)&1);
                }
                cout << " ";
                for(int i = 63; i >= 0; --i){
                    printf("%llu", (hf2 >> i)&1);
                }
                cout << '\n';
            }
        }
};

BitString operator "" _BS128(const char* in) {
    BitString out;
    int i = 0;
    while(in[i++] != '\0');
    i = i - 2;
    if (i > 127) {
        out = 0;
        return out;
    }
    for (int k = 0; in[k] != '\0'; k++) {
        if (in[k] == '1') {
            out = out | (out.e() << i);
            i--;
        } else if (in[k] == '0') {
            i--;
        } else {
            out = 0;
            break;
        }
    }
    return out;
}

int main(void)
{
    BitString a;
    a = 10000000000100000000000000000000010000000000000000000000000000000000001110000000000000000000000000000000000001010010001000000001_BS128;
    cout << "a = 10000000000100000000000000000000010000000000000000000000000000000000001110000000000000000000000000000000000001010010001000000001_BS128:\n";
    a.print("bin");
    a = 0_BS128;
    cout << "a = 0_BS128:\n";
    a.print("bin");
    a = 1_BS128;
    cout << "a = 1_BS128:\n";
    a.print("bin");
    a = 10010010_BS128;
    cout << "a = 10010010_BS128:\n";
    a.print("bin");
    a = 10020010_BS128;
    cout << "a = 10020010_BS128:\n";
    a.print("bin");
    return 0;
}

