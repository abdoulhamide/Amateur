#include <stdio.h>
#include "course.h"
#include "courseResult.h"

int testResultCourse()
{
	Course course = createCourse("CSE 4202", "Structured Programming II Lab", 1.5);
	CourseResult result = createCourseResult(&course, 77);
	return result.course == &course;
}

int testResultMarks()
{
	Course course = createCourse("CSE 4202", "Structured Programming II Lab", 1.5);
	CourseResult result = createCourseResult(&course, 77);
	return result.marks == 77;
}
