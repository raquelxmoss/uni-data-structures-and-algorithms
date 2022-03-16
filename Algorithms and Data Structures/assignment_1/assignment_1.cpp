// Raquel Moss
// ID: 22001105
// Hello!
// Thank you for marking my assignment.
// You might notice some changes to the skeleton code, and a few quirks in how I write things.
// In my day job, I'm a software developer working with higher-level languages (mostly Ruby
// and JavaScript). I'm accustomed to some naming and style conventions through my work, so
// you might see them here.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
  int row;
  int column;
  int value;
  Node *next;
};

Node *A, *B, *Result;

int number_of_columns = 0, number_of_rows = 0;

void reverse_list(Node * &listpointer) {
  if (listpointer == NULL) { return; }

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
    if (current == NULL) { break; }
    if (current->row == row && current->column == column) { return current; }
    current = current->next;
  }

  return NULL;
}

void add_matricies(Node * matrix_1, Node * matrix_2) {
  for (int row = 0; row < number_of_rows; ++row) {
    for (int col = 0; col < number_of_columns; ++col) {
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

void print_matrix(Node * listpointer) {
  Node *current;
  current = listpointer;

  for (int row_index = 0; row_index < number_of_rows; ++row_index) {
    for (int col_index = 0; col_index < number_of_columns; ++col_index) {
      Node* value = search_matrix(current, row_index, col_index);
      int output = value ? value->value : 0;

      printf("%i ", output);
    }

    printf("\n");
  }
}

void read_matrix(Node* &a, char *file_name) {
  ifstream input;
  input.open(file_name);

  if (!input.good()) {
    cout << "Cannot open file " << file_name << endl;
    exit(0);
  }

  string line;

  if (input.good()) {
    getline(input, line);
    stringstream sline(line);
    sline >> number_of_rows >> number_of_columns;
  }

  int value = 0;

  for (int row = 0; row < number_of_rows; ++row) {
    if (input.good()) {
      getline(input, line);
      stringstream sline(line);

      for (int col = 0; col < number_of_columns; ++col) {
        sline >> value;

        if (value != 0) {
          add_node(a, row, col, value);
        }
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
    if (current == NULL) { break; }

    printf("%i ", current->value);
    current = current->next;
  }
}

void print_matricies(Node * matrix_1, Node * matrix_2, Node * matrix_3) {
  printf("Matrix 1: ");
  print_linked_list(matrix_1);
  printf("\n");
  print_matrix(A);

  printf("Matrix 2: ");
  print_linked_list(matrix_2);
  printf("\n");
  print_matrix(B);

  printf("Matrix Result: ");
  print_linked_list(matrix_3);
  printf("\n");
  print_matrix(Result);
}

int main(int argc, char** argv) {
  if (argc != 3) { printf("needs two matrices \n"); exit(0); }
  read_matrix(A, argv[1]);
  read_matrix(B, argv[2]);

  add_matricies(A, B);

  print_matricies(A, B, Result);
}

// test6 -- expected 8, got 21
