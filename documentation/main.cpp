#include "PFM.hpp"
#include "pfm_operators.hpp"

int main() {
    // Initialize users and assign their levels
    userLevel["Alice"] = USER;
    userLevel["Bob"] = ADMIN;
    userLevel["Charlie"] = OWNER;

    // Create PFM objects for files with different protection levels
    PFM file1(PL_NONE);
    PFM file2(PL_MED);
    PFM file3(PL_READONLY);
    PFM file4(PL_HIDDEN);

    // Print access reports for each user before promotions
    for (auto& [name, level] : userLevel) {
        std::cout << name << ":\n" << file2.AccessReport(level) << "\n";
    }

    // Create a dummy PFM object to use promotion functions
    PFM fileDummy;

    // Promote Alice from USER to ADMIN
    fileDummy.promoteToAdmin("Alice");

    // Promote Bob from ADMIN to OWNER (only if no other OWNER exists)
    fileDummy.promoteToOwner("Bob");

    // Print access reports for each user after promotions
    for (auto& [name, level] : userLevel) {
        std::cout << name << ":\n" << file2.AccessReport(level) << "\n";
    }

    // Attempt to change file1 permissions to FULL using OWNER
    try {
        file1.setPermissions(PL_FULL, OWNER);
        std::cout << "New file1 level: " << file1.getPermissionLevel_file() << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << "\n";
    }

    // Attempt to change file2 permissions using USER (should fail)
    try {
        file2.setPermissions(PL_READONLY, USER);
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << "\n";
    }

    // Check individual file permissions for specific users
    std::cout << "Can USER delete file2?: " << (file2.canDeleteFile(USER) ? "Yes" : "No") << "\n";
    std::cout << "Can ADMIN see file3?: " << (file3.canSeeFile(ADMIN) ? "Yes" : "No") << "\n";
    std::cout << "Can OWNER modify file3?: " << (file3.canModifyFile(OWNER) ? "Yes" : "No") << "\n";
    std::cout << "Is file4 hidden from USER?: " << (file4.isHidden(USER) ? "Yes" : "No") << "\n";

    // Create another file to demonstrate file comparison
    PFM anotherFile(PL_MED);

    // Compare files
    std::cout << "file2 == anotherFile? " << (file2 == anotherFile ? "Yes" : "No") << "\n";
    std::cout << "file1 != file3? " << (file1 != file3 ? "Yes" : "No") << "\n";

    return 0;
}
