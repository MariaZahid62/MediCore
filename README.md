# MediCore
A console-based Hospital Management System built in C++ using Object-Oriented Programming (OOP), designed to streamline patient registration, staff management, appointment scheduling, and pharmacy billing.

---

##  Table of Contents

- [Overview](#overview)
- [Key Features](#key-features)
- [Technologies Used](#technologies-used)
- [OOP Concepts Implemented](#oop-concepts-implemented)
- [Getting Started](#getting-started)
  - [Compiling and Running the Code](#compiling-and-running-the-code)
  - [User Interaction](#user-interaction)
- [Example Program Flow](#example-program-flow)
- [Learning Outcomes](#learning-outcomes)
- [Author](#author)
- [License](#license)

---

##  Overview

**MediCore** is a simplified yet functional Hospital Management System built for academic and demonstration purposes. It handles basic operations like patient registration, appointment scheduling, staff tracking, and pharmacy billing – all from a console interface. Ideal for learning OOP and file handling in C++.

---

##  Key Features

- **Patient Management**
  - Add new patients with demographic and health details
  - View and search patient records

- **Staff Management**
  - Add and manage doctors, nurses, and admin staff
  - View staff roster and contact info

- **Appointment Scheduling**
  - Schedule and manage appointments for patients
  - Assign doctors to specific time slots

- **Pharmacy Billing**
  - Basic billing system to record prescribed medicines
  - Calculate and display bill summaries

---

##  Technologies Used

- **Language:** C++
- **Compiler:** g++ / Visual Studio (MSVC)
- **IDE:** Visual Studio / Code::Blocks / VS Code
- **Concepts:** OOP, File I/O, Console I/O

---

##  OOP Concepts Implemented

- **Classes & Objects**  
  - Separate classes for Patient, Staff, Appointment, and Billing

- **Encapsulation**  
  - Private attributes with public setters/getters

- **Inheritance**  
  - Base class for Person → Derived: Patient, Staff

- **Polymorphism**  
  - Virtual functions for displaying person info

- **File Handling**  
  - Using `fstream` to store and retrieve data

---

##  Getting Started

###  Compiling and Running the Code

1. **Open the project** in Visual Studio or any C++ IDE.
2. **Build the solution** (e.g., press `Ctrl+Shift+B` in Visual Studio).
3. **Run the executable**

---
## User Interaction
Upon launching, you will see:

Welcome to MediCore – Hospital Management System

1. Register Patient
2. View Patient Records
3. Manage Staff
4. Schedule Appointment
5. Generate Bill
6. Exit

(Just type the number corresponding to the action you want to perform.)

---
## Example Program Flow

1. Registers a patient
2. Schedules an appointment with a doctor
3. Generates a bill for medication
4. View patient history
5. Logs out or exits the program

---
## Learning Outcomes
Apply real-world OOP principles in C++
Work with text file handling for data persistence
Practice writing clean, modular code
Understand how hospital systems are digitally managed

---

## Author
Maria Zahid
Student – BS Computer Science, Bahria University
🔗 LinkedIn Profile
📫 Email: your.email@example.com

---
## License
This project is open-source and available under the MIT License.
