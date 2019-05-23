
/*
 * Matrix Calculation - by hieutran
 *	
 * Given 2 matrices A, B, and scalar (real number/ fraction) c: 
 *	A+B	returns the matrix as the result of A+B 
 *	A-B	returns the matrix as the result of A-B
 *	A*B	returns the matrix as the result of A*B
 *
 *	A*c	returns the matrix as the result of c*A
 *
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int max(int a, int b) {
	return (a > b ? a : b);
}

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

double toDouble(string f) {
	double ans = 0;

	bool negative;
	int i;

	if (f[0] == '-') {
		negative = true;
		i = 1;
	} else {
		negative = false;
		i = 0;
	}

	while (i < f.size() && f[i] != '.') {
		ans = ans*10 + (f[i] - '0');
		i++;
	}

	double temp = 0.1;
	for (i = i+1; i < f.size(); i++) {
		ans = ans + temp*(f[i] - '0');
		temp /= 10;
	}
	
	if (negative) return -ans;
	else return ans;
}

class fraction {
private:
	int x;
	int y;

public:
	//Create
	fraction() {
		x = 1;
		y = 1;
	}

	fraction(int _x, int _y) {
		x = _x; 
		y = _y;

		reduce();
	}

	fraction(double c) {
		bool negative = false;
		if (c < 0) {
			negative = true;
			c = -c;
		}

		int decimalPart = (c-int(c)) * 100000000;
		
		fraction ans(decimalPart, 100000000);
		ans = (ans + int(c)).reduce();

		x = ans.x;
		y = ans.y;

		if (negative) x = -x;
	}

	fraction (string f) {
		fraction ans;

		bool isFraction = false;

		//check whether f is a fraction from
		for (int i = 0; i < f.size(); i++) {
			if (f[i] == '/') isFraction = true;
		}

		if (!isFraction) { // f is a string of real number

			*this = fraction(toDouble(f));

		} else { // f is a string of fraction

			bool negative;
			int i;

			if (f[0] == '-') {
				negative = true;
				i = 1;
			} else {
				negative = false;
				i = 0;
			}

			int numerator = 0;
			while (i < f.size() && f[i] != '/') {
				numerator = numerator*10 + (f[i] - '0'); 	
				i++;
			}

			int denominator = 0;
			for (i = i+1; i < f.size(); i++) {
				denominator = denominator*10 + (f[i] - '0');
			}

			*this = fraction(numerator, denominator);
			if (negative) {
				*this = (*this) * (-1);
			}
		}
	}

	//Read
	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	double getValue() {
		return double(x)/y;	
	}

	string toString() {
		if (x == 0) {
			return "0";
		}

		string numerator = "";

		bool negative;
		int temp;

		if (x < 0) {
			negative = true;
			temp = -x;
		} else {
			negative = false;
			temp = x;
		}

		while (temp != 0) {
			numerator = (char)('0' + temp%10) + numerator;
			temp /= 10;
		}

		if (negative) {
			numerator = "-" + numerator;
		}

		string denominator = "";
		for (temp = y; temp != 0; temp /= 10) denominator = (char)('0' + temp%10) + denominator;
	
		if (y == 1) return numerator; return numerator + "/" + denominator;	
	}

	//Update
	void set(int _x, int _y) {
		x = _x;
		y = _y;

		reduce();
	}
	void setX(int _x) {
		x = _x;
		reduce();
	}
	void setY(int _y) {
		y = _y;
		reduce();
	}

	//operator
	fraction operator + (fraction other) {
		fraction ans;

		if (this->y == other.y) {
			ans.set(this->x + other.x, this->y);
		} else {
			ans.set(this->x*other.y + other.x*this->y, this->y * other.y);
		}
		return ans.reduce();
	}

	
	fraction operator * (int c) {
		fraction ans;
		
		ans.set(c*x, y);
		return ans.reduce();
	}

	fraction operator * (fraction other) {
		fraction ans;

		ans.set(this->x * other.x, this->y * other.y);
		return ans.reduce();
	}

	fraction operator - (fraction other) {
		return *this + other*(-1);
	}

	fraction operator + (int c) {
		if (c == 0) return *this;
		fraction ans = (*this) + fraction(c*this->y, this->y);
		return ans.reduce();
	}

	fraction operator / (fraction other) {
		fraction ans = (*this) * fraction(other.y, other.x);
		return ans.reduce();
	}

	fraction operator / (int c) {
		fraction ans = (*this) * fraction(1, c);
		return ans.reduce();
	}

	fraction operator += (fraction other) {
		*this = *this + other;
		return *this;
	}
	fraction operator -= (fraction other) {
		*this = *this - other;
		return *this;
	}
	fraction operator *= (fraction other) {
		*this = *this * other;
		return *this;
	}
	fraction operator /= (fraction other) {
		*this = *this / other;
		return *this;
	}
	
	//Other
	fraction reduce() {
		int g;

		if (x < 0) g = gcd(-x, y);
		else g = gcd(x, y);

		x /= g;
		y /= g; 
		return *this;
	}

	void print() {
		cout << x << "/" << y;
	}
};

template<class T>
class matrix {
private:
	int row, col;
	vector<vector<T>> mat;
	
public:
	//Create
	matrix() {
		row = 0;
		col = 0;
	}
	matrix(int _row, int _col) {
		row = _row;
		col = _col;

		mat.clear();
		for (int i = 0; i < _row; i++) {
			mat.push_back(vector<T>(col));
		}
	}
	matrix(vector<vector<T>> _mat) {
		mat = _mat;
		row = mat.size();
		col = mat[0].size();
	}

	//Read
	int getRow() {
		return row;
	}
	int getCol() {
		return col;
	}
	T get(int i, int j) {
		return mat[i][j];
	}
	
	//Update
	void setSize(int _row, int _col) {
		row = _row;
		col = _col;

		mat.clear();
		for (int i = 0; i < _row; i++) {
			mat.push_back(vector<T>(col));
		}
	}
	void setRow(int _row) {
		row = _row;
	}
	void setCol(int _col) {
		col = _col;
	}
	void set(int i, int j, int value) {
		mat[i][j] = value;
	}

	void read() {
		for (int i = 0; i < row; i++) 
		for (int j = 0; j < col; j++) {
			string entry;
			cin >> entry;
			mat[i][j] = fraction(entry);
		}
	}
	void read(int _row, int _col) {
		setSize(_row, _col);
		read();
	}

	//operators
	matrix operator + (matrix other) {
		matrix ans(row, col);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				ans.mat[i][j] = this->mat[i][j] + other.mat[i][j];	
			}
		}
		
		return ans;
	}

	matrix operator * (double scalar) {
		matrix<T> ans(row, col);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				ans.mat[i][j] = this->mat[i][j]*scalar;
			}
		}
	}
	matrix operator * (fraction scalar) {
		matrix<T> ans(row, col);
		
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				ans.mat[i][j] = this->mat[i][j]*scalar;
			}
		}

		return ans;
	}

	matrix operator - (matrix other) {
		return *this + other*(-1);
	}

	matrix operator * (matrix other) {
		matrix<T> ans(this->row, other.col);

		for (int i = 0; i < this->getRow(); i++)
		for (int j = 0; j < other.getCol(); j++) {
			ans.mat[i][j] = 0;
			for (int k = 0; k < this->getCol(); k++) {
				ans.mat[i][j] += this->mat[i][k] * other.mat[k][j];	
			}			
		}

		return ans;
	}

	//others
	void print() {
		cout << "matrix of Size " << row << "x" << col << ": " << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << mat[i][j].toString() << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
};

void print2matrix(matrix<fraction> A, matrix<fraction> B) {
	system("clear");

	for (int i = 0; i < max(A.getRow(), B.getRow()); i++) {
		int entryWidth = 8;

		bool printA = (i < A.getRow());
		bool printB = (i < B.getRow());

		if (printA) {
			cout << " | ";
		} else {
			cout << "   ";
		}

		for (int j = 0; j < A.getCol(); j++) {
			if (printA) cout << setw(entryWidth) << A.get(i, j).toString();
			else cout << setw(entryWidth) << "";
		}
		
		if (printA) cout << " |" << setw(entryWidth) << "---";
		else cout << "  " << setw(entryWidth) << "";


		if (printB) {
			cout << setw(entryWidth) << "| ";
		}

		for (int j = 0; j < B.getCol(); j++) {
			if (printB) cout << setw(entryWidth) << B.get(i, j).toString();
			else cout << "          ";
		}

		if (printB) {
			cout << " |";
		}

		cout << endl;
	}
	cout << endl;
}

int main() {
	int row, col;

	//Declare matrix	
	matrix<fraction> A;
	matrix<fraction> B;
		
	//Input matrix A
	cout << "Input matrix A's size : "; cin >> row >> col;
	cout << "Input matrix A: " << endl; A.read(row, col);

	cout << endl;

	//Input matrix B
	cout << "Input matrix B's size : "; cin >> row >> col;
	cout << "Input matrix B: " << endl; B.read(row, col);

	//print 2 matrix
	print2matrix(A, B);

	cout << "Input operations: " << endl << endl;

	//Input operation
	string operation;
	while (cin >> operation, operation != "end") {
		if (operation == "A") {
			A.print();
		}
		if (operation == "B") {
			B.print();
		}
		if (operation == "A+B") {
			(A+B).print();
		}	

		if (operation == "A-B") {
			(A-B).print();
		}

		if (operation == "A*B") {
			(A*B).print();	
		}

		if (operation == "A*scalar") {
			string scalar;
			cin >> scalar;
			(A*fraction(scalar)).print();
		}

		if (operation == "A*=B") {
			A = A*B;
			cout << "new A = " << endl;
			A.print();
		}
		if (operation == "B*=scalar") {
			string scalar;
			cin >> scalar;
			B = B*fraction(scalar);
			A.print();
		}

		if (operation == "B*=A") {
			B = B*A;
			cout << "New B = " << endl;
			B.print();
		}

		if (operation == "B*=scalar") {
			double scalar;
			cin >> scalar;
			B = B*fraction(scalar);
			B.print();
		}

		if (operation == "swap") {
			matrix<fraction> temp = A;
			A = B;
			B = temp;
		}

		if (operation == "clear") {
			print2matrix(A, B);
			cout << endl;
			cout << "Input operations: " << endl << endl;
		}
	}

	return 0;
}
