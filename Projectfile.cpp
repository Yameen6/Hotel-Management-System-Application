#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  //Input/output manipulation
#include <sstream>  //String stream operations
#include <ctime>    //Date and time functions
#include <limits> // Required for numeric_limits.To clear input buffer and prevent crashes
#include <cstdlib> // Required for system("cls")

using namespace std;
const int MAX_SIZE = 1000;

//  Prototypes 

// for safe input reading for integers. Returns true on success.
bool safeReadInt(int& value);
// for safe input reading for doubles. Returns true on success.
bool safeReadDouble(double& value);
// Consumes leftover input buffer to prevent crashes.
void clearInputBuffer(); 
// Calculates the number of full days/nights between two dates (DD-MM-YYYY).
int calculate_days_between(const string& start_date, const string& end_date);
// Simple check for room availability status
bool checkRoomAvailable(const int roomNumbers[], const string roomStatuses[],
const bool roomActives[], int roomCount, int roomNo);
// Admin login check
bool admin_login_check(const string& user, const string& pass);

// Helper function to safely convert string to int
int safe_stoi_local(const string& str);
// Helper function to safely convert string to double
double safe_stod_local(const string& str);


// File I/O Prototypes
void saveRooms(const int roomNumbers[], const string roomTypes[], const double roomPrices[],
const string roomStatuses[], const bool roomActives[], int roomCount);
void saveGuests(const string guestEmails[], const string guestPasswords[],
const bool guestActives[], int guestCount);
void saveBookings(const string bookingEmails[], const int bookingRoomNos[],
const string bookingInDates[], const string bookingOutDates[], const double bookingTotalPrices[], 
const bool bookingActives[], int bookingCount);

void loadRooms(int roomNumbers[], string roomTypes[], 
double roomPrices[], string roomStatuses[], 
bool roomActives[], int& roomCount);
void loadGuests(string guestEmails[], string guestPasswords[], bool guestActives[], int& guestCount);
void loadBookings(string bookingEmails[], int bookingRoomNos[], string bookingInDates[],
string bookingOutDates[], double bookingTotalPrices[], bool bookingActives[], int& bookingCount);

// Room/Guest/Booking CRUD & View Prototypes

// Admin Add room (Returns true on success)
bool addRoom(int roomNumbers[], string roomTypes[], double roomPrices[], 
string roomStatuses[], bool roomActives[], int& roomCount);

// Admin Delete room (Returns true on success)
bool deleteRoom(int roomNumbers[], string roomStatuses[],
bool roomActives[], int roomCount, int delNumber);

// Admin Update room (Returns true on success)
bool updateRoom(int roomNumbers[], string roomTypes[], 
double roomPrices[], bool roomActives[], int roomCount, int updNumber);

// Change Room Status
void markRoomStatus(int roomNumbers[], string roomStatuses[],
bool roomActives[], int roomCount, int roomNumber, const string& newStatus);

// Admin/Guest View Rooms (Prints output)
void viewRooms(const int roomNumbers[], const string roomTypes[],
const double roomPrices[], const string roomStatuses[], 
const bool roomActives[], int roomCount, bool showOnlyAvailable);

// Guest Signup (Returns true on success)
bool guestSignup(string guestEmails[], string guestPasswords[],
bool guestActives[], int& guestCount);

// Guest Login (Returns email on success, empty string on failure)
string guestLogin(const string guestEmails[], const string guestPasswords[],
     const bool guestActives[], int guestCount);

// Guest Book room (Returns total price, 0on failure)
// UPDATED PROTOYPE: Added const string roomStatuses[]
double bookRoom(const int roomNumbers[], const double roomPrices[],
    const string roomStatuses[], const bool roomActives[], int roomCount,
    string bookingEmails[], int bookingRoomNos[], string bookingInDates[],
    string bookingOutDates[], double bookingTotalPrices[], 
    bool bookingActives[], int& bookingCount,
    const string& currentUserEmail);

// Guest Cancel booking 
bool cancelBooking(string bookingEmails[], int bookingRoomNos[], bool bookingActives[],
int bookingCount, const string& userEmail, int roomNumberToCancel);

// Admin/Guest View Bookings 
void viewBookings(const string bookingEmails[], const int bookingRoomNos[], const string bookingInDates[], 
const string bookingOutDates[], const double bookingTotalPrices[], const bool bookingActives[], 
int bookingCount, const string& userEmail, bool isAdmin);

// Admin Generate Report 
void generateRevenueReport(const int roomNumbers[], const string roomStatuses[],
const bool roomActives[], int roomCount,const double bookingTotalPrices[], 
const bool bookingActives[], int bookingCount, int guestCount);


// MAIN BODY
int main() {
    int roomNumbers[MAX_SIZE];
    string roomTypes[MAX_SIZE];
    double roomPrices[MAX_SIZE]; 
    string roomStatuses[MAX_SIZE]; 
    bool roomActives[MAX_SIZE];
    int roomCount = 0;

    string guestEmails[MAX_SIZE];
    string guestPasswords[MAX_SIZE];
    bool guestActives[MAX_SIZE];
    int guestCount = 0;

    string bookingEmails[MAX_SIZE];
    int bookingRoomNos[MAX_SIZE];
    string bookingInDates[MAX_SIZE];
    string bookingOutDates[MAX_SIZE];
    double bookingTotalPrices[MAX_SIZE]; 
    bool bookingActives[MAX_SIZE];
    int bookingCount = 0;

    string currentUserEmail = "";
    int choice = 0;
    bool firstTime = true;

    // Load existing data
    loadRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount);
    loadGuests(guestEmails, guestPasswords, guestActives, guestCount);
    loadBookings(bookingEmails, bookingRoomNos, bookingInDates, 
    bookingOutDates, bookingTotalPrices, bookingActives, bookingCount);
    
    while (true) {
        system("cls"); //  for Clear screen
        if (firstTime) {
            cout << "---------------------------------------------------------" << endl;
            cout << "---------------Hotel Management System------------------" << endl;
            cout << "---------------------------------------------------------" << endl;
            firstTime = false;
        }
        cout << "---------------------------------" << endl;
        cout << "\n========== Main Menu ==========\n";
        cout << "1. Admin Login\n2. Guest Signup\n3. Guest Login\n4. Exit\n";
        cout << "Enter choice: ";
        
       if (safeReadInt(choice) == false)
        {
            cout << "\n*Invalid choice! Please enter a number between 1-4. *\n";
             continue;
              }
        
        switch (choice)
         {
            case 1:
             { 
                // Admin Login
                system("cls");
                string Username, password;
                int attempts = 0;
                const int maxAttempts = 3;

while (attempts < maxAttempts) {
clearInputBuffer();
cout << "\n===== Admin Login =====\n";
cout << "Enter Admin Username: ";
getline(cin, Username);
cout << "Enter Admin Password: ";
getline(cin, password);

if (admin_login_check(Username, password)) {
     cout << "\n* Login Successful! Welcome Admin *\n";
                        
        // Admin Panel
int admin_choice;
bool admin_running = true;
    while (admin_running) {
     system("cls");
     cout << "\n========== Admin Panel ==========\n";
    cout << "1. Add Room\n2. View All Rooms\n3. View Available Rooms\n4. View Booked Rooms\n5. Update Room\n6. Delete Room\n7. Generate Revenue Report\n8. Logout\n";
    cout << "Enter choice: ";
                            
    if (safeReadInt(admin_choice) == false) 
        { 
    cout << "\n* Invalid choice! Please enter a number between 1-8. *\n";
    continue; 
         }
    if (admin_choice == 1)                       
                            
         // Add Room

{                      
    if (addRoom(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount))
    {
    saveRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount);

    cout << "\n*** Room added successfully! ***\n";

     } 
     else 
    {
     cout << "\n* Failed to add room! (Check array size or input) *\n";

      }
        }

    else if (admin_choice == 2)  
                                
        // ViewRooms

         { 
        viewRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount, false);

     } 
     else if (admin_choice == 3)
            { 
          // View Available Rooms
    viewRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount, true);

             } 
        else if (admin_choice == 4)
         { 
        // View Booked Rooms
      viewBookings(bookingEmails, bookingRoomNos, bookingInDates, bookingOutDates,
                    bookingTotalPrices, bookingActives, bookingCount, "", true);

        } 
                            
         else if (admin_choice == 5) 
        { 
         // Update Room


        int updNumber;
          cout << "\n===== Update Room =====\n";
          cout << "Enter Room Number to update: ";

         if (safeReadInt(updNumber)) 
                                
             {

            if (updateRoom(roomNumbers, roomTypes, roomPrices, roomActives, roomCount, updNumber)) 
               {
               saveRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount);

              cout << "\n* Room updated successfully! *\n";
                 } 
                 else
                      {
             cout << "\n* Room not found or update failed! *\n";
                  }

                 } 
               else 

              {
               cout << "\n* Invalid Room Number input! *\n";
                   }
                  } 
          else if (admin_choice == 6) 
         { 
                                
          // Delete Room


 int delNumber;
cout << "\n===== Delete Room =====\n";
 cout << "Enter Room Number to delete: ";

if (safeReadInt(delNumber))
 {
                                   
  if (deleteRoom(roomNumbers, roomStatuses, roomActives, roomCount, delNumber)) 
      {
          saveRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount);
          cout << "\n* Room deleted successfully! *\n";

          }
        else
             {
               cout << "\n* Room not found  (Room is booked)! *\n";
                      }

                      }
        else 
 {
           cout << "\n* Invalid Room Number input! *\n";
     }
      } 
                            
          else if (admin_choice == 7) 
                            
        { 
         // Revenue Report


 generateRevenueReport(roomNumbers, roomStatuses, roomActives, roomCount, 
                     bookingTotalPrices, bookingActives, bookingCount, guestCount);
      } 
         else if (admin_choice == 8) 
                            
             { 
                          // Logout

                 cout << "\n* Logging out. *\n";
                 admin_running = false;
                            } 
                            
             else 
        {
           cout << "\n* Invalid choice! Please enter a number between 1-8. *\n";
        }
                            
            if (admin_running)
                            
            { 
                  // Pause after operations

             cout << "\nPress Enter to continue...";
             clearInputBuffer();
             cin.get();
                      }

                     }

         break; 

        }
         else 
{
          attempts++;
         cout << "\n* Invalid Admin credentials! *\n";

         if (attempts < maxAttempts) 
                        
         {
                            
         cout << "Attempts remaining: " << (maxAttempts - attempts) << endl;

                  }
            else 
               {
              cout << "Maximum login attempts reached. Returning to main menu.\n";
                  }
                    }
                }
                
        break;
                
            }

        case 2:
            
            { 
                // Guest Signup

        system("cls");
        if (guestSignup(guestEmails, guestPasswords, guestActives, guestCount))
     {
        saveGuests(guestEmails, guestPasswords, guestActives, guestCount);
         cout << "\n* Signup successful! You can login now. *\n";

         } 
        else 
             {
                    
             cout << "\n* Signup failed. Email  already registred *\n";

                }

     cout << "\nPress Enter to continue.";
    clearInputBuffer();
    cin.get();
    break;
            }

    case 3: 
            
    { 
                // Guest Login


    system("cls");
     currentUserEmail = guestLogin(guestEmails, guestPasswords, guestActives, guestCount);
                
    if (currentUserEmail != "") 
        {
           // Guest Panel
      int guest_choice;
     bool guest_running = true;
      while (guest_running)
                    
         {
             system("cls");
              cout << "\n========== Guest Panel ==========\n";
             cout << "1. View Available Rooms\n2. Book a Room\n3. View My Bookings\n4. Cancel Booking\n5. Logout\n";
             cout << "Enter choice: ";
                        
             if (safeReadInt(guest_choice) == false)
                        
             {
                  cout << "\n* Invalid choice! Please enter a number between 1-5. *\n";

                  continue;

                 }

 if (guest_choice == 1)
                        
        { 
         // View Available Rooms


     viewRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount, true);
          }
                        
 else if (guest_choice == 2) 
                        
    { 
                            // Book a Room

          system("cls");
         cout << "\n===== Book a Room =====\n";
                         // Show available rooms first
         viewRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount, true); 

                            // UPDATED CALL: Passed roomStatuses array
        double totalPrice = bookRoom(roomNumbers, roomPrices, roomStatuses, roomActives, roomCount,
          bookingEmails, bookingRoomNos, bookingInDates, bookingOutDates, 
        bookingTotalPrices, bookingActives, bookingCount,currentUserEmail);
        if (totalPrice > 0)
             {
                         // Must call the functions to update dependencies after a successful bookRoom call

            int bookedRoomNo = bookingRoomNos[bookingCount - 1]; // Get room number from the last added booking


             markRoomStatus(roomNumbers, roomStatuses, roomActives, roomCount, bookedRoomNo, "Booked");
                saveRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount);
                      saveBookings(bookingEmails, bookingRoomNos, bookingInDates, bookingOutDates,
                                 bookingTotalPrices, bookingActives, bookingCount);

                     cout << "\n* Booking Successful! *\n";
                     cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << "\n";
                            } 
         else
                  {
                      cout << "\n* Booking Failed. (Invalid room/dates/full) *\n";
           }

              }
             else if (guest_choice == 3)
             { 
              // View My Bookings

     viewBookings(bookingEmails, bookingRoomNos, bookingInDates, bookingOutDates,
                  bookingTotalPrices, bookingActives, bookingCount, currentUserEmail, false);

            }
             else if (guest_choice == 4)
                          { 
                            // Cancel Booking

        int roomNumberToCancel;
         cout << "\n===== Cancel Booking =====\n";
         viewBookings(bookingEmails, bookingRoomNos, bookingInDates, bookingOutDates, bookingTotalPrices,
                bookingActives, bookingCount, currentUserEmail, false);

             cout << "\nEnter Room Number to cancel booking: ";
                            
          if (safeReadInt(roomNumberToCancel))
                             {
             if (cancelBooking(bookingEmails, bookingRoomNos, bookingActives, bookingCount, currentUserEmail, roomNumberToCancel))
                                 {
                                    // Must call the function to update dependencies after a successful cancelBooking call

                 markRoomStatus(roomNumbers, roomStatuses, roomActives, roomCount, roomNumberToCancel, "Available");
                 saveRooms(roomNumbers, roomTypes, roomPrices, roomStatuses, roomActives, roomCount);
             saveBookings(bookingEmails, bookingRoomNos, bookingInDates, bookingOutDates, bookingTotalPrices, bookingActives, bookingCount);

              cout << "\n* Booking cancelled successfully! *\n";
                      } 
              else
                  {
                  cout << "\n* Booking not found or cancellation failed! *\n";
                     }
             }
             else
                  {
                  cout << "\n* Invalid Room Number input! *\n";
              }
                  } 
             else if (guest_choice == 5) 
         { 
              // Logout

             cout << "\n* Logging out... *\n";
         currentUserEmail = "";
         guest_running = false;
      } 
      else 
   {
         cout << "\n* Invalid choice! Please enter a number between 1-5. *\n";
          }
                        
     if (guest_running)
                         { 
                            // Pause after operations

      cout << "\nPress Enter to continue...";
      clearInputBuffer();
         cin.get();
                        }
                    }
                } 
 else
                 {
                    cout << "\n* Login failed! *\n";
                    cout << "\nPress Enter to continue...";
                    clearInputBuffer();
                    cin.get();
                }
 break;
            }
  case 4:
             { 
                // Exit
  cout << "\n* Thank you for using Hotel Management System! *\n";
    return 0;
            }

 default:
             {
    cout << "\n* Invalid choice! Please enter a number between 1-4. *\n";
    cout << "\nPress Enter to continue...";
         clearInputBuffer();
      cin.get();
            }
        }
    }
}

// FUNCTION IMPLEMENTATIONS

//  Helper Functions
//Ignore everything in the waiting room until you hit the point where the user pressed Enter
void clearInputBuffer() 
{
    if (cin.fail()) 
    {
        cin.clear();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
//Catch mistakes like typing abc when the program expects 1 before they crash your code.
bool safeReadInt(int& value) 
{
    if (!(cin >> value))
     {
        clearInputBuffer();
        return false;
    }

    clearInputBuffer();
    return true;
}
//Safety Inspector for money or measurements.Like if you expect 12.34 but the user types twelve point thirty four or expensive.
bool safeReadDouble(double& value) 
{
    if (!(cin >> value)) 
    {
        clearInputBuffer();
        return false;
    }

    clearInputBuffer();
    return true;
}

// Simple date parser for DD-MM-YYYY to struct tm
//This function is like a Date Translator.
bool parse_date_tm(const string& date_str, tm& t) {
    if (date_str.length() != 10 || date_str[2] != '-' || date_str[5] != '-') 
    {
        return false;
    }
    stringstream SS;
    SS.str(date_str);
    int day, month, year;
    char dash;

    if (!(SS >> day >> dash && dash == '-' && SS >> month >> dash && dash == '-' && SS >> year))
     {
        return false;
    }

    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1; 

    return true;
}
// This function calculates the number of days between two dates.translate both text dates into computer format.
int calculate_days_between(const string& start_date, const string& end_date) 
{
    tm start_tm = {0};
    tm end_tm = {0};

    if (!parse_date_tm(start_date, start_tm) || !parse_date_tm(end_date, end_tm))
    
    
    {
        return 0; // Invalid date format
    }

    time_t start_time = mktime(&start_tm);
    time_t end_time = mktime(&end_tm);

    if (start_time == (time_t)-1 || end_time == (time_t)-1) 
    {
        return 0; // Error in mktime
    }

    // Calculate difference in seconds
    double diff_seconds = difftime(end_time, start_time);

    // Convert to days (86400 seconds in a day)

    long long diff_days_ll = static_cast<long long>(diff_seconds / (60 * 60 * 24));

    // Ensure check-out is strictly after check-in, and at least 1 day/night

    if (diff_days_ll <= 0) 
    {
        return 0;
    }
    
    // Return as integer
    return static_cast<int>(diff_days_ll);
}
// This function checks if a room is free to be booked.
bool checkRoomAvailable(const int roomNumbers[], const string roomStatuses[], const bool roomActives[], int roomCount, int roomNo)
 {
    for (int i = 0; i < roomCount; i++)
     {
        if (roomNumbers[i] == roomNo && roomActives[i]) 
        {
            return (roomStatuses[i] == "Available");
        }
    }
    return false;
}
//Checks if the admin username and password are correct.
bool admin_login_check(const string& username, const string& password)
 {
    const string adminUsername = "admin@yameen";
    const string adminPassword = "Admin@123#";
    return (username == adminUsername && password == adminPassword);
}
// This function turns text into a number without crashing.
//Convert "100" to 100 safely and if user enter Abc return 0.
int safe_stoi_local(const string& str) 
{
    try 
    {
        if (str.empty()) return 0;
        return stoi(str);
    }
     catch (...)
     {
        return 0;
    }
}
// This function turns text into a decimal number without crashing.
//Convert "99.99" to 99.99 safely and if user enter Dollar return 0.

double safe_stod_local(const string& str)
 {
    try 
    {
        if (str.empty()) return 0.0;
        return stod(str);
    } 
    catch (...) 
    {
        return 0.0;
    }
}


// File Input output Functions
//This function saves room data to a text file.
void saveRooms(const int roomNumbers[], const string roomTypes[], const double roomPrices[], 
    const string roomStatuses[], const bool roomActives[], int roomCount) 
    {

    ofstream file("rooms.txt");
    if (file.is_open()) 
    {
        for (int i = 0; i < roomCount; i++)
         {
            file << roomNumbers[i] << ","
                 << roomTypes[i] << ","
                 << fixed << setprecision(2) << roomPrices[i] << ","
                 << roomStatuses[i] << ","
                 << (roomActives[i] ? "1" : "0") << "\n";
        }

        file.close();
    }

}
//This function saves guest data to a text file.
void saveGuests(const string guestEmails[], const string guestPasswords[], const bool guestActives[], int guestCount)
 {
    ofstream file("guests.txt");

    if (file.is_open()) 
    {
        for (int i = 0; i < guestCount; i++)
         {
            file << guestEmails[i] << ","
                 << guestPasswords[i] << ","
                 << (guestActives[i] ? "1" : "0") << "\n";
        }

        file.close();
    }
}
// This function saves all hotel reservations to a file
void saveBookings(const string bookingEmails[], const int bookingRoomNos[], const string bookingInDates[],
     const string bookingOutDates[], const double bookingTotalPrices[], const bool bookingActives[], int bookingCount)
      {

    ofstream file("bookings.txt");

    if (file.is_open()) 
    {
        for (int i = 0; i < bookingCount; i++) 
        {
            file << bookingEmails[i] << ","
                 << bookingRoomNos[i] << ","
                 << bookingInDates[i] << ","
                 << bookingOutDates[i] << ","
                 << fixed << setprecision(2) << bookingTotalPrices[i] << ","
                 << (bookingActives[i] ? "1" : "0") << "\n";
        }

        file.close();
    }
}
// This function reads the room data from the text file into the program
void loadRooms(int roomNumbers[], string roomTypes[], double roomPrices[],
     string roomStatuses[], bool roomActives[], int& roomCount) 
     {
    ifstream roomFile("rooms.txt");
    roomCount = 0;
    string line;

    while (getline(roomFile, line) && roomCount < MAX_SIZE)
     {
        if (line.empty()) continue;
        stringstream ss(line);
        string number, type, price, status, active;
        
        if (getline(ss, number, ',') &&
            getline(ss, type, ',') &&
            getline(ss, price, ',') &&
            getline(ss, status, ',') &&
            getline(ss, active)) {
            
            roomNumbers[roomCount] = safe_stoi_local(number);
            roomTypes[roomCount] = type;
            roomPrices[roomCount] = safe_stod_local(price);
            roomStatuses[roomCount] = status;
            roomActives[roomCount] = (active == "1");
            roomCount++;
        }


    }

    roomFile.close();
}
// This function loads all guest accounts from the text file into the program.
void loadGuests(string guestEmails[], string guestPasswords[], bool guestActives[], int& guestCount) 
{
    ifstream guestFile("guests.txt");
    guestCount = 0;
    string line;
    while (getline(guestFile, line) && guestCount < MAX_SIZE) {
        if (line.empty()) 
        continue;

        stringstream ss(line);
        string email, password, active;
        
        if (getline(ss, email, ',') &&
            getline(ss, password, ',') &&
            getline(ss, active)) {
            
            guestEmails[guestCount] = email;
            guestPasswords[guestCount] = password;
            guestActives[guestCount] = (active == "1");
            guestCount++;
        }
    }

    guestFile.close();
}
// This function loads all hotel Booking from the text file into the program.
void loadBookings(string bookingEmails[], int bookingRoomNos[], string bookingInDates[],
     string bookingOutDates[], double bookingTotalPrices[], bool bookingActives[], int& bookingCount) 
     
    {

    ifstream bookingFile("bookings.txt");
    bookingCount = 0;
    string line;

    while (getline(bookingFile, line) && bookingCount < MAX_SIZE)
     {
        if (line.empty()) continue;
        stringstream ss(line);
        string email, room, checkIn, checkOut, price, active;
        
        if (getline(ss, email, ',') &&
            getline(ss, room, ',') &&
            getline(ss, checkIn, ',') &&
            getline(ss, checkOut, ',') &&
            getline(ss, price, ',') &&
            getline(ss, active)) {
            
            bookingEmails[bookingCount] = email;
            bookingRoomNos[bookingCount] = safe_stoi_local(room);
            bookingInDates[bookingCount] = checkIn;
            bookingOutDates[bookingCount] = checkOut;
            bookingTotalPrices[bookingCount] = safe_stod_local(price);
            bookingActives[bookingCount] = (active == "1");
            bookingCount++;
        }
    }

    bookingFile.close();

}


//Room CRUD Functions

//This function adds a new room to the system.
bool addRoom(int roomNumbers[], string roomTypes[], double roomPrices[], string roomStatuses[], 
    bool roomActives[], int& roomCount) 
    
    {
    if (roomCount >= MAX_SIZE)
     {
        return false;
    }
    
    int number;
    string type;
    double price;
    
    cout << "\n===== Add New Room =====\n";
    cout << "Enter Room Number: ";

    if (!safeReadInt(number)) 
    {
        cout << "\n* Invalid input for Room Number! *\n";

        return false;
    }
    
    // Check if room number already exists

    for (int i = 0; i < roomCount; i++) 
    {
        if (roomNumbers[i] == number && roomActives[i])
         {
            cout << "\n* Room number already exists! *\n";
            return false;
        }
    }
    
    cout << "Enter Room Type: ";
    clearInputBuffer(); 
    getline(cin, type); 
    
    cout << "Enter Room Price (per night): ";

    if (!safeReadDouble(price)) {
        
        cout << "\n* Invalid input for Room Price! *\n";
        return false;

    }

    roomNumbers[roomCount] = number;
    roomTypes[roomCount] = type;
    roomPrices[roomCount] = price;
    roomStatuses[roomCount] = "Available";
    roomActives[roomCount] = true;
    roomCount++;
    
    return true;
}
// This function deletes a room from the system.
bool deleteRoom(int roomNumbers[], string roomStatuses[], bool roomActives[], int roomCount, int delNumber)
 {
    for (int i = 0; i < roomCount; i++)
     {
        if (roomNumbers[i] == delNumber && roomActives[i])
         {
            if (roomStatuses[i] == "Booked")
             {
                cout << "\n* Cannot delete! Room is currently booked. *\n";
                return false;
            }
            roomActives[i] = false;
            return true;
        }
    }
    
    return false;
}
// This function updates room details.
bool updateRoom(int roomNumbers[], string roomTypes[], double roomPrices[], bool roomActives[], int roomCount, int updNumber) 
{
    for (int i = 0; i < roomCount; i++) 
    {
        if (roomNumbers[i] == updNumber && roomActives[i])
         {
            string newType;
            double newPrice;

            cout << "Enter new Room Type: ";
            clearInputBuffer();
            getline(cin, newType);
            
            cout << "Enter new Room Price (per night): ";
            if (!safeReadDouble(newPrice)) {
                cout << "\n* Invalid input for Room Price! Update failed. *\n";
                return false;
            }

            roomTypes[i] = newType;
            roomPrices[i] = newPrice;
            return true;

        }
    }

    return false;
}
// This function changes the status of a room.
void markRoomStatus(int roomNumbers[], string roomStatuses[], bool roomActives[],
     int roomCount, int roomNumber, const string& newStatus)
     
     {

    for (int i = 0; i < roomCount; i++) 
    {
        if (roomNumbers[i] == roomNumber && roomActives[i]) 
        {
            roomStatuses[i] = newStatus;

            return;
        }
    }
}
// This function displays rooms based on availability.
void viewRooms(const int roomNumbers[], const string roomTypes[], const double roomPrices[],
     const string roomStatuses[], const bool roomActives[], int roomCount, bool showOnlyAvailable) 
     
    {

    cout << "\n===== " << (showOnlyAvailable ? "Available" : "All") << " Rooms =====" << "\n";
    cout << "-----------------------------------------------------------\n";
    cout << setw(10) << "Room#" << setw(15) << "Type" << setw(12) << "Price/Night" << setw(15) << "Status" << "\n";
    cout << "-----------------------------------------------------------\n";
    
    bool hasRooms = false;
    for (int i = 0; i < roomCount; i++) 

    {

        if (roomActives[i] && (!showOnlyAvailable || roomStatuses[i] == "Available")) 

        {

            cout << setw(10) << roomNumbers[i] 
                 << setw(15) << roomTypes[i] 
                 << setw(11) << "$" << fixed << setprecision(2) << roomPrices[i]
                 << setw(15) << roomStatuses[i] << '\n';
            hasRooms = true;

        }

    }
    
    if (!hasRooms)
     {
        cout << (showOnlyAvailable ? "No available rooms." : "No rooms in system.") << "\n";
    }
    
}
//Guest Functions
bool guestSignup(string guestEmails[], string guestPasswords[], bool guestActives[], int& guestCount) 
{
    if (guestCount >= MAX_SIZE)
     {
        return false;
    }
    
    string username, password, cpassword;

    cout << "\n===== Guest Signup =====\n";

    cout << "Enter Email (Username): ";
    if (!(cin >> username)) 
    return false;

    // Check if email already exists


    for (int i = 0; i < guestCount; i++) 
    {
        if (guestEmails[i] == username && guestActives[i])

         {
            cout << "\n* Email already registered! *\n";

            return false;
        }

    }
    
    cout << "Enter Password: ";
    if (!(cin >> password))
     return false;
    
    cout << "Confirm Password: ";

    if (!(cin >> cpassword))
     return false;
    
    if(password != cpassword)
    {
        cout << "\n* Passwords do not match. Please try again. *\n";
        return false;
    }
    if(password.length() < 8)
    {
        cout << "\n*Password should be at least 8 characters long. *\n";

        return false;

    }
    //npos is a constant representing "not found" in string operations.
    if(username.find('@') == string::npos || username.find('.') == string::npos) 

    {
        cout << "\n* Invalid email format. *\n";

        return false;

    }

    guestEmails[guestCount] = username;
    guestPasswords[guestCount] = password;
    guestActives[guestCount] = true;
    guestCount++;
    
    return true;
}
// This function handles guest login.
string guestLogin(const string guestEmails[], const string guestPasswords[], const bool guestActives[], int guestCount) 
{
    string username, password;
    int attempts = 0;
    const int maxAttempts = 3;
    
    while (attempts < maxAttempts) 
    {
        cout << "\n===== Guest Login =====\n";
        cout << "Enter Username (Email): ";
        if (!(cin >> username)) //this is a safety check to prevent crashes if user enter invalid input.
        return ""; 
        // Crash protection
        
        cout << "Enter Password: ";

        if (!(cin >> password)) return ""; 
        // Crash protection

        for (int i = 0; i < guestCount; i++) 
        {
            if (guestEmails[i] == username && guestPasswords[i] == password && guestActives[i])
             {
                return username; // Return email on successful login
            }
        }
        
        attempts++;

        cout << "\n* Invalid Guest credentials! *\n";

        if (attempts < maxAttempts)
         {

            cout << "Attempts remaining: " << (maxAttempts - attempts) << endl;

        }
         else 
         {
           
            cout << "Maximum login attempts reached.\n";
            
        }

    }

    return ""; // Return empty string on failure

}

// UPDATED IMPLEMENTATION: Added const string roomStatuses parameter
double bookRoom(const int roomNumbers[], const double roomPrices[], const string roomStatuses[], const bool roomActives[], int roomCount,
                string bookingEmails[], int bookingRoomNos[], string bookingInDates[], string bookingOutDates[], double bookingTotalPrices[], 
                bool bookingActives[], int& bookingCount,
                const string& currentUserEmail)
                 {

    if (bookingCount >= MAX_SIZE)
     {
        cout << "\n* Booking limit reached! *\n";
        return 0;
    }
    
    int roomNumber = 0;
    double roomPricePerNight = 0;
    string checkInDate, checkOutDate;
    
    cout << "\nEnter Room Number to book: ";
    //safety check for integer input
    if (!safeReadInt(roomNumber)) 
    {
        cout << "\n* Invalid input for Room Number! *\n";
        return 0;
    }
    
    int roomIndex = -1; //this means no room found yet.
    for (int i = 0; i < roomCount; i++) 
    {
        if (roomNumbers[i] == roomNumber && roomActives[i]) 
        {
            roomPricePerNight = roomPrices[i];
            roomIndex = i; // found the room
            break;

        }
    }

    // checkRoomAvailable now correctly receives roomStatuses
    if (roomIndex == -1 || !checkRoomAvailable(roomNumbers, roomStatuses, roomActives, roomCount, roomNumber)) 

    {
        cout << "\n* Room is not available or does not exist! *\n";
        return 0;
    }
    
    cout << "Enter Check-In Date (DD-MM-YYYY): ";

    getline(cin, checkInDate); 
    
    cout << "Enter Check-Out Date (DD-MM-YYYY): ";

    getline(cin, checkOutDate);
    
    int numberOfDays = calculate_days_between(checkInDate, checkOutDate);

    if (numberOfDays <= 0) 
    {
        cout << "\n* Invalid date range! Check-out date must be after check-in date. (DD-MM-YYYY format required) *\n";
        
        return 0;
    }

    double totalPrice = roomPricePerNight * numberOfDays;
    
    bookingEmails[bookingCount] = currentUserEmail;
    bookingRoomNos[bookingCount] = roomNumber;
    bookingInDates[bookingCount] = checkInDate;
    bookingOutDates[bookingCount] = checkOutDate;
    bookingTotalPrices[bookingCount] = totalPrice;
    bookingActives[bookingCount] = true;
    bookingCount++;
    
    return totalPrice;

}
// This function cancels an existing booking.
bool cancelBooking(string bookingEmails[], int bookingRoomNos[], bool bookingActives[],
     int bookingCount, const string& userEmail, int roomNumberToCancel) 
     {

    for (int i = 0; i < bookingCount; i++) 

    {
        if (bookingActives[i] && 
            bookingEmails[i] == userEmail && 
            bookingRoomNos[i] == roomNumberToCancel) 
            {
            
            bookingActives[i] = false;

            return true;
        }
    }

    return false;
}

//  View/Report Functions 

void viewBookings(const string bookingEmails[], const int bookingRoomNos[], const string bookingInDates[],
     const string bookingOutDates[], const double bookingTotalPrices[], const bool bookingActives[], 
     int bookingCount, const string& userEmail, bool isAdmin) 
     
     {

    cout << "\n " << (isAdmin ? "Booked Rooms (Admin View)" : "My Bookings") << " \n";
    
    if (isAdmin)
     {
        cout << "------------------------------------------------------------------------------------------------\n";
        cout << setw(10) << "Room#" << setw(25) << "Guest Email" << setw(15) << "Check-In" << setw(15) << "Check-Out" << setw(12) << "Total Price" << "\n";
        cout << "------------------------------------------------------------------------------------------------\n";
    } 
    else 
    {
        cout << "-----------------------------------------------------------\n";
        cout << setw(10) << "Room#" << setw(15) << "Check-In" << setw(15) << "Check-Out" << setw(12) << "Total Price" << "\n";
        cout << "-----------------------------------------------------------\n";
    }
    
    bool hasBookings = false;
    for (int i = 0; i < bookingCount; i++) 
    {
        if (bookingActives[i] && (isAdmin || bookingEmails[i] == userEmail)) 
        {
            if (isAdmin)
             {
                cout << setw(10) << bookingRoomNos[i] 
                     << setw(25) << bookingEmails[i] 
                     << setw(15) << bookingInDates[i] 
                     << setw(15) << bookingOutDates[i] 
                     << setw(12) << "$" << fixed << setprecision(2) << bookingTotalPrices[i] << '\n';
            } 
            else 
            {
                cout << setw(10) << bookingRoomNos[i] 
                     << setw(15) << bookingInDates[i] 
                     << setw(15) << bookingOutDates[i] 
                     << setw(12) << "$" << fixed << setprecision(2) << bookingTotalPrices[i] << '\n';
            }

            hasBookings = true;
        }
    }
    
    if (!hasBookings) 
    {
        cout << (isAdmin ? "No active bookings found." : "No active bookings for you.") << "\n";
    }
}

void generateRevenueReport(const int roomNumbers[], const string roomStatuses[], const bool roomActives[], int roomCount,
                           const double bookingTotalPrices[], const bool bookingActives[], int bookingCount, int guestCount)
{
    double totalRevenue = 0;
    int totalActiveBookings = 0;
    
    cout << "\n===== Revenue Report =====\n";

    for (int i = 0; i < bookingCount; i++) 
    {
        if (bookingActives[i])
         {
            totalRevenue += bookingTotalPrices[i];
            totalActiveBookings++;
        }
    }
    
    cout << "Total Active Bookings: " << totalActiveBookings << "\n";
    cout << "Total Estimated Revenue: $" << fixed << setprecision(2) << totalRevenue << "\n";
    int availableRooms = 0;
    int bookedRooms = 0;
    
    for (int i = 0; i < roomCount; i++) 
    {
        if (roomActives[i]) 
        {
            if (roomStatuses[i] == "Available")
            {
                availableRooms++;
            } 
            else 
            {
                bookedRooms++;
            }
        }
    }
    
    cout << "\n-- Room Status --\n";
    cout << "Available Rooms: " << availableRooms << "\n";
    cout << "Booked Rooms: " << bookedRooms << "\n";
    cout << "Total Active Rooms: " << (availableRooms + bookedRooms) << "\n";
    cout << "Total Registered Guests: " << guestCount << "\n";
    cout << "-----------------------------------------------------------\n";
}