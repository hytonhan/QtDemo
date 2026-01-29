SELECT firstName, lastName, address, phoneNumber, id
FROM student
INNER JOIN program_student ON student.id = program_student.student_id
WHERE program_student.program_id = :program_id
