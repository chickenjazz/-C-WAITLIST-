#include <iostream>
#include <string>
#include <limits>

#define MAX_WAITING_LIST 10

using namespace std;

void menu();

struct order {
    string food;
    string drink;
    string dessert;
    int orderId;
};

class intQueue {
private:
    order* queueArray;
    int front;
    int rear;
    int numItems;

public:
    intQueue();
    ~intQueue();
    void enqueue(string food, string drink, string dessert);
    void dequeue();
    bool isEmpty();
    bool isFull();
    void clear();
    void displayNext();
    int peek();
    void receipt();
};

intQueue::intQueue() {
    queueArray = new order[MAX_WAITING_LIST];
    front = 0;
    rear = -1;
    numItems = 0;
}

intQueue::~intQueue() {
    delete[] queueArray;
}

void intQueue::enqueue(string food, string drink, string dessert) {
    if (!isFull()) {
        rear = (rear + 1) % MAX_WAITING_LIST;
        queueArray[rear].food = food;
        queueArray[rear].drink = drink;
        queueArray[rear].dessert = dessert;
        queueArray[rear].orderId = rear + 100;
        numItems++;

        cout << "\nORDER ID #" << queueArray[rear].orderId << "\n\n";
        if (numItems == 1) {
            front = rear; //indicate as the first element
        }
    } else {
        cout << "Waiting list is full." << endl;
        system("pause");
    }
}

void intQueue::dequeue() {

    if (!isEmpty()) {
        cout << "Order #" << queueArray[front].orderId << " has been claimed!" << endl;
        front = (front + 1) % MAX_WAITING_LIST;
        numItems--;
        if (numItems == 0) {
            front = 0;
            rear = -1;
        }
    } else {
        cout << "No orders to claim!" << endl;
        system("pause");
    }
}

bool intQueue::isEmpty() {
    return numItems == 0;
}

bool intQueue::isFull() {
    return numItems == MAX_WAITING_LIST;
}

void intQueue::clear() {
    rear = -1;
    front = 0;
    numItems = 0;
}

void intQueue::displayNext() {
    if (numItems <= 1) {
        cout << "No next orders in the queue." << endl;
    } else {
        for (int i = 1; i < numItems; i++) {
            int index = (front + i) % MAX_WAITING_LIST;
            cout << queueArray[index].orderId << endl;
        }
    }
}

int intQueue::peek() {
    if (!isEmpty()) {
        return queueArray[front].orderId;
    }
    return -1; // Return -1 if there are no orders
}

void intQueue::receipt() {
    if (!isEmpty()) {
        cout << "    ORDER SUMMARY: \n\n"
            << "______________________\n"
            << "MEAL: " << queueArray[front].food << endl
            << "DRINKS: " << queueArray[front].drink << endl
            << "DESSERT: " << queueArray[front].dessert << endl
            << "______________________\n"
            << "TOTAL:            $150\n";
    } else {
        cout << "No orders to display!" << endl;
    }
}

int main() {
    int choice;
    intQueue syst;
    string meal, drink, dessert;

    do {
        system("cls");
        cout << "=============================================\n"
            << "        MCJONALD 150's ORDERING SYSTEM\n"
            << "=============================================\n\n"
            << "NOW SERVING: ";
        int currentOrder = syst.peek();
        if (currentOrder != -1) {
            cout << currentOrder << "\n\n";
        } else {
            cout << "No orders.\n\n";
        }
        cout << "NEXT-IN-LINE: \n";
        syst.displayNext();
        cout << "\n\n"
            << "=============================================\n\n"
            << "            [1] ORDER\n" // can add info to the struct order
            << "            [2] CLAIM ORDER\n" // displays order and dequeues
            << "            [3] EXIT\n\n"

            << "choose: ";
        cin >> choice;
         if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid entry! Please enter a number.\n";
            system("pause");
            continue;
        }

        cin.ignore();

        switch (choice) {
            case 1:
                system("cls");

            cout << "=============================================\n"
                    << "        MCJONALD 150's ORDERING SYSTEM\n"
                    << "=============================================\n\n";

                cout << "Enter Meal: ";
                getline(cin, meal);
                cout << "Enter drinks: ";
                getline(cin, drink);
                cout << "Enter dessert: ";
                getline(cin, dessert);
                syst.enqueue(meal, drink, dessert);
                system("pause");
                
                break;
            case 2:
                system("cls");
            cout << "=============================================\n"
                    << "        MCJONALD 150's ORDERING SYSTEM\n"
                    << "=============================================\n\n";

                if (!syst.isEmpty()){
                    syst.receipt();
                    char confirm;

                    cout << "Claim Order? [Y/N]: ";
                    cin >> confirm;
                    confirm = toupper(confirm);

                    if (confirm == 'Y') {
                        syst.dequeue();
                        cout << endl;
                        system("pause");
                    } else if (confirm == 'N') {
                        break;
                    } else {
                        cout << "Invalid choice!\n";
                        system("pause");
                        break;
                    }
                }
                else{
                    cout << "No orders to claim!\n";
                    system("pause");
                }
                break;
            case 3: 
                exit(0);
            default:
                cout << "Invalid entry!\n";
                system("pause");
                system("cls");
            }
    } while (choice != 3);

    return 0;
}
