#include "StdPlus/StdPlus.h"

#include "RealSocket/RealSocketFactory.h"
#include "RealSocket/RealSocket.h"

#include "Net/ISocketStream.hpp"
#include "RealSocket/SupportFunctions.hpp"

#include "Client/ClientCore.h"
#include "Client/NetworkMap.h"

int main(int argc, char ** argv)
{
    AMSG("Hello from Client");
    APAUSE_MSG("Press any key for start client");

    stdplus::CmdParser cmd;
    cmd.parseData(argc, argv);

    std::string ip = cmd.getValue<std::string>("ip", "127.0.0.1");
    int port = cmd.getValue<int>("port", 34567);

    AVAR(ip);
    AVAR(port);

    ClientCore client;
    std::string fullAdress = ip + ":" + stdplus::to_string(port);

    client.connect(fullAdress);

    std::string prefix = "none";
    ARED(prefix);

    int idTo = 0;
    ARED(idTo);

    unsigned i = 0;
    while (client.isConnecting())
    {
        APAUSE_MSG("press for sent next msg");
        std::string msg = prefix + "_" + stdplus::to_string(i);
        AVAR(msg);
        client.sendData(idTo, msg);
        i++;

        MsgContainer inp = client.getMessages();

        for (auto & msg : inp)
        {
            AVAR(msg); 
        }
    }
    client.disconnect();


    APAUSE_MSG("Press any key for close console window");
}