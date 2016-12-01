#pragma once
#include <vector>

#include "GameObject.h"

class RenderSubQueue {
public:
  RenderSubQueue(int depth) {
    m_depth = depth;
  }
  virtual ~RenderSubQueue() {
    for(auto &o : m_renderQueue) {
      delete o;
    }
  }

  int  getDepth()          {  return m_depth; }
  void setDepth(int depth) { m_depth = depth; }
  bool empty() { return m_renderQueue.empty(); }

  void update(sf::Time delta) {
    for(auto &o : m_renderQueue) {
      if(o->isDestroyed()) {
        m_renderQueue.erase(std::remove(m_renderQueue.begin(),
                                        m_renderQueue.end(),
                                        o), m_renderQueue.end());
      } else {
        // Update at constant rate FPS.
        o->update(delta);
      }
    }
  }

  void draw(sf::RenderWindow &window) {
    sortQueue();
    for(auto &o : m_renderQueue) {
      window.draw(*o);
    }
  }

  void addToQueue(GameObject *gameObject) {
    m_renderQueue.push_back(gameObject);
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
  virtual ~Level() {
    for(auto &q : m_subQueues) {
      delete q;
    }
  }

  void update(sf::Time delta) {
    for(auto &q : m_subQueues) {
      q->update(delta);
    }
  }

  void draw(sf::RenderWindow &window) {
    //if(m_timeSinceStart.getElapsedTime().asMilliseconds() % 2000 == 0) preenQueue();
    //sortQueue();
    for(auto &q : m_subQueues) {
      //std::cout << "SubQueue at depth " << q->getDepth() << std::endl;
      q->draw(window);
    }
  }

  void addToQueue(RenderSubQueue *renderSubQueue) {
    m_subQueues.push_back(renderSubQueue);
    sortQueue();
  }
  void addToQueue(int depth, GameObject *gameObject) {
    if(m_subQueues.empty()) {
      m_subQueues.push_back(new RenderSubQueue(depth));
      m_subQueues.back()->addToQueue(gameObject);
      //std::cout << "Adding new sub queue..." << std::endl;
    } else {
      auto foundQueue = std::find_if(m_subQueues.begin(), m_subQueues.end(),
                                    [&depth](RenderSubQueue *q)
                                    {
                                      return q->getDepth() == depth;
                                    });
      if(foundQueue != m_subQueues.end()) {
        //std::cout << &gameObject << std::endl;
        (*foundQueue)->addToQueue(gameObject);
      } else {
        m_subQueues.push_back(new RenderSubQueue(depth));
        m_subQueues.back()->addToQueue(gameObject);
        //std::cout << "Adding a new sub queue..." << std::endl;
      }
    }
    sortQueue();
  }

private:
  std::vector<RenderSubQueue *> m_subQueues;
  sf::Clock m_timeSinceStart;

  void sortQueue() {
    sort(m_subQueues.begin(), m_subQueues.end(),
        [](RenderSubQueue *a, RenderSubQueue *b) -> bool
    {
        return a->getDepth() < b->getDepth();
    });
  }

  void preenQueue() {
    m_subQueues.erase(
      std::remove_if(m_subQueues.begin(), m_subQueues.end(),
      [](RenderSubQueue *a) -> bool {
        return a->empty();
      }),
      m_subQueues.end()
    );
  }
};
