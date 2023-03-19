#include "catalog_service/catalog_server.h"


int main(int argc, char*argv[]) 
{
    HTTPWebServer app;
    return app.run(argc, argv);
}