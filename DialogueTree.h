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

	int getfJakeStartIndex() const { return fJakeStartIndex; }
	int getJakeStartIndex() const { return jakeStartIndex; }
	int getRyanStartIndex() const { return ryanStartIndex; }
	int getAlchemistStartIndex() const { return alcStartIndex; }
	
private:
	vector <DialogueNode*> dialogueNodes;
	int jakeStartIndex;
	int fJakeStartIndex;
	int ryanStartIndex;
	int alcStartIndex;
};

