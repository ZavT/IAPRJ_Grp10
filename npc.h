#pragma once
#include "DialogueTree.h"
#include "player.h"
#include "inventory.h"

class npc
{
public:
	enum class Type { Jake, Ryan, Alchemist, Chest };
	npc(Type t, DialogueTree* tree) : type(t), dialogue(tree) {}
	// when player overlaps npc
	void onOverlap(player& p, inventory& bag);
	static bool talkedToRyan;

private:
	Type type;
	DialogueTree* dialogue;
};

