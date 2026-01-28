SELECT firstName, lastName, address, phoneNumber, id, salary, field
FROM teacher
INNER JOIN program_teacher ON teacher.id = program_teacher.teacher_id
WHERE program_teacher.program_id = :program_id
