#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>


std::string userInputString;
std::string inputFName;
std::unordered_map<std::string, int> finalMap;


// file for reading
std::ifstream inputFStream;

int totalWordCount = 0;     // total word count

static int GetMaxFreqWord(std::unordered_map<std::string, int> &finalMap);
static void RemoveEmptyWord(std::unordered_map<std::string, int> &finalMap);

int main(int argc, char * argv[])
{
    // check if number of input arguments are equal to two
    if(argc == 2)
    {
        // the second parametar is path to the input file
        inputFName.assign(argv[1]);
        std::cout << "Input file path: " << inputFName << std::endl;

        inputFStream.open(inputFName);

        if(!inputFStream.is_open())
        {
            std::cerr << "Unable to open file " << inputFName << " for read" << std::endl;
            return -1;
        }
    }
    else
    {
        std::cerr << "Wrong number of argument provided in call, expect 2 but " << argc << " provided" << std::endl;
        return -1;
    }

    while(std::getline(inputFStream, userInputString))
    {
        // read input sentence form user
        std::cout << userInputString << std::endl;

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
                        //std::cout << tempWord << " not found!" << std::endl;
                        finalMap[tempWord] = 1;
                    }else
                    {
                        finalMap[tempWord]++;
                    }

                    // increment total word counter
                    totalWordCount++;

                    // clear tempWord
                    tempWord.clear(); 
                }                
            }else
            {
                // add word to unordered map
                if (finalMap.find(tempWord) == finalMap.end()) {
                    //std::cout << tempWord << " not found!" << std::endl;
                    finalMap[tempWord] = 1;
                }else
                {
                    finalMap[tempWord]++;
                }

                // increment total word counter
                totalWordCount++;

                // clear tempWord
                tempWord.clear(); 
            }               
        }
    }

    std::cout << std::endl;

    std::cout << "Total word count: " << totalWordCount << std::endl;

    // at the end of word frequency calculation printout unordered_map content
    std::cout << std::endl << "Unordered_map content: " << std::endl; 

    for(auto itt = finalMap.begin(); itt != finalMap.end(); itt++)
    {
        std::cout << (*itt).first << " - " << (*itt).second << std::endl;
    }

    RemoveEmptyWord(finalMap);

    // printout the word with max frequency count
    GetMaxFreqWord(finalMap);

    return 0;
}

static int GetMaxFreqWord(std::unordered_map<std::string, int> &finalMap)
{
    auto tempWord = finalMap.begin();
    for(auto it =  finalMap.begin(); it != finalMap.end(); it++)
    {
        if((*tempWord).second < (*it).second)
        {
            tempWord = it;
        }
    
    } 

    std::cout << "Word with max frequency is: " <<  (*tempWord).first << " count: " <<  (*tempWord).second << std::endl; 

    return (*tempWord).second;
}

static void RemoveEmptyWord(std::unordered_map<std::string, int> &finalMap)
{
    for(auto it =  finalMap.begin(); it != finalMap.end(); it++)
    {
        if((*it).first == "")
        {
            it = finalMap.erase(it);
        }
    
    } 


}