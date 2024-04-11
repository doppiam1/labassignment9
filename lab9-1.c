#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int	id;
	char name;
	int	order;
};

struct Node {
    struct RecordType data;
    struct Node* next;
};

// Fill out this structure
struct HashType
{
    struct Node* nodes[101];
    int nodesSize[101];
};

// Compute the hash function
int hash(int x)
{
    int hashSize = 101;
    return x % hashSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, " %c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	for (int i = 0; i < 101; i++)
	{
		struct Node* currentNode = pHashArray->nodes[i];
		if (currentNode == NULL)
		{
			continue;
		}
		printf("Index %d = ", i);

		while (currentNode != NULL)
		{
			printf("id: %d, name: %c, order: %d -> ", currentNode->data.id, currentNode->data.name, currentNode->data.order);
			currentNode = currentNode->next;
		}
		printf("NULL\n");
	}
}

void initializeHash(struct HashType* hashTable)
{
    for (int i = 0; i < 101; i++)
    {
        hashTable->nodes[i] = NULL;
        hashTable->nodesSize[i] = 0;
    }
}

void insertRecord(struct HashType* hashTable, struct RecordType record)
{
    int i = hash(record.id);

    struct Node* newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation error\n");
        exit(-1);
    }

    newNode->data = record;
    newNode->next = NULL;

    if (hashTable->nodes[i] == NULL)
    {
        hashTable->nodes[i] = newNode;
    }
    else
    {
        newNode->next = hashTable->nodes[i];
        hashTable->nodes[i] = newNode;
    }
    hashTable->nodesSize[i]++;
}

int main(void)
{
    struct HashType hashTable;
	struct RecordType *pRecords;
	int recordSz = 0;
	initializeHash(&hashTable);

	recordSz = parseData("input.txt", &pRecords);

	for (int i = 0; i < recordSz; i++)
	{
	   insertRecord(&hashTable, pRecords[i]);
	}
	printRecords(pRecords, recordSz);
	displayRecordsInHash(&hashTable, 101);

	// Your hash implementation

	free(pRecords);
}
