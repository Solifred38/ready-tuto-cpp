#include "maj_db_sqlite_res.h"
#include "maj_db_sqlite_run.h"
#include "common_file.h"

maj_db_sqlite_res::maj_db_sqlite_res()
: m_resRoot("../res")
, m_resPath("/sqlite/scripts") {

}

maj_db_sqlite_res::~maj_db_sqlite_res() {

}

void maj_db_sqlite_res::run() {
    common_string lPath = m_resRoot + m_resPath;

    DIR* lDir = opendir(lPath.c_str());
    if(!lDir) {
        slog(eGERR, "Le chemin de la ressource n'existe pas."
        "|codeErreur=%d"
        "|msgErreur=%s"
        "|path=%s", errno, strerror(errno), lPath.c_str());
        m_errors.addProblem();
        return;
    }

    const common_string DIR_CUR      = ".";
    const common_string DIR_PREV     = "..";
    const common_string RES_SEP      = "-";
    const common_string SOURCE_SEP   = ";";

    while(1) {
        struct dirent* lEntry = readdir(lDir);

        if(!lEntry) break;

        common_string lFilename = lEntry->d_name;

        if(lFilename == DIR_CUR) continue;
        if(lFilename == DIR_PREV) continue;

        common_string lFullname = lPath + "/" + lFilename;
        struct stat lInfo ;

        if(stat(lFullname.c_str(), &lInfo) == -1) {
            slog(eGERR, "La recherche des infos sur la ressource a échoué."
            "|codeErreur=%d"
            "|msgErreur=%s"
            "|path=%s", errno, strerror(errno), lFullname.c_str());
            m_errors.addProblem();
            continue;
        }

        if((lInfo.st_mode & S_IFMT) == S_IFDIR) {
            slog(eGERR, "La ressource ne doit pas être de type répertoire."
            "|path=%s", lFullname.c_str());
            continue;
        }
        else {
            int lCount = lFilename.countSep(RES_SEP);
            if(lCount != 2) {
                slog(eGERR, "Le chemin de la ressource doit contenir un seul caractère (-)."
                "|path=%s", lFullname.c_str());
                continue;
            }

            common_string lCode = lFilename.extractSep(RES_SEP, 0);

            if(lCode.size() != 6) {
                slog(eGERR, "Le code de la ressource doit avoir une taille de 6 caractères."
                "|path=%s", lFullname.c_str());
                continue;
            }

            common_file lFile(lFullname);
            common_string lSource = lFile.readText();

            if(lFile.getErrors().hasErrors()) {
                slog(eGERR, "La lecture de la ressource a échoué."
                "|path=%s", lFullname.c_str());
                m_errors.addErrors(lFile.getErrors());
                continue;
            }

            int lCount2 = lSource.countSep(SOURCE_SEP);
            std::vector<common_string> lSourceList;

            for(int i = 0; i < lCount2; i++) {
                common_string lSourceItem = lSource.extractSep(SOURCE_SEP, i).trim();
                if(lSourceItem.empty()) continue;
                lSourceList.push_back(lSourceItem);
            }

            maj_db_sqlite_run lRes(lCode, lFilename, lSourceList);
            lRes.run();

            if(lRes.getErrors().hasErrors()) {
                slog(eGERR, "L'exécution de la ressource a échoué."
                "|path=%s", lFullname.c_str());
                m_errors.addErrors(lRes.getErrors());
                continue;
            }
        }
    }
}
