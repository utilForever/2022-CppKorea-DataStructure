#include <iostream>

class SparseMatrix;

class MatrixTerm
{
 public:
    friend SparseMatrix;

 private:
    int row, col, value;
};

class SparseMatrix
{
 public:
    // Create SparseMatrix with r rows, c columns, t terms (not 0)
    SparseMatrix(int r, int c, int t);

    // Transpose all elements of *this and return it
    SparseMatrix Transpose() const;

    // Fast version of Transpose()
    SparseMatrix FastTranspose() const;

    // Add *this and b and return result
    SparseMatrix Add(const SparseMatrix& b);

    // Subtract *this and b and return result
    SparseMatrix Subtract(const SparseMatrix& b);

    // Multiply *this and b and return result
    SparseMatrix Multiply(const SparseMatrix& b);

    // Add new term into last element of smArray
    void NewTerm(size_t idx, const int& r, const int& c, const int& val) const;

    // Print sparse matrix
    void Output() const;

 private:
    MatrixTerm* smArray;
    int rows, cols, terms;
};

SparseMatrix::SparseMatrix(int r, int c, int t)
    : smArray(new MatrixTerm[t]), rows(r), cols(c), terms(t)
{
    // Do nothing
}

SparseMatrix SparseMatrix::Transpose() const
{
    const SparseMatrix b(cols, rows, terms);

    if (terms > 0)
    {
        int currentB = 0;

        for (int c = 0; c < cols; ++c)
        {
            // Transpose each column
            for (int i = 0; i < terms; ++i)
            {
                // Find element from column c and move it
                if (smArray[i].col == c)
                {
                    b.smArray[currentB].row = c;
                    b.smArray[currentB].col = smArray[i].row;
                    b.smArray[currentB].value = smArray[i].value;

                    currentB++;
                }
            }
        }
    }

    return b;
}

SparseMatrix SparseMatrix::FastTranspose() const
{
    const SparseMatrix b(cols, rows, terms);

    if (terms > 0)
    {
        int* rowSize = new int[cols];
        int* rowStart = new int[cols];

        std::fill_n(rowSize, cols, 0);

        for (int i = 0; i < terms; ++i)
        {
            rowSize[smArray[i].col]++;
        }

        // Start point of row i of rowStart[i] = b
        rowStart[0] = 0;

        for (int i = 1; i < cols; ++i)
        {
            rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
        }

        // Copy *this to b
        for (int i = 0; i < terms; ++i)
        {
            const int j = rowStart[smArray[i].col];

            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;

            rowStart[smArray[i].col]++;
        }

        delete[] rowSize;
        delete[] rowStart;
    }

    return b;
}

SparseMatrix SparseMatrix::Add(const SparseMatrix& b)
{
    // TODO: Implement this function by assignment
    return SparseMatrix{ 0, 0, 0 };
}

SparseMatrix SparseMatrix::Subtract(const SparseMatrix& b)
{
    // TODO: Implement this function by assignment
    return SparseMatrix{ 0, 0, 0 };
}

SparseMatrix SparseMatrix::Multiply(const SparseMatrix& b)
{
    // TODO: Implement this function by assignment
    return SparseMatrix{ 0, 0, 0 };
}

void SparseMatrix::NewTerm(size_t idx, const int& r, const int& c,
                           const int& val) const
{
    smArray[idx].row = r;
    smArray[idx].col = c;
    smArray[idx].value = val;
}

void SparseMatrix::Output() const
{
    std::cout << "\trow"
              << "\tcol"
              << "\tvalue" << '\n';

    for (int i = 0; i < terms; ++i)
    {
        std::cout << "\t" << smArray[i].row << "\t" << smArray[i].col << "\t"
                  << smArray[i].value << '\n';
    }
}

int main()
{
    SparseMatrix m(6, 6, 8);
    m.NewTerm(0, 0, 0, 15);
    m.NewTerm(1, 0, 3, 22);
    m.NewTerm(2, 0, 5, -15);
    m.NewTerm(3, 1, 1, 11);
    m.NewTerm(4, 1, 2, 3);
    m.NewTerm(5, 2, 3, -6);
    m.NewTerm(6, 4, 0, 91);
    m.NewTerm(7, 5, 2, 28);

    const SparseMatrix transposedM = m.FastTranspose();
    transposedM.Output();
}
