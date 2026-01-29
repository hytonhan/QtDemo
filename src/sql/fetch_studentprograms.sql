SELECT p.id, p.name
FROM program AS p
INNER JOIN program_student ON p.id = program_student.program_id
WHERE program_student.student_id = :student_id
