#include <iostream>
#include <cstdlib>

using namespace std;

int a,b,c,d;
///-----------------------------------------------------------------------------
/// Given matrix a b
///              c d
/// replaces by the square of the matrix.
///-----------------------------------------------------------------------------
void matrix_multiply(int save[][2], int A[][2], int B[][2])
{
    a = A[0][0]*B[0][0] + A[0][1]*B[1][0];
    b = A[1][0]*B[0][0] + A[1][1]*B[1][0];
    c = A[0][0]*B[0][1] + A[0][1]*B[1][1];
    d = A[1][0]*B[0][1] + A[1][1]*B[1][1];
    save[0][0] = a;
    save[0][1] = b;
    save[1][0] = c;
    save[1][1] = d;
}

void printMatrix(int matrix[][2])
{
    printf("%d %d\n%d %d\n\n", matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]);
}

int main()
{
    int n = 29;
    int A[][2] = {{0,1},{1,1}};
    int B[][2] = {{0,0},{0,0}};
    int num = n;
    if (n == 1)
    {
        printMatrix(A);
        return 0;
    }
    if (n % 2 != 0)
    {
        B[0][0] = A[0][0];
        B[0][1] = A[0][1];
        B[1][0] = A[1][0];
        B[1][1] = A[1][1];
    }
    for (int i = 1; i < n; i <<= 1)
    {
        matrix_multiply(A, A, A);
        num >>= 1;
        if (num & 1)
        {
            if (B[0][1] != 0)
            {
                matrix_multiply(B, A, B);
            }
            else
            {
                B[0][0] = A[0][0];
                B[0][1] = A[0][1];
                B[1][0] = A[1][0];
                B[1][1] = A[1][1];
            }
        }
    }

    printMatrix(B);

    return EXIT_SUCCESS;
}
