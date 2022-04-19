#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

class NFA {
    int n;
    int startState;
    int inputSize;
    string *inputs;
    int ***states;
    string *stateNames;
    unordered_map<string, int> isDone;
    unordered_map<string, int> inputSet;

    void takeInputSet() {
        int n;
        cout << "Enter no of inputs in input set = ";
        cin >> n;
        while(n < 2) {
            cout << "Atleast 2 input required = ";
            cin >> n;
        }

        this->inputSize = n;
        this->inputs = new string[n];

        for(int i=0; i<n; i++) {
            cout << "Enter input string " << (i + 1) << " = ";
            string s;
            cin >> s;
            while(this->inputSet.count(s) > 0) {
                cout << "Input is already given. Enter another = ";
                cin >> s;
            }
            this->inputSet[s] = i;
            inputs[i] = s;
        }
    }

    void inputNames() {
        cout << "Enter " << this->n  << " names for NFA states." << endl;

        for(int i=0; i<n; i++) {
            string s;
            cin >> s;
            while(this->isDone.count(s) > 0) {
                cout << "Name is taken. Enter another = ";
                cin >> s;
            }
            this->isDone[s] = i;
            this->stateNames[i] = s;
        }
    }

    void inputStartState() {
        cout << "Enter name of start state = ";
        string s;
        cin >> s;
        while(this->isDone.count(s) == 0) {
            cout << "No such state present. Enter again = ";
            cin >> s;
        }
        this->startState = this->isDone[s];
    }

    void makeNFA() {
        this->inputNames();
        this->inputStartState();
        this->takeInputSet();

        for(int i=0; i<this->n; i++) {
            cout << endl;
            cout << "----- DETAILS FOR STATE '" << this->stateNames[i] << "' -----" << endl;

            this->states[i] = new int*[1 + this->inputSize];

            for(int j=1; j<=this->inputSize; j++) {
                int n;
                cout << "Enter no of output states for input '" << this->inputs[j - 1] << "' = ";
                cin >> n;
                while(n < 0) {
                    cout << "Enter value grater than 0 = ";
                    cin >> n;
                }

                this->states[i][j] = new int[n + 1];
                this->states[i][j][0] = n;

                for(int k=1; k<=n; k++) {
                    cout << "Enter output no " << k << " = ";
                    string s;
                    cin >> s;
                    while(this->isDone.count(s) == 0) {
                        cout << "No such state present. Enter again = ";
                        cin >> s;
                    }
                    this->states[i][j][k] = this->isDone[s];
                }
            }

            this->states[i][0] = new int[1];
            cout << "Is this state a final state?" << endl;
            cout << "Enter 1 for yes, any other for no." << endl;
            int a;
            cin >> a;
            if(a == 1) this->states[i][0][0] = 1;
            else this->states[i][0][0] = 0;

            cout << endl;
        }
    }

    int countStatesInDFA() const {
        unordered_map<string, bool> isCounted;
        int stateCount = 0;
        queue<string> q;

        q.push(this->stateNames[this->startState]);

        while(!q.empty()) {
            stateCount++;
            string s = q.front();
            q.pop();
            isCounted[s] = true;

            for(int i=1; i<=this->inputSize; i++) {
                int *output = this->states[this->isDone[s]]
            }
        }
    }

public:
    NFA() {
        int n;
        cout << "Enter no of states = ";
        cin >> n;
        while(n < 1) {
            cout << "Enter value grater than 0 = ";
            cin >> n;
        }

        this->n = n;
        this->startState = 0;
        
        this->states = new int**[n];
        this->stateNames = new string[n];

        this->makeNFA();
    }

    ~NFA() {
        delete[] this->inputs;
        delete[] this->stateNames;
        for(int i=0; i<this->n; i++) {
            delete[] this->states[i][0];
            for(int j=1; j<=this->inputSize; j++) delete[] this->states[i][j];
            delete[] this->states[i];
        }
        delete[] this->states;
    }

    void printNFA() const {
        cout << endl;
        cout << "--------------------------" << endl;
        cout << "No of states: " << this->n << endl;
        cout << "Start State: " << this->stateNames[this->startState] << endl;
        for(int i=0; i<n; i++) {
            cout << endl;
            cout << "State " << (i + 1) << endl;
            cout << "Name: " << this->stateNames[i] << endl;
            for(int j=1; j<=this->inputSize; j++) {
                cout << "Output at '" << this->inputs[j - 1] << "': ";
                for(int k=1; k<=this->states[i][j][0]; k++) cout << this->stateNames[this->states[i][j][k]] << " ";
                cout << endl;
            }
            cout << "Final state: " << (this->states[i][0][0] ? "Yes" : "No") << endl;
        }
        cout << "--------------------------" << endl;
        cout << endl;
    }

    void convertToDFA() {}
};