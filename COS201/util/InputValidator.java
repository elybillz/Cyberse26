package util;

public class InputValidator {

    // Validate course code (e.g., COS201, GST111)
    public static boolean isValidCourseCode(String code) {

        if (code == null || code.trim().isEmpty()) {
            return false;
        }

        code = code.trim().toUpperCase();

        // Must start with letters followed by numbers
        return code.matches("[A-Z]{2,10}[0-9]{3}");
    }

    // Validate course title
    public static boolean isValidCourseTitle(String title) {

        if (title == null) {
            return false;
        }

        title = title.trim();

        return !title.isEmpty();
    }

    // Validate course unit
    public static boolean isValidUnit(int unit) {

        return unit >= 1 && unit <= 6;

    }

}