#include "ThriftClient.h"

bool ThriftClient::startThrift() {
    ::std::shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
    ::std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    ::std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    SendSensordataServiceClient client(protocol);
    ServerFileManagement* handle = new ServerFileManagement();

    transport->open();

    SensorDataMessage msg;

    std::ofstream file;

    file.open(handle->getAll(), ios::app);

    bool check;

    if (file.is_open()) {

        std::ostream& os = file;
        client.getData(msg);
        msg.printTo(os);
        std::cout << "Current Data: " << handle->readLineFromFile(handle->getAll(), 0, true) << std::endl;
        check = true;
    }
    else {
        std::cout << "Couldn't write to " << handle->getAll() << "!" << std::endl;
        check = false;
    }
    transport->close();
    delete handle;
    return check;
}