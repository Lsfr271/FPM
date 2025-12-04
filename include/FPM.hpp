/* LSFR__ 26/11/2025 (November 26th, 2025)

    Questions you might ask:
        What is FPM? FPM is a File Permission Manager. (Originally called Permission File Manager (FPM))
        Can you use FPM? Yes, this is open source.
        Can you modify FPM's Source code? No, not for now.
        Can you join in as a contributor? No, not for now.
*/

#ifndef FPM_MANAGER_H
#define FPM_MANAGER_H

#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <chrono>
#include <ctime>


enum USERS {
    /* User permissions, which is 0 (basic permissions, can delete user-created
    files. but not system files) */
    USER = 0,

    /* Admin permissions, which is 1 (can change users to an admin but cannot delete
    system files)*/
    ADMIN = 1,

    /* Owner permissions, which is 2 (has full control & ability of admin) */
    OWNER = 2
};


enum FILES {
    /*
    Zero protection, meaning USER can modify, rename, and delete the file.
    This can also apply to ADMIN and OWNER.
    */
    PL_NONE = 0,

    /*
    Medium Protection, meaning USER can modify, rename, but CANNOT delete
    the file. This applies to ADMIN and OWNER but they can delete the file.
    */
    PL_MED = 1,

    /*
    Full Protection, USER cannot modify or rename or delete.
    ADMIN can modify, rename, but CANNOT delete. Owner can modify, rename,
    and delete.
    */
    PL_FULL = 2,

    /* Read only, means no one can modify the file. Not even OWNER, unless they
    reset the permission of the file. (owner can delete the file but admin cannot)*/
    PL_READONLY = 3,

    /* Hidden to USER, means USER cannot view the file unless promoted to ADMIN (admin & owner
    can edit, modify, rename, and delete the hidden file)*/
    PL_HIDDEN = 4,

    /* Hidden to both USER and ADMIN, means USER and ADMIN cannot see the file,
    only OWNER can. (owner can rename, edit, or delete the system file)*/
    PL_SYSTEM = 5,
};

extern std::map<std::string, USERS> userLevel;

struct FPM {
    private:
        std::vector<std::string> _history;
        FILES _fp;

    public:
        FPM() = default;
        FPM(FILES fp) : _fp(fp) {}

        FPM& operator=(const FPM& other);

        FILES getPermission() const; // gets the file permission level of _fp

        bool canDeleteFile(USERS user); // checks if user can delete file
        bool canSeeFile(USERS user); // checks if a user can see the file
        bool canModifyFile(USERS user); // checks if a user can modify the file
        bool canRenameFile(USERS user); // checks if a user can rename the file
        bool isHidden(USERS user); // returns true if the file is hidden from the user
        bool isProtected(); // returns true if the file has any protection
        bool hasFullControl(USERS user); // checks if the user has full control
        bool isAccessible(USERS user); // checks if the file is accessible (viewable, modifiable)
        bool isOwner(const std::string& name); // checks if a user is an OWNER

        void setPermissions(FILES newPerm, USERS user); // sets the file permissions, NOTE: OWNER can only do this
        void promoteToAdmin(const std::string& name); // promotes a USER to ADMIN
        void promoteToOwner(const std::string& name); // promotes an ADMIN to OWNER
        void lockFile(USERS user); // locks the file as PL_READONLY
        void unlockFile(USERS user); // unlocks the file as PL_NONE (no protection)
        void setOwner(const std::string& name); // sets the owner
        void demoteToUser(const std::string& name); // demotes an ADMIN to USER
        void logAction(USERS user, const std::string& action); // logs a users action in history
        void reset(USERS user); // resets the file permission to PL_NONE (OWNER only)

        FPM clone() const; // returns a copy of this PFM object

        std::string getPermissionLevel_user(USERS user); // returns a string describing the users permission level
        std::string getPermissionLevel_file() const; // returns a string describing the files permission level
        std::string AccessReport(USERS user); // returns a report of the users access to the file
        std::string getOwner(); // returns the current OWNER's name

        std::vector<std::string> getHistory() const; // returns the full action history
        std::vector<std::string> filterHistory(USERS user) const; // returns the history filtered by user level
};

#endif
