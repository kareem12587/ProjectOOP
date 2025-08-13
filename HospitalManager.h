// HospitalManager.h
#ifndef HOSPITAL_MANAGER_H
#define HOSPITAL_MANAGER_H

#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class HospitalManager 
{
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

    string patientsFile;
    string doctorsFile;
    string appointmentsFile;

public:
    // Constructor
    HospitalManager(string patFile = "patients.txt", string docFile = "doctors.txt", string appFile = "appointments.txt");

    // Patient Management
    bool addPatient(const Patient& patient);
    bool removePatient(string patientId);
    Patient* findPatient(string patientId);
    void displayAllPatients() const;
    void displayPatient(string patientId) const;

    // Doctor Management
    bool addDoctor(const Doctor& doctor);
    bool removeDoctor(string doctorId);
    Doctor* findDoctor(string doctorId);
    void displayAllDoctors() const;
    void displayDoctor(string doctorId) const;

    // Appointment Management
    bool addAppointment(const Appointment& appointment);
    bool removeAppointment(string appointmentId);
    Appointment* findAppointment(string appointmentId);
    void displayAllAppointments() const;
    void displayAppointment(string appointmentId) const;
    void displayPatientAppointments(string patientId) const;
    void displayDoctorAppointments(string doctorId) const;

    // File 
    void saveAllData();
    void loadAllData();
    bool savePatients();
    bool saveDoctors();
    bool saveAppointments();
    bool loadPatients();
    bool loadDoctors();
    bool loadAppointments();

    // Utility Methods
    int getPatientsCount() const;
    int getDoctorsCount() const;
    int getAppointmentsCount() const;
    void generateReport() const;
    void showMainMenu() const;

    // Destructor
    ~HospitalManager();
};

#endif