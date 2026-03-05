#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

template<typename T>
class PointClass
{
    public:
        PointClass(T x, T y) : x(x), y(y) {}
        T getX() const { return x; }
        T getY() const { return y; }
        T distanceTo(const PointClass& other) const
        {
            T dx = x - other.x;
            T dy = y - other.y;
            return sqrt(dx*dx + dy*dy);
        }

        // define setters for x and y
        void setX(T data)
        {
            x = data;
        }

        void setY(T data)
        {
            y = data;
        }   

        bool operator==(const PointClass& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator<(const PointClass& other) const
        {
            if (x < other.x) return true;
            if (x > other.x) return false;
            return y < other.y;
        }

    private:
        T x;
        T y;
};


int main(int argc, char* argv[])
{
    // define std::vector
    std::vector<PointClass<float>> pointsVec;
    std::vector<PointClass<float>> patternVec;
    std::vector<PointClass<float>> destinationVec;

    pointsVec.push_back(PointClass<float>(3.0f, 4.0f));
    pointsVec.push_back(PointClass<float>(1.0f, 2.0f));
    pointsVec.push_back(PointClass<float>(5.0f, 6.0f));
    pointsVec.push_back(PointClass<float>(3.0f, 4.0f));
    pointsVec.push_back(PointClass<float>(7.0f, 8.0f));

    patternVec.push_back(PointClass<float>(3.0f, 4.0f));
    patternVec.push_back(PointClass<float>(1.0f, 2.0f));

    auto position = std::search(pointsVec.begin(), pointsVec.end(), patternVec.begin(), patternVec.end());
    bool patternFound = (position != pointsVec.end());
    if(patternFound)
    {
        std::cout << "Pattern found in vector." << std::endl;
    }
    else
    {
        std::cout << "Pattern not found in vector." << std::endl;
    }

    // now merge vector pointsVec and patternVec into destinationVec    
    destinationVec.reserve(pointsVec.size() + patternVec.size());
    std::merge(pointsVec.begin(), pointsVec.end(), patternVec.begin(), patternVec.end(), std::back_inserter(destinationVec));
    
    for(auto it = destinationVec.begin(); it != destinationVec.end(); ++it)
    {
        std::cout << "Point: (" << it->getX() << ", " << it->getY() << ")" << std::endl;
    }

    int countNumber = std::count(pointsVec.begin(), pointsVec.end(), PointClass<float>(3.0f, 4.0f));
    std::cout << "Number of points in vector: " << countNumber << std::endl;

    // serach for a specific pattern in the vector

    // at this point we would like to sort the vector of points
    std::sort(pointsVec.begin(), pointsVec.end());

        std::cout  << "Running: " << argv[0] << std::endl;
    PointClass<float> point1(3.0f, 4.0f);
    PointClass<float> point2(0.0f, 0.0f);
    std::cout << "Distance: " << point1.distanceTo(point2) << std::endl;

    std::cout << "\nDisplay size in bytes for standard types:" << std::endl;
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of long int: " << sizeof(long int) << " bytes" << std::endl;
    std::cout << "Size of float: " << sizeof(float) << " bytes" << std::endl;
    std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "Size of long double: " << sizeof(long double) << " bytes" << std::endl;
    std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
    std::cout << "Size of bool: " << sizeof(bool) << " bytes" << std::endl;

    // create while 1 loop to set new values for pint1 and point2 and print the distance
    while(1)
    {
        std::cout << "\nEnter new x and y for point1: ";
        std::string input1, input2;
        float x1, y1;
        std::cin >> input1 >> input2;
        try{
            x1 = std::stof(input1);
            y1 = std::stof(input2);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Invalid input. Please enter numeric values." << std::endl;
            continue; // skip the rest of the loop and prompt again
        }
        
        point1.setX(x1);
        point1.setY(y1);

        std::cout << "\nEnter new x and y for point2: ";
        std::string input3, input4;
        float x2, y2;
        std::cin >> input3 >> input4;
        try{
            x2 = std::stof(input3);
            y2 = std::stof(input4);
        }
        catch(const std::exception& e)
        {   
            std::cerr << "Invalid input. Please enter numeric values." << std::endl;
            continue; // skip the rest of the loop and prompt again
        }
        
        point2.setX(x2);
        point2.setY(y2);

        std::cout << "\nDistance: " << point1.distanceTo(point2) << std::endl;
    }

    return 0;
}