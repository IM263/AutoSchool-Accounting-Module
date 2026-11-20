#pragma once
#using <System.dll>
#using <System.Data.dll>

using namespace System;
using namespace System::Data::SqlClient;

public ref class AutoSchoolService {
private:
    SqlConnection^ sqlConnection;

public:
    AutoSchoolService(SqlConnection^ conn);

    // CRUD для учебных групп
    bool CreateGroup(String^ groupName, String^ courseType, String^ startDate, String^ endDate);
    void ShowAllGroups();
    bool UpdateGroupEndDate(int groupId, String^ newEndDate);
    bool DeleteGroup(int groupId);

    // CRUD для экзаменов
    bool RecordExamResult(int studentId, String^ examType, String^ examDate, int score, bool isPassed);
    void ShowStudentExams(int studentId);
    bool UpdateExamStatus(int examId, int newScore, bool isPassed);
};
