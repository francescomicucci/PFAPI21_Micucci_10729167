#include<stdio.h>
#include<string.h>

const unsigned int MAX=429496725;

typedef struct{
	int cammino;
	int numero_grafo;
}top;

typedef struct{
	int num;
	int key;
}nodo;

nodo* minheapify(int i, nodo v[], int lunghezza){ 
	int l=(2*(i+1))-1, r=(2*(i+1)), min;
	nodo temp;
	
	if (l<=lunghezza && v[l].key<v[i].key){
		min=l;
	}
	else min=i;
	if (r<=lunghezza && v[r].key<v[min].key){
		min=r;
	}
	if(min!=i){
		temp=v[i];
		v[i]=v[min];
		v[min]=temp;
		minheapify(min, v, lunghezza);
	}
	return v;
}

int main(){
	char input[14], comando1[14]="AggiungiGrafo";
	int d, k, numerografo=0, valorebuttato;
	int i, j, somma=0, posizione_corrente=-1, padre, corrente;
	nodo temp;
	valorebuttato=scanf("%d %d", &d, &k);
    int matrice[d][d], size;
    nodo u, node[d], miniheap[d];
	top ordine[k], temptop1, temptop2;
	
	u.key=-1;
	valorebuttato=scanf("%s", input);
	ordine[0].cammino=MAX;
	
	ciclo:
	while(strcmp(input, comando1)==0){
		for(i=0;i<d;i++){
			for(j=0;j<d-1;j++){
				valorebuttato=scanf("%d,", &matrice[i][j]);
			}
			valorebuttato=scanf("%d\n", &matrice[i][j]);
		}
		
		numerografo++;
		
//		for(i=0;i<d;i++){
//			for(j=0;j<d-1;j++){
//				printf("%d, ", matrice[i][j]);
//			}
//			printf("%d\n", matrice[i][j]);
//		}
//	printf("\n");

	size=0;
	for(i=0;i<d;i++){
		node[i].num=i;
	}	
    node[0].key=0;
	miniheap[size].key=0;
	miniheap[size].num=node[0].num;
	size++;

	for(i=1;i<d;i++){
	    node[i].key=MAX;
	    miniheap[size].key=MAX;
		miniheap[size].num=node[i].num;
		size++;
		corrente=size-1;
		
		if(node[i].key<=miniheap[corrente].key){
		miniheap[corrente].key=node[i].key;
		while(corrente>0 && miniheap[((corrente+1)/2)-1].key>miniheap[corrente].key){
			padre=((corrente+1)/2)-1;
			temp=miniheap[padre];
			miniheap[padre]=miniheap[corrente];
			miniheap[corrente]=temp;
			corrente=padre;
			}
		}
	}

	while(size>0){
		if(size>0){ 
		u=miniheap[0];
		miniheap[0]=miniheap[size-1];  
		minheapify(0, miniheap, size-1); 
		}
		size=size-1;
		for(i=0;i<d;i++){
			if(matrice[u.num][i]!=0){
				if(node[i].key>(node[u.num].key+matrice[u.num][i])){
					node[i].key=node[u.num].key+matrice[u.num][i];
					for(j=0;j<d;j++){
						if(node[i].num==miniheap[j].num){
							posizione_corrente=j;
						}
					}
					if(node[i].key<=miniheap[posizione_corrente].key){
					    miniheap[posizione_corrente].key=node[i].key;
					    while(posizione_corrente>0 && miniheap[((posizione_corrente+1)/2)-1].key>miniheap[posizione_corrente].key){
					        padre=((posizione_corrente+1)/2)-1;
					        temp=miniheap[padre];
					        miniheap[padre]=miniheap[posizione_corrente];
					        miniheap[posizione_corrente]=temp;
					        posizione_corrente=padre;
					    }
					}
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
			ordine[i].numero_grafo=numerografo-1;
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

	valorebuttato=scanf("%s", input);
	}
	if(numerografo>k){
		for(i=0;i<k;i++){
		printf("%d ",ordine[i].numero_grafo);
		}
	}
	else{
		for(i=0;i<numerografo;i++){
		printf("%d ",ordine[i].numero_grafo);
		}
	}
	
	
	valorebuttato=scanf("%s", input);
	if(strcmp(input, comando1)==0){
		printf("\n");
		goto ciclo;
	}
	
	if(valorebuttato==1){
		printf("Errore\n");
	}
}
