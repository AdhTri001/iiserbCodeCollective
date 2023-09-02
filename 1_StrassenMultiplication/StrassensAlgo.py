import numpy as np
from time import time

MatrixSize = 2**8

######################## UTIL FUNCTIONS ########################

def funcTimer(func):
    '''
    This function decorator prints out the
    execution time of the function call that was made.
    '''
    def wrapper(*args, **kwargs):
        start= time()
        res = func(*args, **kwargs)
        end  = time()
        print("Time taken to execute ", func.__name__,
              " was: ", (end-start)*(10000), "ms", sep= '')
        return res
    return wrapper

def printMat(mat, maxDigits):
    '''
    Beautifully prints out the matrices.
    Prints the whole matrix if the matrix size is less than or
    equal to 6 else prints with dotted notation.
    '''
    i=0
    while i < MatrixSize:
        if i == 0:
            print('⌈', end=' ')
        elif i == MatrixSize-1:
            print('⌊', end=' ')
        else:
            print('|', end=' ')
        if MatrixSize > 6 and i == 4:
            print(('⋮'.center(maxDigits)+' ') * 4, end= '')
            print('⋱', end=' ')
            print('⋮'.center(maxDigits), end=' ')
            print('|')
            i = MatrixSize-1
            continue
        j = 0
        while j < MatrixSize:
            if MatrixSize <= 6 or j < 4:
                print(str(mat[i][j]).ljust(maxDigits), end= ' ')
            else:
                if i < 4 or i == MatrixSize-1:
                    print('⋯', end=' ')
                    print(str(mat[i][MatrixSize-1]).ljust(maxDigits), end= ' ')
                break
            j+=1
        if i == 0:
            print('⌉')
        elif i == MatrixSize-1:
            print('⌋')
        else:
            print('|')
        i+=1

#################### Random Matrices A and b ###################

A = np.random.randint(0, 10, (MatrixSize, MatrixSize))
B = np.random.randint(0, 10, (MatrixSize, MatrixSize))

print("\nA:")
printMat(A, 1)
print("\nB:")
printMat(B, 1)
print('-'*30, end='\n\n')

########### Implementations of Matrix Multiplication ###########

@funcTimer
def matMul(A, B):
    '''
    Product of two square Matrices A and B using 3 for loops
    '''
    C = np.zeros((MatrixSize, MatrixSize), np.int16)
    for i in range(0, MatrixSize):
        for j in range(0, MatrixSize):
            for k in range(0, MatrixSize):
                C[i][j] += A[i][k]*B[k][j]

    return C

@funcTimer
def strassensMatMul(A, B):
    '''
    Product of two square Matrices A and B, using Strassens matrix multiplication algorithm.
    See: https://en.wikipedia.org/wiki/Strassen_algorithm#Algorithm
    '''
    C = np.zeros((MatrixSize, MatrixSize), np.int16)
    _strassensMatMulHelper(A, B, MatrixSize, C)
    return C

def _strassensMatMulHelper(A, B, size, C):
    '''Called by `strassensMatMul` to handle recursion'''
    if size <= 128:
        for i in range(0, size):
            for j in range(0, size):
                for k in range(0, size):
                    C[i][j] += A[i][k]*B[k][j]
    else: # The case where m1,m2,...,m7 are submatrices
        A11 = A[0:size//2   ,0:size//2]
        A12 = A[0:size//2   ,size//2:size]
        A21 = A[size//2:size,0:size//2]
        A22 = A[size//2:size,size//2:size]
        B11 = B[0:size//2   ,0:size//2]
        B12 = B[0:size//2   ,size//2:size]
        B21 = B[size//2:size,0:size//2]
        B22 = B[size//2:size,size//2:size]
        m1 = np.zeros((size//2, size//2))
        m2 = np.zeros((size//2, size//2))
        m3 = np.zeros((size//2, size//2))
        m4 = np.zeros((size//2, size//2))
        m5 = np.zeros((size//2, size//2))
        m6 = np.zeros((size//2, size//2))
        m7 = np.zeros((size//2, size//2))
        _strassensMatMulHelper((A11 + A22), (B11 + B22), size//2, m1)
        _strassensMatMulHelper((A21 + A22), B11        , size//2, m2)
        _strassensMatMulHelper(A11        , (B12 - B22), size//2, m3)
        _strassensMatMulHelper(A22        , (B21 - B11), size//2, m4)
        _strassensMatMulHelper((A11 + A12), B22        , size//2, m5)
        _strassensMatMulHelper((A21 - A11), (B11 + B12), size//2, m6)
        _strassensMatMulHelper((A12 - A22), (B21 + B22), size//2, m7)
        C11 = m1+m4-m5+m7
        C12 = m3+m5
        C21 = m2+m4
        C22 = m1-m2+m3+m6
        for i in range(size//2):
            for j in range(size//2):
                C[i][j]                 = C11[i][j]
                C[i][j+size//2]         = C12[i][j]
                C[i+size//2][j]         = C21[i][j]
                C[i+size//2][j+size//2] = C22[i][j]
    return C


C1= matMul(A, B)
print("\nC1:")
printMat(C1, len(str(MatrixSize*81)))
print('')
C2= strassensMatMul(A, B)
print("\nC2:")
printMat(C2, len(str(MatrixSize*81)))

'''
RESULTS==============================

MatrixSize=2**1
Normal method   : Unnoticable
Strassens method: Unnoticable
MatrixSize=2**2
Normal method   : Unnoticable
Strassens method: Unnoticable
MatrixSize=2**3
Normal method   : Unnoticable
Strassens method: Unnoticable
MatrixSize=2**4
Normal method   : Unnoticable
Strassens method: ~5000µs
MatrixSize=2**5
Normal method   : ~32000µs
Strassens method: ~35000µs
MatrixSize=2**6
Normal method   : ~2735ms
Strassens method: ~2781ms
MatrixSize=2**7
Normal method   : ~21013ms
Strassens method: ~20272ms
MatrixSize=2**8
Normal method   : ~169685ms
Strassens method: ~138124ms
'''