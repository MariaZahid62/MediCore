#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include <fstream>
#include <sstream>
using namespace std;

class Person {     // Base class for Staff and Patient
protected:
    string name;

public:
    Person(string n) : name(n) {}
    virtual void display() const = 0;
    string getName() const { return name; }
    virtual ~Person() {} // Virtual destructor
};

class Patient : public Person {   // Derived from Person; encapsulates patient details.
private:
    string conditionHistory;
    string prescribedMedication;
    string treatment;

public:
    Patient(string n, string ch, string pm, string t)
        : Person(n), conditionHistory(ch), prescribedMedication(pm), treatment(t) {
    }

    void updateDetails(string ch, string pm, string t) {
        conditionHistory = ch;
        prescribedMedication = pm;
        treatment = t;
    }

    void display() const override {
        cout << "\nPatient: " << name << endl;
        cout << "Condition History: " << conditionHistory << endl;
        cout << "Prescribed Medications: " << prescribedMedication << endl;
        cout << "Treatments: " << treatment << endl;
        cout << "---------------------------------\n";
    }
};

class Staff : public Person {    // Derived from Person; stores staff information.
private:
    string role;
    string contact;

public:
    Staff(string n, string r, string c) : Person(n), role(r), contact(c) {}

    void display() const override {
        cout << name << " (" << role << "), Contact: " << contact << endl;
    }

    string getRole() const { return role; }
    string getContact() const { return contact; }
};

class Appointment {    // Handles appointment booking, cancellation, and viewing.
public:
    bool booked;
    string patientName;
    string timeSlot;
    string shift;

    Appointment() : booked(false), patientName(""), timeSlot(""), shift("") {}

    void book(string pName, string tSlot, string s) {
        booked = true;
        patientName = pName;
        timeSlot = tSlot;
        shift = s;
    }

    void cancel() {
        booked = false;
        patientName = "";
        timeSlot = "";
        shift = "";
    }

    void display(const string& staffName) const {
        if (booked)
            cout << staffName << " is booked for: " << patientName << " at " << timeSlot << " (" << shift << ")\n";
        else
            cout << staffName << " has no appointments.\n";
    }
};

class Pharmacy {    // Manages medications and billing.
private:
    vector<string> medicationNames = { "Aspirin", "Paracetamol", "Amoxicillin" };
    vector<double> medicationPrices = { 10.0, 8.5, 15.0 };

public:
    void showMedications() const {
        cout << "\n===== Medications Available =====\n";
        for (size_t i = 0; i < medicationNames.size(); ++i) {
            cout << i + 1 << ". " << medicationNames[i] << " - $" << medicationPrices[i] << endl;
        }
    }

    void calculateBill() const {
        double total = 0;
        int choice;
        cout << "\nEnter medication number to add to bill (0 to finish): ";
        while (true) {
            cin >> choice;
            if (choice == 0) break;
            if (choice >= 1 && choice <= (int)medicationNames.size()) {
                total += medicationPrices[choice - 1];
                cout << "Added. Current total: $" << total << endl;
            }
            else {
                cout << "Invalid choice. Try again.\n";
            }
        }
        cout << "\nFinal Bill: $" << total << endl;
    }
};

// ======= Class: HospitalManagementSystem =======
// Central controller for patients, staff, appointments, pharmacy.
class HospitalManagementSystem {
private:
    vector<Patient*> patients;
    vector<Staff*> staff;
    vector<Appointment> appointments;
    Pharmacy pharmacy;

public:
    HospitalManagementSystem() {
        // === Load Staff from File ===
        ifstream staffFile("staff.txt");
        string line;
        while (getline(staffFile, line)) {
            string name, role, contact;
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, role, '|');
            getline(ss, contact, '|');

            if (!name.empty() && !role.empty() && !contact.empty()) {
                staff.push_back(new Staff(name, role, contact));
            }
        }
        staffFile.close();

        // Resize appointments based on number of staff
        appointments.resize(staff.size());

        // === Load Patients from File ===
        ifstream patientFile("patients.txt");
        while (getline(patientFile, line)) {
            string name, history, medication, treatment;
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, history, '|');
            getline(ss, medication, '|');
            getline(ss, treatment, '|');

            if (!name.empty() && !history.empty() && !medication.empty() && !treatment.empty()) {
                patients.push_back(new Patient(name, history, medication, treatment));
            }
        }
        patientFile.close();
    }

    ~HospitalManagementSystem() {
        for (auto p : patients) delete p;
        for (auto s : staff) delete s;
    }

    void showMainMenu();
    void patientMenu();
    void staffMenu();
    void appointmentMenu();
    void pharmacyMenu();
};

// ===== Patient Management =====
void HospitalManagementSystem::patientMenu() {
    int choice;
    cout << "\n===== Patient Management =====\n";
    cout << "1. Add New Patient\n2. Update Patient\n3. View All Patients\nEnter choice: ";
    cin >> choice; cin.ignore();

    if (choice == 1) {
        string name, ch, pm, t;
        cout << "Enter name: "; getline(cin, name);
        cout << "Condition history: "; getline(cin, ch);
        cout << "Prescribed meds: "; getline(cin, pm);
        cout << "Treatment: "; getline(cin, t);
        patients.push_back(new Patient(name, ch, pm, t));
        cout << "Patient added.\n";
    }
    else if (choice == 2) {
        string name;
        cout << "Enter patient name to update: "; getline(cin, name);
        bool found = false;
        for (auto p : patients) {
            if (p->getName() == name) {
                found = true;
                string ch, pm, t;
                cout << "New condition history: "; getline(cin, ch);
                cout << "New meds: "; getline(cin, pm);
                cout << "New treatment: "; getline(cin, t);
                p->updateDetails(ch, pm, t);
                cout << "Updated.\n";
                break;
            }
        }
        if (!found) cout << "Patient not found.\n";
    }
    else if (choice == 3) {
        for (auto p : patients) p->display();
    }
}

// ===== Staff Management =====
void HospitalManagementSystem::staffMenu() {
    int choice;
    cout << "\n===== Staff Management =====\n";
    cout << "1. Add Staff\n2. View Staff\nEnter choice: ";
    cin >> choice; cin.ignore();

    if (choice == 1) {
        string name, role, contact;
        cout << "Name: "; getline(cin, name);
        cout << "Role: "; getline(cin, role);
        cout << "Contact: "; getline(cin, contact);
        staff.push_back(new Staff(name, role, contact));
        appointments.push_back(Appointment());
        cout << "Staff added.\n";
    }
    else if (choice == 2) {
        cout << "\n--- Staff List ---\n";
        cout << left << setw(25) << "Name" << setw(15) << "Role" << setw(15) << "Contact" << "\n";
        cout << string(55, '-') << "\n";
        for (auto s : staff) {
            // Downcast to access Staff-specific methods
            Staff* staffMember = dynamic_cast<Staff*>(s);
            if (staffMember) {
                cout << left
                    << setw(25) << staffMember->getName()
                    << setw(15) << staffMember->getRole()
                    << setw(15) << staffMember->getContact()
                    << "\n";
            }
        }
    }

}

// ===== Appointment Management =====
void HospitalManagementSystem::appointmentMenu() {
    int choice;
    cout << "\n===== Appointment Management =====\n";
    cout << "1. Book Appointment\n2. Cancel Appointment\n3. View Appointments\nEnter choice: ";
    cin >> choice; cin.ignore();

    if (choice == 1) {
        for (size_t i = 0; i < staff.size(); i++) {
            cout << i + 1 << ". "; staff[i]->display();
        }
        int idx;
        cout << "Choose staff #: "; cin >> idx; cin.ignore();
        if (idx < 1 || idx >(int)staff.size()) return;

        if (appointments[idx - 1].booked) {
            cout << "Already booked.\n";
            return;
        }

        cout << "1. Morning\n2. Evening\nEnter shift: ";
        int shiftOpt; cin >> shiftOpt; cin.ignore();
        string shiftName = (shiftOpt == 1) ? "Morning" : "Evening";
        vector<string> slots = (shiftOpt == 1)
            ? vector<string>{"8:00 AM", "8:30 AM", "9:00 AM", "9:30 AM"}
        : vector<string>{ "2:00 PM", "2:30 PM", "3:00 PM", "3:30 PM" };

        for (size_t i = 0; i < slots.size(); i++)
            cout << i + 1 << ". " << slots[i] << endl;

        int slotChoice;
        cout << "Choose time slot: "; cin >> slotChoice; cin.ignore();

        string patientName;
        cout << "Enter patient name: "; getline(cin, patientName);
        appointments[idx - 1].book(patientName, slots[slotChoice - 1], shiftName);
        cout << "Appointment booked.\n";
    }
    else if (choice == 2) {
        for (size_t i = 0; i < staff.size(); i++) {
            cout << i + 1 << ". "; staff[i]->display();
        }
        int idx;
        cout << "Choose staff #: "; cin >> idx; cin.ignore();
        appointments[idx - 1].cancel();
        cout << "Appointment cancelled.\n";
    }
    else if (choice == 3) {
        for (size_t i = 0; i < staff.size(); i++)
            appointments[i].display(staff[i]->getName());
    }
}

// ===== Pharmacy Menu =====
void HospitalManagementSystem::pharmacyMenu() {
    int choice;
    do {
        cout << "\n===== Pharmacy =====\n";
        cout << "1. View Medications\n2. Calculate Bill\n3. Back\nEnter choice: ";
        cin >> choice; cin.ignore();

        if (choice == 1) pharmacy.showMedications();
        else if (choice == 2) pharmacy.calculateBill();
    } while (choice != 3);
}

// ===== Main Menu =====
void HospitalManagementSystem::showMainMenu() {
    int opt;
    do {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Patient Management\n2. Staff Management\n3. Appointment Management\n4. Pharmacy\n5. Exit\nEnter choice: ";
        cin >> opt; cin.ignore();

        switch (opt) {
        case 1: patientMenu(); break;
        case 2: staffMenu(); break;
        case 3: appointmentMenu(); break;
        case 4: pharmacyMenu(); break;
        case 5: cout << "Goodbye!\n"; break;
        default: cout << "Invalid option.\n";
        }
    } while (opt != 5);
}

int main() {
    HospitalManagementSystem hms;
    cout << "\n===== Welcome to Hospital Management System =====\n";
    hms.showMainMenu();
    return 0;
}


