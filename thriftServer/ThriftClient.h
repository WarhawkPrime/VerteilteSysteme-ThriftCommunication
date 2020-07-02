#pragma once

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




class ThriftClient {

public:
	ThriftClient() {}
	~ThriftClient() {}

	bool startThrift();

};

