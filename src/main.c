#include<stdio.h>

unsigned int MAX=4294967295;

typedef struct{
	unsigned int cammino;
	unsigned int numero_grafo;
}top;

typedef struct{
	unsigned int num;
	unsigned int key;
}nodo;

int main(){
	char input[14], comando1[14]="AggiungiGrafo", numero[5000];
	int d, k, q, n, i, j, valorebuttato, valore;
	char* punt;
	valorebuttato=scanf("%d %d", &d, &k);
	top maxheap[k], temptop;
	int matrice[d][d], numerografo=0, size=0, r, l , min, padre, somma=0, max_size=0, max_temp, nonconnesso=0; //shortcut=0, top, bottom;
	nodo miniheap[d], u, temp;
	
	valorebuttato=scanf("%s", input);
	ciclo:
	while(input[0]==comando1[0]){
		punt=fgets(numero, 5000, stdin);
		for(i=0;i<d;i++){
			if(i==0){
				punt=fgets(numero, 5000, stdin);
				valore=0;
				j=0;
				q=2;
				while(numero[j]<='9' && numero[j]>='0'){
					j++;
				}
				j++;
				n=j;
				while(numero[j]<='9' && numero[j]>='0'){
					j++;
				}
				while(n<j){
					valore=valore*10+(numero[n]-'0');
					n++;
				}
				matrice[0][1]=valore;
				n++;
				j++;
				while(q<d){
					valore=0;
					while(numero[j]<='9' && numero[j]>='0'){
						j++;
					}
					while(n<j){
						valore=valore*10+(numero[n]-'0');
						n++;
					}
					if(valore!=matrice[0][1]){
						nonconnesso=-1;
					}
					matrice[i][q]=valore;
					n++;
					if(numero[j]==','){
						j++;
					}
					q++;
				}
			}
			else{
				if(nonconnesso==0){
					punt=fgets(numero, 5000, stdin);
				}
				else{
					punt=fgets(numero, 5000, stdin);
					j=0;
					q=0;
					n=0;
					while(q<d){
						valore=0;
						while(numero[j]<='9' && numero[j]>='0'){
							j++;
						}
						while(n<j){
							valore=valore*10+(numero[n]-'0');
							n++;
						}
						matrice[i][q]=valore;
						n++;
						if(numero[j]==','){
							j++;
						}
						q++;
					}
				}
			}
		}
		numerografo++;
		if(nonconnesso==0){
			somma=matrice[0][1]*(d-1);
			goto insert;
		}
		nonconnesso=0;
		
		size=d;
		miniheap[0].key=0;
		miniheap[0].num=0;
		for(i=1;i<d;i++){
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
		if(max_size<k){
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
				while((2*(i+1)-1)<k){
					l=(2*(i+1))-1;
					r=(2*(i+1));
					if(maxheap[l].cammino>maxheap[i].cammino){
						max_temp=l;
					}
					else max_temp=i;
					if(r<k && maxheap[r].cammino>maxheap[max_temp].cammino){
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
					else i=k;
				}
			}
		}
		somma=0;
		valorebuttato=scanf("%s", input);
		valorebuttato=*punt;

	}

	if(numerografo>k){
		for(i=0;i<k-1;i++){
			printf("%d ",maxheap[i].numero_grafo);
		}
		printf("%d",maxheap[k-1].numero_grafo);
	}
	else{
		if(numerografo!=0){
			for(i=0;i<numerografo-1;i++){
			printf("%d ", i);
			}
			printf("%d", i);
		}
	}
	valorebuttato=scanf("%s", input);
	if(input[0]==comando1[0]){
		printf("\n");
		goto ciclo;
	}
	
	printf("\n");
	if(valorebuttato==-2){
		printf("Errore\n");
	}
	return 0;
}
