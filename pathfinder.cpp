#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;
// class path;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    int totalStops = 0;
    MetroStop* stop = node;
    while (stop != nullptr) {
        totalStops++;
        stop = stop->getNextStop();
    }
    return totalStops;

}

void MetroLine::populateLine(std::string filename) {
    // Read the file and populate the line
    ifstream file(filename);

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, ' ')) {
            tokens.push_back(token);
        }

       
        int fare = stoi(tokens.back());
        string station_name ;
        for (int i = 0; i < tokens.size() - 1;i++) {
            station_name += tokens[i];
            station_name += " ";
        }
        // cout<<station_name<< " " <<fare<<endl;
        MetroStop* stop = new MetroStop(station_name,this, fare);

        if (this->getNode() == nullptr) {
            node = stop;
        } else {
            MetroStop* last_node = node;
            while (last_node->getNextStop() != nullptr) {
                last_node = last_node->getNextStop();
            }
            last_node->setNextStop(stop);
            stop->setPrevStop(last_node);
        }
    }

    file.close();
}
// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;                                     ////////////
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = height(node->getLeft());
    int rightHeight = height(node->getRight());

    return std::max(leftHeight, rightHeight) + 1;
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}

void AVLTree::rotateLeft(AVLNode* node) {
    // AVLNode* newRoot = node->getRight();
    // node->setRight(newRoot->getLeft());
    // newRoot->setLeft(node);
    // node = newRoot;
    if (node == nullptr || node->getRight() == nullptr) {
        return;
    }

    AVLNode* newRoot = node->getRight();
    node->setRight(newRoot->getLeft());
    if (newRoot->getLeft() != nullptr) {
        newRoot->getLeft()->setParent(node);
    }

    newRoot->setLeft(node);
    newRoot->setParent(node->getParent());

    if (node->getParent() != nullptr) {
        if (node == node->getParent()->getLeft()) {
            node->getParent()->setLeft(newRoot);
        } else {
            node->getParent()->setRight(newRoot);
        }
    } else {
        root = newRoot;
    }

    node->setParent(newRoot);
    
}

void AVLTree::rotateRight(AVLNode* node) {
    // AVLNode* newRoot = node->getLeft();
    // node->setLeft(newRoot->getRight());
    // newRoot->setRight(node);
    // node = newRoot;
    if (node == nullptr || node->getLeft() == nullptr) {
        return;
    }

    AVLNode* newRoot = node->getLeft();
    node->setLeft(newRoot->getRight());
    if (newRoot->getRight() != nullptr) {
        newRoot->getRight()->setParent(node);
    }

    newRoot->setRight(node);
    newRoot->setParent(node->getParent());

    if (node->getParent() != nullptr) {
        if (node == node->getParent()->getLeft()) {
            node->getParent()->setLeft(newRoot);
        } else {
            node->getParent()->setRight(newRoot);
        }
    } else {
        root = newRoot;
    }

    node->setParent(newRoot);
}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
        if (node == nullptr) {
            AVLNode* newNode = new AVLNode(metroStop->getStopName());
            newNode->addMetroStop(metroStop);
            return;
        }

        int existenceComparison = stringCompare(metroStop->getStopName(), node->getStopName());

        if (existenceComparison == 0) {
            node->addMetroStop(metroStop);
        }
        else if (existenceComparison > 0) {
            if (node->getRight() != nullptr) {
                insert(node->getRight(), metroStop);
                
            }
            else {
                AVLNode* newNode = new AVLNode(metroStop->getStopName());
                node->setRight(newNode);
                newNode->setParent(node);
                newNode->addMetroStop(metroStop);
                this->balance(newNode);
            }
        }
        else{
            if (node->getLeft() != nullptr) {
                insert(node->getLeft(), metroStop);
            }
            else {
                AVLNode* newNode = new AVLNode(metroStop->getStopName());
                node->setLeft(newNode);
                newNode->setParent(node);
                newNode->addMetroStop(metroStop);
                this->balance(newNode);
            }
        }

        // return node;
}
void AVLTree::balance(AVLNode* node) {
    AVLNode* current = node;
        if (current->getParent() == NULL) {
            return;
        }

        AVLNode* gr_parent = current->getParent()->getParent();
        while (gr_parent != nullptr) {
            int balance = balanceFactor(gr_parent);
            if (balance > 1 || balance < -1) {
                if (balance < -1 ) {
                    if(stringCompare(gr_parent->getStopName(), current->getParent()->getStopName()) < 0 && stringCompare(current->getParent()->getStopName(), current->getStopName()) < 0){
                        rotateLeft(gr_parent);
                        return;
                    } else if (stringCompare(gr_parent->getStopName(), current->getParent()->getStopName()) < 0 && stringCompare(current->getParent()->getStopName(), current->getStopName()) > 0) {
                        rotateRight(current->getParent());
                        rotateLeft(gr_parent);
                    return;
                    }
                } 
                else if (balance > 1 ) {
                    if(stringCompare(gr_parent->getStopName(), current->getParent()->getStopName()) > 0 && stringCompare(current->getParent()->getStopName(), current->getStopName()) > 0){
                        rotateRight(gr_parent);
                        return;
                    }
                    else if (stringCompare(gr_parent->getStopName(), current->getParent()->getStopName()) > 0 && stringCompare(current->getParent()->getStopName(), current->getStopName()) < 0) {
                        rotateLeft(current->getParent());
                        rotateRight(gr_parent);
                    return;
                    }
                } 
            }
            
            current = current->getParent();
            gr_parent = gr_parent->getParent();
        }
}

void AVLTree::populateTree(MetroLine* metroLine) {
     if (metroLine == NULL) {
        return;
    }

    MetroStop* currentStop = metroLine->getNode();
    while (currentStop != nullptr) {
        insert(this->getRoot(), currentStop);
        currentStop = currentStop->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    // if (node == nullptr) {
    //     return;
    // }
    // inOrderTraversal(node->getLeft());
    
    // cout << node->getStopName() << std::endl;
    
    // inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
    // AVLNode* currentNode = root;
    // while (currentNode != nullptr) {
    //     int cmp = stringCompare(stopName, currentNode->getStopName());
    //     if (cmp < 0) {
    //         currentNode = currentNode->getLeft();
    //     } else if (cmp > 0) {
    //         currentNode = currentNode->getRight();
    //     } else {
    //         return currentNode;
    //     }
    // }
    // return nullptr; // Stop not found

}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
}

Path* PathFinder::findPath(std::string origin, std::string destination) {
    // Initialize exploration queue and visited set
    // Exploration exploration;
    // std::unordered_set<MetroStop*> visited;

    // // Find the origin and destination AVL nodes
    // AVLNode* originNode = tree->searchStop(origin);
    // AVLNode* destinationNode = tree->searchStop(destination);

    // if (originNode == nullptr || destinationNode == nullptr) {
    //     return nullptr;  // Origin or destination not found
    // }

    // // Create initial trips for both directions from the origin
    // Trip* forwardTrip = new Trip(originNode, nullptr);
    // Trip* backwardTrip = new Trip(originNode, nullptr);

    // // Enqueue initial trips for exploration
    // exploration.enqueue(forwardTrip);
    // exploration.enqueue(backwardTrip);

    // while (!exploration.isEmpty()) {
    //     Trip* currentTrip = exploration.dequeue();
    //     AVLNode* currentNode = currentTrip->getNode();

    //     // If the destination is reached in either direction, return the path
    //     if (currentNode == destinationNode) {
    //         return constructPath(currentTrip);
    //     }

    //     // Mark the current node as visited
    //     visited.insert(currentNode);

    //     // Explore adjacent nodes in both directions
    //     for (AVLNode* adjacentNode : getAdjacentNodes(currentNode)) {
    //         if (visited.find(adjacentNode) == visited.end()) {
    //             Trip* newTrip = new Trip(adjacentNode, currentTrip);
    //             exploration.enqueue(newTrip);
    //         }
    //     }
    // }

    // return nullptr;  // No path found
}
    
vector<MetroLine*> lines;
