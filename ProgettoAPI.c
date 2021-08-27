#include<stdio.h>
//#include<math.h>
#include<time.h>

unsigned int MAX=4294967295;

typedef struct{
	unsigned int cammino;
	unsigned int numero_grafo;
}top;

typedef struct{
	unsigned int num;
	unsigned int key;
}nodo;

clock_t start, end;

int main(){
	char input[14], comando1[14]="AggiungiGrafo", numero[5000];
	int d, k, q, n, i, j, valorebuttato, valore;
	char* punt;
	valorebuttato=scanf("%d %d", &d, &k);
	top maxheap[k], temptop;
	int matrice[d][d], numerografo=0, size=0, r, l , min, padre, somma=0, max_size=0, max_temp, nonconnesso=0; //shortcut=0, top, bottom;
	nodo miniheap[d], u, temp;
	
	valorebuttato=scanf("%s", input);
	//start=clock();
	ciclo:
	while(input[0]==comando1[0]){
		//start=clock();
		punt=fgets(numero, 5000, stdin);
		//printf("%s\n", numero);
		/*for(i=0;i<d;i++){
			j=0;
			q=0;
			while(j<d){
				valore=0;
				car[0]=fgetc(stdin);
				while(car[q]<='9' && car[q]>='0'){
					q++;
					car[q]=fgetc(stdin);
				}
				for(n=0;n<q;n++){
					valore+=pow(10, q-n-1)*(car[n]-'0');
				}
				q=0;
				//matrice[i][j]=valore;
				j++;
			}
		}*/
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
					//valore=valore+pow_(j-n-1)*(numero[n]-'0');
					valore=valore*10+(numero[n]-'0');
					n++;
				}
				//car[i]=valore;
				matrice[0][1]=valore;
				n++;
				j++;
				while(q<d){
					valore=0;
					while(numero[j]<='9' && numero[j]>='0'){
						j++;
					}
					while(n<j){
						//valore=valore+pow_(j-n-1)*(numero[n]-'0');
						valore=valore*10+(numero[n]-'0');
						n++;
					}
					if(valore!=matrice[0][1]){
						nonconnesso=-1;
					}
					//car[i]=valore;
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
							//valore=valore+pow_(j-n-1)*(numero[n]-'0');
							valore=valore*10+(numero[n]-'0');
							n++;
						}
						matrice[i][q]=valore;
						//car[q]=valore;
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
		//end=clock();
		//printf("tempo: %f\n", ((double)(end-start))/CLOCKS_PER_SEC);
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
//		start2=clock();
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
//	end2=clock();
//	printf("%d) algoritmo: %f\n", numerografo, ((double)(end2-start2)/CLOCKS_PER_SEC));
//	insert:
//		start3=clock();	
//		printf("somma: %d\n", somma);
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

		/*for(i=0;i<d;i++){
			for(j=0;j<d-1;j++){
				printf("%d,",matrice[i][j]);
			}
			printf("%d\n", matrice[i][j]);
		}
		printf("\n");*/
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
//	end4=clock();
//	printf("\nscrittura: %f\n\n",  ((double)(end4 - start4)) / CLOCKS_PER_SEC);
	valorebuttato=scanf("%s", input);
	if(input[0]==comando1[0]){
		printf("\n");
		goto ciclo;
	}
	
	printf("\n");
	//end=clock();
	//printf("tempo: %f\n", ((double)(end-start))/CLOCKS_PER_SEC);
	if(valorebuttato==-2){
		printf("Errore\n");
	}
	return 0;
}
