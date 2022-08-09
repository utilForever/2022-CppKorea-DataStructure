#include <iostream>

class String
{
 public:
    // Constructor with content *c, length n
    String(char* c, int n);

    // Return true if *this's string is equal to t's.
    // Otherwise, return false.
    bool operator==(String t) const;

    // Return true if *this's string is empty.
    // Otherwise, return false;
    bool operator!() const;

    // Return the number of *this's characters
    int Length() const;

    // Return *this's string + t's
    String Concat(String t);

    // Return substring with index (i, i+1, ..., i+j-1) of *this's string
    String Substr(int i, int j);

    // Return index i if *this's substring matches pat's string
    // Return -1 if pat is empty or not *this's substring
    int Find(String pat) const;

    // Fast version of Find()
    int FastFind(String pat) const;

 private:
    // Failure function for KMP algorithm
    void Fail();

    char* str;
    int length;
    int f[100]{};
};

String::String(char* c, int n) : str(c), length(n)
{
    std::fill_n(f, 100, -1);
}

bool String::operator==(String t) const
{
    if (length != t.length)
    {
        return false;
    }

    for (int i = 0; i < length; ++i)
    {
        if (str[i] != t.str[i])
        {
            return false;
        }
    }

    return true;
}

bool String::operator!() const
{
    return length == 0;
}

int String::Length() const
{
    return length;
}

String String::Concat(String t)
{
    // TODO: Implement this function by assignment
    return String{ nullptr, 0 };
}

String String::Substr(int i, int j)
{
    // TODO: Implement this function by assignment
    return String{ nullptr, 0 };
}

int String::Find(String pat) const
{
    for (int start = 0; start <= length - pat.length; ++start)
    {
        // Check pattern match at str[start]
        int j;

        for (j = 0; j < pat.length && str[start + j] == pat.str[j]; ++j)
        {
            // Do nothing
        }

        // Found match
        if (j == pat.length)
        {
            return start;
        }
    }

    // pat is empty or not exist in *this
    return -1;
}

int String::FastFind(String pat) const
{
    pat.Fail();

    int posP = 0, posS = 0;
    const int lengthP = pat.length;
    const int lengthS = length;

    while (posP < lengthP && posS < lengthS)
    {
        // String match
        if (pat.str[posP] == str[posS])
        {
            posP++;
            posS++;
        }
        else
        {
            if (posP == 0)
            {
                posS++;
            }
            else
            {
                posP = pat.f[posP - 1] + 1;
            }
        }
    }

    if (posP < lengthP)
    {
        return -1;
    }

    return posS - lengthP;
}

void String::Fail()
{
    const int lengthP = length;

    f[0] = -1;

    for (int j = 1; j < lengthP; ++j)
    {
        int i = f[j - 1];

        while (*(str + j) != *(str + i + 1) && i >= 0)
        {
            i = f[i];
        }

        if (*(str + j) == *(str + i + 1))
        {
            f[j] = i + 1;
        }
        else
        {
            f[j] = -1;
        }
    }
}

int main()
{
    const String s("abcabcdefg", 10);

    const String pat1("cde", 3);
    std::cout << s.FastFind(pat1) << '\n';

    const String pat2("abc", 3);
    std::cout << s.FastFind(pat2) << '\n';

    const String pat3("abcabcacab", 10);
    std::cout << s.FastFind(pat3) << '\n';
}
