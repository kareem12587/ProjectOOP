// main.cpp
#include <iostream>
#include <string>
#include "HospitalManager.h"
using namespace std;

void patientMenu(HospitalManager& manager);
void doctorMenu(HospitalManager& manager);
void appointmentMenu(HospitalManager& manager);
void showSubMenu(const string& title, const vector<string>& options);

int main() 
{
    cout << "Welcome to the Hospital Management System" << endl;

    HospitalManager manager;
    int choice;

    do {
        manager.showMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                patientMenu(manager);
                break;
            case 2:
                doctorMenu(manager);
                break;
            case 3:
                appointmentMenu(manager);
                break;
            case 4:
                manager.generateReport();
                break;
            case 5:
                manager.saveAllData();
                cout << "All data has been saved successfully!" << endl;
                break;
            case 6:
                manager.loadAllData();
                cout << "All data has been loaded successfully!" << endl;
                break;
            case 0:
                cout << "Thanks for using the system!" << endl;
                break;
            default:
                cout << "Incorrect choice. Please try again." << endl;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    return 0;
}

void patientMenu(HospitalManager& manager) 
{
    vector<string> options = {
        "1. Add new patient",
        "2. View all patients",
        "3. Find patient",
        "4. Delete patient",
        "5. View patient's appointments",
        "0. Back to main menu"
    };

    int choice;
    do {
        showSubMenu("Patient Management", options);
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string id, name, phone, address, medHistory;
                int age;

                cout << "Enter patient ID: ";
                getline(cin, id);
                cout << "Enter patient name: ";
                getline(cin, name);
                cout << "Enter patient age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter patient phone: ";
                getline(cin, phone);
                cout << "Enter patient address: ";
                getline(cin, address);
                cout << "Enter patient medical history: ";
                getline(cin, medHistory);

                Patient newPatient(id, name, age, phone, address, medHistory);
                manager.addPatient(newPatient);
                break;
            }
            case 2:
                manager.displayAllPatients();
                break;
            case 3: {
                string id;
                cout << "Enter patient ID: ";
                getline(cin, id);
                manager.displayPatient(id);
                break;
            }
            case 4: {
                string id;
                cout << "Enter patient ID to delete: ";
                getline(cin, id);
                manager.removePatient(id);
                break;
            }
            case 5: {
                string id;
                cout << "Enter patient ID: ";
                getline(cin, id);
                manager.displayPatientAppointments(id);
                break;
            }
            case 0:
                break;
            default:
                cout << "Incorrect choice!" << endl;
        }
    } while (choice != 0);
}

void doctorMenu(HospitalManager& manager) 
{
    vector<string> options = {
        "1. Add new doctor",
        "2. View all doctors",
        "3. Find doctor",
        "4. Delete doctor",
        "5. View doctor's appointments",
        "0. Back to main menu"
    };

    int choice;
    do {
        showSubMenu("Doctor Management", options);
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string id, name, specialization, phone, email, schedule;

                cout << "Enter doctor ID: ";
                getline(cin, id);
                cout << "Enter doctor name: ";
                getline(cin, name);
                cout << "Enter specialization: ";
                getline(cin, specialization);
                cout << "Enter phone: ";
                getline(cin, phone);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter schedule: ";
                getline(cin, schedule);

                Doctor newDoctor(id, name, specialization, phone, email, schedule);
                manager.addDoctor(newDoctor);
                break;
            }
            case 2:
                manager.displayAllDoctors();
                break;
            case 3: {
                string id;
                cout << "Enter doctor ID: ";
                getline(cin, id);
                manager.displayDoctor(id);
                break;
            }
            case 4: {
                string id;
                cout << "Enter doctor ID to delete: ";
                getline(cin, id);
                manager.removeDoctor(id);
                break;
            }
            case 5: {
                string id;
                cout << "Enter doctor ID: ";
                getline(cin, id);
                manager.displayDoctorAppointments(id);
                break;
            }
            case 0:
                break;
            default:
                cout << "Incorrect choice!" << endl;
        }
    } while (choice != 0);
}

void appointmentMenu(HospitalManager& manager) 
{
    vector<string> options = {
        "1. Book new appointment",
        "2. View all appointments",
        "3. Find appointment",
        "4. Delete appointment",
        "5. Update appointment status",
        "0. Back to main menu"
    };

    int choice;
    do {
        showSubMenu("Appointment Management", options);
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string appId, patientId, doctorId, date, time;

                cout << "Enter appointment ID: ";
                getline(cin, appId);
                cout << "Enter patient ID: ";
                getline(cin, patientId);
                cout << "Enter doctor ID: ";
                getline(cin, doctorId);
                cout << "Enter date: ";
                getline(cin, date);
                cout << "Enter time: ";
                getline(cin, time);

                Appointment newAppointment(appId, patientId, doctorId, date, time);
                manager.addAppointment(newAppointment);
                break;
            }
            case 2:
                manager.displayAllAppointments();
                break;
            case 3: {
                string id;
                cout << "Enter appointment ID: ";
                getline(cin, id);
                manager.displayAppointment(id);
                break;
            }
            case 4: {
                string id;
                cout << "Enter appointment ID to delete: ";
                getline(cin, id);
                manager.removeAppointment(id);
                break;
            }
            case 5: {
                string id, newStatus;
                cout << "Enter appointment ID: ";
                getline(cin, id);
                cout << "Enter new status (Booked/Completed/Cancelled): ";
                getline(cin, newStatus);

                Appointment* app = manager.findAppointment(id);
                if (app) {
                    app->updateStatus(newStatus);
                    cout << "Appointment status has been updated successfully!" << endl;
                } else {
                    cout << "Appointment not found!" << endl;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Incorrect choice!" << endl;
        }
    } while (choice != 0);
}

void showSubMenu(const string& title, const vector<string>& options) 
{
    cout << "\n=============== " << title << " ==============" << endl;
    for (size_t i = 0; i < options.size(); i++) {
        cout << options[i] << endl;
    }
    cout << "====================================" << endl;
    cout << "Select the required option: ";
}