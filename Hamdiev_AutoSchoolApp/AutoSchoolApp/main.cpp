#using <System.dll>
#using <System.Data.dll>
#include "include/AutoSchoolService.h"

using namespace System;
using namespace System::Data::SqlClient;

int main() {
    // Connection string to your SQL Server (Windows Authentication)
    String^ connStr = "Data Source=DESKTOP-06H78GM;Initial Catalog=AutoSchoolDB;Integrated Security=True;TrustServerCertificate=True";
    SqlConnection^ connection = gcnew SqlConnection(connStr);

    Console::WriteLine("Connecting to server DESKTOP-06H78GM...");
    try {
        connection->Open();
        Console::WriteLine("Successfully connected to AutoSchoolDB database!");
    }
    catch (Exception^ ex) {
        Console::WriteLine("Connection error: " + ex->Message);
        Console::WriteLine("Press Enter to exit...");
        Console::ReadLine();
        return 1;
    }

    AutoSchoolService^ service = gcnew AutoSchoolService(connection);
    int choice = -1;

    while (choice != 0) {
        Console::WriteLine("\n--- DRIVING SCHOOL ACCOUNTING MODULE ---");
        Console::WriteLine("1. [READ]   Show all study groups");
        Console::WriteLine("2. [CREATE] Add a new study group");
        Console::WriteLine("3. [READ]   Show student exams (ID = 1)");
        Console::WriteLine("4. [UPDATE] Update exam status (test audit trigger)");
        Console::WriteLine("0. Exit");
        Console::Write("Select an action: ");

        String^ input = Console::ReadLine();
        if (!Int32::TryParse(input, choice)) {
            Console::WriteLine("Error: please enter a valid number.");
            choice = -1;
            continue;
        }

        if (choice == 1) {
            service->ShowAllGroups();
        }
        else if (choice == 2) {
            Console::Write("Enter group name (e.g., C-05): ");
            String^ name = Console::ReadLine();

            Console::Write("Enter category (A/B/C): ");
            String^ type = Console::ReadLine();

            if (service->CreateGroup(name, type, "2026-11-15", "2027-01-20")) {
                Console::WriteLine("Group successfully added to the database!");
            }
            else {
                Console::WriteLine("Error adding group (see app.log for details).");
            }
        }
        else if (choice == 3) {
            service->ShowStudentExams(1);
        }
        else if (choice == 4) {
            Console::Write("Enter Exam ID to update (e.g., 2): ");
            int examId = 0;
            Int32::TryParse(Console::ReadLine(), examId);

            Console::Write("New error count: ");
            int score = 0;
            Int32::TryParse(Console::ReadLine(), score);

            Console::Write("Passed? (1 - yes, 0 - no): ");
            int passed = 0;
            Int32::TryParse(Console::ReadLine(), passed);

            if (service->UpdateExamStatus(examId, score, passed == 1)) {
                Console::WriteLine("Status updated! Record added to AuditLog table.");
            }
            else {
                Console::WriteLine("Failed to update exam status (check ID).");
            }
        }
    }

    connection->Close();
    Console::WriteLine("Database connection closed.");
    return 0;
}
