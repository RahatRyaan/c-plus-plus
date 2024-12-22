#include<iostream>
using namespace std;

#define heavyToll   800;
#define mediumToll  500;
#define lightToll   300;
struct TollInformation {
    string vehicleNumber, vehicleType, date;
    int ticketNumber, vehicleToll;
    
    TollInformation() {
        vehicleNumber = "0";
        vehicleType = "0";
        date = "0";
        ticketNumber = 0;
        vehicleToll = 0;
    }
};

#define MAX_SIZE 100
class Queue {
    int front, rear;
    TollInformation *arr;
public:
    Queue();
    bool isEmpty();
    bool isFull();
    void enqueue(TollInformation);
    void dequeue();
    int size();
    int earingsByDate(string);
    int earingsByCounter();
    TollInformation search(string);
    TollInformation Front();
};
Queue::Queue() {
    front = rear = -1;
    arr = new TollInformation[MAX_SIZE];
}
bool Queue::isEmpty() {
    return (front == -1 && rear == -1);
}
bool Queue::isFull() {
    return ((rear+1)%MAX_SIZE == front);
}
void Queue::enqueue(TollInformation x) {
    if(isFull()) {
        cout << "queue is full\n";
        return;
    }else if(isEmpty()) {
        front = rear = 0;
    }else {
        rear = (rear + 1)%MAX_SIZE;
    }
    arr[rear] = x;
}
void Queue::dequeue() {
    if(isEmpty()) {
        cout << "queue is empty\n";
    }else if(front == rear) {
        front = rear = -1;
    }else {
        front = (front + 1)%MAX_SIZE;
    }
}
int Queue::size() {
    int s = (rear+MAX_SIZE-front)%MAX_SIZE+1;
    return s;
}
int Queue::earingsByDate(string date) {
    int total = 0;
    int n = size();
    for(int i=0; i<n; i++) {
        int index = (front+i)%MAX_SIZE;
        if(arr[index].date == date) {
            total += arr[index].vehicleToll;
        }
    }
    return total;
}
int Queue::earingsByCounter() {
    int total = 0;
    int n = size();
    for(int i=0; i<n; i++) {
        int index = (front+i)%MAX_SIZE;
        total += arr[index].vehicleToll;
    }
    return total;
}
TollInformation Queue::Front() {
    if(isEmpty()) {
        cout << "Error: cannot return front from empty queue\n";
        TollInformation temp;
        return temp;
    }else {
        return arr[front];
    }
}
TollInformation Queue::search(string vNum) {
    TollInformation v;
    int n = size();
    for(int i=0; i<n; i++) {
        int index = (front+i)%MAX_SIZE;
        if(arr[index].vehicleNumber == vNum) {
            v = arr[index];
            break;
        }
    }
    return v;
}

class TollSystem {
    Queue counter01, counter02, counter03;
public:
    bool insertTollInfo(char, TollInformation);
    void addEarnings(int);
    void displayTollInfo(string);
    int displayEarningsByDate(string);
    int displayEarningsByCounter(string);
};
bool TollSystem::insertTollInfo(char counterNo, TollInformation tInfo) {
    bool flag = false;
    if(counterNo == '1') {
        counter01.enqueue(tInfo);
        flag = true;
    }else if(counterNo == '2') {
        counter02.enqueue(tInfo);
        flag = true;
    }else if(counterNo == '3') {
        counter03.enqueue(tInfo);
        flag = true;
    }
    return flag;
}
void TollSystem::displayTollInfo(string vNum) {
    TollInformation v = counter01.search(vNum);
    if(v.vehicleType == "0") {
        v = counter02.search(vNum);
    }
    if(v.vehicleType == "0") {
        v = counter03.search(vNum);
    }
    if(v.vehicleType == "0") {
        cout << "Vechile NOT FOUND!\n";
    }else {
        cout << "\n\tToll Information\n";
        cout << "----------------------------------------\n";
        cout << "Vechile Number : " << v.vehicleNumber << "\n";
        cout << "Vechile Type : " << v.vehicleType << "\n";
        cout << "Ticket Number : " << v.ticketNumber << "\n";
        cout << "Vechile Toll : " << v.vehicleToll << "/-\n";
        cout << "Date : " << v.date << "\n";
        cout << "----------------------------------------\n";
    }
}
int TollSystem::displayEarningsByDate(string date) {
    int total = counter01.earingsByDate(date) + counter02.earingsByDate(date) + counter03.earingsByDate(date);
    return total;
}
int TollSystem::displayEarningsByCounter(string counter) {
    int total = 0;
    if(counter == "1") {
        total = counter01.earingsByCounter();
    }else if(counter == "2") {
        total = counter02.earingsByCounter();
    }else if(counter == "3") {
        total = counter03.earingsByCounter();
    }
    return total;
}

int main() {
    TollSystem tollSystem;
    TollInformation tollInfo;
    int tcNumber = 1; string input;
    cout << "\n\nWELCOME TO PADMA BRIDGE TOLL-BOX\n";
    cout << "\tDhaka-Mawa Highway\n\n";
    bool repeat = true;
    while(repeat) {
        cout << "1. Toll-Box\n2. Show Information\n3. Show Total Earnings\n4. Exit";
        cout << "\nEnter your choice : ";
        char choice; cin >> choice;

        switch(choice) {
            case '1':
                cout << "\nWELCOME TO TOLLBOX\nChoose Vehicle Type :\n";
                cout << "1. Heavy-duty Vehicle\n2. Medium-duty\n3. Light-duty\n";
                cout << "Enter your choice : ";
                char vChoice; cin >> vChoice;
                switch(vChoice) {
                    case '1':
                        cout << "\nCounter 1 For Heavy-duty Vehicle\n";
                        tollInfo.vehicleType = "Heavy-duty";
                        cout << "Enter vehicle number : ";
                        cin >> tollInfo.vehicleNumber;
                        cout << "Enter date : ";
                        cin >> tollInfo.date;
                        tollInfo.vehicleToll = heavyToll;
                        tollInfo.ticketNumber = tcNumber++; 
                        if(tollSystem.insertTollInfo(vChoice, tollInfo)) {
                            cout << "Toll Information Inserted Successfully\n";
                            tollSystem.displayTollInfo(tollInfo.vehicleNumber);
                        }else {
                            cout << "Toll Information Is NOT Inserted\n";
                        }
                        break;
                    case '2':
                        cout << "\nCounter 2 For Medium-duty Vehicle\n";
                        tollInfo.vehicleType = "Medium-duty";
                        cout << "Enter vehicle number : ";
                        cin >> tollInfo.vehicleNumber;
                        cout << "Enter date : ";
                        cin >> tollInfo.date;
                        tollInfo.vehicleToll = mediumToll;
                        tollInfo.ticketNumber = tcNumber++; 
                        if(tollSystem.insertTollInfo(vChoice, tollInfo)) {
                            cout << "Toll Information Inserted Successfully\n";
                            tollSystem.displayTollInfo(tollInfo.vehicleNumber);
                        }else {
                            cout << "Toll Information Is NOT Inserted\n";
                        }
                        break;
                    case '3': 
                        cout << "\nCounter 3 For Light-duty Vehicle\n";
                        tollInfo.vehicleType = "Light-duty";
                        cout << "Enter vehicle number : ";
                        cin >> tollInfo.vehicleNumber;
                        cout << "Enter date : ";
                        cin >> tollInfo.date;
                        tollInfo.vehicleToll = lightToll;
                        tollInfo.ticketNumber = tcNumber++; 
                        if(tollSystem.insertTollInfo(vChoice, tollInfo)) {
                            cout << "Toll Information Inserted Successfully\n";
                            tollSystem.displayTollInfo(tollInfo.vehicleNumber);
                        }else {
                            cout << "Toll Information Is NOT Inserted\n";
                        }
                        break;
                    default :
                        cout << "Invalid Choice\n";
                        break;
                }
                break;
            case '2':
                cout << "\nShow Information For Vehicle\n";
                cout << "Enter vehicle number to show information :\n";
                cin >> input;
                tollSystem.displayTollInfo(input);
                break;
            case '3':
                cout << "\nShow Total Earnings\n";
                cout << "1. Earnings by date\n2. Earings by counter\n";
                cin >> input;
                if(input == "1") {
                    cout << "Enter date : ";
                    cin >> input;
                    cout << "\nDate : " << input << "\n";
                    cout << "\nTotal Earnings : " << tollSystem.displayEarningsByDate(input) << "\n";
                }else if(input =="2") {
                    cout << "Enter counter number : ";
                    cin >> input;
                    if(input == "1" || input =="2" || input == "3"){
                        tollSystem.displayEarningsByCounter(input);
                        cout << "\nCounter number : " << input << "\n";
                        cout << "\nTotal Earnings : " << tollSystem.displayEarningsByCounter(input) << "\n";
                    }else {
                        cout << "No such counter exists!\n";
                    }
                }else {
                    cout << "Invalid Choice\n";
                }
                break;
            case '4': 
                cout << "Thanks for using our service\n";
                cout << "\nBangladesh\n";
                repeat = false;
                break;
            default :
                cout << "Invalid Choice\n";
                break;
        }
    }

    return 0;
}