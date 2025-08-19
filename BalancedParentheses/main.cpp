/* Using stack structure check if string has balanced parenthesis
   The SW shall enable user to enter custome string with parethensis

   ena
   */

#include <iostream>
#include <stack>

using namespace std;

std::string inputString = "(()a+b)*(c+d))(";
std::stack<char> myStack;

int main()
{
    std::cout<< "Hello world" << endl;

    for(auto it = inputString.begin(); it<inputString.end(); it++)
    {
        if(*it == '(')
        {
            myStack.push(*it);
        }
        else if(*it == ')')
        {
            // pop if not empty
            if(myStack.empty() == false)
            {
                myStack.pop();
            }
            else
            {
                std::cout << "Parenthesis not balanced" << std::endl;
                return 0;
            }
        }
    }
    if(myStack.empty() == true)
    {
        std::cout << "Parenthesis balanced" << std::endl;
    }
    else
    {
        std::cout << "Parenthesis NOT balanced" << std::endl;
    }
    
    
    // add comment to set up gitHub Account
    return 0;
}
