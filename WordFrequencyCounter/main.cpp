#include <iostream>
#include <map>
#include <unordered_map>


std::string userInputString;
std::unordered_map<std::string, int> finalMap;

int main()
{
    while(1)
    {
        // read input sentence form user
        std::cout << "Input sentence" << std::endl;
        std::getline(std::cin, userInputString);

        // define temp word
        std::string tempWord;

        // clear tempWord
        tempWord.clear();

        // iterate through the string to find temporary words
        for(auto it = userInputString.begin(); it != userInputString.end(); it++)
        { 
            if(*it != ' ')
            {
                tempWord.push_back(*it);

                // check if it+1 is end of iterator
                if(it+1 == userInputString.end())
                {
                    // this is the last word in the sentence add to the unordered map
                                    // add word to unordered map
                    if (finalMap.find(tempWord) == finalMap.end()) {
                        std::cout << tempWord << " not found!" << std::endl;
                        finalMap[tempWord] = 1;
                        // clear tempWord
                        tempWord.clear();
                    }else
                    {
                        finalMap[tempWord]++;
                    }
                }                
            }else
            {
                // add word to unordered map
                if (finalMap.find(tempWord) == finalMap.end()) {
                    std::cout << tempWord << " not found!" << std::endl;
                    finalMap[tempWord] = 1;
                    // clear tempWord
                    tempWord.clear();
                }else
                {
                    finalMap[tempWord]++;
                }
            }    
            
        // print unordered_map elements

        }

        std::cout << "Loop end " << std::endl; 

        for(auto itt = finalMap.begin(); itt != finalMap.end(); itt++)
        {
            std::cout << (*itt).first << " - " << (*itt).second << std::endl;
        }
    }

    return 0;
}