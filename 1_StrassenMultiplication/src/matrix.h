#define MaxRows2Print 8
#define MaxCols2Print 4
#define DecimalPrecision 2

#include <assert.h>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <string>
#include <iomanip>
#include <iostream>

template<class T>
class SubMat2d;

template<class T>
static char digtoChar(T n) {
    int _n = (int) n;
    switch (_n % 10) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        default: return '0';
    }
}

template<class T>
static void updateWidth(T val, short * nDig) {
    if (val == 0) {
        if (1 > *nDig) *nDig = 1;
        return;
    }
    short digs = 0;
    if(val < 0) {
        digs++;
        val*=-1;
    }
    if (std::is_floating_point<T>::value) {
        // From here
        long long deciCounterStart = 1;
        short m = 0;
        while (m < DecimalPrecision) {
            deciCounterStart *= 10;
            m++;
        }
        // Till here will be computed on compile time

        long long deciCounter = 10, _val = (long long)((val - trunc(val))*deciCounterStart);
        while(m > 0) {
            if(_val % deciCounter >= 1)
                break;
            m--;
            deciCounter *= 10;
        }
        digs += m + 1;
    }
    while (val >= 1) {
        digs++;
        val /= 10;
    }
    if (digs > *nDig) *nDig = digs;
}

template<class T>
static std::string numToStr(T val) {
    std::string str = "";
    if (val == 0) {
        return "0";
    }
    bool isNeg = false;
    if (val < 0) {
        isNeg = true;
        val*=-1;
    }

    long long _val = (long long)val;
    while (_val) {
        str = digtoChar(_val) + str;
        _val /= 10;
    }
    if(std::is_floating_point<T>::value) {
        str += '.';
        long long deciCounterStart = 1;
        short m = 0;
        while (m < DecimalPrecision) {
            deciCounterStart *= 10;
            m++;
        }
        val -= trunc(val);
        T _temp = val * deciCounterStart;
        long long digs = trunc(_temp);
        if (_temp - digs >= .5)
            digs += 1;
        while(m > 0) {
            if((digs % 10) >= 1)
                break;
            m--;
            digs/=10;
            deciCounterStart/=10;
        }
        while(m--) {
            deciCounterStart /= 10;
            str += digtoChar(digs / deciCounterStart);
        }
    }
    if (isNeg) str = '-' + str;
    return str;
}

/**
 * T the type of data to store
 * m number of rows
 * n number of cols
*/
template<class T>
class Mat2d {
    static_assert(
        std::is_arithmetic<T>::value, "Only arithmetic values can be stored in this Matrix."
    );
public:
    friend class SubMat2d<T>;

    Mat2d(uint16_t _nrows, uint16_t _ncols, T val = 0, bool setZero = false) : m(_nrows), n(_ncols) {
        values = std::shared_ptr<T>(new T[_nrows*_ncols], [](T* x){delete[] x;});
        if ((val == 0) && setZero)
            m_isZero = true;
        else
            m_isZero = false;
    
        std::fill_n(values.get(), m*n, val);
    }

    Mat2d(uint16_t _nrows, uint16_t _ncols, T vals[]) : m(_nrows), n(_ncols) {
        values = std::shared_ptr<T>(new T[_nrows*_ncols], [](T* x){delete[] x;});
        m_isZero = false;

        std::copy(vals, vals + (m*n), values.get());
    }

    Mat2d(const Mat2d<T> & mat) : m(mat.m), n(mat.n) {
        values = mat.values;
        m_isZero = false;
    }

    virtual Mat2d<T>* set(uint16_t a, uint16_t b, T val = 0) {
        if ((a < m) && (b < n))
            values.get()[a*this->n + b] = val;
        return this;
    }

    virtual T get(uint16_t a, uint16_t b) const {
        assert((a < this->m) && (b < this->n));
        return values.get()[a*this->n + b];
    }

    uint16_t getm() const {
        return m;
    }

    uint16_t getn() const {
        return n;
    }

    Mat2d<T> operator+(const Mat2d<T>& rmat) {
        assert((rmat.m == this->m) && (rmat.n == this->n));
        auto mat = Mat2d<T>(rmat.m, rmat.n);
        for(uint16_t i = 0; i < m; i++) { 
            for(uint16_t j = 0; j < n; j++) {
                mat.set(i, j, this->get(i, j) + rmat.get(i, j));
            }
        }
        return mat;
    }

    Mat2d<T> operator-(const Mat2d<T>& rmat) {
        assert((rmat.m == this->m) && (rmat.n == this->n));
        auto mat = Mat2d<T>(rmat.m, rmat.n);
        for(uint16_t i = 0; i < m; i++) { 
            for(uint16_t j = 0; j < n; j++) {
                mat.set(i, j, this->get(i, j) - rmat.get(i, j));
            }
        }
        return mat;
    }

    void print(bool newLine = true) {
        if (newLine) std::cout << "\n";

        // First calculate max width of character.
        uint16_t nCols;
        if (this->n <= MaxCols2Print)
            nCols = this->n;
        else
            nCols = MaxCols2Print - 1;
        short maxWidth[nCols] = { 0 };
        uint16_t i, j, k; i = j = k = 0;
        while(j < this->n) {
            while (i < this->m) {
                if ((this->m > MaxRows2Print) && (i == (MaxRows2Print - 2)))
                    i = this->m-1;
                updateWidth(this->get(i, j), maxWidth + k);
                i++;
            }
            j++;k++;i=0;
            if ((this->n > MaxCols2Print) && (j == (MaxCols2Print - 2))) {
                j = this->n - 1;
            }
        }
        i = j = k = 0;

        std::string str;
        uint16_t w = 0;
        while(i < this->m) {
            if (i == 0)
                std::cout << "⎾";
            else if (i == m-1)
                std::cout << "⎿";
            else
                std::cout << "⎹";
            while(j < this->n) {
                if ((this->n > MaxCols2Print) && (j == (MaxCols2Print - 2))) {
                    if ((this->m > MaxRows2Print) && (i == this->m-2))
                        std::cout << " ⋱";
                    else
                        std::cout << " ⋯";
                    j = this->n - 1;
                    continue;
                }
                else
                    if ((this->m > MaxRows2Print) && (i == this->m-2)) {
                        str = "⋮";
                        if (j == 0)
                            w = maxWidth[k] + 3;
                        else
                            w = maxWidth[k] + 4;
                    }
                    else {
                        str = numToStr<T>(this->get(i, j));
                        if (j == 0)
                            w = maxWidth[k] + 1;
                        else
                            w = maxWidth[k] + 2;
                    }
                std::cout << std::setw(w) << str;
                j++;k++;
            } k=j=0;
            if (i == 0)
                std::cout << " ⏋" << std::endl;
            else if (i == m-1)
                std::cout << " ⏌" << this->m << "x" << this->n << std::endl;
            else
                std::cout << " ⎹" << std::endl;
            i++;
            if ((this->m > MaxRows2Print) && (i == (MaxRows2Print-2)))
                i = this->m-2;
        }
    }

    SubMat2d<T> createSubMat(uint16_t rowStart, uint16_t colStart, uint16_t _nrows, uint16_t _ncols) {
        return SubMat2d<T>(rowStart, colStart, _nrows, _ncols, this);
    }

    void emplaceSubMat(const Mat2d<T> & subMat, uint16_t iInit, uint16_t jInit) {
        for(uint16_t i = 0; i< subMat.m; i++) {
            if((i + iInit) >= this->m)
                break;
            for(uint16_t j = 0; j< subMat.n; j++) {
                if((j + jInit) < this->n)
                    this->set(
                        i + iInit, j + jInit, subMat.get(i, j));
                else
                    break;
            }
        }
    }

    bool isZero() {
        return m_isZero;
    }

private:
    uint16_t m, n;
    std::shared_ptr<T> values;
    bool m_isZero;

    Mat2d() {
        m_isZero = false;
    }
};


template<class T>
class SubMat2d : public Mat2d<T> {
public:

    SubMat2d<T>* set(uint16_t a, uint16_t b, T val) {
        if(((a + this->rs) < this->m) && ((b + this->cs) < this->n))
            this->values.get()[((a + this->rs) * this->n) + (b + this->cs)] = val;
        return this;
    }

    T get(uint16_t a, uint16_t b) const {
        if (this->m_isZero) {
            return 0;
        }
        assert((a < this->m) || (b < this->n));
        return this->values.get()[((a + this->rs) * this->n) + (b + this->cs)];
    }

    ~SubMat2d() {
    };

private:
    uint16_t rs, cs; // Row Start, Column Start

    SubMat2d(uint16_t rowStart, uint16_t colStart, uint16_t _m, uint16_t _n, const Mat2d<T>* mat) {
        this->rs = rowStart;
        this->cs = colStart;
        this->n  = _m;
        this->m  = _n;
        this->m_isZero = (mat->m <= this->rs) && (mat->n <= this->cs);
        this->values = mat->values;
    }

    friend SubMat2d<T> Mat2d<T>::createSubMat(uint16_t, uint16_t, uint16_t, uint16_t);
};