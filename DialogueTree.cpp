#include "DialogueTree.h"
#include <limits>

DialogueOption::DialogueOption(string Text, int ReturnCode, DialogueNode* NextNode) {
	this->text = Text;
	this->returnCode = ReturnCode;
	this->nextNode = NextNode;
}

DialogueNode::DialogueNode(string Text) {
	this->text = Text;
}

DialogueTree::DialogueTree() {
	jakeStartIndex = dialogueNodes.size();
	DialogueNode* node0 = new DialogueNode("It's a mutant. You tense, ready for another fight -- but something seems off. It recoils in fear, and you falter at the look in its eyes.\n'STOP! I'm not gonna hurt you, I swear. I'm not like the rest of them. Please, just lower your weapon.'");
	DialogueNode* node1 = new DialogueNode("Surprise flashes over his face. You put away your weapon.\n'You must be Jake. Ryan said you could tell me about this 'scientist'.'\nJake relaxes at the mention of Ryan's name. 'Well, yes.What do you want to know?'");
	DialogueNode* node2 = new DialogueNode("His twisted face sours.\n'That scientist... he liked experimenting on people. I'm one of his early prototypes. He mutated my body, but for some reason, my mind stayed intact. You don't have to be wary around me.'");
	DialogueNode* node3 = new DialogueNode("Well, it's always about money, isn't it? He pays people to be his experiments. Buys his way out of trouble. Next thing you know, everyone's dead or mutated and we're in the midst of a damn apocalypse.'\n<You gained 1 Intelligence!>");
	DialogueNode* node4 = new DialogueNode("When I first escaped, I thought I could make one. I gathered whatever equipment I could scavenge and tried to synthesize a cure. But... something's missing. And I'd bet whatever I need is in that lab...");
	DialogueNode* node5 = new DialogueNode("His eyes are on you, and there's a small glimmer of hope in them that wasn't there before.\n'My research is still over there on the workbench. If you can find the right materials, maybe you can finish the cure. Free everyone from this torture.'");
	DialogueNode* node6 = new DialogueNode("'It's a tall order, I know. But really... what kind of life would we all be living otherwise? I know you're capable. You've come this far, haven't you?'");
	DialogueNode* node7 = new DialogueNode("'Even if there was one, you can't just kill him like that. He’s altered himself, too. As long as the mutants are alive, he'll keep regenerating.'");
	DialogueNode* node8 = new DialogueNode("'If you want to end him, you need to hunt down every last mutant guarding that facility. Only when they're dead will he be vulnerable. Do that, and you might actually stand a chance.'");
	DialogueNode* node9 = new DialogueNode("'Y'know, I've heard that he could be planning something for the end of March. Like, a world-ending type of something. Not to rush you or anything...'");
	DialogueNode* node10 = new DialogueNode("''If it makes you feel better, have this. It's a failed version of the cure. It should ease your pain.'\n<You gained 1 Health Potion!> ");

	node0->dialogueOptions.push_back(DialogueOption("<1: You lower your weapon.>", 0, node1));
	node0->dialogueOptions.push_back(DialogueOption("<2: 'Bye.'>", 1, nullptr));
	dialogueNodes.push_back(node0);

	node1->dialogueOptions.push_back(DialogueOption("<1: 'What happened to you - and them?'>", 0, node2));
	node1->dialogueOptions.push_back(DialogueOption("<2: 'Maybe later, I've got things to do.'>", 5, nullptr));
	dialogueNodes.push_back(node1);

	node2->dialogueOptions.push_back(DialogueOption("<1: 'But how did he get people to experiment on?'>", 8, node3));
	node2->dialogueOptions.push_back(DialogueOption("<2: 'Is there a cure?'>", 0, node4));
	dialogueNodes.push_back(node2);

	node3->dialogueOptions.push_back(DialogueOption("<1: 'Is there a cure?'>", 0, node4));
	dialogueNodes.push_back(node3);

	node4->dialogueOptions.push_back(DialogueOption("<1: ...>", 0, node5));
	node4->dialogueOptions.push_back(DialogueOption("<2: 'I don't suppose you know a secret way in?'>", 0, node7));
	dialogueNodes.push_back(node4);
	
	node5->dialogueOptions.push_back(DialogueOption("<1: 'And by find, you mean break into his lab and steal them.'>", 0, node6));
	dialogueNodes.push_back(node5);

	node6->dialogueOptions.push_back(DialogueOption("<1: 'I don't suppose you know a secret way in?'>", 0, node7));
	dialogueNodes.push_back(node6);

	node7->dialogueOptions.push_back(DialogueOption("<1: 'Jeez, what a nut.'>", 0, node8));
	dialogueNodes.push_back(node7);

	node8->dialogueOptions.push_back(DialogueOption("<1: 'Piece of cake.'>", 0, node9));
	node8->dialogueOptions.push_back(DialogueOption("<2: 'Every last mutant...'>", 0, node10));
	dialogueNodes.push_back(node8);

	node9->dialogueOptions.push_back(DialogueOption("<1: 'Oh.'>", 2, nullptr));
	dialogueNodes.push_back(node9);

	node10->dialogueOptions.push_back(DialogueOption("<1: 'Sweet! Thanks.'> ", 9, node9));
	dialogueNodes.push_back(node10);

	// Jake's second tree
	fJakeStartIndex = dialogueNodes.size();

	DialogueNode* fjake0 = new DialogueNode("It's a mutant. You tense, ready for another fight -- but something seems off. It recoils in fear, and you falter at the look in its eyes.\n'STOP! I'm not gonna hurt you, I swear. I'm not like the rest of them. Please, just lower your weapon.'");

	fjake0->dialogueOptions.push_back(DialogueOption("<1: '...'>", 4, nullptr));
	dialogueNodes.push_back(fjake0);

	// Ryan's tree
	ryanStartIndex = dialogueNodes.size();

	DialogueNode* ryan0 = new DialogueNode("'Need any weapons?'");
	DialogueNode* ryan1 = new DialogueNode("'Hey, you look lost. I'm Ryan. It's nice to see another survivor.'");
	DialogueNode* ryan2 = new DialogueNode("'What, you mean with the giant rats and those mutants? Have you been living under a rock?'");
	DialogueNode* ryan3 = new DialogueNode("'Lucky you. I've been fighting for my life since all this started.'\nRyan heaves a sigh, his face haggard and weary.\n'Some scientist was experimenting on animals and humans. Gods know what he was trying to achieve, but he turned them into those monsters out there.'");
	DialogueNode* ryan4 = new DialogueNode("'Yep. I'd hunt him down myself if I wasn't injured so badly.'");
	DialogueNode* ryan5 = new DialogueNode("'Hell if I know. You can try asking Jake, though. He's in one of those sewers somewhere. He's a mutant, but he isn't like the rest of them. He can still think for himself. Don't worry, he won't harm you.'");

	ryan0->dialogueOptions.push_back(DialogueOption("<1: View weapon shop>", 5, nullptr));
	ryan0->dialogueOptions.push_back(DialogueOption("<2: Chat>", 0, ryan1));
	dialogueNodes.push_back(ryan0);

	ryan1->dialogueOptions.push_back(DialogueOption("<1: 'What the hell is going on out there?'>", 0, ryan2));
	ryan1->dialogueOptions.push_back(DialogueOption("<2: 'See you around.'>", 3, nullptr));
	dialogueNodes.push_back(ryan1);

	ryan2->dialogueOptions.push_back(DialogueOption("<1: 'In a bunker, actually.'>", 0, ryan3));
	dialogueNodes.push_back(ryan2);

	ryan3->dialogueOptions.push_back(DialogueOption("<1: '...He caused all this?'>", 0, ryan4));
	ryan3->dialogueOptions.push_back(DialogueOption("<2: 'Where is he?'>", 0, ryan5));
	dialogueNodes.push_back(ryan3);

	ryan4->dialogueOptions.push_back(DialogueOption("<1: 'Where is he?'>", 0, ryan5));
	dialogueNodes.push_back(ryan4);

	ryan5->dialogueOptions.push_back(DialogueOption("<1: 'Thanks. I'll be going now.'>", 3, nullptr));
	dialogueNodes.push_back(ryan5);

	// Alchemist's tree
	alcStartIndex = dialogueNodes.size();

	DialogueNode* alc0 = new DialogueNode("'My potions will greatly aid you on your journey.");

	alc0->dialogueOptions.push_back(DialogueOption("<1: View potion shop>", 6, nullptr));
	alc0->dialogueOptions.push_back(DialogueOption("<2: 'No thanks.'>", 7, nullptr));
	dialogueNodes.push_back(alc0);
}

DialogueTree::~DialogueTree() {
	for (size_t i = 0; i < dialogueNodes.size(); i++) {
		delete dialogueNodes[i];
	}
	dialogueNodes.clear();
}


int DialogueTree::performDialogue() {
	return performDialogue(0);
}

int DialogueTree::performDialogue(int startIndex) {
	if (startIndex < 0 || startIndex >= (int)dialogueNodes.size()) {
		cerr << "Invalid start index for dialogue: " << startIndex << "\n";
		return -1;
	}

	DialogueNode* current = dialogueNodes[startIndex];

	while (current) {
		cout << current->text << "\n\n";

		// If there are no options, ends conversation
		if (current->dialogueOptions.empty()) {
			return 0;
		}

		// Print the choices
		for (size_t i = 0; i < current->dialogueOptions.size(); ++i) {
			cout << current->dialogueOptions[i].text << "\n";
		}

		int choice = 0;
		while (true) {
			cout << "> ";
			cin >> choice;

			// prevents crash if presses letter instad of a num
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
			}

			// valid
			if (choice >= 1 && choice <= (int)current->dialogueOptions.size()) {
				break;
			}
			cout << "Invalid choice. Try again.\n";
		}

		// Move to the next node based on the player's choice
		DialogueOption& opt = current->dialogueOptions[choice - 1];
		if (opt.nextNode == nullptr) {
			return opt.returnCode;
		}
		current = opt.nextNode;
	}

	return 0;
}


