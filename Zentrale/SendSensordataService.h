/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef SendSensordataService_H
#define SendSensordataService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "verbindung_types.h"

namespace Thrift {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class SendSensordataServiceIf {
 public:
  virtual ~SendSensordataServiceIf() {}
  virtual bool buildMessage(const Message& msg) = 0;
};

class SendSensordataServiceIfFactory {
 public:
  typedef SendSensordataServiceIf Handler;

  virtual ~SendSensordataServiceIfFactory() {}

  virtual SendSensordataServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(SendSensordataServiceIf* /* handler */) = 0;
};

class SendSensordataServiceIfSingletonFactory : virtual public SendSensordataServiceIfFactory {
 public:
  SendSensordataServiceIfSingletonFactory(const ::std::shared_ptr<SendSensordataServiceIf>& iface) : iface_(iface) {}
  virtual ~SendSensordataServiceIfSingletonFactory() {}

  virtual SendSensordataServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(SendSensordataServiceIf* /* handler */) {}

 protected:
  ::std::shared_ptr<SendSensordataServiceIf> iface_;
};

class SendSensordataServiceNull : virtual public SendSensordataServiceIf {
 public:
  virtual ~SendSensordataServiceNull() {}
  bool buildMessage(const Message& /* msg */) {
    bool _return = false;
    return _return;
  }
};

typedef struct _SendSensordataService_buildMessage_args__isset {
  _SendSensordataService_buildMessage_args__isset() : msg(false) {}
  bool msg :1;
} _SendSensordataService_buildMessage_args__isset;

class SendSensordataService_buildMessage_args {
 public:

  SendSensordataService_buildMessage_args(const SendSensordataService_buildMessage_args&);
  SendSensordataService_buildMessage_args& operator=(const SendSensordataService_buildMessage_args&);
  SendSensordataService_buildMessage_args() {
  }

  virtual ~SendSensordataService_buildMessage_args() noexcept;
  Message msg;

  _SendSensordataService_buildMessage_args__isset __isset;

  void __set_msg(const Message& val);

  bool operator == (const SendSensordataService_buildMessage_args & rhs) const
  {
    if (!(msg == rhs.msg))
      return false;
    return true;
  }
  bool operator != (const SendSensordataService_buildMessage_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SendSensordataService_buildMessage_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class SendSensordataService_buildMessage_pargs {
 public:


  virtual ~SendSensordataService_buildMessage_pargs() noexcept;
  const Message* msg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _SendSensordataService_buildMessage_result__isset {
  _SendSensordataService_buildMessage_result__isset() : success(false), unavailable(false) {}
  bool success :1;
  bool unavailable :1;
} _SendSensordataService_buildMessage_result__isset;

class SendSensordataService_buildMessage_result {
 public:

  SendSensordataService_buildMessage_result(const SendSensordataService_buildMessage_result&);
  SendSensordataService_buildMessage_result& operator=(const SendSensordataService_buildMessage_result&);
  SendSensordataService_buildMessage_result() : success(0) {
  }

  virtual ~SendSensordataService_buildMessage_result() noexcept;
  bool success;
  ClientUnavailable unavailable;

  _SendSensordataService_buildMessage_result__isset __isset;

  void __set_success(const bool val);

  void __set_unavailable(const ClientUnavailable& val);

  bool operator == (const SendSensordataService_buildMessage_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(unavailable == rhs.unavailable))
      return false;
    return true;
  }
  bool operator != (const SendSensordataService_buildMessage_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SendSensordataService_buildMessage_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _SendSensordataService_buildMessage_presult__isset {
  _SendSensordataService_buildMessage_presult__isset() : success(false), unavailable(false) {}
  bool success :1;
  bool unavailable :1;
} _SendSensordataService_buildMessage_presult__isset;

class SendSensordataService_buildMessage_presult {
 public:


  virtual ~SendSensordataService_buildMessage_presult() noexcept;
  bool* success;
  ClientUnavailable unavailable;

  _SendSensordataService_buildMessage_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class SendSensordataServiceClient : virtual public SendSensordataServiceIf {
 public:
  SendSensordataServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  SendSensordataServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool buildMessage(const Message& msg);
  void send_buildMessage(const Message& msg);
  bool recv_buildMessage();
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class SendSensordataServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<SendSensordataServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (SendSensordataServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_buildMessage(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  SendSensordataServiceProcessor(::std::shared_ptr<SendSensordataServiceIf> iface) :
    iface_(iface) {
    processMap_["buildMessage"] = &SendSensordataServiceProcessor::process_buildMessage;
  }

  virtual ~SendSensordataServiceProcessor() {}
};

class SendSensordataServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  SendSensordataServiceProcessorFactory(const ::std::shared_ptr< SendSensordataServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::std::shared_ptr< SendSensordataServiceIfFactory > handlerFactory_;
};

class SendSensordataServiceMultiface : virtual public SendSensordataServiceIf {
 public:
  SendSensordataServiceMultiface(std::vector<std::shared_ptr<SendSensordataServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~SendSensordataServiceMultiface() {}
 protected:
  std::vector<std::shared_ptr<SendSensordataServiceIf> > ifaces_;
  SendSensordataServiceMultiface() {}
  void add(::std::shared_ptr<SendSensordataServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  bool buildMessage(const Message& msg) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->buildMessage(msg);
    }
    return ifaces_[i]->buildMessage(msg);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class SendSensordataServiceConcurrentClient : virtual public SendSensordataServiceIf {
 public:
  SendSensordataServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  SendSensordataServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool buildMessage(const Message& msg);
  int32_t send_buildMessage(const Message& msg);
  bool recv_buildMessage(const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

} // namespace

#endif