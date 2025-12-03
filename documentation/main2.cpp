#include "FPM.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Setup users
    userLevel["Alice"] = USER;
    userLevel["Bob"] = ADMIN;
    userLevel["Charlie"] = OWNER;

    FPM file(PL_NONE);

    std::string currentUser;
    std::cout << "Enter your username (Alice, Bob, Charlie): ";
    std::cin >> currentUser;

    USERS user = userLevel[currentUser];

    bool running = true;
    while (running) {
        std::cout << "\n--- File Management Game ---\n";
        std::cout << "File status: " << file.getPermissionLevel_file() << "\n";
        std::cout << "1. See file\n";
        std::cout << "2. Modify file\n";
        std::cout << "3. Delete file\n";
        std::cout << "4. Rename file\n";
        std::cout << "5. Lock file\n";
        std::cout << "6. Unlock file\n";
        std::cout << "7. Promote user to Admin\n";
        std::cout << "8. Promote user to Owner\n";
        std::cout << "9. Demote user to User\n";
        std::cout << "10. View access report\n";
        std::cout << "11. View file history\n";
        std::cout << "12. Exit\n";
        std::cout << "Choose an action: ";

        int choice;
        std::cin >> choice;

        try {
            switch(choice) {
                case 1:
                    if(file.canSeeFile(user)) {
                        std::cout << "You can see the file.\n";
                        file.logAction(user, "Viewed the file");
                    } else {
                        std::cout << "You cannot see the file.\n";
                        file.logAction(user, "Tried to view the file but failed");
                    }
                    break;

                case 2:
                    if(file.canModifyFile(user)) {
                        std::cout << "File modified successfully!\n";
                        file.logAction(user, "Modified the file");
                    } else {
                        std::cout << "Modification denied.\n";
                        file.logAction(user, "Attempted to modify the file but failed");
                    }
                    break;

                case 3:
                    if(file.canDeleteFile(user)) {
                        std::cout << "File deleted!\n";
                        file.logAction(user, "Deleted the file");
                    } else {
                        std::cout << "Delete denied.\n";
                        file.logAction(user, "Attempted to delete the file but failed");
                    }
                    break;

                case 4:
                    if(file.canRenameFile(user)) {
                        std::cout << "File renamed successfully!\n";
                        file.logAction(user, "Renamed the file");
                    } else {
                        std::cout << "Rename denied.\n";
                        file.logAction(user, "Attempted to rename the file but failed");
                    }
                    break;

                case 5:
                    file.lockFile(user);
                    std::cout << "File locked (read-only).\n";
                    file.logAction(user, "Locked the file");
                    break;

                case 6:
                    file.unlockFile(user);
                    std::cout << "File unlocked.\n";
                    file.logAction(user, "Unlocked the file");
                    break;

                case 7: {
                    std::string target;
                    std::cout << "Enter username to promote to Admin: ";
                    std::cin >> target;
                    file.promoteToAdmin(target);
                    std::cout << target << " promoted to Admin.\n";
                    file.logAction(user, "Promoted " + target + " to Admin");
                    break;
                }

                case 8: {
                    std::string target;
                    std::cout << "Enter username to promote to Owner: ";
                    std::cin >> target;
                    file.promoteToOwner(target);
                    std::cout << target << " promoted to Owner.\n";
                    file.logAction(user, "Promoted " + target + " to Owner");
                    break;
                }

                case 9: {
                    std::string target;
                    std::cout << "Enter username to demote to User: ";
                    std::cin >> target;
                    file.demoteToUser(target);
                    std::cout << target << " demoted to User.\n";
                    file.logAction(user, "Demoted " + target + " to User");
                    break;
                }

                case 10:
                    std::cout << file.AccessReport(user) << "\n";
                    file.logAction(user, "Viewed access report");
                    break;

                case 11: {
                    std::cout << "--- File History ---\n";
                    for(const auto& entry : file.getHistory()) {
                        std::cout << entry << "\n";
                    }
                    break;
                }

                case 12:
                    running = false;
                    break;

                default:
                    std::cout << "Invalid choice.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            file.logAction(user, std::string("Exception: ") + e.what());
        }
    }

    std::cout << "Exiting game...\n";
    return 0;
}
