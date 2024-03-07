
#include "emergency_travel.h"
#include <iostream>
#include <limits>
using namespace std;

int graphMatrix[MAX_CITIES][MAX_CITIES];//initialize the graph matrix
// cityQue array
int cityQueue[MAX_CASES][MAX_CITIES * 3];
// Initialize front and rear for each case
int frontCity[MAX_CASES] = {0}, rearCity[MAX_CASES] = {0};

void enqueue(Queue *q, int p)
{
    if (q->rear == 99)
    {
        cout<<"QUEUE IS FULL"<<endl;
    }
    q->rear = q->rear + 1;
    q->array[q->rear] = p;
}

bool isEmpty(Queue *q)
{
    if (q->rear == -1)
    {
        cout<<"QUEUE IS EMPTY"<<endl;
        return 1;
    }
    return 0;
}

void dequeue(Queue *q)
{
    if (!isEmpty(q))
    {
        q->front = q->front + 1;
    }
}

void createAerialRoutes(Graph *graphQue, int source, int destination)
{
    graphQue->adjlist[source].aerial = &graphQue->adjlist[destination];
}
void printRoadNodeRoutes(node *head)
{

    node *temp = head;
    temp = head->road;
    while (temp != nullptr)
    {
        cout<<temp->cityno<<"--->";
        temp = temp->road;
    }
}
void printAirialNodeRoutes(node *head)
{

    node *temp = head;
    node *temp1 = head;

    temp = head->aerial;
    if (temp != nullptr)
    {
        cout<<temp1->cityno<<"-.->";
        while (temp != nullptr)
        {
            cout<<temp->cityno<<endl;
            temp = temp->aerial;
        }
    }
}

bool presentinq(Queue *q,int no)
{
    for(int i=0;i<100;i++)
    {
        if(q->array[i]==no)
        return true;
        else
        {
            return false;
        }
    }
}

void createGraphQueue(Graph *graphQue) {
    for (int j = 0; j < graphQue->cities; j++) {
        graphQue->adjlist[j].cityno = j;
    }

    for (int j = 0; j < graphQue->cities; j++) {
        graphQue->adjlist[j].road = new node(j + 1);
    }
    graphQue->adjlist[graphQue->cities - 1].road = nullptr; // Last city's road leads to nullptr

    cout<<graphQue->adjlist[0].cityno<<"--->";
    for (int j = 0; j < graphQue->cities; j++) {
        printRoadNodeRoutes(&graphQue->adjlist[j]);
    }
}

void displayGraphMatrixConnections(int num_cities) {
    cout<<"Graphical Representation of cities vertex connection with Routes:\n";

    for (int i = 0; i < num_cities; ++i) {
        cout<<"Vertex "<<i<<" is connected to: ";

        for (int j = 0; j < num_cities; ++j) {
            if (graphMatrix[i][j] == 1) {
                cout<<i<<"--->"<<j<<"(Road) ";
            } else if (graphMatrix[i][j] == 2) {
                cout<<i<<"-.->"<<j<<"(Arial) ";
            }
        }

        cout<<endl;
    }
}


void displayGraphWithRoutes(Graph *graphQue, int num_case) {

    //1st implementation with
    cout<<"\nGraphical Representation of cityQueue with Routes:\n";
    for (int i = 0; i < rearCity[num_case]; i += 3) {
        int currentCity = cityQueue[num_case][i];
        int days = cityQueue[num_case][i + 1];
        int travel = cityQueue[num_case][i + 2];

        cout<<"Day "<<days<<": ";
        cout<<"City "<<currentCity<<" ";

        if (travel == 0) {
            // Display road route with a straight line
            if (i + 3 < rearCity[num_case]) {
                int nextCity = cityQueue[num_case][i + 3];
                cout<<"---> ";
            }
        } else {
            // Display aerial route with a dotted line
            if (i + 3 < rearCity[num_case]) {
                int nextCity = cityQueue[num_case][i + 3];
                cout<<"-.-> ";
            }
        }
    }

    //2nd implementation with graphQue
    cout<<"\nGraphical Representation of GraphQue with routes:\n";

    for (int i = 0; i < graphQue->cities; ++i) {
        cout<<"City "<<graphQue->adjlist[i].cityno<<": ";

        // Display road routes
        node *roadNode = graphQue->adjlist[i].road;
        while (roadNode != nullptr) {
            cout<<roadNode->cityno<<"(Road) ";
            roadNode = roadNode->road;
        }

        // Display aerial routes
        node *aerialNode = graphQue->adjlist[i].aerial;
        if (aerialNode != nullptr) {
            cout<<"-.-> ";
            while (aerialNode != nullptr) {
                cout<<aerialNode->cityno<<"(Aerial) ";
                aerialNode = aerialNode->aerial;
            }
        }

        cout<<endl;
    }

}


int bfs(int num_cities, Graph *graphQue, int num_case) {

    // Arrays to store {city, days, travel} triplets
    cityQueue[num_case][rearCity[num_case]++] = 0;  // Starting from city 0
    cityQueue[num_case][rearCity[num_case]++] = 0;  // Initial days
    cityQueue[num_case][rearCity[num_case]++] = 0;  // Initial travel count

    // when frontCity ++ deque to temp citque array
    // when rearCity ++ enqque to temp citque array
    while (frontCity[num_case] < rearCity[num_case]) {
        int currentCity = cityQueue[num_case][frontCity[num_case]++];
        int days = cityQueue[num_case][frontCity[num_case]++];
        int travel = cityQueue[num_case][frontCity[num_case]++];

        if (currentCity == num_cities - 1) {
            return (travel == 0 ? days : days + 1);  // Reached the destination
        }
        for (int neighbor = 0; neighbor < num_cities; ++neighbor) {
            //when checking with 1 it is for road
            if (graphMatrix[currentCity][neighbor] == 1) {
                if (travel == 5) {
                    cityQueue[num_case][rearCity[num_case]++] = neighbor;
                    cityQueue[num_case][rearCity[num_case]++] = days + 1;
                    if(neighbor != num_cities - 1){
                        cityQueue[num_case][rearCity[num_case]++] = 0;  // Road route, reset travel count
                    }else{
                        cityQueue[num_case][rearCity[num_case]++] = 1;
                    }

                } else {
                    cityQueue[num_case][rearCity[num_case]++] = neighbor;
                    cityQueue[num_case][rearCity[num_case]++] = days;
                    cityQueue[num_case][rearCity[num_case]++] = travel + 1;  // Road route, increment travel count
                }
            }

            //when checking by 2 it is for arial
            //when he reaches city by aerial route he has end of day
            if (graphMatrix[currentCity][neighbor] == 2) {
                cityQueue[num_case][rearCity[num_case]++] = neighbor;
                if(travel > 0 || currentCity ==0){
                    cityQueue[num_case][rearCity[num_case]++] = days + 1;
                }
                else{
                    cityQueue[num_case][rearCity[num_case]++] = days;
                }
                cityQueue[num_case][rearCity[num_case]++] = 0;  // Air route, reset travel count
            }
        }
    }

    //2nd implementation with graphQue
    Queue q;

    enqueue(&q, 0);  // Starting from city 0
    enqueue(&q, 0);  // Initial days
    enqueue(&q, 0);  // Initial travel count

    while (!isEmpty(&q)) {
        int currentCity = q.array[q.front];
        dequeue(&q);
        int days = q.array[q.front];
        dequeue(&q);
        int travel = q.array[q.front];
        dequeue(&q);

        if (currentCity == num_cities - 1) {
            return (travel == 0 ? days : days + 1);  // Reached the destination
        }

        for (int neighbor = 0; neighbor < num_cities; ++neighbor) {
            if (graphQue->adjlist[currentCity].road != nullptr) {
                if (!presentinq(&q, neighbor)) {
                    enqueue(&q, neighbor);
                    enqueue(&q, days);
                    enqueue(&q, travel + 1);
                }
            }

            if (graphQue->adjlist[currentCity].aerial != nullptr) {
                if (travel > 0 || currentCity == 0) {
                    enqueue(&q, neighbor);
                    enqueue(&q, days + 1);
                    enqueue(&q, 0);  // Air route, reset travel count
                }
            }
        }
    }

    //frontCity[num_case] = front, rearCity[num_case] = rear;
    return -1; // Return -1 if not possible to reach the destination
}

int minDaysToReachDestination(int num_cities, const Route* routes, int num_routes, Graph *graphQue, int num_case) {
    //we create matrix to find min days (the mmatrix is bal it is used in bfs method)
    //initialize the graph matrix with matrix num_cities X num_cities
    for(int i = 0; i < num_cities; i++) {
        for(int j = 0; j < num_cities; j++) {
            graphMatrix[i][j] = 0; // Set the value to 0
        }
    }

    //here in matrix we distinguish road and air routes with 1 and 2 all rest are 0
    for (int i = 0; i < num_routes; ++i) {
        const Route& route = routes[i]; //routes from main function
        if (route.type == 0) {
            graphMatrix[route.source][route.destination] = 1;  // Road route
        } else {
            graphMatrix[route.source][route.destination] = 2;  // Air route
        }
    }

    //traverse the graph by BFS to explore cities and reach destination within specified constraint
    return bfs(num_cities, graphQue, num_case);
}

void displayGraphMatrix(int num_cities) {
    cout<<"\nGraphical Representation:\n";
    for (int i = 0; i < num_cities; ++i) {
        for (int j = 0; j < num_cities; ++j) {
            cout<<graphMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

// Function to handle input validation
int getValidInput(const string& prompt, int minVal, int maxVal) {
    int input;
    while (true) {
        cout<<prompt;
        cin >> input;

        if (cin.fail() || input < minVal || input > maxVal) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout<<"Invalid input. Please enter a valid value between "<<minVal<<" and "<<maxVal<<".\n";
        } else {
            break;
        }
    }
    return input;
}
