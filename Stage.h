#pragma once
#include <functional>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>

#include "GameObject.h"

struct CompareGameObjectDepth : std::binary_function<GameObject*, GameObject*, bool> {
  bool operator()(GameObject *lhs, GameObject *rhs) const {
    return lhs->getDepth() > rhs->getDepth();
  }
};
typedef std::priority_queue<GameObject, std::deque<GameObject *>, CompareGameObjectDepth> ObjectDepthPriorityQueue;

class RenderQueue {
public:
  RenderQueue() {}
  RenderQueue(int depth) {
    m_depth = depth;

    std::cout << "new RenderQueue...\n";
  }
  ~RenderQueue() {}

  void update(sf::Time delta) {}

  void draw(sf::RenderWindow &window) {
    for(auto &o : m_objectQueue) {
      if(o->isDestroyed()) {
        auto i = &o - &m_objectQueue[0];
        m_objectQueue.erase(m_objectQueue.begin() + i);
      }
      o->update(sf::seconds(1.f / GSGetMaxFPS)); // FIX THIS
      window.draw(*o);
    }
  }

  void addToQueue(GameObject *gameObject) {
    m_objectQueue.push_back(gameObject);
  }

  int getDepth() const { return m_depth; }
  void setDepth(int depth) { m_depth = depth; }
private:
  int m_depth = 0;

  std::vector<GameObject *> m_objectQueue;
};

struct CompareRenderQueueDepth : std::binary_function<RenderQueue*, RenderQueue*, bool> {
  bool operator()(RenderQueue *lhs, RenderQueue *rhs) const {
    return lhs->getDepth() > rhs->getDepth();
  }
};
typedef std::priority_queue<RenderQueue, std::deque<RenderQueue *>, CompareRenderQueueDepth> RenderPriorityQueue;

class Stage {
public:
  Stage() { }
  virtual ~Stage() {}

  void draw(sf::RenderWindow &window) {
    RenderPriorityQueue queue(m_renderQueues);
    while(!queue.empty()) {
      queue.top()->draw(window);
      queue.pop();
    }
  }

  void addRenderQueue(RenderQueue *renderQueue) {
    m_renderQueues.push(renderQueue);
  }

  void addObjectToStage(int depth, GameObject *gameObject) {
    // If there are no render queues make one!
    if(m_renderQueues.empty()) {
      RenderQueue *queue = new RenderQueue(depth);
      queue->addToQueue(gameObject);
      m_renderQueues.push(queue);
      return; // Escape!
    }
    // Add to existing queue..
    RenderPriorityQueue queues(m_renderQueues);
    while(!queues.empty()) {
      if(queues.top()->getDepth() == depth) {
        queues.top()->addToQueue(gameObject);
        return; // Exit because we've found our match.
      } else {
        queues.pop();
      }
    }
    // Or create a new queue at depth.
    RenderQueue *queue = new RenderQueue(depth);
    queue->addToQueue(gameObject);
    m_renderQueues.push(queue);
  }

private:
  RenderPriorityQueue m_renderQueues;
};
