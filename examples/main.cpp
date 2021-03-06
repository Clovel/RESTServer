/**
 * @brief C++ REST API test main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "RESTServer.hpp"

/* C++ system */
#include <iostream>
#include <string>
#include <vector>
#include <memory>

/* C system */
#include <cstring>

/* Defines --------------------------------------------- */
#define ADDRESS "localhost"

/* Notes ----------------------------------------------- */

/* Variable declaration -------------------------------- */
std::unique_ptr<RESTServer> gRESTServer;

/* Type definitions ------------------------------------ */

/* Support functions ----------------------------------- */
static void printUsage(const char * const pProgName)
{
    std::cout << "[USAGE] %s" << pProgName << std::endl;
    std::cout << "        <arg1> : Localhost port number" << std::endl;
}

/* REST Test callbacks */
static RESTServer::methodFct_t sGetCallback = [](const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut) -> HttpStatus {
    pOut += "{\r\n";
    pOut += "\t\"Path\": \"" + pPath + "\"\r\n";

    for(uint8_t i = 0U; i < pQueries.size(); i++) {
        pOut += "\t\"" + pQueries.at(i) + "\": \"received\"";
        if(pQueries.size() - 1U != i) {
            pOut += ",";
        }
        pOut += "\r\n";
    }

    pOut += "}\r\n";

    return HttpStatus::OK;
};

/* ----------------------------------------------------- */
/* Main tests ------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    if ((argc < 2) || (std::strcmp(argv[1U], "--help") == 0)) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    std::string lAddr = ADDRESS;
    std::string lPort = std::string(argv[1U]);
    std::string lPath = "OSCO-OD-Gen/Action";

    /* Create server */
    gRESTServer = std::unique_ptr<RESTServer>(new RESTServer(lAddr, lPort, lPath));

    /* Set REST API callbacks */
    gRESTServer->setGetCallback(sGetCallback);

    /* Open server */
    if(!gRESTServer->open()) {
        return EXIT_FAILURE;
    }

    std::cout << "[INFO] Listening for request at: " << lAddr << ":" << lPort << "/" << lPath << std::endl;

    /* Main loop */
    gRESTServer->listen();

    /* Close server */
    if(!gRESTServer->close()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
