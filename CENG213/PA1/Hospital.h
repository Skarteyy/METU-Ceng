#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "FCFSList.h"
#include "SortedList.h"
#include "Actors.h"

struct EventResult
{
    EventType type;
    int patientIdOrDoctorIndex;
    int timePoint;
};

std::ostream& operator<<(std::ostream&, const EventResult& r);

class Hospital
{
    friend std::ostream& operator<<(std::ostream& stream, const Hospital& h);

    private:
    // Lifetime of patients are handled by these queues
    // Start on the reg queue,
    // Move to the exam queue
    // After the exam is done, delete the patient
    FCFSList<Patient*>  regQueue;
    SortedList<Patient> examQueue;
    // Priority Queue for events
    SortedList<Event>   eventQueue;
    // Doctors in the hospital
    Doctor      doctors[2];
    Patient*    patientsInExam[2];

    int         currentTime;
    int         registrationTime;
    int         doctorCheckTime;

    public:
    // Constructors & Destructor
                    Hospital(const Doctor& d0,
                             const Doctor& d1,
                             int registrationTime,
                             int doctorCheckTime);
                    ~Hospital();

    // Only two functionalities
    void        AddPatient(int id, int priority);
    EventResult DoSingleEventIteration();

};

#endif
