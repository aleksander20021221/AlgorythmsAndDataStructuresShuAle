#include <iostream>
#include <string>
using namespace std;
//#include<bits/stdc++.h> 
class Binary {
private:
    string binStr;
    int binSize;
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
public:
    void setBinary(long long int n, int binSize) {
        this->binStr = binaryForm(n, binSize);
        this->binSize = binSize;
    }

    string getBinary() {
        return this->binStr;
    }
    int getBinSize() {
        return this->binSize;
    }

    Binary(string s) {
        binStr = s;
    }
    Binary(string s, int binSiz) {
        binStr = s;
        binSize = binSiz;
    }
    Binary() {};

        
    Binary checkSum(Binary b) {

         string first = this->getBinary();
         string second = b.getBinary();

            string sumResult = binarySum(first, second, 1);
            if (sumResult.size() == this->binSize && (sumResult[0] == '0' || ((sumResult[0] == '1') && (first[0] == '1' || second[0] == '1'))))
                return Binary(sumResult, this->binSize);

            else if ( (sumResult.size() == this->binSize +1)  &&  (   (first[0] =='1' && '1' == second[0] && '1' == sumResult[1]) || (first[0] != second[0])))
                return Binary(sumResult.erase(0, 1), this->binSize);


            else return Binary ("Invalid result! Out of range");
        }
    Binary binaryMult(Binary bstr) {

        int j = this->binSize;
        string ab = "";
        bool flag = 0;
        string a = this->getBinary();
        string b = bstr.getBinary();
        Binary zero;
        Binary answer;
        zero.setBinary(0,j);

        if (b == zero.getBinary()) {
            return zero;
        }

        if (a[0] != b[0]) flag = 1;

        string first = a;
        string second = b;

        if (a[0]=='1') first = complement(a, j);
        if (b[0] == '1') second = complement(b, j);

        for (int i = second.size()-1; i >= 0; i--) {
            if (second[i]=='1')
                ab = binarySum(ab, first, second.size() - i);
        }
        while ((ab[0] == '0') && (ab.size() > j)) {
            ab = ab.erase(0,1);
        }

        if (ab.size() > j || ab[0]=='1') return Binary ("Invalid result! Out of range");

        else if (flag == 1) {
            return Binary (complement(ab, j),this->binSize);
        }
        else if (flag==0)
            return Binary(ab, this->binSize);
    }
    Binary difference(Binary b) {
        return this->checkSum(complement(b, binSize));
    }

    int binaryToDecimal()
    {
        Binary n = *this;
        int dec_value = 0;

        int base = 1;

        int len = n.getBinary().length();
        if (n.getBinary()[0] == '0') {
            for (int i = len - 1; i >= 0; i--) {
                if (n.getBinary()[i] == '1')
                    dec_value += base;
                base = base * 2;
            }
            return dec_value;
        }
        if (n.getBinary()[0] == '1') {

            //cout << n.getBinary() + "   " << n.getBinSize() << endl;

            Binary num = Binary(complement(n.getBinary(), this->binSize));
            for (int i = len - 1; i >= 0; i--) {
                if (num.getBinary()[i] == '1')
                    dec_value += base;
                base = base * 2;
            }
            return -dec_value;
        }

        
    }
    
};
template <class T>
class Stack
{
public:
    Stack() : root(nullptr) {}
    void push(const T& x) {
        Node* newnode = new Node;
        newnode->data = x;
        newnode->next = root;
        root = newnode;
    }
    bool empty() const {
        return root == nullptr;
    }

    const T& top() const {
        if (empty()) {
            throw length_error("stack is empty");
        }
        return root->data;
    }
    T pop() {
        if (empty()) {
            throw length_error("stack is empty");
        }
        Node* delnode = root;
        T x = delnode->data;
        root = delnode->next;
        delete delnode;
        return x;
    };

private:
    struct Node {
        T data;
        Node* next;
    };
    Node* root;
};

bool isInteger(string str) {
    int s = 0;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) || (((str[0] == '-') || (str[0] == '+')) && isdigit(str[i + 1])))
            s++;
    }
    if ((s == str.length()) &&(str!=""))
        return true;

    return false;
}

static string findstr(string  &s) {
    while (s[0]==' ') {
        s.erase(0,1);
    }
    int place=0;
    

    for (int i = 0; i < s.size(); i++) {
        if (isspace(s[i])) {
            place = i;
            break;
        }
    }
    string sbstr = s.substr(0, place);
    s.erase(0, place);
    return sbstr;
}




int main() {
    
    int binSize = 10;
    string error = "Invalid result! Out of range";

    Stack <Binary> stack;
    Stack <string> stackSt;

    string str = " 22 5 8 - 15 - * 8 + *";
    str.append(" ");
    cout << str << endl;

    string s, resBin;
    int sizeS = 0;
    int sizeB = 0;


    while (!str.empty()) {

        s = findstr(str);
        
        if ((s == "+") || (s == "-") || (s == "*")) {
            stackSt.push(s);
            sizeS++;
            resBin.append(s+" ");
        }
        if (isInteger(s)) {
            Binary binaryNum;
            binaryNum.setBinary(stoi(s), binSize);
            stack.push(binaryNum);
            sizeB++;
            resBin.append(binaryNum.getBinary()+" ");
        }



        if (sizeS>0 && sizeB>1) {
            Binary last = stack.pop();
            Binary first = stack.pop();
            string sign = stackSt.pop();

            Binary result;
            if (sign == "*")
                result = first.binaryMult(last);
            if (sign == "-")
                result = first.difference(last);
            if (sign == "+")
                result = first.checkSum(last);

            stack.push(result);
            sizeS--;
            sizeB--;
        }

        
    }




    cout << "--------------------------------------------" << endl;

    if (((sizeB == 1) && (sizeS == 0)))
        while (!stack.empty()) {
            Binary answer = stack.pop();
            if (answer.getBinary() == error)
                cout << error << " ";
            else {
                cout << answer.binaryToDecimal() << " " << endl;
                cout << answer.getBinary() << endl;
            }

        }
    else
        cout << "Error in input of RPN" << endl;
    
    cout << "--------------------------------------------" << endl;
    while (!stack.empty()) {
        Binary answer = stack.pop();
        if (answer.getBinary() == error)
            cout << error << " ";
        else {
            cout << answer.binaryToDecimal() << " " << endl;
            cout << answer.getBinary() << endl;
        }

    }
    while (!stackSt.empty()) {
        cout << stackSt.pop() << " ";
    }
    cout << endl;


    cout << resBin;


}
*/





