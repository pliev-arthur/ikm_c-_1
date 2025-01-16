#include <iostream>
#include <vector>
#include <string>

using namespace std;

// the function of dividing a string into substrings of 9 digits
// and entering them into a vector as numbers (from the end)
void massiv(vector <long int> &a, string s, int len, int part)
{
    string sub;
    // j - the number of the element in the array, k is the number of the substring
    // i - the position of the first character in the substring
    int k = 1, i = len - 9, j = 0;
    while (k <= part)
    {
        // select a substring of 9 digits, moving from the end
        // if the last substring contains less than 9 characters, then
        // we take all the remaining characters from the 0th character
        sub = i >= 0 ? s.substr(i, 9) : s.substr(0, 9 + i);
        a[j] = atoi(sub.c_str()); // conversion to a number
        j++; k++;
        i -= 9;
    }
}
// converting to a string and removing the leading zeros.
string to_str(long int m)
{
    string s = to_string(m);
    if (s == "0")
        s = "";
    return s;
}
// the function of the sum of 2 lines
string sum(string s1, string s2)
{
    int len1 = s1.length();
    int len2 = s2.length();
    // adding zeros on the left to the smaller substring
    if (len1 < len2)
        {
            s1.insert(0, len2 - len1, '0');
        }
        else
            if (len1 > len2)
                s2.insert(0, len1 - len2, '0');
    int len = s1.length(); // the total length of the string
    // dividing the string into parts of 9 characters each
    int part = len % 9 == 0 ? len / 9 : len / 9 + 1;
    // we allocate memory, including an additional bit on the left
    vector <long int> a(part + 1,0);
    vector <long int> b(part + 1,0);

    // calling the function for entering strings into vectors
    massiv(a, s1, len, part);
    massiv(b, s2, len, part);
    int ost1, ost2 = 0;
    for (int i = 0; i <= part; i++)
    {
        ost1 = (a[i] + b[i]) / 1000000000; // transfer
        a[i] = (a[i] + b[i]) % 1000000000 + ost2; // the sum of the numbers
        ost2 = ost1; // the remainder is for the next step
    }
    string result = "";
    for (int i = part; i >= 0; i--)
        result.append(to_str(a[i]));
    return result;
}
// the function of the multiplication of 2 lines
string multiply(string s1, string s2)
{
    string result;
    int len;
    // calculating the maximum length of the final string
    if (s1.length() >= s2.length())
    {
        result.insert(0, s1.length() * 2, '0');
        len = s1.length() * 2 - 1;
    }
    else
    {
        result.insert(0, s2.length() * 2, '0');
        len = s2.length() * 2 - 1;
    }
    // 2 remainders as in the sum function
    int ost1 = 0; int ost2 = 0;
    // s1_str and s2_str are elements of lines s1 and s2
    // r_str is an element of the final line for writing the product s1_str and s2_str
    string s1_str, s2_str, r_str;

    int r_int, s1_int, s2_int; // s1_str, s2_str and r_str, but as int

    for (int i = s1.length() - 1; i >= 0; i--)
    {
        int k = len; // the current index of the result
        for (int j = s2.length() - 1; j >= 0; j--)
        {
            r_str = result[k]; s1_str = s1[i]; s2_str = s2[j];
            // converting to int
            r_int = atoi(r_str.c_str()); s1_int = atoi(s1_str.c_str()); s2_int = atoi(s2_str.c_str());
            ost1 = (r_int + (s1_int * s2_int) + ost2) / 10;
            r_int = (r_int + (s1_int * s2_int) + ost2) % 10;
            ost2 = ost1; // the remainder is for the next step
            result[k] = char(48 + r_int); // converting to string and writing in result
            k--;
        }
        result[k] += ost1; // adding the remainder after exiting the loop
        ost1 = 0;
        ost2 = 0;
        len--;
    }
    result.erase(0, result.find_first_not_of('0')); // removing leading zeros
    return result;
}
// checking for a non-negative integer and entering a new one
void check (string &s, int param) // if param == 0 - specially for n
{
    string result = s;
    if (result.size() > 1 && result[0] == '0') // checking if integer starting with "0"
        result.erase(0, 1); // deleting "0"
    bool flag1 = false, flag2;
    while (flag1 == false)
    {
        if (result == "0" && param == 0) // if n == 0
        {
            cout << "n не может быть равно 0: ";
            cin >> result;
            continue;
        }
        if (result.size() > 9 && param == 0) // if length of n > 9
        {
            cout << "извините, но n не может содержать больше 9 разрядов: ";
            cin >> result;
            continue;
        }
        flag2 = true;
        int i = 0;
        while ((flag2 == true) && (i < result.size()))
        {
            // checking that there are only characters from "0" to "9" in the string
            if (result[i] < '0' || result[i] > '9')
                flag2 = false;
            i++;
        }
        if (flag2 == false)
        {
            cout << "Пожалуйста, введите целое неотрицательное число: ";
            cin >> result;
        }
        else
            flag1 = true;
    }
    s = result;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    long int n;
    bool flag1 = true, flag2;
    // x0 = x ^ (n - 1) - previous value x
    string x, x0, a, n_str, summa;
    while (flag1 == true)
    {
        flag2 = true;
        // we enter n and x and do the first 2 passes of the cycle
        // starting from a0
        cout << "Вычисление точного значения многочлена вида a_n * x^n + a_(n-1) * x^(n-1) + ... + a_1 * x + a_0 " << endl;
        cout << "Введите n (целое неотрицательное число и не 0): ";
        cin >> n_str;
        check(n_str, 0);
        n = stoi(n_str);
        cout << "Введите x(целое неотрицательное число): ";
        cin >> x;
        check(x, 1);
        x0 = x;
        cout << "Введите a_0(целое неотрицательное число) (осталось " << n << "):";
        cin >> a;
        check(a, 1);
        summa = a;
        cout << "Введите a_1(целое неотрицательное число) (осталось " << n - 1 << "):";
        cin >> a;
        check(a, 1);
        summa = sum(summa, multiply(a, x));
        for (int i = 2; i < n; i++)
        {
            cout << "Введите a_" << i << "(целое неотрицательное число) (осталось " << n - i << "):";
            cin >> a;
            check(a, 1);
            // calculating x^(n)
            x0 = multiply(x0, x);
            summa = sum(summa, multiply(a, x0));
        }
        cout << "Ваш ответ: " << summa << endl;
        // asking for another one
        cout << "Вы желаете вычислить еще один многочлен? (1 - да, 0 - нет): ";
        string c1;
        while (flag2 == true)
        {
            cin >> c1;
            if (c1 == "1" || c1 == "0")
                flag2 = false;
            else
                cout << "Пожалуйста, введите 1 или 0: ";
        }
        if (c1 == "1")
            continue;
        else
            break;
    }
}
