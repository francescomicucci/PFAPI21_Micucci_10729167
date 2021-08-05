#include<stdio.h>
#include<string.h>

const unsigned int MAX=4294967295;

typedef struct{
	int num;
	int key;
}nodo;

typedef struct{
	int size;
	nodo miniheap[4294967295];
}vettore;

typedef struct{
	int cammino;
	int numero_grafo;
}top;

vettore v;

void minheapify(int i){ 
	int l=(2*(i+1))-1, r=(2*(i+1)), min;
	nodo temp;
	
	if (l<=v.size && v.miniheap[l].key<v.miniheap[i].key){
		min=l;
	}
	else min=i;
	if (r<=v.size && v.miniheap[r].key<v.miniheap[min].key){
		min=r;
	}
	if(min!=i){
		temp=v.miniheap[i];
		v.miniheap[i]=v.miniheap[min];
		v.miniheap[min]=temp;
		minheapify(min);
	}
}


nodo heapextractmin(){ 
	nodo min;
	min.key=-1;
	
	if(v.size>0){ 
		min=v.miniheap[0];
		v.miniheap[0]=v.miniheap[v.size-1];  
		v.size=v.size-1;
		minheapify(0);
		return min; 
	}
	return min;
}

void heapdecreasekey(int corrente, nodo nodo_corrente){
	nodo temp;
	int padre;
	if(nodo_corrente.key<=v.miniheap[corrente].key){
		v.miniheap[corrente].key=nodo_corrente.key;
		while(corrente>0 && v.miniheap[((corrente+1)/2)-1].key>v.miniheap[corrente].key){
			padre=((corrente+1)/2)-1;
			temp=v.miniheap[padre];
			v.miniheap[padre]=v.miniheap[corrente];
			v.miniheap[corrente]=temp;
			corrente=padre;
		}
	}
}

void minheapinsert(nodo nodo_corrente){
	v.miniheap[v.size].key=MAX;
	v.miniheap[v.size].num=nodo_corrente.num;
	v.size++;
	heapdecreasekey(v.size-1, nodo_corrente);
}

//Main
int main(){
	//Variabili locali
	char input[14], comando1[14]="AggiungiGrafo";
	int d, k, numerografo=0;
	int i, j, matrice[MAX][MAX], somma=0, posizione_corrente;
	nodo u, node[MAX];
	top ordine[MAX], temptop1, temptop2;	
	
	//Programma
	scanf("%d %d", &d, &k);
//	printf("%d, %d\n", d, k);
	scanf("%s", input);
	
	ordine[0].cammino=MAX;
	while(strcmp(input, comando1)==0){
		for(i=0;i<d;i++){
			for(j=0;j<d-1;j++){
				scanf("%d,", &matrice[i][j]);
			}
			scanf("%d\n", &matrice[i][j]);
		}
		
		numerografo++;
		
//		for(i=0;i<d;i++){
//			for(j=0;j<d-1;j++){
//				printf("%d, ", matrice[i][j]);
//			}
//			printf("%d\n", matrice[i][j]);
//		}
	
	v.size=0;
	for(i=0;i<d;i++){
		node[i].num=i;
	}	
    node[0].key=0;
	minheapinsert(node[0]);

	for(i=1;i<d;i++){
	    node[i].key=MAX;
	    minheapinsert(node[i]);
	}

	while(v.size>0){
		u=heapextractmin();
		for(i=0;i<d;i++){
			if(matrice[u.num][i]!=0){
				if(node[i].key>(node[u.num].key+matrice[u.num][i])){
					node[i].key=node[u.num].key+matrice[u.num][i];
					for(j=0;j<d;j++){
						if(node[i].num==v.miniheap[j].num){
							posizione_corrente=j;
						}
					}
					heapdecreasekey(posizione_corrente, node[i]);
				}
			}
		}
		}
	
	for(i=1;i<d;i++){
		if(node[i].key==MAX){
			node[i].key=0;
		}
		somma=somma+node[i].key;
	}
	
//	printf("%d\n", somma);
	
	
	
	for(i=0;i<numerografo;i++){
		if(ordine[i].cammino>somma){
			temptop1=ordine[i];
			ordine[i].cammino=somma;
			ordine[i].numero_grafo=numerografo;
			i++;
			while(i<numerografo){
				temptop2=ordine[i];
				ordine[i]=temptop1;
				temptop1=temptop2;
				i++;
			}
		}
	}
	somma=0;

	scanf("%s", input);
	}
	
	for(i=0;i<(numerografo-1);i++){
		printf("%d ",ordine[i].numero_grafo);
	}
}
