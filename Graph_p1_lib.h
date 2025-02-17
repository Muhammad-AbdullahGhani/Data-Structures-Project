#ifndef GRAPH_P1_LIB_H
#define GRAPH_P1_LIB_H
#pragma once
#include<iostream>
using namespace std;
typedef struct {
    char name[50];
    int index;
} City;
struct Node {
    int city;
    struct Node* next;
};
class Qnode {
public:
    char data;
    Qnode* next;
};
extern double distances[50];
class Queue {
public:
    Qnode* Front;
    Qnode* rear;
    int counter;

    Queue();

    void insertQueue(char data);

    char dequeue();

    bool empty();
};

int hash_func(char* city1, char* city2);
void insert_edge(Node* adj_list[], int src, int dest);
int add_distance(double distances[], char* city1, char* city2, double distance);
int find_distance(double distances[], char* city1, char* city2);
void print_path(int parent[], int src, int dest, City cities[]);
void bfs(Node* adj_list[], int src, int dest, City cities[], int n);

#endif
