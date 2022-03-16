// Raquel Moss
// ID: 22001105
// Hello!
// Thank you for marking my assignment.
// You might notice some changes to the skeleton code, and a few quirks in how I write things.
// In my day job, I'm a software developer working with higher-level languages (mostly Ruby
// and JavaScript). I'm accustomed to some naming and style conventions through my work, so
// you might see them here.

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

bool isoperator(char op) {
  if (op == '+') return true;
  if (op == '-') return true;
  if (op == '/') return true;
  if (op == '*') return true;

  printf("operator %c is invalid", op);

  return false;
}

struct Node {
  int data;
  Node* next;
};

class Stack {
  private:
    Node* listpointer;
  public:
    Stack() {
      listpointer = NULL;
    };

    ~Stack() { };

    void push(int new_data) {
      Node *temp;
      temp = new Node;

      temp->data = new_data;
      temp->next = listpointer;
      listpointer = temp;
    };

    void pop() {
      Node *temp;
      temp = listpointer;

      if (listpointer != NULL) {
        listpointer = listpointer->next;
        delete temp;
      }
    };

    int top() {
      if (!isEmpty()) {
        return listpointer->data;
      } else {
        return -1;
      }
    };

    bool isEmpty() {
      if (listpointer == NULL) { return true; }
      return false;
    };
};

int compute_result(int term_1, int term_2, char op) {
  if (op == '+') { return term_1 + term_2; }
  if (op == '-') { return term_1 - term_2; }
  if (op == '/') { return term_1 / term_2; }
  if (op == '*') { return term_1 * term_2; }

  return -1;
}

int main(int argc, char** argv) {
	int result, term_1, term_2, number;
	char oper;
  Stack *terms = new Stack();

	string input;
	ifstream input_file;

	if (argc != 2) {
	  cout << "needs a filename as argument  " << endl;
	  exit(0);
	}

	input_file.open(argv[1]);

	if (!input_file.good()) {
	  cout << "cannot read file " << argv[1] << endl;
	  exit(0);
	}

  // 3 4 +
  // +
  // 4
  // 3
	while (!input_file.eof()) {
		getline(input_file, input);

    if (input.empty()) { continue; }

    stringstream line(input);

		if (isdigit(input[0])) {
		  line >> number;

      printf("reading number %i\n", number);

      terms->push(number);
		} else if (isoperator(input[0])) {
      line >> oper;

      printf("reading operator %c\n", oper);

      term_2 = terms->top();
      terms->pop();

      if (terms->isEmpty()) {
        printf("too many operators\n");
        exit(0);
      }

      term_1 = terms->top();
      terms->pop();

      int thing = compute_result(term_1, term_2, oper);

      terms->push(thing);
    }
  }

  result = terms->top();

  // checking for too many terms
  terms->pop();

  if (!terms->isEmpty()) {
    printf("too many numbers\n");
    exit(0);
  }

  printf("The result is %i\n", result);

  return result;
}
