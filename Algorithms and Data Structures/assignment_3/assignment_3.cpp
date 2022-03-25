// Hello Ryan
// I am very sad.
//
// Okay, first thing to know is that I didn't write most of the code. It's the skeleton
// they gave us, which is why the spacing and indentaiton is so chaotic and everything is
// wild.
//
// Usually I re-write the skeletons into something more useable, but because they don't give
// specs and so when I tried that this time, I accidentally introduced a bug.
//
// So, fuck it, we're rolling with the bad skeleton.
// There's also a lot of comments in the skeleton. Ones actually written by me are marked
// with "// *"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
using namespace std;

// * I implemented the Node and Queue
struct Node {
  float data;
  Node *next;
};

class Queue {
  private:
    Node *front, *rear;
    int length;
  public:
    Queue() {
      length = 0;
      front = NULL;
      rear = NULL;
    };

    ~Queue() { };

    void Join(float new_item) {
      Node *temp;
      temp = new Node;
      temp->data = new_item;
      temp->next = NULL;

      if (rear != NULL) { rear->next = temp; }
      rear = temp;
      if (front == NULL) { front = temp; }

      ++length;
    };

    void Leave() {
      if (isEmpty()) { return; }
      length = length - 1;

      Node * temp;
      if (front == NULL) { return; }
      temp = front;
      front = front->next;
      if (front == NULL) { rear = NULL; }
      delete temp;
    };

    float Front() {
      return front->data;
    };

    int Length() {
      return length;
    }

    bool isEmpty() {
      if (front == NULL) { return true; }
      return false;
    };
};




////////////////////////////////////////////////////////////////////////

#define TIMEDELAY 3 //DO NOT CHANGE THIS VALUE!!!
#define N 128 //DO NOT CHANGE THIS VALUE!!!
int OutQueues_current[N];
int Congestion_Size[N];

/*include your array of queues declarations somewhere here, for example: */
Queue InputQueues[N];
Queue OutputQueues[N];

void init_simulation(){
  for(int a=0;a<N;a++){
    OutQueues_current[a]=0;
    Congestion_Size[a]=0;
  }
}

int sum_elements_array(int array[]){
  int sum=0;
  for(int a=0;a<N;a++){
    sum=sum+array[a];
  }
  return sum;
}

int number_of_ports=0;

int main(int argc, char** argv){//get arguments from command line, the name of the simulation text file
  //read the file, print the input ports contents
  int portnumber=0;
  int destination=0;
  //char oper;
  string expression;
  string geninput;
  ifstream input_file;
  if(argc!=2) {cout<< "Type a file name. " << endl << argv[1] << endl; exit(0);}
  input_file.open(argv[1]);
  if(input_file.is_open()==false) {cout << "Could not read file: " << endl << argv[1] << endl; exit(0);}
  string token;
  while(!input_file.eof()){
     getline(input_file,expression);
     stringstream line(expression);
     if(input_file.eof()) break;
     if(expression[0] =='#') continue;//jump line, this is a line of comments
     if(expression[0] =='P') {
       getline(line, token,' ');
       getline(line, token,' ');
       number_of_ports=atoi(token.c_str());
       continue;
     }

     // * very chaotic as to whether we're dealing with port numbers (starting at 1)
     // * or array indexes in the array of ports (starting at 0). Who fucking knows.
     portnumber++;

     cout << "Port " << portnumber << ": " << endl;//DEBUG, comment for final version

     while(getline(line, token,' ')){
       int destination;
       destination = atoi(token.c_str());//use this one if your compiler is not C++11
       if (destination < 0 || destination > number_of_ports || number_of_ports<portnumber) {cout << "ERROR in the format of the text file" << endl; exit(0);}

       // * hey look finally some code I wrote. Just adding an item to the input queue.
       InputQueues[portnumber].Join(destination);
     }
     int sumofinputpackets=0;
     // * And checking the length of the queues, this is just for debugging I think,
     // * Idk, this skeleton is dumb
     sumofinputpackets += InputQueues[portnumber].Length();
     cout<< "Input packets at input queue for port "<< portnumber << " = " << sumofinputpackets << endl;//DEBUG, comment for final version
     cout<< "if this value is still zero, it is because you did not implement the queues yet..." << endl;//DEBUG, comment for final version
  }

  //now carry on with the simulation
  cout << endl << "Start of the simulation, press a key " << endl << endl;//DEBUG, comment for final version
  getline(cin, geninput);// pause //DEBUG, comment for final version
  init_simulation();
  unsigned long int clock=0;
  unsigned long int currentsum=99999999;//sum_elements_array(OutQueues_current);
  portnumber=0;

  while (currentsum > 0) {
    // cout << "Input portnumber " << portnumber+1 << endl;//DEBUG, comment for final version
    portnumber++;
    if(portnumber > (number_of_ports-1)) portnumber=0;

    // * here's some code from me
    if (!InputQueues[portnumber].isEmpty()){
      // * The trouble that I'm running into is that even after I add
      // * something to the queue with Join() in this while loop,
      // * it doesn't seem to add properly/the length doesn't increment
      // * and I don't know why.
      // * I've tried various access by value/reference/assigning to a variable
      // * and I'm lost.
      int destination = InputQueues[portnumber].Front();
      Queue &output_queue = OutputQueues[destination];

      // join the output queue
      output_queue.Join(destination);
      cout << "length? " << output_queue.Length() << endl;

      // * update the current total for the output queue. OutQueues_current is terribly named.
      OutQueues_current[destination] = OutputQueues[destination].Length();
      // * leave the input queue
      OutputQueues[destination].Leave();
    }

    clock++;

    if(clock % (TIMEDELAY*number_of_ports) == 0 && clock!=0) { //DO NOT MODIFY THIS LINE!
      cout << "Packets can leave the output queues at " << clock << " microsec " << endl;//DEBUG, comment for final version
      for(int a=0;a<number_of_ports;a++){
        //Delete 1 packet from each queue and count number of packets again
        OutputQueues[a].Leave();

        /* and count number of packets again */
        Congestion_Size[a] = OutputQueues[a].Length();
      }
    }
    //
    // include the queue updates for the simulation
    //
    //
    //compute the current state of the output queues
    // cout << "Current sum: " << currentsum << endl;//DEBUG, comment for final version
    /* currentsum = sum_elements_array(OutQueues_current); */

    if(currentsum > sum_elements_array(Congestion_Size)){
      for(int a=0;a<number_of_ports;a++){
        Congestion_Size[a]=OutQueues_current[a];
      }
    }
  }
  //FINAL PRINTOUT, remember to comment out all the other debugging printouts above
  for(int a=0;a<number_of_ports;a++){
    cout << "output port " << a+1 << ": " << Congestion_Size[a] << " packets" << endl;
  }
}
