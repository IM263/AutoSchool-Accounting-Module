-- 1. СОЗДАНИЕ САМОЙ БАЗЫ ДАННЫХ
CREATE DATABASE AutoSchoolDB;
GO

-- Переключаем контекст выполнения на созданную БД
USE AutoSchoolDB;
GO

-- 2. СОЗДАНИЕ ТАБЛИЦЫ УЧЕБНЫХ ГРУПП (Главная для студентов и занятий)
CREATE TABLE Groups (
    GroupID INT IDENTITY(1,1) PRIMARY KEY,
    GroupName NVARCHAR(50) NOT NULL UNIQUE,
    CourseType NVARCHAR(20) NOT NULL, -- Категории: 'A', 'B', 'C'
    StartDate DATE NOT NULL,
    EndDate DATE NOT NULL
);

-- 3. СОЗДАНИЕ ТАБЛИЦЫ ИНСТРУКТОРОВ (Главная для занятий)
CREATE TABLE Instructors (
    InstructorID INT IDENTITY(1,1) PRIMARY KEY,
    LastName NVARCHAR(50) NOT NULL,
    FirstName NVARCHAR(50) NOT NULL,
    MiddleName NVARCHAR(50),
    LicenseNumber NVARCHAR(20) NOT NULL UNIQUE,
    Phone NVARCHAR(20)
);

-- 4. СОЗДАНИЕ ТАБЛИЦЫ КУРСАНТОВ (Связана с Groups по GroupID)
CREATE TABLE Students (
    StudentID INT IDENTITY(1,1) PRIMARY KEY,
    GroupID INT,
    LastName NVARCHAR(50) NOT NULL,
    FirstName NVARCHAR(50) NOT NULL,
    MiddleName NVARCHAR(50),
    BirthDate DATE NOT NULL,
    Phone NVARCHAR(20),
    MedicalCertificate NVARCHAR(20),
    -- Настройка внешнего ключа к таблице групп (1:М)
    CONSTRAINT FK_Students_Groups FOREIGN KEY (GroupID) 
        REFERENCES Groups(GroupID) ON DELETE SET NULL
);

-- 5. СОЗДАНИЕ ТАБЛИЦЫ ЗАНЯТИЙ (Связана с Groups и Instructors)
CREATE TABLE Lessons (
    LessonID INT IDENTITY(1,1) PRIMARY KEY,
    GroupID INT,
    InstructorID INT,
    LessonDate DATETIME NOT NULL,
    LessonType NVARCHAR(30) NOT NULL, -- 'Теория ПДД', 'Вождение (Автодром)' и т.д.
    Topic NVARCHAR(150),
    -- Настройка внешних ключей
    CONSTRAINT FK_Lessons_Groups FOREIGN KEY (GroupID) 
        REFERENCES Groups(GroupID) ON DELETE CASCADE,
    CONSTRAINT FK_Lessons_Instructors FOREIGN KEY (InstructorID) 
        REFERENCES Instructors(InstructorID) ON DELETE NO ACTION
);

-- 6. СОЗДАНИЕ ТАБЛИЦЫ ЭКЗАМЕНОВ (Связана со Students по StudentID)
CREATE TABLE Exams (
    ExamID INT IDENTITY(1,1) PRIMARY KEY,
    StudentID INT,
    ExamType NVARCHAR(30) NOT NULL, -- 'Внутренний (Теория)', 'Внутренний (Город)', 'ГИБДД'
    ExamDate DATE NOT NULL,
    Score INT NOT NULL, -- Количество ошибок / баллов
    IsPassed BIT NOT NULL DEFAULT 0, -- 1 - Сдано, 0 - Не сдано
    -- Настройка внешнего ключа к таблице студентов (1:М)
    CONSTRAINT FK_Exams_Students FOREIGN KEY (StudentID) 
        REFERENCES Students(StudentID) ON DELETE CASCADE
);
GO
