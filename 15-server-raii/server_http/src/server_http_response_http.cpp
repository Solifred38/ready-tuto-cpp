#include "server_http_response_http.h"

GENUM_CONVERT(
      e_server_http_response_http_status , common_string

    , {e_server_http_response_http_status::Continue                       , "Continue"}
    , {e_server_http_response_http_status::SwitchingProtocol              , "SwitchingProtocol"}
    , {e_server_http_response_http_status::Processing                     , "Processing"}
    , {e_server_http_response_http_status::EarlyHints                     , "EarlyHints"}

    , {e_server_http_response_http_status::Ok                             , "Ok"}
    , {e_server_http_response_http_status::Created                        , "Created"}
    , {e_server_http_response_http_status::Accepted                       , "Accepted"}
    , {e_server_http_response_http_status::NonAuthoritativeInformation    , "NonAuthoritativeInformation"}
    , {e_server_http_response_http_status::NoContent                      , "NoContent"}
    , {e_server_http_response_http_status::ResetContent                   , "ResetContent"}
    , {e_server_http_response_http_status::PartialContent                 , "PartialContent"}
    , {e_server_http_response_http_status::MultiStatus                    , "MultiStatus"}
    , {e_server_http_response_http_status::AlreadyReported                , "AlreadyReported"}
    , {e_server_http_response_http_status::ImUsed                         , "ImUsed"}

    , {e_server_http_response_http_status::MultipleChoice                 , "MultipleChoice"}
    , {e_server_http_response_http_status::MovedPermanently               , "MovedPermanently"}
    , {e_server_http_response_http_status::Found                          , "Found"}
    , {e_server_http_response_http_status::SeeOther                       , "SeeOther"}
    , {e_server_http_response_http_status::NotModified                    , "NotModified"}
    , {e_server_http_response_http_status::UseProxy                       , "UseProxy"}
    , {e_server_http_response_http_status::TemporaryRedirect              , "TemporaryRedirect"}
    , {e_server_http_response_http_status::PermanentRedirect              , "PermanentRedirect"}

    , {e_server_http_response_http_status::BadRequest                     , "BadRequest"}
    , {e_server_http_response_http_status::Unauthorized                   , "Unauthorized"}
    , {e_server_http_response_http_status::PaymentRequired                , "PaymentRequired"}
    , {e_server_http_response_http_status::Forbidden                      , "Forbidden"}
    , {e_server_http_response_http_status::NotFound                       , "NotFound"}
    , {e_server_http_response_http_status::MethodNotAllowed               , "MethodNotAllowed"}
    , {e_server_http_response_http_status::NotAcceptable                  , "NotAcceptable"}
    , {e_server_http_response_http_status::ProxyAuthenticationRequired    , "ProxyAuthenticationRequired"}
    , {e_server_http_response_http_status::RequestTimeout                 , "RequestTimeout"}
    , {e_server_http_response_http_status::Conflict                       , "Conflict"}
    , {e_server_http_response_http_status::Gone                           , "Gone"}
    , {e_server_http_response_http_status::LengthRequired                 , "LengthRequired"}
    , {e_server_http_response_http_status::PreconditionFailed             , "PreconditionFailed"}
    , {e_server_http_response_http_status::PayloadTooLarge                , "PayloadTooLarge"}
    , {e_server_http_response_http_status::UriTooLong                     , "UriTooLong"}
    , {e_server_http_response_http_status::UnsupportedMediaType           , "UnsupportedMediaType"}
    , {e_server_http_response_http_status::RangeNotSatisfiable            , "RangeNotSatisfiable"}
    , {e_server_http_response_http_status::ExpectationFailed              , "ExpectationFailed"}
    , {e_server_http_response_http_status::MisdirectedRequest             , "MisdirectedRequest"}
    , {e_server_http_response_http_status::UnprocessableEntity            , "UnprocessableEntity"}
    , {e_server_http_response_http_status::Locked                         , "Locked"}
    , {e_server_http_response_http_status::FailedDependency               , "FailedDependency"}
    , {e_server_http_response_http_status::TooEarly                       , "TooEarly"}
    , {e_server_http_response_http_status::UpgradeRequired                , "UpgradeRequired"}
    , {e_server_http_response_http_status::PreconditionRequired           , "PreconditionRequired"}
    , {e_server_http_response_http_status::TooManyRequests                , "TooManyRequests"}
    , {e_server_http_response_http_status::RequestHeaderFieldsTooLarge    , "RequestHeaderFieldsTooLarge"}
    , {e_server_http_response_http_status::UnavailableForLegalReasons     , "UnavailableForLegalReasons"}

    , {e_server_http_response_http_status::InternalServerError            , "InternalServerError"}
    , {e_server_http_response_http_status::NotImplemented                 , "NotImplemented"}
    , {e_server_http_response_http_status::BadGateway                     , "BadGateway"}
    , {e_server_http_response_http_status::ServiceUnavailable             , "ServiceUnavailable"}
    , {e_server_http_response_http_status::GatewayTimeout                 , "GatewayTimeout"}
    , {e_server_http_response_http_status::HttpVersionNotSupported        , "HttpVersionNotSupported"}
    , {e_server_http_response_http_status::VariantAlsoNegotiates          , "VariantAlsoNegotiates"}
    , {e_server_http_response_http_status::InsufficientStorage            , "InsufficientStorage"}
    , {e_server_http_response_http_status::LoopDetected                   , "LoopDetected"}
    , {e_server_http_response_http_status::NotExtended                    , "NotExtended"}
    , {e_server_http_response_http_status::NetworkAuthenticationRequired  , "NetworkAuthenticationRequired"}
)

server_http_response_http::server_http_response_http(
const common_string& _responseData
, const common_string& _responseType
, const e_server_http_response_http_status& _responseStatus) {
    m_responseData      = _responseData;
    m_responseType      = _responseType;
    m_responseStatus    = _responseStatus;
}

server_http_response_http::~server_http_response_http() {

}

void server_http_response_http::run() {
    std::stringstream lResponseText;
    lResponseText << "HTTP/1.1 " << static_cast<int>(m_responseStatus) << " " << GENUM_TO_VALUE(e_server_http_response_http_status, m_responseStatus) << std::endl;
    lResponseText << "Content-Type: " << m_responseType << std::endl;
    lResponseText << "Content-Length: " << m_responseData.size() << std::endl;
    lResponseText << std::endl;
    lResponseText << m_responseData << std::endl;
    m_responseText = lResponseText.str();
}

