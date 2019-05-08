//
//  main.cpp
//  Sem_05_03_18_part_2(Big_INt)
//
//  Created by Михаил Остапчук on 05.03.2018.
//  Copyright © 2018 Михаил Остапчук. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <string>
#include <math.h>

class BigInt {
private:
    constexpr static size_t MAX_LENGTH = 1000;
    constexpr static int BASE = 100;
    
    typedef uint16_t  digit_type;
    typedef uint32_t long_digit_type;
    
    digit_type data[MAX_LENGTH];
    size_t size;
    bool is_negative;
public:
    BigInt() : size(0){} //приравнять число 0
    
    BigInt(int Int) { // присвоить int'у
        size = 0;
        char tmp[MAX_LENGTH * 10];
        int i = 0;
        while (Int) {
            tmp[i] = Int % 10 + '0';
            tmp[i + 1] = '\0';
            Int /= 10;
            i++;
        }
        char tmp2[i + 1];
        for (int j = 0; j < i; ++j) {
            tmp2[j] = tmp[i - 1 - j];
            tmp2[j + 1] = '\0';
        }
        *this = BigInt(tmp2);
    }
        
    BigInt(const char* Str) {
        size = 0;
        int pow_BASE = 0;
        int tmp_BASE = BASE;
        while (tmp_BASE % 10 == 0) {
            tmp_BASE /= 10;
            pow_BASE++;
        }
        for (int i = (int)strlen(Str) - 1; i >= 0; i -= pow_BASE) {
            if (i >= pow_BASE) {
                data[size] = 0;
                for (int j = pow_BASE - 1, k = 0; j >= 0; --j, ++k) {
                    data[size] += (Str[i - k] - '0') * (int)pow(10, k);
                }
                size++;
            } else if (i != 0) {
                data[size] = 0;
                for (int j = i, k = 0; j >= 0; --j, ++k) {
                    data[size] += (Str[i - k] - '0') * (int)pow(10, k);
                }
                size++;
            } else {
                data[size] = Str[i] - '0';
                size++;
            }
        }
    }
    
    BigInt operator + (const BigInt& other) const {
        BigInt res;
        size_t Max_Size = std::max(this->size, other.size);
        int next = 0;
        while(res.size != Max_Size - 0) {
            res.data[res.size] = next;
            if (other.size > res.size) {
                res.data[res.size] += other.data[res.size];
            }
            if (this->size > res.size) {
                res.data[res.size] += this->data[res.size];
            }
            next = res.data[res.size] / BASE;
            res.data[res.size] %= BASE;
            res.size++;
        }
        if (next != 0) {
            res.data[res.size] = next;
            res.size++;
        }
        return res;
    }
    
    BigInt operator * (const BigInt& other) const {
        BigInt res;
        int next = 0;
        res.size = this->size + other.size;
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < other.size; j++) {
                res.data[i + j] = 0;
            }
        }
        std::cout << this->size << "this->size \n";
        std::cout << other.size << "other.size \n";
        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < other.size; j++) {
                res.data[i + j] += this->data[i] * other.data[j] + next;
                next = res.data[i + j] / BASE;
                std::cout << res.data[i + j] << "res.data[i + j] \n";
                std::cout << next << "next \n";
                res.data[i + j] %= BASE;
                std::cout << res.data[i + j] << "res.data[i + j] \n";
            }
            if (next != 0) {
                res.data[i + other.size - 1] = next;
                std::cout << res.data[i + other.size - 1] << "res.data[i + other.size - 1] \n";
            }
        }
        return res;
    }
    
    BigInt operator - (const BigInt& other) const {
        BigInt res;
        size_t Max_Size = std::max(this->size, other.size);
        int next = 0;
        while(res.size != Max_Size - 0) {
            res.data[res.size] = next;
            if (other.size > res.size) {
                res.data[res.size] -= other.data[res.size];
            }
            if (this->size > res.size) {
                res.data[res.size] -= this->data[res.size];
            }
            next = res.data[res.size] / BASE;
            res.data[res.size] %= BASE;
            res.size++;
        }
        if (next != 0) {
            res.data[res.size] = next;
            res.size++;
        }
        return res;
    }
    
    BigInt& operator -= (const BigInt& other) {
        BigInt res(*this - other);
        *this = res;
        return *this;
    }
    
    BigInt& operator += (const BigInt& other) {
        BigInt res(*this + other);
        *this = res;
        return *this;
    }
    
    BigInt& operator *= (const BigInt& other) {
        BigInt res(*this * other);
        *this = res;
        return *this;
    }
    
    bool operator < (const BigInt& other) const {
        if (this->size < other.size) {
            return true;
        } else if (this->size > other.size) {
            return false;
        } else {
            for (int i = 0; i < this->size; ++i) {
                if (this->data[i] < other.data[i]) {
                    return true;
                } else if (this->data[i] > other.data[i]) {
                    return false;
                }
            }
            return false;
        }
    }
    
    bool operator > (const BigInt& other) const {
        return (other < *this);
    }
    
    bool operator == (const BigInt& other) const {
        if (this->size == other.size) {
            for (int i = 0; i < this->size; ++i) {
                if (this->data[i] != other.data[i]) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }
    
    bool operator != (const BigInt& other) const {
        return !(*this == other);
    }
    
    bool operator <= (const BigInt& other) const {
        if ((*this < other) || (*this == other)) {
            return true;
        } else {
            return false;
        }
    }
    
    bool operator >= (const BigInt& other) const {
        return (other <= *this);
    }
    
    friend std::ostream& operator << (std::ostream& out, const BigInt& other) {
        for (int i = (int)other.size - 1; i >= 0; i --) {
            out << other.data[i];
        }
        return out;
    }
    
    friend std::istream& operator >> (std::istream& in, BigInt& bigint){
        char buffer[MAX_LENGTH * 10];
        in >> buffer;
        bigint = BigInt(buffer);
        return in;
    }
    
};
int main() {
    BigInt A, B;
    std::cin >> A >> B;
    std::cout << (A + B) << std::endl;
    return 0;
}
