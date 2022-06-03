// Raquel Moss
// ID: 22001105
// Hello!
// Thank you for marking my assignment.
// I'm not proud of this code, it's definitely not my best. It works, but I know there are several
// inefficiencies and poor use of c++ paradigms and language features. Unfortunately I've been
// completely swamped at work this week and haven't been able to dedicate as much time to this
// assignment as I would have liked to.
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstring>

using namespace std;

int MAX = std::numeric_limits<signed int>::max();

struct Node {
  char key;
  int distance;
  Node *next;
};

struct GraphNode {
  char key;
  Node *listpointer;
};

class Graph {
  private:
    vector<GraphNode> adjacency_list;
  public:
    Graph(){};

    ~Graph(){};

    GraphNode* At(int position) {
      return &adjacency_list[position];
    }

    int IndexOf(char key) {
      int found = -1;

      for (int i = 0; i < adjacency_list.size(); i++) {
        if (adjacency_list.at(i).key == key) {
          found = i;
          break;
        }
      }

      return found;
    }

    int Size() {
      return adjacency_list.size();
    }

    void AddNewGraphNode(char new_graph_node) {
      GraphNode temp;
      temp.key = new_graph_node;
      temp.listpointer = NULL;

      adjacency_list.push_back(temp);
    };

    void AddNewEdgeBetweenGraphNodes(char A, char B, int distance) {
      int a;
      for (a = 0; adjacency_list.size(); a++) {
        if (A == adjacency_list[a].key) break;
      }

      AddNode(adjacency_list[a].listpointer, B, distance);
    };

    void AddNode(Node *&listpointer, char key, int distance) {
      Node *temp;
      temp = new Node;
      temp->key = key;
      temp->distance = distance;
      temp->next = listpointer;
      listpointer = temp;
    };
};

int indexofSmallestElement(int d[], int states[], int size) {
  int index = 0;
  int n = MAX;
  for (int i = 1; i < size; i++) {
    if (d[i] < n && states[i] == 0) {
      n = d[i];
      index = i;
    }
  }
 return index;
}

void dijkstra(Graph* graph, GraphNode* source_node) {
  int size = graph->Size();
  int d[size];
  int states[size];

  GraphNode* current = source_node;

  d[0] = 0;
  states[0] = 1;

  for (int i = 0; i < size; i++) {
    GraphNode* node = graph->At(i);

    if (node == NULL || node->key == '\0') { continue; }
    if (node == source_node) { continue; }

    d[(int)node->key - 65] = MAX;
    states[(int)node->key - 65] = 0;
  }

  int permanent_states_count = 0;

  while (permanent_states_count < size) {
    Node* neighbour = current->listpointer;

    while (true) {
      if (neighbour == NULL) { break; }
      if (neighbour->key == current->key) { continue; }

      d[(int)neighbour->key - 65] = min(d[(int)neighbour->key - 65], d[(int)current->key - 65] + neighbour->distance);
      neighbour = neighbour->next;
    }

    int smallest_distance = indexofSmallestElement(d, states, size);
    int smallest_distance_graph_index = graph->IndexOf(smallest_distance + 65);
    current = graph->At(smallest_distance_graph_index);

    states[current->key - 65] = 1;

    permanent_states_count++;
  }

  for (int i = 0; i <= size; i++)  {
    int index = graph->IndexOf((char)i + 65);
    GraphNode* node = graph->At(index);

    if (node->key == 'A') { continue; }
    if (node == NULL || node->key == '\0') { continue; }

    cout << "From A to " <<  node->key << ":" << d[i] << endl;
  };
}

int main(int argc, char** argv) {
  string expression;
  ifstream input_file;
  string token;
  Graph graph;
  if (argc != 2) {
    cout<< "Type a file name. " << endl << argv[1] << endl;
    exit(0);
  }

  input_file.open(argv[1]);

  if (input_file.is_open() == false) {
    cout << "Could not read file: " << endl << argv[1] << endl;
    exit(0);
  }

  while (!input_file.eof()) {
    getline(input_file, expression);
    stringstream line(expression);

    if (input_file.eof()) break;
    if (expression[0] == '#') continue;

    if (expression[0] == 'N' && expression[1] == 'o') {
      char node_name;

      getline(line, token, ' ');
      getline(line, token, ' ');

      node_name = (token.c_str())[0];

      graph.AddNewGraphNode(node_name);
    } else {
      char nodefrom;
      char nodeto;
      int cost;

      getline(line, token, ' ');
      nodefrom = (token.c_str())[0];

      getline(line, token, ' ');
      nodeto = (token.c_str())[0];

      getline(line, token, ' ');
      cost = atoi(token.c_str());

      graph.AddNewEdgeBetweenGraphNodes(nodefrom, nodeto, cost);
    }
  }

  int source_node_index = graph.IndexOf('A');
  GraphNode* source_node = graph.At(source_node_index);
  dijkstra(&graph, source_node);
}
