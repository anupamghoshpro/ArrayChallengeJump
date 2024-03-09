/*
Have the function Jump() take the array of numbers stored in arr
and first determine the largest element in the array,
and then determine whether or not you can reach that same element within
the array by moving left or right continuously according to whatever integer
is in the current spot. If you can reach the same spot within the array,
then your program should output the least amount of jumps it took.

For example: if the input is [2, 3, 5, 6, 1] you'll start at the spot where
6 is and if you jump 6 spaces to the right while looping around the array you
end up at the last element where the 1 is. Then from here you jump 1 space to
the left and you're back where you started, so your program should output 2.
If it's impossible to end up back at the largest element in the array your
program should output -1. The largest element in the array will never equal
the number of elements in the array. The largest element will be unique. 

Input:1,2,3,4,2
Output:3

Input:1,7,1,1,1,1
Output:2
*/
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

/* Structure to represent a node in BFS */
struct Node
{
    int index;
    int jumpCount;
};


class ArrayJumper
{
private:
    int *arr;
    int size;
    /*
    The keys of the unordered map are the indices of elements 
    in the array. The boolearn value respective to a particular
    key/index indicates if that key has already been visited. 
    If so, its set true, otherwise false.
    */
    unordered_map<int, bool> indexFound;

    /* 
    Determines the index of the largest 
    element in the array 
    */
    int FindIndexOfLargestElement()
    {
        return distance(arr, max_element(arr, arr + size));
    }

    /* 
    Calculates the left and right jump 
    indecies of the target location 
    */
    pair<int, int> CalculateIndexes(int currentIndex)
    {
        int currentElement = arr[currentIndex];
        
        int leftIndex = (currentIndex - currentElement + size) % size;
        int rightIndex = (currentIndex + currentElement) % size;

        return make_pair(leftIndex, rightIndex); // Return the pair of left and right indexes
    }

public:
    ArrayJumper(int array[], int arraySize) : arr(array), size(arraySize)
    {
        /* Initialize the map for each index */
        for (int index = 0; index < size; index++)
        {
            indexFound[index] = false;

        }
    }

    // Method to find the minimum number of jumps needed to reach the largest element in the array
    int Jump()
    {
        int targetIndex = FindIndexOfLargestElement();
        /* Calculate the left and right indices */
        pair<int, int> indecies = CalculateIndexes(targetIndex);

        // Create nodes for the left and right locations after an array jump
        Node left = {indecies.first, 1};
        Node right = {indecies.second, 1};

        // Create a queue to perform BFS
        queue<Node> list;
        list.push(left); // Push the left node into the queue
        list.push(right); // Push the right node into the queue

        // Perform BFS
        while (!list.empty())
        {
            Node current = list.front();
            list.pop();

            // Check if we reach the target location
            if (current.index == targetIndex)
            {
                return current.jumpCount;
            }
            
            /* Marks the current index as visited */
            indexFound[current.index] = true;

            /* Calculate the left and right indecies for the current index */
            pair<int, int> nextIndexes = CalculateIndexes(current.index);

            /* Update the left and right nodes with the new indexes and counts */
            left.index = nextIndexes.first;
            left.jumpCount = current.jumpCount + 1;
            right.index = nextIndexes.second;
            right.jumpCount = current.jumpCount + 1;

            /* 
            Checks if the new indecies have been previously analyzed. 
            If so stops this traversal path and move on with the other 
            indecies in the quues. If not add the respective indecies 
            for a particular jump into the queue and marks them them 
            as visited.
            */
            if (!indexFound[left.index])
            {
                indexFound[left.index] = true;
                list.push(left);
            }
            if (!indexFound[right.index])
            {
                indexFound[right.index] = true;
                list.push(right);
            }
        }

        /* Return -1 if the target is not reachable */
        return -1;
    }
};


int main()
{
    int arr1[] = {2, 3, 5, 6, 1};
    int arr2[] = {1, 2, 3, 4, 2};
    int arr3[] = {1, 7, 1, 1, 1, 1};
    int arr4[] = {1, 6, 7, 2, 1, 1};

    ArrayJumper jumper1(arr1, sizeof(arr1) / sizeof(arr1[0]));
    ArrayJumper jumper2(arr2, sizeof(arr2) / sizeof(arr2[0]));
    ArrayJumper jumper3(arr3, sizeof(arr3) / sizeof(arr3[0]));
    ArrayJumper jumper4(arr4, sizeof(arr4) / sizeof(arr4[0]));
    
    cout << jumper1.jump() << endl; /* Output: 2 */
    cout << jumper2.jump() << endl; /* Output: 3 */
    cout << jumper3.jump() << endl; /* Output: 2 */
    cout << jumper4.jump() << endl; /* Output: -1 */
    
    return 0;
}

