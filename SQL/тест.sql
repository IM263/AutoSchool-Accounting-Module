USE AutoSchoolDB;
GO

-- Проверяем, как связались курсанты и их оценки
SELECT s.LastName + ' ' + s.FirstName AS [Курсант], g.GroupName AS [Группа], e.ExamType AS [Экзамен], e.Score AS [Ошибки], e.IsPassed AS [Статус]
FROM Students s
JOIN Groups g ON s.GroupID = g.GroupID
JOIN Exams e ON s.StudentID = e.StudentID;
