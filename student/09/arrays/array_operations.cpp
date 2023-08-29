#include "array_operations.hh"
#include <iostream>
#include <climits>

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int size: number of elements to be examined
 * return value: the greatest element of the array
 */
int greatest_v1(int *itemptr, int size)
{
    int biggest = INT_MIN;
    for(int* position = itemptr; position < itemptr + size; ++position){
        if (*position > biggest) {
            biggest = *position;
        }
    }
    return biggest;
}

/*
 * Returns the greatest element of the array.
 * int* itemptr: pointer to the first array element to be examined
 * int* endptr: pointer to the memory address after the last element of the array
 * return value: the greatest element of the array
 */
int greatest_v2(int *itemptr, int *endptr)
{
    // calclulate distance between itemptr and endptr, size of subarray
    int size = endptr - itemptr;

    int biggest = INT_MIN;
    for(int* position = itemptr; position < itemptr + size; ++position){
        if (*position > biggest) {
            biggest = *position;
        }
    }
    return biggest;
}

/* Copies the content of the array to another array
 * int* itemptr: pointer to the first array element to be copied
 * int* endptr: pointer to the memory address after the last element of the array to be copied
 * int* targetptr: pointer to the head of the array, to which to copy
 */
void copy(int *itemptr, int *endptr, int *targetptr)
{
    // calclulate distance between itemptr and endptr, size of subarray
    int size = endptr - itemptr;

    int i = 0;
    for(int* position = itemptr; position < itemptr + size; ++position){
        *(targetptr + i) = *position;
        i++;
    }
}

/* Reverses the elements of the array
 * int* leftptr: pointer to the first element of the reversable part
 * int* rightptr: pointer to the next memory address after the reversable part
 */
void reverse(int *leftptr, int *rightptr)
{

    leftptr++;
    rightptr++;

    // get size, -1 cause rightptr is after last element
    //int size = leftptr - rightptr -1;

    // copy table
    //int sub_array[size];
    //copy(leftptr, rightptr, sub_array);

    // reverse table
    //for(int* position = rightptr; position > leftptr + size; --position){
       // std::cout
    //}

}
