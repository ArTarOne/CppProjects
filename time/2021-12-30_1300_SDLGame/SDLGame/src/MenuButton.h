#pragma once
#include "GameObjectFactory.h"
#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton();
    void draw() override;
    void update() override;
    void clean() override;
    void load(const LoaderParams* pParams) override;
    void setCallback(void (*callback)());
    int  getCallbackID() const;

private:
    enum ButtonStateEnum
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*m_callback)();
    bool   m_bReleased;
    int    m_callbackID;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* createGameObject() const override;
};
