// Raquel Moss
// ID: 22001105
// Hello!
// Thank you for marking my assignment.
// You might notice some changes to the skeleton code, and a few quirks in how I write things.
// In my day job, I'm a software developer working with higher-level languages (mostly Ruby
// and JavaScript). I'm accustomed to some naming and style conventions through my work, so
// you might see them here.

#include <stdio.h>
#include <stack>
#include <stdlib.h>
#include <string>

#include <iostream>
#include <fstream>

using namespace std;

class Tree {
  private:
    char data;
    Tree *leftpointer, *rightpointer;
  public:
    Tree(char character, Tree* l, Tree* r) {
      data = character;
      leftpointer = l;
      rightpointer = r;
    }

    ~Tree() { }

    char RootData() { return data; }

    Tree* Left() { return leftpointer; }

    Tree* Right() { return rightpointer; }
};

void printInOrder(Tree* tree) {
  if (tree == NULL) { return ; }

  if(!isdigit(tree->RootData())) {
    cout << '(';
  }

  printInOrder(tree->Left());

  cout << tree->RootData();

  printInOrder(tree->Right());

  if(!isdigit(tree->RootData())) {
    cout << ")";
  }
}

void printPostOrder(Tree* tree) {
  if (tree == NULL) { return ; }

  printPostOrder(tree->Left());
  printPostOrder(tree->Right());
  cout << tree->RootData() << " ";
}

int main(int argc, char** argv) {
  char digit;
  char oper;
  char expression[100];
  ifstream input_file;

  Tree *T1, *T2, *T;
  stack<Tree*> ExpressionStack;

  if (argc == 2) {
    input_file.open(argv[1]);
  } else {
    printf("The program needs a filename as argument \n");
    exit(0);
  }

  while(input_file >> expression) {
    if (isdigit(expression[0])) {
      sscanf(expression, "%c", &digit);

      Tree *newTree = new Tree(digit, NULL, NULL);
      ExpressionStack.push(newTree);
    } else {
      sscanf(expression,"%c",&oper);

      T1 = ExpressionStack.top();
      ExpressionStack.pop();

      T2 = ExpressionStack.top();
      ExpressionStack.pop();

      ExpressionStack.push(new Tree(oper, T2, T1));
    }
  }

  T = ExpressionStack.top();

  cout << "In-fix:" << endl;
  printInOrder(T);
  cout << endl;
  cout << "Post-fix:" << endl;
  printPostOrder(T);
}
