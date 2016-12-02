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
typedef std::priority_queue<GameObject, std::vector<GameObject *>, CompareGameObjectDepth> ObjectDepthPriorityQueue;

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
    ObjectDepthPriorityQueue queue(m_objectQueue);
    while(!queue.empty()) {
      // TODO: Remove this bullshit.
      queue.top()->update(sf::seconds(1.f / GSGetMaxFPS));
      // END BULLSHIT
      window.draw(*queue.top());
      queue.pop();
    }
  }

  void addToQueue(GameObject *gameObject) {
    m_objectQueue.push(gameObject);
  }

  int getDepth() const { return m_depth; }
  void setDepth(int depth) { m_depth = depth; }
private:
  int m_depth = 0;

  ObjectDepthPriorityQueue m_objectQueue;
};

struct CompareRenderQueueDepth : std::binary_function<RenderQueue*, RenderQueue*, bool> {
  bool operator()(RenderQueue *lhs, RenderQueue *rhs) const {
    return lhs->getDepth() > rhs->getDepth();
  }
};
typedef std::priority_queue<RenderQueue, std::vector<RenderQueue *>, CompareRenderQueueDepth> RenderPriorityQueue;

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
      return;
    }
    // Add to existing queue..
    RenderPriorityQueue queues(m_renderQueues);
    while(!queues.empty()) {
      if(queues.top()->getDepth() == depth) {
        queues.top()->addToQueue(gameObject);
        return;
      } else {
        queues.pop();
      }
    }
    // Or create a new queue at depth
    RenderQueue *queue = new RenderQueue(depth);
    queue->addToQueue(gameObject);
    m_renderQueues.push(queue);
  }

private:
  RenderPriorityQueue m_renderQueues;
};
