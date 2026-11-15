COS202 - SMART CLINIC APPOINTMENT & PATIENT MANAGEMENT SYSTEM (SCAPMS)

REQUIREMENTS
- Qt Creator
- Qt 6 with the MinGW kit matching your installed compiler
- Qt Widgets module

OPENING THE PROJECT
1. Extract the SCAPMS_COS202 folder.
2. Open Qt Creator.
3. Choose File > Open File or Project.
4. Select SCAPMS.pro.
5. Select a Qt 6 MinGW kit when prompted.
6. Click Configure Project.
7. Click the green Run button.

BUILDING AN EXE
1. Select the MinGW kit.
2. Choose Build > Build Project "SCAPMS" (Ctrl+B).
3. The executable is normally created in a build folder such as:
   build-SCAPMS-Desktop_Qt_6_x_MinGW_64_bit-Debug/debug/SCAPMS.exe
4. For a cleaner submission, change the build configuration to Release and build again.
5. Open the matching Qt MinGW command prompt (or use the Qt installation's bin folder).
6. Run:
   windeployqt "FULL_PATH_TO_SCAPMS.exe"
   This copies the Qt runtime DLLs and plugins needed beside the EXE.
7. Test the deployed folder on a Windows PC that does not have Qt Creator installed.

IMPORTANT
- Do not send only the EXE. Send the deployed folder containing the EXE, Qt DLLs and platforms folder.
- This is a student starter implementation. Test every feature and complete the additional coursework items before final submission.
- Current save/load stores patient details and categories. Appointment records are held during the running session but are not yet included in the saved text file.
- Binary search sorts the vector by ID before searching. This is intentional because binary search requires sorted data.
- The two manual sorting algorithms are Selection Sort (name) and Insertion Sort (age).
- The recursive search looks up an exact patient name.
