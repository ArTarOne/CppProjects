#include "StdPlus/StdPlus.h"
#include "User/User.h"
#include "Net/ISocket.h"


bool operator<(const MsgData & left, const MsgData & right)
{
    if (left.m_from >= right.m_from)
        return false;

    if (left.m_to >= right.m_to)
        return false;

    if (left.m_msg >= right.m_msg)
        return false;

    return true;
}

User makeNewUser(ISocket * newClientSocket)
{
    AFUN;

    User user;

    user.m_ptrUserSocket = newClientSocket;
    static unsigned id = 0;
    id++;
    user.m_userData.m_id = id;
    AVAR(user.m_userData.m_id);
    user.m_userData.m_name = "User";
    user.m_userData.m_status = true;

    return user;
}

MsgData fillMsgData(int from, int to, std::string msg)
{
    MsgData newMsgData;

    newMsgData.m_from = from;
    newMsgData.m_to = to;
    newMsgData.m_msg = msg;

    return newMsgData;
}

std::ostream & operator<<(std::ostream & os, const MsgData & msg)
{
    os
        << "m_from=" << msg.m_from << "; "
        << "m_to=" << msg.m_to << "; "
        << "m_msg=" << msg.m_msg << "; "
        ;
    return os;
}

std::ostream & operator<<(std::ostream & os, const User & user)
{
    os
        << "name=" << user.m_userData.m_name << "; "
        << "id=" << user.m_userData.m_id << "; "
        << "countMsgs=" << user.m_storeMessages.size() << "; "
        ;

    int index = 0;
    for (auto & userMsg : user.m_storeMessages)
    {
        os << std::endl;
        os << index << " " << userMsg;
        index++;
    }

    return os;
}

bool operator==(const User & left, const User & right)
{
    return left.m_ptrUserSocket == right.m_ptrUserSocket;
}



std::ostream & operator<<(std::ostream & os, const UserData & usData)
{
    os
        << "m_id=" << usData.m_id << "; "
        << "m_name=" << usData.m_name << "; "
        << "m_status=" << usData.m_status << "; "
        ;
    return os;
}