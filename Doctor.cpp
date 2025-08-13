// Doctor.cpp
#include "Doctor.h"
#include <sstream>


Doctor::Doctor() 
{
    doctorId = "";
    name = "";
    specialization = "";
    phone = "";
    email = "";
    schedule = "";
    patientsCount = 0;
}

// Parameterized Constructor
Doctor::Doctor(string id, string n, string spec, string ph, string em, string sched) 
{
    doctorId = id;
    name = n;
    specialization = spec;
    phone = ph;
    email = em;
    schedule = sched;
    patientsCount = 0;
}

// Setters
void Doctor::setDoctorId(string id) { doctorId = id; }
void Doctor::setName(string n) { name = n; }
void Doctor::setSpecialization(string spec) { specialization = spec; }
void Doctor::setPhone(string ph) { phone = ph; }
void Doctor::setEmail(string em) { email = em; }
void Doctor::setSchedule(string sched) { schedule = sched; }
void Doctor::setPatientsCount(int count) { patientsCount = count; }

// Getters
string Doctor::getDoctorId() const { return doctorId; }
string Doctor::getName() const { return name; }
string Doctor::getSpecialization() const { return specialization; }
string Doctor::getPhone() const { return phone; }
string Doctor::getEmail() const { return email; }
string Doctor::getSchedule() const { return schedule; }
int Doctor::getPatientsCount() const { return patientsCount; }

// Add patient
void Doctor::addPatient() {
    patientsCount++;
}

// Remove patient
void Doctor::removePatient() {
    if (patientsCount > 0) {
        patientsCount--;
    }
}

// Update schedule
void Doctor::updateSchedule(string newSchedule)
{
    schedule = newSchedule;
}

// Display doctor information
void Doctor::displayDoctorInfo() const {
    cout << "=============================" << endl;
    cout << "doc info :" << endl;
    cout << " doc id: " << doctorId << endl;
    cout << "name: " << name << endl;
    cout << "specialization: " << specialization << endl;
    cout << "phone no: " << phone << endl;
    cout << " email: " << email << endl;
    cout << " table: " << schedule << endl;
    cout << " no of patient: " << patientsCount << endl;
    cout << "================================" << endl;
}

// Convert to file format
string Doctor::toFileFormat() const
{
    string schedCopy = schedule;
    for (int i = 0; i < schedCopy.length(); i++)
    {
        if (schedCopy[i] == '|') schedCopy[i] = ';';
    }

    return doctorId + "|" + name + "|" + specialization + "|" +
           phone + "|" + email + "|" + schedCopy + "|" + to_string(patientsCount);
}

// Create from file format
void Doctor::fromFileFormat(string line) 
{
    stringstream ss(line);
    string item;
    int count = 0;
    

    while (getline(ss, item, '|'))
    {
        switch (count)
        {
            case 0: doctorId = item; break;
            case 1: name = item; break;
            case 2: specialization = item; break;
            case 3: phone = item; break;
            case 4: email = item; break;
            case 5:
                schedule = item;
                for (int i = 0; i < schedule.length(); i++) {
                    if (schedule[i] == ';') schedule[i] = '|';
                }
                break;
            case 6: patientsCount = stoi(item); break;
        }
        count++;
    }
}


Doctor::~Doctor()
{

}
