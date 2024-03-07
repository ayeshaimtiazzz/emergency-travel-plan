#include "emergency_travel.h"
#include <iostream>

using namespace std;

int main() {
    int choice;
      // You can adjust this based on your needs
    Graph graphQue[MAX_CASES];


    do {
        cout<<"\n**** Flight Emergeny Plan Menu *****\n";
        cout<<"1. Input total cases the cities, routes and required paths \n";
        cout<<"2. Input a Case and Display Graphical Representation\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";
        choice = getValidInput("", 1, 3);

        switch (choice) {
            case 1:
                int num_cases;
                //Take cases input from user
                cout<<"Enter Number of Cases: ";
                cin >> num_cases;

                //inputs and processing for each number of case
                for (int i = 0; i < num_cases; ++i) {
                    // Input a Case and Display Graphical Representation
                    int num_cities, num_air_routes;

                    // take cities and aerial route counts
                    cout<<"Enter number of cities for case "<<i+1<<": ";
                    num_cities = getValidInput("", 2, MAX_CITIES);

                    cout<<"Enter number of aerial routes for case "<<i+1<<": ";
                    num_air_routes = getValidInput("", 0, num_cities * (num_cities - 1) / 2);

                    //create a graph
                    graphQue[i] = Graph(num_cities);
                    createGraphQueue(&graphQue[i]);
                    // Generate sequential road routes
                    const int num_road_routes = num_cities - 1;

                    Route routes[num_road_routes + num_air_routes];

                    // get routes
                    for (int j = 0; j < num_road_routes; ++j) {
                        routes[j] = {0, j, j + 1};  // Road route
                    }

                    // Input user-defined air routes
                    cout<<"\n\nEnter the cities (in number) the source and destination (separated by space)"<<endl;
                    for (int j = 0; j < num_air_routes; ++j) {
                        int air_src, air_dest;
                        cout<<j + 1<<". Source<space>Destination: ";
                        cin >> air_src >> air_dest;

                        // Input validation for air routes
                        while (air_src < 0 || air_src >= num_cities || air_dest < 0 || air_dest >= num_cities || air_src == air_dest) {
                            cout<<"Invalid input. Please enter valid source and destination cities.\n";
                            cout<<j + 1<<". Source<space>Destination: ";
                            cin >> air_src >> air_dest;
                        }

                        routes[num_road_routes + j] = {1, air_src, air_dest};// Air route creation
                        createAerialRoutes(&graphQue[i], air_src, air_dest); // aerial route with que creation
                    }

                    int minimum_days =  minDaysToReachDestination(num_cities, routes, num_road_routes + num_air_routes, &graphQue[i], i);
                    cout<<"Minimum days to reach the destination for case "<<i+1<<": "<<minimum_days<<" days"<<endl;
                }
                break;
            case 2: {

                int num_case;
                //Take case input from user to view the graph representation
                cout<<"Enter Number of Case to view graphical representation: ";
                cin >> num_case;

                num_case = num_case -1; //because we take input from 1 onwards but actual case are saved from 0

                cout<<"\nArial Routes are:  ";
                for (int j = 0; j < graphQue[num_case].cities; j++) {
                    printAirialNodeRoutes(&graphQue[num_case].adjlist[j]);
                }
                // Display graphical representation
                displayGraphWithRoutes(&graphQue[num_case], num_case);

                //Display vertex connections
                displayGraphMatrixConnections(graphQue[num_case].cities);
                //graph matrix representation
                displayGraphMatrix(graphQue[num_case].cities);
                break;
            }
            case 3:
                // Exit
                cout<<"Exiting the system. Goodbye!\n";
                break;
            default:
                cout<<"Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 3);

    return 0;
}
