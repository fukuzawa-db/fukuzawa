#include"MargeJoin.h" 

MargeJoin::MargeJoin(Operator *innerOpeNode_, Operator *outerOpeNode_, JOIN_OPERATION_NODE *joinOpeNode_, unsigned int nodeNum_){
	innerOpeNode = innerOpeNode_;
	outerOpeNode = outerOpeNode_;
	preOperator = NULL;
	joinOpeNode = joinOpeNode_;
	nodeNum = nodeNum_;
}

MargeJoin::~MargeJoin(){
}


void MargeJoin::init(DbEnv *env_){
	assert(innerOpeNode != NULL && outerOpeNode != NULL);
	env = env_;
	innerOpeNode->init(env);
	outerOpeNode->init(env);
	innerAttriNum = innerOpeNode->getAttriNum();
	outerAttriNum = outerOpeNode->getAttriNum();
	attriNum = innerAttriNum + outerAttriNum;
	initAttriRec(attriNum);

	innerOpeNode->getAttriRec(attriRec, innerAttriNum);
	outerOpeNode->getAttriRec(attriRec + innerAttriNum, outerAttriNum);
	initPosVal();

	setJoinPos();
	getRowFlag = 0;
	rootNode = NULL;
}

int MargeJoin::getRow(PosVal **pv_, unsigned int pvNum_){
	int returnCode, returnCmp;
	unsigned int i;

	if(getRowFlag == 0){
		returnCode = innerOpeNode->getRow(pv, innerAttriNum);
		assert(returnCode == 0);
		returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
		assert(returnCode == 0);
		getRowFlag = 1;	
	}
	if(getRowFlag == -1){
		return -1;
	}
	if(getRowFlag >= 3){
		if(listIndex == NULL){
			returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode != 0){
				getRowFlag = -1;
				return (-1);
			}else if(cmpPV(rootNode->pv, &pv[innerAttriNum]) == 0){
				listIndex = rootNode;
				for(i = 0; i < innerAttriNum; i++)
					*pv_[i] = *(listIndex->pv[i]);
				for(;i  < attriNum; i++)
					*pv_[i] = *pv[i];
				listIndex = listIndex->next;				
				return 0;
			}else if(getRowFlag == 4){
				getRowFlag = -1;
				return (-1);
			}else{
				getRowFlag = 1;
			}
		}else{
			for(i = 0; i < innerAttriNum; i++)
				*pv_[i] = *listIndex->pv[i];
			listIndex = listIndex->next;
			return 0;
		}	
	}

	while(1){
		returnCmp = cmpPV();
		
		if(returnCmp < 0){
			returnCode = innerOpeNode->getRow(pv, innerAttriNum);
			if(returnCode != 0){
				getRowFlag = -1;
				return (-1);
			}

		}else if(returnCmp > 0){
			returnCode = outerOpeNode->getRow(&pv[innerAttriNum], outerAttriNum);
			if(returnCode != 0){
				getRowFlag = -1;
				return (-1);
			}
			if(cmpPV(rootNode->pv, &pv[innerAttriNum]) == 0){
				listIndex = rootNode;
				for(i = 0; i < innerAttriNum; i++)
					*pv_[i] = *(listIndex->pv[i]);
				for(;i  < attriNum; i++)
					*pv_[i] = *pv[i];
				listIndex = listIndex->next;				
				getRowFlag = 3;
				return 0;
			}
		}else{
			if(rootNode != NULL && cmpInnerPV(rootNode->pv, pv) == 0){
				newNode = new PV_LIST;
				initPosVal(newNode->pv, 0, innerAttriNum -1);
				for(unsigned int j = 0; j < innerAttriNum; j++){
					*(newNode->pv[j]) = *pv[j];
				}
				newNode->next = NULL;
				lastNodePos->next = newNode;
				lastNodePos = newNode;
			}else{
				if(rootNode != NULL)
					deleteNode(rootNode, innerAttriNum);
				rootNode = new PV_LIST;
				initPosVal(rootNode->pv, 0, innerAttriNum -1);
				for(unsigned int j = 0; j < innerAttriNum; j++){
					*(rootNode->pv[j]) = *pv[j];
				}
				rootNode->next = NULL;
				lastNodePos = rootNode;
			}

			for(i = 0; i < attriNum; i++)
				*pv_[i] = *pv[i];

			
			returnCode = innerOpeNode->getRow(pv, innerAttriNum);
			if(returnCode != 0){
				listIndex = rootNode->next;
				getRowFlag = 4;
				return 0;
			}
			return 0;
		}			
	}	
}

unsigned int MargeJoin::getAttriNum(void){
	return attriNum;
}

void MargeJoin::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}


void MargeJoin::deleteNode(PV_LIST *node_, unsigned int pvNum_){
	if(node_->next != NULL)
		deleteNode(node_->next, pvNum_);

	for(unsigned int i = 0; i < pvNum_; i++)
		delete node_->pv[i];
	delete []node_->pv;

	delete node_;
}


void MargeJoin::setJoinPos(void){
	innerPos = new unsigned int[nodeNum];
	outerPos = new unsigned int[nodeNum];
	options = new unsigned int[nodeNum];

	unsigned int i;
	for(unsigned int j = 0; j < nodeNum; j++){
		assert(joinOpeNode[j].rightNode.option == joinOpeNode[j].leftNode.option);
		options[j] = joinOpeNode[j].rightNode.option;

		for(i = 0;i < innerAttriNum; i++){
			if(joinOpeNode[j].rightNode.attributeID == attriRec[i]->attributeID && joinOpeNode[j].rightNode.tableID == attriRec[i]->tableID){
				innerPos[j] = i;
				break;
			}
		}
		assert(i != innerAttriNum);

		for(i = innerAttriNum; i < attriNum; i++){
			if(joinOpeNode[j].leftNode.attributeID == attriRec[i]->attributeID && joinOpeNode[j].leftNode.tableID == attriRec[i]->tableID){
				outerPos[j] = i;
				break;
			}
		}
		assert(i != attriNum);
	}
}
		
int MargeJoin::cmpPV(void){
	for(unsigned int i = 0; i < nodeNum; i++){
		if(options[i] == 0){
			if(*pv[innerPos[i]] < pv[outerPos[i]]){
				return -1;
			}else if(*pv[innerPos[i]] > pv[outerPos[i]]){
				return 1;
			}
		}
		else if(options[i] == 1){
			if(*pv[innerPos[i]] < pv[outerPos[i]]){
				return 1;
			}else if(*pv[innerPos[i]] > pv[outerPos[i]]){
				return -1;
			}
		}
		else{
			cout << "ERROR OPTION" << endl;
			exit(-1);
		}
	}
	return 0;
}

int MargeJoin::cmpPV(PosVal **innerPV_, PosVal **outerPV_){
	for(unsigned int i = 0; i < nodeNum; i++){
		if(options[i] == 0){
			if(*innerPV_[innerPos[i]] < outerPV_[outerPos[i] - innerAttriNum]){
				return -1;
			}else if(*innerPV_[innerPos[i]] > outerPV_[outerPos[i] - innerAttriNum]){
				return 1;
			}
		}
		else if(options[i] == 1){
			if(*innerPV_[innerPos[i]] > outerPV_[outerPos[i] - innerAttriNum]){
				return 1;
			}else if(*innerPV_[innerPos[i]] > outerPV_[outerPos[i] - innerAttriNum]){
				return -1;
			}
		}
		else{
			cout << "ERROR OPTION" << endl;
			exit(-1);
		}
	}
	return 0;
}

int MargeJoin::cmpInnerPV(PosVal **innerPV1_, PosVal **innerPV2_){
	for(unsigned int i = 0; i < nodeNum; i++){
		if(options[i] == 0){
			if(*innerPV1_[innerPos[i]] < innerPV2_[innerPos[i]]){
				return -1;
			}else if(*innerPV1_[innerPos[i]] > innerPV2_[innerPos[i]]){
				return 1;
			}
		}
		else if(options[i] == 1){
			if(*innerPV1_[innerPos[i]] > innerPV2_[innerPos[i]]){
				return 1;
			}else if(*innerPV1_[innerPos[i]] > innerPV2_[innerPos[i]]){
				return -1;
			}
		}
		else{
			cout << "ERROR OPTION" << endl;
			exit(-1);
		}
	}
	return 0;
}

