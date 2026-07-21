#include <stdio.h>
#include <stdlib.h>
#include "course.h"
#include "courseResult.h"
#include "gpa.h"

void addCourse(Course courses[], int *n_courses)
{
    char code[16], name[100];
    double credit;
    int semester;

    printf("Enter Course Code: ");
    scanf("%s", code);
    printf("Enter Course Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Credit: ");
    scanf("%lf", &credit);
    printf("Enter Semester: ");
    scanf("%d", &semester);

    courses[*n_courses] = createCourse(code, name, credit, semester);
    (*n_courses)++;
    courses[*n_courses] = createCourse("NULL", "NULL", 0.0, 0);
}

void addCourseResult(Course courses[], int n_courses, CourseResult results[], int *n_results)
{
    int course_no;
    printf("Select a Course:\n");
    for (int i = 0; i < n_courses; i++)
    {
        printf("%d. %s\n", i + 1, courses[i].name);
    }
    printf("Enter Choice: ");
    scanf("%d", &course_no);

    if (course_no < 1 || course_no > n_courses) return;

    int choice;
    printf("Completed?\n1. YES\n2. NO\nEnter Choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        double marks;
        printf("Enter Marks: ");
        scanf("%lf", &marks);
        // Utilisation de la fonction unique de la Feature 006
        results[*n_results] = createCourseResult(&courses[course_no - 1], marks);
    }
    else
    {
        // Pour un cours incomplet, la note est mise à 0.0 par défaut
        results[*n_results] = createCourseResult(&courses[course_no - 1], 0.0);
    }
    (*n_results)++;
}

int main()
{
    Course courses[1000];
    CourseResult results[1000];
    CourseResult filtered[1000];
    int n_courses = 0;
    int n_results = 0;

    courses[n_courses] = createCourse("NULL", "NULL", 0.0, 0);

    int choice;
    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Add Course\n");
        printf("2. Add Course Result\n");
        printf("3. View GPA Report\n");
        printf("4. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            addCourse(courses, &n_courses);
        }
        else if (choice == 2)
        {
            int actual_courses = countCoursesBeforeNull(courses, n_courses);
            addCourseResult(courses, actual_courses, results, &n_results);
        }
        else if (choice == 3)
        {
            sortCourseResultsBySemester(results, n_results);
            printf("\nResults\n");
            for (int sem = 1; sem <= 2; sem++)
            {
                filterCourseResultsBySemester(results, n_results, sem, filtered);
                int n_filtered = countCourseResultsBeforeNull(filtered, 1000);
                
                if (n_filtered > 0)
                {
                    for (int i = 0; i < n_filtered; i++)
                    {
                        viewCourseResult(filtered[i]);
                        printf("Grade: %s\n", getLetterGrade(filtered[i]));
                    }
                    printf("Semester %d GPA: %.2f\n", sem, calculateGPA(filtered, n_filtered));
                }
            }
            printf("CGPA: %.2f\n", calculateGPA(results, n_results));
        }
        else if (choice == 4)
        {
            break;
        }
    }

    return 0;
}
