// 159201 assignment 1 skeleton
// You need to add your own AddNode and PrintLL functions, as well as an AddMatrices function
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <string>

using namespace std;

struct Node {
  int row;
  int column;
  int value;
  Node *next;
};
Node *A, *B;

//reads a matrix from a file
void read_matrix(Node* &a, char *file_name) {
  int col = 0, row = 0, value = 0;

  ifstream input;
  input.open(file_name);

  if (!input.good()) {
    cout << "Cannot open file " << file_name << endl;
    exit(0);
  }

  /* int c; */
  string line;

  //reads the first line to get dimensions
  if (input.good()) {
    getline(input,line);
    stringstream sline(line);
    sline >> row >> col;
    cout << "Matrix dimensions " << row << " " << col << endl;
  }

  //read matrix
  for (int i = 0; i < row; ++i) {
    if (input.good()) {
      getline(input,line);
      stringstream sline(line);

      for (int j = 0; j < col; ++j) {
        sline >> value;
        if(value == 0) continue;
        //
        //Include your own add_node(a, i, j, value); function here
        //
        //The next line is for debbuging, it can be commented later
        cout << "Element at (" << i << " " << j << ") is different than zero and it is: "<< value <<" ";
      }
      //the next line is for debugging purposes, it can be commented out later
      cout << endl;
    }
  }

  input.close();
}

int main(int argc, char** argv) {
  if (argc != 3) { printf("needs two matrices \n"); exit(0); }
  read_matrix(A, argv[1]);
  read_matrix(B, argv[2]);
}
