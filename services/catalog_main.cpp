#include "catalog_service/catalog_server.h"


int main(int argc, char*argv[]) 
{
    HTTPOtherWebServer app;
    return app.run(argc, argv);
}