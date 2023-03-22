#include<stdio.h>

typedef struct{
	unsigned int path;
	unsigned int graphNumber;
}top;

typedef struct{
	unsigned int num;
	unsigned int key;
}node;

unsigned int MAX = 4294967295;
int scanReturnValue, dim, numberOfRankedElement, currentGraphNumber = 0;

void readNewGraph(int dim, int* notConnected, int (*matrix)[dim]);
int dijkstraAlgorithm(int dim, int (*matrix)[dim]);
void rankGraph(int sum, int numberOfRankedElement, int currentGraphNumber, int* maxheapSize, top maxheap[]);
void printResults(int currentGraphNumber, int numberOfRankedElement, top maxheap[]);

int main(){
	char input[14], command1[14] = "AggiungiGrafo";
	scanReturnValue = scanf("%d %d", &dim, &numberOfRankedElement);
	int matrix[dim][dim], currentMaxheapSize = 0, notConnected = 0, newRanking = 0;
	top maxheap[numberOfRankedElement];
	scanReturnValue = scanf("%s", input);

	while(newRanking == 0){
		newRanking = 1;
		while(input[0] == command1[0]){
			readNewGraph(dim, &notConnected, matrix);
			currentGraphNumber++;
			if(notConnected == 0){
				rankGraph(matrix[0][1]*(dim-1), numberOfRankedElement, currentGraphNumber, &currentMaxheapSize, maxheap);
				scanReturnValue = scanf("%s", input);
				continue;
			}
			notConnected = 0;
			rankGraph(dijkstraAlgorithm(dim, matrix), numberOfRankedElement, currentGraphNumber, &currentMaxheapSize, maxheap);
			scanReturnValue = scanf("%s", input);
		}

		printResults(currentGraphNumber, numberOfRankedElement, maxheap);

		scanReturnValue = scanf("%s", input);
		if(input[0] == command1[0]){
			printf("\n");
			newRanking = 0;
		}
	}

	printf("\n");
	if(scanReturnValue==-2){
		printf("Error!\n");
	}
	return 0;
}

void readNewGraph(int dim, int* notConnected, int (*matrix)[dim]){
	int rowNum, colNum, characterPosition, n, value;
	char* returnCondition;
	char row[5000];

	returnCondition = fgets(row, 5000, stdin);
	for(rowNum = 0; rowNum < dim; rowNum++){
		if(rowNum == 0){
			returnCondition = fgets(row, 5000, stdin);
			value = 0;
			characterPosition = 0;
			colNum = 2;
			while(row[characterPosition] <= '9' && row[characterPosition] >= '0'){
				characterPosition++;
			}
			characterPosition++;
			n = characterPosition;
			while(row[characterPosition] <= '9' && row[characterPosition] >= '0'){
				characterPosition++;
			}
			while(n < characterPosition){
				value = value*10+(row[n]-'0');
				n++;
			}
			matrix[0][1] = value;
			n++;
			characterPosition++;
			while(colNum < dim){
				value = 0;
				while(row[characterPosition] <= '9' && row[characterPosition] >= '0'){
					characterPosition++;
				}
				while(n < characterPosition){
					value = value * 10 + (row[n] - '0');
					n++;
				}
				if(value != matrix[0][1]){
					*notConnected =- 1;
				}
				matrix[rowNum][colNum] = value;
				n++;
				if(row[characterPosition] == ','){
					characterPosition++;
				}
				colNum++;
			}
		}
		else{
			if(*notConnected == 0){
				returnCondition = fgets(row, 5000, stdin);
			}
			else{
				returnCondition = fgets(row, 5000, stdin);
				characterPosition = 0;
				colNum = 0;
				n = 0;
				while(colNum < dim){
					value = 0;
					while(row[characterPosition] <= '9' && row[characterPosition] >= '0'){
						characterPosition++;
					}
					while(n < characterPosition){
						value = value * 10 + (row[n] - '0');
						n++;
					}
					matrix[rowNum][colNum] = value;
					n++;
					if(row[characterPosition] == ','){
						characterPosition++;
					}
					colNum++;
				}
			}
		}
	}
	scanReturnValue =* returnCondition;
}

int dijkstraAlgorithm(int dim, int (*matrix)[dim]){
	int sum = 0, size = dim, min, left, right, father;
	int i, j;
	node miniheap[dim], temp, root;

	miniheap[0].key = 0;
	miniheap[0].num = 0;
	for(int counter = 1; counter < dim; counter++){
		miniheap[counter].key = MAX;
		miniheap[counter].num = counter;
	}

	while(size > 0 && miniheap[0].key != MAX){
		root = miniheap[0];
		miniheap[0]	= miniheap[size-1];
		miniheap[size-1] = root;
		i = 0;
		size = size-1;
		sum = sum + miniheap[size].key;

		while((2*(i+1)-1) < size){
			left  = (2*(i+1))-1;
			right = (2*(i+1));
			min   = i;

			if(left < size && miniheap[left].key < miniheap[i].key){ min = left; }
			if(right < size && miniheap[right].key < miniheap[min].key){ min = right; }
			if(min != i){
				temp 			= miniheap[i];
				miniheap[i] 	= miniheap[min];
				miniheap[min]   = temp;
				i				= min;
				left  			= (2*(i+1))-1;
				right 			= (2*(i+1));
			}
			else i = size;
		}

		for(i = 0; i < size; i++){
			j = miniheap[i].num;
			if(matrix[root.num][j] != 0 && miniheap[i].key > root.key+matrix[root.num][j]){
				miniheap[i].key = root.key + matrix[root.num][j];
				j = i;
				while(j > 0 && miniheap[((j+1)/2)-1].key > miniheap[j].key){
					father = ((j+1)/2)-1;
					temp = miniheap[father];
					miniheap[father] = miniheap[j];
					miniheap[j] = temp;
					j = father;
				}
			}
		}
	}

	return sum;
}

void rankGraph(int sum, int numberOfRankedElement, int currentGraphNumber, int* maxheapSize, top maxheap[]){
	int left, right, tempMax, i;
	top temp;
	
	if(*maxheapSize < numberOfRankedElement){
		i = *maxheapSize;
		*maxheapSize = i + 1;
		maxheap[*maxheapSize - 1].path = sum;
		maxheap[*maxheapSize - 1].graphNumber = currentGraphNumber - 1;
		while(i > 0 && maxheap[((i+1)/2)-1].path < maxheap[i].path){
			temp = maxheap[((i+1)/2)-1];
			maxheap[((i+1)/2)-1] = maxheap[i];
			maxheap[i] = temp;
			i = ((i+1)/2)-1;
		}
	}
	else{
		if(maxheap[0].path > sum){
			maxheap[0].path = sum;
			maxheap[0].graphNumber = currentGraphNumber - 1;
			i = 0;
			while((2*(i+1)-1) < numberOfRankedElement){
				left = (2*(i+1))-1;
				right = (2*(i+1));
				if(maxheap[left].path > maxheap[i].path){
					tempMax = left;
				}
				else tempMax = i;
				if(right < numberOfRankedElement && maxheap[right].path > maxheap[tempMax].path){
					tempMax = right;
				}
				if(tempMax != i){
					temp = maxheap[i];
					maxheap[i] = maxheap[tempMax];
					maxheap[tempMax] = temp;
					i = tempMax;
					left = (2*(i+1))-1;
					right = (2*(i+1));
				}
				else i = numberOfRankedElement;
			}
		}
	}
}

void printResults(int currentGraphNumber, int numberOfRankedElement, top maxheap[]){
	int counter;

	if(currentGraphNumber > numberOfRankedElement){
		for(counter = 0; counter < numberOfRankedElement - 1; counter++){
			printf("%d ", maxheap[counter].graphNumber);
		}
		printf("%d", maxheap[numberOfRankedElement - 1].graphNumber);
	}
	else{
		if(currentGraphNumber!=0){
			for(counter = 0; counter < currentGraphNumber - 1; counter++){
				printf("%d ", counter);
			}
			printf("%d", counter);
		}
	}
}
