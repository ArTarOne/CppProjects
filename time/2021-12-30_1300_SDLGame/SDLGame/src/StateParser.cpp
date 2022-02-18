#include <iostream>

#include "StateParser.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Utils.h"

bool StateParser::parseState(const char*               stateFile, const std::string& stateID,
                             std::vector<GameObject*>* pObjects,
                             std::vector<std::string>* pTextureIDs)
{
    tinyxml2::XMLDocument xmlDoc;
    if(xmlDoc.LoadFile(utils::deepSearch(stateFile).c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Error loading xml file " << stateFile << ". Error: " << xmlDoc.ErrorID() <<
            "\n";
        return false;
    }

    std::cout << "xml: start parsing state " << stateID << " in file " << stateFile << "\n";

    // xml elements
    tinyxml2::XMLElement* pRoot      = xmlDoc.RootElement();
    tinyxml2::XMLElement* pStateRoot = nullptr;
    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == stateID)
        {
            pStateRoot = e;
        }
    }

    if(!pStateRoot)
    {
        std::cerr << "xml: state " << stateID << " not found\n";
        return false;
    }

    // textures
    tinyxml2::XMLElement* pTextureRoot = nullptr;
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }

    if(!pTextureRoot)
    {
        std::cerr << "xml: element TEXTURES not found\n";
        return false;
    }

    parseTextures(pTextureRoot, pTextureIDs);
    std::cout << "xml: found " << pTextureIDs->size() << " textures\n";

    // objects
    tinyxml2::XMLElement* pObjectRoot = nullptr;
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        if(e->Value() == std::string("OBJECTS"))
        {
            pObjectRoot = e;
        }
    }

    if(!pObjectRoot)
    {
        std::cerr << "xml: element OBJECTS not found\n";
        return false;
    }

    parseObjects(pObjectRoot, pObjects);
    std::cout << "xml: found " << pObjects->size() << " objects\n";

    return true;
}

void StateParser::parseObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*>* pObjects)
{
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        int         x           = e->IntAttribute("x");
        int         y           = e->IntAttribute("y");
        int         width       = e->IntAttribute("width");
        int         height      = e->IntAttribute("height");
        int         numFrames   = e->IntAttribute("numFrames");
        int         callbackID  = e->IntAttribute("callbackID");
        int         animSpeed   = e->IntAttribute("animSpeed");
        std::string textureID   = e->Attribute("textureID");
        GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(new LoaderParams(x,
                                           y,
                                           width,
                                           height,
                                           textureID,
                                           numFrames,
                                           callbackID,
                                           animSpeed));
        pObjects->push_back(pGameObject);
    }
}

void StateParser::parseTextures(tinyxml2::XMLElement*     pStateRoot,
                                std::vector<std::string>* pTextureIDs)
{
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->
        NextSiblingElement())
    {
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute       = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute);
        TheTextureManager::Instance()->load(filenameAttribute,
                                            idAttribute,
                                            TheGame::Instance()->getRenderer());
    }
}
