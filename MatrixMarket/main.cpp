//
//  main.cpp
//  MatrixMarket
//
//  Created by Dos Zh on 18.10.2022.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

class Matrix {
private:
    int **array;
    int rows;
    int cols;
public:
    Matrix(const int, const int);
    Matrix& operator=(const int &right);
    
    int* operator [] (const int i) {
        if( (i<0) || (i >= rows) ) {
             cout<<endl<<"Error: Array out of bound";
             exit(1);
        }
        return array[i];
    }
    
    int numberOfColumns() {
        return cols;
    }

    int numberOfRows() {
        return rows;
    }
};

Matrix:: Matrix(const int rows, const int cols) {
    array = new int *[rows];
    this->rows = rows;
    this->cols = cols;
    for(int i = 0; i < rows; i++) {
        array[i] = new int[cols];
    }
}

Matrix& Matrix::operator=(const int &right)
{
    for (int i=0; i<rows; i++) {
      for (int j=0; j<cols; i++)
          this->array[i][j] = right;
    }
return *this;
}

int takeUserInput(string consoleText) {
    int var;
    cout << consoleText << endl;
    cin >> var;
    return var;
}

void populateMatrix(Matrix &matrix, int num_rows, int num_cols) {
    for(int row = 0; row < num_rows; row++) {
        for(int col = 0; col < num_cols; col++) {
            cout << "value for matrix" << row << col << endl;
            cin >> matrix[row][col];
        }
    }
}

    
void multiplyMatrices(Matrix &res_matrix, Matrix &matrix1, Matrix &matrix2) {
    int num_rows = matrix1.numberOfRows();
    int num_cols = matrix2.numberOfColumns();
#pragma omp parallel
#pragma omp for
    for(int row1 = 0; row1 < num_rows; row1++) {
        for(int col2 = 0; col2 < num_cols; col2++) {
            for(int col1 = 0; col1 < num_cols; col1++) {
                int num1 = matrix1[row1][col1];
                int num2 = matrix2[col1][col2];
                res_matrix[row1][col2] = num1 * num2;
            }
        }
    }
}

void printMatrix(Matrix &matrix) {
    int num_rows = matrix.numberOfRows();
    int num_cols = matrix.numberOfColumns();
    for(int row = 0; row < num_rows; row++) {
        for(int col = 0; col < num_cols; col++) {
            cout <<  matrix[row][col] << " ";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    cout << "Let's create a 1st matrix" << endl;
    
    int num_rows1 = takeUserInput("How many rows in matrix?");
    int num_cols1 = takeUserInput("And number of columns?");
    Matrix *matrix1 = new Matrix(num_rows1,num_cols1);
    populateMatrix(*matrix1, num_rows1, num_cols1);
    
    cout << "and the 2nd matrix" << endl;
    
    int num_rows2 = takeUserInput("How many rows in matrix?");
    int num_cols2 = takeUserInput("And number of columns?");
    Matrix *matrix2 = new Matrix(num_rows2,num_cols2);
    populateMatrix(*matrix2, num_rows2, num_cols2);
    
    Matrix *res_matrix = new Matrix(num_rows1,num_cols2);
    
    if(num_cols1 == num_rows2) {
        multiplyMatrices(*res_matrix, *matrix1, *matrix2);
        
        cout << "result of the matrixByMatix product is " << endl;
        cout << "[" << endl;
        printMatrix(*res_matrix);
        cout << "]" << endl;
    } else {
        cout << "Error, cannot proceed because the number of rows and columns are not equal" << endl;
    }
    return 0;
}

