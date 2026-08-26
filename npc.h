#pragma once
#include "DialogueTree.h"
#include "player.h"
#include "inventory.h"

class npc
{
public:
	enum class Type { fJake, Jake, Ryan, Alchemist, Chest };

	npc(Type t, DialogueTree* tree) : type(t), dialogue(tree) {}

	// when player overlaps npc
	void onOverlap();

private:
	Type type;
	DialogueTree* dialogue;

	player player;
	inventory bag;
};

