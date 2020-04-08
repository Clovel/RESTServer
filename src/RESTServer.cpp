/**
 * @brief RESTServer class implementation
 * 
 * @file RESTServer.cpp
 */

/* Includes -------------------------------------------- */
#include "RESTServer.hpp"
#include "HTTPRequest.hpp"

#include "webpages.hpp"

/* C++ system */
#include <iostream>

/* C errno */
#include <cstring>
#include <cstdlib>
#include <errno.h>

/* C Network */
#include <sys/socket.h> /* socket */
#include <netinet/in.h> /* sockaddr_in */
#include <unistd.h>     /* close */

/* Defines --------------------------------------------- */
#define SERVER_BUFFER_SIZE 4096U

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* Helper functions ------------------------------------ */

/* RESTServer class implementation --------------------- */
/* Contructors */
RESTServer::RESTServer(const std::string &pAddr, const std::string pPort, const std::string &pPath) :
    mAddr(pAddr),
    mPort(pPort),
    mPath(pPath)
{
    /* Empty */
}

/* Destructor */
RESTServer::~RESTServer() {
    /* Empty */
}

/* Getters */
std::string RESTServer::address(void) const {
    return mAddr;
}

std::string RESTServer::port(void) const {
    return mPort;
}

std::string RESTServer::apiPath(void) const {
    return mPath;
}

RESTServer::methodFct_t RESTServer::getCallback(void) const {
    return mGetCallback;
}

RESTServer::methodFct_t RESTServer::postCallback(void) const {
    return mPostCallback;
}

RESTServer::methodFct_t RESTServer::putCallback(void) const {
    return mPutCallback;
}

RESTServer::methodFct_t RESTServer::delCallback(void) const {
    return mDelCallback;
}

/* Setters */
void RESTServer::setGetCallback(const methodFct_t &pFct) {
    mGetCallback = pFct;
}

void RESTServer::setPostCallback(const methodFct_t &pFct) {
    mPostCallback = pFct;
}

void RESTServer::setPutCallback(const methodFct_t &pFct) {
    mPutCallback = pFct;
}

void RESTServer::setDelCallback(const methodFct_t &pFct) {
    mDelCallback = pFct;
}

/* Server management */
bool RESTServer::open(void) {
    /* Create a socket */
    errno = 0;
    int lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if(0 > mServerSocket) {
        std::cerr << "[ERROR] <RESTServer::open> Failed to create socket" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    /* Set the socket member variable */
    mServerSocket = lSocket;

    /* Initialisation de la structure sockaddr_in */
    struct sockaddr_in lServerAddrIn;
    std::memset(&lServerAddrIn, 0, sizeof(struct sockaddr_in));
    /* Socket type */
    lServerAddrIn.sin_family = AF_INET;
    /* Accpeted client IP addresses */
    lServerAddrIn.sin_addr.s_addr = INADDR_ANY;
    /* Port */
    lServerAddrIn.sin_port = htons(std::atoi(mPort.c_str()));

    /* Set socket options */
    errno = 0;
    const int lEnableOption = 1;
    if(0 > setsockopt(mServerSocket, SOL_SOCKET, SO_REUSEADDR, (const void *)&lEnableOption, sizeof(lEnableOption))) {
        std::cerr << "[ERROR] <RESTServer::open> setsockopt SO_REUSEADDR failed" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }
    if(0 > setsockopt(mServerSocket, SOL_SOCKET, SO_REUSEPORT, (const void *)&lEnableOption, sizeof(lEnableOption))) {
        std::cerr << "[ERROR] <RESTServer::open> setsockopt SO_REUSEPORT failed" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    /* Bind socket */
    errno = 0;
    if(0 > bind(mServerSocket, (const struct sockaddr *)&lServerAddrIn , sizeof(lServerAddrIn))) {
        std::cerr << "[ERROR] <RESTServer::open> Failed to bind socket" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    return true;
}

bool RESTServer::listen(void) {
    /* Listen for connections */
    errno = 0;
    if(0 > ::listen(mServerSocket, 32)) {
        std::cerr << "[ERROR] <RESTServer::listen> Failed to listen for new connections" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    /* Set up before listening in */
    int lClientSock = 0;
    struct sockaddr_in lClientAddrIn;
    std::memset(&lClientAddrIn, 0, sizeof(struct sockaddr_in));
    socklen_t lsInSize = sizeof(lClientAddrIn);
    char lClientMsg[SERVER_BUFFER_SIZE];

    /* Start listening loop */
    while((lClientSock = accept(mServerSocket, (struct sockaddr *)&lClientAddrIn, &lsInSize))) {
        /* Check if the client is valid */
        if(0 <= lClientSock) {
            /* Read the contents of the message */
            size_t lReadBytes = 0;
            while(0 < (lReadBytes = recv(lClientSock, lClientMsg, SERVER_BUFFER_SIZE, 0))) {
                /* Process the message */
                std::cout << "[DEBUG] <RESTServer::listen> Got message : " << std::endl
                          << lClientMsg << std::endl;
                
                if(processClientMessage(lClientMsg, lReadBytes, lClientSock)) {
                    break; /* TODO : Manage error cases */
                }
            }

            /* Close the client's socket */
            errno = 0;
            if(0 > ::close(lClientSock)) {
                std::cerr << "[ERROR] <RESTServer::listen> Failed to close client socket" << std::endl;
                if(0 != errno) {
                    std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
                }

                return false;
            }
        } else {
            std::cerr << "[ERROR] <RESTServer::listen> Failed to accept client connection" << std::endl;
            if(0 != errno) {
                std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
            }

            return false;
        }
    }

    return true;
}

bool RESTServer::close(void) {
    errno = 0;
    if(0 > ::close(mServerSocket)) {
        std::cerr << "[ERROR] <RESTServer::close> Failed to close socket" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    return true;
}

bool RESTServer::processClientMessage(const char * const pMsg, const size_t &pReadBytes, const int &pClientSocket) const {
    (void)pReadBytes;

    if(nullptr == pMsg) {
        std::cerr << "[DEBUG] <RESTServer::processClientMessage> pMsg arg is nullptr" << std::endl;
        return false;
    }

    /* Set a httpMessage_t var for the HTTP Parser */
    HTTPRequest *lHTTPRequest = nullptr;
    try {
        lHTTPRequest = new HTTPRequest((std::string(pMsg)));
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <RESTServer::processClientMessage> Failed to parse the HTTPRequest" << std::endl;
        return false;
    }

    /* For debug purposes, print everything */
    std::cout << "[DEBUG] <RESTServer::processClientMessage> HTTPRequest contents : " << std::endl
        << "        Raw : " << std::endl << lHTTPRequest->msg() << std::endl
        << "        Method     : " << lHTTPRequest->methodStr() << std::endl
        << "        URL        : " << lHTTPRequest->URL() << std::endl
        << "        Path       : " << lHTTPRequest->path() << std::endl
        << "        Query      : " << lHTTPRequest->query() << std::endl
        << "        HTTPV      : " << lHTTPRequest->httpVersionStr() << std::endl
        << "        Host       : " << lHTTPRequest->host() << std::endl
        << "        User-Agent : " << lHTTPRequest->userAgent() << std::endl
        << "        Accept     : " << lHTTPRequest->accept() << std::endl
        ;

    int lSentBytes = 0;
    std::string lResponse = "";
    HttpStatus lStatus = HttpStatus::UNKNOWN;
    switch(lHTTPRequest->method()) {
        case HTTP_METHOD_GET:
            std::cout << "[DEBUG] <RESTServer::processClientMessage> Got GET request from client" << std::endl;

            /* Get through the REST Callback */
            lStatus = getCallback()(lHTTPRequest->path(), lHTTPRequest->queries(), lResponse);

            /* Build HTTP header */
            lResponse = buildHeader(lHTTPRequest->httpVersionStr(), lStatus) + "\r\n" + lResponse;

            std::cout << "[DEBUG] <RESTServer::processClientMessage> Response is :" << std::endl << lResponse << std::endl;

            lSentBytes = send(pClientSocket, lResponse.c_str(), std::strlen(lResponse.c_str()), 0);
            if(0 > lSentBytes) {
                std::cerr << "[ERROR] <RESTServer::processClientMessage> Failed to send a response to the client" << std::endl;
                if(0 != errno) {
                    std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
                }

                delete lHTTPRequest;

                return false;
            } else {
                std::cout << "[DEBUG] <RESTServer::processClientMessage> Sent " << lSentBytes << " bytes as a response" << std::endl;
            }
            break;
        default:
            std::cerr << "[ERROR] <RESTServer::processClientMessage> Got unsupported HTTP method request : " << lHTTPRequest->methodStr() << std::endl;

            lSentBytes = send(pClientSocket, htmlResponseCode501, std::strlen(htmlResponseCode501), 0);
            if(0 > lSentBytes) {
                std::cerr << "[ERROR] <RESTServer::processClientMessage> Failed to send a response to the client" << std::endl;
                if(0 != errno) {
                    std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
                }
            } else {
                std::cout << "[DEBUG] <RESTServer::processClientMessage> Sent " << lSentBytes << " bytes as a response" << std::endl;
            }

            delete lHTTPRequest;

            return false;
    }

    delete lHTTPRequest;

    return true;
}
