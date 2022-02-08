#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>

#include "string.cpp"

#define CONST_K 10;

using namespace std;

struct Node {
    Node(string id) {
        this->id = id;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    Node(string id, Node* parent, Node* left, Node* right) {
        this->id = id;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }

    void set_left(Node* left) {
        if (this->left != nullptr) {
            this->left->parent = nullptr;
        }

        this->left = left;
        left->parent = this;
    }

    void set_right(Node* right) {
        if (this->right != nullptr) {
            this->right->parent = nullptr;
        }

        this->right = right;
        right->parent = this;
    }

    bool isReal() {
        // Return true if this id does not contain character X
        return this->id.find('X') == string::npos;
    }

    Node* get_left() {
        return this->left;
    }

    Node* get_right() {
        return this->right;
    }

    Node* get_parent() {
        return this->parent;
    }

    string get_id() {
        return this->id;
    }

    void set_id(string id) {
        this->id = id;
    }

private:
    string id;
    Node* parent;
    Node* left;
    Node* right;
};

struct TreeResult {
public:
    int level_n;
    int collisions;
    int successes;
    int idles;
    int time_slots;

    TreeResult() {
        this->level_n = 0;
        this->collisions = 0;
        this->successes = 0;
        this->idles = 0;
        this->time_slots = 0;
    }

    double get_efficiency() {
        return (this->time_slots != 0) ? (double)this->successes / (double)this->time_slots * 100 : 0.0;
    }

    void print() {
        cout << "Level n: " << this->level_n << endl;
        cout << "Collisions: " << this->collisions << endl;
        cout << "Success: " << this->successes << endl;
        cout << "Idle: " << this->idles << endl;
        cout << "Time slots: " << this->time_slots << endl;
        cout << "Efficiency: " << this->get_efficiency() << "%" << endl;
    }
};

struct Tree {
    Tree(int K) {
        // Initialize value of K and tree result object
        this->K = K;
        this->result = TreeResult();

        // Initialize root node and levels vector
        this->root = new Node(StringExtension::pad_left("", "X", K));
        this->levels = vector<vector<Node*>>({ { root } });

        // Initialize levels to K members
        for (int t = 1; t <= K; t++) {
            this->levels.push_back(vector<Node*>());
        }

        // Construct tree recursively
        this->construct(this->root, "");
    }

    Node* get_root() {
        return this->root;
    }

    TreeResult get_result() {
        return this->result;
    }

    void probe(vector<string> ids) {
        this->probe(ids, 0);
    }

    void probe(vector<string> ids, int level_n) {
        this->result = TreeResult();

        vector<string> ids_pad = this->convert_to_binary_strings(ids);
        this->result.level_n = level_n;

        if (level_n > 0) {
            vector<Node*> level = this->levels[level_n];

            // For each leaf node, probe the leaf
            for (Node* leaf : level) {
                this->result.time_slots++;
                this->probe(leaf, ids_pad);

                if (this->result.successes == ids.size()) {
                    break;
                }
            }

        } else {
            // Start from root
            this->result.time_slots++;
            vector<string> ids_pad = this->convert_to_binary_strings(ids);
            this->probe(this->root, ids_pad);
        }
    }

    void print_tree() {
        this->print_tree(this->root);
        cout << endl;
    }

    // Print levels
    void print_levels() {
        for (int t = 0; t < this->levels.size(); t++) {
            cout << "Level " << t << ": ";
            for (Node* node : this->levels[t]) {
                cout << node->get_id() << " ";
            }
            cout << endl;
        }
    }

private:
    int K;
    Node* root;
    vector<vector<Node*>> levels;
    TreeResult result;

    void construct(Node* parent, string prefix) {
        int k = prefix.length() + 1;

        if (k <= this->K) {
            // Left
            string prefix_0 = prefix + "0";
            string prefix_0X = StringExtension::pad_right(prefix_0, "X", K);
            Node* node_0 = new Node(prefix_0X);
            parent->set_left(node_0);
            this->construct(node_0, prefix_0);

            // Right
            string prefix_1 = prefix + "1";
            string prefix_1X = StringExtension::pad_right(prefix_1, "X", K);
            Node* node_1 = new Node(prefix_1X);
            parent->set_right(node_1);
            this->construct(node_1, prefix_1);

            this->levels[k].push_back(node_0);
            this->levels[k].push_back(node_1);
        }
    }

    void probe(Node* node, vector<string> ids) {
        // Check collision
        vector<string> collide_ids = this->get_collide_ids(node, ids);


        if (collide_ids.size() == 1) {
            // cout << "success: " << collide_ids[0] << endl;
            this->result.successes++;
            return;
        } else if (collide_ids.size() == 0) {
            // cout << "idle: " << node->get_id() << endl;
            this->result.idles++;
            return;
        }


        // When there is a collide
        // cout << "collision: " << node->get_id() << ", size: " << collide_ids.size() << endl;
        this->result.collisions++;

        // If left and right child is not null, then recursively calls probe
        if (node->get_left() != nullptr) {
            this->result.time_slots++;
            this->probe(node->get_left(), collide_ids);
        }

        if (node->get_right() != nullptr) {
            this->result.time_slots++;
            this->probe(node->get_right(), collide_ids);
        }

    }

    vector<string> get_collide_ids(Node* node, vector<string> ids) {
        // Find index of X in id
        int index = node->get_id().find('X');

        // Vector of collide ids
        vector<string> collide_ids;

        // Check if the first n characters of node id is the same with current id in for loop
        for (string id : ids) {
            if (id.substr(0, index) == node->get_id().substr(0, index)) {
                collide_ids.push_back(id);
            }
        }

        return collide_ids;
    }

    // Integer to binary integer
    int to_binary(int n) {
        int result = 0;
        int power = 1;

        while (n > 0) {
            result += (n % 2) * power;
            n /= 2;
            power *= 10;
        }

        return result;
    }

    // Convert int vector to binary int vector
    vector<string> convert_to_binary_strings(vector<string> ids) {
        vector<string> result;

        for (string num : ids) {
            int binary = this->to_binary(stoi(num));
            string binary_string(to_string(binary));
            binary_string = StringExtension::pad_left(binary_string, "0", this->K);
            result.push_back(binary_string);
        }

        return result;
    }

    // Display binary tree
    void print_tree(Node* root) {
        if (root == NULL) {
            cout << "_";
            return;
        }

        cout << "(";
        print_tree(root->get_left());
        cout << " " << root->get_id() << " ";
        print_tree(root->get_right());
        cout << ")";
    }
};


// Read the input file and return a vector of integers
vector<string> read_file(string fileName) {
    ifstream file(fileName);
    vector<string> result;
    string line;
    while (getline(file, line)) {
        result.push_back(line);
    }
    return result;
}





int main() {
    int K = CONST_K;
    Tree tree(K);

    // Loop for file name from customer1 to customer 10
    for (int t = 1; t <= 10; t++) {
        // Open file
        cout << "Customer " << t << endl;

        string fileName = "customer" + to_string(t) + ".txt";
        vector<string> ids = read_file(fileName);

        TreeResult highest_efficiency_result;

        // For each value from 0 to K, find the highest efficiency tree
        // Here, when k = 0 indicates starts from root, k = K indicates starts from leaf
        for (int k = 0; k <= K; k++) {
            tree.probe(ids, k);
            tree.get_result().print();
            cout << endl;

            // If current tree efficiency is higher than highest eficiency tree, then update
            if (tree.get_result().get_efficiency() > highest_efficiency_result.get_efficiency()) {
                highest_efficiency_result = tree.get_result();
            }
        }

        cout << "Highest efficiency result: " << endl;
        highest_efficiency_result.print();
        cout << endl << endl << endl;
    }
}