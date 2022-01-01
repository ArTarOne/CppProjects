#include "StdPlus/StdPlus.h"

#include "RealSocket/RealSocketFactory.h"
#include "RealSocket/RealSocket.h"

#include "Net/ISocketStream.hpp"
#include "RealSocket/SupportFunctions.hpp"

#include "Server/Server.h"

int main(int argc, char ** argv)
{    
    std::string logFileName = stdplus::dateTimeStr() + " ServerLog.txt";
    std::ofstream logFile(logFileName);
    LOG_STD_REGISTER_STREAM(logFile);

    AMSG("Hello from Server");

    Server serv;

    stdplus::CmdParser cmd;
    cmd.parseData(argc, argv);
    std::string ip = cmd.getValue<std::string>("ip", "127.0.0.1");
    int port = cmd.getValue<int>("port", 34567);
    std::string fullAdress = ip + ":" + stdplus::to_string(port);
   
    try
    {
        serv.start(fullAdress);
    }
    catch (std::logic_error & exceptionInMain)
    {
        AVAR(exceptionInMain.what());
    }

    APAUSE_MSG("Press any key for close console window");
    LOG_STD_UNREGISTER_STREAM(logFile);
}