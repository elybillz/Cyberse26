#ifndef CLINICMANAGER_H
#define CLINICMANAGER_H

#include "../model/PatientRecord.h"
#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include <array>

namespace clinic {

class ClinicManager {
    struct UndoAction {
        QString type;
        std::shared_ptr<PatientRecord> patient;
    };

    std::vector<std::shared_ptr<PatientRecord>> patients;
    std::queue<QString> waitingQueue;
    std::stack<UndoAction> undoStack;
    std::array<PatientRecord*, 10> recentPatients{};

public:
    const std::vector<std::shared_ptr<PatientRecord>>& allPatients() const { return patients; }
    bool addPatient(const QString &id, const QString &name, int age,
                    const QString &contact, const QString &category, QString &error);
    bool deletePatient(const QString &id, QString &error);
    bool undoLast(QString &message);
    PatientRecord* linearSearch(const QString &id);
    PatientRecord* binarySearchById(const QString &id);
    PatientRecord* recursiveSearchByName(const QString &name, int index = 0);
    void selectionSortByName();
    void insertionSortByAge();
    void addToQueue(const QString &id) { waitingQueue.push(id); }
    QString callNext();
    int waitingCount() const { return static_cast<int>(waitingQueue.size()); }
    int categoryCount(const QString &category) const;
    int pendingAppointments() const;
    std::vector<std::shared_ptr<PatientRecord>>& mutablePatients() { return patients; }
};

}
#endif
