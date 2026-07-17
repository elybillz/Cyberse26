import ui.AddCourseDialog;
package ui;

import model.Course;
import service.CourseManager;
import service.FileManager;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;

public class Dashboard extends JFrame {

    private JTable table;
    private DefaultTableModel tableModel;
    private JLabel statusLabel;

    private CourseManager manager;

    private JButton addButton;
    private JButton editButton;
    private JButton deleteButton;
    private JButton searchButton;
    private JButton sortButton;
    private JButton statisticsButton;
    private JButton exitButton;

    public Dashboard() {

        manager = new CourseManager();
        manager.setCourses(FileManager.loadCourses());

        setTitle("Student Course Management System");

        setSize(1000,650);

        setLocationRelativeTo(null);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BorderLayout(10,10));

        // =========================================
        // HEADER
        // =========================================

        JPanel headerPanel = new JPanel();

        headerPanel.setLayout(new GridLayout(3,1));

        JLabel universityLabel =
                new JLabel("MIVA OPEN UNIVERSITY",
                        SwingConstants.CENTER);

        universityLabel.setFont(
                new Font("Arial",
                        Font.BOLD,
                        28));

        JLabel systemLabel =
                new JLabel("STUDENT COURSE MANAGEMENT SYSTEM",
                        SwingConstants.CENTER);

        systemLabel.setFont(
                new Font("Arial",
                        Font.BOLD,
                        18));

        JLabel developerLabel =
                new JLabel("Developed By : NWOYE ELEAZAR",
                        SwingConstants.CENTER);

        developerLabel.setFont(
                new Font("Arial",
                        Font.PLAIN,
                        15));

        headerPanel.add(universityLabel);
        headerPanel.add(systemLabel);
        headerPanel.add(developerLabel);

        add(headerPanel, BorderLayout.NORTH);

        // =========================================
        // TOOL BAR
        // =========================================

        JPanel toolBar =
                new JPanel(new FlowLayout(
                        FlowLayout.LEFT));

        addButton =
                new JButton("Add");

        editButton =
                new JButton("Edit");

        deleteButton =
                new JButton("Delete");

        searchButton =
                new JButton("Search");

        sortButton =
                new JButton("Sort");

        statisticsButton =
                new JButton("Statistics");

        exitButton =
                new JButton("Exit");

        toolBar.add(addButton);
        toolBar.add(editButton);
        toolBar.add(deleteButton);
        toolBar.add(searchButton);
        toolBar.add(sortButton);
        toolBar.add(statisticsButton);
        toolBar.add(exitButton);

        // =========================================
        // TABLE
        // =========================================

        String[] columns = {

                "Course Code",

                "Course Title",

                "Unit"

        };

        tableModel =
                new DefaultTableModel(columns,0){

                    @Override
                    public boolean isCellEditable(int row,
                                                  int column){

                        return false;

                    }

                };

        table =
                new JTable(tableModel);

        table.setRowHeight(25);

        table.getTableHeader().setFont(
                new Font("Arial",
                        Font.BOLD,
                        14));

        JScrollPane scrollPane =
                new JScrollPane(table);

        JPanel centerPanel =
                new JPanel(new BorderLayout());

        centerPanel.add(toolBar,
                BorderLayout.NORTH);

        centerPanel.add(scrollPane,
                BorderLayout.CENTER);

        add(centerPanel,
                BorderLayout.CENTER);

        // =========================================
        // STATUS BAR
        // =========================================

        statusLabel =
                new JLabel(" Ready");

        add(statusLabel,
                BorderLayout.SOUTH);

        // =========================================
        // LOAD COURSES INTO TABLE
        // =========================================

        refreshTable();
        // =========================================
        // BUTTON EVENTS
        // =========================================

        addButton.addActionListener(e -> {

    AddCourseDialog dialog = new AddCourseDialog(
            this,
            manager,
            this::refreshTable
    );

    dialog.setVisible(true);

});

        editButton.addActionListener(e -> {

            int row = table.getSelectedRow();

            if (row == -1) {

                JOptionPane.showMessageDialog(
                        this,
                        "Select a course first.");

                return;

            }

            String code = tableModel.getValueAt(row,0).toString();

            String title = JOptionPane.showInputDialog(
                    this,
                    "New Course Title:",
                    tableModel.getValueAt(row,1));

            if(title == null)
                return;

            String unitText = JOptionPane.showInputDialog(
                    this,
                    "New Unit:",
                    tableModel.getValueAt(row,2));

            if(unitText == null)
                return;

            try{

                int unit = Integer.parseInt(unitText);

                manager.editCourse(code,title,unit);

                FileManager.saveCourses(manager.getCourses());

                refreshTable();

                JOptionPane.showMessageDialog(
                        this,
                        "Course Updated.");

            }catch(NumberFormatException ex){

                JOptionPane.showMessageDialog(
                        this,
                        "Invalid Unit.");

            }

        });

        deleteButton.addActionListener(e -> {

            int row = table.getSelectedRow();

            if(row==-1){

                JOptionPane.showMessageDialog(
                        this,
                        "Select a course.");

                return;

            }

            String code =
                    tableModel.getValueAt(row,0).toString();

            int option =
                    JOptionPane.showConfirmDialog(

                            this,

                            "Delete "+code+" ?",

                            "Confirm",

                            JOptionPane.YES_NO_OPTION

                    );

            if(option==JOptionPane.YES_OPTION){

                manager.deleteCourse(code);

                FileManager.saveCourses(manager.getCourses());

                refreshTable();

            }

        });

        searchButton.addActionListener(e -> {

            String keyword =
                    JOptionPane.showInputDialog(
                            this,
                            "Enter Title Keyword:");

            if(keyword==null)
                return;

            ArrayList<Course> result =
                    manager.searchByTitle(keyword);

            tableModel.setRowCount(0);

            for(Course c : result){

                tableModel.addRow(new Object[]{

                        c.getCourseCode(),

                        c.getCourseTitle(),

                        c.getCourseUnit()

                });

            }

            statusLabel.setText(result.size()+" course(s) found.");

        });

        sortButton.addActionListener(e -> {

            manager.sortCourses();

            FileManager.saveCourses(manager.getCourses());

            refreshTable();

            JOptionPane.showMessageDialog(
                    this,
                    "Courses Sorted.");

        });

        statisticsButton.addActionListener(e -> {

            JOptionPane.showMessageDialog(

                    this,

                    "Total Courses : "+manager.getCourseCount()

                    +"\nTotal Units : "+manager.getTotalUnits()

                    +"\nHighest Unit : "+manager.getHighestUnit()

                    +"\nLowest Unit : "+manager.getLowestUnit()

                    +"\nAverage Unit : "

                    +String.format("%.2f",

                    manager.getAverageUnit())

            );

        });

        exitButton.addActionListener(e -> {

            FileManager.saveCourses(manager.getCourses());

            System.exit(0);

        });

    }

    // =========================================
    // REFRESH TABLE
    // =========================================

    private void refreshTable(){

        tableModel.setRowCount(0);

        ArrayList<Course> courses =
                manager.getCourses();

        for(Course c : courses){

            tableModel.addRow(new Object[]{

                    c.getCourseCode(),

                    c.getCourseTitle(),

                    c.getCourseUnit()

            });

        }

        statusLabel.setText(
                courses.size()+" course(s) loaded.");

    }

}