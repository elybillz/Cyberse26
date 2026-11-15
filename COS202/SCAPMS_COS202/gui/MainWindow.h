#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>

#include "../controller/ClinicManager.h"

namespace clinic {
class MainWindow : public QMainWindow {
    Q_OBJECT
    ClinicManager manager;
    QTableWidget *table;
    QLineEdit *idEdit, *nameEdit, *ageEdit, *contactEdit, *searchEdit, *appointmentEdit;
    QComboBox *categoryBox, *searchBox, *sortBox;
    QLabel *statusLabel;
    void refreshTable();
    void addPatient();
    void deletePatient();
    void searchPatient();
    void sortPatients();
    void scheduleAppointment();
    void saveData();
    void loadData();
    void showReports();
public:
    explicit MainWindow(QWidget *parent = nullptr);
};
}
#endif
