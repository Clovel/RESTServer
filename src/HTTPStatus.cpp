/**
 * @brief HTTP status codes
 * 
 * @file HTTPStatus.cpp
 */

/* Includes -------------------------------------------- */
#include "HTTPStatus.hpp"

/* C++ system */
#include <string>

/* Defines --------------------------------------------- */

/* Functions ------------------------------------------- */
std::string toStr(const HttpStatus &pStatus) {
    switch(pStatus) {
        case HttpStatus::CONTINUE:
            return "Continue";
            break;
        case HttpStatus::SWITCHING_PROTOCOLS:
            return "Switching Protocols";
            break;
        case HttpStatus::PROCESSING:
            return "Processing";
            break;
        case HttpStatus::EARLY_HINTS:
            return "Early Hints";
            break;
        case HttpStatus::OK:
            return "OK";
            break;
        case HttpStatus::CREATED:
            return "Created";
            break;
        case HttpStatus::ACCEPTED:
            return "Accepted";
            break;
        case HttpStatus::NON_AUTH_INFO:
            return "Non-Authoritative Information";
            break;
        case HttpStatus::NO_CONTENT:
            return "No Content";
            break;
        case HttpStatus::RESET_CONTENT:
            return "Reset Content";
            break;
        case HttpStatus::PARTIAL_CONTENT:
            return "Partial Content";
            break;
        case HttpStatus::MULTI_STATUS:
            return "Multi-Status";
            break;
        case HttpStatus::ALREADY_REPORTED:
            return "Already Reported";
            break;
        case HttpStatus::IM_USED:
            return "IM Used";
            break;
        case HttpStatus::MULTIPLE_CHOICES:
            return "Multiple Choices";
            break;
        case HttpStatus::MOVED_PERM:
            return "Moved Permanently";
            break;
        case HttpStatus::FOUND:
            return "Found (Moved Temporarily)";
            break;
        case HttpStatus::SEE_OTHER:
            return "See Other";
            break;
        case HttpStatus::NOT_MODIFIED:
            return "Not Modified";
            break;
        case HttpStatus::USE_PROXY:
            return "Use Proxy";
            break;
        case HttpStatus::SWITCH_PROXY:
            return "Switch Proxy";
            break;
        case HttpStatus::TEMP_REDIRECT:
            return "Temporary Redirect";
            break;
        case HttpStatus::PERM_REDIRECT:
            return "Permanent Redirect";
            break;
        case HttpStatus::BAD_REQUEST:
            return "Bad Request";
            break;
        case HttpStatus::UNAUTHORIZED:
            return "Unauthorized";
            break;
        case HttpStatus::PAYMENT_REQUIRED:
            return "Payment Required";
            break;
        case HttpStatus::FORBIDDEN:
            return "Forbidden";
            break;
        case HttpStatus::NOT_FOUND:
            return "Not Found";
            break;
        case HttpStatus::METHOD_NOT_ALLOWED:
            return "Method Not Allowed";
            break;
        case HttpStatus::NOT_ACCEPTABLE:
            return "Not Acceptable";
            break;
        case HttpStatus::PROXY_AUTH_REQUIRED:
            return "Proxy Authentication Required";
            break;
        case HttpStatus::REQUEST_TIMEOUT:
            return "Request Timeout";
            break;
        case HttpStatus::CONFLICT:
            return "Conflict";
            break;
        case HttpStatus::GONE:
            return "Gone";
            break;
        case HttpStatus::LEN_REQUIRED:
            return "Length Required";
            break;
        case HttpStatus::PRECONDITION_FAILED:
            return "Precondition Failed";
            break;
        case HttpStatus::PAYLOAD_TOO_LARGE:
            return " Payload Too Large";
            break;
        case HttpStatus::URI_TOO_LONG:
            return "URI Too Long";
            break;
        case HttpStatus::UNSUPPORTED_MEDIA_TYPE:
            return "Unsupported Media Type";
            break;
        case HttpStatus::RANGE_NOT_SATISFIABLE:
            return "Range Not Satisfiable";
            break;
        case HttpStatus::EXPECTATION_FAILED:
            return "Expectation Failed";
            break;
        case HttpStatus::IM_A_TEAPOT:
            return "I'm a teapot !";
            break;
        case HttpStatus::MISDIRECTED_REQUEST:
            return "Misdirected Request";
            break;
        case HttpStatus::UNPROCESSABLE_ENTITY:
            return "Unprocessable Entity";
            break;
        case HttpStatus::LOCKED:
            return "Locked";
            break;
        case HttpStatus::FAILED_DEPENDENCY:
            return "Failed Dependency";
            break;
        case HttpStatus::TOO_EARLY:
            return "Too Early";
            break;
        case HttpStatus::UPGRADE_REQUIRED:
            return "Upgrade Required";
            break;
        case HttpStatus::PRECONDITION_REQUIRED:
            return "Precondition Required";
            break;
        case HttpStatus::TOO_MANY_REQUESTS:
            return "Too Many Requests";
            break;
        case HttpStatus::REQUEST_HEADER_FIELDS_TOO_LARGE:
            return "Request Header Fields Too Large";
            break;
        case HttpStatus::UNAVAIL_LEGAL:
            return "Unavailable For Legal Reasons";
            break;
        case HttpStatus::INTERNAL_SERVER_ERROR:
            return "Internal Server Error";
            break;
        case HttpStatus::NOT_IMPLEMENTED:
            return "Not Implemented";
            break;
        case HttpStatus::BAD_GATEWAY:
            return "Bad Gateway";
            break;
        case HttpStatus::SERVICE_UNAVAILABLE:
            return "Service Unavailable";
            break;
        case HttpStatus::GATEWAY_TIMEOUT:
            return "Gateway Timeout";
            break;
        case HttpStatus::HTTP_VERSION_NOT_SUPPORTED:
            return "HTTP Version Not Supported";
            break;
        case HttpStatus::VARIANT_ALSO_NEGOTIATES:
            return "Variant Also Negotiates";
            break;
        case HttpStatus::INSUFFICIENT_STORAGE:
            return "Insufficient Storage";
            break;
        case HttpStatus::LOOP_DETECTED:
            return "Loop Detected";
            break;
        case HttpStatus::NOT_EXTENDED:
            return "Not Extended";
            break;
        case HttpStatus::NETWORK_AUTH_REQUIRED:
            return "Network Authentication Required";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}
