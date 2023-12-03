#include<stdio.h>
#include<stdlib.h>

int search(int val, int *arr, int lim){
	for(int i=0;i<lim;i++)
		if(val==arr[i]) return i;
	return -1;
}

void printTabh(int frames, int lr){
	if(lr==0) return;
	printf("Ref Str\t\t");
        for(int i=0;i<frames;i++) printf("Frame %d\t\t",i+1);
        printf("Hit/Miss\n");
}

void printTabr(int ac, int frames, int *arr, char isHit, int lr){
	if(lr==0) return;
	printf("%d\t\t",ac);
        for(int i=0;i<frames;i++) printf("%d\t\t",arr[i]);
        printf("%c\n",isHit);
}

int FIFO(int frames, int count, int *arr, int pr){
	int *fr=(int*)calloc(frames, sizeof(int));
	int wr=0, hit=0;
	if(pr==1) printf("\n\nFIFO : frames = %d\n",frames);
	printTabh(frames,pr);
	for(int i=0;i<count;i++){
		char isHit;
		if(search(arr[i],fr,frames)<0){
			fr[wr]=arr[i];
			wr=(wr+1)%frames;
			isHit='M';
		}
		else{
			hit++;
			isHit='H';
		}
		printTabr(arr[i],frames, fr, isHit, pr);
	}
	return hit;
}

int min(int *arr, int lim){
	int sm=0;
	for(int i=1;i<lim;i++)
		if(arr[i]<arr[sm]) sm=i;
	return sm;
}

int max(int *arr, int lim){
	int mx=0;
	for(int i=1;i<lim;i++)
		if(arr[i]>arr[mx]) mx=i;
	return mx;
}

int LRU(int frames, int count, int *arr, int pr){
	int *fr=(int*)calloc(frames*2,sizeof(int));
	int hit=0;
	if(pr==1) printf("\n\nLRU : frames = %d\n",frames);
	printTabh(frames, pr);
	for(int i=0; i<count; i++){
		char isHit;
		int fat = search(arr[i], fr, frames);
		if(fat<0){
			fat=min(&fr[frames],frames);
			fr[fat]=arr[i];
			isHit='M';
		}
		else{
			hit++;
			isHit='H';
		}
		fr[frames+fat]=i+1;
		printTabr(arr[i], frames, fr, isHit, pr);
	}
	return hit;
}

int OPT(int frames, int count, int *arr, int pr){
	int *fr=(int*)calloc(frames,sizeof(int));
	int hit=0;
	if(pr==1) printf("\n\nOPT : frames = %d\n",frames);
	printTabh(frames, pr);
	for(int i=0; i<count; i++){
		char isHit;
		int fat = search(arr[i], fr, frames);
		if(fat<0){
			int lastac = -1, lastacpos=-1;
			for(int j=0;j<frames;j++){
				int nextac = search(fr[j], arr+i+1, count-(i+1));
				if(nextac<0){
					lastac = j;
					break;
				}
				if(lastacpos<nextac){
					lastac = j;
					lastacpos = nextac;
				}
			}
			fr[lastac] = arr[i];
			isHit='M';
		}
		else{
			hit++;
			isHit='H';
		}
		printTabr(arr[i], frames, fr, isHit, pr);
	}
	return hit;
}

void graph(int lim, int *arr, int buff){
	int xmin=arr[min(arr, lim)], xmax=arr[max(arr, lim)];
	int ymin=arr[min(arr+lim,lim)+lim], ymax=arr[max(arr+lim,lim)+lim];
	for(int i=ymax+buff;i>=ymin-buff;i--){
		printf("%d \t|\t",i);
		for(int j = xmin-buff;j<=xmax+buff;j++){
			for(int k=0;k<lim;k++)
				if(arr[k]==j && arr[k+lim]==i){
					printf("*");
					break;
				}
			printf("\t");
		}
		printf("\n");
	}
	printf("\t");
	for(int j = xmin-buff;j<=xmax+buff;j++) printf("--------");
	printf("-\n\t\t");
	for(int j = xmin-buff;j<=xmax+buff;j++) printf("%d\t", j);
	printf("\n");
}

int main(){
	/*int ar[]={1,2,3,4,3,2,5,6,1,5};
	int fr=3, c=10;
	printf("Hits : %d\n",OPT(fr,c,ar,1));*/
	/*int arr[]={1,2,3,1,2,3};
	graph(3,arr,0);*/
	int c, fm, fs, ch=0, full, pr=1;
	printf("Enter no. of access : ");
	scanf("%d",&c);
	int *arr=(int*)calloc(c,sizeof(int));
	printf("Enter %d pages : ", c);
	for(int i=0;i<c;i++){
		//printf("Enter %d : ", i+1);
		scanf("%d",&arr[i]);
	}
	printf("Enter min and max no. of frames : ");
	scanf("%d %d", &fs, &fm);
	full = fm-fs+1;
	int *hitf=(int*)calloc(full*2,sizeof(int));
	for(int i=0;i<full;i++)
		hitf[i]=fs+i;
	while(ch!=5){
		printf("1. FIFO\n2. OPT\n3. LRU\n4. Toggle Table Print\n5. Exit\nEnter choice : ");
		scanf("%d",&ch);
		printf("\n");
		switch(ch){
			case 1:
			case 2:
			case 3:break;
			case 4:pr=(pr+1)%2;
				printf("Table will %sbe printed\n\n",(pr==1)?"":"not ");
				continue;
			case 5:exit(0);
			default:printf("\nWrong Input\n");
		}
		for(int i = 0;i < full;i++){
			switch(ch){
				case 1:hitf[full+i] = FIFO(fs+i,c,arr,pr); break;
				case 2:hitf[full+i] = OPT(fs+i,c,arr,pr); break;
				case 3:hitf[full+i] = LRU(fs+i,c,arr,pr); break;
			}
			if(pr==1) printf("Hit Ratio : %d/%d\n\n",hitf[full+i],c);
		}
		printf("\nNo. of Frames vs Hits\n");
		graph(full,hitf,0);
		printf("\n");
	}
}