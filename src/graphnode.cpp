#include "graphedge.h"
#include "graphnode.h"

#include<iostream>

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
    
    // if(_chatBot){
    //     std::cout << "Deleting chatbot";
    //     delete &_chatBot;
    // };

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToChildNode(GraphEdgeUniquePtr &&edge)
{
    _childEdges.emplace_back(std::move(edge));
}


GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    if(index < 0) 
        index = 0;

    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}

void GraphNode::SetChatBot(ChatBot chatBot){
    std::cout << "this->_chatBot = std::move(chatBot);\n";
    this->_chatBot = std::move(chatBot);
    this->_chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatBotToNode(GraphNode* newNode){
    newNode->SetChatBot(std::move(this->_chatBot));
}