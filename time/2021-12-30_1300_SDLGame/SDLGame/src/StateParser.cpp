#include <iostream>

#include "StateParser.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Utils.h"

bool StateParser::parseState(const char*               stateFile,
                             const std::string&        stateID,
                             std::vector<GameObject*>* pObjects,
                             std::vector<std::string>* pTextureIDs)
{
    tinyxml2::XMLDocument xmlDoc;
    if(xmlDoc.LoadFile(utils::deepSearch(stateFile).c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Error loading xml file " << stateFile << ". Error: " << xmlDoc.ErrorID() << "\n";
        _ASSERT(false);
        return false;
    }

    // found states.xml:<STATES><state-id-name>
    tinyxml2::XMLElement* pRoot      = xmlDoc.RootElement();
    tinyxml2::XMLElement* pStateRoot = nullptr;
    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == stateID)
        {
            pStateRoot = e;
        }
    }
    if(!pStateRoot)
    {
        std::cerr << "xml: state " << stateID << " not found\n";
        _ASSERT(false);
        return false;
    }

    // textures
    tinyxml2::XMLElement* pTextureRoot = nullptr;
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }
    if(!pTextureRoot)
    {
        std::cerr << "xml: element TEXTURES not found\n";
        _ASSERT(false);
        return false;
    }
    parseTextures(pTextureRoot, pTextureIDs);

    // objects
    tinyxml2::XMLElement* pObjectRoot = nullptr;
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("OBJECTS"))
        {
            pObjectRoot = e;
        }
    }
    if(!pObjectRoot)
    {
        std::cerr << "xml: element OBJECTS not found\n";
        _ASSERT(false);
        return false;
    }
    parseObjects(pObjectRoot, pObjects);

    return true;
}

/**
 * \brief load states from states.xml to container
 * \param pStateRoot [in] states.xml:<STATES><state-name><OBJECTS>
 * \param pObjects [out] add objects to this container
 */
void StateParser::parseObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*>* pObjects)
{
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        const int         x           = e->IntAttribute("x");
        const int         y           = e->IntAttribute("y");
        const int         width       = e->IntAttribute("width");
        const int         height      = e->IntAttribute("height");
        const int         numFrames   = e->IntAttribute("numFrames");
        const int         callbackID  = e->IntAttribute("callbackID");
        const int         animSpeed   = e->IntAttribute("animSpeed");
        const std::string textureID   = e->Attribute("textureID");
        GameObject*       pGameObject = TheGameObjectFactory::instance()->create(e->Attribute("type"));
        pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
        pObjects->push_back(pGameObject);
    }
}

/**
 * \brief load textures from states.xml to TheTextureManager
 * \param pStateRoot [in] states.xml:<STATES><state-name><TEXTURES>
 * \param pTextureIDs [out] add ID's to this container
 */
void StateParser::parseTextures(tinyxml2::XMLElement* pStateRoot, std::vector<std::string>* pTextureIDs)
{
    for(tinyxml2::XMLElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute       = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute);
        TheTextureManager::instance()->load(filenameAttribute, idAttribute, TheGame::instance()->getRenderer());
    }
}
