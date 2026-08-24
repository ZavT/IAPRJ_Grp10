#include "npc.h"
#include <iostream>

void npc::onOverlap()
{
	switch (type) {
	case Type::Jake:
		dialogue->performDialogue(dialogue->getJakeStartIndex());
		break;
	case Type::Ryan:
		dialogue->performDialogue(dialogue->getRyanStartIndex());
		break;
	case Type::Alchemist:
		dialogue->performDialogue(dialogue->getAlchemistStartIndex());
		break;
	default:
		dialogue->performDialogue();
		break;
	}
    DialogueTree dialogueTree;
    int rv = dialogueTree.performDialogue();
    if (rv == 1) {
        std::cout << "\n'Oh... well, thanks for sparing me.'\n";
    }
    if (rv == 2) {
        std::cout << "\n'Good luck, stranger. Make him pay for what he did to us.'\n";
    }
    if (rv == 3) {
        std::cout << "\n'Hey, come back to me if you need any weapons. You should arm yourself up before you go out there.'\n";
    }
    if (rv == 4) {
        std::cout << "\nYou hesitate but back away cautiously, hoping you won't regret your decision later.\n";
    }
    if (rv == 5) {
        std::cout << "\nWeapon shop\n";
    }
    if (rv == 6) {
        std::cout << "\nPotion shop\n";
    }
    if (rv == 7) {
        std::cout << "\n'Good luck...'\n";
    }
}
