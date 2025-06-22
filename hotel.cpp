#include <iostream>
#include <vector>
#include <string>
#include <limits> // Not used in C++98 context but kept for consistency
using namespace std;

class Room {
private:
    int roomNumber;
    string roomType;
    bool isBooked;

public:
    Room(int number, const string &type) {
        roomNumber = number;
        roomType = type;
        isBooked = false;
    }

    int getRoomNumber() const {
        return roomNumber;
    }

    bool getBookingStatus() const {
        return isBooked;
    }

    void book() {
        if (!isBooked) {
            isBooked = true;
            cout << "? Room " << roomNumber << " booked successfully.\n";
        } else {
            cout << "? Room " << roomNumber << " is already booked.\n";
        }
    }

    void checkout() {
        if (isBooked) {
            isBooked = false;
            cout << "? Checked out of Room " << roomNumber << ".\n";
        } else {
            cout << "? Room " << roomNumber << " is not booked.\n";
        }
    }

    void showDetails() const {
        cout << "Room No: " << roomNumber
             << ", Type: " << roomType
             << ", Status: " << (isBooked ? "Booked" : "Available") << '\n';
    }
};

class Hotel {
private:
    vector<Room> rooms;

public:
    void addRoom(int number, const string &type) {
        rooms.push_back(Room(number, type));
        cout << "? Room " << number << " (" << type << ") added successfully.\n";
    }

    void showRooms() const {
        if (rooms.empty()) {
            cout << "?? No rooms available.\n";
            return;
        }
        cout << "?? All Rooms:\n";
        for (size_t i = 0; i < rooms.size(); ++i) {
            rooms[i].showDetails();
        }
    }

    void bookRoom(int number) {
        for (size_t i = 0; i < rooms.size(); ++i) {
            if (rooms[i].getRoomNumber() == number) {
                rooms[i].book();
                return;
            }
        }
        cout << "? Room " << number << " not found.\n";
    }

    void checkoutRoom(int number) {
        for (size_t i = 0; i < rooms.size(); ++i) {
            if (rooms[i].getRoomNumber() == number) {
                rooms[i].checkout();
                return;
            }
        }
        cout << "? Room " << number << " not found.\n";
    }
};

int main() {
    Hotel hotel;

    // Preloaded Rooms
    hotel.addRoom(101, "Standard");
    hotel.addRoom(102, "Deluxe");
    hotel.addRoom(103, "Standard");

    while (1) {
        cout << "\n=== ?? Hotel Management System ===\n"
             << "1. Show All Rooms\n"
             << "2. Book a Room\n"
             << "3. Checkout a Room\n"
             << "4. Add New Room\n"
             << "5. Exit\n"
             << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "? Invalid input. Enter a number.\n";
            continue;
        }

        int roomNumber;
        string roomType;

        switch (choice) {
            case 1:
                hotel.showRooms();
                break;

            case 2:
                cout << "Enter room number to book: ";
                cin >> roomNumber;
                hotel.bookRoom(roomNumber);
                break;

            case 3:
                cout << "Enter room number to checkout: ";
                cin >> roomNumber;
                hotel.checkoutRoom(roomNumber);
                break;

            case 4:
                cout << "Enter new room number: ";
                cin >> roomNumber;
                cout << "Enter room type (Standard/Deluxe/etc.): ";
                cin.ignore();
                getline(cin, roomType);
                hotel.addRoom(roomNumber, roomType);
                break;

            case 5:
                cout << "?? Exiting system.\n";
                return 0;

            default:
                cout << "? Invalid choice. Try again.\n";
                break;
        }
    }

    return 0;
}

