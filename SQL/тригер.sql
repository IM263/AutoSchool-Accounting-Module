-- Таблица для логирования аудита
CREATE TABLE AuditLog (
    LogID INT IDENTITY(1,1) PRIMARY KEY,
    ExamID INT,
    OldIsPassed BIT,
    NewIsPassed BIT,
    ChangedBy NVARCHAR(100) DEFAULT USER_NAME(),
    ChangedAt DATETIME DEFAULT GETDATE()
);
GO

-- Триггер, который сработает автоматически при изменении результатов экзамена
CREATE TRIGGER trg_AuditExamChanges
ON Exams
AFTER UPDATE
AS
BEGIN
    INSERT INTO AuditLog (ExamID, OldIsPassed, NewIsPassed)
    SELECT d.ExamID, d.IsPassed, i.IsPassed
    FROM deleted d
    JOIN inserted i ON d.ExamID = i.ExamID
    WHERE d.IsPassed <> i.IsPassed;
END;
GO
