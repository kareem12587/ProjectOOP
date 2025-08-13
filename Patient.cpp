// Patient.cpp
#include "Patient.h"
// to control the time
#include <ctime>
// to change no. to text and viceversa
#include <sstream>


Patient::Patient()
{
    patientId = "";
    name = "";
    age = 0;
    phone = "";
    address = "";
    medicalHistory = "";

    //  current time
    time_t now = time(0);
    char* dt = ctime(&now);
    registrationDate = string(dt);
}


Patient::Patient(string id, string n, int a, string ph, string addr, string medHist) {
    patientId = id;
    name = n;
    age = a;
    phone = ph;
    address = addr;
    medicalHistory = medHist;

    time_t now = time(0);
    char* dt = ctime(&now);
    registrationDate = string(dt);
}

// Set
void Patient::setPatientId (string id) { patientId = id; }
void Patient::setName(string n) { name = n; }
void Patient::setAge(int a) { age = a; }
void Patient::setPhone(string ph) { phone = ph; }
void Patient::setAddress (string addr) { address = addr; }
void Patient::setMedicalHistory(string medHist) { medicalHistory = medHist; }
void Patient::setRegistrationDate(string date) { registrationDate = date; }

// Gett
string Patient::getPatientId() const { return patientId; }
string Patient::getName()  const { return name; }
int Patient::getAge() const { return age; }
string Patient::getPhone() const { return phone; }
string Patient::getAddress() const { return address; }
string Patient::getMedicalHistory() const { return medicalHistory; }
string Patient::getRegistrationDate() const { return registrationDate; }

// Update medical history
void Patient::updateMedicalHistory(string newRecord)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    string currentDate = string(dt);

    if (!medicalHistory.empty())
    {
        medicalHistory += "\n" + currentDate + ": " + newRecord;
    }
    else
    {
        medicalHistory = currentDate + ": " + newRecord;
    }
}

// Display patient information
void Patient::displayPatientInfo() const
{
    cout << "================================" << endl;
    cout << "patient info: " << endl;
    cout << "patient id : " << patientId << endl;
    cout << "name: " << name << endl;
    cout << "age: " << age << " سنة" << endl;
    cout << "phone num: " << phone << endl;
    cout << "adress: " << address << endl;
    cout << " register date: " << registrationDate;
    cout << " medival history: " << endl << medicalHistory << endl;
    cout << "========================" << endl;
}

// Convert to file
string Patient::toFileFormat() const
{
    string medHistCopy = medicalHistory;
    // to prevent ( اللغبطه   عشان مش عارف ترجمتها)
    for (int i = 0; i < medHistCopy.length(); i++) {
        if (medHistCopy[i] == '|') medHistCopy[i] = ';';
    }
    // use to_string to change num to text
    return patientId + "|" + name + "|" + to_string(age) + "|" +
           phone + "|" + address + "|" + medHistCopy + "|" + registrationDate;
}

// Create from file format
void Patient::fromFileFormat(string line)
{
    stringstream ss(line);
    string item;
    int count = 0;

    while (getline(ss, item, '|'))
    {
        switch (count)
        {
            case 0: patientId = item; break;
            case 1: name = item; break;
            case 2: age = stoi(item); break;
            case 3: phone = item; break;
            case 4: address = item; break;
            case 5:
                medicalHistory = item;

                for (int i = 0; i < medicalHistory.length(); i++) {
                    if (medicalHistory[i] == ';') medicalHistory[i] = '|';
                }
                break;
            case 6: registrationDate = item; break;
        }
        count++;
    }
}

// Destructor
Patient::~Patient()
{}
