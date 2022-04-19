#include <iostream>
#include <unordered_map>
using namespace std;

class DFA {
    int n;
    int **states;
    string *stateNames;
    int startState;
    unordered_map<string, int> isDone;

    void inputNames() {
        cout << "Enter " << this->n  << " names for DFA states." << endl;

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

    void makeDFA() {
        this->inputNames();
        this->inputStartState();
        
        for(int i=0; i<n; i++) {
            cout << endl;
            cout << "----- DETAILS FOR STATE '" << this->stateNames[i] << "' -----" << endl;
            
            // At input 0
            cout << "Enter output state name at input 0 = ";
            string s;
            cin >> s;
            while(this->isDone.count(s) == 0) {
                cout << "No such state present. Enter again = ";
                cin >> s;
            }
            this->states[i][0] = this->isDone[s];
            
            // At input 1
            cout << "Enter output state name at input 1 = ";
            cin >> s;
            while(this->isDone.count(s) == 0) {
                cout << "No such state present. Enter again = ";
                cin >> s;
            }
            this->states[i][1] = this->isDone[s];

            // Final State
            cout << "Is this state a final state?" << endl;
            cout << "Enter 1 for yes, any other for no." << endl;
            int a;
            cin >> a;
            if(a == 1) this->states[i][2] = 1;
            else this->states[i][2] = 0;

            cout << endl;
        }
    }

public:
    DFA() {
        int n;
        cout << "Enter no of states = ";
        cin >> n;
        while(n < 1) {
            cout << "Enter value grater than 0 = ";
            cin >> n;
        }

        this->n = n;
        this->startState = 0;
        
        this->states = new int*[n];
        for(int i=0; i<n; i++) this->states[i] = new int[3];

        this->stateNames = new string[n];

        this->makeDFA();
    }

    ~DFA() {
        for(int i=0; i<this->n; i++) delete[] this->states[i];
        delete[] this->states;
        delete[] this->stateNames;
    }

    void printDFA() const {
        cout << endl;
        cout << "--------------------------" << endl;
        cout << "No of states: " << this->n << endl;
        cout << "Start State: " << this->stateNames[this->startState] << endl;
        for(int i=0; i<n; i++) {
            cout << endl;
            cout << "State " << (i + 1) << endl;
            cout << "Name: " << this->stateNames[i] << endl;
            cout << "Output at 0: " << this->stateNames[this->states[i][0]] << endl;
            cout << "Output at 1: " << this->stateNames[this->states[i][1]] << endl;
            cout << "Final state: " << (this->states[i][2] ? "Yes" : "No") << endl;
        }
        cout << "--------------------------" << endl;
        cout << endl;
    }

    void validateString(string s) const {
        int m = s.size();
        int currState = this->startState, totalStates = 0;
        unordered_map<int, bool> isTraversed;

        cout << endl;
        cout << "Staring from state " << this->stateNames[currState] << endl;

        for(int i=0; i<m; i++) {
            if(s[i] != '0' && s[i] != '1') {
                cout << "Input '" << s[i] << "' is not present in input set {0, 1}." << endl;
                return;
            }
            int inp = s[i] - 48;
            if(isTraversed.count(currState) == 0) totalStates++;
            isTraversed[currState] = true;
            currState = this->states[currState][inp];

            cout << "Input " << inp << " -> State " << this->stateNames[currState] << endl;

            if(this->states[currState][0] == currState && this->states[currState][1] == currState) {
                if(!this->states[currState][2]) {
                    cout << "Dead state reached" << endl;
                    return;
                }
            }
        }

        if(!this->states[currState][2]) {
            cout << "Final state not reached." << endl;
            return;
        }

        cout << "String accepted." << endl;
        cout << "No of unique state traversed is " << totalStates << endl;
    }
};

int main() {
    DFA d1;
    d1.printDFA();

    string s;
    cout << "Enter an string to check = ";
    cin >> s;
    d1.validateString(s);

    return 0;
}