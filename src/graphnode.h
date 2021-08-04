#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include <memory>
#include "chatbot.h"
#include <wx/bitmap.h>

// forward declarations
class GraphEdge;

class GraphNode
{
private:
    //// STUDENT CODE
    ////
    ChatBot _chatBot;

    typedef std::unique_ptr<GraphEdge> GraphEdgeUniquePtr; // to avoid long and confusing lines

    // data handles (owned)
    std::vector<GraphEdgeUniquePtr> _childEdges;  // edges to subsequent nodes

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

    void SetChatBot(ChatBot ChatBot);
    void MoveChatBotToNode(GraphNode* newNode);
    wxBitmap* GetChatBotImageHandler() { return _chatBot.GetImageHandle(); }
    void SendMessageToChatBot(std::string message){
        _chatBot.ReceiveMessageFromUser(message);
    }

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);
    void AddEdgeToChildNode(GraphEdgeUniquePtr &&edge);
    void incrementParentsCount(){ ++parentsCount; };
};

#endif /* GRAPHNODE_H_ */