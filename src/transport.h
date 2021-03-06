#pragma once

#include "preheader.h"

namespace ucorf
{
    typedef boost::any SessId;

    class ITransport
    {
    public:
        typedef boost::function<size_t(SessId, const char* data, size_t bytes)> OnReceiveF;
        typedef boost::function<void(boost_ec const&)> OnSndF;
        typedef boost::function<void(SessId)> OnConnectedF;
        typedef boost::function<void(SessId, boost_ec const&)> OnDisconnectedF;

        virtual ~ITransport() {}

        virtual void Shutdown() = 0;
        virtual void SetReceiveCb(OnReceiveF const&) = 0;
        virtual void SetConnectedCb(OnConnectedF const&) {}
        virtual void SetDisconnectedCb(OnDisconnectedF const&) {}
        virtual void SetOption(boost::any const& opt) {}
    };

    class ITransportServer : public ITransport
    {
    public:
        virtual boost_ec Listen(std::string const& url) = 0;
        virtual void Send(SessId id, const void* data, size_t bytes, OnSndF const& cb = NULL) = 0;
        virtual std::string LocalUrl() const = 0;
    };

    class ITransportClient : public ITransport
    {
    public:
        virtual boost_ec Connect(std::string const& url) = 0;
        virtual void Send(const void* data, size_t bytes, OnSndF const& cb = NULL) = 0;
        virtual bool IsEstab() = 0;
        virtual std::string RemoteUrl() const = 0;
    };

} //namespace ucorf
