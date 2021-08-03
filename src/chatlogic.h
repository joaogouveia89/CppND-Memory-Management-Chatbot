#ifndef CHATLOGIC_H_
#define CHATLOGIC_H_

#include <vector>
#include <string>
#include "chatgui.h"
#include "chatbot.h"

// forward declarations
class GraphEdge;
class GraphNode;


class ChatLogic
{
private:
    //// STUDENT CODE
    ////

    typedef std::unique_ptr<GraphNode> GraphNodeUniquePtr; // to avoid long and confusing lines

    // data handles (owned)
    std::vector<GraphNodeUniquePtr> _nodes;

    ////
    //// EOF STUDENT CODE

    // data handles (not owned)
    GraphNode *_currentNode;
    ChatBotPanelDialog *_panelDialog;

    // proprietary type definitions
    typedef std::vector<std::pair<std::string, std::string>> tokenlist;

    // proprietary functions
    template <typename T>
    void AddAllTokensToElement(std::string tokenID, tokenlist &tokens, T &element);

public:

    // constructor / destructor
    ChatLogic();
    ~ChatLogic();

    // getter / setter
    void SetPanelDialogHandle(ChatBotPanelDialog *panelDialog);

    // proprietary functions
    void LoadAnswerGraphFromFile(std::string filename);
    void SendMessageToUser(std::string message);

    GraphNode* GetCurrentNode() const{return _currentNode;}

    void SetCurrentNode(GraphNode* node){_currentNode = node; }
};

#endif /* CHATLOGIC_H_ */