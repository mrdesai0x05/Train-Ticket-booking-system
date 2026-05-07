# 🚆 Train Ticket Booking System

![C++](https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?logo=windows&logoColor=white)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio-purple?logo=visualstudio&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![License](https://img.shields.io/badge/License-MIT-green)

> 🎓 **Submitted for:** PEP Summer Training Report — Data Structures and Algorithms
> 🏫 **Institution:** Lovely Professional University, Phagwara, Punjab
> 📅 **Training Period:** 23rd June 2025 – 30th July 2025

---

## 📌 Project Overview

The **Train Ticket Booking System** is a console-based C++ application developed as part of the **28-day DSA Summer Training Program** at Lovely Professional University. The system automates the process of train ticket reservation, simulating real-world operations such as booking, cancellation, seat allocation, and waiting list management — all backed by persistent file storage.

---

## 🎯 Objectives

- ✅ Design and implement a ticket reservation system using C++
- ✅ Apply data structures (arrays, queues) for train and passenger management
- ✅ Implement a **waiting list mechanism** with automatic seat reallocation on cancellation
- ✅ Use **file handling** for persistent storage of train and booking records
- ✅ Create a clean, menu-driven console interface for ease of use

---

## 🔹 What It Does

- Add and manage trains with details like train number, name, source, destination, seat capacity, and price
- Search for trains between any two locations
- Book tickets with auto-generated **PNR numbers** and sequential seat allocation
- Automatically add passengers to a **waiting list** when seats are full
- Cancel tickets and instantly reallocate freed seats to waiting passengers
- View booking status by PNR number
- Persist all records in binary files (`trains.dat`, `bookings.dat`)

---

## ✨ Features

| Feature | Description |
|---|---|
| Train Management | Add, view, and search trains by source & destination |
| Ticket Booking | Auto PNR generation, seat allocation in sequential order |
| Waiting List | Queue-based waiting list — auto-assigns on cancellation |
| Cancellation | Frees seat and triggers waiting list reallocation |
| PNR Lookup | View full ticket details by entering PNR |
| Data Persistence | Binary file storage — records survive program restart |
| Menu Interface | Simple numbered console menu for all operations |

---

## ⚙️ System Modules

| Module | Description |
|---|---|
| **Train Management** | Admin can add and list all available trains |
| **Booking Engine** | Handles seat availability check and ticket allocation |
| **Waiting List Handler** | Queue-style management for overbooked trains |
| **Cancellation Handler** | Cancels ticket and triggers waiting list assignment |
| **File Manager** | Reads/writes `trains.dat` and `bookings.dat` at startup and exit |

---

## 🚀 How to Run Locally

### Prerequisites

- Windows OS
- Visual Studio (or any C++ compiler with GCC/MinGW)
- C++ Standard: C++11 or higher

### Steps

**1. Clone or download the project**
```sh
git clone https://github.com/<your-username>/Train-Ticket-Booking-System.git
cd Train-Ticket-Booking-System
```

**2. Open in Visual Studio**
- Open the `.cpp` file in Visual Studio
- Build the solution (`Ctrl + Shift + B`)
- Run the program (`Ctrl + F5`)

**3. Using GCC (Command Line)**
```sh
g++ -o booking main.cpp
./booking
```

---

## 📂 Project Structure

```
Train-Ticket-Booking-System/
│
├── main.cpp              # Main source file — all modules included
├── trains.dat            # Binary file storing train records (auto-generated)
├── bookings.dat          # Binary file storing booking records (auto-generated)
│
└── README.md             # Project documentation
```

---

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| **C++** | Core programming language |
| **Arrays & Structs** | Storage of train and passenger records |
| **File Handling (fstream)** | Persistent binary file storage |
| **Queue Logic** | Waiting list management |
| **Visual Studio** | IDE for coding, debugging, and execution |
| **Windows OS** | Development and testing environment |

---

## 📊 Sample Output

### Menu
```
====== Train Ticket Booking System ======
1. Add Train (Admin)
2. View Trains
3. Search Train
4. Book Ticket
5. Cancel Ticket
6. View My Tickets
7. Exit
Enter choice:
```

### Booking a Ticket
```
Enter Train Number to Book: 101
Enter Passenger Name: Veeresh A
Enter Age: 21
🎟️ Ticket Booked! PNR: 1001, Seat No: 1
```

### Waiting List
```
⚠️ No seats available! Added to waiting list. PNR: 1005
```

### Cancellation with Reallocation
```
❌ Ticket Cancelled for Veeresh A
✅ Seat given to waiting passenger: Ravi Kumar (PNR: 1005)
```

---

## 🔮 Future Improvements

- ✅ Add a **Graphical User Interface (GUI)** for better user interaction
- ✅ Integrate a **database (MySQL / SQLite)** to replace binary file storage
- ✅ Add **payment gateway** simulation for realistic ticket pricing
- ✅ Support **seat preference selection** (window, aisle, etc.)
- ✅ Add **mobile app access** and online booking interface
- ✅ Implement **aging mechanism** to handle waiting list priority fairly

---

## 📚 References

- Cormen, T. H., et al. — *Introduction to Algorithms* (3rd ed.), MIT Press
- Sedgewick, R. & Wayne, K. — *Algorithms* (4th ed.), Addison-Wesley
- Malik, D. S. — *Data Structures Using C++*, Cengage Learning
- [GeeksforGeeks — DSA Tutorials](https://www.geeksforgeeks.org)
- [HackerRank — DSA Practice](https://www.hackerrank.com)
- [LeetCode — Programming Challenges](https://leetcode.com)
- [Skillstone — Training Assignments](https://www.skillstone.in/account/)

---

## 📌 Course Details

| Detail | Info |
|---|---|
| **Program** | PEP Summer Training — Data Structures and Algorithms |
| **Degree** | BTech CSE (AI and ML) |
| **Institution** | Lovely Professional University |
| **Training Period** | 23rd June 2025 – 30th July 2025 |
| **Developer** | Veeresh A (Reg. No: 12319252) |
| **Submission Date** | August 2025 |
