// Patient.h
#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
using namespace std;

class Patient {
private:
    string patientId;
    string name;
    int age;
    string phone;
    string address;
    string medicalHistory;
    string registrationDate;

public:
    // Constructor
    Patient();
    Patient(string id, string n, int a, string ph, string addr, string medHist = "");

    // Set
    void setPatientId(string id);
    void setName(string n);
    void setAge(int a);
    void setPhone(string ph);
    void setAddress(string addr);
    void setMedicalHistory(string medHist);
    void setRegistrationDate(string date);

    // Get
    string getPatientId() const;
    string getName() const;
    int getAge() const;
    string getPhone() const;
    string getAddress() const;
    string getMedicalHistory() const;
    string getRegistrationDate() const;

    // Methods
    void updateMedicalHistory(string newRecord);
    void displayPatientInfo() const;
    string toFileFormat() const;
    void fromFileFormat(string line);

    // Destructor
    ~Patient();
};

#endif
