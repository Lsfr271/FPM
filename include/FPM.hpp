/* LSFR__ 26/11/2025 (November 26th, 2025)

    Questions you might ask:
        What is PFM? PFM is a File Permission Manager. (Originally called Permission File Manager (PFM))
        Can you use PFM? Yes, this is open source.
        Can you modify PFM's Source code? No, not for now.
        Can you join in as a contributor? No, not for now.
*/

#ifndef PFM_MANAGER_H
#define PFM_MANAGER_H

#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <algorithm>


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

struct PFM {
    public:
        FILES _fp;

        PFM() = default;
        PFM(FILES fp) : _fp(fp) {}

        bool canDeleteFile(USERS user);
        bool canSeeFile(USERS user);
        bool canModifyFile(USERS user);
        bool canRenameFile(USERS user);
        bool isHidden(USERS user);
        bool isProtected();
        bool hasFullControl(USERS user);
        bool isAccessible(USERS user);

        void setPermissions(FILES newPerm, USERS user);
        void promoteToAdmin(const std::string& name);
        void promoteToOwner(const std::string& name);
        void lockFile(USERS user);
        void unlockFile(USERS user);


        std::string getPermissionLevel_user(USERS user);
        std::string getPermissionLevel_file();
        std::string AccessReport(USERS user);
};

#endif
