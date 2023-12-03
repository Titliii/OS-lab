#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
	int pid, start, length;
	struct Node* next;
};
typedef struct Node Node;

Node* allocN(Node *head, int pid, int length){
	Node *proc=(Node *)malloc(sizeof(Node)), *hole=head->next;
	proc->pid=pid;
	proc->start=hole->start;
	proc->length=length;
	hole->start+=length;
	hole->length-=length;
	if(hole->length<=0){
		proc->next=hole->next;
		free(hole);
	}
	else proc->next=hole;
	head->next=proc;
	return proc;
}

Node* deallocN(Node *head, int pid){
	Node *pre=head, *temp=head->next, *toRet=NULL;
	while(temp!=NULL){
		if(temp->pid!=pid){
			pre=temp;
			temp=temp->next;
			continue;
		}
		temp->pid=-1;
		toRet=temp;
		if(temp->next->pid==-1){
			Node *nt=temp->next;
			temp->length+=nt->length;
			temp->next=nt->next;
			free(nt);
		}
		if(pre->pid==-1){
			pre->length+=temp->length;
			pre->next=temp->next;
			free(temp);
			toRet=pre;
		}
		return toRet;
	}
	return toRet;
}

Node* firstFit(Node *head,int val){
	Node *temp,*temp1;
	temp=head;
	temp1=temp;
	temp=temp->next;
	while(temp!=NULL){
		if(temp->pid<0){
			if(((temp->length)-val>=0)){
				return temp1;
			}
		}
		temp1=temp;
		temp=temp->next;
	}
	return NULL;
}

Node* bestFit(Node *head,int val){
	Node *temp,*temp1,*temp2=NULL;
	temp=head;
	temp1=temp;
	temp=temp->next;
	int var=-1;//variable to store lengthth of hole
	while(temp!=NULL){
		if(temp->pid<0){//hole finding
			if((temp->length)-val==0){
				return temp1;
			}
			else if((temp->length)-val>0){
		        if((var-(temp->length)>0 && var!=-1) || var==-1){
		 		 	var=temp->length;
		 		 	temp2=temp1;
				}
			}
		}
		temp1=temp;
		temp=temp->next;
	}
	return temp2;
}

Node* worstFit(Node *head,int val){
	Node *temp,*temp1,*temp2=NULL;
	temp=head;
	temp1=temp;
	temp=temp->next;
	int var=-1;//variable to store lengthth of hole
	while(temp!=NULL){
		if(temp->pid<0){//hole finding
			if((temp->length)-val>=0){
		        if((var-(temp->length)<0 && var!=-1) || var==-1){
		 		 	var=temp->length;
		 		 	temp2=temp1;
				}
			}
		}
		temp1=temp;
		temp=temp->next;
	}
	return temp2;
}

void printL(Node *head){
	Node *temp=head->next;
	while(temp!=NULL){
        if(temp->pid>=0)
            printf("PID : %d",temp->pid);
        else printf("HOLE");
		printf("\tStart : %d\tLength : %d\n",temp->start,temp->length);
		temp=temp->next;
	}
}

void printGV(Node* he) {
	Node *head=he;

    head = head->next;
    while (head != NULL) {
        if (head->pid > 0) {
            printf("%02d +++++ PID %d\n", head->start, head->pid);
            for (int i = 1; i < head->length; i++) {
                printf("   +++++\n");
            }
        }
		else{
            printf("%02d xxxxx HOLE\n", head->start);
            for (int i = 1; i < head->length; i++) {
                printf("   xxxxx\n");
            }
        }
        head = head->next;
    }
}

Node* newMem(int length){
	Node *head=(Node*)malloc(sizeof(Node)), *temp;
	head->pid=head->start=head->length=-2;

	head->next=(Node*)malloc(sizeof(Node));
	head->next->pid=-1;
	head->next->start=0;
	head->next->length=length;
	return head;
}

void freeMem(Node *head){
	if(head==NULL)
		return;
	freeMem(head->next);
	free(head);
}

int chAlgo(){
	int ch=-1;
	while(1){
		printf("1. First Fit\n2. Best Fit\n3. Worst Fit\nChoose Algo : ");
		scanf("%d",&ch);
		if(ch>=0 && ch<=3)
			return ch;
		printf("Invalid Input\n\n");
	}
}

int main(){
	int maxl, ch=-1, algo, pid=1;
	printf("Enter memory size : ");
	scanf("%d",&maxl);
	algo=chAlgo();

	Node *head=newMem(maxl);

	while(ch!=6){
		printf("\n\n1. Clear Memory\n2. Change Algo\n3. Create New Process\n4. Remove Existing Process\n5. Display Graph\n6. Exit\nEnter Choice : ");
		scanf("%d",&ch);
		switch(ch){
			case 1 :freeMem(head);
					head=newMem(maxl);
					printf("\nMemory Cleared\n\n");
					break;
			case 2 :algo=chAlgo();
					break;
			case 3 :int pLen;
					Node *change;
					printf("\nEnter process size : ");
					scanf("%d",&pLen);
					switch(algo){
						case 1 :change=firstFit(head,pLen);break;
						case 2 :change=bestFit(head,pLen);break;
						case 3 :change=worstFit(head,pLen);break;
					}
					if(change==NULL)
						printf("\nSpace not available\n\n");
					else{
						change=allocN(change,pid++,pLen);
						printf("\nProcess allocated as PID %d at %d\n\n",change->pid,change->start);
					}
					break;
			case 4 :int rpid;
					printf("\nEnter PID : ");
					scanf("%d",&rpid);
					Node *newHole=deallocN(head,rpid);
					if(newHole==NULL)
						printf("\nProcess not found\n\n");
					else
						printf("\nProcess removed\nNew hole at %d\n\n",newHole->start);
					break;
			case 5 :printf("\n------------------\n\n");
					printGV(head);
					printf("\n------------------\n\n");
                    break;
			case 6 :break;
			default:printf("\nWrong Input\n\n");
		}
	}
}