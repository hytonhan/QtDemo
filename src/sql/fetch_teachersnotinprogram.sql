SELECT firstName, lastName, address, phoneNumber, id, salary, field
FROM teacher
WHERE NOT EXISTS (
    SELECT 1
    FROM program_teacher
    WHERE program_teacher.teacher_id = teacher.id
    AND program_teacher.program_id = :program_id
);
