/// @author Benjamin Alcocer

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cstdlib>
#include <ostream>

template <class T>
class Matrix
{
public:
    Matrix();
    Matrix(const Matrix<T>& rhs);
    Matrix(const std::vector<std::vector<T>>& matrixTemplate);
    Matrix(const std::vector<T>& vectorTemplate, bool isColumnVector);
    ~Matrix();

    // overloads
    T operator()(std::size_t idx, std::size_t jdx) const
    {
        return matrix[idx][jdx];
    }
    void operator()(std::size_t idx, std::size_t jdx, T value)
    {
        matrix[idx][jdx] = value;
    }
    void operator=(const Matrix& rhs);

    // Functions----------------------------------------------------------------
    // clear(): Call to clear/empty the matrix
    void clear();
    // augmentRight(): A = [A|B]; Call A.augmentRight(B);
    bool augmentRight(const Matrix& rhs);

    // m() and n(): Returns the size of m or n in an mxn matrix
    std::size_t m() const {return msize;}
    std::size_t n() const {return nsize;}
private:
    std::vector<std::vector<T>> matrix; // an mxn matrix
    std::size_t msize, nsize;           // m and n respectively
};


template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
{
    if (mat.m() != 0)
    {
        for (size_t i = 0; i < mat.m(); ++i)
        {
            for (size_t j = 0; j < mat.n(); ++j)
            {
                os << mat(i, j) << " ";
            }
            os << "\n";
        }
    }
    else
    {
        os << "[](0x0)";
    }
    
    return os;
}

template<class T>
void Matrix<T>::operator=(const Matrix& rhs)
{
    msize = rhs.m();
    nsize = rhs.n();
    matrix = rhs.matrix;
}

// Constructors and Destructor
///-----------------------------------------------------------------------------
template <class T>
Matrix<T>::Matrix()
{
    msize = nsize = 0;
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
{
    *this = rhs;
}

template <class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& matrixTemplate)
{
    msize = matrixTemplate.size();
    nsize = msize != 0 ? matrixTemplate[0].size() : 0;
    
    for (std::size_t i = 0; i < msize; ++i)
    {
        matrix.push_back(matrixTemplate[i]);
    }
}

template <class T>
Matrix<T>::Matrix(const std::vector<T>& vectorTemplate, bool isColumnVector)
{
    msize = nsize = 0;
    if (vectorTemplate.empty())
    {
        return;
    }
    if (isColumnVector)
    {
        msize = vectorTemplate.size();
        nsize = 1;
        matrix = std::vector<std::vector<T>>(msize, std::vector<T>(1, 0));
        for (std::size_t i = 0; i < msize; ++i)
        {
            matrix[i][0] = vectorTemplate[i];
        }
    }
    else
    {
        nsize = vectorTemplate.size();
        msize = 1;
        matrix.push_back(vectorTemplate);
    }
}

template <class T>
Matrix<T>::~Matrix()
{
    clear();
}
///-----------------------------------------------------------------------------
template <class T>
void Matrix<T>::clear()
{
    matrix.clear();
    msize = nsize = 0;
}

template <class T>
bool Matrix<T>::augmentRight(const Matrix<T>& rhs)
{
    if (msize != rhs.m())
    {
        return false;
    }
    for (size_t i = 0; i < msize; ++i)
    {
        for (size_t j = 0; j < rhs.n(); ++j)
        {
            matrix[i].push_back(rhs(i, j));
        }
    }
    nsize += rhs.n();
    return true;
}

//------------------------------------------------------------------------------
// Non member functions

///-----------------------------------------------------------------------------
/// Operator overload of binary operator *, to implement matrix multiplication
/// A*B => returns the matrix multiplication of A and B if defined
/// else returns an empty Matrix<T>.
///-----------------------------------------------------------------------------
template <class T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b)
{
    std::vector<std::vector<T>> createMatrix;

    if (a.n() == b.m())
    {
        T sum;
        createMatrix = std::vector<std::vector<T>>(a.m(), std::vector<T>(b.n()));
        for (std::size_t i = 0; i < a.m(); ++i)
        {
            for (std::size_t k = 0; k < b.n(); ++k)
            {
                sum = {};   // to zero initialize
                for (std::size_t j = 0; j < b.m(); ++j)
                {
                    sum = sum + (a(i,j) * b(j,k));
                }
                createMatrix[i][k] = sum;
            }
        }
    }
    Matrix<T> obj(createMatrix);
    return obj;
}

///-----------------------------------------------------------------------------
/// Operator overload of binary operator +, to implement matrix addition
/// A+B => returns the matrix addition of A and B if defined
/// else returns an empty Matrix<T>.
///-----------------------------------------------------------------------------
template <class T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
    std::vector<std::vector<T>> createMatrix;

    // Defined when matrix a and and matrix b have the same dimensions
    if (a.n() == b.n() && a.m() == b.m())
    {
        createMatrix = std::vector<std::vector<T>>(a.m(), std::vector<T>(a.n()));
        for (std::size_t i = 0; i < a.m(); ++i)
        {
            for (std::size_t j = 0; j < a.n(); ++j)
            {
                createMatrix[i][j] = a(i,j) + b(i,j);
            }
        }
    }
    Matrix<T> obj(createMatrix);
    return obj;
}

#endif  // MATRIX_H
