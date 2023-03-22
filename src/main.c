#include<stdio.h>

unsigned int MAX = 4294967295;
int scanReturnValue;

typedef struct{
	unsigned int cammino;
	unsigned int numero_grafo;
}top;

typedef struct{
	unsigned int num;
	unsigned int key;
}nodo;

void readNewGraph(int dim, int* notConnected, int (*matrix)[dim]);
void printResults(int currentGraphNumber, int numberOfRankedElement, top maxheap[]);

int main(){
	char input[14], comando1[14]="AggiungiGrafo";
	int dim, numberOfRankedElement, i, j;
	scanReturnValue=scanf("%d %d", &dim, &numberOfRankedElement);
	top maxheap[numberOfRankedElement], temptop;
	int matrice[dim][dim], numerografo=0, size=0, r, l , min, padre, somma=0, max_size=0, max_temp, nonconnesso=0;
	nodo miniheap[dim], u, temp;
	
	scanReturnValue=scanf("%s", input);
	ciclo:
	while(input[0]==comando1[0]){
		readNewGraph(dim, &nonconnesso, matrice);
		numerografo++;
		if(nonconnesso==0){
			somma=matrice[0][1]*(dim-1);
			goto insert;
		}
		nonconnesso=0;
		
		size=dim;
		miniheap[0].key=0;
		miniheap[0].num=0;
		for(i=1;i<dim;i++){
			miniheap[i].key=MAX;
			miniheap[i].num=i;
		}
		while(size>0 && miniheap[0].key!=MAX){
			u=miniheap[0];
			miniheap[0]=miniheap[size-1];
			miniheap[size-1]=u;
			i=0;
			size=size-1;
			somma=somma+miniheap[size].key;

		while((2*(i+1)-1)<size){
			l=(2*(i+1))-1;
			r=(2*(i+1));
			if(l<size && miniheap[l].key<miniheap[i].key){
				min=l;
			}
			else min=i;
			if(r<size && miniheap[r].key<miniheap[min].key){
				min=r;
			}
			if(min!=i){
				temp=miniheap[i];
				miniheap[i]=miniheap[min];
				miniheap[min]=temp;
				i=min;
				l=(2*(i+1))-1;
				r=(2*(i+1));
			}
			else i=size;
		}
	
		for(i=0;i<size;i++){
			j=miniheap[i].num;
			if(matrice[u.num][j]!=0 && miniheap[i].key>(u.key+matrice[u.num][j])){
				miniheap[i].key=(u.key+matrice[u.num][j]);
				j=i;
				while(j>0 && miniheap[((j+1)/2)-1].key>miniheap[j].key){
					padre=((j+1)/2)-1;
					temp=miniheap[padre];
					miniheap[padre]=miniheap[j];
					miniheap[j]=temp;
					j=padre;
				}
			}
		}
	}

		insert:
		if(max_size<numberOfRankedElement){
			i=max_size;
			max_size++;
			maxheap[max_size-1].cammino=somma;
			maxheap[max_size-1].numero_grafo=numerografo-1;
			while(i>0 && maxheap[((i+1)/2)-1].cammino<maxheap[i].cammino){
				temptop=maxheap[((i+1)/2)-1];
				maxheap[((i+1)/2)-1]=maxheap[i];
				maxheap[i]=temptop;
				i=((i+1)/2)-1;
			}
		}
		else{
			if(maxheap[0].cammino>somma){
				maxheap[0].cammino=somma;
				maxheap[0].numero_grafo=numerografo-1;
				i=0;
				while((2*(i+1)-1)<numberOfRankedElement){
					l=(2*(i+1))-1;
					r=(2*(i+1));
					if(maxheap[l].cammino>maxheap[i].cammino){
						max_temp=l;
					}
					else max_temp=i;
					if(r<numberOfRankedElement && maxheap[r].cammino>maxheap[max_temp].cammino){
						max_temp=r;
					}
					if(max_temp!=i){
						temptop=maxheap[i];
						maxheap[i]=maxheap[max_temp];
						maxheap[max_temp]=temptop;
						i=max_temp;
						l=(2*(i+1))-1;
						r=(2*(i+1));
					}
					else i=numberOfRankedElement;
				}
			}
		}
		somma=0;
		scanReturnValue=scanf("%s", input);
	}

	printResults(numerografo, numberOfRankedElement, maxheap);

	scanReturnValue=scanf("%s", input);
	if(input[0]==comando1[0]){
		printf("\n");
		goto ciclo;
	}
	
	printf("\n");
	if(scanReturnValue==-2){
		printf("Errore\n");
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

void printResults(int currentGraphNumber, int numberOfRankedElement, top maxheap[]){
	int counter;

	if(currentGraphNumber > numberOfRankedElement){
		for(counter = 0; counter < numberOfRankedElement - 1; counter++){
			printf("%d ", maxheap[counter].numero_grafo);
		}
		printf("%d", maxheap[numberOfRankedElement - 1].numero_grafo);
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
