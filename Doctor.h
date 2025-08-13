// Doctor.h
#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>
using namespace std;

class Doctor 
{
private:
    string doctorId;
    string name;
    string specialization;
    string phone;
    string email;
    string schedule;
    int patientsCount;

public:
    // Constructors
    Doctor();
    Doctor(string id, string n, string spec, string ph, string em, string sched = "");

    // Sett
    void setDoctorId(string id);
    void setName(string n);
    void setSpecialization(string spec);
    void setPhone(string ph);
    void setEmail(string em);
    void setSchedule(string sched);
    void setPatientsCount(int count);

    // Gett
    string getDoctorId() const;
    string getName() const;
    string getSpecialization() const;
    string getPhone() const;
    string getEmail() const;
    string getSchedule() const;
    int getPatientsCount() const;

    // Methods
    void addPatient();
    void removePatient();
    void updateSchedule(string newSchedule);
    void displayDoctorInfo() const;
    string toFileFormat() const;
    void fromFileFormat(string line);

    // Destructor
    ~Doctor();
};

#endif
