#include "../include/AutoSchoolService.h"
#include "../include/Logger.h"

AutoSchoolService::AutoSchoolService(SqlConnection^ conn) : sqlConnection(conn) {}

bool AutoSchoolService::CreateGroup(String^ groupName, String^ courseType, String^ startDate, String^ endDate) {
    if (String::IsNullOrWhiteSpace(groupName) || String::IsNullOrWhiteSpace(courseType)) {
        Logger::Error("Validation error: group name and course category cannot be empty.");
        return false;
    }

    String^ query = "INSERT INTO Groups (GroupName, CourseType, StartDate, EndDate) VALUES (@name, @type, @start, @end);";
    SqlCommand^ cmd = gcnew SqlCommand(query, sqlConnection);

    // Built-in SQL injection protection using ADO.NET parameters
    cmd->Parameters->AddWithValue("@name", groupName);
    cmd->Parameters->AddWithValue("@type", courseType);
    cmd->Parameters->AddWithValue("@start", startDate);
    cmd->Parameters->AddWithValue("@end", endDate);

    try {
        cmd->ExecuteNonQuery();
        Logger::Info("New group added via SqlCommand.");
        return true;
    }
    catch (Exception^ ex) {
        Console::WriteLine("Database error: " + ex->Message);
        Logger::Error("Failed to create group in database.");
        return false;
    }
}

void AutoSchoolService::ShowAllGroups() {
    String^ query = "SELECT GroupID, GroupName, CourseType, CAST(StartDate AS VARCHAR), CAST(EndDate AS VARCHAR) FROM Groups;";
    SqlCommand^ cmd = gcnew SqlCommand(query, sqlConnection);
    SqlDataReader^ reader = nullptr;

    try {
        reader = cmd->ExecuteReader();
        Console::WriteLine("\nList of groups (ID | Name | Category | Start Date | End Date):");
        while (reader->Read()) {
            Console::WriteLine("{0} | {1} | {2} | {3} | {4}",
                reader->GetInt32(0),
                reader->GetString(1),
                reader->GetString(2),
                reader->GetString(3),
                reader->GetString(4));
        }
    }
    catch (Exception^ ex) {
        Console::WriteLine("Read error: " + ex->Message);
    }
    finally {
        if (reader != nullptr) reader->Close();
    }
}

bool AutoSchoolService::UpdateGroupEndDate(int groupId, String^ newEndDate) {
    String^ query = "UPDATE Groups SET EndDate = @end WHERE GroupID = @id;";
    SqlCommand^ cmd = gcnew SqlCommand(query, sqlConnection);
    cmd->Parameters->AddWithValue("@end", newEndDate);
    cmd->Parameters->AddWithValue("@id", groupId);

    try {
        return cmd->ExecuteNonQuery() > 0;
    }
    catch (Exception^) {
        return false;
    }
}

bool AutoSchoolService::DeleteGroup(int groupId) {
    String^ query = "DELETE FROM Groups WHERE GroupID = @id;";
    SqlCommand^ cmd = gcnew SqlCommand(query, sqlConnection);
    cmd->Parameters->AddWithValue("@id", groupId);

    try {
        return cmd->ExecuteNonQuery() > 0;
    }
    catch (Exception^) {
        return false;
    }
}

bool AutoSchoolService::RecordExamResult(int studentId, String^ examType, String^ examDate, int score, bool isPassed) {
    String^ query = "INSERT INTO Exams (StudentID, ExamType, ExamDate, Score, IsPassed) VALUES (@sid, @type, @date, @score, @passed);";
    SqlCommand^ cmd = gcnew SqlCommand(query, sqlConnection);
    cmd->Parameters->AddWithValue("@sid", studentId);
    cmd->Parameters->AddWithValue("@type", examType);
    cmd->Parameters->AddWithValue("@date", examDate);
    cmd->Parameters->AddWithValue("@score", score);
    cmd->Parameters->AddWithValue("@passed", isPassed);

    try {
        cmd->ExecuteNonQuery();
        Logger::Info("Exam result recorded.");
        return true;
    }
    catch (Exception^) {
        return false;
    }
}

void AutoSchoolService::ShowStudentExams(int studentId) {
    String^ query = "SELECT ExamID, ExamType, CAST(ExamDate AS VARCHAR), Score, IsPassed FROM Exams WHERE StudentID = @sid;";
    SqlCommand^ cmd = gcnew SqlCommand(query, sqlConnection);
    cmd->Parameters->AddWithValue("@sid", studentId);
    SqlDataReader^ reader = nullptr;

    try {
        reader = cmd->ExecuteReader();
        Console::WriteLine("\nStudent exams:");
        while (reader->Read()) {
            String^ status = reader->GetBoolean(4) ? "Passed" : "Failed";
            Console::WriteLine("ID: {0} | {1} | Date: {2} | Errors: {3} | {4}",
                reader->GetInt32(0), reader->GetString(1), reader->GetString(2), reader->GetInt32(3), status);
        }
    }
    finally {
        if (reader != nullptr) reader->Close();
    }
}

bool AutoSchoolService::UpdateExamStatus(int examId, int newScore, bool isPassed) {
    String^ query = "UPDATE Exams SET Score = @score, IsPassed = @passed WHERE ExamID = @id;";
    SqlCommand^ cmd = gcnew SqlCommand(query, sqlConnection);
    cmd->Parameters->AddWithValue("@score", newScore);
    cmd->Parameters->AddWithValue("@passed", isPassed);
    cmd->Parameters->AddWithValue("@id", examId);

    try {
        if (cmd->ExecuteNonQuery() > 0) {
            Logger::Info("Exam status updated.");
            return true;
        }
        return false;
    }
    catch (Exception^) {
        return false;
    }
}
