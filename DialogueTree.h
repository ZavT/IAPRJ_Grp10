#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class DialogueNode;

class DialogueOption {
public:
	DialogueOption(string Text, int ReturnCode, DialogueNode *NextNode);
	string text;
	int returnCode;
	DialogueNode* nextNode;
};

class DialogueNode {
public:
	DialogueNode(string Text);
	string text;
	vector<DialogueOption> dialogueOptions;
};

class DialogueTree
{
public:
	DialogueTree();
	~DialogueTree();
	int performDialogue();
	int performDialogue(int startIndex);

	int getJakeStartIndex() const { return fjakeStartIndex; }
	int getRyanStartIndex() const { return ryanStartIndex; }
	int getAlchemistStartIndex() const { return alcStartIndex; }
	int getChestStartIndex() const { return chestStartIndex; }

private:
	vector <DialogueNode*> dialogueNodes;
	int fjakeStartIndex; // start index for Jake's second dialogue tree
	int ryanStartIndex; // start index for Ryan's dialogue tree
	int alcStartIndex; // start index for alchemist's dialogue tree
	int chestStartIndex; // start index for chest's dialogue tree
};

