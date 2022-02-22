#pragma once
#include <string>
#include <vector>
#include <tinyxml2.h>

class GameObject;

/**
 * \brief Read states.xml and return true if success
 */
class StateParser
{
public:
    /**
     * \brief Read states.xml and return true if success
     * \param stateFile [in] states.xml
     * \param stateID [in] id for search in xml, like MENU, PAUSE or GAMEOVER
     * \param pObjects [out] push back new GameObject's
     * \param pTextureIDs [out] push back new TextureIDs
     * \return false in case of error (ASSERTION in Debug)
     */
    bool parseState(const char*               stateFile, const std::string&       stateID,
                    std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs);
private:
    void parseObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*>* pObjects);
    void parseTextures(tinyxml2::XMLElement* pStateRoot, std::vector<std::string>* pTextureIDs);
};
