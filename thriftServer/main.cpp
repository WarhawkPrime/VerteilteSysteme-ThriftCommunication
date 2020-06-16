#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "SendSensordataService.h"
#include "ServerFileManagement.h"


#include <ostream>
#include <fstream>


using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Thrift;


int main() {

    //::std::shared_ptr<SendSensordataServiceHandler> handler(new SendSensordataServiceHandler());
    //::std::shared_ptr<TProcessor> processor(new SendSensordataServiceProcessor(handler));
    //::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket("localhost", 9090));
    //::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    //::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    ::std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
    ::std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    ::std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    SendSensordataServiceClient client(protocol);
    ServerFileManagement* handle = new ServerFileManagement();

        transport->open();

        SensorDataMessage msg;
  
        std::ofstream file;
        
        file.open(handle->getAll(), ios::app);

        if (file.is_open()) {

            std::ostream& os = file;
            client.getData(msg);
            msg.printTo(os);
	    std::cout << "Current Data: " <<  handle->readLineFromFile(handle->getAll(), 0, true) << std::endl;
        }
        else {
            std::cout << "Couldn't write to " << handle->getAll() << "!" << std::endl;
        }
        transport->close();
	delete handle;
	return 0;
}
