// Appointment.cpp
#include "Appointment.h"
#include <sstream>

// Default Constructor
Appointment::Appointment() {
    appointmentId = "";
    patientId = "";
    doctorId = "";
    date = "";
    time = "";
    status = "Booked";
}

// Parameterized Constructor
Appointment::Appointment(string appId, string patId, string docId, string appointmentDate, string appointmentTime, string appointmentStatus) {
    appointmentId = appId;
    patientId = patId;
    doctorId = docId;
    date = appointmentDate;
    time = appointmentTime;
    status = appointmentStatus;
}

// Display appointment details
void Appointment::displayAppointment() const {
    cout << "===========================================" << endl;
    cout << "Appointment Details:" << endl;
    cout << "===========================================" << endl;
    cout << "Appointment ID: " << appointmentId << endl;
    cout << "Patient ID: " << patientId << endl;
    cout << "Doctor ID: " << doctorId << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << time << endl;
    cout << "Status: " << status << endl;
    cout << "===========================================" << endl;
}

// Display appointment info (alias for displayAppointment)
void Appointment::displayAppointmentInfo() const {
    displayAppointment();
}

// Convert appointment to string for file operations
string Appointment::toString() const {
    return appointmentId + "," + patientId + "," + doctorId + "," + date + "," + time + "," + status;
}

// Convert to file format (same as toString but with | separator)
string Appointment::toFileFormat() const {
    return appointmentId + "|" + patientId + "|" + doctorId + "|" + date + "|" + time + "|" + status;
}

// Create from file format
void Appointment::fromFileFormat(string line) {
    stringstream ss(line);
    string item;
    int count = 0;

    while (getline(ss, item, '|')) {
        switch (count) {
            case 0: appointmentId = item; break;
            case 1: patientId = item; break;
            case 2: doctorId = item; break;
            case 3: date = item; break;
            case 4: time = item; break;
            case 5: status = item; break;
        }
        count++;
    }
}

// Destructor
Appointment::~Appointment() {
    // Nothing specific to clean up for now
}