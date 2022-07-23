#include <iostream>
#include <string>
using namespace std;
//#include<bits/stdc++.h> 
class Binary {
private:
    string binStr;
public:
    void setBinary(long long int n, int binSize) {
        binStr = binaryForm(n, binSize);
    }
    string getBinary() {
        return binStr;
    }
    Binary(string s) {
        binStr = s;
    }
    Binary() {};

     string binarySum(string a, string b, char place) {
        string result = "";
        b.insert(b.size(), place - 1, '0');
        int temp = 0;
        int size_a = a.size() - 1;
        int size_b = b.size() - 1;
        while (size_a >= 0 || size_b >= 0 || temp == 1) {
            temp += ((size_a >= 0) ? a[size_a] - '0' : 0);
            temp += ((size_b >= 0) ? b[size_b] - '0' : 0);
            result = char(temp % 2 + '0') + result;
            temp /= 2;
            size_a--; size_b--;
        }
        return result;
    }
    string translate(long long int n)
    {
        string r;
        while (n != 0) {
            r += (n % 2 == 0 ? "0" : "1");
            n /= 2;
        }
        reverse(r.begin(), r.end());
        r.insert(0, "0");
        return r;
    }
     string complement(Binary stri, int binSize) {
         string str = stri.getBinary();
        str = fill(str, binSize);
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '0') str[i] = '1';
            else if (str[i] == '1') str[i] = '0';
        }

        str= binarySum(str, "1", 1);
        if (str.size() > binSize) str.erase(0, 1);
        return str;
    }
    string binaryForm(long long int num, int binSize) {
        if (num < 0)
            return complement(translate(-num), binSize);
        else
            return fill(translate(num), binSize);
    }
     string fill(string str, int binSize) {
        while (str.size() < binSize)
        {
            str.insert(0, "0");
        }
        return str;
    }
     Binary checkSum(Binary a, Binary b, int binSize) {
         string first = a.getBinary();
         string second = b.getBinary();

            string sumResult = binarySum(first, second, 1);
            if (sumResult.size() == binSize && (sumResult[0] == '0' || ((sumResult[0] == '1') && (first[0] == '1' || second[0] == '1'))))
                return Binary(sumResult);

            else if ( (sumResult.size() == binSize+1)  &&  (   (first[0] =='1' && '1' == second[0] && '1' == sumResult[1]) || (first[0] != second[0])))
                return Binary(sumResult.erase(0, 1));


            else return Binary ("Invalid result! Out of range");
        }

     string toStraight(string s, int binSize) {
        string minusOne = "1";
        string res = checkSum(s, minusOne, binSize).getBinary();
        for (int i = 0; i < res.size(); i++) {
            if (res[i] == '1') res[1] = '0';
            else res[i] = '1';
        }
        return res;
    }
    Binary binaryMult(Binary astr, Binary bstr, int binSize) {
        int j = binSize;
        string ab = "";
        bool flag = 0;
        string a = astr.getBinary();
        string b = bstr.getBinary();

        if (a[0] != b[0]) flag = 1;

        string first = a;
        string second = b;

        if (a[0]=='1') first = complement(a, binSize);
        if (b[0] == '1') second = complement(b, binSize);

        for (int i = second.size()-1; i >= 0; i--) {
            if (second[i]=='1')
                ab = binarySum(ab, first, second.size() - i);
        }
        while ((ab[0] == '0') && (ab.size() > j)) {
            ab = ab.erase(0,1);
        }
        //cout << ab<<"  result" << endl;

        if (ab.size() > j || ab[0]=='1') return Binary ("Invalid result! Out of range");

        else if (flag == 1) {
            return Binary (complement(ab, binSize));
        }
        else if (flag==0)
            return Binary(ab);
    }

    Binary difference(Binary a, Binary b, int binSize) {

        return Binary(checkSum(a, complement(b, binSize), binSize));
    }

     int binaryToDecimal(Binary n, int binSize)
    {
        Binary num = n;
        int dec_value = 0;

        int base = 1;

        int len = num.getBinary().length();
        if (n.getBinary()[0] == '0') {
            for (int i = len - 1; i >= 0; i--) {
                if (num.getBinary()[i] == '1')
                    dec_value += base;
                base = base * 2;
            }
            return dec_value;
        }
        if (n.getBinary()[0] == '1') {
            num = Binary(complement(n.getBinary(), binSize));
            for (int i = len - 1; i >= 0; i--) {
                if (num.getBinary()[i] == '1')
                    dec_value += base;
                base = base * 2;
            }
            return -dec_value;
        }

        
    }
    
};

bool isInteger(string str) {
    for (int i = 1; i < str.length(); i++)
        if (!(isdigit(str[i]) && ((str[0] == '-') || (isdigit(str[0])))))
            return false;
    return true;
}

    int input() {
    cout << "Enter the number" << endl;
    string name;
    do {
        getline(cin, name);
        if (!isInteger(name))
            cout << "Invalid! Enter the number again" << endl;
    } while (!isInteger(name));
    int i = stoi(name);
    return i;
}

int main() {
    cout << "Hello World!\n" << endl;
    Binary binary, binary1;
    long long int a, b;
    string sign;
    a = input();
    b = input();
    int binSize = 8;

    
    cout << endl;

    binary.setBinary(a, binSize);
    binary1.setBinary(b, binSize);

    cout << "first number in binary:    " << binary.getBinary()<<endl;
    cout << "second number in binary:    " << binary1.getBinary() << endl;
    cout << endl;

    cout << "sum in binary:   "<<binary.checkSum(binary, binary1, binSize).getBinary() << endl;
    cout << "sum in decimal:   "<<binary.binaryToDecimal(binary.checkSum(binary, binary1, binSize), binSize) << endl;
    cout << endl;

    cout << "differ in binary:   " << binary.difference(binary, binary1, binSize).getBinary() << endl;
    cout << "differ in decimal:    " << binary.binaryToDecimal(binary.difference(binary, binary1, binSize), binSize) << endl;
    cout << endl;

    cout << "mult in binary:   " << binary.binaryMult(binary, binary1, binSize).getBinary() << endl;
    cout << "mult in decimal:  " << binary.binaryToDecimal(binary.binaryMult(binary, binary1, binSize),binSize);
    cout << endl;




}

