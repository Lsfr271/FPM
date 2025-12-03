#include <iostream>
#include <string>
#include <vector>

#include "FPM.hpp"
#include "FPM_operators.hpp"

int main() {
    // Initialize users
    userLevel["James"] = USER;
    userLevel["Nalice"] = ADMIN;
    userLevel["Scot"] = ADMIN;
    userLevel["Marn"] = OWNER;

    // Create files
    FPM file1(PL_NONE);
    FPM file2(PL_MED);
    FPM file3(PL_READONLY);
    FPM file4(PL_HIDDEN);

    std::vector<FPM> files = {file1, file2, file3, file4};
    std::vector<std::string> filenames = {"file1", "file2", "file3",
    "file4"};

    FPM file(PL_NONE);

    // log actions
    file.logAction(OWNER, "unlocked file");
    file.logAction(USER, "Attempted to delete file");

    for (const auto& entry : file.getHistory())
    {
        std::cout << entry << "\n";
    }

    std::string currentUser;

    std::cout << "Enter your username: " << "\n";
    std::cin >> currentUser;

    if (userLevel.find(currentUser) == userLevel.end()){
        std::cout << "User not found." << "\n";

        return 0;
    }

    USERS level = userLevel[currentUser];

    std::cout << "Welcome " << currentUser << "! Your level is: "
    << FPM().getPermissionLevel_user(level) << "\n";

    while (true){
        std::cout << "Files available: \n";

        for (size_t i = 0; i < files.size(); i++){
            if (files[i].canSeeFile(level)){
                std::cout << i << ": " << filenames[i] << "\n";
            }
        }

        int choice;

        std::cout << "Select a file index (-1 to quit): " << "\n";
        std::cin >> choice;

        if (choice == -1){
            break;
        }

        if (choice < 0 || choice >= files.size()){
            std::cout << "Invalid file index." << "\n";

            continue;
        }

        std::cout << "Actions: \n";
        std::cout << "1: View Access Report \n";
        std::cout << "2: Try Modify \n";
        std::cout << "3: Try Rename \n";
        std::cout << "4: Try Delete \n";

        if (level == ADMIN || level == OWNER){
            std::cout << "5: Promote user to Admin \n";
        }

        if (level == OWNER){
            std::cout << "6: Promote Admin to Owner \n";
        }

        int action;

        std::cout << "Choose action: \n";
        std::cin >> action;

        switch (action){
            case 1:
                std::cout << files[choice].AccessReport(level) << "\n";

                break;

            case 2:
                std::cout << "Modify " << (
                    files[choice].canModifyFile(level) ? "succeeded!\n"
                    : "failed!\n"
                );

                break;

            case 3:
                std::cout << "Rename " << (
                    files[choice].canRenameFile(level) ? "suceeded!\n"
                    : "failed!\n"
                );

                break;

            case 4:
                std::cout << "Delete " << (
                    files[choice].canDeleteFile(level) ? "suceeded!\n"
                    : "failed!\n"
                );

                break;

            case 5:
                if (level == ADMIN || level == OWNER){
                    std::string uname;

                    std::cout << "Enter username to promote: \n";
                    std::cin >> uname;

                    files[0].promoteToAdmin(uname);

                    std::cout << uname << "promoted.\n";
                }

                break;

            case 6:
                 if (level == OWNER){
                    std::string uname;

                    std::cout << "Enter admin username to promote to Owner: ";
                    std::cin >> uname;

                    files[0].promoteToOwner(uname);

                    std::cout << uname << " promoted to Owner!\n";
                }

                break;

            default:
                std::cout << "Invalid action.\n";
        }
    }
}
