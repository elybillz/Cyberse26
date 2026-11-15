#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QString>
#include <vector>
#include <memory>
#include "../model/PatientRecord.h"

namespace clinic {
class FileHandler {
public:
    static bool savePatients(const QString &fileName,
        const std::vector<std::shared_ptr<PatientRecord>> &patients, QString &error);
    static bool loadPatients(const QString &fileName,
        std::vector<std::shared_ptr<PatientRecord>> &patients, QString &error);
};
}
#endif
