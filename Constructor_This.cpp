#include <iostream>
#include <cstring>

using namespace std;

class Person {
private:
    char* name;
    int age;
    char* phone;

public:
    Person() : name(nullptr), age(0), phone(nullptr) {
        name = new char[1];
        name[0] = '\0';
        phone = new char[1];
        phone[0] = '\0';
    }

    Person(const char* n, int a, const char* p) : age(a) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        phone = new char[strlen(p) + 1];
        strcpy(phone, p);
    }

    Person(const Person& other) : age(other.age) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        phone = new char[strlen(other.phone) + 1];
        strcpy(phone, other.phone);
    }

    Person& operator=(const Person& other) {
        if (this != &other) {
            delete[] name;
            delete[] phone;
            
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            phone = new char[strlen(other.phone) + 1];
            strcpy(phone, other.phone);
            age = other.age;
        }
        return *this;
    }
    ~Person() {
        delete[] name;
        delete[] phone;
    }

    void print() const {
        cout << "Name: " << name << ", Age: " << age << ", Phone: " << phone << endl;
    }

    const char* getName() const { return name; }
};

class Apartment {
private:
    Person* residents;
    int numResidents;
    int apartmentNumber;
    double area;

public:
    Apartment() : residents(nullptr), numResidents(0), apartmentNumber(0), area(0.0) {}
    Apartment(int number, double a) : apartmentNumber(number), area(a), numResidents(0), residents(nullptr) {}

    Apartment(const Apartment& other) : 
        apartmentNumber(other.apartmentNumber), 
        area(other.area),
        numResidents(other.numResidents) {
        if (other.numResidents > 0) {
            residents = new Person[other.numResidents];
            for (int i = 0; i < numResidents; i++) {
                residents[i] = other.residents[i];
            }
        } else {
            residents = nullptr;
        }
    }

    Apartment& operator=(const Apartment& other) {
        if (this != &other) {
            delete[] residents;
            
            apartmentNumber = other.apartmentNumber;
            area = other.area;
            numResidents = other.numResidents;
            
            if (numResidents > 0) {
                residents = new Person[numResidents];
                for (int i = 0; i < numResidents; i++) {
                    residents[i] = other.residents[i];
                }
            } else {
                residents = nullptr;
            }
        }
        return *this;
    }

    ~Apartment() {
        delete[] residents;
    }

    void addResident(const Person& person) {
        Person* newResidents = new Person[numResidents + 1];
        for (int i = 0; i < numResidents; i++) {
            newResidents[i] = residents[i];
        }
        newResidents[numResidents] = person;
        
        delete[] residents;
        residents = newResidents;
        numResidents++;
    }

    void print() const {
        cout << "Apartment #" << apartmentNumber << ", Area: " << area << " m²" << endl;
        cout << "Residents (" << numResidents << "):" << endl;
        for (int i = 0; i < numResidents; i++) {
            cout << "  ";
            residents[i].print();
        }
    }

    int getApartmentNumber() const { return apartmentNumber; }
};

class Building {
private:
    Apartment* apartments;
    int numApartments;
    char* address;

public:
    Building() : apartments(nullptr), numApartments(0), address(nullptr) {
        address = new char[1];
        address[0] = '\0';
    }

    Building(const char* addr, int numApts) : numApartments(numApts) {
        address = new char[strlen(addr) + 1];
        strcpy(address, addr);
        apartments = new Apartment[numApartments];
    }

    Building(const Building& other) : numApartments(other.numApartments) {
        address = new char[strlen(other.address) + 1];
        strcpy(address, other.address);
        
        apartments = new Apartment[numApartments];
        for (int i = 0; i < numApartments; i++) {
            apartments[i] = other.apartments[i];
        }
    }

    Building& operator=(const Building& other) {
        if (this != &other) {
            delete[] apartments;
            delete[] address;
            
            numApartments = other.numApartments;
            address = new char[strlen(other.address) + 1];
            strcpy(address, other.address);
            
            apartments = new Apartment[numApartments];
            for (int i = 0; i < numApartments; i++) {
                apartments[i] = other.apartments[i];
            }
        }
        return *this;
    }

    ~Building() {
        delete[] apartments;
        delete[] address;
    }

    void setApartment(int index, const Apartment& apt) {
        if (index >= 0 && index < numApartments) {
            apartments[index] = apt;
        }
    }

    void print() const {
        cout << "Building address: " << address << endl;
        cout << "Number of apartments: " << numApartments << endl;
        for (int i = 0; i < numApartments; i++) {
            cout << "\n";
            apartments[i].print();
        }
    }
};
int main(int argc, char* argv[])
{
    Person person1("John Smith", 25, "+1234567890");
    Person person2("Mary Johnson", 30, "+2345678901");
    Person person3("Peter Brown", 45, "+3456789012");

    Apartment apt1(1, 50.5);
    apt1.addResident(person1);
    apt1.addResident(person2);

    Apartment apt2(2, 75.0);
    apt2.addResident(person3);

    Building building("123 Main Street", 2);
    building.setApartment(0, apt1);
    building.setApartment(1, apt2);

    building.print();

    Building building2 = building;
    cout << "\nCopy of the building:\n";
    building2.print();

    return 0;
}
