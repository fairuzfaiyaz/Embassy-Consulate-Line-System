// Embassy Consulate Line System Assignment
// File name: 23-54707-3.cpp
// NAME: FAIRUZ FAIYAZ <> DATA STRUCTURE LAB[T] <> 
// Description: Implements a visa queue system for an embassy with 4 counters and 4 visa types.

#include <iostream>  // Include standard input/output library
using namespace std; // Use standard namespace

// Constants for limits
const int MAX_APPLICANTS_PER_TYPE = 25; // Maximum applicants each visa type can handle daily
const int MAX_TOTAL_APPLICANTS = 100;   // Total maximum applicants across all types daily

// Struct to store individual token info
struct Token {
    string visaType; // Stores visa type (TR, MED, BS, GO)
    int number;      // Unique token number (e.g., TR-1, MED-2)
};

// Simple queue implementation using array
struct Queue {
    Token tokens[MAX_APPLICANTS_PER_TYPE]; // Array to store tokens
    int front = 0; // Index of first element in queue
    int rear = 0;  // Index where next element will be added
    int count = 0; // Current number of elements in queue

    // Add token to end of queue
    bool enqueue(Token t) {
        if (count >= MAX_APPLICANTS_PER_TYPE) return false; // Check if queue is full
        tokens[rear++] = t;  // Add token and move rear forward
        count++;             // Increase element count
        return true;
    }

    // Remove and return token from front of queue
    Token dequeue() {
        if (count == 0) return { "", -1 }; // Check if queue is empty
        Token t = tokens[front++]; // Get front token and move front forward
        count--;                    // Decrease element count
        return t;
    }

    // Check if queue has no elements
    bool isEmpty() { return count == 0; }

    // Get current number of elements in queue
    int size() { return count; }

    // View front element without removing it
    Token peek() {
        if (count == 0) return { "", -1 }; // Check if empty
        return tokens[front]; // Return front element
    }
};

// Create separate queues for each visa type
Queue trQueue, medQueue, bsQueue, goQueue;

// Counter structure to manage service counters
struct Counter {
    string primaryVisa;      // Main visa type this counter handles
    int served = 0;          // Number of applicants served
    string servedTypes[100]; // Array to store types of served tokens
    int servedTokens[100];   // Array to store served token numbers
};

// Array of 4 counters (one for each visa type)
Counter counters[4];

// Global variables tracking system state
int globalTokenNumber = 1;     // Sequential token number starting from 1
int totalApplicants = 0;       // Total tokens issued today
int visaTypeCounts[4] = { 0 }; // Count of served applicants per visa type [TR, MED, BS, GO]

// Helper function to get queue based on visa type string
Queue* getQueue(string type) {
    if (type == "TR") return &trQueue;
    if (type == "MED") return &medQueue;
    if (type == "BS") return &bsQueue;
    if (type == "GO") return &goQueue;
    return nullptr; // Return null for invalid types
}

// Convert visa type string to array index (TR->0, MED->1, etc.)
int getVisaIndex(string type) {
    if (type == "TR") return 0;
    if (type == "MED") return 1;
    if (type == "BS") return 2;
    if (type == "GO") return 3;
    return -1; // Invalid index for unknown types
}

// Set up counters with their default visa types
void initializeCounters() {
    counters[0].primaryVisa = "TR"; // Counter 1 handles Tourist
    counters[1].primaryVisa = "MED"; // Counter 2 handles Medical
    counters[2].primaryVisa = "BS"; // Counter 3 handles Business
    counters[3].primaryVisa = "GO"; // Counter 4 handles Government
}

// Handle new token requests from applicants
void requestToken(string visaType) {
    // Check daily total limit
    if (totalApplicants >= MAX_TOTAL_APPLICANTS) {
        cout << "Daily limit reached." << endl;
        return;

    }

    Queue* q = getQueue(visaType); // Get correct queue
    // Check type-specific limit
    if (q->size() >= MAX_APPLICANTS_PER_TYPE) {
        cout << "Daily limit reached for " << visaType << " visa." << endl;
        return;
    }

    // Create and enqueue new token
    Token t = { visaType, globalTokenNumber++ };
    q->enqueue(t);
    totalApplicants++; // Update total tokens issued

    cout << "Your token is: " << visaType << "-" << t.number << endl;
}

// Process serving from a specific queue
void serveFromQueue(Counter& counter, Queue* q, int index) {
    if (!q->isEmpty()) {
        Token t = q->dequeue(); // Get next token
        // Record served token details
        counter.servedTokens[counter.served] = t.number;
        counter.servedTypes[counter.served] = t.visaType;
        counter.served++; // Increment counter's served count

        // Update visa type statistics
        int visaIndex = getVisaIndex(t.visaType);
        visaTypeCounts[visaIndex]++;

        cout << "Counter " << index + 1 << ", Please serve the token number \""
            << t.visaType << "-" << t.number << "\"" << endl;
    }
    else {
        cout << "Counter " << index + 1 << ": No applicants in this queue." << endl;
    }
}

// Handle next customer service for a counter
void callNextCustomer(int counterIndex) {
    Counter& counter = counters[counterIndex];
    Queue* primary = getQueue(counter.primaryVisa);

    // First try serving from primary queue
    if (!primary->isEmpty()) {
        serveFromQueue(counter, primary, counterIndex);
        return;
    }

    // If primary queue empty, find longest other queue
    Queue* candidates[4] = { &trQueue, &medQueue, &bsQueue, &goQueue };
    int longest = -1;
    int maxSize = 0;

    // Search for longest non-primary queue
    for (int i = 0; i < 4; ++i) {
        if (counters[counterIndex].primaryVisa == counters[i].primaryVisa) continue;
        if (candidates[i]->size() > maxSize) {
            maxSize = candidates[i]->size();
            longest = i;
        }
    }

    // Serve from longest queue if found
    if (longest != -1) {
        serveFromQueue(counter, candidates[longest], counterIndex);
    }
    else {
        cout << "Counter " << counterIndex + 1 << ": No applicants remaining to serve." << endl;
    }
}

// Generate end-of-day statistics report
void generateSummaryReport() {
    cout << "\n    Daily Summary Report \n" << endl;

    string visaNames[4] = { "TR (Tourist)", "MED (Medical)", "BS (Business)", "GO (Government Officials)" };

    // Section 1: Applicants per visa type
    cout << "1. Applicants served by Visa Type:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << "   " << visaNames[i] << ": " << visaTypeCounts[i] << endl;
    }

    // Section 2: Counter-wise service details
    cout << "\n2. Applicants served by Counter:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << "   Counter " << i + 1 << " (" << counters[i].primaryVisa << "): ";
        if (counters[i].served == 0) {
            cout << "Idle";
        }
        else {
            // List all served tokens for the counter
            for (int j = 0; j < counters[i].served; ++j) {
                cout << counters[i].servedTypes[j] << "-" << counters[i].servedTokens[j];
                if (j < counters[i].served - 1) cout << ", ";
            }
        }
        cout << endl;
    }

    // Section 3: Idle counters list
    cout << "\n3. Idle Counters:" << endl;
    bool anyIdle = false;
    for (int i = 0; i < 4; ++i) {
        if (counters[i].served == 0) {
            cout << "   Counter " << i + 1 << " (" << counters[i].primaryVisa << ")" << endl;
            anyIdle = true;
        }
    }
    if (!anyIdle) cout << "   None" << endl;

    // Total served calculation and display
    int totalServed = visaTypeCounts[0] + visaTypeCounts[1] +
        visaTypeCounts[2] + visaTypeCounts[3];
    cout << "\nTotal Applicants Served: " << totalServed << endl;
}

// Display main menu options
void showMenu() {
    cout << "\n    Embassy Consulate System    \n";
    cout << "1. Request Token\n";
    cout << "2. Call Next Customer (Counter 1-4)\n";
    cout << "3. Generate Daily Summary Report\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

// Main program execution
int main() {
    initializeCounters(); // Set up counters with default types

    // Main program loop
    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(); // Clear input buffer

        // Handle menu choices
        if (choice == 1) {
            // Visa type selection sub-menu
            int visaChoice;
            cout << "\nSelect Visa Type:\n";
            cout << "1. Tourist Visa\n";
            cout << "2. Medical Visa\n";
            cout << "3. Business Visa\n";
            cout << "4. Government Officials Visa\n";
            cout << "Enter your choice (1-4): ";
            cin >> visaChoice;
            cin.ignore();

            string visaType;
            if (visaChoice == 1) visaType = "TR";
            else if (visaChoice == 2) visaType = "MED";
            else if (visaChoice == 3) visaType = "BS";
            else if (visaChoice == 4) visaType = "GO";
            else {
                cout << "Invalid choice. Returning to main menu." << endl;
                continue;
            }

            requestToken(visaType); // Process token request
        }

        else if (choice == 2) {
            // Counter selection for service
            cout << "Enter counter number (1-4): ";
            int c;
            cin >> c;
            if (c >= 1 && c <= 4)
                callNextCustomer(c - 1); // Convert to 0-based index
            else
                cout << "Invalid counter number." << endl;
        }

        else if (choice == 3) {
            generateSummaryReport(); // Show daily report
        }

        else if (choice == 4) {
            // Exit program
            cout << "\nExiting...Program\nThank you for using Embassy Consulate Line System! ";
            break;
        }

        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}