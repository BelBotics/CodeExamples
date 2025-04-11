#include <iostream>
#include <vector>

using namespace std;
int main()
{
    cout << "Hello world!" << endl;
    cout << "Check what will be user email" << endl;

    // Create some vector and check what is capacity of it
    vector<int> myTestVector(10, 0);

    // create an iterator for vector of int variables
    vector<int>::iterator it;

    // printout vector size and capacity
    cout << "Vector size is:" << myTestVector.size() << endl;
    cout << "Vector capacity is:" << myTestVector.capacity() << endl << endl;

    myTestVector.push_back(5);
    myTestVector.push_back(5);
    myTestVector.push_back(5);
    myTestVector.push_back(5);

    myTestVector[15] = 184;

    cout << "Vector size is:" << myTestVector.size() << endl;
    cout << "Vector capacity is:" << myTestVector.capacity() << endl << endl;

    for (int i = 0; i < myTestVector.size(); i++)
    {
        //cout << "Vector value of " << i << " is " << myTestVector[i] << endl;
    }

    for(it = myTestVector.begin(); it != myTestVector.end(); it++)
    {
        cout << "Iterator value is: " << *it << endl;
    }


    return 0;
}