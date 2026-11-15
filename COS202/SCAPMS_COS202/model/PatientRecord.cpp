#include "PatientRecord.h"

namespace clinic {

PatientRecord::PatientRecord(QString patientId, QString patientName, int patientAge, QString patientContact)
    : id(patientId), name(patientName), contact(patientContact), age(patientAge) {}

bool PatientRecord::scheduleAppointment(const QString &dateTime)
{
    if (dateTime.trimmed().isEmpty()) return false;
    appointments.push_back({dateTime, "Clinic consultation", "Pending"});
    return true;
}

bool PatientRecord::cancelAppointment(int appointmentIndex)
{
    if (appointmentIndex < 0 || appointmentIndex >= static_cast<int>(appointments.size()))
        return false;
    appointments[appointmentIndex].status = "Cancelled";
    return true;
}

void PatientRecord::completeAppointment(int appointmentIndex)
{
    if (appointmentIndex >= 0 && appointmentIndex < static_cast<int>(appointments.size()))
        appointments[appointmentIndex].status = "Completed";
}

} // namespace clinic
