#include <iostream>
#include <string>
#include <memory>

// Create basic class which will hold parameters of configuration
// some integer, double and string values

class BMSParameters
{
    public:
        BMSParameters()
        {
            std::cout << "BMSParameters constructor called" << std::endl;
        };
        ~BMSParameters()
        {
            std::cout << "BMSParameters destructor called" << std::endl;
        };
        int m_numOfCells;
        double m_current;
        std::string m_cellManufacturer; 
};

class ReceiverClass
{
    public:
        void PrintParams(BMSParameters * bmsParams)
        {        
            std::cout << "Printing params: " << bmsParams->m_cellManufacturer << std::endl;
        }
};

class Parent
{
    public:
        Parent()
        {
            std::cout << "Parent class constructor called" << std::endl;

            m_bmsParams.m_cellManufacturer = "MX553BUH82";

            m_receiver = std::make_unique<ReceiverClass> ();
        };
        ~Parent()
        {
            std::cout << "Parent class destructor called" << std::endl;
        }

        void TransferData()
        {
            m_receiver->PrintParams(&m_bmsParams);
        }
    private:
        BMSParameters m_bmsParams;
        std::unique_ptr<ReceiverClass> m_receiver;
};



int main()
{

    std::cout << "Hello world" << std::endl;

    // create an object of class Parent
    Parent myParentObj;

    myParentObj.TransferData();


    return 0;
}