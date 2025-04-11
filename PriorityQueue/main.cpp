/*! \brief: Wreate a C++ class to implement a priority queue using a max-heap with methods to 
    insert, extract the maximim, and display elements.

    Key Concepts of Max Heap:

    Max Heap Property: In a max heap, for any given node i, the value of i is greater than or equal to the values of its children. 
    This ensures that the largest element is always at the root.

    Complete Binary Tree: A max heap is a complete binary tree, meaning all levels are fully filled except possibly the last level, which is filled from left to right.
*/

#include <iostream>
#include <vector>

using namespace std;

class Node
{
    public:
        ~Node()
        {
            cout << "Calling Node destructor function" << endl;
        }
        int data;
        Node * left;
        Node * right;
};

class PriorityQueue
{
    public:
        PriorityQueue()
        {
            top = NULL;
            bottom = NULL;
        }

        Node * findBottom()
        {
            Node * tempPtr;

            tempPtr = top;

            while(tempPtr != NULL)
            {
                if(tempPtr->left == NULL)
                {
                    // this is the last node 
                    return tempPtr;
                }
                else if(tempPtr->left == NULL)
                {

                }
            }
        }

        void restoreMaxHeap(int index)
        {
            //int index = priorityQueue.size() - 1;
            int tempData;

            if(index != 0)
            {
                // find index of the last element
                if(priorityQueue[index]->data > priorityQueue[index/2]->data)
                {
                    // swap data
                    tempData = priorityQueue[index]->data;
                    priorityQueue[(index - 1)/2]->data = priorityQueue[index]->data;
                    priorityQueue[index]->data = tempData;

                    restoreMaxHeap((index - 1)/2);                
                }
            }
        }

        void insert(int newValue)
        {
            // create new object of Node
            Node tempPtr;

            // add new object to the vector
            priorityQueue.push_back(&tempPtr);

            // update value of newly created node
            tempPtr.data = newValue;
            
            // after adding a new element a heap is not max heap any more
            //restoreMaxHeap(priorityQueue.size() - 1);
        }

        void extractMax()
        {

        }

        void display()
        {
            vector<Node *>::iterator it;

            for(it = priorityQueue.begin(); it < priorityQueue.end(); it++)
            cout << (*it)->data << endl;
        }
    private:
        Node * top;
        Node * bottom;
        vector<Node *> priorityQueue;

};

int main()
{
    PriorityQueue myQueue;


    myQueue.insert(15);
    myQueue.insert(5);
    myQueue.insert(22);
    myQueue.insert(17);
    myQueue.insert(3);
    myQueue.insert(8);

    myQueue.display();




    return 0;
}