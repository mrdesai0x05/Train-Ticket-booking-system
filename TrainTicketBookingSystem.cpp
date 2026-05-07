/*
 * ============================================================
 *   TRAIN TICKET BOOKING SYSTEM
 * ============================================================
 *   Course   : Data Structures and Algorithms (PEP Summer Training)
 *   Degree   : BTech CSE (AI and ML)
 *   Institute: Lovely Professional University, Phagwara, Punjab
 *   Developer: Veeresh A  |  Reg. No: 12319252
 *   Period   : 23rd June 2025 – 30th July 2025
 * ============================================================
 *   Description:
 *   A console-based train ticket reservation system built in C++.
 *   Supports train management, ticket booking, cancellation,
 *   waiting list handling, and persistent file storage.
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

// ─────────────────────────────────────────────
//  CONSTANTS
// ─────────────────────────────────────────────
const int MAX_TRAINS    = 20;
const int MAX_BOOKINGS  = 200;
const int MAX_WAITING   = 50;

// ─────────────────────────────────────────────
//  DATA STRUCTURES
// ─────────────────────────────────────────────

struct Train {
    int   trainNo;
    char  name[50];
    char  source[30];
    char  destination[30];
    int   totalSeats;
    int   availableSeats;
    float price;
};

struct Passenger {
    int  pnr;
    char name[50];
    int  age;
    int  trainNo;
    int  seatNo;        // -1 means on waiting list
};

// ─────────────────────────────────────────────
//  GLOBAL ARRAYS (primary data store)
// ─────────────────────────────────────────────
Train     trains[MAX_TRAINS];
Passenger bookings[MAX_BOOKINGS];
Passenger waitingList[MAX_WAITING];

int trainCount   = 0;
int bookingCount = 0;
int waitingCount = 0;
int pnrCounter   = 1000;   // auto-incrementing PNR seed

// ─────────────────────────────────────────────
//  UTILITY: separator line
// ─────────────────────────────────────────────
void line(char c = '-', int n = 50) {
    for (int i = 0; i < n; i++) cout << c;
    cout << "\n";
}

// ─────────────────────────────────────────────
//  FILE HANDLING — Save all data to binary files
// ─────────────────────────────────────────────
void saveData() {
    // Save trains
    ofstream fout1("trains.dat", ios::binary | ios::trunc);
    if (fout1) {
        fout1.write((char*)&trainCount, sizeof(trainCount));
        fout1.write((char*)trains,      sizeof(Train) * trainCount);
        fout1.write((char*)&pnrCounter, sizeof(pnrCounter));
        fout1.close();
    }

    // Save confirmed bookings
    ofstream fout2("bookings.dat", ios::binary | ios::trunc);
    if (fout2) {
        fout2.write((char*)&bookingCount, sizeof(bookingCount));
        fout2.write((char*)bookings,      sizeof(Passenger) * bookingCount);
        fout2.close();
    }

    // Save waiting list
    ofstream fout3("waiting.dat", ios::binary | ios::trunc);
    if (fout3) {
        fout3.write((char*)&waitingCount, sizeof(waitingCount));
        fout3.write((char*)waitingList,   sizeof(Passenger) * waitingCount);
        fout3.close();
    }
}

// ─────────────────────────────────────────────
//  FILE HANDLING — Load all data from binary files
// ─────────────────────────────────────────────
void loadData() {
    ifstream fin1("trains.dat", ios::binary);
    if (fin1) {
        fin1.read((char*)&trainCount, sizeof(trainCount));
        fin1.read((char*)trains,      sizeof(Train) * trainCount);
        fin1.read((char*)&pnrCounter, sizeof(pnrCounter));
        fin1.close();
    }

    ifstream fin2("bookings.dat", ios::binary);
    if (fin2) {
        fin2.read((char*)&bookingCount, sizeof(bookingCount));
        fin2.read((char*)bookings,      sizeof(Passenger) * bookingCount);
        fin2.close();
    }

    ifstream fin3("waiting.dat", ios::binary);
    if (fin3) {
        fin3.read((char*)&waitingCount, sizeof(waitingCount));
        fin3.read((char*)waitingList,   sizeof(Passenger) * waitingCount);
        fin3.close();
    }
}

// ─────────────────────────────────────────────
//  MODULE 1 — Add a new train (Admin)
// ─────────────────────────────────────────────
void addTrain() {
    if (trainCount >= MAX_TRAINS) {
        cout << "  [!] Maximum train limit reached.\n";
        return;
    }

    line();
    cout << "  ADD NEW TRAIN\n";
    line();

    Train& t = trains[trainCount];

    cout << "  Train Number   : "; cin >> t.trainNo;

    // Check for duplicate train number
    for (int i = 0; i < trainCount; i++) {
        if (trains[i].trainNo == t.trainNo) {
            cout << "  [!] Train number already exists!\n";
            return;
        }
    }

    cin.ignore();
    cout << "  Train Name     : "; cin.getline(t.name, 50);
    cout << "  Source         : "; cin.getline(t.source, 30);
    cout << "  Destination    : "; cin.getline(t.destination, 30);
    cout << "  Total Seats    : "; cin >> t.totalSeats;
    cout << "  Ticket Price   : Rs. "; cin >> t.price;

    t.availableSeats = t.totalSeats;
    trainCount++;
    saveData();

    cout << "\n  [OK] Train added successfully!\n";
}

// ─────────────────────────────────────────────
//  MODULE 2 — View all available trains
// ─────────────────────────────────────────────
void viewTrains() {
    line();
    cout << "  ALL AVAILABLE TRAINS\n";
    line();

    if (trainCount == 0) {
        cout << "  No trains in the system yet.\n";
        return;
    }

    cout << left
         << setw(8)  << "  No."
         << setw(25) << "Train Name"
         << setw(15) << "Source"
         << setw(15) << "Destination"
         << setw(10) << "Seats"
         << setw(12) << "Price (Rs.)"
         << "\n";
    line();

    for (int i = 0; i < trainCount; i++) {
        cout << "  "
             << left  << setw(6)  << trains[i].trainNo
             << setw(25) << trains[i].name
             << setw(15) << trains[i].source
             << setw(15) << trains[i].destination
             << setw(10) << trains[i].availableSeats
             << fixed << setprecision(2) << trains[i].price
             << "\n";
    }
}

// ─────────────────────────────────────────────
//  MODULE 3 — Search trains by source & destination
// ─────────────────────────────────────────────
void searchTrain() {
    line();
    cout << "  SEARCH TRAIN\n";
    line();

    char src[30], dest[30];
    cin.ignore();
    cout << "  Enter Source      : "; cin.getline(src, 30);
    cout << "  Enter Destination : "; cin.getline(dest, 30);

    bool found = false;
    cout << "\n  Results:\n";
    line();

    for (int i = 0; i < trainCount; i++) {
        if (strcmp(trains[i].source, src) == 0 &&
            strcmp(trains[i].destination, dest) == 0) {
            cout << "  Train No : " << trains[i].trainNo << "\n"
                 << "  Name     : " << trains[i].name    << "\n"
                 << "  Seats    : " << trains[i].availableSeats << "\n"
                 << "  Price    : Rs. " << fixed << setprecision(2)
                                        << trains[i].price << "\n";
            line('~');
            found = true;
        }
    }

    if (!found)
        cout << "  [!] No trains found between " << src << " and " << dest << ".\n";
}

// ─────────────────────────────────────────────
//  MODULE 4 — Book a ticket
// ─────────────────────────────────────────────
void bookTicket() {
    line();
    cout << "  BOOK TICKET\n";
    line();

    viewTrains();

    int tno;
    cout << "\n  Enter Train Number to Book : "; cin >> tno;

    for (int i = 0; i < trainCount; i++) {
        if (trains[i].trainNo == tno) {

            Passenger p;
            p.pnr     = pnrCounter++;
            p.trainNo = tno;

            cin.ignore();
            cout << "  Passenger Name : "; cin.getline(p.name, 50);
            cout << "  Age            : "; cin >> p.age;

            if (trains[i].availableSeats > 0) {
                // Confirmed booking
                p.seatNo = trains[i].totalSeats - trains[i].availableSeats + 1;
                bookings[bookingCount++] = p;
                trains[i].availableSeats--;
                saveData();

                line();
                cout << "  [OK] Ticket Booked Successfully!\n";
                cout << "  PNR Number : " << p.pnr    << "\n";
                cout << "  Seat No    : " << p.seatNo << "\n";
                cout << "  Train      : " << trains[i].name << "\n";
                cout << "  From       : " << trains[i].source
                     << "  -->  " << trains[i].destination << "\n";
                cout << "  Price      : Rs. " << fixed << setprecision(2)
                                              << trains[i].price << "\n";
                line();

            } else {
                // Waiting list
                if (waitingCount >= MAX_WAITING) {
                    cout << "  [!] Waiting list is also full. Cannot book.\n";
                    return;
                }
                p.seatNo = -1;
                waitingList[waitingCount++] = p;
                saveData();

                cout << "\n  [WAIT] No seats available.\n";
                cout << "  Added to Waiting List.\n";
                cout << "  PNR : " << p.pnr
                     << "  |  Position in queue : " << waitingCount << "\n";
            }
            return;
        }
    }
    cout << "  [!] Train number not found!\n";
}

// ─────────────────────────────────────────────
//  MODULE 5 — Cancel a ticket
// ─────────────────────────────────────────────
void cancelTicket() {
    line();
    cout << "  CANCEL TICKET\n";
    line();

    int pnr;
    cout << "  Enter PNR to Cancel : "; cin >> pnr;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].pnr == pnr) {
            int tno      = bookings[i].trainNo;
            char pname[50];
            strcpy(pname, bookings[i].name);

            // Remove from bookings array (shift left)
            for (int j = i; j < bookingCount - 1; j++)
                bookings[j] = bookings[j + 1];
            bookingCount--;

            // Free seat in train record
            for (int k = 0; k < trainCount; k++) {
                if (trains[k].trainNo == tno) {
                    trains[k].availableSeats++;

                    // If waiting list has passengers → give the freed seat
                    if (waitingCount > 0) {
                        Passenger wp = waitingList[0];

                        // Shift waiting list left (FIFO queue)
                        for (int w = 0; w < waitingCount - 1; w++)
                            waitingList[w] = waitingList[w + 1];
                        waitingCount--;

                        wp.seatNo = trains[k].totalSeats
                                    - trains[k].availableSeats + 1;
                        bookings[bookingCount++] = wp;
                        trains[k].availableSeats--;

                        cout << "\n  [OK] Ticket cancelled for : " << pname << "\n";
                        cout << "  [OK] Seat reallocated to  : "
                             << wp.name << "  (PNR: " << wp.pnr
                             << ", Seat: " << wp.seatNo << ")\n";
                    } else {
                        cout << "\n  [OK] Ticket cancelled for : " << pname << "\n";
                        cout << "  Seat is now available.\n";
                    }
                    break;
                }
            }

            saveData();
            return;
        }
    }

    // Check if PNR is on waiting list
    for (int i = 0; i < waitingCount; i++) {
        if (waitingList[i].pnr == pnr) {
            char pname[50];
            strcpy(pname, waitingList[i].name);

            for (int j = i; j < waitingCount - 1; j++)
                waitingList[j] = waitingList[j + 1];
            waitingCount--;

            saveData();
            cout << "\n  [OK] Waiting list entry cancelled for : " << pname << "\n";
            return;
        }
    }

    cout << "  [!] PNR not found in bookings or waiting list!\n";
}

// ─────────────────────────────────────────────
//  MODULE 6 — View ticket by PNR
// ─────────────────────────────────────────────
void viewMyTicket() {
    line();
    cout << "  VIEW TICKET BY PNR\n";
    line();

    int pnr;
    cout << "  Enter PNR : "; cin >> pnr;

    // Search confirmed bookings
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].pnr == pnr) {
            // Find train details
            for (int k = 0; k < trainCount; k++) {
                if (trains[k].trainNo == bookings[i].trainNo) {
                    line('=');
                    cout << "         BOOKING CONFIRMED\n";
                    line('=');
                    cout << "  PNR          : " << bookings[i].pnr        << "\n";
                    cout << "  Name         : " << bookings[i].name       << "\n";
                    cout << "  Age          : " << bookings[i].age        << "\n";
                    cout << "  Train No     : " << trains[k].trainNo      << "\n";
                    cout << "  Train Name   : " << trains[k].name         << "\n";
                    cout << "  From         : " << trains[k].source       << "\n";
                    cout << "  To           : " << trains[k].destination  << "\n";
                    cout << "  Seat No      : " << bookings[i].seatNo     << "\n";
                    cout << "  Ticket Price : Rs. " << fixed << setprecision(2)
                                                   << trains[k].price    << "\n";
                    cout << "  Status       : CONFIRMED\n";
                    line('=');
                    return;
                }
            }
        }
    }

    // Search waiting list
    for (int i = 0; i < waitingCount; i++) {
        if (waitingList[i].pnr == pnr) {
            line('=');
            cout << "         WAITING LIST\n";
            line('=');
            cout << "  PNR        : " << waitingList[i].pnr    << "\n";
            cout << "  Name       : " << waitingList[i].name   << "\n";
            cout << "  Age        : " << waitingList[i].age    << "\n";
            cout << "  Train No   : " << waitingList[i].trainNo << "\n";
            cout << "  Position   : " << (i + 1) << " in waiting queue\n";
            cout << "  Status     : WAITING\n";
            line('=');
            return;
        }
    }

    cout << "  [!] No ticket found for PNR: " << pnr << "\n";
}

// ─────────────────────────────────────────────
//  MODULE 7 — View all bookings (Admin)
// ─────────────────────────────────────────────
void viewAllBookings() {
    line();
    cout << "  ALL CONFIRMED BOOKINGS\n";
    line();

    if (bookingCount == 0) {
        cout << "  No bookings yet.\n";
        return;
    }

    cout << left
         << setw(8)  << "  PNR"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(10) << "TrainNo"
         << setw(8)  << "Seat"
         << "\n";
    line();

    for (int i = 0; i < bookingCount; i++) {
        cout << "  "
             << left << setw(6)  << bookings[i].pnr
             << setw(20) << bookings[i].name
             << setw(6)  << bookings[i].age
             << setw(10) << bookings[i].trainNo
             << setw(8)  << bookings[i].seatNo
             << "\n";
    }

    line();
    cout << "  Total confirmed bookings : " << bookingCount << "\n";
    cout << "  Passengers on wait list  : " << waitingCount << "\n";
}

// ─────────────────────────────────────────────
//  MAIN MENU
// ─────────────────────────────────────────────
void showMenu() {
    cout << "\n";
    line('=');
    cout << "       TRAIN TICKET BOOKING SYSTEM\n";
    cout << "       Lovely Professional University\n";
    line('=');
    cout << "  1.  Add Train          (Admin)\n";
    cout << "  2.  View All Trains\n";
    cout << "  3.  Search Train\n";
    cout << "  4.  Book Ticket\n";
    cout << "  5.  Cancel Ticket\n";
    cout << "  6.  View My Ticket (by PNR)\n";
    cout << "  7.  View All Bookings  (Admin)\n";
    cout << "  8.  Exit\n";
    line('=');
    cout << "  Enter your choice : ";
}

// ─────────────────────────────────────────────
//  MAIN FUNCTION
// ─────────────────────────────────────────────
int main() {
    loadData();   // Load persisted records at startup

    int choice;
    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTrain();        break;
            case 2: viewTrains();      break;
            case 3: searchTrain();     break;
            case 4: bookTicket();      break;
            case 5: cancelTicket();    break;
            case 6: viewMyTicket();    break;
            case 7: viewAllBookings(); break;
            case 8:
                saveData();
                cout << "\n  Data saved. Goodbye!\n\n";
                return 0;
            default:
                cout << "\n  [!] Invalid choice. Please enter 1–8.\n";
        }
    }
}
