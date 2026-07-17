package model;

import java.io.Serializable;

public class Course implements Serializable {

    private static final long serialVersionUID = 1L;

    private String courseCode;
    private String courseTitle;
    private int courseUnit;

    public Course(String courseCode, String courseTitle, int courseUnit) {
        this.courseCode = courseCode.trim().toUpperCase();
        this.courseTitle = courseTitle.trim();
        this.courseUnit = courseUnit;
    }

    public String getCourseCode() {
        return courseCode;
    }

    public String getCourseTitle() {
        return courseTitle;
    }

    public int getCourseUnit() {
        return courseUnit;
    }

    public void setCourseCode(String courseCode) {
        this.courseCode = courseCode.trim().toUpperCase();
    }

    public void setCourseTitle(String courseTitle) {
        this.courseTitle = courseTitle.trim();
    }

    public void setCourseUnit(int courseUnit) {
        this.courseUnit = courseUnit;
    }

    @Override
    public String toString() {
        return String.format("%-10s %-35s %2d Unit(s)",
                courseCode,
                courseTitle,
                courseUnit);
    }
}