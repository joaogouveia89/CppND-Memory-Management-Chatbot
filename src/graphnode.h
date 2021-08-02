#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include <memory>
#include "chatbot.h"
#include <iostream>

// forward declarations
class GraphEdge;

class GraphNode
{
private:
    //// STUDENT CODE
    ////

    typedef std::unique_ptr<GraphEdge> GraphEdgeUniquePtr; // to avoid long and confusing lines

    // data handles (owned)
    std::vector<GraphEdgeUniquePtr> _childEdges;  // edges to subsequent nodes

    // data handles (not owned)
    //std::vector<GraphEdge *> _parentEdges; // edges to preceding nodes 
    ChatBot* _chatBot;

    int parentsCount = { 0 };

    ////
    //// EOF STUDENT CODE

    // proprietary members
    int _id;
    std::vector<std::string> _answers;

public:
    // constructor / destructor
    GraphNode(int id);
    ~GraphNode();

    // getter / setter
    int GetID() { return _id; }
    int GetNumberOfChildEdges() { return _childEdges.size(); }
    GraphEdge *GetChildEdgeAtIndex(int index);
    std::vector<std::string> GetAnswers() { return _answers; }
    int GetNumberOfParents(){ return parentsCount; }

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);
    void AddEdgeToChildNode(GraphEdgeUniquePtr &&edge);
    void incrementParentsCount(){ ++parentsCount; };

    //// STUDENT CODE
    ////

    void MoveChatbotHere(ChatBot* chatbot);

    ////
    //// EOF STUDENT CODE

    void MoveChatbotToNewNode(GraphNode* newNode);
};

#endif /* GRAPHNODE_H_ */