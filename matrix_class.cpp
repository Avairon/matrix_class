#include <iostream>

using std::cout;
using std::cin;

class matrix{
private:
    int rows; int cols;
    double** arr;

    matrix getMinor(matrix& matrix_, int rows, int cols){
        int n = matrix_.rows;

        matrix out_minor = *new matrix(n - 1, n - 1);

        /*
        double** out_minor.arr = new double*[n - 1];
        for (int i = 0; i < n - 1; i++){
            out_minor.arr[i] = new double[n - 1];
        }*/

        if(n == 1) return matrix_;

        for(int i = 0, p = 0; i < n; i++){
            if(i == rows) continue;
            for(int j = 0, q = 0; j < n; j++){
                if(j == cols) continue;
                out_minor.arr[p][q] = matrix_.arr[i][j];
                q++;
            }
            p++;
        }
        //cout << "minor\n";
        return out_minor;
    }

    double determinant(matrix& matrix_){
        int n = matrix_.rows;
        int b = matrix_.cols;

        int det = 0;

        if(n != b){
            cout << "Not square! n = " << n << " b = " << b << "\n";
            return 0;
        } 

        if(n == 0){
            return 0;
        }
        else if(n == 1){
            //cout << "deter\n";
            return matrix_.arr[0][0];
        }
        else if(n == 2){
            //cout << "deter\n";
            return (matrix_.arr[0][0] * matrix_.arr[1][1]) - (matrix_.arr[0][1] * matrix_.arr[1][0]); //косяк тут
        }
        else{
            for(int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    matrix minor = *new matrix;
                    minor = getMinor(matrix_, i, j);
                    int sign = j % 2 ? 1 : -1;
                    det += sign * matrix_.arr[i][j] * determinant(minor);
                //cout << sign << ":s " << matrix_[i][j] << ":m " << determinant(minor) << ":d" << det << ":det\n";
                }
            }
            
            //cout << "deter\n";
            //cout << det << ":det" << "\n";
            return det;
        }
    }

    matrix getAlgAppend(matrix& mat_){// передача обьекта вместо массива
        int n = mat_.rows;
        
        matrix cofactors = *new matrix(n, n);
        cofactors.arr = new double*[n];

        for (int i = 0; i < n; i++){
            cofactors.arr[i] = new double[n - 1];
        }

        


        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                matrix minors = *new matrix; 
                minors = getMinor(mat_, i, j);
                int sign = (i + j) % 2 == 0 ? 1: -1;
                cofactors.arr[j][i] = double(sign * determinant(minors));
            }
        }
        //cout << "alg\n";
        return cofactors;
    }

public:
    matrix(){} //создание
    matrix(int Rows, int Cols){ //конструктор с кол-вом строк и столбцов
        rows = Rows;
        cols = Cols; 
        arr = new double*[Rows];

        for (int i = 0; i < Rows; i++){
            arr[i] = new double[Cols];
        }
    }
    matrix(matrix& other)//копирование
    {
        rows = other.rows;
        cols = other.cols;
        arr = other.arr;
    }
    ~matrix(){
        /*
        for(int a = 0; a < rows; a++){
            delete[] arr[a];
        }
        delete[] arr;
        */
    };


    matrix operator + (const matrix &mat_){

        double** arr_ = arr;

        if(rows != mat_.rows or cols != mat_.cols){
            throw("Error: Cannot sum it because matrix have different sizes!");
        }

        matrix out = *new matrix;
        out.changeMatrix(arr_, mat_.rows, mat_.cols);

        out.SumMatrix(mat_);

        return out;
    }

    matrix operator - (const matrix &mat_){
        double** arr_ = arr;

        if(rows != mat_.rows or cols != mat_.cols){
            throw("Error: Cannot sub it because matrix have different sizes!");
        }

        matrix out = *new matrix;
        out.changeMatrix(arr_, rows, cols);

        out.SubMatrix(mat_);

        return out;
    }

    bool operator == (const matrix &other){
        return this->EqMatrix(other);
    }

    void operator = (const matrix &other){
        rows = other.rows;
        cols = other.cols;
        arr = other.arr;
    }

    void operator += (const matrix &other){
        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot sum it because matrix have different sizes!");
        }

        this->SumMatrix(other);
    }
    void operator -= (const matrix &other){
        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot sub it because matrix have different sizes!");
        }

        this->SubMatrix(other);
    }
    void operator *= (int count){
        this->MulNumber(count);
    }
    void operator *= (const matrix &other){
        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot mul it because matrix have different sizes!");
        }

        this->MulMatrix(other);
    }

    //+ - *int *arr == = += -= *= 

    matrix operator * (int count){
        double** arr_ = arr;
        matrix out = *new matrix;
        out.changeMatrix(arr_, rows, cols);

        out.MulNumber(count);
        
        return out;
    }
    matrix operator * (const matrix &mat_){
        double** arr_ = arr;

        if(rows != mat_.rows or cols != mat_.cols){
            throw("Error: Cannot exp it because matrix have different sizes!");
        }

        matrix out = *new matrix;
        out.changeMatrix(arr_, rows, cols);

        out.MulMatrix(mat_);

        return out;
    }

    void changeMatrix(double** arr_, int Rows, int Cols){
        cols = Cols;
        //cout << "colCre\n";
        rows = Rows;
        //cout << "rowCre\n";
        arr = arr_;
        //cout << "arrCre\n";
    }

    void setRows(int Rows){
        rows = Rows;
    }
    void setCols(int Cols){
        cols = Cols;
    }
    void setArr(double** arr_){
        arr = arr_;
    }
    int getRows(){
        return rows;
    }
    int getCols(){
        return cols;
    }
    double** getArr(){
        return arr;
    }
    void printMatrix(){
        cout << "rows: " << rows << "\n";
        cout << "cols: " << cols << "\n";

        for(int a = 0; a < rows; a++){
            for(int b = 0; b < cols; b++){
                cout << arr[a][b] << " ";
            }
            cout << "\n";
        }
    }

    bool EqMatrix(const matrix& other){
        if(rows == other.rows and cols == other.cols and arr == other.arr){
            return true;
        }
        return false;
    }

    matrix SumMatrix(const matrix& other){
        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot sum it because matrix have different sizes!");
        }

        for(int a = 0; a < cols; a++){
            for(int b = 0; b < rows; b++){
                arr[a][b] += other.arr[a][b];
            }
        }

        matrix out = *new matrix;
        out.changeMatrix(arr, rows, cols);
        return out;
    }

    matrix SubMatrix(const matrix& other){

        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot sub it"); 
        }

        for(int a = 0; a < cols; a++){
            for(int b = 0; b < rows; b++){
                arr[a][b] -= other.arr[a][b];
            }
        }
        matrix out = *new matrix;
        out.changeMatrix(arr, rows, cols);
        return out;
    }

    matrix MulNumber(const double num){
        for(int a = 0; a < cols; a++){
            for(int b = 0; b < rows; b++){
                arr[a][b] *= num;
            }
        }
        matrix out = *new matrix;
        out.changeMatrix(arr, rows, cols);
        return out;
    }

    matrix MulMatrix(const matrix& other){
        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot exp it because matrix have different sizes!");
        }

        for(int a = 0; a < cols; a++){
            for(int b = 0; b < rows; b++){
                arr[a][b] *= other.arr[a][b];
            }
        }

        matrix out = *new matrix;
        out.changeMatrix(arr, rows, cols);
        return out;
    }

    matrix Transpose(){
        matrix out = *new matrix(cols, rows);

        double** arrT = new double*[rows];
        for (int i = 0; i < rows; i++){
            arrT[i] = new double[cols];
        }

        out.arr = arrT;

        for(int a = 0; a < rows; a++){
            for(int b = 0; b < cols; b++){
                out.arr[b][a] = arr[a][b];
            }
        }
        out.cols = rows;
        out.rows = cols;

        return out;
    }

    /*
        1 2 3
        4 5 6
        7 8 9
        эл 6
        1 2
        7 8
    */
    
    
    matrix CalcComplements(){
        if(cols != rows) throw("Error: Matrix is not square");
        matrix in = *new matrix;
        in.arr = this->arr;
        in.rows = this->rows;
        in.cols = this->cols;

        matrix out = *new matrix(rows, cols);
        //cout << "_1\n";
        out = getAlgAppend(in);
        //cout << "_2\n";

        return out;  
    }
};


int main(){
    matrix matTest = *new matrix();
    
    int a, b;
    a = 3; b = 3;

    double** matTestArr = new double*[a];
    for (int i = 0; i < a; i++){
        matTestArr[i] = new double[b];
    }

    int counter = 1;
    for(int y = 0; y < a; y++){
        for(int x = 0; x < b; x++){
            matTestArr[y][x] = counter;
            counter++;
        }
    }

    matTest.changeMatrix(matTestArr, a, b);
    matTest.printMatrix();
    matTest.CalcComplements().printMatrix();
}
