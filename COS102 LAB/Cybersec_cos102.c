#include <stdio.h>

int main() {
    int choice;

    // Outer loop to keep the program running until the user chooses to exit
    do {
        printf("\n===== MENU_COS102_LAB =====\n");
        printf("===== CYBERSEC_COS102 =====\n");
        printf("1. Check Right-Angled Triangle\n");
        printf("2. Check Palindrome Number\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Option 1: Triangle Logic
        if (choice == 1) {
            int angle1, angle2, angle3;

            printf("Enter first angle: ");
            scanf("%d", &angle1);

            printf("Enter second angle: ");
            scanf("%d", &angle2);

            // Calculate the missing angle based on the sum of a triangle (180 degrees)
            angle3 = 180 - (angle1 + angle2);

            // Validation: Ensure angles are positive and the sum of two doesn't exceed 180
            if (angle1 + angle2 < 180 && angle1 > 0 && angle2 > 0 && angle3 > 0) {
                printf("Third angle is: %d\n", angle3);

                // A triangle is right-angled if any one of its angles is exactly 90 degrees
                if (angle1 == 90 || angle2 == 90 || angle3 == 90) {
                    printf("The triangle is a Right-Angled Triangle.\n");
                } else {
                    printf("The triangle is NOT a Right-Angled Triangle.\n");
                }
            } else {
                printf("Invalid triangle input.\n");
            }

        // Option 2: Palindrome Logic
        } else if (choice == 2) {
            int number, original, remainder, reverse = 0;

            printf("Enter a number: ");
            scanf("%d", &number);

            original = number; // Store the original value to compare later

            // Reverse the number mathematically
            while (number != 0) {
                remainder = number % 10;            // Get the last digit
                reverse = reverse * 10 + remainder; // Append digit to the reversed variable
                number = number / 10;               // Remove the last digit from the number
            }

            // If the reversed version matches the original, it's a palindrome
            if (original == reverse) {
                printf("The number is a Palindrome.\n");
            } else {
                printf("The number is NOT a Palindrome.\n");
            }

        // Option 3: Exit
        } else if (choice == 3) {
            printf("Exiting program...\n");
        } else {
            // Error handling for numbers outside 1-3
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 3); // Condition to repeat the menu

    return 0;
}