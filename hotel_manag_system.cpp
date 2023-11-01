#include <iostream>
#include <fstream>
#include <cstring> // Include the cstring library for string comparison
using namespace std;

class Hotel
{
private:
    int RoomNum;
    char GuestName[50];
    char GuestAddress[100];
    char GuestPhone[15];

public:
    void addBooking();
    void displayBookings();
    void editBooking();
    void deleteBooking();
    void Order_food();
};

void Hotel::addBooking()
{
    ofstream hotelFile("hotel_data.txt", std::ios::app);

    if (!hotelFile.is_open())
    {
        std::cerr << "Error opening the data file." << std::endl;
        return;
    }

    // for checking if room already exists
    int addRoom;
    cout << "Enter Room Number: ";
    cin >> addRoom;

    if (addRoom < 1 || addRoom > 50)
    {
        cout << "Invalid room number. Please choose a room between 1 and 50." << endl;
        return;
    }

    ifstream checkFile("hotel_data.txt");
    bool roomAlreadyBooked = false;

    while (checkFile >> RoomNum)
    {
        checkFile.ignore(); // Consume the space
        checkFile.getline(GuestName, 50, ' ');
        checkFile.getline(GuestAddress, 100, ' ');
        checkFile.getline(GuestPhone, 15);

        if (RoomNum == addRoom)
        {
            roomAlreadyBooked = true;
            cout << "Room is already booked." << endl;
            break;
        }
    }

    checkFile.close();

    if (roomAlreadyBooked)
    {
        return; // Don't proceed with the booking.
    }

    RoomNum = addRoom;

    cin.ignore(); // Clear the newline left in the input buffer (ignore the one character)
    cout << "Enter Guest Name: ";
    cin.getline(GuestName, 50);

    cout << "Enter Guest Address: ";
    cin.getline(GuestAddress, 100);

    cout << "Enter Guest Phone: ";
    cin.getline(GuestPhone, 15);

    hotelFile << RoomNum << ' ' << GuestName << ' ' << GuestAddress << ' ' << GuestPhone << std::endl;

    hotelFile.close();
    cout << "Booking added successfully!" << endl;
}

void Hotel::displayBookings()
{
    ifstream hotelFile("hotel_data.txt");
    if (!hotelFile.is_open())
    {
        cout << "Error opening the data file." << endl;
        return;
    }

    cout << "Room Number\tGuest Name\tGuest Address\tGuest Phone" << endl;

    while (hotelFile >> RoomNum)
    {
        hotelFile.ignore(); // Consume the space
        hotelFile.getline(GuestName, 50, ' ');
        hotelFile.getline(GuestAddress, 100, ' ');
        hotelFile.getline(GuestPhone, 15);

        cout << RoomNum << '\t' << GuestName << '\t' << GuestAddress << '\t' << GuestPhone << endl;
    }

    hotelFile.close();
}

void Hotel::editBooking()
{
    ifstream hotelFile("hotel_data.txt");
    if (!hotelFile.is_open())
    {
        cerr << "Error opening the data file." << endl;
        return;
    }

    int roomToEdit;
    cout << "Enter the room number to edit: ";
    cin >> roomToEdit;

    char newGuestName[50], newGuestAddress[100], newGuestPhone[15];
    bool found = false;

    ofstream tempFile("temp_data.txt");
    while (hotelFile >> RoomNum)
    {
        hotelFile.ignore(); // Consume the space
        hotelFile.getline(GuestName, 50, ' ');
        hotelFile.getline(GuestAddress, 100, ' ');
        hotelFile.getline(GuestPhone, 15);

        if (RoomNum == roomToEdit)
        {
            cin.ignore(); // Clear the newline left in the input buffer
            cout << "Enter New Guest Name: ";
            cin.getline(newGuestName, 50);

            if (strcmp(GuestName, newGuestName) == 0)
            {
                cout << "Enter New Guest Address: ";
                cin.getline(newGuestAddress, 100);

                cout << "Enter New Guest Phone: ";
                cin.getline(newGuestPhone, 15);

                tempFile << RoomNum << ' ' << newGuestName << ' ' << newGuestAddress << ' ' << newGuestPhone << endl;

                cout << "Booking updated successfully!" << endl;
                found = true;
            }
            else
            {
                tempFile << RoomNum << ' ' << GuestName << ' ' << GuestAddress << ' ' << GuestPhone << endl;
            }
        }
        else
        {
            tempFile << RoomNum << ' ' << GuestName << ' ' << GuestAddress << ' ' << GuestPhone << endl;
        }
    }

    if (!found)
    {
        cout << "Booking not found." << endl;
    }

    hotelFile.close();
    tempFile.close();

    remove("hotel_data.txt");
    rename("temp_data.txt", "hotel_data.txt");
}

void Hotel::deleteBooking()
{
    ifstream hotelFile("hotel_data.txt");
    if (!hotelFile.is_open())
    {
        cerr << "Error opening the data file." << endl;
        return;
    }

    int roomToDelete;
    cout << "Enter the room number to delete: ";
    cin >> roomToDelete;

    bool found = false;

    ofstream tempFile("temp_data.txt");
    while (hotelFile >> RoomNum)
    {
        hotelFile.ignore(); // Consume the space
        hotelFile.getline(GuestName, 50, ' ');
        hotelFile.getline(GuestAddress, 100, ' ');
        hotelFile.getline(GuestPhone, 15);

        if (RoomNum == roomToDelete)
        {
            found = true;
            cout << "Booking deleted successfully!" << endl;
        }
        else
        {
            tempFile << "RoomNo:" << RoomNum << ' ' << " Name:" << GuestName << ' ' << " Address:" << GuestAddress << ' ' << " Contact:" << GuestPhone << endl;
        }
    }

    if (!found)
    {
        cout << "Booking not found." << endl;
    }

    hotelFile.close();
    tempFile.close();

    remove("hotel_data.txt");
    rename("temp_data.txt", "hotel_data.txt");
}

void Hotel::Order_food()
{
    string food_items[20] = {"Butter Chicken", "Biryani", "Paneer Tikka", "Masala Dosa", "Chicken Tikka Masala", "Palak Paneer",
                             "Aloo Paratha", "Malai Kofta", "Dhokla", "Chhole Bhature", "Chicken Korma", "Tandoori Fish", "Shahi Paneer",
                             "Dal Makhani", "Paneer Butter Masala", "Aloo Jeera", "Gobi Manchurian", "Baingan Bharta", "Veg Kofta", "Veg Biryani"};
    string food;
    cout << "Enter the food: ";
    cin.ignore(); // Clear the newline left in the input buffer
    getline(cin, food);

    bool found = false;
    for (int i = 0; i < 20; i++)
    {
        if (food == food_items[i])
        {
            cout << "Your food will be delivered soon." << endl;
            found = true;
            break; // Food found, no need to continue searching.
        }
    }

    if (!found)
    {
        cout << "Food item not available." << endl;
    }
}

int main()
{
    Hotel hotel;
    int choice;

    do
    {
        cout << "Hotel Management System\n";
        cout << "1. Add Booking\n";
        cout << "2. Display Bookings\n";
        cout << "3. Edit Booking\n";
        cout << "4. Delete Booking\n";
        cout << "5. Order food\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            hotel.addBooking();
            break;
        case 2:
            hotel.displayBookings();
            break;
        case 3:
            hotel.editBooking();
            break;
        case 4:
            hotel.deleteBooking();
            break;
        case 5:
            hotel.Order_food();
            break;
        case 6:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}


