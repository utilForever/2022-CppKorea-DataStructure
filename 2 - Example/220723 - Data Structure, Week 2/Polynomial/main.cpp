#include <iostream>

class Polynomial;

class Term
{
 public:
    friend Polynomial;

 private:
    float coef;
    int exp;
};

class Polynomial
{
 public:
    // Create polynomial p(x) = 0
    Polynomial();

    // Add polynomial *this and b
    Polynomial Add(const Polynomial& b) const;

    // Multiply polynomial *this and b
    Polynomial Multiply(const Polynomial& b) const;

    // After assign f into x, evaluate polynomial and return result
    float Eval(const float& f);

    // Add new term into last element of termArray
    void NewTerm(const float& coef, const int& exp);

    // Print polynomial
    void Output() const;

 private:
    Term* termArray;
    int capacity;
    int terms;
};

Polynomial::Polynomial() : termArray(new Term[1]), capacity(1), terms(0)
{
    // Do nothing
}

Polynomial Polynomial::Add(const Polynomial& b) const
{
    Polynomial c;
    int aPos = 0, bPos = 0;

    while (aPos < terms && bPos < b.terms)
    {
        if (termArray[aPos].exp == b.termArray[bPos].exp)
        {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;

            if (t != 0.0f)
            {
                c.NewTerm(t, termArray[aPos].exp);
            }

            aPos++;
            bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp)
        {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else
        {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }

    // Add rest terms of *this
    while (aPos < terms)
    {
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        aPos++;
    }

    // Add rest terms of b(x)
    while (bPos < b.terms)
    {
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
        bPos++;
    }

    return c;
}

Polynomial Polynomial::Multiply(const Polynomial& b) const
{
    // TODO: Implement this function by assignment
    return Polynomial{};
}

float Polynomial::Eval(const float& f)
{
    // TODO: Implement this function by assignment
    return 0.0f;
}

void Polynomial::NewTerm(const float& coef, const int& exp)
{
    if (terms == capacity)
    {
        // Expand the size of termArray twice
        capacity *= 2;

        Term* temp = new Term[capacity];
        std::copy_n(termArray, terms, temp);
        delete[] termArray;
        termArray = temp;
    }

    termArray[terms].coef = coef;
    termArray[terms].exp = exp;

    terms++;
}

void Polynomial::Output() const
{
    std::cout << "\t"
              << "Coef"
              << "\t"
              << "Exp" << '\n';

    for (int i = 0; i < terms; ++i)
    {
        std::cout << "\t" << termArray[i].coef << "\t" << termArray[i].exp
                  << '\n';
    }
}

int main()
{
    Polynomial a;
    a.NewTerm(3.0f, 3);
    a.NewTerm(2.0f, 2);
    a.NewTerm(-4.0f, 1);

    Polynomial b;
    b.NewTerm(1.0f, 8);
    b.NewTerm(-10.0f, 5);
    b.NewTerm(-3.0f, 3);
    b.NewTerm(1.0f, 0);

    const Polynomial c = a.Add(b);
    c.Output();
}
