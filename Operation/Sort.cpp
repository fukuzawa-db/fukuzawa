#include"Sort.h"

Sort::Sort(OPERATION_NODE *sortNode_, unsigned int sortNum_  ){
	sortNode = new OPERATION_NODE[sortNum_];
	sortNum = sortNum_;
	memcpy(sortNode, sortNode_, sizeof(OPERATION_NODE) * sortNum);
	readIndex = 0;
	preNode = NULL;
}

Sort::~Sort(){
	if(newDbNode != NULL){
		delete newDbNode->db;
		delete newDbNode;
	}
}

void Sort::init(DbEnv *env_){
	assert(preOperator != NULL);
	env = env_;
	preOperator->init(env);
	attriNum = preOperator->getAttriNum();
	initAttriRec(attriNum);
	preOperator->getAttriRec(attriRec, attriNum);
	setSortPosition();
	initPosVal();
	initSortFlag = false;
}


void Sort::setSortPosition(void){
	sortPosition = new SORT_POS[sortNum];
	for(unsigned int i = 0; i < sortNum; i++){
		if(sortNode[i].attributeID == 0 && sortNode[i].tableID == 0){
			sortPosition[i].pos = sortNode[i].position;
			sortPosition[i].option = sortNode[i].option;
		}else{
			for(unsigned int j = 0; j < attriNum ; j++){
				if(sortNode[i].attributeID == attriRec[j]->attributeID && sortNode[i].tableID == attriRec[j]->tableID){
					sortPosition[i].pos = j;
					sortPosition[i].option = sortNode[i].option;
					break;
				}
			}
		}
	}
	delete[] sortNode;
}



unsigned int  Sort::getAttriNum(void){
	return attriNum;
}

void Sort::getAttriRec(ATTRIBUTE_REC **attriRec_, unsigned int attriNum_){
	for(unsigned int i = 0; i < attriNum_; i++){
		memcpy(attriRec_[i], attriRec[i], sizeof(ATTRIBUTE_REC));
	}
}

int Sort::getRow(PosVal **pv_, unsigned int attriNum_){
	if(initSortFlag == false){
		initSort();
		initSortFlag = true;
	}
	
	if(inMemFlag == true){
		if(readIndex >= listNodeNum)return (-1);
		for(unsigned int i = 0; i < attriNum; i++){
			*pv_[i] = *sortArray[readIndex]->pv[i];
		}
		readIndex++;
	}else{
		readIndex++;
		return readDb->getRow(pv_, attriNum_);
	}
	return 0;
}



void Sort::initSort(){
	margeFileNum = 0;
	inMemFlag = true;
	rootDbNode = NULL;
	newDbNode = NULL;
	tailDbNode = NULL;

	int buffSize = getDataBufSize();
	char dataBuffer[buffSize];
	unsigned int dataSize;

	while(1){
		getList();
		currentNode = rootNode;
		sortArray = new RECORD_LIST_NODE*[listNodeNum];
		for(unsigned int i =0 ; i < listNodeNum ; i++){
			sortArray[i] = currentNode;
			currentNode = currentNode->next;
		}
		assert(currentNode == NULL);
		qsortList(sortArray, 0, listNodeNum-1);

		if(preNode == NULL){
			if(inMemFlag == true)break;
			
			newDbNode = new DB_LIST_NODE;
			newDbNode->next = rootDbNode;
			rootDbNode = newDbNode;
			tmpnam(tmpFileName);
			fileName = tmpFileName;
			newDbNode->db = new BDBOpe(env, fileName);
			newDbNode->db->open();
			for(unsigned int i = 1; i <= listNodeNum; i++){
				dataSize = getDataBuffer(dataBuffer, buffSize, sortArray[i-1]);
				newDbNode->db->writeRecord(&i, sizeof(i), dataBuffer, dataSize, false);
			}
			newDbNode->db->close();			
			deleteRecList(rootNode);
			delete []sortArray;
			margeFileNum++;
			break;
		}

		tmpnam(tmpFileName);
		fileName = tmpFileName;
		if(rootDbNode == NULL){
			newDbNode = new DB_LIST_NODE;
			newDbNode->next = NULL;
			newDbNode->db = new BDBOpe(env, fileName);
			rootDbNode = newDbNode;
			tailDbNode = rootDbNode;
			inMemFlag = false;
		}else{
			newDbNode = new DB_LIST_NODE;
			newDbNode->next = rootDbNode;
			rootDbNode = newDbNode;
			newDbNode->db = new BDBOpe(env, fileName);
		}

		newDbNode->db->open();
		unsigned int dataSize;
		for(unsigned int i = 1; i <= listNodeNum; i++){
			dataSize = getDataBuffer(dataBuffer, buffSize, sortArray[i-1]);
			newDbNode->db->writeRecord(&i, sizeof(i), dataBuffer, dataSize, false);
		}
		newDbNode->db->close();			
		deleteRecList(rootNode);
		delete []sortArray;
		margeFileNum++;
	}

	if(inMemFlag == false){
		margeEndFlag = false;
		pivotDbNode = rootDbNode;
		Scan *readNode[MAX_MARGE_BLOCK];
		PosVal **scanPV[MAX_MARGE_BLOCK];
		RECORD_LIST_NODE extractPV;


		while(1){
			preDbNode = pivotDbNode;

			tmpnam(tmpFileName);
			fileName = tmpFileName;
			newDbNode = new DB_LIST_NODE;
			newDbNode->db = new BDBOpe(env, fileName);
			newDbNode->db->open();

			for(unsigned int i = 0; i < MAX_MARGE_BLOCK; i++){
				pivotDbNode->db->reopen();
				readNode[i] = new Scan(pivotDbNode->db, attriRec, attriNum);
				initPosVal(scanPV[i]);
				if(readNode[i]->getRow(scanPV[i], attriNum) != 0){
					cout << "ERROR NoEntity \n";
				}

				if(pivotDbNode == tailDbNode){
					margeEndFlag = true;
					for(i++ ;i < MAX_MARGE_BLOCK; i++){
						readNode[i] = NULL;
						scanPV[i] = NULL;
					}
					break;
				}
			 	assert(pivotDbNode->next != NULL);
				pivotDbNode = pivotDbNode->next;
			}

			int posIndex = -1;
			unsigned int key = 1;
			while(1){
				for(unsigned int i = 0; i < MAX_MARGE_BLOCK; i++){
					if(scanPV[i] != NULL && posIndex == -1){
						extractPV.pv = scanPV[i];
						posIndex = i;
					}else if(scanPV[i] != NULL){
	
						for(unsigned int j = 0; j < sortNum; j++){
							if(sortPosition[j].option == 0){
								if(*extractPV.pv[sortPosition[j].pos] > scanPV[i][sortPosition[j].pos]){
									extractPV.pv = scanPV[i];
									posIndex = i;
									break;
								}
							}else if(sortPosition[j].option == 1){
								if(*extractPV.pv[sortPosition[j].pos] < scanPV[i][sortPosition[j].pos]){
									extractPV.pv = scanPV[i];
									posIndex = i;
									break;
								}
							}else{
								cout << "ERROR OPTION" << endl;
								exit(-1);
							}
							if(*extractPV.pv[sortPosition[j].pos] != scanPV[i][sortPosition[j].pos])
								break;
						}
					}
				}


				if(posIndex == -1)break;
				dataSize = getDataBuffer(dataBuffer, buffSize, &extractPV);
				newDbNode->db->writeRecord(&key, sizeof(key), dataBuffer, dataSize, false);
				if(readNode[posIndex]->getRow(scanPV[posIndex], attriNum) != 0){
					scanPV[posIndex] = NULL;
				}
				posIndex = -1;
				key ++;
			}

			for(int i = 0; i < MAX_MARGE_BLOCK; i++)
				delete readNode[i];
			while(preDbNode != pivotDbNode){
				tmpDbNode = preDbNode;
				preDbNode = preDbNode->next;
				tmpDbNode->db->close();
				tmpDbNode->db->remove();
				delete tmpDbNode->db;
				delete tmpDbNode;
			}
		
			if(margeEndFlag == true){
				readDb = new Scan(newDbNode->db, attriRec, attriNum);
				break;
			}

			tailDbNode->next = newDbNode;
			tailDbNode = tailDbNode->next;
			newDbNode->db->close();
			newDbNode = NULL;
		
		}
	}
}


void Sort::qsortList(RECORD_LIST_NODE* array_[], int left_, int right_){
	int x = left_;
	int y = right_;
	RECORD_LIST_NODE *pivot;

	pivot = array_[(left_ + right_) / 2];
	while(1){
/* 		sort         */
		while(1){
			sortEqualFlag = true;
			for(unsigned int i = 0; i < sortNum ; i++){
				if(sortPosition[i].option == 0){
					if((*(sortArray[x]->pv[sortPosition[i].pos]) > pivot->pv[sortPosition[i].pos]))
						goto END_LEFT;
				}else if(sortPosition[i].option == 1){
					if((*(sortArray[x]->pv[sortPosition[i].pos]) < pivot->pv[sortPosition[i].pos]))
						goto END_LEFT;
				}else{
					cout << "ERROR OPTION" << endl;
					exit(-1);
				}	
				if(*(sortArray[x]->pv[sortPosition[i].pos]) != pivot->pv[sortPosition[i].pos]){
					sortEqualFlag = false;
					break;
				}
			}
			if(sortEqualFlag == true)
				break;
			x++;
		}
END_LEFT:

		while(1){
			sortEqualFlag = true;
			for(unsigned int i = 0; i < sortNum; i++){
				if(sortPosition[i].option == 0){
					if(*pivot->pv[sortPosition[i].pos] > sortArray[y]->pv[sortPosition[i].pos])
						goto END_RIGHT;
				}else if(sortPosition[i].option == 1){
					if(*pivot->pv[sortPosition[i].pos] < sortArray[y]->pv[sortPosition[i].pos])
						goto END_RIGHT;
				}else{
					cout << "ERROR OPTION" << endl;
					exit(-1);
				}	
				if(*(sortArray[y]->pv[sortPosition[i].pos]) != pivot->pv[sortPosition[i].pos]){
					sortEqualFlag = false;
					break;
				}
			}
			if(sortEqualFlag == true)
				break;
			y--;
		}
END_RIGHT:

		if(x >= y)break;
		swap(array_, x, y);
		x++;
		y--;
	}

	if(left_ < x-1 )
		qsortList(array_, left_, x-1);
	if(y + 1 < right_)
		qsortList(array_, y + 1, right_);
}

void Sort::swap(RECORD_LIST_NODE *array_[], int i, int j){
	RECORD_LIST_NODE *temp;
	temp = array_[i];
	array_[i] = array_[j];
	array_[j] = temp;
}

RECORD_LIST_NODE *Sort::getList(void){
	listNodeNum = 0;
	bool rootInitFlag = false;

	if(preNode != NULL){
		rootNode = preNode;
		rootInitFlag = true;
		listNodeNum++;
		currentNode = rootNode;
		work_space += getPosValSize(rootNode->pv);
	}else{
		rootNode = new RECORD_LIST_NODE;
		initPosVal(rootNode->pv);
	}
	preNode = NULL;
	unsigned int nodeSize;
	int returnCode;

	while(1){
		if(rootInitFlag == false){
			rootNode->next = NULL;
			returnCode = preOperator->getRow(rootNode->pv, attriNum);
			if(returnCode != 0){
				delete rootNode;
				rootNode = NULL;
				return NULL;
			}
			work_space = 0;
			work_space += getPosValSize(rootNode->pv);
			listNodeNum++;
			currentNode = rootNode;
			rootInitFlag = true;
		}else{
			currentNode->next = new RECORD_LIST_NODE;
			initPosVal(currentNode->next->pv);
			currentNode->next->next = NULL;
			returnCode = preOperator->getRow(currentNode->next->pv, attriNum);
			if(returnCode != 0){
				deleteRecList(currentNode->next);
				currentNode->next = NULL;
				preNode = NULL;
				return rootNode;
			}
			nodeSize = getPosValSize(currentNode->next->pv);
			if(work_space + nodeSize > MAX_WORK_SPACE){
				preNode = currentNode->next;
				currentNode->next = NULL;
				work_space = nodeSize;
				return rootNode;
			}
			currentNode = currentNode->next;
			listNodeNum++;
			work_space += nodeSize;
		}
	}
}

void Sort::deleteRecList(RECORD_LIST_NODE *node){
	RECORD_LIST_NODE *p, *np;
	p=node;
	do{
		np = p->next;
		for(unsigned int i = 0; i < attriNum; i++)
			delete p->pv[i];
		delete[] p->pv;
		delete p;
		p = np;
	}while(p != NULL);
		
	/*
	if(node->next != NULL)deleteRecList(node->next);
	for(unsigned int i = 0; i < attriNum; i++)
		delete node->pv[i];
	
	delete[] node->pv;
	delete node;
	*/
}


unsigned int Sort::getPosValSize(PosVal **pv){
	unsigned int totalSize = 0;
	for(unsigned int i = 0; i < attriNum; i++){
		totalSize += pv[i]->getSize();
		if(pv[i]->type == VARIABLE_TEXT)totalSize++;
	}
	return totalSize;
}

unsigned int Sort::getDataBufSize(void){
	int size = 0;
	for(unsigned int i = 0; i < attriNum; i++){
		size += attriRec[i]->dataLength;
		if(attriRec[i]->dataType == VARIABLE_TEXT)size++;
	}
	return size;
}


unsigned int Sort::getDataBuffer(char *dataBuffer_, unsigned int dataBufSize_, RECORD_LIST_NODE *node)
{
	unsigned int size = 0;

	for(int i = 0; i < (int)attriNum; i++){
		switch(attriRec[i]->dataType){
			case INT:
				assert(size + sizeof(int) <= dataBufSize_);
				memcpy(dataBuffer_ + size, node->pv[i]->value, sizeof(int));
				size += sizeof(int);
				break;

			case LONG:
				assert(size + sizeof(long) <= dataBufSize_);
				memcpy(dataBuffer_ + size, node->pv[i]->value, sizeof(long));
				size += sizeof(long);
				break;

			case FLOAT:
				assert(size + sizeof(float) <= dataBufSize_);
				memcpy(dataBuffer_ + size, node->pv[i]->value, sizeof(float));
				size += sizeof(float);
				break;

			case DOUBLE:	
				assert(size + sizeof(double) <= dataBufSize_);
				memcpy(dataBuffer_ + size, node->pv[i]->value, sizeof(double));
				size += sizeof(double);
				break;

			case FIXED_TEXT:
				assert(size + attriRec[i]->dataLength <= dataBufSize_);
				memcpy(dataBuffer_ + size, node->pv[i]->value, attriRec[i]->dataLength);
				size += attriRec[i]->dataLength;
				break;

			case VARIABLE_TEXT:
				assert(size + strlen((char *)node->pv[i]->value) <= dataBufSize_);
				strcpy(dataBuffer_ + size, (char *)(node->pv[i]->value));
				size += strlen((char *)(node->pv[i])->value) + 1;
				break;

			case DATE:
				assert(size + attriRec[i]->dataLength <= dataBufSize_);
				memcpy(dataBuffer_ + size, (char *)node->pv[i]->value, attriRec[i]->dataLength);
				size += attriRec[i]->dataLength;
				break;

			default:
				cout << "Error insertVoidData" << endl;
				exit (EXIT_FAILURE);
		}
	}
	return size;
}

