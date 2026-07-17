package ui;

import model.Course;
import service.CourseManager;
import service.FileManager;

import javax.swing.*;
import java.awt.*;

public class AddCourseDialog extends JDialog {

    private JTextField codeField;
    private JTextField titleField;
    private JTextField unitField;

    public AddCourseDialog(JFrame parent, CourseManager manager, Runnable refreshCallback) {

        super(parent, "Add New Course", true);

        setSize(400,250);
        setLocationRelativeTo(parent);
        setLayout(new BorderLayout(10,10));

        JPanel formPanel = new JPanel(new GridLayout(3,2,10,10));

        formPanel.add(new JLabel("Course Code:"));
        codeField = new JTextField();
        formPanel.add(codeField);

        formPanel.add(new JLabel("Course Title:"));
        titleField = new JTextField();
        formPanel.add(titleField);

        formPanel.add(new JLabel("Course Unit:"));
        unitField = new JTextField();
        formPanel.add(unitField);

        add(formPanel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel();

        JButton saveButton = new JButton("Save");
        JButton cancelButton = new JButton("Cancel");

        buttonPanel.add(saveButton);
        buttonPanel.add(cancelButton);

        add(buttonPanel, BorderLayout.SOUTH);

        saveButton.addActionListener(e -> {

            try {

                String code = codeField.getText().trim();
                String title = titleField.getText().trim();
                int unit = Integer.parseInt(unitField.getText().trim());

                Course course = new Course(code, title, unit);

                if(manager.addCourse(course)){

                    FileManager.saveCourses(manager.getCourses());

                    refreshCallback.run();

                    JOptionPane.showMessageDialog(this,
                            "Course Added Successfully.");

                    dispose();

                }else{

                    JOptionPane.showMessageDialog(this,
                            "Course Code Already Exists.");

                }

            }catch(Exception ex){

                JOptionPane.showMessageDialog(this,
                        "Invalid Input.");

            }

        });

        cancelButton.addActionListener(e -> dispose());

    }

}
