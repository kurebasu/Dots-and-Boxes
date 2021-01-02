/*
*File: main.cc
*Author: Said Krebbers (s1381164)
*Last edit date: -
*/


#include <vector>

// const int numberOfGames = 100;
const int gamesPerSelection = 1;
int gNumberOfNodes;



class Node{
public:
	Node(Node* creator);							//constructor for children nodes
	Node(int rows, int columns);			//constructor for the root node
	~Node();													//destructor

	void cleanTree();

	bool isLeafNode();
	void backPropagate(int wins1, int losses1, int ties1);//function to propagate upwards in tree
	// void expand(int amountOfMoves, int noOfChildren);			//function to expand downwards in tree

	int getWins()	{return wins;}
	int getLosses()	{return losses;}
	int getTies()	{return ties;}
	int getVisits() {return wins+losses+ties;}

	int 		maxChild(bool justSelection = true);

	void 		printAllChild();
	double 	calcUCB1Value();
	bool 		isConsistent();
	void 		printTree(bool first = true);
	void 		printRoot(bool first = true);




	// static const int maxSize = 8;																//maximum dimentions of the board (in boxes)
	// static const int maxNoOfMoves = (2 * (maxSize+1) * maxSize);	//maximum number of doable moves in the beginning of the maxSize board is 2 * 9 * 8
	int rows, columns, maxNoOfMoves;																//all this information might be redundant
	int wins, losses, ties;
	bool isRoot;
	int nodeNumber;

	Node* parent;
	std::vector<Node*> children;

private:
	void updateValue();		//update the value of this tree according to children
};


Node::Node(int rows, int columns){
	this->rows = rows;
	this->columns = columns;
	maxNoOfMoves = ((rows+1) * columns) + (rows * (columns + 1));
	wins = losses = ties = 0;
	isRoot = true;
	parent = NULL;
	nodeNumber = 0;
	gNumberOfNodes = 1;
}

Node::Node(Node* creator){
	isRoot = false;
	parent = creator;
	wins = losses = ties = 0;
	nodeNumber = gNumberOfNodes;
	gNumberOfNodes++;
}

Node::~Node(){
	for(Node* node : children){
		delete node;
	}
}


void Node::cleanTree(){
	for(Node* node : children){
		// std::cout << "hier 4" << std::endl;
		delete node;
		node = NULL;
		// std::cout << "hier 5" << std::endl;
	}
	children.clear();
	wins = losses = ties = 0;
	gNumberOfNodes = 1;
}

bool Node::isLeafNode(){
	return !(bool)(children.size());
}

int Node::maxChild(bool justSelection){
	double maxValue = INT_MIN;
	double currentValue = INT_MIN;
	int move = 0;
	int bestMove = INT_MIN;
	int visits = 0;
	// if(this->isRoot){
		// std::cout << "begin maxchild" << std::endl;
		// std::cout << "#children = " << children.size() << std::endl;
		// printTree();
	// }
	for(Node* node : children){
		if(gMove == 0 || justSelection){//UCB1
			currentValue = node->calcUCB1Value();
		}
		else if(gMove == 1){//MAX CHILD
			visits = node->getVisits();
			if (visits == 0){
				visits = 1; //make sure we don't divide by 0
			}
			currentValue = double((double)(node->getWins())/(double)(visits));
		}
		else if(gMove == 2){//ROBUST CHILD
			currentValue = node->getVisits();
		}
		if(currentValue > maxValue){
			bestMove = move;
			maxValue = currentValue;
		}
		++move;
	}
	// std::cout << std::endl;
	return bestMove;
}

void Node::printAllChild(){
	double currentValue = INT_MIN;
	int i = 0;
	int visits = 0;
	for(Node* node : children){
		if(gMove == 0){//UCB1
			currentValue = node->calcUCB1Value();
		}
		else if(gMove == 1){//MAX CHILD
			visits = node->getVisits();
			if (visits == 0){
				visits = 1; //make sure we don't divide by 0
			}
			currentValue = (double)(node->getWins())/(double)(visits);
		}
		else if(gMove == 2){//ROBUST CHILD
			currentValue = node->getVisits();
		}
		std::cout << "currentValue for child " << i++ << " : " << currentValue <<std::endl;
	}
}

double Node::calcUCB1Value(){
	double C = 0.4; //constant value
	int Wi = wins;
	double ni = (double)getVisits();
	int Ni = 0;
	double UCB1 = 0;
	if(parent != NULL) //which it should never be...
		Ni = parent->getVisits();

  //for calculation purposes and avoiding dividing by 0
  if(ni == 0){
		ni = 0.5;
	}

	UCB1 = (Wi/ni) + (C * sqrt( (log(Ni) / ni) ));

	return UCB1;
}



void Node::updateValue(){
	int oldWins 	= wins;
	int oldLosses 	= losses;
	int oldTies 	= ties;

	wins = losses = ties = 0;

	for(Node* node : children){
		if(node != NULL){
			wins 	+= node->getWins();
			losses 	+= node->getLosses();
			ties 	+= node->getTies();
		}
	}

	if(parent != NULL){
		parent->backPropagate((wins - oldWins), (losses - oldLosses), (ties - oldTies)); //Give the difference in score back to parent
	}
}

void Node::backPropagate(int wins1, int losses1, int ties1){
	wins 	+= wins1;
	losses 	+= losses1;
	ties 	+= ties1;
	if(parent != NULL){
		parent->backPropagate(wins1, losses1, ties1);
	}
}

bool Node::isConsistent(){
	int cWins = 0;
	int cLosses = 0;
	int cTies = 0;

	for(Node* node : children){
		if(node != NULL){
			cWins += node->getWins();
			cLosses += node->getLosses();
			cTies += node->getTies();
		}
	}
	// //Check if this node is inconsistent with children
	// if(cWins != wins || cLosses != losses || cTies != ties){
	// 	return false;
	// }

	//Check if this node is inconsistent with children (might be off by 2 but eh)
	// if(!((cWins == wins || cWins == wins +1)
  //  	&&(cLosses == losses || cLosses == losses +1)
	// 	&&(cTies == ties || cTies == ties + 1))){
	// 		return false;
	// 	}
	// if(!(getVisits() == cWins + cLosses + cTies + 1)){
		// std::cout << nodeNumber << " is the problemo" << std::endl;
		// std::cout << "cwins = " << cWins << " closses = " << cLosses << " cTies = " << cTies << std::endl;
		// std::cout << "getvisits() = " << getVisits() << std::endl;
		// std::cout << "getvisits = niet alles children +1" << std::endl;
		// return false;
	// }

	// else{ //check if children are consistent
		for(Node* node : children){
			if(node != NULL){
				if(!(node->isConsistent())){
					return false;
				}
			}
		}
	// }

	return true;

}

void Node::printTree(bool first){
	Node* cParent = parent;
	if(first){
		std::cout << "start of print tree:" << std::endl;
		std::cout << "digraph test{" << std::endl;
	}

	//print line for the node itself
	// if(getVisits() > 0){ //if it is not empty
		std::cout << nodeNumber << " [label=\"" << wins << "/" << losses << "/" << ties << "\" color=black, "
							<< "fontcolor=black, fontsize=12, shape=circle]" << std::endl;
		//print line for connection with parent:
		if(parent!= NULL){
			std::cout << parent->nodeNumber << " -> " << nodeNumber << ";" << std::endl;
		}
	// }


	// std::cout << "myNumber: " << nodeNumber <<std::endl;
	//
	// while(cParent != NULL){
	// 	std::cout << " child of: " << cParent->nodeNumber;
	// 	cParent = cParent->parent;
	// }
	//
	// std::cout << std::endl << "wins :" << wins << " losses: " << losses << " ties: " << ties << std::endl;
	//
	// std::cout << std::endl;

	for (Node* node : children){
		node->printTree(false);
	}


	if(first){
		std::cout << "}" << std::endl;
		std::cout << "end of print tree:" << std::endl;
	}

}

void Node::printRoot(bool first){
	Node* cParent = parent;
	if(first){
		std::cout << "start of print tree:" << std::endl;
		std::cout << "digraph test{" << std::endl;
	}

	//print line for the node itself
	if(getVisits() > 0){ //if it is not empty
		std::cout << nodeNumber << " [label=\"" << wins << "/" << losses << "/" << ties << "\" color=black, "
							<< "fontcolor=black, fontsize=12, shape=circle]" << std::endl;
		//print line for connection with parent:
		if(parent!= NULL){
			std::cout << parent->nodeNumber << " -> " << nodeNumber << ";" << std::endl;
		}
	}


	// std::cout << "myNumber: " << nodeNumber <<std::endl;
	//
	// while(cParent != NULL){
	// 	std::cout << " child of: " << cParent->nodeNumber;
	// 	cParent = cParent->parent;
	// }
	//
	// std::cout << std::endl << "wins :" << wins << " losses: " << losses << " ties: " << ties << std::endl;
	//
	// std::cout << std::endl;
	if(first)
		for (Node* node : children){
			node->printRoot(false);
		}

	if(first){
		std::cout << "}" << std::endl;
		std::cout << "end of print tree:" << std::endl;
	}

}




/**********************************************************************************************************************************/

class MCTSPlayer : public Player{
public:
	MCTSPlayer(Dotsboxes* g);	//constructor;
	~MCTSPlayer();						//deconstructor;
	void doMove();
	void cleanTree();

private:
	Dotsboxes gameCopy;
	Node* root;
	Node* currentState;

	void select();				//select most promising node
	void expand();
	int simulate(double &ratio);
	void updateTree();

};

MCTSPlayer::MCTSPlayer(Dotsboxes* g){
	game = g;
	root = new Node(g->getHeight(), g->getWidth());
	currentState = root;
	gameCopy = *game;
}

MCTSPlayer::~MCTSPlayer(){
	delete root;
	root = currentState = NULL;
}


void MCTSPlayer::cleanTree(){
	root->cleanTree();
}

void MCTSPlayer::select(){
	currentState = root;
	int move = -1;
	while(!currentState->isLeafNode()){
		move = currentState->maxChild(true);
		currentState = currentState->children[move];
		gameCopy.doMove(move, true);
	}
}

void MCTSPlayer::expand(){
	if(currentState->getVisits() == 0){
		//do nothing, we want rollouts for this state
		return;
	}
	else{
		//We want to add a child for each possible move, then make currentState the first node and do rollout
		if(currentState->children.size() != 0){
			std::cout << "Er gaat iets fout in expand, we expanden terwijl er al kinderen zijn" << std::endl;
		}
		Node *node;
		for(int i = 0; i < gameCopy.numberOfEmptyEdges(); ++i){
			node = new Node(currentState);
			currentState->children.push_back(node);
		}

		if(currentState->children.size() > 0){//check if there is a child now (if not it's a end state)
			currentState = currentState->children[0];
			gameCopy.doMove(0, true);
		}
	}
	return;
}

int MCTSPlayer::simulate(double &ratio){
	// std::cout << "we simuleren voor node:" << currentState->nodeNumber << std::endl;
	return gameCopy.randomPlayout(ratio);
}



void MCTSPlayer::doMove(){
	currentState = root;
	int move = -1;
	double ratio = INT_MIN;
	int simResult = INT_MIN;
	int player = 0;
	bool isLeafNode = false;
	int bestMove = -1;
	if(game->whois() == true){
		player = 1;
	}
// std::cout << "numberofgames = " << numberOfGames << std::endl;
	for(int i = 0; i < gIterations; ++i){
		// std::cout << "BEGIN NUMBER OF GAMES: " << i << std::endl;
		gameCopy = *game;
		//selection of node to expand or roll out (changes currentRoot and gamecopy accordingly)
		select();
		//expand if needed
		expand();
		//simulate
		simResult = simulate(ratio);
	// 	//update the tree
		if(simResult == player){													//win for MCTS player
			currentState->backPropagate(1, 0, 0);
			// std::cout << "simresult == player!!!!!" << std::endl;
		}
		else if(simResult != player && simResult != 2){		//loss for MCTS player
			currentState->backPropagate(0, 1, 0);
			// std::cout << "simresult != player???????" << std::endl;
		}
		else if(simResult == 2){													//tie
			currentState->backPropagate(0, 0, 1);
		}
		// root->printTree();

	}
	if(gMCTSprint == true){
		root->printTree();
		std::cout << "einde beurt-----------------------------------------------" << std::endl;
		root->printRoot();
		root->printAllChild();
	}

	if(!root->isConsistent()){
		std::cout << "root is not consistent" << std::endl;
	}
	// 	//goto: select node
	// }
	if(root->children[0] != NULL){
		bestMove = root->maxChild(false);
	}


	game->doMove(bestMove,0);
	currentState = root;
	cleanTree();

}
