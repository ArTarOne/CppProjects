#pragma once

#include "ISocket.h"
#include "StdPlus\StdPlus.h"
#include "User\User.h"

#include "Client/NetworkMap.h"

enum SocketStreamType
{
    e_socketStreamType_none             ,
    e_socketStreamType_string           ,
    e_socketStreamType_file             ,
    e_socketStreamType_msg              ,
    e_socketStreamType_user             ,
    e_socketStreamType_userData         ,
    e_socketStreamType_ping             ,
    e_socketStreamType_vector           ,
    e_socketStreamType_list             ,
    e_socketStreamType_recieveClientData,
    e_socketStreamType_sendMsgs         ,
    e_socketStreamType_recvMsgs         ,

};

inline std::ostream & operator<<(std::ostream & os, const SocketStreamType & d)
{
    const static std::map<SocketStreamType, std::string> strs =
    {
        { e_socketStreamType_none             , "socketStreamType_none" },
        { e_socketStreamType_string           , "socketStreamType_string" },
        { e_socketStreamType_file             , "socketStreamType_file" },
        { e_socketStreamType_msg              , "socketStreamType_msg" },
        { e_socketStreamType_user             , "socketStreamType_user" },
        { e_socketStreamType_userData         , "socketStreamType_userData" },
        { e_socketStreamType_ping             , "socketStreamType_ping" },
        { e_socketStreamType_vector           , "socketStreamType_vector" },
        { e_socketStreamType_list             , "socketStreamType_list" },
        { e_socketStreamType_recieveClientData, "socketStreamType_recieveClientData" },
        { e_socketStreamType_sendMsgs         , "socketStreamType_sendMsgs" },
        { e_socketStreamType_recvMsgs         , "socketStreamType_recvMsgs" },
    };

    os << strs.at(d);

    return os;
}

template<typename T>
inline ISocket & operator<<(ISocket & s, const T & type)
{
    //AFUN;
    s.send((char *)&type, sizeof(type));
    return s;
}


template<typename T>
inline ISocket & operator >> (ISocket & s, T & type)
{
    //AFUN;
    s.recv((char *)&type, sizeof(type));
    return s;
}



inline ISocket & operator<<(ISocket & s, const std::string & str)
{
    s << e_socketStreamType_string;
    s << str.size();
    s.send(str.c_str(), str.size());
    return s;
}


inline ISocket & operator >> (ISocket & s, std::string & str)
{
    SocketStreamType type;
    s >> type;

    if (type != e_socketStreamType_string)
        throw std::logic_error("ERROR: ...");

    size_t stringSize;
    s >> stringSize;

    char * strBuf = new char[stringSize + 1];
    s.recv(strBuf, stringSize);

    strBuf[stringSize] = '\0';
    str = stdplus::to_string(strBuf);
    delete[] strBuf;
    return s;
}

const int STREAM_BUFF_SIZE = 1024;

inline ISocket & operator<<(ISocket & s, const std::ifstream & in_ifs)
{

    s << e_socketStreamType_file;

    long long numberBytes = 0;


    std::istream & ifs = const_cast<std::ifstream &>(in_ifs);
    ifs.seekg(0, std::ios::end);
    const long long fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    s << fileSize;

    char * sendDataBuffer = new char[STREAM_BUFF_SIZE];

    while (numberBytes != fileSize)
    {
        long long curBuffSize = 0;
        curBuffSize = fileSize - numberBytes;
        if (curBuffSize > STREAM_BUFF_SIZE)
            curBuffSize = STREAM_BUFF_SIZE;

        ifs.read(sendDataBuffer, curBuffSize);
        long long curSend = s.send(sendDataBuffer, curBuffSize);
        numberBytes += curSend;
    }
    delete[] sendDataBuffer;
    return s;
}

inline ISocket & operator >> (ISocket & s, std::ofstream & ofs)
{

    SocketStreamType type;
    s >> type;

    if (type != e_socketStreamType_file)
        throw std::logic_error("ERROR: ...");



    long long numberBytes = 0;

    long long fileSize = 0;
    s >> fileSize;

    char * dataBuff = new char[STREAM_BUFF_SIZE];

    while (numberBytes != fileSize)
    {
        long long curBuffSize = 0;
        curBuffSize = fileSize - numberBytes;
        if (curBuffSize > STREAM_BUFF_SIZE)
            curBuffSize = STREAM_BUFF_SIZE;

        long long curSend = s.recv(dataBuff, curBuffSize);
        ofs.write(dataBuff, curBuffSize);
        numberBytes += curSend;
    }
    delete[] dataBuff;
    return s;
}




inline ISocket & operator<<(ISocket & s, const UserData & usData)
{
    s << e_socketStreamType_userData;
    s << usData.m_id;
    s << usData.m_name;
    s << usData.m_status;
    return s;
}

inline ISocket & operator >> (ISocket & s, UserData & usData)
{
    SocketStreamType type;
    s >> type;

    if (type != e_socketStreamType_userData)
        throw std::logic_error("ERROR: ...");

    s >> usData.m_id;
    s >> usData.m_name;
    s >> usData.m_status;

    return s;
}




inline ISocket & operator<<(ISocket & s, const MsgData & msg)
{
    s << e_socketStreamType_msg;
    s << msg.m_from;
    s << msg.m_to;
    s << msg.m_msg;
    return s;
}

inline ISocket & operator >> (ISocket & s, MsgData & msg)
{
    SocketStreamType type;
    s >> type;

    if (type != e_socketStreamType_msg)
        throw std::logic_error("ERROR: ...");

    s >> msg.m_from;
    s >> msg.m_to;
    s >> msg.m_msg;

    return s;
}



inline ISocket & operator<<(ISocket & s, const User & user)
{
    s << e_socketStreamType_user;
    s << user.m_userData.m_name;
    s << user.m_userData.m_id;
    s << user.m_userData.m_status;
    return s;
}

inline ISocket & operator >> (ISocket & s, User & user)
{
    SocketStreamType type;
    s >> type;

    if (type != e_socketStreamType_user)
        throw std::logic_error("ERROR: ...");

    s >> user.m_userData.m_name;
    s >> user.m_userData.m_id;
    s >> user.m_userData.m_status;
    return s;
}






template<typename T>
inline ISocket & operator<<(ISocket & s, const std::vector<T> & d)
{
    s << e_socketStreamType_vector;
    size_t numElements = d.size();
    s << numElements;

    for (size_t i = 0; i < numElements; ++i)
    {
        const T & element = d.at(i);
        s << element;
    }
    return s;
}

template<typename T>
inline ISocket & operator >> (ISocket & s, std::vector<T> & pData)
{
    SocketStreamType type;
    s >> type;

    if (type != e_socketStreamType_vector)
        throw std::logic_error("ERROR: ... Invalid socketStream_type_vector");

    size_t numElements;
    s >> numElements;

    for (size_t i = 0; i < numElements; ++i)
    {
        T recieveElement;
        s >> recieveElement;
        pData.push_back(recieveElement);
    }
    return s;
}


template<typename T>
inline ISocket & operator<<(ISocket & s, const std::list<T> & d)
{
    s << e_socketStreamType_list;
    size_t numElements = d.size();
    s << numElements;

    for (auto & element : d)
    {
        s << element;
    }

    return s;
}

template<typename T>
inline ISocket & operator >> (ISocket & s, std::list<T> & pData)
{
    SocketStreamType type;
    s >> type;

    if (type != e_socketStreamType_list)
        throw std::logic_error("ERROR: ... Invalid socketStream_type_list");

    size_t numElements;
    s >> numElements;

    for (size_t i = 0; i < numElements; ++i)
    {
        T recieveElement;
        s >> recieveElement;
        pData.push_back(recieveElement);
    }
    return s;
}


inline ISocket & operator<<(ISocket & s, const NetworkMap & networkMap)
{
    s << e_socketStreamType_recieveClientData;
    s << networkMap.m_clientList;
    s << networkMap.m_msgs;
    return s;
}

inline ISocket & operator >> (ISocket & s, NetworkMap & networkMap)
{
    SocketStreamType type;
    s >> type;
    if (type != e_socketStreamType_recieveClientData)
        throw std::logic_error("ERROR: ... Invalid socketStream_type");

    s >> networkMap.m_clientList;
    s >> networkMap.m_msgs;
    return s;
}