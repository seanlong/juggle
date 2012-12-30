#include "HelloWorldScene.h"
#include "AppMacros.h"
#include <algorithm>
#include <math.h>

USING_NS_CC;
const static int BLOCK_WIDTH = 30;
const static int TEXTURE_WIDTH = 17;

static long millisecondNow()  
{ 
  struct cc_timeval now; 
  CCTime::gettimeofdayCocos2d(&now, NULL); 
  return (now.tv_sec * 1000 + now.tv_usec / 1000); 
} 

Block* Block::create(Box* owner, const CCRect& spriteRect)
{
  Block *pobSprite = new Block(owner);
  if(pobSprite){
    if(!pobSprite->initWithTexture(Box::s_blocksBatchNode->getTexture(), spriteRect))
    //if(!pobSprite->initWithFile("blocks.png", spriteRect))
      return NULL;
    pobSprite->autorelease();
    pobSprite->setAnchorPoint(ccp(0, 0));
    pobSprite->setScale((float)BLOCK_WIDTH/(float)TEXTURE_WIDTH);
    return pobSprite;
  }
  CC_SAFE_DELETE(pobSprite);
  return NULL;
}

void Block::removeFromBox()
{
  m_owner->removeChildBlock(this);
}

void Block::moveDownward(int levels)
{
  CCPoint pos = getPosition();
  setPosition(ccp(pos.x, pos.y - levels * BLOCK_WIDTH));
}

Box::BlocksStatesMap Box::s_blocksStatesMap;
CCSpriteBatchNode* Box::s_blocksBatchNode;
Box::BlockSpriteRectMap Box::s_blockSpriteRectMap;

void Box::initBlocksBatchNode(HelloWorld* layer)
{
  s_blocksBatchNode = CCSpriteBatchNode::create("blocks.png");
  layer->addChild(s_blocksBatchNode, 1);
  for(int i = 0; i < END_TYPE; i++){
    s_blockSpriteRectMap.insert(std::make_pair(static_cast<BoxTypes>(i), 
      CCRectMake(i * (TEXTURE_WIDTH + 1), 1, TEXTURE_WIDTH, TEXTURE_WIDTH)));
  }
}

void Box::initBlocksStatesMap(void)
{
  //ONE
  {
    BlocksStates bss;
    Coord c1[4] = {Coord(-2, 0), Coord(-1, 0), Coord(0, 0), Coord(1, 0)};
    BlocksState bs1(4);
    std::copy(c1, c1 + 4, bs1.begin());
    bss.push_back(bs1);
    Coord c2[4] = {Coord(0, 0), Coord(0, 1), Coord(0, 2), Coord(0, 3)};
    BlocksState bs2(4);
    std::copy(c2, c2 + 4, bs2.begin());
    bss.push_back(bs2);
    s_blocksStatesMap.insert(std::make_pair(ONE, bss));//copy construction use pointer instead?
  }
  //TWO
  {
    BlocksStates bss;
    Coord c1[4] = {Coord(0, 0), Coord(1, 0), Coord(0, 1), Coord(0, 2)};
    BlocksState bs1(4);
    std::copy(c1, c1 + 4, bs1.begin());
    bss.push_back(bs1);
    Coord c2[4] = {Coord(0, 0), Coord(0, 1), Coord(1, 1), Coord(2, 1)};
    BlocksState bs2(4);
    std::copy(c2, c2 + 4, bs2.begin());
    bss.push_back(bs2);
    Coord c3[4] = {Coord(0, 2), Coord(1, 2), Coord(1, 1), Coord(1, 0)};
    BlocksState bs3(4);
    std::copy(c3, c3 + 4, bs3.begin());
    bss.push_back(bs3);
    Coord c4[4] = {Coord(0, 0), Coord(1, 0), Coord(2, 0), Coord(2, 1)};
    BlocksState bs4(4);
    std::copy(c4, c4 + 4, bs4.begin());
    bss.push_back(bs4);
    s_blocksStatesMap.insert(std::make_pair(TWO, bss));//copy construction use pointer instead?
  }
  //THREE
  {
    BlocksStates bss;
    Coord c1[4] = {Coord(1, 0), Coord(2, 0), Coord(2, 1), Coord(2, 2)};
    BlocksState bs1(4);
    std::copy(c1, c1 + 4, bs1.begin());
    bss.push_back(bs1);
    Coord c2[4] = {Coord(0, 0), Coord(1, 0), Coord(2, 0), Coord(0, 1)};
    BlocksState bs2(4);
    std::copy(c2, c2 + 4, bs2.begin());
    bss.push_back(bs2);
    Coord c3[4] = {Coord(0, 0), Coord(0, 1), Coord(0, 2), Coord(1, 2)};
    BlocksState bs3(4);
    std::copy(c3, c3 + 4, bs3.begin());
    bss.push_back(bs3);
    Coord c4[4] = {Coord(0, 1), Coord(1, 1), Coord(2, 1), Coord(2, 0)};
    BlocksState bs4(4);
    std::copy(c4, c4 + 4, bs4.begin());
    bss.push_back(bs4);
    s_blocksStatesMap.insert(std::make_pair(THREE, bss));//copy construction use pointer instead?
  }
  //FOUR
  {
    BlocksStates bss;
    Coord c1[4] = {Coord(0, 1), Coord(1, 0), Coord(1, 1), Coord(2, 0)};
    BlocksState bs1(4);
    std::copy(c1, c1 + 4, bs1.begin());
    bss.push_back(bs1);
    Coord c2[4] = {Coord(0, 0), Coord(0, 1), Coord(1, 1), Coord(1, 2)};
    BlocksState bs2(4);
    std::copy(c2, c2 + 4, bs2.begin());
    bss.push_back(bs2);
    s_blocksStatesMap.insert(std::make_pair(FOUR, bss));//copy construction use pointer instead?
  }
  //FIVE
  {
    BlocksStates bss;
    Coord c1[4] = {Coord(0, 0), Coord(1, 0), Coord(1, 1), Coord(2, 1)};
    BlocksState bs1(4);
    std::copy(c1, c1 + 4, bs1.begin());
    bss.push_back(bs1);
    Coord c2[4] = {Coord(0, 1), Coord(0, 2), Coord(1, 0), Coord(1, 1)};
    BlocksState bs2(4);
    std::copy(c2, c2 + 4, bs2.begin());
    bss.push_back(bs2);
    s_blocksStatesMap.insert(std::make_pair(FIVE, bss));//copy construction use pointer instead?
  }
  //SIX
  {
    BlocksStates bss;
    Coord c1[4] = {Coord(0, 0), Coord(1, 0), Coord(0, 1), Coord(1, 1)};
    BlocksState bs1(4);
    std::copy(c1, c1 + 4, bs1.begin());
    bss.push_back(bs1);
    s_blocksStatesMap.insert(std::make_pair(SIX, bss));//copy construction use pointer instead?
  }
  //SEVEN
  {
    BlocksStates bss;
    Coord c1[4] = {Coord(0, 0), Coord(1, 0), Coord(1, 1), Coord(2, 0)};
    BlocksState bs1(4);
    std::copy(c1, c1 + 4, bs1.begin());
    bss.push_back(bs1);
    Coord c2[4] = {Coord(1, 0), Coord(1, 1), Coord(1, 2), Coord(2, 1)};
    BlocksState bs2(4);
    std::copy(c2, c2 + 4, bs2.begin());
    bss.push_back(bs2);
    Coord c3[4] = {Coord(0, 1), Coord(1, 0), Coord(1, 1), Coord(2, 1)};
    BlocksState bs3(4);
    std::copy(c3, c3 + 4, bs3.begin());
    bss.push_back(bs3);
    Coord c4[4] = {Coord(0, 1), Coord(1, 0), Coord(1, 1), Coord(1, 2)};
    BlocksState bs4(4);
    std::copy(c4, c4 + 4, bs4.begin());
    bss.push_back(bs4);
    s_blocksStatesMap.insert(std::make_pair(SEVEN, bss));//copy construction use pointer instead?
  }
}

Box* Box::createBox(BoxTypes type, HelloWorld* layer)
{
  Box* ret = 0;

  BlockSpriteRectMap::iterator prect;
  prect = s_blockSpriteRectMap.find(type);
  CCAssert(prect != s_blockSpriteRectMap.end(), "error! can't find mapping rect");

  BlocksStatesMap::iterator pbss;
  pbss = s_blocksStatesMap.find(type);
  CCAssert(pbss != s_blocksStatesMap.end(), "error! can't find mapping blocks states");
  ret = new Box(&pbss->second, prect->second, layer);

  return ret;
}

Box* Box::createRandomBox()
{
  return 0;
}

Box::Box(BlocksStates *bss, const CCRect& blockRect, HelloWorld* layer):
  m_states(bss), m_layer(layer), m_stateIdx(0), m_stepInterval(0.4f)
{
  const BlocksState& bs = (*m_states)[0]; 
  int blockNum = bs.size();
  
  for(int i = 0; i < blockNum; i++){
    const Coord& coord = bs[i];
    Block* block = Block::create(this, blockRect);
    CCAssert(block, "error! can't create block object");
    block->setPosition(ccp(coord.x*BLOCK_WIDTH, coord.y*BLOCK_WIDTH));
    m_blocks.push_back(block);
    addChild(block, 1, i);
  }
}

void Box::rotate()
{
  int stateNum = m_states->size();
  int newIdx = (m_stateIdx + 1) % stateNum;
  const BlocksState& bs = (*m_states)[newIdx];
  int blockNum = m_blocks.size();

  bool canRotate = true;
  if(!testBlocksState(bs)){
    canRotate = false;
    int i = 1;
    while(i < blockNum){
      if(testBlocksStateWithCoordinate(bs, Coord(m_coord.x + i, m_coord.y))){
        setCoordinate(Coord(m_coord.x + i, m_coord.y));
        canRotate = true;
        break;
      }
      if(testBlocksStateWithCoordinate(bs, Coord(m_coord.x - i, m_coord.y))){
        setCoordinate(Coord(m_coord.x - i, m_coord.y));
        canRotate = true;
        break;
      }
      i++;
    }
  }
  
  if(!canRotate)
    return;

  m_stateIdx = newIdx;
  for(int i = 0; i < blockNum; i++){
    const Coord& coord = bs[i];
    Block* block = m_blocks[i];
    block->setPosition(ccp(coord.x*BLOCK_WIDTH, coord.y*BLOCK_WIDTH));
  }
}

void Box::removeChildBlock(Block* block)
{
  std::vector<Block*>::iterator it;
  it = std::find(m_blocks.begin(), m_blocks.end(), block);
  
  CCAssert(it != m_blocks.end(), "error! block not in box.");
  m_blocks.erase(it);
  removeChild(block);
  if(m_blocks.empty())
    m_layer->removeChild(this);
}

void Box::accelerateStepSpeed(int multiple)
{
  if(multiple < 1)
    return;

  m_stepInterval = m_stepInterval/multiple;
  unschedule(schedule_selector(Box::step));
  schedule(schedule_selector(Box::step), m_stepInterval);
}

bool Box::testBlocksStateWithCoordinate(const BlocksState& bs, const Coord& coord)
{
  int blockNum = m_blocks.size();

  for(int i = 0; i < blockNum; i++){
    int x = bs[i].x + coord.x;
    int y = bs[i].y + coord.y;
    if(x < 0 || x > HelloWorld::COL_NUM - 1)
      return false;
    if(y < 0)
      return false;
    if(m_layer->getCoordState(x, y))
      return false;
  }

  return true;
}

bool Box::testBlocksState(const BlocksState& bs)
{
  return testBlocksStateWithCoordinate(bs, m_coord);
}

void Box::setCoordinate(const Coord& coord)
{
  m_coord = coord;
  setPosition(ccp(coord.x * BLOCK_WIDTH, coord.y * BLOCK_WIDTH));
}

bool Box::testCoordinate(const Coord& coord)
{
  int blockNum = m_blocks.size();
  BlocksState& bs = (*m_states)[m_stateIdx];

  for(int i = 0; i < blockNum; i++){
    int x = coord.x + bs[i].x;
    int y = coord.y + bs[i].y;
    if(m_layer->getCoordState(x, y))
      return false;
  }

  return true;
}

void Box::step(float dt)
{
  int blockNum = m_blocks.size();
  BlocksState& bs = (*m_states)[m_stateIdx];
  
  for(int i = 0; i < blockNum; i++){
    int x = m_coord.x + bs[i].x;
    int y = m_coord.y + bs[i].y - 1;
    if(m_layer->getCoordState(x, y)){
      unschedule(schedule_selector(Box::step));
      m_layer->updateTilesMap();
      m_layer->testClearLevels();
      m_layer->nextBox();
      return;
    }
  }

  setCoordinate(Coord(m_coord.x, m_coord.y - 1));
}

void HelloWorld::updateTilesMap()
{
  const Box::BlocksState& bs = m_currentBox->getBlocksState();
  Coord coord = m_currentBox->getCoordinate();
  int blockNum = bs.size();

  for(int i = 0; i < blockNum; i++){
    int x = bs[i].x + coord.x;
    int y = bs[i].y + coord.y;
    if(m_tiles[y][x])
      CCLOG("tile already occupied");
    else{
      m_tiles[y][x] = 1;
      m_blocks[y][x] = m_currentBox->getBlock(i);
    }
  }

}

void HelloWorld::testClearLevels()
{
  int r, c;
  std::vector<int> rows;

  for(r = 1; r < ROW_NUM - 1; r++){
    for(c = 1; c < COL_NUM - 1; c++){
      if(!m_tiles[r][c])
        break;
    }
    if(c == COL_NUM - 1)
      rows.push_back(r);
  }

  std::vector<int>::iterator it = rows.begin();
  for(; it != rows.end(); it++){
    for(c = 1; c < COL_NUM - 1; c++){
      Block* block = m_blocks[*it][c];
      CCAssert(block != 0, "error! block == 0");
      block->removeFromBox();
      m_tiles[*it][c] = 0;
      m_blocks[*it][c] = 0;
    }
  }

  if(rows.empty())
    return;

  char numberBuf[16];
  m_totalClearedLevels += rows.size();
  sprintf(numberBuf, "%d", m_totalClearedLevels);
  m_score->setString(numberBuf);//FIXME

  for(r = 1; r < ROW_NUM - 1; r++){
    int moveLevels = 0;
    for(it = rows.begin(); it != rows.end(); it++){
      if(r > *it)
        moveLevels++;
    }
    if(!moveLevels)
      continue;
    for(c = 1; c < COL_NUM -1; c++){
      Block* block = m_blocks[r][c];
      if(!block)
        continue;
      block->moveDownward(moveLevels);
      m_tiles[r][c] = 0;
      m_blocks[r][c] = 0;
      m_tiles[r - moveLevels][c] = 1;
      m_blocks[r - moveLevels][c] = block;
    }
  }
}

void HelloWorld::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
  m_touchBegan = true;
  m_boxMoved = false;
  m_touchBeganTime = millisecondNow();
  m_savedPos = touch->getLocation();
  m_isCurrentBoxAccelerated = false;

  return true;
}

void HelloWorld::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
  if(!m_touchBegan)
    return;

  CCPoint currPos = touch->getLocation();
  int deltaX = (currPos.x - m_savedPos.x) / BLOCK_WIDTH;
  int deltaY = (m_savedPos.y - currPos.y) / BLOCK_WIDTH;

  if(abs(deltaX) >= 1 || deltaY >= 2){
    m_savedPos = currPos;
    Coord coord = m_currentBox->getCoordinate();

    if(abs(deltaX) >= 1){
      Coord newCoord(coord.x + deltaX, coord.y);
      if(!m_currentBox->testCoordinate(newCoord))
        return;
      m_currentBox->setCoordinate(newCoord);
      m_boxMoved = true;
    }
    if(deltaY >= 2){
      m_isCurrentBoxAccelerated = true;
      if(deltaY < 3)
        m_currentBox->accelerateStepSpeed(2);
      else
        m_currentBox->accelerateStepSpeed(4);
    }
  }

}

void HelloWorld::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
  if(!m_touchBegan || m_boxMoved || m_isCurrentBoxAccelerated)
    return;

  m_boxMoved = false;
  m_touchBegan = false;
  long now = millisecondNow();
  long duration = now - m_touchBeganTime;

  if(duration < 160)
    m_currentBox->rotate();
}

void HelloWorld::draw()
{
  CCLayer::draw();
  int b = BLOCK_WIDTH;

  glLineWidth(1);
	ccDrawColor4B(255, 255, 255, 128);
  for(int r = 0; r <= ROW_NUM; r++){
    ccDrawLine(ccp(0, b*r), ccp(COL_NUM*b, b*r));
  }

  for(int c = 0; c <= COL_NUM; c++){
    ccDrawLine(ccp(b*c, 0), ccp(b*c, b*ROW_NUM));
  }

#if 1
  //show tiles setting debugging info 
  glLineWidth(1);
  for(int r = 0; r < ROW_NUM; r++){
    for(int c = 0; c < COL_NUM; c++){
      if(!m_tiles[r][c])
        continue;
      CCPoint rectVertices[] = { 
        ccp(c*b, r*b), 
        ccp((c+1)*b, r*b), 
        ccp((c+1)*b, (r+1)*b), 
        ccp(c*b, (r+1)*b) };
      ccDrawSolidPoly(rectVertices, 4, ccc4f(0.5f, 0, 0, 0.3));
      //ccDrawPoly(rectVertices, 4, true);
    }
  }
#endif

  glLineWidth(1);
	ccDrawColor4B(255,255,255,255);
	ccPointSize(1);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::nextBox()
{
  float random = CCRANDOM_0_1();
  Box* box;
  int type = floor(random * 7);
  box = Box::createBox(static_cast<Box::BoxTypes>(type), this);

  Coord coord(5, 23);
  box->setCoordinate(coord);
  addChild(box, -1);
  //Box::s_blocksBatchNode->addChild(box);
  m_currentBox = box;
  m_isCurrentBoxAccelerated = false;
  
  box->schedule(schedule_selector(Box::step), box->getStepInterval());
}

bool HelloWorld::init()
{
  if ( !CCLayer::init() )
  {
      return false;
  }
  
  CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
  CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
  
  //close menu
  CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                      "CloseNormal.png",
                                      "CloseSelected.png",
                                      this,
                                      menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
  CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
  pMenu->setPosition(CCPointZero);
  this->addChild(pMenu, 1);
  
  //score label
  CCLabelTTF* pScoreStr = CCLabelTTF::create("score:", "Marker Felt", 23);
  pScoreStr->setPosition(ccp(380, 770));
  this->addChild(pScoreStr, 2);
  m_score = CCLabelTTF::create("0", "Marker Felt", 20);
  m_score->setPosition(ccp(440, 770));
  this->addChild(m_score, 2);
  
  memset(m_blocks, 0, sizeof(m_blocks));
  memset(m_tiles, 0, sizeof(m_tiles));
  m_touchBegan = false;
  m_totalClearedLevels = 0;

  for(int i = 0; i < COL_NUM; i++)
    m_tiles[0][i] = 1;

  for(int i = 0; i < ROW_NUM; i++){
    m_tiles[i][0] = 1;
    m_tiles[i][COL_NUM - 1] = 1;
  }

  Box::initBlocksStatesMap();
  Box::initBlocksBatchNode(this);
  nextBox();
  
  this->setTouchEnabled(true);
  return true;
}

CCScene* HelloWorld::scene()
{
  CCScene *scene = CCScene::create();
  HelloWorld *layer = HelloWorld::create();
  scene->addChild(layer);
  
  return scene;
}

