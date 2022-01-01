CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(Chat)

MESSAGE("*****************************************************************")
MESSAGE($ENV{STD_PLUS_DIR})
MESSAGE("*****************************************************************")

INCLUDE_DIRECTORIES(
    $ENV{STD_PLUS_DIR}/include
    src
    )

ADD_EXECUTABLE(Server 
    $ENV{STD_PLUS_DIR}/src/OopSocket/SocketAddress.cpp
    $ENV{STD_PLUS_DIR}/src/OopSocket/SocketUtil.cpp
    $ENV{STD_PLUS_DIR}/src/OopSocket/TCPSocket.cpp
    $ENV{STD_PLUS_DIR}/src/OopSocket/UDPSocket.cpp    
    
    src/Client/NetworkMap.h
    src/Client/NetworkMap.cpp
    src/RealSocket/RealSocket.h
    src/RealSocket/RealSocket.cpp
    src/RealSocket/RealSocketFactory.h
    src/RealSocket/RealSocketFactory.cpp
    src/User/User.h
    src/User/User.cpp
    
    src/Server/Server.h
    src/Server/Server.cpp
    src/ServerMain.cpp
    )


ADD_EXECUTABLE(Client 
    $ENV{STD_PLUS_DIR}/src/OopSocket/SocketAddress.cpp
    $ENV{STD_PLUS_DIR}/src/OopSocket/SocketUtil.cpp
    $ENV{STD_PLUS_DIR}/src/OopSocket/TCPSocket.cpp
    $ENV{STD_PLUS_DIR}/src/OopSocket/UDPSocket.cpp    
    
    src/Client/NetworkMap.h
    src/Client/NetworkMap.cpp
    src/RealSocket/RealSocket.h
    src/RealSocket/RealSocket.cpp
    src/RealSocket/RealSocketFactory.h
    src/RealSocket/RealSocketFactory.cpp
    src/User/User.h
    src/User/User.cpp
    
    src/Client/ClientCore.h   
    src/Client/ClientCore.cpp    
    src/ClientMain.cpp	
    )


