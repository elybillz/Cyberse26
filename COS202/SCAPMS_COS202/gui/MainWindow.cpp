#include "MainWindow.h"
#include "../utils/FileHandler.h"
#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QFileDialog>
#include <QInputDialog>
#include <QDateTime>

namespace clinic {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Smart Clinic Appointment & Patient Management System");
    resize(1050, 650);

    auto *tabs = new QTabWidget(this);
    auto *patientsPage = new QWidget;
    auto *patientLayout = new QVBoxLayout(patientsPage);
    auto *form = new QFormLayout;

    idEdit = new QLineEdit; nameEdit = new QLineEdit;
    ageEdit = new QLineEdit; contactEdit = new QLineEdit;
    categoryBox = new QComboBox;
    categoryBox->addItems({"General", "Emergency", "Follow-Up"});
    form->addRow("Patient ID:", idEdit);
    form->addRow("Full name:", nameEdit);
    form->addRow("Age:", ageEdit);
    form->addRow("Contact:", contactEdit);
    form->addRow("Patient category:", categoryBox);
    patientLayout->addLayout(form);

    auto *buttons = new QHBoxLayout;
    auto *addButton = new QPushButton("Register Patient");
    auto *deleteButton = new QPushButton("Delete Selected");
    auto *undoButton = new QPushButton("Undo Last Operation");
    buttons->addWidget(addButton); buttons->addWidget(deleteButton); buttons->addWidget(undoButton);
    patientLayout->addLayout(buttons);

    table = new QTableWidget(0, 5);
    table->setHorizontalHeaderLabels({"Patient ID", "Name", "Age", "Contact", "Category"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    patientLayout->addWidget(table);
    tabs->addTab(patientsPage, "Patient Records");

    auto *searchPage = new QWidget;
    auto *searchLayout = new QVBoxLayout(searchPage);
    auto *searchRow = new QHBoxLayout;
    searchEdit = new QLineEdit; searchEdit->setPlaceholderText("Enter patient ID or exact name");
    searchBox = new QComboBox; searchBox->addItems({"Linear Search (ID)", "Binary Search (ID)", "Recursive Search (Name)"});
    auto *searchButton = new QPushButton("Search");
    searchRow->addWidget(searchEdit); searchRow->addWidget(searchBox); searchRow->addWidget(searchButton);
    searchLayout->addLayout(searchRow);

    auto *sortRow = new QHBoxLayout;
    sortBox = new QComboBox; sortBox->addItems({"Selection Sort - Name", "Insertion Sort - Age"});
    auto *sortButton = new QPushButton("Sort Patient Table");
    sortRow->addWidget(sortBox); sortRow->addWidget(sortButton);
    searchLayout->addLayout(sortRow);
    searchLayout->addWidget(new QLabel("Search results and sorted records appear in the Patient Records tab."));
    tabs->addTab(searchPage, "Search & Sort");

    auto *appointmentPage = new QWidget;
    auto *appointmentLayout = new QVBoxLayout(appointmentPage);
    appointmentEdit = new QLineEdit; appointmentEdit->setPlaceholderText("Enter patient ID");
    auto *appointmentButton = new QPushButton("Schedule Appointment for Patient");
    auto *queueButton = new QPushButton("Add Patient to Waiting Queue");
    auto *nextButton = new QPushButton("Call Next Patient");
    appointmentLayout->addWidget(new QLabel("Patient ID:"));
    appointmentLayout->addWidget(appointmentEdit);
    appointmentLayout->addWidget(appointmentButton);
    appointmentLayout->addWidget(queueButton);
    appointmentLayout->addWidget(nextButton);
    tabs->addTab(appointmentPage, "Appointments & Queue");

    auto *reportsPage = new QWidget;
    auto *reportsLayout = new QVBoxLayout(reportsPage);
    auto *reportButton = new QPushButton("Generate Clinic Reports");
    reportsLayout->addWidget(reportButton);
    tabs->addTab(reportsPage, "Reports");

    statusLabel = new QLabel("Ready. Register a patient to begin.");
    auto *central = new QWidget;
    auto *mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(tabs);
    mainLayout->addWidget(statusLabel);
    setCentralWidget(central);

    connect(addButton, &QPushButton::clicked, this, [this]{ addPatient(); });
    connect(deleteButton, &QPushButton::clicked, this, [this]{ deletePatient(); });
    connect(undoButton, &QPushButton::clicked, this, [this]{
        QString msg; manager.undoLast(msg); refreshTable(); statusLabel->setText(msg);
    });
    connect(searchButton, &QPushButton::clicked, this, [this]{ searchPatient(); });
    connect(sortButton, &QPushButton::clicked, this, [this]{ sortPatients(); });
    connect(appointmentButton, &QPushButton::clicked, this, [this]{ scheduleAppointment(); });
    connect(queueButton, &QPushButton::clicked, this, [this]{
        QString id = appointmentEdit->text().trimmed();
        if (!manager.linearSearch(id)) { QMessageBox::warning(this, "Not found", "Register that patient first."); return; }
        manager.addToQueue(id); statusLabel->setText("Patient added to waiting queue.");
    });
    connect(nextButton, &QPushButton::clicked, this, [this]{
        statusLabel->setText(manager.callNext());
    });
    connect(reportButton, &QPushButton::clicked, this, [this]{ showReports(); });

    auto *fileMenu = menuBar()->addMenu("File");
    auto *saveAction = fileMenu->addAction("Save");
    auto *loadAction = fileMenu->addAction("Load");
    fileMenu->addSeparator(); auto *exitAction = fileMenu->addAction("Exit");
    connect(saveAction, &QAction::triggered, this, [this]{ saveData(); });
    connect(loadAction, &QAction::triggered, this, [this]{ loadData(); });
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    searchButton->setToolTip("Search by patient ID or exact patient name.");
    addButton->setToolTip("Register a new clinic patient.");
    refreshTable();
}

void MainWindow::refreshTable()
{
    table->setRowCount(0);
    int row = 0;
    for (const auto &p : manager.allPatients()) {
        table->insertRow(row);
        QStringList values{p->getId(), p->getName(), QString::number(p->getAge()), p->getContact(), p->category()};
        for (int col = 0; col < values.size(); ++col) {
            auto *item = new QTableWidgetItem(values[col]);
            if (p->category() == "Emergency") item->setBackground(QColor(255, 210, 210));
            table->setItem(row, col, item);
        }
        ++row;
    }
    statusLabel->setText(QString("Registered patients: %1 | Waiting: %2")
        .arg(manager.allPatients().size()).arg(manager.waitingCount()));
}

void MainWindow::addPatient()
{
    bool ok = false; int age = ageEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Invalid age", "Enter age as a number."); return; }
    QString error;
    if (!manager.addPatient(idEdit->text().trimmed(), nameEdit->text().trimmed(), age,
        contactEdit->text().trimmed(), categoryBox->currentText(), error)) {
        QMessageBox::warning(this, "Cannot register patient", error); return;
    }
    idEdit->clear(); nameEdit->clear(); ageEdit->clear(); contactEdit->clear();
    refreshTable();
}

void MainWindow::deletePatient()
{
    int row = table->currentRow();
    if (row < 0) { QMessageBox::information(this, "Select patient", "Select a patient row first."); return; }
    QString error;
    if (!manager.deletePatient(table->item(row, 0)->text(), error))
        QMessageBox::warning(this, "Delete failed", error);
    refreshTable();
}

void MainWindow::searchPatient()
{
    QString key = searchEdit->text().trimmed();
    if (key.isEmpty()) { QMessageBox::warning(this, "Search", "Enter an ID or name."); return; }
    PatientRecord *found = nullptr;
    int mode = searchBox->currentIndex();
    if (mode == 0) found = manager.linearSearch(key);
    else if (mode == 1) found = manager.binarySearchById(key);
    else found = manager.recursiveSearchByName(key);
    refreshTable();
    if (found) {
        QMessageBox::information(this, "Patient found",
            QString("ID: %1\nName: %2\nAge: %3\nCategory: %4\nCare note: %5")
            .arg(found->getId(), found->getName()).arg(found->getAge())
            .arg(found->category(), found->careNote()));
    } else QMessageBox::information(this, "Search result", "No matching patient was found.");
}

void MainWindow::sortPatients()
{
    if (sortBox->currentIndex() == 0) manager.selectionSortByName();
    else manager.insertionSortByAge();
    refreshTable();
    statusLabel->setText("Patient records sorted using the selected manual algorithm.");
}

void MainWindow::scheduleAppointment()
{
    QString id = appointmentEdit->text().trimmed();
    PatientRecord *p = manager.linearSearch(id);
    if (!p) { QMessageBox::warning(this, "Not found", "Patient ID does not exist."); return; }
    QString date = QDateTime::currentDateTime().addDays(1).toString("yyyy-MM-dd hh:mm");
    bool ok = false;
    date = QInputDialog::getText(this, "Schedule appointment", "Enter date and time (YYYY-MM-DD HH:MM):",
                                 QLineEdit::Normal, date, &ok);
    if (!ok) return;
    if (!p->scheduleAppointment(date)) { QMessageBox::warning(this, "Invalid", "Appointment date is required."); return; }
    QMessageBox::information(this, "Appointment", "Appointment scheduled for " + p->getName());
}

void MainWindow::saveData()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save patient records", "patients.txt", "Text files (*.txt)");
    if (fileName.isEmpty()) return;
    QString error;
    if (!FileHandler::savePatients(fileName, manager.mutablePatients(), error))
        QMessageBox::critical(this, "Save error", error);
    else QMessageBox::information(this, "Saved", "Patient records saved successfully.");
}

void MainWindow::loadData()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load patient records", "", "Text files (*.txt)");
    if (fileName.isEmpty()) return;
    QString error;
    if (!FileHandler::loadPatients(fileName, manager.mutablePatients(), error))
        QMessageBox::critical(this, "Load error", error);
    else { refreshTable(); QMessageBox::information(this, "Loaded", "Patient records loaded."); }
}

void MainWindow::showReports()
{
    QString report = "PATIENT CATEGORY DISTRIBUTION\n";
    report += QString("General patients: %1\n").arg(manager.categoryCount("General"));
    report += QString("Emergency patients: %1\n").arg(manager.categoryCount("Emergency"));
    report += QString("Follow-Up patients: %1\n").arg(manager.categoryCount("Follow-Up"));
    report += QString("\nPending appointments: %1\n").arg(manager.pendingAppointments());
    report += QString("Patients currently waiting: %1").arg(manager.waitingCount());
    QMessageBox::information(this, "Clinic Reports", report);
}

}
