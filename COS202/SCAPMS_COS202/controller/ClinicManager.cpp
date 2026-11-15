#include "ClinicManager.h"

namespace clinic {

bool ClinicManager::addPatient(const QString &id, const QString &name, int age,
    const QString &contact, const QString &category, QString &error)
{
    if (id.trimmed().isEmpty() || name.trimmed().isEmpty() || contact.trimmed().isEmpty()) {
        error = "Please enter patient ID, name and contact."; return false;
    }
    if (age < 0 || age > 120) { error = "Patient age must be between 0 and 120."; return false; }
    if (linearSearch(id)) { error = "That patient ID already exists."; return false; }

    std::shared_ptr<PatientRecord> p;
    if (category == "Emergency") p = std::make_shared<EmergencyPatient>(id, name, age, contact);
    else if (category == "Follow-Up") p = std::make_shared<FollowUpPatient>(id, name, age, contact);
    else p = std::make_shared<GeneralPatient>(id, name, age, contact);

    patients.push_back(p);
    undoStack.push({"ADD", p});
    recentPatients[patients.size() % recentPatients.size()] = p.get();
    return true;
}

bool ClinicManager::deletePatient(const QString &id, QString &error)
{
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if ((*it)->getId() == id) {
            undoStack.push({"DELETE", *it});
            patients.erase(it);
            return true;
        }
    }
    error = "Patient ID was not found."; return false;
}

bool ClinicManager::undoLast(QString &message)
{
    if (undoStack.empty()) { message = "There is no operation to undo."; return false; }
    UndoAction action = undoStack.top(); undoStack.pop();
    if (action.type == "ADD") {
        for (auto it = patients.begin(); it != patients.end(); ++it)
            if (*it == action.patient) { patients.erase(it); break; }
        message = "Last patient registration was undone.";
    } else {
        patients.push_back(action.patient);
        message = "Last patient deletion was undone.";
    }
    return true;
}

PatientRecord* ClinicManager::linearSearch(const QString &id)
{
    for (auto &p : patients) if (p->getId() == id) return p.get();
    return nullptr;
}

PatientRecord* ClinicManager::binarySearchById(const QString &id)
{
    // Binary search requires records to be sorted by patient ID first.
    // Manually arrange records by ID using insertion sort before binary search.
    for (int i = 1; i < static_cast<int>(patients.size()); ++i) {
        auto current = patients[i];
        int j = i - 1;
        while (j >= 0 && patients[j]->getId() > current->getId()) {
            patients[j + 1] = patients[j];
            --j;
        }
        patients[j + 1] = current;
    }
    int low = 0, high = static_cast<int>(patients.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (patients[mid]->getId() == id) return patients[mid].get();
        if (patients[mid]->getId() < id) low = mid + 1;
        else high = mid - 1;
    }
    return nullptr;
}

PatientRecord* ClinicManager::recursiveSearchByName(const QString &name, int index)
{
    if (index >= static_cast<int>(patients.size())) return nullptr;
    if (patients[index]->getName().compare(name, Qt::CaseInsensitive) == 0)
        return patients[index].get();
    return recursiveSearchByName(name, index + 1);
}

void ClinicManager::selectionSortByName()
{
    for (int i = 0; i < static_cast<int>(patients.size()); ++i) {
        int smallest = i;
        for (int j = i + 1; j < static_cast<int>(patients.size()); ++j)
            if (patients[j]->getName().toLower() < patients[smallest]->getName().toLower())
                smallest = j;
        if (smallest != i) {
            auto temp = patients[i]; patients[i] = patients[smallest]; patients[smallest] = temp;
        }
    }
}

void ClinicManager::insertionSortByAge()
{
    for (int i = 1; i < static_cast<int>(patients.size()); ++i) {
        auto current = patients[i];
        int j = i - 1;
        while (j >= 0 && patients[j]->getAge() > current->getAge()) {
            patients[j + 1] = patients[j]; --j;
        }
        patients[j + 1] = current;
    }
}

QString ClinicManager::callNext()
{
    if (waitingQueue.empty()) return "The waiting queue is empty.";
    QString id = waitingQueue.front(); waitingQueue.pop();
    return "Next patient: " + id;
}

int ClinicManager::categoryCount(const QString &category) const
{
    int count = 0;
    for (const auto &p : patients) if (p->category() == category) ++count;
    return count;
}

int ClinicManager::pendingAppointments() const
{
    int count = 0;
    for (const auto &p : patients)
        for (const auto &a : p->getAppointments()) if (a.status == "Pending") ++count;
    return count;
}

}
