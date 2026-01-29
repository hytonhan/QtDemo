SELECT p.id, p.name
FROM program AS p
INNER JOIN program_teacher ON p.id = program_teacher.program_id
WHERE program_teacher.teacher_id = :teacher_id
