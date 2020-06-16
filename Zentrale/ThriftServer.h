// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "SendSensordataService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

using namespace std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace apache::thrift::concurrency;

using namespace  ::Thrift;

#include <ostream>
#include "FileManagement.h"

class SendSensordataServiceHandler : virtual public SendSensordataServiceIf {
public:
    SendSensordataServiceHandler() {
        // Your initialization goes here
    }

    void getData(SensorDataMessage& _return) {
        // Your implementation goes here

        FileManagement* handle = new FileManagement();

        //TO DO set the correct data from the FileManager
        std::string tempData = handle->readLineFromFile(handle->getTemp(), 0, true);
        std::string windData = handle->readLineFromFile(handle->getAirspd(), 0, true);
        std::string brightnessData = handle->readLineFromFile(handle->getLux(), 0, true);
        std::string humidityData = handle->readLineFromFile(handle->getHumidty(), 0, true);
       
        _return.newestTempData = tempData;
        _return.newestWindData = windData;
        _return.newestBrightnessData = brightnessData;
        _return.newestHumidityData = humidityData;

        std::cout << tempData << windData << brightnessData << humidityData << std::endl;
    }


    int initializeThrift() {

        SensorDataMessage msg;
        std::ostream &os = std::cout;   //goes into the console
        msg.printTo(os);
        

        int port = 9090;
        ::std::shared_ptr<SendSensordataServiceHandler> handler(new SendSensordataServiceHandler());
        ::std::shared_ptr<TProcessor> processor(new SendSensordataServiceProcessor(handler));
        ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket("127.0.0.1", port));
        ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
        ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

        TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
        server.serve();
        return 0;
    }

};

