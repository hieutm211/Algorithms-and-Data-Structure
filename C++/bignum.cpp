// Addition, Subtraction, Multiplication with big Integer C++, written by TMH
// Phép cộng, Trừ, Nhân Số nguyên lớn C++ 
// Addition/ Phép cộng : O(n);
// Subtraction/ Phép trừ : O(n);
// Multiplication/ Phép nhân : O(n^2);

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int bignumSize = 1000; // Number of Digits up to 5*bignumSize

class bignum{
private:
	int length;
	bool pos;
	int val[bignumSize+5];
public:
	bignum(){ length = 1; val[0] = 0; }
	bignum(const char* s){
		int start, suffix, tmp;

		this->length = 0;

		start = 0;
		while (s[start] != '+' && s[start] != '-' && (s[start] < '0' && '9' < s[start])) ++start;
		this->pos = (s[start] != '-');
		start = (s[start] == '+' || s[start] == '-');

		suffix = 0; tmp = 1;
		for (int i = strlen(s)-1; i >= start; --i){
			suffix = (s[i] - '0') * tmp + suffix;
			tmp = tmp * 10;
			if (tmp == 1e5){
				this->val[length++] = suffix;
				suffix = 0;
				tmp = 1;
			}
		}
		if (suffix != 0) this->val[length++] = suffix;
	}

	bignum abs() const { bignum ans(*this); ans.pos = 1; return ans; }

	int cmp (const bignum& other) const {
		if (this->pos != other.pos) return (this->pos ? 1 : -1);
		if (this->length != other.length){
			if (!this->pos) return (this->length < other.length) ? 1 : -1;
			else return (this->length > other.length ? 1 : -1);
		}

		for (int i = this->length-1; i >= 0; --i)
			if (this->val[i] < other.val[i]) return (!this->pos ? 1 : -1);
			else if (this->val[i] > other.val[i]) return (this->pos ? 1 : -1);

		return 0;
	}

	int cmp_abs (const bignum& other) const {
		if (this->length != other.length){
			if (!this->pos) return (this->length < other.length) ? 1 : -1;
			else return (this->length > other.length ? 1 : -1);
		}

		for (int i = this->length-1; i >= 0; --i)
			if (this->val[i] < other.val[i]) return (!this->pos ? 1 : -1);
			else if (this->val[i] > other.val[i]) return (this->pos ? 1 : -1);

		return 0;
	}	

	bignum operator + (const bignum& other) const {
		bignum ans;
		int carry, sum;

		if (!this->pos && !other.pos){
			ans = *this - other.abs();
			ans.pos = 0;
			return ans;
		} else {
			if (!this->pos){
				ans = other - this->abs();
				ans.pos = (other.cmp_abs(*this) >= 0); 
				return ans;
			}
			if (!other.pos){
				ans = *this - other.abs();
				ans.pos = (this->cmp_abs(other) >= 0);
				return ans;
			}
		}

		ans.pos = 1;
		ans.length = max(this->length, other.length);

		carry = 0; sum = 0;
		for (int i = 0; i < ans.length; ++i){
			sum = (this->length > i) * this->val[i] + (other.length > i) * other.val[i] + carry;
			ans.val[i] = sum % (int) 1e5;
			carry = sum / 1e5;
		}

		if (carry) ans.val[ans.length++] = carry;

		return ans;
	}

	bignum operator - (const bignum& other) const {
		bignum ans;
		int carry;

		if (!this->pos && other.pos){
			ans = this->abs() + other.abs();
			ans.pos = 0;
			return ans;
		}
		if (this->pos && !other.pos){
			ans = this->abs() + other.abs();
			ans.pos = 1;
			return ans;
		}
		if (!this->pos && !other.pos){
			ans = other.abs() - this->abs();
			ans.pos = (other.abs().cmp_abs(*this) >= 0);
			return ans;
		}
		if (this->pos && other.pos)
			if (this->cmp(other) == -1){
				ans = other - *this;
				ans.pos = 0;
				return ans;
			}

		ans.length = this->length;
		ans.pos = 1;

		carry = 0;
		for (int i = 0; i < ans.length; ++i){
			ans.val[i] = this->val[i] - (other.length > i)*other.val[i] - carry;
			if (ans.val[i] < 0){
				ans.val[i] += 1e5;
				carry = 1;
			} else carry = 0;
		}
		while (ans.length >= 2 && ans.val[ans.length-1] == 0) --ans.length;
		return ans;
	}

	bignum operator * (const bignum& other){
		bignum ans;
		int carry;
		long long product;

		ans.length = this->length + other.length;
		for (int i = 0; i < ans.length; ++i) ans.val[i] = 0;

		for (int j = 0; j < other.length; ++j){
			carry = 0;
			for (int i = 0; i < this->length; ++i){
				product = (long long) this->val[i] * other.val[j] + carry + ans.val[i+j];
				ans.val[i+j] = product % (int)1e5;
				carry = product / 1e5;
			}
			if (carry) ans.val[this->length + j] = carry;
		}
		while (ans.length >= 2 && ans.val[ans.length-1] == 0) --ans.length;

		ans.pos = (this->pos == other.pos);
		return ans;
	}

	int size(){ return length; }
	void print(){
		if (!this->pos) printf("-");
		printf("%d", val[length-1]);
		for (int i = length-2; i >= 0; --i) printf("%05d", val[i]);  
	}
	void println(){ print(); printf("\n"); }
};

int main(){
	char number1[bignumSize*5], number2[bignumSize*5];

	printf("number1 = "); cin >> number1;
	printf("number2 = "); cin >> number2;

	bignum a = number1;
	bignum b = number2;

	printf("\n");
	printf("a + b = "); (a + b).println();
	printf("a - b = "); (a - b).println();
	printf("a * b = "); (a * b).println();

	return 0;
}

