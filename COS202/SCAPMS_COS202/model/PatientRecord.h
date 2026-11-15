#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H

#include <QString>
#include <vector>

namespace clinic {

class Appointable {
public:
    virtual ~Appointable() = default;
    virtual bool scheduleAppointment(const QString &dateTime) = 0;
    virtual bool cancelAppointment(int appointmentIndex) = 0;
};

struct Appointment {
    QString dateTime;
    QString reason;
    QString status = "Pending";
};

class PatientRecord : public Appointable {
protected:
    QString id, name, contact;
    int age;
    std::vector<Appointment> appointments;

public:
    PatientRecord(QString patientId, QString patientName, int patientAge, QString patientContact);
    virtual ~PatientRecord() = default;

    QString getId() const { return id; }
    QString getName() const { return name; }
    QString getContact() const { return contact; }
    int getAge() const { return age; }
    const std::vector<Appointment>& getAppointments() const { return appointments; }

    void setName(const QString &value) { name = value; }
    void setAge(int value) { age = value; }
    void setContact(const QString &value) { contact = value; }

    virtual QString category() const = 0;
    virtual QString careNote() const = 0;

    bool scheduleAppointment(const QString &dateTime) override;
    bool cancelAppointment(int appointmentIndex) override;
    void completeAppointment(int appointmentIndex);
};

class GeneralPatient : public PatientRecord {
public:
    using PatientRecord::PatientRecord;
    QString category() const override { return "General"; }
    QString careNote() const override { return "Normal clinic priority"; }
};

class EmergencyPatient : public PatientRecord {
public:
    using PatientRecord::PatientRecord;
    QString category() const override { return "Emergency"; }
    QString careNote() const override { return "HIGH PRIORITY - attend immediately"; }
};

class FollowUpPatient : public PatientRecord {
public:
    using PatientRecord::PatientRecord;
    QString category() const override { return "Follow-Up"; }
    QString careNote() const override { return "Review previous treatment"; }
};

} // namespace clinic
#endif
