#pragma once
#include <string>
#include <vector>
#include <tinyxml2.h>

using TiXmlElement = tinyxml2::XMLElement; // TODO - remove it

class GameObject;

class StateParser
{
public:
    bool parseState(const char*               stateFile, const std::string&       stateID,
                    std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs);
private:
    void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects);
    void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
};
