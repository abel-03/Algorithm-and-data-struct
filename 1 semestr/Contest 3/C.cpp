#include <iostream>
#include <string>

class Node {
 public:

  Node(std::string& first, std::string& second) : racer_(first), car_(second) {}
  void Clear();
  Node* Insert(Node* node, std::string& str1, std::string& str2);
  static void Print(Node* node, std::string& request, int request_num);

 private:
  std::string racer_;
  std::string car_;
  Node* left_ = nullptr;
  Node* right_ = nullptr;

  Node* ToLeft();
  Node* ToRight();
  Node* ZigZig(std::string& request);
  Node* ZigZag(std::string& request);
  Node* ZagZag(std::string& request);
  void SwapLeft(Node* root);
  void SwapRight(Node* root);
  Node* Splay(Node* node, std::string& request);
};

void Node::Print(Node* node, std::string& request, int request_num) {
    for(int i = 0;i < request_num; ++i) {
    std::cin >> request;
    node = node->Splay(node, request);
    std::cout << node->car_ << "\n";
  }
}

void Node::Clear() {
  if (this->left_ != nullptr) {
    this->left_->Clear();
  }
  if (this->right_ != nullptr) {
    this->right_->Clear();
  }
  delete this;
}

Node* Node::ToRight() {
  Node* tmp = this->left_;
  this->left_ = tmp->right_;
  tmp->right_ = this;
  return tmp;
}

Node* Node::ToLeft() {
  Node* tmp = this->right_;
  this->right_ = tmp->left_;
  tmp->left_ = this;
  return tmp;
}

Node* Node::ZigZig(std::string& request) {
  this->left_->left_ = Splay(this->left_->left_, request);
  return this->ToRight();
}

Node* Node::ZagZag(std::string& request) {
  this->right_->right_ = Splay(this->right_->right_, request);
  return this->ToLeft();
}

Node* Node::ZigZag(std::string& request) {
  this->left_->right_ = Splay(this->left_->right_, request);
  return nullptr != this->left_->right_ ? this->left_->ToLeft() : this;
}

Node* Node::Splay(Node* node, std::string& request) {
  if (nullptr == node || node->racer_ == request) {
    return node;
  }
  if (request < node->racer_) {
    if (nullptr == node->left_) {
      return node;
    }
    if (request < node->left_->racer_) {
      node->left_->left_ = Splay(node->left_->left_, request);
      node = node->ZigZig(request);
    } else if (request > node->left_->racer_) {
      if (nullptr != node->left_->right_) {
        node->left_ = node->ZigZag(request);
      }
    }
    return nullptr == node->left_ ? node : node->ToRight();
  }
  if (nullptr == node->right_) {
    return node;
  }
  if (request < node->right_->racer_) {
    node->right_->left_ = Splay(node->right_->left_, request);
    if (nullptr != node->right_->left_) {
      node->right_ = node->right_->ToRight();
    }
  } else if (request > node->right_->racer_) {
    node = node->ZagZag(request);
  }
  return nullptr == node->right_ ? node : node->ToLeft();
}

Node* Node::Insert(Node* node, std::string& str1, std::string& str2) {
  if (nullptr == node) {
    return new Node(str1, str2);
  }
  node = Splay(node, str1);
  if (str1 == node->racer_) {
    return node;
  }
  Node* tmp = new Node(str1, str2);
  str1 < node->racer_ ? tmp->SwapLeft(node) : tmp->SwapRight(node);
  return tmp;
}

void Node::SwapLeft(Node* root) {
  this->right_ = root;
  this->left_ = root->left_;
  root->left_ = nullptr;
}

void Node::SwapRight(Node* root) {
  this->left_ = root;
  this->right_ = root->right_;
  root->right_ = nullptr;
}

int main() {
  int car_num = 0;
  int request_num = 0;
  std::string racer;
  std::string car;
  std::string request;
  std::cin >> car_num;
  std::cin >> racer >> car;
  Node* root = new Node(racer, car);
  root = root->Insert(root, car, racer);
  for(int i = 0; i < car_num; ++i) {
    std::cin >> racer >> car;
    root = root->Insert(root, racer, car);
    root = root->Insert(root, car, racer);
  }
  root->Print(root, request, request_num);
  std::cin >> request_num;
  root->Clear();
  return 0;
}

