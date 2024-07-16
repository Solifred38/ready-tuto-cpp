#include "common_template.h"

common_template::common_template()
: m_templateRoot    ("../res") {

}

common_template::common_template(const common_string& _templateRoot)
: m_templateRoot    (_templateRoot) {

}

common_template::~common_template() {

}

common_string common_template::parse(const common_string& _filename) {
    common_string lData;
    try {
        common_string lPath = m_templateRoot + _filename;
        inja::Environment lEnv;
        inja::Template lTemplate = lEnv.parse_template(lPath.c_str());
        lData = lEnv.render(lTemplate, m_dataJson);
    }
    catch(const std::exception& e) {
        slog(eGERR, "L'exécution du moteur de template a échoué."
        "|msgErreur=%s", e.what());
        m_errors.addProblem();
    }
    return lData;
}

common_string common_template::render(const common_string& _data) {
    common_string lData;
    try {
        inja::Environment lEnv;
        lData = lEnv.render(_data.c_str(), m_dataJson);
    }
    catch(const std::exception& e) {
        slog(eGERR, "L'exécution du moteur de template a échoué."
        "|msgErreur=%s", e.what());
        m_errors.addProblem();
    }
    return lData;
}

common_template& common_template::operator=(const common_template& _obj) {
    m_templateRoot  = _obj.m_templateRoot;
    m_dataJson      = _obj.m_dataJson;
    return *this;
}

nlohmann::json& common_template::operator[](const common_string& _key) {
    return m_dataJson[_key.c_str()];
}

