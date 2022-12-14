#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

int* generateTestMatrix(int n);
int* generateOutputTestMatrix(const int n);
int countDigit(long long n);
void printMatrix(int* matrix, int n);
int checkMatricesEquality(const int* matrix1, const int* matrix2, int n);

#endif // COMMONFUNCTIONS_H
