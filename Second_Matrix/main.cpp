#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <exception>
using namespace std;

class Matrix{
public:
    Matrix(){
        num_rows=0;
        num_cols=0;
    }
    Matrix(int Num_rows,int Num_cols){
        Reset(Num_rows,Num_cols);
    }
    void Reset(int Num_rows,int Num_cols){
        if(Num_rows<0 || Num_cols<0)
            throw out_of_range("Negative value");
        num_rows=Num_rows;
        num_cols=Num_cols;
        matrix.assign(num_rows, vector<int>(Num_cols));
    }
    int At(const int first,const int second)const {
        if(first<0 || second<0)
            throw out_of_range("Negative value");
        return matrix.at(first).at(second);
    }
    int& At(const int first,const int second){
        if(first<0 || second<0)
            throw out_of_range("Negative value");
        return matrix.at(first).at(second);
    }
    int GetNumRows() const {
        return num_rows;
    }
    int GetNumColumns() const {
        return num_cols;
    }
    vector<vector<int >> matrix;
private:
    int num_rows;
    int num_cols;

};
istream& operator>>(istream& is,Matrix& mx){
    int tmp_rows=0,tmp_columns=0;
    is>>tmp_rows>>tmp_columns;
    mx.Reset(tmp_rows,tmp_columns);
    for (int i = 0; i <tmp_rows ; ++i) {
        for (int j = 0; j <tmp_columns ; ++j) {
            is>>mx.At(i,j);
        }
    }
    return is;
}
ostream& operator<< (ostream& os,const Matrix& mx) {
    os << mx.GetNumRows() << " " << mx.GetNumColumns() << '\n';
    for (int i = 0; i < mx.GetNumRows(); ++i) {
        for (int j = 0; j < mx.GetNumColumns(); ++j) {
            if (j!=mx.GetNumColumns()-1)
            os << mx.At(i, j)<<" ";
            else{
                os << mx.At(i, j);
            }
        }
        os << '\n';
    }
    return os;
}
bool operator==(const Matrix& lhs,const Matrix& rhs){
    if((lhs.GetNumColumns()==rhs.GetNumColumns()) && (lhs.GetNumRows()==rhs.GetNumRows())){
        for (int i = 0; i <lhs.GetNumRows(); ++i) {
            for (int j = 0; j <lhs.GetNumColumns(); ++j) {
                if(lhs.At(i,j)!=rhs.At(i,j))
                    return false;
            }
        }
        return true;
    }else{
        return false;
    }
}
Matrix operator+(const Matrix& lhs,const Matrix& rhs){
    if((lhs.GetNumColumns()==rhs.GetNumColumns()) && (lhs.GetNumRows()==rhs.GetNumRows())){
        Matrix mx(lhs.GetNumRows(),lhs.GetNumColumns());
        for (int i = 0; i <lhs.GetNumRows(); ++i) {
            for (int j = 0; j <lhs.GetNumColumns() ; ++j) {
                mx.At(i,j)=lhs.At(i,j)+rhs.At(i,j);
            }
        }
        return mx;
    }
    else{
        throw invalid_argument("Different ranges ");
    }

}

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

int main() {

    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}
