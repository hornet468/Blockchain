#include <httplib.h>
#include "../node/node.h"


void server() {
   httplib::Server server;
   Node node("Node one");
   
   


   server.listen("123.45", 8080);
}
