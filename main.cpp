#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Set text color for console output
void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    cout << "\033[" << color << "m";
#endif
}

// Movie class to store movie details
class Movie {
public:
    string name;
    int availableTickets;
    double price;

    Movie(string n, int tickets, double p)
        : name(n), availableTickets(tickets), price(p) {}
};

// Booking class to store booking records
class Booking {
public:
    string movieName;
    int ticketsBooked;
    double totalPrice;

    Booking(string movie, int tickets, double price)
        : movieName(movie), ticketsBooked(tickets), totalPrice(price) {}
};

// Clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Display all movies
void displayMovies(const vector<Movie>& movies) {
    setColor(36); // Cyan
    cout << "\n+---------------------------------------------+\n";
    cout << "|               Available Movies              |\n";
    cout << "+---------------------------------------------+\n";

    setColor(32); // Green
    for (size_t i = 0; i < movies.size(); ++i) {
        cout << "| " << setw(2) << i + 1 << ". " << setw(30) << left << movies[i].name
             << " Tickets: " << setw(2) << movies[i].availableTickets
             << " Price: $" << fixed << setprecision(2) << movies[i].price << " |\n";
    }

    setColor(36); // Cyan
    cout << "+---------------------------------------------+\n";
    setColor(37); // Default
}

// Book tickets
void bookTicket(vector<Movie>& movies, vector<Booking>& bookings) {
    int movieChoice, tickets;

    displayMovies(movies);

    setColor(33); // Yellow
    cout << "\nSelect a movie by number: ";
    cin >> movieChoice;

    if (movieChoice < 1 || movieChoice > movies.size()) {
        setColor(31); // Red
        cout << "Invalid choice. Try again.\n";
        setColor(37); // Default
        return;
    }

    Movie& selectedMovie = movies[movieChoice - 1];

    cout << "Enter number of tickets: ";
    cin >> tickets;

    if (tickets <= 0 || tickets > selectedMovie.availableTickets) {
        setColor(31); // Red
        cout << "Invalid number of tickets. Try again.\n";
        setColor(37); // Default
        return;
    }

    double totalPrice = tickets * selectedMovie.price;
    selectedMovie.availableTickets -= tickets;
    bookings.emplace_back(selectedMovie.name, tickets, totalPrice);

    setColor(32); // Green
    cout << "\nBooking successful! Total Price: $" << fixed << setprecision(2) << totalPrice << "\n";
    setColor(37); // Default
}

// View booking history
void viewBookings(const vector<Booking>& bookings) {
    if (bookings.empty()) {
        setColor(31); // Red
        cout << "\nNo bookings found.\n";
        setColor(37); // Default
        return;
    }

    setColor(36); // Cyan
    cout << "\n+---------------------------------------------+\n";
    cout << "|               Booking History               |\n";
    cout << "+---------------------------------------------+\n";

    setColor(32); // Green
    for (const auto& booking : bookings) {
        cout << "| Movie: " << setw(30) << left << booking.movieName
             << " Tickets: " << setw(2) << booking.ticketsBooked
             << " Total: $" << fixed << setprecision(2) << booking.totalPrice << " |\n";
    }

    setColor(36); // Cyan
    cout << "+---------------------------------------------+\n";
    setColor(37); // Default
}

// Simulate loading animation
void loadingEffect(const string& message) {
    cout << message;
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
#ifdef _WIN32
        Sleep(500);
#else
        usleep(500000); // microseconds
#endif
    }
    cout << "\n";
}

// Main program
int main() {
    vector<Movie> movies = {
        {"Avengers: Endgame", 50, 10.0},
        {"Joker", 40, 8.5},
        {"Toy Story 4", 30, 7.0}
    };

    vector<Booking> bookings;
    int choice;

    while (true) {
        clearScreen();

        setColor(36); // Cyan
        cout << "+---------------------------------------------+\n";
        cout << "|           Movie Ticket Booking System       |\n";
        cout << "+---------------------------------------------+\n";

        setColor(33); // Yellow
        cout << "1. View Movies\n";
        cout << "2. Book Ticket\n";
        cout << "3. View Bookings\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
            case 1:
                displayMovies(movies);
                break;
            case 2:
                bookTicket(movies, bookings);
                break;
            case 3:
                viewBookings(bookings);
                break;
            case 4:
                setColor(35); // Magenta
                loadingEffect("Exiting");
                setColor(37); // Default
                return 0;
            default:
                setColor(31); // Red
                cout << "Invalid choice. Please try again.\n";
                setColor(37); // Default
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
