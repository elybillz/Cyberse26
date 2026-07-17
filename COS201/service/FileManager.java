package service;

import model.Course;

import java.io.*;
import java.util.ArrayList;

public class FileManager {

    private static final String FILE_NAME = "courses.dat";

    // Save courses to file
    public static void saveCourses(ArrayList<Course> courses) {

        try (ObjectOutputStream out =
                     new ObjectOutputStream(
                             new FileOutputStream(FILE_NAME))) {

            out.writeObject(courses);

            System.out.println("\nCourses saved successfully.");

        } catch (IOException e) {

            System.out.println("\nError saving courses.");
            System.out.println(e.getMessage());

        }

    }

    // Load courses from file
    @SuppressWarnings("unchecked")
    public static ArrayList<Course> loadCourses() {

        try (ObjectInputStream in =
                     new ObjectInputStream(
                             new FileInputStream(FILE_NAME))) {

            return (ArrayList<Course>) in.readObject();

        } catch (FileNotFoundException e) {

            System.out.println("\nNo saved courses found.");
            return new ArrayList<>();

        } catch (IOException | ClassNotFoundException e) {

            System.out.println("\nError loading courses.");
            return new ArrayList<>();

        }

    }

}