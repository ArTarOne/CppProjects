#pragma once



class NetworkMap
{
public:
    NetworkMap();
    ~NetworkMap();

    std::vector<UserData> m_clientList;
    MsgContainer m_msgs;

private:

};

