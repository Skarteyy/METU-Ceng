#include "Hospital.h"

#include <cassert>

std::ostream& operator<<(std::ostream& s, const EventResult& r)
{
    int enumIndex = (r.type < 0 || r.type > InvalidEvent) ? InvalidEvent : r.type;
    s << "Time[" << r.timePoint << "]: ";
    switch(enumIndex)
    {
        case DoctorQueueCheck:
            s << "Doctor(" << r.patientIdOrDoctorIndex
              << ") checked the patient queue." << std::endl;
            break;
        case RegistrationQueueEntrance:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") " << "is registering." << std::endl;
            break;
        case RegistrationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") registeration is complete." << std::endl;
            break;
        case ExaminationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") examination is completed." << std::endl;
            break;
        case InvalidEvent:
        default:
            s << "Invalid Event!" << std::endl;
            break;
    }

    return s;
}

int Doctor::ExamTimeOf(const Patient& patient) const
{
    int r;
    r = (MAX_PATIENT_PRIORTIY - patient.getPriority() + 1) * baselineExaminationTime;
    return r;
}


Hospital::Hospital(const Doctor& d0,
                   const Doctor& d1,
                   int rTime, int docTime)
    : currentTime(0)
    , registrationTime(rTime)
    , doctorCheckTime(docTime)
{
    doctors[0] = d0;
    doctors[1] = d1;
    patientsInExam[0] = NULL;
    patientsInExam[1] = NULL;
    
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 0));
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 1));
}

Hospital::~Hospital()
{
    if (regQueue.IsEmpty()) return;
    
    while (!regQueue.IsEmpty()){
        Patient* deqPatient = regQueue.Dequeue();
        delete deqPatient;
    }
}

void Hospital::AddPatient(int id, int priority)
{
    if (priority < 0 || MAX_PATIENT_PRIORTIY < priority) return;
    Patient* newPatient = new Patient(id, priority);
    regQueue.Enqueue(newPatient);
    eventQueue.InsertItem(new Event(currentTime, RegistrationQueueEntrance, newPatient));
}

EventResult Hospital::DoSingleEventIteration()
{
    EventResult result;
    Event* currEvent = eventQueue.RemoveFirstItem();
    currentTime = currEvent->getTimePoint();
    if (!currEvent) return result;
    switch(currEvent->getType()){
        case RegistrationQueueEntrance:{
            const Patient* newPatient = currEvent->getPatient();
            
            int id = newPatient->getId();
     
            Event* nextEvent = new Event(currentTime + registrationTime, RegistrationEnd, newPatient);/**/
           
            eventQueue.InsertItem(nextEvent);
            
            result.type = RegistrationQueueEntrance;
            result.patientIdOrDoctorIndex = id;
            result.timePoint = currEvent->getTimePoint();
            break;
        }
        case RegistrationEnd: {
            
            Patient* newPatient = regQueue.Dequeue(); 
            int id = newPatient->getId();
            
            examQueue.InsertItem(newPatient);

            result.type = RegistrationEnd;
            result.patientIdOrDoctorIndex = id;
            result.timePoint = currEvent->getTimePoint();
            break;
        }
        case DoctorQueueCheck: {
            int doctorIndex = currEvent->getDoctorIndex();
            if (examQueue.IsEmpty()){
                Event* nextEvent = new Event(currentTime + doctorCheckTime, DoctorQueueCheck, doctorIndex);
                eventQueue.InsertItem(nextEvent);
            }
            else{
                Patient* newPatient = examQueue.RemoveFirstItem();
                patientsInExam[doctorIndex] = newPatient;
                if (doctorIndex != -1) eventQueue.InsertItem(new Event(currentTime + doctors[doctorIndex].ExamTimeOf(*newPatient), ExaminationEnd, newPatient));
            }
            result.type = DoctorQueueCheck;
            result.patientIdOrDoctorIndex = currEvent->getDoctorIndex();
            result.timePoint = currEvent->getTimePoint();
            break;
        }
        case ExaminationEnd:{
            int doctorIndex = -1;
            int id = -1;
            for (int j = 0; j <2; j++){
                if (currEvent->getPatient() == patientsInExam[j]){
                    doctorIndex = j;
                }
            }
            if (patientsInExam[doctorIndex]) {
                id = patientsInExam[doctorIndex]->getId();
                delete patientsInExam[doctorIndex];
                patientsInExam[doctorIndex] = NULL;
            }
            if (examQueue.IsEmpty()){
                Event* nextEvent = new Event(currentTime + doctorCheckTime, DoctorQueueCheck, doctorIndex);
                eventQueue.InsertItem(nextEvent);
            }
            else{
                Patient* newPatient = examQueue.RemoveFirstItem();
                patientsInExam[doctorIndex] = newPatient;
                eventQueue.InsertItem(new Event(currentTime + doctors[doctorIndex].ExamTimeOf(*newPatient), ExaminationEnd, newPatient));
                
            }
            result.type = ExaminationEnd;
            result.patientIdOrDoctorIndex = id;
            result.timePoint = currEvent->getTimePoint();
            break;
        }
        default:
            break;
    }
    delete currEvent;
    return result; 
}
















