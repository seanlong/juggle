#include "MenuLayerMainMenu.h"

#include "HelloWorldScene.h"

//------------------------------------------------------------------
//
// MenuLayerMainMenu
//
//------------------------------------------------------------------
MenuLayerMainMenu::MenuLayerMainMenu()
{

}
bool MenuLayerMainMenu::init()
{
  if ( !CCLayer::init() )
  {
      return false;
  }
    setTouchEnabled(true);
    setTouchPriority(kCCMenuHandlerPriority + 1);
    setTouchMode(kCCTouchesOneByOne);



  
    
    // simple Item
    CCMenuItemFont *item1 = CCMenuItemFont::create("simple", this, menu_selector(MenuLayerMainMenu::menuCallbackStartGame) );
    

    // hard Item
    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont *item2 = CCMenuItemFont::create("hard", this, menu_selector(MenuLayerMainMenu::menuCallbackStartGame2));
    
    // tough Item
    CCMenuItemFont *item3 = CCMenuItemFont::create("tough", this, menu_selector(MenuLayerMainMenu::menuCallbackStartGame));

    // exit Item
    CCMenuItemFont* item4 = CCMenuItemFont::create("Quit", this, menu_selector(MenuLayerMainMenu::onQuit));
    
     CCMenu* menu = CCMenu::create( item1, item2, item3, item4, NULL);
    menu->alignItemsVertically();
    
    
    // elastic effect
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    addChild(menu);
    menu->setPosition(ccp(s.width/2, s.height/2));
	return true;
}

bool MenuLayerMainMenu::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
    return true;
}

void MenuLayerMainMenu::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
}

void MenuLayerMainMenu::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
}

void MenuLayerMainMenu::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
}

MenuLayerMainMenu::~MenuLayerMainMenu()
{
}

void MenuLayerMainMenu::menuCallbackStartGame2(CCObject* sender)
{
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
 CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::transitionWithDuration(1.2f,pScene));

}

void MenuLayerMainMenu::menuCallbackStartGame(CCObject* sender)
{
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::transitionWithDuration(1.2f, pScene));

}

void MenuLayerMainMenu::allowTouches(float dt)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->setPriority(kCCMenuHandlerPriority+1, this);
    unscheduleAllSelectors();
    CCLog("TOUCHES ALLOWED AGAIN");
}



void MenuLayerMainMenu::onQuit(CCObject* sender)
{



   CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

CCScene* MenuLayerMainMenu::scene()
{
  CCScene *scene = CCScene::create();
  MenuLayerMainMenu *layer = MenuLayerMainMenu::create();
  scene->addChild(layer);
  return scene;
}