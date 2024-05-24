#include "Graph_p1_lib.h"
double distances[50] = { 0 };
Queue::Queue() {
    Front = NULL;
    rear = NULL;
    counter = 0;
}

void Queue::insertQueue(char data) {
    Qnode* newnode = new Qnode;
    newnode->data = data;
    if (empty()) {
        Front = newnode;
    }
    else {
        rear->next = newnode;
    }
    rear = newnode;
    counter++;
}

char Queue::dequeue() {
    if (empty()) {
        cout << "Queue is empty" << endl;
        return '\0';
    }
    Qnode* temp = Front;
    char item = Front->data;
    Front = Front->next;
    delete temp;
    counter--;
    return item;
}

bool Queue::empty() {
    return counter == 0;
}

int hash_func(char* city1, char* city2) {
    int sum1 = 0;
    for (int i = 0; city1[i] != '\0'; i++) {
        sum1 = sum1 + city1[i];
    }
    int sum2 = 0;
    for (int j = 0; city2[j] != '\0'; j++) {
        sum2 = sum2 + city2[j];
    }
    int result = sum1 + sum2;
    return result % 50;
}

void insert_edge(Node* adj_list[], int src, int dest) {
    Node* newnode = new Node();
    newnode->city = dest;
    newnode->next = adj_list[src];
    adj_list[src] = newnode;
}

int add_distance(double distances[], char* city1, char* city2, double distance) {
    int key = hash_func(city1, city2);
    cout << "Adding distance between " << city1 << " and " << city2 << " with key: " << key << endl;
    if (distances[key] != -1) {
        cout << "Distance already exists for key " << key << ": " << distances[key] << endl;
    }
    ::distances[key] = distance;  // Accessing global distances array
    cout << "Distance set for key " << key << ": " << distance << endl;
    return static_cast<int>(distance);
}

int find_distance(double distances[], char* city1, char* city2) {
    int key = hash_func(city1, city2);
    cout << "Finding distance between " << city1 << " and " << city2 << " with key: " << key << endl;
    if (::distances[key] != -1) {  // Accessing global distances array
        cout << "Distance found for key " << key << ": " << ::distances[key] << endl;
        return static_cast<int>(::distances[key]);
    }
    else {
        cout << "Distance not found for key " << key << endl;
        return -1;
    }
}

void print_path(int parent[], int src, int dest, City cities[]) {
    if (parent[dest] == -1) {
        cout << "No path exists between " << cities[src].name << " and " << cities[dest].name << endl;
        return;
    }
    int path_index = 0;
    int* path = new int[10];
    for (int i = dest; i != -1; i = parent[i], path_index++) {
        path[path_index] = i;
    }
    cout << "Names of cities: " << cities[src].name << " " << cities[dest].name << endl;
    for (int j = path_index - 1; j >= 0; j--) {
        cout << "Cities between the path are " << cities[path[j]].name << endl;
    }
    int opt = 0;
    cout << "Press 1 to find distance between cities else press 0" << endl;
    cin >> opt;

    double total_distance = 0;
    if (opt == 1) {

        for (int j = path_index - 1; j > 0; j--) {
            total_distance += find_distance(::distances, cities[path[j]].name, cities[path[j - 1]].name);  // Accessing global distances array
        }
        cout << "Distance between the two cities: " << total_distance << endl;
    }


    delete[] path;
}

void bfs(Node* adj_list[], int src, int dest, City cities[], int n) {
    bool* visited = new bool[50];
    int* parent = new int[50];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        parent[i] = -1;
    }
    Queue q;
    q.insertQueue(src);
    visited[src] = true;
    while (!q.empty()) {
        int u = q.dequeue();
        Node* aj = adj_list[u];
        while (aj) {
            int s = aj->city;
            if (!visited[s]) {
                q.insertQueue(s);
                visited[s] = true;
                parent[s] = u;
                if (aj->city == dest) {
                    print_path(parent, src, dest, cities);
                    return;
                }
            }
            aj = aj->next;
        }
    }
    print_path(parent, src, dest, cities);
}
