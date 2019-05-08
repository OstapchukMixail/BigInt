//
//  main.cpp
//  T_T(MATRIX)
//
//  Created by Михаил Остапчук on 18.04.2018.
//  Copyright © 2018 Михаил Остапчук. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <math.h>

template<typename T>
class SquareMatrix;

class MatrixAllocationError {
};

class MatrixWrongSizeError {
};

class MatrixIndexError {
};

class MatrixIsDegenerateError {
};

// non-specified functions to get "zero" and "one" of type T

template<typename T> T getZero() {
    return T(0);
}

template<typename T> T getOne() {
    return T(1);
}

//=============== Matrix class ===============//

template<typename T>
class Matrix {
private:
    int rowsCnt;
    int colsCnt;
    //type your code here
protected:
    T **array;
    //type your code here
public:
    explicit Matrix(int rowsCnt, int colsCnt) {
        this->rowsCnt = rowsCnt;
        this->colsCnt = colsCnt;
        array = new T*[rowsCnt];
        for (int i = 0; i < rowsCnt; ++i) {
            array[i] = new T[colsCnt];
        }
    }
    
    ~Matrix() {
        if (array != nullptr) {
            for (int i = 0; i < rowsCnt; ++i) {
                delete[] array[i];
            }
            delete[] array;
        }
    }
    
    Matrix& operator = (const Matrix& other) {
        if (&other != this) {
            this->~Matrix();
            rowsCnt = other.rowsCnt;
            colsCnt = other.colsCnt;
            array = new T*[rowsCnt];
            for (int i = 0; i < rowsCnt; ++i) {
                array[i] = new T[colsCnt];
            }
            for (int i = 0; i < rowsCnt; ++i) {
                for (int j = 0; j < colsCnt; ++j) {
                    array[i][j] = other.array[i][j];
                }
            }
        }
        return *this;
    }
    
    Matrix(const Matrix& other) : Matrix(other.rowsCnt, other.colsCnt) {
        *this = other;
    }
    
    friend std::istream& operator >> (std::istream& in, const Matrix& other) {
        for (int i = 0; i < other.rowsCnt; ++i) {
            for (int j = 0; j < other.colsCnt; ++j) {
                in >> other.array[i][j];
            }
        }
        return in;
    }
    
    friend std::ostream& operator << (std::ostream& out, const Matrix& other) {
        for (int i = 0; i < other.rowsCnt; ++i) {
            for (int j = 0; j < other.colsCnt; ++j) {
                out << other.array[i][j] << ' ';
            }
            out << '\n';
        }
        return out;
    }
    
    Matrix operator * (T value) const {
        Matrix res(*this);
        for (int i = 0; i < rowsCnt; ++i) {
            for (int j = 0; j < colsCnt; ++j) {
                res.array[i][j] = res.array[i][j] * value;
            }
        }
        return res;
    }
    
    Matrix& operator *= (T value) {
        *this = *this * value;
        return *this;
    }
    
    friend Matrix operator * (const Matrix& first, const Matrix& other) {
        if (first.colsCnt != other.rowsCnt) {
            throw MatrixWrongSizeError();
        }
        Matrix res(first.rowsCnt, other.colsCnt);
        for (int i = 0; i < first.rowsCnt; ++i) {
            for (int j = 0; j < other.colsCnt; ++j) {
                res.array[i][j] = 0;
                for (int k = 0; k < first.colsCnt; ++k) {
                    res.array[i][j] += first.array[i][k] * other.array[k][j];
                }
            }
        }
        return res;
    }
    
    Matrix& operator *= (const Matrix& other) {
        *this = *this * other;
        return *this;
    }
    
    Matrix& operator += (const Matrix& other) {
        if ((this->rowsCnt != other.rowsCnt) || (this->colsCnt != other.colsCnt)) {
            throw MatrixWrongSizeError();
        }
        for (int i = 0; i < rowsCnt; ++i) {
            for (int j = 0; j < colsCnt; ++j) {
                array[i][j] += other.array[i][j];
            }
        }
        return *this;
    }
    
    Matrix operator + (const Matrix& other) const {
        Matrix res(*this);
        res += other;
        return res;
    }
    
    Matrix& operator -= (const Matrix& other) {
        Matrix res(other);
        res = res * -1;
        *this += res;
        return *this;
    }
    
    Matrix operator - (const Matrix& other) const {
        Matrix res(*this);
        res -= other;
        return res;
    }
    
    friend Matrix operator * (T value, const Matrix& other) {
        Matrix res(other);
        res = res * value;
        return res;
    }
    
    Matrix getTransposed() const {
        Matrix res(this->colsCnt, this->rowsCnt);
        for (int i = 0; i < res.rowsCnt; ++i) {
            for (int j = 0; j < res.colsCnt; ++j) {
                res.array[i][j] = this->array[j][i];
            }
        }
        return res;
    }
    
    Matrix& transpose() {
        *this = getTransposed();
        return *this;
    }
    
    int getRowsNumber() const {
        return this->rowsCnt;
    }
    
    int getColumnsNumber() const {
        return this->colsCnt;
    }
    
    T& operator () (int i, int j) {
        if ((i < 0) || (i >= this->rowsCnt) || (j < 0) || (j >= this->colsCnt)) {
            throw MatrixIndexError();
        }
        return this->array[i][j];
    }
    
    T operator () (int i, int j) const {
        if ((i < 0) || (i >= this->rowsCnt) || (j < 0) || (j >= this->colsCnt)) {
            throw MatrixIndexError();
        }
        return this->array[i][j];
    }
};

//=============== SquareMatrix class ===============//

template<typename T>
class SquareMatrix : public Matrix<T> {
protected:
    int size;
public:
    explicit SquareMatrix(int size) : size(size), Matrix<T>(size, size) {}
    
    friend std::istream& operator >> (std::istream& in, const SquareMatrix& other) {
        for (int i = 0; i < other.size; ++i) {
            for (int j = 0; j < other.size; ++j) {
                in >> other.array[i][j];
            }
        }
        return in;
    }
    
    friend std::ostream& operator << (std::ostream& out, const SquareMatrix& other) {
        for (int i = 0; i < other.size; ++i) {
            for (int j = 0; j < other.size; ++j) {
                out << other.array[i][j] << ' ';
            }
            out << '\n';
        }
        return out;
    }
    
    SquareMatrix operator * (T value) const {
        SquareMatrix res(*this);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                res.array[i][j] = res.array[i][j] * value;
            }
        }
        return res;
    }
    
    SquareMatrix& operator *= (T value) {
        *this = *this * value;
        return *this;
    }
    
    SquareMatrix operator * (const SquareMatrix& other) const {
        if (this->size != other.size) {
            throw MatrixWrongSizeError();
        }
        SquareMatrix res(this->size);
        for (int i = 0; i < this->size; ++i) {
            for (int j = 0; j < other.size; ++j) {
                res.array[i][j] = 0;
                for (int k = 0; k < this->size; ++k) {
                    res.array[i][j] += this->array[i][k] * other.array[k][j];
                }
            }
        }
        return res;
    }
    
    SquareMatrix& operator *= (const SquareMatrix& other) {
        *this = *this * other;
        return *this;
    }
    
    SquareMatrix& operator += (const SquareMatrix& other) {
        if (this->size != other.size) {
            throw MatrixWrongSizeError();
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                this->array[i][j] += other.array[i][j];
            }
        }
        return *this;
    }
    
    SquareMatrix operator + (const SquareMatrix& other) const {
        SquareMatrix res(*this);
        res += other;
        return res;
    }
    
    SquareMatrix& operator -= (const SquareMatrix& other) {
        SquareMatrix res(other);
        res = res * -1;
        *this += res;
        return *this;
    }
    
    SquareMatrix operator - (const SquareMatrix& other) const {
        SquareMatrix res(*this);
        res -= other;
        return res;
    }
    
    friend SquareMatrix operator * (T value, const SquareMatrix& other) {
        SquareMatrix res(other);
        res = res * value;
        return res;
    }
    
    int getSize() const{
        return this->size;
    }
        
    T getDeterminant() const {
        SquareMatrix tmp(*this);
        int multiplier = 1;
        for (int k = 0; k < tmp.size; ++k) {
            for (int j = k + 1; j < tmp.size; ++j) {
                if (tmp.array[k][k] == 0) {
                    int l = k;
                    while((l < tmp.size) && (tmp.array[l][k] == 0)) {
                        l++;
                    }
                    if (l == tmp.size) {
                        return (T)0;
                    } else {
                        std::swap(tmp.array[l], tmp.array[k]);
                        multiplier *= -1;
                    }
                }
                T tmp_value = tmp.array[k][j] / tmp.array[k][k];
                for (int i = 0; i < tmp.size; ++i) {
                    tmp.array[i][j] -= tmp.array[i][k] * tmp_value;
                }
            }
        }
        T res = multiplier;
        for (int i = 0; i < tmp.size; ++i) {
            res *= tmp.array[i][i];
        }
        return res;
    }
    
    T getTrace() const {
        T res = 0;
        for (int i = 0; i < this->size; ++i) {
            res += this->array[i][i];
        }
        return res;
    }
    
    SquareMatrix getTransposed() const {
        SquareMatrix res = *this;
        for (int i = 0; i < res.size; ++i) {
            for (int j = i; j < res.size; ++j) {
                T tmp = res.array[i][j];
                res.array[i][j] = res.array[j][i];
                res.array[j][i] = tmp;
            }
        }
        return res;
    }
    
    SquareMatrix& transpose() {
        for (int i = 0; i < this->size; ++i) {
            for (int j = i; j < this->size; ++j) {
                T tmp = this->array[i][j];
                this->array[i][j] = this->array[j][i];
                this->array[j][i] = tmp;
            }
        }
        return *this;
    }
    
    T& operator () (int i, int j) {
        if ((i < 0) || (i >= this->size) || (j < 0) || (j >= this->size)) {
            throw MatrixIndexError();
        }
        return this->array[i][j];
    }
    
    T operator () (int i, int j) const {
        if ((i < 0) || (i >= this->size) || (j < 0) || (j >= this->size)) {
            throw MatrixIndexError();
        }
        return this->array[i][j];
    }
    
    
    
    SquareMatrix& invert() {
        if (this->getDeterminant() == 0) {
            throw MatrixIsDegenerateError();
        }
        SquareMatrix tmp(*this), E(this->size);
        for (int i = 0; i < this->size; ++i) {
            for (int j = 0; j < this->size; ++j) {
                if (i != j) {
                    E.array[i][j] = (T)0;
                } else {
                    E.array[i][j] = (T)1;
                }
            }
        }
        for (int k = 0; k < tmp.size; ++k) {
            if (tmp.array[k][k] == 0) {
                int l = k;
                while (tmp.array[l][k] == 0) {
                    l++;
                }
                std::swap(tmp.array[l], tmp.array[k]);
                std::swap(E.array[l], E.array[k]);
            }
            T tmp_value = tmp.array[k][k];
            for (int j = 0; j < tmp.size; ++j) {
                tmp.array[k][j] /= tmp_value;
                E.array[k][j] /= tmp_value;
            }
            for (int i = k + 1; i < tmp.size; ++i) {
                T tmp_value_first = tmp.array[i][k];
                for (int j = 0; j < tmp.size; ++j) {
                    tmp.array[i][j] -= tmp.array[k][j] * tmp_value_first;
                    E.array[i][j] -= E.array[k][j] * tmp_value_first;
                }
            }
        }
        for (int k = tmp.size - 1; k >= 0; --k) {
            T tmp_value = tmp.array[k][k];
            for (int j = 0; j < tmp.size; ++j) {
                tmp.array[k][j] /= tmp_value;
                E.array[k][j] /= tmp_value;
            }
            for (int i = k - 1; i >= 0; --i) {
                tmp_value = tmp.array[i][k];
                for (int j = 0; j < tmp.size; ++j) {
                    tmp.array[i][j] -= tmp.array[k][j] * tmp_value;
                    E.array[i][j] -= E.array[k][j] * tmp_value;
                }
            }
        }
        *this = E;
        return *this;
    }
    
    SquareMatrix getInverse() const {
        SquareMatrix res(*this);
        return res.invert();
    }
    
};

// this works also for SquareMatrix as this does not rely on any square-specific features


//================ class Rational ===============//

class RationalDivisionByZero {
};

int GCD (int a, int b) {
    a = abs(a);
    b = abs(b);
    if ((a == 0) || (b == 0) || (a == b)) {
        return std::max(a, b);
    } else if ((a == 1) || (b == 1)) {
        return 1;
    } else if ((a % 2 == 0) && (b % 2 == 0)) {
        return 2 * GCD(a / 2, b / 2);
    } else if ((a % 2 == 0) && (b % 2 != 0)) {
        return GCD(a / 2, b);
    } else if ((a % 2 != 0) && (b % 2 == 0)) {
        return GCD(a, b / 2);
    } else if ((a % 2 != 0) && (b % 2 != 0) && (b > a)) {
        return GCD((b - a) / 2, a);
    } else {
        return GCD((a - b) / 2, b);
    }
}

class Rational {
private:
    int p;
    uint32_t q; // is maintained to be positive
    
    void reduce() {
        int intGCD;
        if (p == 0) {
            q = 1;
        } else if (p == q) {
            p = 1;
            q = 1;
        } else {
            intGCD = abs(GCD(p, q));
            p /= intGCD;
            q /= intGCD;
        }
    }
    
public:
    Rational() {}
    
    Rational(int p) : p(p), q(1) {}
    
    Rational(int p, int q) {
        if (q < 0) {
            this->q = q * (-1);
            this->p = p * (-1);
        } else {
            this->p = p;
            this->q = q;
        }
        reduce();
    }
    
    int getNumerator() const {
        return this->p;
    }
    
    int getDenominator() const {
        return this->q;
    }
    
    friend std::istream& operator >> (std::istream& in, Rational& other) {
        in >> other.p;
        if (in.peek() == '/') {
            char tmp;
            in >> tmp >> other.q;
        } else {
            other.q = 1;
        }
        return in;
    }
    
    friend std::ostream& operator << (std::ostream& out, const Rational& other) {
        out << other.p;
        if (other.q != 1) {
            out << '/' << other.q;
        }
        return out;
    }
    
    friend Rational operator / (const Rational& first, const Rational& other) {
        Rational res;
        if (other.p == 0) {
            throw RationalDivisionByZero();
        } else {
            res.p = first.p * other.q;
            res.q = first.q * abs(other.p);
        }
        if (other.p < 0) {
            res.p *= -1;
        }
        res.reduce();
        return res;
    }
    
    friend bool operator < (const Rational& first, const Rational& other) {
        return ((first.p * (int)other.q) < ((int)first.q * other.p));
    }
    
    friend bool operator > (const Rational& first, const Rational& other) {
        return ((first.p *(int)other.q) > ((int)first.q * other.p));
    }
    
    friend bool operator == (const Rational& first, const Rational& other) {
        return ((!(first < other)) && (!(first > other)));
    }
    
    friend bool operator != (const Rational& first, const Rational& other) {
        return (!(first == other));
    }
    
    friend bool operator >= (const Rational& first, const Rational& other) {
        return (!(first < other));
    }
    
    friend bool operator <= (const Rational& first, const Rational& other) {
        return (!(first > other));
    }
    
    friend Rational operator + (const Rational& first, const Rational& other) {
        Rational res;
        res.p = first.p * (int)other.q + other.p * (int)first.q;
        res.q = first.q * other.q;
        res.reduce();
        return res;
    }
    
    friend Rational operator * (const Rational& first, const Rational& other) {
        Rational res;
        res.p = first.p * other.p;
        res.q = first.q * other.q;
        res.reduce();
        return res;
    }
    
    friend Rational operator - (const Rational& first, const Rational& other) {
        Rational res;
        res.p = first.p * (int)other.q - other.p * (int)first.q;
        res.q = first.q * other.q;
        res.reduce();
        return res;
    }
    
    friend Rational& operator += (Rational& first, const Rational& other) {
        first = (first + other);
        return first;
    }
    
    friend Rational& operator -= (Rational& first, const Rational& other) {
        first = (first - other);
        return first;
    }
    
    friend Rational& operator *= (Rational& first, const Rational& other) {
        first = (first * other);
        return first;
    }
    
    friend Rational& operator /= (Rational& first, const Rational& other) {
        first = (first / other);
        return first;
    }
    
    friend Rational operator + (const Rational& first) {
        Rational res;
        res = first;
        return res;
    }
    
    friend Rational operator - (const Rational& first) {
        Rational res;
        res = first;
        res.p *= (-1);
        return res;
    }
    
    Rational operator ++ (int) {
        Rational res;
        res = *this;
        *this = (*this + 1);
        this->reduce();
        return res;
    }
    
    friend Rational& operator ++ (Rational& first) {
        first = (first + 1);
        first.reduce();
        return first;
    }
    
    Rational operator -- (int) {
        Rational res;
        res = *this;
        *this = (*this - 1);
        this->reduce();
        return res;
    }
    
    friend Rational& operator -- (Rational& first) {
        first = (first - 1);
        first.reduce();
        return first;
    }
};

//=================== main() ===============//

using namespace std;

int main() {
    int m, n, p, q;
    cin >> m >> n >> p >> q;
    
    Matrix<int> A(m, n), B(p, q);
    cin >> A >> B;
    
    A = A;
    try {
        cout << A + B * 2 - m * A << endl;
        cout << (A -= B += A *= 2) << endl;
        cout << (((A -= B) += A) *= 2) << endl;
    } catch (const MatrixWrongSizeError&) {
        cout << "A and B are of different size." << endl;
    }
    B = A;
    cout << B << endl;
    
    Rational r;
    cin >> r;
    Matrix<Rational> C(m, n), D(p, q);
    cin >> C >> D;
    try {
        cout << C * D << endl;
        cout << (C *= D) << endl;
        cout << C << endl;
    } catch (const MatrixWrongSizeError&) {
        cout << "C and D have not appropriate sizes for multiplication." << endl;
    }
    cout << C.getTransposed() * (r * C) << endl;
    cout << C.transpose() << endl;
    cout << C << endl;
    
    SquareMatrix<Rational> S(m);
    cin >> S;
    SquareMatrix<Rational> P(S);
    const SquareMatrix<Rational>& rS = S;
    cout << rS.getSize() << ' ' << rS.getDeterminant() << ' ' << rS.getTrace() << endl;
    cout << (S = S) * (S + rS) << endl;
    cout << (S *= S) << endl;
    C.transpose();
    cout << rS * C << endl;
    cout << S << endl;
    S = P;
    cout << (Rational(1, 2) * S).getDeterminant() << endl;
    try {
        cout << rS(0, 0) << endl;
        (S(0, 0) *= 2) /= 2;
        cout << rS(0, m) << endl;
    } catch (const MatrixIndexError&) {
        cout << "Index out of range." << endl;
    }
    cout << rS.getTransposed() << endl;
    try {
        cout << rS.getInverse() << endl;
        cout << S.invert().getTransposed().getDeterminant() << endl;
        cout << S << endl;
    } catch (const MatrixIsDegenerateError&) {
        cout << "Cannot inverse S." << endl;
    }
    
    return 0;
}
