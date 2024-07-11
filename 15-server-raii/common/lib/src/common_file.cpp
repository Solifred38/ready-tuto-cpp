//===============================================
#include "common_file.h"
//===============================================
common_file::common_file(const common_string& _filename)
: m_filename(_filename) {

}
//===============================================
common_file::~common_file() {

}
//===============================================
bool common_file::existFile() const {
    std::ifstream lFile(m_filename.c_str());
    return lFile.good();
}
//===============================================
common_string common_file::readText() {
    if(!existFile()) {
        slog(eGERR, "Le fichier n'existe pas."
        "|filename=%s", m_filename.c_str());
        m_errors.addProblem();
        return "";
    }
    std::ifstream lFile(m_filename.c_str());
    if(!lFile) {
        slog(eGERR, "L'ouverture du fichier a échoué."
        "|filename=%s", m_filename.c_str());
        m_errors.addProblem();
        return "";
    }
    std::stringstream lBuffer;
    lBuffer << lFile.rdbuf();
    return lBuffer.str();
}
//===============================================
common_string common_file::readBin() {
    if(!existFile()) {
        slog(eGERR, "Le fichier n'existe pas."
        "|filename=%s", m_filename.c_str());
        m_errors.addProblem();
        return "";
    }
    std::ifstream lFile(m_filename.c_str(), std::ios::in | std::ios::binary);
    if(!lFile) {
        slog(eGERR, "L'ouverture du fichier a échoué."
        "|filename=%s", m_filename.c_str());
        return "";
    }
    std::vector<char> lData = std::vector<char>(std::istreambuf_iterator<char>(lFile), std::istreambuf_iterator<char>());
    return lData;
}
//===============================================
bool common_file::appendText(const common_string& _data) {
    if(!existFile()) {
        slog(eGERR, "Le fichier n'existe pas."
        "|filename=%s", m_filename.c_str());
        m_errors.addProblem();
        return "";
    }
    std::ofstream lFile(m_filename.c_str(), std::ios::out | std::ios::app);
    if(!lFile) {
        slog(eGERR, "L'ouverture du fichier a échoué."
        "|filename=%s", m_filename.c_str());
        m_errors.addProblem();
        return false;
    }
    lFile << _data.c_str();
    return !m_errors.hasErrors();
}
//===============================================
bool common_file::writeText(const common_string& _data) {
    if(!existFile()) {
        slog(eGERR, "Le fichier n'existe pas."
        "|filename=%s", m_filename.c_str());
        m_errors.addProblem();
        return "";
    }
    std::ofstream lFile(m_filename.c_str());
    if(!lFile) {
        slog(eGERR, "L'ouverture du fichier a échoué."
        "|filename=%s", m_filename.c_str());
        m_errors.addProblem();
        return false;
    }
    lFile << _data.c_str();
    return !m_errors.hasErrors();
}
//===============================================
bool common_file::writeBin(const common_string& _data) {
    if(!existFile()) {
        slog(eGERR, "Le fichier n'existe pas."
        "|filename=%s", m_filename.c_str());
        m_errors.addProblem();
        return "";
    }
    std::ofstream lFile(m_filename.c_str(), std::ios::out | std::ios::binary);
    if(!lFile) {
        slog(eGERR, "L'ouverture du fichier a échoué."
        "|filename=%s", m_filename.c_str());
        return false;
    }
    lFile.write(_data.c_str(), _data.size());
    return !m_errors.hasErrors();
}
//===============================================
