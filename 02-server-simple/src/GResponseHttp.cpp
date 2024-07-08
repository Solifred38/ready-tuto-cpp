//===============================================
#include "GResponseHttp.h"
//===============================================
GENUM_CONVERT(
      eGResponseHttpStatus , GString

    , {eGResponseHttpStatus::Continue                       , "Continue"}
    , {eGResponseHttpStatus::SwitchingProtocol              , "SwitchingProtocol"}
    , {eGResponseHttpStatus::Processing                     , "Processing"}
    , {eGResponseHttpStatus::EarlyHints                     , "EarlyHints"}

    , {eGResponseHttpStatus::Ok                             , "Ok"}
    , {eGResponseHttpStatus::Created                        , "Created"}
    , {eGResponseHttpStatus::Accepted                       , "Accepted"}
    , {eGResponseHttpStatus::NonAuthoritativeInformation    , "NonAuthoritativeInformation"}
    , {eGResponseHttpStatus::NoContent                      , "NoContent"}
    , {eGResponseHttpStatus::ResetContent                   , "ResetContent"}
    , {eGResponseHttpStatus::PartialContent                 , "PartialContent"}
    , {eGResponseHttpStatus::MultiStatus                    , "MultiStatus"}
    , {eGResponseHttpStatus::AlreadyReported                , "AlreadyReported"}
    , {eGResponseHttpStatus::ImUsed                         , "ImUsed"}

    , {eGResponseHttpStatus::MultipleChoice                 , "MultipleChoice"}
    , {eGResponseHttpStatus::MovedPermanently               , "MovedPermanently"}
    , {eGResponseHttpStatus::Found                          , "Found"}
    , {eGResponseHttpStatus::SeeOther                       , "SeeOther"}
    , {eGResponseHttpStatus::NotModified                    , "NotModified"}
    , {eGResponseHttpStatus::UseProxy                       , "UseProxy"}
    , {eGResponseHttpStatus::TemporaryRedirect              , "TemporaryRedirect"}
    , {eGResponseHttpStatus::PermanentRedirect              , "PermanentRedirect"}

    , {eGResponseHttpStatus::BadRequest                     , "BadRequest"}
    , {eGResponseHttpStatus::Unauthorized                   , "Unauthorized"}
    , {eGResponseHttpStatus::PaymentRequired                , "PaymentRequired"}
    , {eGResponseHttpStatus::Forbidden                      , "Forbidden"}
    , {eGResponseHttpStatus::NotFound                       , "NotFound"}
    , {eGResponseHttpStatus::MethodNotAllowed               , "MethodNotAllowed"}
    , {eGResponseHttpStatus::NotAcceptable                  , "NotAcceptable"}
    , {eGResponseHttpStatus::ProxyAuthenticationRequired    , "ProxyAuthenticationRequired"}
    , {eGResponseHttpStatus::RequestTimeout                 , "RequestTimeout"}
    , {eGResponseHttpStatus::Conflict                       , "Conflict"}
    , {eGResponseHttpStatus::Gone                           , "Gone"}
    , {eGResponseHttpStatus::LengthRequired                 , "LengthRequired"}
    , {eGResponseHttpStatus::PreconditionFailed             , "PreconditionFailed"}
    , {eGResponseHttpStatus::PayloadTooLarge                , "PayloadTooLarge"}
    , {eGResponseHttpStatus::UriTooLong                     , "UriTooLong"}
    , {eGResponseHttpStatus::UnsupportedMediaType           , "UnsupportedMediaType"}
    , {eGResponseHttpStatus::RangeNotSatisfiable            , "RangeNotSatisfiable"}
    , {eGResponseHttpStatus::ExpectationFailed              , "ExpectationFailed"}
    , {eGResponseHttpStatus::MisdirectedRequest             , "MisdirectedRequest"}
    , {eGResponseHttpStatus::UnprocessableEntity            , "UnprocessableEntity"}
    , {eGResponseHttpStatus::Locked                         , "Locked"}
    , {eGResponseHttpStatus::FailedDependency               , "FailedDependency"}
    , {eGResponseHttpStatus::TooEarly                       , "TooEarly"}
    , {eGResponseHttpStatus::UpgradeRequired                , "UpgradeRequired"}
    , {eGResponseHttpStatus::PreconditionRequired           , "PreconditionRequired"}
    , {eGResponseHttpStatus::TooManyRequests                , "TooManyRequests"}
    , {eGResponseHttpStatus::RequestHeaderFieldsTooLarge    , "RequestHeaderFieldsTooLarge"}
    , {eGResponseHttpStatus::UnavailableForLegalReasons     , "UnavailableForLegalReasons"}

    , {eGResponseHttpStatus::InternalServerError            , "InternalServerError"}
    , {eGResponseHttpStatus::NotImplemented                 , "NotImplemented"}
    , {eGResponseHttpStatus::BadGateway                     , "BadGateway"}
    , {eGResponseHttpStatus::ServiceUnavailable             , "ServiceUnavailable"}
    , {eGResponseHttpStatus::GatewayTimeout                 , "GatewayTimeout"}
    , {eGResponseHttpStatus::HttpVersionNotSupported        , "HttpVersionNotSupported"}
    , {eGResponseHttpStatus::VariantAlsoNegotiates          , "VariantAlsoNegotiates"}
    , {eGResponseHttpStatus::InsufficientStorage            , "InsufficientStorage"}
    , {eGResponseHttpStatus::LoopDetected                   , "LoopDetected"}
    , {eGResponseHttpStatus::NotExtended                    , "NotExtended"}
    , {eGResponseHttpStatus::NetworkAuthenticationRequired  , "NetworkAuthenticationRequired"}
)
//===============================================
GResponseHttp::GResponseHttp()
: m_status          (eGResponseHttpStatus::Ok)
, m_reason          (GENUM_TO_VALUE(eGResponseHttpStatus, m_status))
, m_responseType    (rdv::RESPONSE_TYPE_HTML)
, m_version         (rdv::HTTP_1_1) {

}
//===============================================
GResponseHttp::~GResponseHttp() {

}
//===============================================
void GResponseHttp::run() {
    std::stringstream lResponseHttp;
    lResponseHttp << m_version << " " << static_cast<int>(m_status) << " " << m_reason << std::endl;
    lResponseHttp << "Content-Type: " << m_responseType << std::endl;
    lResponseHttp << "Content-Length: " << m_responseData.size() << std::endl;
    lResponseHttp << std::endl;
    lResponseHttp << m_responseData << std::endl;
    m_responseText = lResponseHttp.str();
}
//===============================================
