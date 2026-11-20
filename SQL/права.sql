-- Создание ролей базы данных
CREATE ROLE SchoolAdminRole; -- Роль директора/администратора (полные права)
CREATE ROLE InstructorRole;  -- Роль инструктора (только просмотр и выставление оценок)
GO

-- Назначение прав для Администратора (Все операции CRUD)
GRANT SELECT, INSERT, UPDATE, DELETE ON Groups TO SchoolAdminRole;
GRANT SELECT, INSERT, UPDATE, DELETE ON Students TO SchoolAdminRole;
GRANT SELECT, INSERT, UPDATE, DELETE ON Instructors TO SchoolAdminRole;
GRANT SELECT, INSERT, UPDATE, DELETE ON Lessons TO SchoolAdminRole;
GRANT SELECT, INSERT, UPDATE, DELETE ON Exams TO SchoolAdminRole;

-- Назначение прав для Инструктора (Ограниченный доступ)
GRANT SELECT ON Groups TO InstructorRole;
GRANT SELECT ON Students TO InstructorRole;
GRANT SELECT, INSERT, UPDATE ON Lessons TO InstructorRole; -- Инструктор может вести расписание
GRANT SELECT, INSERT, UPDATE ON Exams TO InstructorRole;   -- Инструктор может ставить зачеты
DENY DELETE ON Exams TO InstructorRole;                   -- Инструктор НЕ может удалять результаты
GO
