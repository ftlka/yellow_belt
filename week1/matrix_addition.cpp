#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Matrix {
public:
    Matrix() {
        vector<vector<int>> m;
        matrix = m;
        rows = 0;
        cols = 0;
    };
    Matrix(int num_rows, int num_cols) {
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("out of range");
        }
        vector<int> row = vector<int>(num_cols, 0);
        matrix = vector<vector<int>>(num_rows, row);
        rows = num_rows;
        cols = num_cols;
    };
    void Reset(int num_rows, int num_cols) {
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("out of range");
        }
        vector<int> row = vector<int>(num_cols, 0);
        matrix = vector<vector<int>>(num_rows, row);
        rows = num_rows;
        cols = num_cols;
    };
    int At(int row, int col) const {
        if (row >= rows || col >= cols ||
            row < 0 || col < 0) {
            throw out_of_range("out of range");
        }
        return matrix[row][col];
    };
    int& At(int row, int col) {
        if (row >= rows || col >= cols ||
            row < 0 || col < 0) {
            throw out_of_range("out of range");
        }
        return matrix[row][col];
    };
    int GetNumRows() const {
        return rows;
    };
    int GetNumColumns() const {
        return cols;
    };
private:
    vector<vector<int>> matrix;
    int rows;
    int cols;
};


istream& operator>>(istream& stream, Matrix& m) {
    int rows;
    int cols;
    stream >> rows;
    stream >> cols;
    m.Reset(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            stream >> m.At(i, j);
        }
    }
    return stream;
};


ostream& operator<<(ostream& stream, const Matrix& m) {
    int rows = m.GetNumRows();
    int cols = m.GetNumColumns();
    stream << rows << " " << cols << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            stream << m.At(i, j) << " ";
        }
        stream << endl;
    }
    return stream;
};


bool operator==(const Matrix& a, const Matrix& b) {
    if ((a.GetNumColumns() == 0 || a.GetNumRows() == 0) &&
        (b.GetNumColumns() == 0 || b.GetNumRows() == 0)) {
        return true;
    }
    if (a.GetNumColumns() != b.GetNumColumns() ||
        a.GetNumRows() != b.GetNumRows()) {
        return false;
    }
    for (int i = 0; i < a.GetNumRows(); i++) {
        for (int j = 0; j < a.GetNumColumns(); j++) {
            if (a.At(i, j) != b.At(i, j)) {
                return false;
            }
        }
    }
    return true;
};


Matrix operator+(const Matrix& a, const Matrix& b) {
    if ((a.GetNumColumns() == 0 || a.GetNumRows() == 0) &&
        (b.GetNumColumns() == 0 || b.GetNumRows() == 0)) {
        return Matrix();
    }
    if (a.GetNumColumns() != b.GetNumColumns() ||
        a.GetNumRows() != b.GetNumRows()) {
        throw invalid_argument("not equal dimensions");
    }
    Matrix sum = Matrix(a.GetNumRows(), a.GetNumColumns());
    for (int i = 0; i < a.GetNumRows(); i++) {
        for (int j = 0; j < a.GetNumColumns(); j++) {
            sum.At(i, j) = a.At(i, j) + b.At(i, j);
        }
    }
    return sum;
}



int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
	return 0;
}
