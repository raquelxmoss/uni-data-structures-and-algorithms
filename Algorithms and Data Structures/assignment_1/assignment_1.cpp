// 159201 assignment 1 skeleton
// You need to add your own AddNode and PrintLL functions, as well as an AddMatrices function
//
// Hello!
// Thank you for marking my assignment.
// You might notice some changes to the skeleton code, and a few quirks in how I write things.
// This is because I'm a professional software developer -- I've been working with Ruby and
// Javascript for the last 7 years, and I'm accustomed to some naming and style conventions from my work.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>


// TODO
// X add_node function
// X add_matrices function
// X print_matrix function
// X print all 3 matricies (inputs, output)
// X print_linked_list in order
//   refactor to remove length variables

using namespace std;

struct Node {
  int row;
  int column;
  int value;
  Node *next;
};

Node *A, *B, *Result;

// TODO can I do this without globals
int column_number = 0, row_number = 0;

void reverse_list(Node * &listpointer) {
  Node *temp1, *temp2, *temp3;
  temp2 = listpointer;
  temp3 = listpointer->next;

  while (temp3 != NULL) {
    temp1 = temp3->next;
    temp3->next = listpointer;
    listpointer = temp3;
    temp3 = temp1;
  }

  temp2->next = NULL;
}

void add_node(Node *& listpointer, int row, int column, int value) {
  Node *node_to_add;

  node_to_add = new Node;
  node_to_add->row = row;
  node_to_add->column = column;
  node_to_add->value = value;
  node_to_add->next = listpointer;

  listpointer = node_to_add;
}

Node* search_matrix(Node * matrix, int row, int column) {
  Node *current;
  current = matrix;

  while (true) {
    if (current == NULL) {
      break;
    }

    if (current->row == row && current->column == column) {
      return current;
    }

    current = current->next;
  }

  return NULL;
}

void add_matricies(Node * matrix_1, Node * matrix_2) {
  if (matrix_1 == NULL || matrix_2 == NULL) {
    printf("Cannot add empty matrices\n");

    return;
  }

  // TODO
  // if matrix_1.length != matrix_2.length
  // return

  for (int row = 0; row < row_number; ++row) {
    for (int col = 0; col < column_number; ++col) {
      Node* matrix_1_node = search_matrix(matrix_1, row, col);
      Node* matrix_2_node = search_matrix(matrix_2, row, col);

      int value_1;
      int value_2;
      int result;

      if (matrix_1_node) {
        value_1 = matrix_1_node->value;
      } else {
        value_1 = 0;
      }

      if (matrix_2_node) {
        value_2 = matrix_2_node->value;
      } else {
        value_2 = 0;
      }

      result = value_1 + value_2;

      if (result != 0) {
        add_node(Result, row, col, result);
      }
    }
  }

  reverse_list(Result);
}

void print_matrix(Node * listpointer, int row_number, int column_number) {
  Node *current;
  current = listpointer;

  for (int row = 0; row < row_number; ++row) {
    for (int col = 0; col < column_number; ++col) {
      Node* value = search_matrix(current, row, col);

      if (value) {
        printf("%i ", value->value);
      } else {
        printf("0 ");
      }

      if (col == column_number - 1) {
        printf("\n");
      }
    }
  }

  printf("\n");
}

void read_matrix(Node* &a, char *file_name) {
  ifstream input;
  input.open(file_name);

  if (!input.good()) {
    cout << "Cannot open file " << file_name << endl;
    exit(0);
  }

  string line;

  // reads the first line to get dimensions of the matrix
  if (input.good()) {
    getline(input, line);
    stringstream sline(line);
    sline >> row_number >> column_number;
  }

  int value = 0;

  for (int row = 0; row < row_number; ++row) {
    if (input.good()) {
      getline(input, line);
      stringstream sline(line);

      for (int col = 0; col < column_number; ++col) {
        sline >> value;
        if (value == 0) continue;

        add_node(a, row, col, value);
      }
    }
  }

  reverse_list(a);

  input.close();
}

void print_linked_list(Node * list) {
  Node *current;
  current = list;

  while (true) {
    if (current == NULL) {
      break;
    }

    printf("%i ", current->value);

    current = current->next;
  }
}

void print_matricies(Node * matrix_1, Node * matrix_2, Node * matrix_3) {
  printf("Matrix 1: ");
  print_linked_list(matrix_1);
  printf("\n");
  print_matrix(A, row_number, column_number);

  printf("Matrix 2: ");
  print_linked_list(matrix_2);
  printf("\n");
  print_matrix(B, row_number, column_number);

  printf("Matrix Result: ");
  print_linked_list(matrix_3);
  printf("\n");
  print_matrix(Result, row_number, column_number);
}

int main(int argc, char** argv) {
  if (argc != 3) { printf("needs two matrices \n"); exit(0); }
  read_matrix(A, argv[1]);
  read_matrix(B, argv[2]);

  add_matricies(A, B);

  print_matricies(A, B, Result);
}
