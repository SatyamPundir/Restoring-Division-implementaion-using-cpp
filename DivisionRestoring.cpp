#include <iostream>
using namespace std;

string toBinary(int n)
{
    int temp[32];

    int i = 0;
    while (n > 0)
    {
        temp[i] = n % 2;
        n = n / 2;
        i++;
    }
    string bin;
    for (int j = i - 1; j >= 0; j--)
    {
        bin += to_string(temp[j]);
    }

    return bin;
}

string add(string n1, string n2)
{
    int l1 = n1.length();
    int l2 = n2.length();
    int i;
    int n;
    int least;
    string res;
    n = max(l1, l2) + 1;

    int carry[n] = {0};

    for (int i = 1; i <= min(l1, l2); i++)
    {
        if (n1[l1 - i] == '1' && n2[l2 - i] == '1')
        {
            if (carry[n - i] == 1)
            {
                res = '1' + res;
                carry[n - i - 1] = 1;
            }
            else
            {
                res = '0' + res;
                carry[n - i - 1] = 1;
            }
        }
        else if (n1[l1 - i] == '0' && n2[l2 - i] == '0')
        {
            if (carry[n - i] == 1)
            {
                res = '1' + res;
                carry[n - i - 1] = 0;
            }
            else
            {
                res = '0' + res;
                carry[n - i - 1] = 0;
            }
        }
        else
        {
            if (carry[n - i] == 1)
            {
                res = '0' + res;
                carry[n - i - 1] = 1;
            }
            else
            {
                res = '1' + res;
                carry[n - i - 1] = 0;
            }
        }
    }

    string temp;
    if (l1 - l2 > 0)
    {
        if (l1 > l2)
            temp = n1;
        else
            temp = n2;
        for (int i = max(l1, l2) - min(l1, l2) - 1; i >= 0; i--)
        {
            if (carry[i + 1] == 0)
            {
                res = temp[i] + res;
                carry[i] = 0;
            }
            else
            {
                if (temp[i] == '0')
                {
                    res = '1' + res;
                    carry[i] = 0;
                }
                else
                {
                    res = '0' + res;
                    carry[i] = 1;
                }
            }
        }
    }
    else
    {
        if (carry[0] = 1)
        {
            res = '1' + res;
        }
        else
        {
            res = '1' + res;
        }
    }
    string temp1;
    if (res.length() > max(l1,l2))
    {
        for (int i =1; i<res.length(); i++)
        {
            temp1 =  temp1 + res[i];
        }
        return temp1;
    }

    return res;
}

string twosComp(string n)
{
    string res;
    for (int i = 0; i < n.length(); i++)
    {
        if (n[i] == '1')
        {
            res += '0';
        }
        else
        {
            res += '1';
        }
    }
    res = add(res, "1");
    return res;
}

string sub(string n1, string n2)
{
    string res;
    string temp;
    temp = twosComp(n2);
    res = add(n1, temp);
    return res;
}

string shiftL(string n1)
{
    string res;
    for (int i = 1; i < (n1.length()); i++)
    {
        res = res + n1[i];
    }
    return res;
}

string DivRestoring(int n1, int n2)
{
    string q = toBinary(n1); // it is n bit
    string m = toBinary(n2); // will be n+1 bit
    string a;                // will be n+1 bit with all 0;
    int n = q.length();

    for (int i = m.length(); i < n + 1; i++)
    {
        m = "0" + m;
    }
    for (int i = 0; i < n + 1; i++)
    {
        a = "0" + a;
    }

    cout << "Q --->  " << q << endl;
    cout << "M --->  " << m << endl;
    cout << "A --->  " << a << endl;
    cout << "we will calculate this using Restoring method of Division Q/M" << endl;
    cout << "We will repeat the following process N-times:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"**************************************************************************************************"<<endl;;
        cout<<i+1<<"th Iteration "<<endl;
        //Step 1:-->
        cout<<"    Configuration:  "<<endl;
        cout<<"             M           |               A           |               Q           |"<<endl;
        cout<<"           "<<m<<"                       "<<a<<"                       "<<q<<endl;
        cout<<endl;
        a = shiftL(a);
        a = a + q[0];
        q = shiftL(q);
        cout<<"     Shift-left Q and A                "<<a<<"                       "<<q<<endl;
        cout<<endl;

        //Step 2:-->
        a = sub(a, m);
        cout<<"     Subtract M from A                 "<<a<<"                       "<<q<<endl;
        cout<<endl;
        
        if (a[0] == '1')
        {
            q = q+"0";   
            a = add(a, m);
            cout<<"     A0->1, set Q0->0                  "<<a<<"                       "<<q<<endl;
            cout<<"       and Restore A              "<<endl;
            cout<<endl;
        }
        else
        {
            q = q + "1";
            cout<<"     A0->0, set Q0->1                  "<<a<<"                       "<<q<<endl;
            cout<<endl;
        }
    }

    cout << "Remainder is A that is" + a << endl;
    cout << "Quotient is Q that is " + q << endl;
}

int main()
{

    DivRestoring(8, 3);
    return 0;
}