#ifndef ACTORS_H
#define ACTORS_H

#include <cassert>
//==========================================//
//   All these functions are implemented!   //
// You should not add anything to this file //
//==========================================//
static const int MAX_PATIENT_PRIORTIY = 4;

class Patient
{
    friend std::ostream& operator<<(std::ostream&, const Patient&);

    private:
    int     id;
    int     priorityLevel;

    public:
    // Constructors & Destructor
            Patient();
            Patient(int id, int priority);
    //
    int     getId() const;
    int     getPriority() const;
    // For SortedList
    bool    operator<(const Patient& other) const;
    bool    operator==(const Patient& other) const;
    bool    operator<(int value) const;
    bool    operator==(int value) const;
    
    // For ChangePriority function ins "SortedList"
    void    setPriority(int priority);
};

//==========================================//
enum EventType
{
    RegistrationQueueEntrance,
    RegistrationEnd,
    //
    DoctorQueueCheck,
    ExaminationEnd,
    //
    InvalidEvent
};

class Event
{
    friend std::ostream& operator<<(std::ostream&, const Event&);

    private:
    int             timePoint;
    EventType       type;

    const Patient*  patient;
    int             doctorIndex;

    public:
    // Constructors & Destructor
    Event();
    Event(int timePointIn, EventType type,
          const Patient* patient);
    Event(int timePointIn, EventType type,
          int doctorIndex);
    // For SortedList
    bool        operator<(const Event& other) const;
    bool        operator==(const Event& other) const;
    bool        operator<(int value) const;
    bool        operator==(int value) const;

    int             getTimePoint() const;
    EventType       getType() const;
    const Patient*  getPatient() const;
    int             getDoctorIndex() const;
    // For change priority function ins "SortedList"
    void            setPriority(int timePoint);
};

//============================================//
class Doctor
{
    private:
    int baselineExaminationTime;

    public:
    // Constructors & Destructor
            Doctor(int baselineExamTime = 0);
    //
    int     ExamTimeOf(const Patient& patient) const;
};

//============================================//
//              IMPLEMENTATIONS               //
//============================================//
inline std::ostream& operator<<(std::ostream& s, const Patient& p)
{
    s << "P[" << p.id << ", " << p.priorityLevel << "]";
    return s;
}

// Constructors & Destructor
inline Patient::Patient()
    : id(-1)
    , priorityLevel(-1)
{}

inline Patient::Patient(int idIn, int priority)
    : id(idIn)
    , priorityLevel(priority)
{}

inline int Patient::getId() const
{
    return id;
}

inline int Patient::getPriority() const
{
    return priorityLevel;
}

inline bool Patient::operator<(const Patient& other) const
{
    return priorityLevel < other.priorityLevel;
}

inline bool Patient::operator==(const Patient& other) const
{
    return priorityLevel == other.priorityLevel;
}

inline bool Patient::operator<(int value) const
{
    return priorityLevel < value;
}

inline bool Patient::operator==(int value) const
{
    return priorityLevel == value;
}

inline void Patient::setPriority(int prio)
{
    priorityLevel = prio;
}

inline std::ostream& operator<<(std::ostream& s, const Event& e)
{
    static const char* const EnumLookup[5] =
    {
        "RegEnter",
        "RegEnd",
        "DocCheck",
        "ExamEnd",
        "Invalid"
    };

    int enumIndex = (e.type < 0 || e.type > InvalidEvent) ? InvalidEvent : e.type;
    const char* enumName = EnumLookup[enumIndex];

    if(e.type == DoctorQueueCheck)
    {
        s << "E[" << e.timePoint << ", " << enumName << ", " << e.doctorIndex << "]";
    }
    else
    {
        s << "E[" << e.timePoint << ", " << enumName << ", " << *e.patient << "]";
    }
    return s;
}

inline Event::Event()
    : timePoint(-1)
    , type(InvalidEvent)
    , patient(NULL)
    , doctorIndex(-1)
{}

inline Event::Event(int timePointIn, EventType typeIn,
                    const Patient* patientIn)
    : timePoint(timePointIn)
    , type(typeIn)
    , patient(patientIn)
    , doctorIndex(-1)
{
    assert(type != DoctorQueueCheck);
}

inline Event::Event(int timePointIn, EventType typeIn,
                    int doctorIndexIn)
    : timePoint(timePointIn)
    , type(typeIn)
    , patient(NULL)
    , doctorIndex(doctorIndexIn)
{
    assert(type == DoctorQueueCheck);
}

inline bool Event::operator<(const Event& other) const
{
    return timePoint < other.timePoint;
}

inline bool Event::operator==(const Event& other) const
{
    return timePoint == other.timePoint;
}

inline bool Event::operator<(int value) const
{
    return timePoint < value;
}

inline bool Event::operator==(int value) const
{
    return timePoint == value;
}

inline int Event::getTimePoint() const
{
    return timePoint;
}

inline EventType Event::getType() const
{
    return type;
}

inline const Patient* Event::getPatient() const
{
    return patient;
}

inline int Event::getDoctorIndex() const
{
    return doctorIndex;
}

inline void Event::setPriority(int tp)
{
    timePoint = tp;
}

inline Doctor::Doctor(int baselineExamTime)
    : baselineExaminationTime(baselineExamTime)
{}

#endif
