#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

// create a base excercise class with a virtual action method that can be overridden by derived classes for specific exercises
class EcxerciseBase
{
    public:
    virtual std::pair<int, int> action() = 0; // pure virtual method to be implemented by derived classes

};

class SumTwoNumbers : public EcxerciseBase
{
    public:

    std::pair<int, int> action() override
    {
        // in vector nums, find two numbers that add to target and return their indices
        for(auto it = nums.begin(); it != nums.end(); ++it)
        {
            // calculate needed value by subracting current value from target
            int neededValue = target - *it;
            // check if needed value is in vector 
            if(std::find(nums.begin(), nums.end(), neededValue) != nums.end())
            {
                std::cout << "Found two numbers that add to target (" << target << "): " << *it << " and " << neededValue << std::endl;
                // return indices of the two numbers
                int index1 = it - nums.begin();
                int index2 = std::find(nums.begin(), nums.end(), neededValue) - nums.begin();
                return std::make_pair(index1, index2);
            }   
        }
        
        // code for task 1 goes here
        std::cout << "No two numbers add to target" << std::endl;
        return std::make_pair(0, 0);
    }

    private:
        // input array
        std::vector<int> nums = {2, 4, 8, 9, 11};
        // target value
        int target = 17;
};
