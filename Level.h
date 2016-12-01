#pragma once
#include <vector>

#include "GameObject.h"

class RenderSubQueue {
public:
  RenderSubQueue(int depth) {
    m_depth = depth;
  }
  virtual ~RenderSubQueue() {}

  int  getDepth()          {  return m_depth; }
  void setDepth(int depth) { m_depth = depth; }

  void draw(sf::RenderWindow &window) {
    sortQueue();
    for(auto &o : m_renderQueue) {
      window.draw(*o);
    }
  }

  void addToQueue(GameObject &gameObject) {
    m_renderQueue.push_back(&gameObject);
  }

private:
  int m_depth;
  std::vector<GameObject *> m_renderQueue;

  void sortQueue() {
    sort(m_renderQueue.begin(), m_renderQueue.end(),
        [](GameObject *a, GameObject *b) -> bool
    {
        return a->getDepth() < b->getDepth();
    });
  }
};

class Level {
public:
  Level() {}
  virtual ~Level() {}

  void draw(sf::RenderWindow &window) {
    for(auto &q : m_subQueues) {
      q->draw(window);
    }
  }

private:
  std::vector<RenderSubQueue *> m_subQueues;

  void sortQueue() {
    sort(m_subQueues.begin(), m_subQueues.end(),
        [](RenderSubQueue *a, RenderSubQueue *b) -> bool
    {
        return a->getDepth() < b->getDepth();
    });
  }
};
