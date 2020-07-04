#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "SendSensordataService.h"
#include "ServerFileManagement.h"


#include <ostream>
#include <fstream>

#include "ThriftClient.h"


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

   	ThriftClient tc;
   	tc.startThrift();
	return 0;
}
