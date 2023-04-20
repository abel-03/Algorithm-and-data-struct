#include <iostream>

class Node {
public:
    bool leaf;       
    int n;          
    int key[30000];  
    Node* c[30000];  

    Node() {
        this->leaf = false;
        this->n = 0;
    }
    Node(int k) {
        this->leaf = true;
        this->n = 1;
        this->key[n - 1] = k;
    }
    Node(Node* r) {
        this->leaf = false;
        this->n = 0;
        this->c[n] = r;
    }
};
class Btree {
public:
    int T;
    Node* root = nullptr;  

    void Insert(int k) {
        if (!this->root) {
            this->root = new Node(k);
        }
        else if (!FindNode(this->root, k)) {
            Node* r = this->root;
            if (r->n == 2 * this->T - 1) {
                Node* s = new Node(r);
                this->root = s;
                SplitChild(s, 0);
                InsertNotFullNode(s, k);
            }
            else {
                InsertNotFullNode(r, k);
            }
        }
    }

    int Next(Node* node, int k) {
        int i = 0;
        if (!node) {
            return -1;
        }
        while (i < node->n) {
            if (node->key[i] == k) {
                return k;
            }
            if (node->key[i] > k) {
                if (node->leaf || (!node->leaf && node->c[i]->key[node->c[i]->n - 1] < k && node->c[i]->leaf)) {
                    return node->key[i];
                }
                return Next(node->c[i], k);
            }
            i++;
        }
        if (node->leaf) {
            return -1;
        }
        return Next(node->c[i], k);
    }
    void DeleteTree() { Delete(this->root); }


private:
    bool FindNode(Node* nd, int k) { return k == Next(nd, k); }
    void Delete(Node* nd) {
        if (nd) {
            if (!nd->leaf) {
                int i = 0;
                while (nd->c[i]) {
                    Delete(nd->c[i]);
                    i++;
                }
            }
            delete nd;
        }
    }


    void SplitChild(Node* x, int i) {
        Node* z = new Node();
        Node* y = x->c[i];
        z->leaf = y->leaf;
        z->n = this->T - 1;
        for (int j = 0; j < this->T - 1; j++) {
            z->key[j] = y->key[j + this->T];
        }

        if (!y->leaf) {
            for (int j = 0; j < this->T; j++) {
                z->c[j] = y->c[j + this->T];
            }
        }
        y->n = this->T - 1;
        for (int j = x->n - 1; j >= i; j--) {
            x->c[j + 1] = x->c[j];
        }
        x->c[i + 1] = z;
        for (int j = x->n + 1; j >= i; j--) {
            x->key[j + 1] = x->key[j];
        }
        x->key[i] = y->key[this->T - 1];
        x->n++;
    }

    void InsertNotFullNode(Node* x, int k) {
        int i = x->n - 1;
        if (x->leaf) {
            while (i >= 0 && k < x->key[i]) {
                x->key[i + 1] = x->key[i];
                i--;
            }
            x->key[i + 1] = k;
            x->n++;
        }
        else {
            while (i >= 0 && k < x->key[i]) i--;
            i++;
            if (x->c[i]->n == 2 * this->T - 1) {
                SplitChild(x, i);
                if (k > x->key[i]) {
                    i++;
                }
            }
            InsertNotFullNode(x->c[i], k);
        }
    }
};

class Command {
public:
    char adne;
    int key;

    int Doit(Btree* tree, int lastres) {
        if (this->adne == '+') {
            tree->Insert((this->key + lastres) % 1000000000);
            lastres = 0;
        }
        else {
            lastres = tree->Next(tree->root, key);
            std::cout << lastres << std::endl;
        }
        return lastres;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    Btree* tree = new Btree();
    tree->T = n;
    Command cmd;
    int lastres = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> cmd.adne >> cmd.key;
        lastres = cmd.Doit(tree, lastres);
    }
    tree->DeleteTree();
    delete tree;
    return 0;
}