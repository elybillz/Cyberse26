#include "FileHandler.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

namespace clinic {
bool FileHandler::savePatients(const QString &fileName,
    const std::vector<std::shared_ptr<PatientRecord>> &patients, QString &error)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        error = file.errorString(); return false;
    }
    QTextStream out(&file);
    for (const auto &p : patients)
        out << p->getId() << "|" << p->getName().replace("|", " ") << "|"
            << p->getAge() << "|" << p->getContact().replace("|", " ") << "|"
            << p->category() << "\n";
    return true;
}

bool FileHandler::loadPatients(const QString &fileName,
    std::vector<std::shared_ptr<PatientRecord>> &patients, QString &error)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        error = file.errorString(); return false;
    }
    std::vector<std::shared_ptr<PatientRecord>> loaded;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('|');
        if (parts.size() != 5) continue;
        bool ok = false; int age = parts[2].toInt(&ok);
        if (!ok || age < 0 || age > 120 || parts[0].trimmed().isEmpty()) continue;
        if (parts[4] == "Emergency")
            loaded.push_back(std::make_shared<EmergencyPatient>(parts[0], parts[1], age, parts[3]));
        else if (parts[4] == "Follow-Up")
            loaded.push_back(std::make_shared<FollowUpPatient>(parts[0], parts[1], age, parts[3]));
        else
            loaded.push_back(std::make_shared<GeneralPatient>(parts[0], parts[1], age, parts[3]));
    }
    patients = std::move(loaded);
    return true;
}
}
