#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Node;
using NodePointer = std::shared_ptr<Node>;
class Graph;
using GraphPointer = std::shared_ptr<Graph>;
using GraphWeakPointer = std::weak_ptr<Graph>;

class Object {
 public:
  using PointerType = std::shared_ptr<Object>;
  Object(const std::string& name) : name_(name) {}
  ~Object() {
    std::cout << "Object " << name_ << " has been destroied." << std::endl;
  }

 private:
  std::string name_;
};

class Node {
 public:
  using Pointer = std::shared_ptr<Node>;

 public:
  Node(const std::string& name) : name_(name) {}
  ~Node() {
    std::cout << "Node " << name_ << " has been destroied." << std::endl;
  }

  void setGraph(GraphPointer belongs_to) {
    belongs_to_ = GraphWeakPointer(belongs_to);
  }

 private:
  GraphWeakPointer belongs_to_;
  std::string name_;
};

class Graph : public std::enable_shared_from_this<Graph> {
 public:
  Graph() = default;
  ~Graph() { std::cout << "Graph has been destroied." << std::endl; }

  void push_back(NodePointer node) {
    node->setGraph(shared_from_this());
    nodes_.push_back(node);
  }

 private:
  std::vector<NodePointer> nodes_;
};

int main() {
  NodePointer obj_ptr1 = std::make_shared<Node>("DingZhen");
  {
    GraphPointer graph = std::make_shared<Graph>();
    graph->push_back(std::move(obj_ptr1));
  }
  if (obj_ptr1) {
    std::cout << "That's impossible, DingZhen should be destoried!"
              << std::endl;
  }
  std::cout << "Hello World!" << std::endl;
  return 0;
}
