// hospitalManager.cpp
#include "HospitalManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

// Constructor
HospitalManager::HospitalManager(string patFile, string docFile, string appFile)
{
    patientsFile = patFile;
    doctorsFile = docFile;
    appointmentsFile = appFile;
    loadAllData();
}

// Add Patient
bool HospitalManager::addPatient(const Patient& patient)
{
    // Check if patient exists
   for (size_t i = 0; i < patients.size(); i++)
   {
    const Patient& p = patients[i];
        if (p.getPatientId() == patient.getPatientId())
        {
            cout << "ERROR: Patient already exists!" << endl;
            return false;
        }
    }

    patients.push_back(patient);
    savePatients();
    cout << "The patient has been added successfully" << endl;
    return true;
}

// Remove Patient
bool HospitalManager::removePatient(string patientId)
{
    // lambda function
    auto it = find_if(patients.begin(), patients.end(),[patientId](const Patient& p) { return p.getPatientId() == patientId; });

    if (it != patients.end())
    {
        patients.erase(it);
        savePatients();
        cout << "Patient deleted successfully!" << endl;
        return true;
    }
    cout << "Patient not fond!" << endl;
    return false;
}

// Find Patient
Patient* HospitalManager::findPatient(string patientId)
{
   for (size_t i = 0; i < patients.size(); i++)
   {
    Patient& patient = patients[i];
        if (patient.getPatientId() == patientId)
        {
            return &patient;
        }
    }
    return nullptr;
}

// Display All Patients
void HospitalManager::displayAllPatients() const {
    if (patients.empty())
    {
        cout << "No patients found!" << endl;
        return;
    }

    cout << "\n========== List of Patients ========" << endl;
    for (size_t i = 0; i < patients.size(); i++)
    {
    const Patient& patient = patients[i];

        cout << "ID: " << patient.getPatientId()
             << " | Name: " << patient.getName()
             << " | Age: " << patient.getAge()
             << " | Phone: " << patient.getPhone() << endl;
    }
    cout << "===============================" << endl;
}

// Display Single Patient
void HospitalManager::displayPatient(string patientId) const
{
    for (size_t i = 0; i < patients.size(); i++)
    {
    const Patient& patient = patients[i];
        if (patient.getPatientId() == patientId) {
            patient.displayPatientInfo();
            return;
        }
    }
    cout << "Patient not found!" << endl;
}

// Add Doctor
bool HospitalManager::addDoctor(const Doctor& doctor) {

    for (size_t i = 0; i < doctors.size(); i++)
    {
    const Doctor& d = doctors[i];
        if (d.getDoctorId() == doctor.getDoctorId()) {
            cout << "ERROR: Doctor with this ID already exists!" << endl;
            return false;
        }
    }
    doctors.push_back(doctor);
    saveDoctors();
    cout << "The doctor has been added successfully" << endl;
    return true;
}

// Remove Doctor
bool HospitalManager::removeDoctor(string doctorId)
{
    auto it = find_if(doctors.begin(), doctors.end(),[doctorId](const Doctor& d) { return d.getDoctorId() == doctorId; });

    if (it != doctors.end())
    {
        doctors.erase(it);
        saveDoctors();
        cout << "Doctor deleted successfully!" << endl;
        return true;
    }
    cout << "Doctor not found!" << endl;
    return false;
}

// Find Doctor

Doctor* HospitalManager::findDoctor(string doctorId)
{
    for (size_t i = 0; i < doctors.size(); i++)
    {
    const Doctor& d = doctors[i];
        if (d.getDoctorId() == doctorId)
        {
            return const_cast<Doctor*>(&d);
        }
    }
    return nullptr;
}

// Display All Doctors
void HospitalManager::displayAllDoctors() const {
    if (doctors.empty()) {
        cout << "No doctors found!" << endl;
        return;
    }

    cout << "\n========== List of Doctors ==========" << endl;
    for (size_t i = 0; i < doctors.size(); i++) {
    const Doctor& d = doctors[i];
        cout << "ID: " << d.getDoctorId()
             << " | Name: " << d.getName()
             << " | Specialization: " << d.getSpecialization()
             << " | Patients: " << d.getPatientsCount() << endl;
    }
    cout << "=====================================" << endl;
}

// Display Single Doctor
void HospitalManager::displayDoctor(string doctorId) const
{
    for (size_t i = 0; i < doctors.size(); i++)
    {
    const Doctor& d = doctors[i];
        if (d.getDoctorId() == doctorId)
        {
            d.displayDoctorInfo();
            return;
        }
    }
    cout << "Doctor not found!" << endl;
}

// Add Appointment
bool HospitalManager::addAppointment(const Appointment& appointment)
{
    for (size_t i = 0; i < appointments.size(); i++)
    {
    const Appointment& a = appointments[i];
        if (a.getAppointmentId() == appointment.getAppointmentId())
        {
            cout << "ERROR: Appointment with this ID already exists!" << endl;
            return false;
        }
    }

    // Check patient and doctor exist
    bool patientExists = findPatient(appointment.getPatientId()) != nullptr;
    bool doctorExists = findDoctor(appointment.getDoctorId()) != nullptr;

    if (!patientExists) {
        cout << "ERROR: Patient does not exist!" << endl;
        return false;
    }

    if (!doctorExists)
    {
        cout << "ERROR: Doctor does not exist!" << endl;
        return false;
    }

    appointments.push_back(appointment);

    // Update doctor
    Doctor* doctor = findDoctor(appointment.getDoctorId());
    if (doctor)
    {
        doctor->addPatient();
        saveDoctors();
    }

    saveAppointments();
    cout << "The appointment has been booked successfully!" << endl;
    return true;
}

// Save Methods
void HospitalManager::saveAllData()
{
    savePatients();
    saveDoctors();
    saveAppointments();
}
// load method
void HospitalManager::loadAllData() {
    loadPatients();
    loadDoctors();
    loadAppointments();
}

bool HospitalManager::savePatients()
{
    ofstream file(patientsFile);
    if (!file.is_open())
     {
        cout << "ERROR: Cannot open patients file!" << endl;
        return false;
    }

    for (size_t i = 0; i < patients.size(); i++)
    {
    const Patient& patient = patients[i];
    file << patient.toFileFormat() << endl;
    }

    file.close();
    return true;
}

bool HospitalManager::saveDoctors()
{
    ofstream file(doctorsFile);
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open doctors file!" << endl;
        return false;
    }

    for (size_t i = 0; i < doctors.size(); i++)
    {
    const Doctor& doctor = doctors[i];
    file << doctor.toFileFormat() << endl;
    }

    file.close();
    return true;
}

bool HospitalManager::saveAppointments()
{
    ofstream file(appointmentsFile);
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open appointments file!" << endl;
        return false;
    }

     for (size_t i = 0; i < appointments.size(); i++)
     {
    const Appointment& appointment = appointments[i];

        file << appointment.toFileFormat() << endl;
    }

    file.close();
    return true;
}

bool HospitalManager::loadPatients()
{
    ifstream file(patientsFile);
    if (!file.is_open())
    {
        cout << "The patients file does not exist. It will be created when adding the first patient." << endl;
        return false;
    }

    string line;
    patients.clear();

    while (getline(file, line))
    {
        if (!line.empty())
        {
            Patient patient;
            patient.fromFileFormat(line);
            patients.push_back(patient);
        }
    }

    file.close();
    return true;
}

bool HospitalManager::loadDoctors()
{
    ifstream file(doctorsFile);
    if (!file.is_open()) {
        cout << "The doctors file does not exist. It will be created when adding the first doctor." << endl;
        return false;
    }

    string line;
    doctors.clear();

    while (getline(file, line))
    {
        if (!line.empty())
        {
            Doctor doctor;
            doctor.fromFileFormat(line);
            doctors.push_back(doctor);
        }
    }

    file.close();
    return true;
}

bool HospitalManager::loadAppointments() {
    ifstream file(appointmentsFile);
    if (!file.is_open()) {
        cout << "The appointments file does not exist. It will be created when adding the first appointment." << endl;
        return false;
    }

    string line;
    appointments.clear();

    while (getline(file, line))
     {
        if ( !line.empty() ) {
            Appointment appointment;
            appointment.fromFileFormat(line);
            appointments.push_back(appointment);
        }
    }

    file.close();
    return true;
}

// Remove Appointment
bool HospitalManager::removeAppointment(string appointmentId)
{
    auto it = find_if(appointments.begin(), appointments.end(),[appointmentId](const Appointment& a) { return a.getAppointmentId() == appointmentId; });

    if (it != appointments.end())
    {
        // Update doctor
        Doctor* doctor = findDoctor (it->getDoctorId());
        if (doctor)
        {
            doctor->removePatient();
            saveDoctors();
        }

        appointments.erase(it);
        saveAppointments();
        cout << "Appointment deleted successfully!" << endl;
        return true;
    }
    cout << "Appointment not found!" << endl;
    return false;
}

// Find Appointment
Appointment* HospitalManager::findAppointment(string appointmentId)
{

    for (size_t i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments[i];
        if (a.getAppointmentId() == appointmentId)
        {
            return const_cast<Appointment*>(&a);
        }
    }
    return nullptr;
}

// Display All Appointments
void HospitalManager::displayAllAppointments() const
{
    if (appointments.empty())
    {
        cout << "No appointments found!" << endl;
        return;
    }

    cout << "\n======== Appointments List ========" << endl;
    for (const auto& appointment : appointments) {
        cout << "Appointment ID: " << appointment.getAppointmentId ()
             << " | Patient: " << appointment.getPatientId ()
             << " | Doctor: " << appointment.getDoctorId ()
             << " | Date: " << appointment.getDate ()
             << " | Status: " << appointment.getStatus () <<endl;
    }
    cout << "===================================" << endl;
}

// Display Single Appointment
void HospitalManager::displayAppointment(string appointmentId) const
{
     for (size_t i = 0; i < appointments.size(); i++)
    {
        const Appointment& a = appointments[i];
        if (a.getAppointmentId() == appointmentId)
        {
            a.displayAppointmentInfo();
            return;
        }
    }
    cout << "Appointment not found!" << endl;
}

// Display Patient Appointments
void HospitalManager::displayPatientAppointments(string patientId) const
{
    bool found = false;
    cout << "\n========== Patient " << patientId << " Appointments =========" << endl;

    for (const auto& appointment : appointments)
    {
        if (appointment.getPatientId() == patientId)
        {
            cout << "Appointment ID: " << appointment.getAppointmentId ()
                 << " | Doctor: " << appointment.getDoctorId ()
                 << " | Date: " << appointment.getDate ()
                 << " | Time: " << appointment.getTime ()
                 << " | Status: " << appointment.getStatus () << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No appointments found for this patient!" << endl;
    }
    cout << "======================================================" << endl;
}


// Display Doctor Appointments
void HospitalManager::displayDoctorAppointments(string doctorId) const
{
    bool found = false;
    cout << "\n========== Doctor " << doctorId << " Appointments =========" << endl;

    for (const auto& appointment : appointments)
    {
        if (appointment.getDoctorId() == doctorId)
        {
            cout << "Appointment ID: " << appointment.getAppointmentId ()
                 << " | Patient: " << appointment.getPatientId ()
                 << " | Date: " << appointment.getDate()
                 << " | Time: " << appointment.getTime ()
                 << " | Status: " << appointment.getStatus () << endl;
            found = true;
        }
    }

    if (!found)
     {
        cout << "No appointments found for this doctor!" << endl;
    }
    cout << "=====================================================" << endl;
}

// Utility Methods
int HospitalManager::getPatientsCount() const
{
    return patients.size();
}

int HospitalManager::getDoctorsCount() const
{
    return doctors.size();

}

int HospitalManager::getAppointmentsCount() const
{
    return appointments.size();
}

// Generate Report
void HospitalManager::generateReport() const
{
    cout << "\n=============== Hospital Report ===============" << endl;
    cout << "Total Patients: " << getPatientsCount() << endl;
    cout << "Total Doctors: " << getDoctorsCount() << endl;
    cout << "Total Appointments: " << getAppointmentsCount() << endl;
    cout << "===============================================" << endl;
}

// Show Main Menu
void HospitalManager::showMainMenu() const
{
    cout << "\n=============== Hospital Management System ==============" << endl;
    cout << "1. Manage Patients" << endl;
    cout << "2. Manage Doctors" << endl;
    cout << "3. Manage Appointments" << endl;
    cout << "4. View Reports" << endl;
    cout << "5. Save All Data" << endl;
    cout << "6. Load Data from Files" << endl;
    cout << "0. Exit" << endl;
    cout << "========================================================" << endl;
    cout << "Choose operation: ";
}

// Destructor
HospitalManager::~HospitalManager()
{
    saveAllData();
}
