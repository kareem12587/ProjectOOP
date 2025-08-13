// Appointment.h
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>
using namespace std;

class Appointment 
{
private:
    string appointmentId;
    string patientId;
    string doctorId;
    string date;
    string time;
    string status; 

public:
    // Constructor
    Appointment();
    Appointment(string appId, string patId, string docId, string appointmentDate, string appointmentTime, string appointmentStatus = "Booked");

    // Getters
    string getAppointmentId() const { return appointmentId; }
    string getPatientId() const { return patientId; }
    string getDoctorId() const { return doctorId; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getStatus() const { return status; }

    // Setters
    void setAppointmentId(string appId) { appointmentId = appId; }
    void setPatientId(string patId) { patientId = patId; }
    void setDoctorId(string docId) { doctorId = docId; }
    void setDate(string appointmentDate) { date = appointmentDate; }
    void setTime(string appointmentTime) { time = appointmentTime; }
    void setStatus(string appointmentStatus) { status = appointmentStatus; }

    // Methods
    void updateStatus(string newStatus) { status = newStatus; }
    void displayAppointment() const;
    void displayAppointmentInfo() const;  
    string toString() const;
    string toFileFormat() const;          
    void fromFileFormat(string line);     

    // Destructor
    ~Appointment();
    
};

#endif