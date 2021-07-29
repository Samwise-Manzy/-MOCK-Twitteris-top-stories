// File Name: program3_sam234.cpp
//
// Auther Samuel Manzanares
// Date: 06/17/2021
// Assignment Number: 2
// CS 2308.501 Summer 2021
// Instructor: Dr. J. Marcos Palacios

 (MOCK) Twitteris re-doing its internet stories trending feature, and has
 asked me to develop a prototype by means of a C++ program that will
 displaya list of the top internet stories. This was done depending
 on the mode of of the stories, with the stories having the same score
 as the mode being displayed. If no mode is found, the top 5 stories
 will be displayed. 

//****************This is the line of 80 characters in length*******************
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct Data { // struct of data type Data to house movie info
    string title;
    string url;
    int score;
};

//***********************************************************
// sortScore: sorts story score in accending order
//
// *arrPtr is pointer to array
// size is the number of elements in the array
// void return type
//***********************************************************
void sortScore(Data *arrPtr, int size) { 
    
    bool swap; // indicates end of sorting
    Data temp; // holds temp variable for swap

    do {

        swap = false;
        for (int i = 0; i < (size-1); i++) { 

            if ((arrPtr+i)->score > (arrPtr+i+1)->score) {

                temp = *(arrPtr+i);
                *(arrPtr+i) = *(arrPtr+i+1);
                *(arrPtr+i+1) = temp;
                swap = true;
            }
        }
        size--;
    } while(swap);

}

//***********************************************************
// findMode: finds are returns mode of story scores of array
//
// *arrPtr is pointer to array
// size is the number of elements in the array
// returns mode of type int
//***********************************************************
int findMode (Data *arrPtr, int size) {

    sortScore(arrPtr, size);

    int counter = 1; // # times we see a value
    int max = 1, x = -1; // score's # of times (largest)

    for (int i = 0; i < size - 1; i++) {

        if ((arrPtr+i)->score == (arrPtr+i+1)->score) {

            counter++;
 
            if (counter > max) {
                
                max = counter;
                x = (arrPtr+i)->score;
            }

        } else {
            counter = 1;
        }
    }

    return x;
}

//***********************************************************
// storyOutput: outputs mode and stories if found
//
// *arrPtr is pointer to array
// size is the number of elements in the array
// mode is the mode found by function findMode
// void return type
//***********************************************************
void storyOutput (Data *arrPtr, int size, int mode) {

    if (mode != -1) {
        cout << "Mode: " << mode << endl << endl;

        for (int i = 0; i < size; i++) {

            if ((arrPtr+i)->score == mode) {

                cout << (arrPtr+i)->title << endl;
                cout << (arrPtr+i)->url << endl << endl;
            }

        }
    } else {
        cout << "No mode was found\n\n";

        for (int i = 0; i < 5; i++) {
            cout << (arrPtr+i)->title << endl;
            cout << (arrPtr+i)->url << endl << endl;
        }
    }

}

//***********************************************************
// inputData: inputs data from file
//
// ptr is a pointer of pass by reference to input data 
// returns size of array
//***********************************************************
int inputData(Data *&ptr) {

    int size; // takes in size(number of) stories in file

    ifstream fin; 

    fin.open("program3stories.txt");

     // Error check to ensure the input file opened:
    if (!fin) {
        cout << "Could not open file. Terminating program.\n";
        return -1;
    }


    fin >> size;

    Data *stories = new Data[size]; // dynamic allocation of array for input

    for (int i = 0; i < size; i++) {
        fin >> ws;
        getline(fin, (stories+i)->title);
        fin >> (stories+i)->url;
        fin >> (stories+i)->score;
    }
    ptr = stories;

    return size;
}

int main() {

    int mode; // gets mode from findMode fuction of stories

    int size; // gets return array size from fuction inputdata
    Data * pntrData = nullptr; // pointer to data array

    size = inputData(pntrData);
    mode = findMode(pntrData, size);

    storyOutput(pntrData, size, mode);

}
