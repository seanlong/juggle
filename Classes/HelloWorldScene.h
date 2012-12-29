#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <map>

using namespace cocos2d;
//class CCLabelTTF;
class Box;
class Block;

class HelloWorld : public CCLayer
{
public:
  static cocos2d::CCScene* scene();
  const static int ROW_NUM = 25;
  const static int COL_NUM = 16;

  virtual bool init();
  virtual void draw();
  virtual void registerWithTouchDispatcher();
  virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
  virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
  virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

  void menuCloseCallback(CCObject* pSender);
  void nextBox(void);
  int getCoordState(int x, int y) { return m_tiles[y][x]; }
  void setCoordState(int x, int y) { m_tiles[y][x] = 1; }
  void clearCoordState(int x, int y) { m_tiles[y][x] = 0; }
  Block* getBlockAtCoord(int x, int y) { return m_blocks[y][x]; }

  void updateTilesMap();
  void testClearLevels();

  CREATE_FUNC(HelloWorld);

private:
  int m_tiles[ROW_NUM][COL_NUM];
  Block* m_blocks[ROW_NUM][COL_NUM];

  Box* m_currentBox;
  bool m_isCurrentBoxAccelerated;
  bool m_touchBegan;
  long m_touchBeganTime;
  bool m_boxMoved;
  CCPoint m_savedPos;
  int m_totalClearedLevels;

  CCLabelTTF* m_score;
};

struct Coord {
  Coord(int ix = 0, int iy = 0) : 
    x(ix), y(iy)
  {};

  int x;
  int y;
};

class Block : public CCSprite
{
  public:
    static Block* create(Box* owner, const CCRect& spriteRect);
    void moveDownward(int levels);
    Block(Box* owner):
      m_owner(owner)
      {}
    void removeFromBox(void);

  private:
    Box* m_owner;
};

class Box : public CCNode
{
  public:
    enum BoxTypes {
      ONE = 0, //|
      TWO, //|_
      THREE, // _|
      FOUR, // -_ 
      FIVE, // _-
      SIX, // |||
      SEVEN, // \|/
      END_TYPE,
    };

    typedef std::vector<Coord > BlocksState;
    typedef std::vector<BlocksState > BlocksStates;
    typedef std::map<BoxTypes, BlocksStates > BlocksStatesMap;
    typedef std::map<BoxTypes, CCRect > BlockSpriteRectMap;

    static CCSpriteBatchNode* s_blocksBatchNode;
    static BlocksStatesMap s_blocksStatesMap;
    static BlockSpriteRectMap s_blockSpriteRectMap;
    static Box* createRandomBox();
    static Box* createBox(BoxTypes type, HelloWorld* layer);
    static void initBlocksStatesMap(void);
    static void initBlocksBatchNode(HelloWorld* layer);

    Box(BlocksStates* bs, const CCRect& blockRect, HelloWorld* layer);

    const BlocksState& getBlocksState(void) { return (*m_states)[m_stateIdx]; }
    Block* getBlock(int idx) { return m_blocks[idx]; }
    void removeChildBlock(Block* block);
    float getStepInterval() { return m_stepInterval; }
    void accelerateStepSpeed(int multiple);
    bool testBlocksStateWithCoordinate(const BlocksState& bs, const Coord& coord);
    bool testBlocksState(const BlocksState& bs);

    Coord getCoordinate() { return m_coord; }
    void setCoordinate(const Coord& coord);
    bool testCoordinate(const Coord& coord);
    void rotate();
    void step(float dt);
  
  private:
    std::vector<Block*> m_blocks;
    BlocksStates* m_states;
    int m_stateIdx;
    Coord m_coord;
    float m_stepInterval;
    HelloWorld* m_layer;
};

#endif // __HELLOWORLD_SCENE_H__
