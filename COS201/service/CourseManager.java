package service;

import model.Course;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class CourseManager {

    private ArrayList<Course> courses;

    public CourseManager() {
        courses = new ArrayList<>();
    }

    // ===========================
    // ADD COURSE
    // ===========================

    public boolean addCourse(Course course) {

        for (Course c : courses) {

            if (c.getCourseCode().equalsIgnoreCase(course.getCourseCode())) {

                return false;

            }

        }

        courses.add(course);

        return true;

    }

    // ===========================
    // DISPLAY COURSES
    // ===========================

    public void displayCourses() {

        if (courses.isEmpty()) {

            System.out.println("\nNo courses available.");

            return;

        }

        System.out.println("\n==============================================================");
        System.out.printf("%-12s %-35s %-5s%n",
                "CODE",
                "TITLE",
                "UNIT");
        System.out.println("==============================================================");

        for (Course c : courses) {

            System.out.printf("%-12s %-35s %-5d%n",
                    c.getCourseCode(),
                    c.getCourseTitle(),
                    c.getCourseUnit());

        }

        System.out.println("==============================================================");

    }

    // ===========================
    // SEARCH BY COURSE CODE
    // ===========================

    public Course searchCourse(String code) {

        for (Course c : courses) {

            if (c.getCourseCode().equalsIgnoreCase(code)) {

                return c;

            }

        }

        return null;

    }

    // ===========================
    // SEARCH BY TITLE
    // ===========================

    public ArrayList<Course> searchByTitle(String keyword) {

        ArrayList<Course> result = new ArrayList<>();

        keyword = keyword.toLowerCase();

        for (Course c : courses) {

            if (c.getCourseTitle().toLowerCase().contains(keyword)) {

                result.add(c);

            }

        }

        return result;

    }

    // ===========================
    // DELETE COURSE
    // ===========================

    public boolean deleteCourse(String code) {

        for (int i = 0; i < courses.size(); i++) {

            if (courses.get(i).getCourseCode().equalsIgnoreCase(code)) {

                courses.remove(i);

                return true;

            }

        }

        return false;

    }

    // ===========================
    // EDIT COURSE
    // ===========================

    public boolean editCourse(String code,
                              String newTitle,
                              int newUnit) {

        Course c = searchCourse(code);

        if (c == null) {

            return false;

        }

        c.setCourseTitle(newTitle);

        c.setCourseUnit(newUnit);

        return true;

    }

    // ===========================
    // SORT BY COURSE CODE
    // ===========================

    public void sortCourses() {

        Collections.sort(courses, Comparator.comparing(Course::getCourseCode));

    }

    // ===========================
    // TOTAL UNITS
    // ===========================

    public int getTotalUnits() {

        int total = 0;

        for (Course c : courses) {

            total += c.getCourseUnit();

        }

        return total;

    }

    // ===========================
    // TOTAL COURSES
    // ===========================

    public int getCourseCount() {

        return courses.size();

    }

    // ===========================
    // HIGHEST UNIT
    // ===========================

    public int getHighestUnit() {

        if (courses.isEmpty()) {

            return 0;

        }

        int highest = courses.get(0).getCourseUnit();

        for (Course c : courses) {

            if (c.getCourseUnit() > highest) {

                highest = c.getCourseUnit();

            }

        }

        return highest;

    }

    // ===========================
    // LOWEST UNIT
    // ===========================

    public int getLowestUnit() {

        if (courses.isEmpty()) {

            return 0;

        }

        int lowest = courses.get(0).getCourseUnit();

        for (Course c : courses) {

            if (c.getCourseUnit() < lowest) {

                lowest = c.getCourseUnit();

            }

        }

        return lowest;

    }

    // ===========================
    // AVERAGE UNIT
    // ===========================

    public double getAverageUnit() {

        if (courses.isEmpty()) {

            return 0;

        }

        return (double) getTotalUnits() / courses.size();

    }

    // ===========================
    // GETTERS / SETTERS
    // ===========================

    public ArrayList<Course> getCourses() {

        return courses;

    }

    public void setCourses(ArrayList<Course> courses) {

        this.courses = courses;

    }

}