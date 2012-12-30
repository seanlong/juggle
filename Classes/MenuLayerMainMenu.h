#ifndef __SETTINGS_MENU_H__
#define __SETTINGS_MENU_H__ 1
#include "cocos2d.h"

using namespace cocos2d;

class MenuLayerMainMenu : public CCLayer
{


public:
	static cocos2d::CCScene* scene();
    MenuLayerMainMenu(void);
    ~MenuLayerMainMenu();

public:
	virtual bool init();
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent * pEvent);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent * pEvent);

    void allowTouches(float dt);
    void menuCallbackStartGame(CCObject* pSender);
	void menuCallbackStartGame2(CCObject* pSender);
    void onQuit(CCObject* pSender);
	CREATE_FUNC(MenuLayerMainMenu);
};

#endif