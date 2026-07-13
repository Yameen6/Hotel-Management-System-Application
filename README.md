Hotel Management System (C++)
A console-based Hotel Management System built with C++, developed as an academic Programming Fundamentals project at UET Lahore. The system manages hotel operations through three main user roles — Admin, Staff, and Guest  handling room, guest, booking, and billing management with structured file handling for persistent data storage.
About
This project follows a structured (procedural) programming approach, using functions and structs to organize logic around a real-world hotel management scenario. It provides a menu-driven interface allowing different users to perform role-specific operations, from room booking to billing and staff administration.
User Roles & Features
👤 Guest
View available rooms and room details (type, price, availability)
Book a room
Cancel a booking
View personal booking history
Generate and view bill for stay
🛎️ Staff
Check guest-in / check-out
View and update room status (occupied/vacant/under maintenance)
View guest details and current bookings
Generate guest bills
Add new guest records
🔑 Admin
Add / update / delete room records (room number, type, price)
Add / remove staff accounts
View all guests and bookings across the system
View overall hotel occupancy and revenue reports
Manage system-wide records (rooms, guests, bookings, bills)
Core Modules
Room Management  Add, update, delete, and view room details and availability
Guest Management Register guests, maintain guest records and booking history
Booking Management  Create, update, and cancel bookings; track check-in/check-out
Billing System  Auto-calculate bill based on room type, duration of stay, and services
Staff Management  Admin-controlled staff accounts with restricted access levels
File Handling Persistent data storage using text/file-based records for rooms, guests, bookings, and bills
Tech Stack
Language: C++
IDE: Visual Studio Code
Paradigm: Structured / Procedural Programming
Data Storage: File handling (text files)
Interface: Console-based menu system
Getting Started
Prerequisites
Visual Studio Code
A C++ compiler (e.g., GCC/MinGW) with the C/C++ extension configured in VS Code
Running the Project
Clone the repository
```
   git clone https://github.com/Yameen6/Hotel-Management-System-Application
   ```
Open the project folder in VS Code
Compile and run via the integrated terminal:
```
   g++ main.cpp -o HotelManagementSystem
   ./HotelManagementSystem
   ```
Run the program and log in based on your role (Admin / Staff / Guest)
Project Structure
```
HotelManagementSystem/
├── main.cpp           # Entry point and main menu
├── admin.cpp/.h        # Admin-related functions
├── staff.cpp/.h         # Staff-related functions
├── guest.cpp/.h         # Guest-related functions
├── room.cpp/.h           # Room management functions
├── booking.cpp/.h        # Booking management functions
├── bill.cpp/.h            # Billing calculation functions
├── rooms.txt            # Stores room data
├── guests.txt           # Stores guest data
├── bookings.txt         # Stores booking data
└── ...                  # Additional supporting files
```
Author
Muhammad Yameen Aslam
BS Computer Science, UET Lahore
GitHub · LinkedIn
License
This project is developed for academic purposes as part of the Programming Fundamentals course at UET Lahore.
