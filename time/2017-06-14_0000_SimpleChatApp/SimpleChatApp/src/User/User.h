#pragma once

#include "StdPlus/StdPlus.h"

class ISocket;

struct UserData
{
    int         m_id;
    std::string m_name;
    bool        m_status;
};

struct MsgData
{
    int         m_from;
    int         m_to;
    std::string m_msg;
};

bool operator<(const MsgData & left, const MsgData & right);

typedef std::list<MsgData> MsgContainer;

class User
{
public:
    ISocket *    m_ptrUserSocket;
    UserData     m_userData;
    MsgContainer m_storeMessages; // все сообщения от этого юзера
};

User makeNewUser(ISocket * newClientSocket);

MsgData fillMsgData(int from, int to, std::string msg);

std::ostream & operator<<(std::ostream & s, const MsgData & msg);

std::ostream & operator<<(std::ostream & s, const User & user);

std::ostream & operator<<(std::ostream & os, const UserData & usData);


bool operator==(const User & left, const User & right);