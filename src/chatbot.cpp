#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

#include "chatlogic.h"
#include "graphnode.h"
#include "graphedge.h"
#include "chatbot.h"

// constructor WITHOUT memory allocation
ChatBot::ChatBot()
{
    // invalidate data handles
    ResetAttributes();
}

// constructor WITH memory allocation
ChatBot::ChatBot(std::string filename)
{
    std::cout << "ChatBot Constructor{ address = " << this << " size = " << sizeof(this) <<" bytes }" << std::endl;
    
    // invalidate data handles
    ResetAttributes();

    this->filename = filename;

    // load image into heap memory
    this->_image = new wxBitmap(filename, wxBITMAP_TYPE_PNG);
}

ChatBot::~ChatBot()
{
    std::cout << "ChatBot Destructor{ address = " << this <<" }" << std::endl;
    if(isCurrentInstance()){
        delete _image;
        //delete _rootNode;
        //delete _chatLogic
        //delete _currentNode
    }
}

//// STUDENT CODE
////

ChatBot::ChatBot(const ChatBot &source){
    _chatLogic = source._chatLogic; // I copy the reference here, as this chatLogic object is supposed to pass along the instances
    _rootNode = source._rootNode;
    *_image = *source._image;
    filename = source.filename;
    _currentNode = source._currentNode;
     std::cout << "ChatBot::COPYING content of instance " << &source << " to instance " << this << std::endl;
}

ChatBot& ChatBot::operator=(const ChatBot &source){
    std::cout << "ChatBot::ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
        return *this;
    ResetAttributes();
    _rootNode = source._rootNode;
    filename = std::string(source.filename);
    *_image = *source._image;
    _chatLogic = source._chatLogic;
    return *this;
}

ChatBot::ChatBot(ChatBot &&source){
    std::cout << "ChatBot::MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;
    this->_chatLogic = source._chatLogic;
    this->_rootNode = source._rootNode;
    this->_image = source._image;
    this->filename = source.filename;
    this->_currentNode = source._currentNode;
    source.ResetAttributes();
}

ChatBot &ChatBot::operator=(ChatBot &&source){
    std::cout << "ChatBot::MOVING (assign) instance " << &source << " to instance " << this << std::endl;
    if (this == &source)
        return *this;
    ResetAttributes();
    this->_image = source._image;
    this->_chatLogic = source._chatLogic;
    this->_rootNode = source._rootNode;
    this->filename = source.filename;
    this->_currentNode = source._currentNode;
    source.ResetAttributes();
    return *this;
}

void ChatBot::ResetAttributes(){
    this->_rootNode = nullptr;
    this->_image = NULL;
    this->_chatLogic = nullptr;
    this->_currentNode = nullptr;
}

bool ChatBot::isCurrentInstance(){
    return _rootNode != nullptr && _image != NULL && _chatLogic != nullptr && _currentNode != nullptr;
}

////
//// EOF STUDENT CODE

void ChatBot::ReceiveMessageFromUser(std::string message)
{
    // loop over all edges and keywords and compute Levenshtein distance to query
    typedef std::pair<GraphEdge *, int> EdgeDist;
    std::vector<EdgeDist> levDists; // format is <ptr,levDist>
    for (size_t i = 0; i < _currentNode->GetNumberOfChildEdges(); ++i)
    {
        GraphEdge *edge = _currentNode->GetChildEdgeAtIndex(i);
        for (auto keyword : edge->GetKeywords())
        {
            EdgeDist ed{edge, ComputeLevenshteinDistance(keyword, message)};
            levDists.push_back(ed);
        }
    }

    // select best fitting edge to proceed along
    GraphNode *newNode;
    if (levDists.size() > 0)
    {
        // sort in ascending order of Levenshtein distance (best fit is at the top)
        std::sort(levDists.begin(), levDists.end(), [](const EdgeDist &a, const EdgeDist &b) { return a.second < b.second; });
        newNode = levDists.at(0).first->GetChildNode(); // after sorting the best edge is at first position
    }
    else
    {
        // go back to root node
        newNode = _rootNode;
    }

    // tell current node to move chatbot to new node
    _currentNode->MoveChatBotToNode(newNode);
}

void ChatBot::SetCurrentNode(GraphNode *node)
{
    // update pointer to current node
    
    _currentNode = node;
    _chatLogic->SetCurrentNode(_currentNode);
    

    // select a random node answer (if several answers should exist)
    std::vector<std::string> answers = _currentNode->GetAnswers();
    std::mt19937 generator(int(std::time(0)));
    std::uniform_int_distribution<int> dis(0, answers.size() - 1);
    std::string answer = answers.at(dis(generator));
    // send selected node answer to user
    _chatLogic->SendMessageToUser(answer);
}

GraphNode* ChatBot::GetCurrentNode() const{
    return _currentNode;
}

int ChatBot::ComputeLevenshteinDistance(std::string s1, std::string s2)
{
    // convert both strings to upper-case before comparing
    std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

    // compute Levenshtein distance measure between both strings
    const size_t m(s1.size());
    const size_t n(s2.size());

    if (m == 0)
        return n;
    if (n == 0)
        return m;

    size_t *costs = new size_t[n + 1];

    for (size_t k = 0; k <= n; k++)
        costs[k] = k;

    size_t i = 0;
    for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i)
    {
        costs[0] = i + 1;
        size_t corner = i;

        size_t j = 0;
        for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j)
        {
            size_t upper = costs[j + 1];
            if (*it1 == *it2)
            {
                costs[j + 1] = corner;
            }
            else
            {
                size_t t(upper < corner ? upper : corner);
                costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
            }

            corner = upper;
        }
    }

    int result = costs[n];
    delete[] costs;

    return result;
}

std::string ChatBot::FileName()const{ return this->filename; }
void ChatBot::FileName(const std::string filename){  this->filename = filename; }