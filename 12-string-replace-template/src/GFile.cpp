//===============================================
#include "GFile.h"
//===============================================
GFile::GFile() {

}
//===============================================
GFile::GFile(const GString& _filename)
: m_filename(_filename) {

}
//===============================================
GFile::~GFile() {

}
//===============================================
bool GFile::existFile() const {
    std::ifstream lFile(m_filename.c_str());
    return lFile.good();
}
//===============================================
GString GFile::readText() {
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
GString GFile::readBin() {
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
bool GFile::appendText(const GString& _data) {
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
bool GFile::writeText(const GString& _data) {
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
bool GFile::writeBin(const GString& _data) {
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
