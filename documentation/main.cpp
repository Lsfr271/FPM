// include both headers. (for Using the PFM API/LIBRARY and the operator overloads)
#include "../PFM/PFM.hpp"
#include "../PFM/pfm_operators.hpp"

int main() {
    // Create PFM Objects with different file protection levels.
    // you can do PFM file1; then set the protection level later.
    PFM file1(PL_NONE);
    PFM file2(PL_MED);
    PFM file3(PL_READONLY);
    PFM file4(PL_HIDDEN);

    // check access report
    std::cout << "file1 AccessReport" << "\n";
    std::cout << file1.AccessReport(USER) << "\n";

    // check permission individually
    std::cout << "Can USER delete file2?: " << (file2.canDeleteFile(USER) ? "Yes" : "No") << "\n";
    std::cout << "Can ADMIN see file3?: " << (file3.canSeeFile(ADMIN) ? "Yes" : "No") << "\n";
    std::cout << "Can OWNER modify file3?: " << (file3.canModifyFile(OWNER) ? "Yes" : "No") << "\n";
    std::cout << "Is file4 hidden from USER?: " << (file4.isHidden(USER) ? "Yes" : "No") << "\n";
    std::cout << "Is file2 protected?: " << (file2.isProtected() ? "Yes" : "No") << "\n";
    std::cout << "Does OWNER have full control over file2?: " << (file2.hasFullControl(OWNER) ? "Yes" : "No") << "\n";
    std::cout << "Is file3 accessible to ADMIN?: " << (file3.isAccessible(ADMIN) ? "Yes" : "No") << "\n";

    // modify permissions, only OWNER can do this
    try {
        std::cout << "Changing file1 permissions to FULL by OWNER" << "\n";

        file1.setPermissions(PL_FULL, OWNER);

        std::cout << "New file1 level: " << file1.getPermissionLevel_file() << "\n";
    } catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << "\n";
    }

    // attempt invalid permission change
    try {
        std::cout << "Trying to change file2 permission by USER\n";

        file2.setPermissions(PL_READONLY, USER);
    } catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << "\n";
    }

    // Get user and file permission levels
    std::cout << "User level descriptions\n: ";
    std::cout << "USER: " << file2.getPermissionLevel_user(USER) << "\n";
    std::cout << "ADMIN: " << file2.getPermissionLevel_user(ADMIN) << "\n";
    std::cout << "OWNER: " << file2.getPermissionLevel_user(OWNER) << "\n";

    std::cout << "\nFile level descriptions: \n";
    std::cout << "file1: " << file1.getPermissionLevel_file() << "\n";
    std::cout << "file2: " << file2.getPermissionLevel_file() << "\n";
    std::cout << "file3: " << file3.getPermissionLevel_file() << "\n";
    std::cout << "file4: " << file4.getPermissionLevel_file() << "\n";

    // Compare PFM objects
    PFM anotherFile(PL_MED);

    std::cout << "Comparing files: \n";
    std::cout << "file2 == anotherFile? " << (file2 == anotherFile ? "Yes" : "No") << "\n";
    std::cout << "file1 != file3? " << (file1 != file3 ? "Yes" : "No") << "\n";
}
