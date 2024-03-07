
#ifndef EMERGENCY_TRAVEL_H
#define EMERGENCY_TRAVEL_H

#include <iostream>

using namespace std;

const int MAX_CITIES = 1000;
const int MAX_CASES = 10;
struct Route {
    int type;  // 0 for road, 1 for air
    int source;
    int destination;
};

struct node
{
    int cityno;
    node *road;
    node *aerial;

    node()
    {
        cityno = -1;
        road = nullptr;
        aerial = nullptr;
    }
    node(int c)
    {
        cityno = c;
        road = nullptr;
        aerial = nullptr;
    }
};

struct Queue
{
    int front;
    int rear;
    int array[100];
    Queue()
    {
        front = -1;
        rear = -1;
        for(int i=0;i<100;i++)
        {
            array[i]=-1;
        }
    }
};


struct Graph
{
    int cities;
    node *adjlist;

    Graph()
    {
        cities = 0;
        adjlist = nullptr;
    }
    Graph(int c)
    {
        cities = c;
        adjlist = new node[cities];
    }
};

int bfs(int num_cities,Graph *graphQue, int num_case);
int minDaysToReachDestination(int num_cities, const Route* routes, int num_routes, Graph *graphQue, int num_case);
int getValidInput(const string& prompt, int minVal, int maxVal);

void displayGraphMatrix(int num_cities);


void enqueue(Queue *q, int p);
bool isEmpty(Queue *q);
void dequeue(Queue *q);
void createGraphQueue(Graph *graphQue);
void printRoadNodeRoutes(node *head);
void printAirialNodeRoutes(node *head);
void createAerialRoutes(Graph *graphQue, int source, int destination);
void displayGraphMatrixConnections(int num_cities);
void displayGraphWithRoutes(Graph *graphQue, int num_case);



#endif // EMERGENCY_TRAVEL_H
