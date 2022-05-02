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
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int charToInt(char character) {
  return character - 48;
}

template <class T>
class List {
  private:
    struct Node {
      T data;
      Node *next;
    };
    Node *front, *current;

  public:
    List() {
      front = NULL;
      current = NULL;
    };

    ~List() {};

    void AddToFront(T newthing) {
      Node *temp;
      temp = new Node;
      temp->data = newthing;
      temp->next = front;
      front = temp;
    };

    void Reverse() {
      Node *temp1, *temp2, *temp3;
      temp2=front;
      temp3=front->next;

      while(temp3 != NULL) {
        temp1=temp3->next;
        temp3->next=front;
        front=temp3;
        temp3=temp1;
      }

      temp2->next=NULL;
    }

    void Print() {
      current = front;
      while (true) {
        if (current == NULL) { break; }
        printf("%i", current->data);
        current = current->next;
      }
    }

    bool FirstItem(T & item) {
      if (front == NULL) { return false; }
      item = front->data;
      current = front;
      return true;
    };

    bool NextItem(T & item) {
      if (current == NULL || current->next == NULL) { return false; }

      current = current->next;
      item = current->data;
      return true;
    };
};

class BigNumber {
  private:
    List<int> list;

  public:
  BigNumber() {};

  ~BigNumber() {};

  bool FirstDigit(int &item) {
    bool ok;
    ok = list.FirstItem(item);

    if (!ok) { item = 0; }
    return ok;
  };

  bool NextDigit(int &item) {
    bool ok;
    ok = list.NextItem(item);

    if (!ok) { item = 0; }
    return ok;
  }

  void AddToFront(int digit) {
    list.AddToFront(digit);
  }

  void ReadFromString(string number) {
    for (int i = 0; i < number.size(); i++) {
      if (number[i] == '\n' || number[i] == '\r') { continue; }

      int temp = charToInt(number[i]);
      list.AddToFront(temp);
    }
  }

  void PrintBigNumber() {
    list.Reverse();
    list.Print();
    cout << "\n";
    list.Reverse();
  }

  void Add(BigNumber B1, BigNumber B2) {
    int carry = 0;

    int digitOne;
    int digitTwo;

    bool digitOneOk = B1.FirstDigit(digitOne);
    bool digitTwoOk = B2.FirstDigit(digitTwo);

    while(digitOneOk || digitTwoOk) {
      int partialResult = digitOne + digitTwo + carry;

      AddToFront(partialResult % 10);

      if (partialResult <= 9) {
        carry = 0;
      } else {
        carry = partialResult / 10;
      }

      digitOneOk = B1.NextDigit(digitOne);
      digitTwoOk = B2.NextDigit(digitTwo);
    }

    if (carry != 0) AddToFront(carry);
    list.Reverse();
  }
};


BigNumber B1, B2, RESULT;

int main(int argc, char **argv) {
  string numberstring;
  int stringseq = 0;
  ifstream input_file;

  if (argc == 2) {
    input_file.open(argv[1]);
  } else {
    cout << "cannot read the file " << argv[1] << endl;
    exit(0);
  }

  while (!input_file.eof()) {
    getline(input_file, numberstring);

    if (!input_file.eof()) {
      if (stringseq == 0) {
        B1.ReadFromString(numberstring);
        stringseq = 1;
      } else {
        B2.ReadFromString(numberstring);
      }
    }
  }

  B1.PrintBigNumber();
  cout << "+" << endl;
  B2.PrintBigNumber();
  cout << "=" << endl;
  RESULT.Add(B1, B2);
  RESULT.PrintBigNumber();
}
