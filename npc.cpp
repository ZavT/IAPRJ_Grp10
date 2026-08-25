#include "npc.h"
#include <iostream>
#include <conio.h>

void npc::onOverlap()
{
    int rv = 0;
    switch (type) {
    case Type::Jake:
        rv = dialogue->performDialogue(dialogue->getJakeStartIndex());
        break;
    case Type::Ryan:
        rv = dialogue->performDialogue(dialogue->getRyanStartIndex());
        break;
    case Type::Alchemist:
        rv = dialogue->performDialogue(dialogue->getAlchemistStartIndex());
        break;
    default:
        rv = dialogue->performDialogue();
        break;
    }
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

    std::cout << "\nPress any key to continue..."; //to end dialogue
    (void)_getch();
}
