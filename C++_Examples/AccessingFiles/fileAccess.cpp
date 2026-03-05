#include <iostream>
#include <fstream>
#include <string>

int main()
{
    // create file stream object
    std::ifstream inputFileStream("input.txt");

    // create output file stream object
    std::ofstream outputFileStream("output.txt", std::ios::out | std::ios::app); // open for writing, append if exists

    try
    {
        // check if file stream is open
        if(!inputFileStream.is_open())
        {
            throw std::ios_base::failure("Failed to open file");
        }

        // read data from file        std::string line;
        std::string line;
        while(std::getline(inputFileStream, line))
        {
            // process the line
            std::cout << line << std::endl; // for demonstration, just print the line

            if(line.empty())
            {
                continue; // skip empty lines
            }

            if(outputFileStream.is_open())
            {
                // write the line to output file
                outputFileStream << line << std::endl;
            }
            else
            {
                throw std::ios_base::failure("Failed to open output file");
            }
        }
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // exit with error code
    }

    return 0;
}
