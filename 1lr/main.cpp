#include <iostream>

using namespace std;

class BitString {
	private:
		unsigned long long hf1;
		unsigned long long hf2;
	public:
		void operator = (unsigned long long val) {
			hf1 = 0;
			hf2 = val;
		}
		BitString operator & (BitString right) {
			BitString out; 
			out.hf1 = hf1 & right.hf1;
			out.hf2 = hf2 & right.hf2;
			return out;
		}
		BitString operator | (BitString right) {
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
		BitString operator ^ (BitString right) {
			BitString out; 
			out.hf1 = hf1 ^ right.hf1;
			out.hf2 = hf2 ^ right.hf2;
			return out;
		}
		BitString operator  << (int right) {
			BitString out; 
			out.hf1 = (hf1 << right) | (hf2 >> (64 - right));
			out.hf2 = hf2 << right;
			return out;
		}
		BitString operator >> (int right) {
			BitString out; 
			out.hf2 = (hf2 >> right) | (hf1 << (64 - right));
			out.hf1 = hf1 >> right;
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

		bool operator == (BitString right) {
			return oneCount() == right.oneCount();
		}
		bool operator < (BitString right) {
			return oneCount() < right.oneCount();
		}
		bool operator > (BitString right) {
			return oneCount() > right.oneCount();
		}
		bool operator >= (BitString right) {
			return oneCount() >= right.oneCount();
		}
		bool operator <= (BitString right) {
			return oneCount() <= right.oneCount();
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

int main(void)
{
	BitString a;
	BitString b;
	a = 1000000000000000;
	a = a << 40;
	b = 1000000000000000;
	cout << "a:\n"; 
	a.print("bin");
	cout << "b:\n"; 
	b.print("bin");
	a = a | b;
	cout << "a = a | b:\n"; 
	a.print("bin");
	a = a << 3;
	cout << "a << 3:\n"; 
	a.print("bin");
	a = a >> 7;
	cout << "a >> 7:\n"; 
	a.print("bin");
	cout << "b:\n"; 
	b.print("bin");
	a = a & b;
	cout << "a = a & b:\n"; 
	a.print("bin");
	cout << a.oneCount() << "\n";
	cout << "a == a:" << (a == a) << "\n";
	cout << "a < b:" << (a < b) << "\n";
	cout << "a > b:" << (a > b) << "\n";
	return 0;
}
