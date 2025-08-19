/* Using stack structure check if string has balanced parenthesis
   The SW shall enable user to enter custome string with parethensis

   ena
   */

#include <iostream>
#include <stack>

using namespace std;

std::string inputString;

int main()
{
    std::cout<< "Find if parathensis ballanced or not. (Press q to exit)" << endl;

    while(1)
    {
        // crate stack object
        std::stack<char> myStack;

        // clear input string
        inputString.clear();

        std::cout << "Enter string:" << std::endl;

        // get input string from console
        std::cin >> inputString;

        if(*inputString.begin() == 'q' && inputString.length() == 1)
        {
            // user entered q to terminate the SW execution
            return 0;
        }

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
                    std::cout << "Parenthesis NOT balanced" << std::endl;
                    goto label1;
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

        label1:
        std::cout << "----------------------" << std::endl;
    }
    
    // add comment to set up gitHub Account
    return 0;
}
