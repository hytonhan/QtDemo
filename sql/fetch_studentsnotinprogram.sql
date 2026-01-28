SELECT firstName, lastName, address, phoneNumber, id
FROM student
WHERE NOT EXISTS (
    SELECT 1
    FROM program_student
    WHERE program_student.student_id = student.id
    AND program_student.program_id = :program_id
);
