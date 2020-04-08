/** 
 * RESTServer project
 * 
 * @file webpages.hpp
 */
#ifndef WEBPAGES_HPP
#define WEBPAGES_HPP

/* Includes -------------------------------------------- */
#include "HTTPStatus.hpp"

/* C++ system */
#include <string>

/* Defines --------------------------------------------- */

/* Forward declarations -------------------------------- */

/* Build header functions ------------------------------ */
std::string buildHeader(const std::string &pHTTPVersion, const HttpStatus &pStatus);

/* Variable declarations ------------------------------- */
extern const char * const htmlResponseCode200;
extern const char * const htmlResponseCode400;
extern const char * const htmlResponseCode404;
extern const char * const htmlResponseCode500;
extern const char * const htmlResponseCode501;

extern const char * const htmlDocType;
extern const char * const htmlPageBegin;
extern const char * const htmlPageEnd;
extern const char * const htmlHead;

extern const char * const htmlGeneralKenobi;

#endif /* WEBPAGES_HPP */
