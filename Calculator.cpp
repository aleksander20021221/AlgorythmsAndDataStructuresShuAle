//#include "C:\Users\albuinsk\source\repos\BinaryClass\BinaryClass\Binary.h"
//#include "C:\Users\albuinsk\source\repos\BinaryClass\BinaryClass\Stack.h"
#include <iostream> 
#include <string> 
#include "../../BinaryClass/BinaryClass/Binary.cpp"
//#include "../../BinaryClass/BinaryClass/Stack.cpp"
using namespace std;

class Calculator {
private:
	string expression;
public:
	void setExpression(string s){
		this->expression = s;
	}
    int count(int binsize1) {
        string str = this->expression;

        int binSize = binsize1;
        string error = "Invalid result! Out of range";

        Stack <Binary> stack;
        Stack <string> stackSt;

        Stack <string> forCheck;

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
                resBin.append(s + " ");
                forCheck.push(s);
            }
            if (isInteger(s)) {
                Binary binaryNum;
                binaryNum.setBinary(stoi(s), binSize);
                stack.push(binaryNum);
                sizeB++;
                resBin.append(binaryNum.getBinary() + " ");
                forCheck.push(s);
            }



            if (sizeS > 0 && sizeB > 1) {
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

        string check = forCheck.pop();

        //cout << check << endl;


        cout << "--------------------------------------------" << endl;
        


        if (!(    (sizeB == 1)       &&     (sizeS == 0)   ) )
            cout << "Error in input of RPN" << endl;
        else if (!(check=="*" || check=="-" || check=="+"))
            cout << "Error in input of RPN" << endl;
        else {
            while (!stack.empty()) {
                Binary answer = stack.pop();
                if (answer.getBinary() == error)
                    cout << error << " ";
                else {
                    cout << answer.binaryToDecimal() << " " << endl;
                    cout << answer.getBinary() << endl;
                }

            }
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
        }


        cout << "--------------------------------------------" << endl;
        cout << "string in binary:" << endl;
        


        cout << resBin;
        cout << endl;
        return 0;
	}

};
int main() {
	string name;
	cout << "Input a RPN:" << endl;
	getline(cin, name);


	Calculator calcStr;
	calcStr.setExpression(name);

    calcStr.count(8);

    cout << "--------------------------------------------" << endl;
	return 0;
}