#include <iostream>
#include <vector>

class Node {
 public:
  int a;
  int b;
  int index;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
  Node(int x, int y, int num) : a(x), b(y), index(num) {}
};

Node* InsertNode(Node* node, int x, int y, int num) {
  if (node == nullptr) {
    node = new Node(x, y, num);
    return node;
  }
  if (node->b < y) {
    Node* new_node = new Node(x, y, num);
    if (node->right != nullptr) {
      node->right->parent = new_node;
    }
    new_node->left = node->right;
    node->right = new_node;
    new_node->parent = node;
    return new_node;
  }
  if (node->parent == nullptr) {
    node->parent = new Node(x, y, num);
    node->parent->left = node;
    return node->parent;
  }
  return InsertNode(node->parent, x, y, num);
}

int main() {
  int n;
  int x;
  int y;
  size_t i = 0;
  Node* node = nullptr;
  std::vector<Node*> node_tree;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> x >> y;
    node = InsertNode(node, x, y, i + 1);
    node_tree.push_back(node);
  }
  std::cout << "YES" << '\n';
  while (i < node_tree.size()) {
    nullptr == node_tree[i]->parent
        ? std::cout << 0 << ' '
        : std::cout << node_tree[i]->parent->index << ' ';
    nullptr == node_tree[i]->left
        ? std::cout << 0 << ' '
        : std::cout << node_tree[i]->left->index << ' ';
    nullptr == node_tree[i]->right
        ? std::cout << 0 << '\n'
        : std::cout << node_tree[i]->right->index << '\n';
    i++;
  }
  for (size_t i = 0; i < node_tree.size(); i++) {
    delete node_tree[i];
  }
}