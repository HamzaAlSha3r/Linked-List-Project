// project 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
/*double linked list*/
typedef struct list* list;
struct list{
    int n1;
    list next;
    list prev;
};
/*function for delete all node from List*/
void DeleteList (list L){
     list temp;
     list l1 =L->next;
     L->next=NULL;
     L->prev=NULL;
    while (l1!=NULL){
      temp=l1->next;
      free(l1);
      l1=temp;
    }
}
/*function to difind new list and store memory for list */
list makeEmpty(list L){
    if(L!=NULL)
        DeleteList (L);
    L=(list)malloc(sizeof (struct list));
    if(L==NULL)
        printf("out the memory ");
    L->next=NULL;
    L->prev = NULL;
    return L;
}
/* function to insert at a first in list ,, to isert to input list*/
void insert_at_first(int n1, list L){
    list newNode = malloc(sizeof(struct list));
    newNode->n1 = n1;
    newNode->next = L->next;
    newNode->prev = L;
    L->next = newNode;
    L->next->prev = newNode;}
/* function to print all node */
void printList(list L){
    list p = L->next;
    if(L->n1==-1)
        printf("%c ",'-');
    while(p!=NULL){
        printf("%d   ",p->n1);
        p = p->next;
    }
    printf(" \n");
}
/*method to check if list empty or not*/
int isEmpty(list l1){
    return l1->next==NULL;
}
/*find last node */
struct list* find_last (struct list* L){
    struct list* c = L;
    while (c->next!=NULL)
        c=c->next;
    return c;
}
/* function to reverse linked list */
void reverse(struct list* L){
    struct list* curr  = L->next;
    struct list* prev = NULL;
    struct list* nxt  = curr->next;

    while(curr!=NULL){
        curr->next = prev;
        curr->prev = nxt;
        prev = curr;
        curr = nxt;

        if(nxt!=NULL)
            nxt = nxt->next;
    }
    L->next = prev;
    prev->prev = L;
}
/* function to insert at a the end in list ,, to insert to output list*/
void insert_At_End(int n ,list L){
    struct list * new_node = (struct list*)malloc(sizeof(struct list));
    new_node->n1 = n;
    struct list* temp = L;
    //to find last node in list
    while (temp->next!=NULL)
        temp =temp->next;
    temp->next=new_node;
    new_node->prev=temp;
    new_node->next=NULL;
}
/*function for printlist from end*/
void print_end (struct list* L){
    struct list* c = find_last(L);
    while (c->prev!= NULL){
        printf("%d   ",c->n1);
        c=c->prev;
    }
    printf(" \n");
}
int length (list l1){
    int count =0 ;
    struct list* c = l1->next;
    while (c!=NULL){
        count++;
        c=c->next;
    }
    return count;
}
/* function compare_two_linked_list*/
int compare (list l1 , list l2){
    reverse(l1);
    reverse(l2);
    struct list * l1_c = l1->next;
    struct list * l2_c = l2->next;
    while (l1_c!=NULL || l2_c!=NULL){
        if(l1_c->n1 > l2_c->n1){
            return 1;//largest
        }

        else if (l1_c->n1 < l2_c->n1){
            return -1; // smallest
        }

        else {
                l1_c=l1_c->next;
                l2_c=l2_c->next;
             }
        }
    return 0;// equle
    }

//method for all oprations start :
/*function oparitaion for subtract two list : "-" */
struct list * subtract (list l1,list l2){
    struct list* output = makeEmpty(NULL);
    if(length(l1)< length(l2)){
      output = subtract(l2,l1);
      output->n1=-1;
      return output;

    } else if (length(l1)== length(l2)){
       if(compare(l1,l2)==-1){
           output = subtract(l2,l1);
           output->n1=-1;
           return output;
       }
   }
    int brow=0;
    while (l1->next !=NULL || l2->next!=NULL){
        int n1=0,n2=0,sub=0;
        if(l1->next!=NULL){
           n1=l1->next->n1;
           l1=l1->next;
        }
        if(l2->next!=NULL){
            n2=l2->next->n1;
            l2=l2->next;
        }
        sub=n1-n2-brow;
        if(sub<0){
            sub+=10;
            brow=1;
        }
        else{
            brow=0;
        }
        insert_at_first(sub,output);
    }
    return output;
}
/*function oparitaion for addition two list : "+"  */
struct lis * addition(list l1,list l2){
    list output= makeEmpty(NULL);
    if(l1->n1==-1 && l2->n1==-1)
        output->n1=-1;
    else if (l1->n1==-1 || l2->n1==-1){
            output= subtract(l1,l2);
            output->n1=-1;
            return output;
    }
    int cin=0;
    while (l1->next !=NULL || l2->next!=NULL || cin){
        int sum=0;
        if(l1->next!=NULL){
            sum+=l1->next->n1;
            l1=l1->next;
        }
        if(l2->next != NULL){
            sum+=l2->next->n1;
            l2=l2->next;
        }
        sum+=cin;
        cin=sum/10;
        sum=sum%10;
        insert_At_End(sum,output);
    }
    if(cin>0)
        insert_At_End(cin,output);
    return output;
}
/*function oparitaion for multiply two list : "*" */
struct list * multiply (list l1,list l2){
    struct list* p=l1;
    int i=0;
    struct list* output = makeEmpty(NULL);
    struct list* temp = makeEmpty(NULL);
    while (l2->next!=NULL){
        int n1,n2,mul=0,cin =0;
        //equals one because the two numbers are equal
        if(i>0){
            for(int j=0;j<i;j++)
            insert_At_End(0,temp);
        }
        /*take first digit from second list to mult all digit  first list and pointer
        move to a next node of second list*/
        if(l2->next!=NULL){
            n2=l2->next->n1;
            l2=l2->next;
        }
        /* this while loop to In order for him to go through all the boxes of the first
         * list and multiply the number that you took from the second list with all the boxes*/
        while (l1->next!=NULL){
            mul=n2*l1->next->n1+cin;
            if(mul>9){
                cin=mul/10;
                mul=mul%10;
                insert_At_End(mul,temp);
                if(l1->next->next==NULL){
                    if(cin>0)
                    insert_At_End(cin,temp);
                }
            } else if( mul<=9){
                insert_At_End(mul,temp);
                if(l1->next->next==NULL){
                    if(cin>0)
                        insert_At_End(cin,temp);
                }
            }
            l1=l1->next;
        }
        output=addition(output,temp);
        temp= makeEmpty(NULL);
        /*The condition is here, because if it did not reach the last digit of the second list, it responds,
         * returning the cursor to the first digit of the first list and increasing the counter to add zeros*/
        if(l2->next!=NULL){
            i++;
            l1=p;
        }
    }
    /*This condition is so that if one of the two lists is negative,
     * it will be stored in the result as a negative*/
    if(l1->n1==-1 && l2->n1==-1)
        output->n1=1;
    else if (l1->n1==-1 || l2->n1==-1)
        output->n1=-1;
        else if (l1->n1!=-1 || l2->n1!=-1)
        output->n1=1;
    return output;
}
/*function oparitaion for divide two list : "/"*/
struct list * divide (list l1 /* divdend*/ , list l2 /*divisor */){
    list result = makeEmpty(NULL);
    /*This condition is so that if one of the two lists is negative,
     * it will be stored in the result as a negative*/
    if(l1->n1==-1 && l2->n1==-1)
        result->n1=1;
    else if (l1->n1==-1 || l2->n1==-1)
        result->n1=-1;
    else if (l1->n1!=-1 || l2->n1!=-1)
        result->n1=1;

    if(length(l1)== length(l2)){
        if(compare(l1,l2)==0){
            //equals one because the two numbers are equal
            insert_At_End(1,result);
        }
        else if (compare(l1,l2)==-1){
            //It is equal to zero because the divisor cannot be less than the dividend
            insert_At_End(0,result);
        }else if (compare(l1,l2)==1){
            int res =1;
            list subtraction = subtract(l1,l2);
            while (compare(subtraction,l2)==1){
                subtraction= subtract(subtraction,l2);
                res+=1;
            }
            while (res!=0){
                int n = res%10;
                res/=10;
                insert_at_first(n,result);
            }

        }
    }
    else{
        int res =1;
        list subtraction = subtract(l1,l2);
        while (compare(subtraction,l2)==1){
            subtraction= subtract(subtraction,l2);
            res++;
        }
        while (res!=0){
            int n = res%10;
            res/=10;
            insert_at_first(n,result);
        }

        }
    return result;
    }
/*function to read number from file and store in list*/
int read_number (struct list* list[]){
    char c;
    int index=0;
    list[0] = makeEmpty(NULL);
   FILE* fin = fopen("input.txt","r");
   while(fscanf(fin,"%c",&c) != EOF){
       int n=c-'0';
       if(c=='\n'){
           index++;
           list[index]= makeEmpty(NULL);
       }
       if(index>0){
           if(c=='-')
               list[index]->n1=-1;
           else if(n>=0 && n<=9 && isdigit(c)){
               insert_at_first(n,list[index]);
           }
       }
       else if(index==0){
           if(c=='-')
               list[0]->n1=-1;
           else if(n>=0 && n<=9 && isdigit(c)){
               insert_at_first(n,list[0]);
           }
       }
   }
    return index;
}
int main() {
   FILE* fout ;
    struct list * list[100];
        int index =0;
        int cheak=0;
      struct list * add = makeEmpty(NULL);
      struct list * sub = makeEmpty(NULL);
      struct list * mult = makeEmpty(NULL);
      struct list * div = makeEmpty(NULL);
    while (cheak!=7){
        printf("choisce from 1-6 opration : \n");
        printf("1. read the input file\n"
               "2.add\n"
               "3.subtract\n"
               "4.multiply\n"
               "5.divide\n"
               "6.print the results to an output file\n"
               "7.exit\n");
        printf("Choose the reading process before any operation .. \n");
        scanf("%d",&cheak);
        switch (cheak) {
            case 1:
                index = read_number(list);
                printf(" the numbers read \n : ");
                break;
            case 2:
                for(int i =0 ; i<=index;i++){
                    add= addition(add,list[i]);
                }
                reverse(add);
                printf("DONE addition\n");
                break;
            case 3:
                for(int i =0 ; i<=index;i++) {
                    sub = subtract(sub, list[i]);
                }
                printf("DONE subtractr\n");
                break;
            case 4:
                for(int i =0 ; i<=index;i++){
                    mult= multiply(mult,list[i]);
                }
                reverse(mult);
                printf("DONE multiply \n");
                break;
            case 5:
                for(int i =0 ; i<=index;i++){
                    div= divide(div,list[i]);
                }
                printf("DONE divtion \n");
                break;
            case 6:
                fout = fopen("output.txt","w");
                //add
                fprintf(fout," addtion  result  : .. \n");
                while (add->next!= NULL){
                    fprintf(fout,"%d  ",add->next->n1);
                    add=add->next;
                }
                fprintf(fout,"\n");
                //sub
                fprintf(fout,"Subtraction result : ..\n");
                while (sub->next!= NULL){
                    fprintf(fout,"%d  ",sub->next->n1);
                    sub=sub->next;
                }
                fprintf(fout,"\n");
                //mult
                fprintf(fout,"multiplication result  : .. \n");
                while (mult->next!= NULL){
                    fprintf(fout,"%d  ",mult->next->n1);
                    mult=mult->next;
                }
                fprintf(fout,"\n");
                //divide
                fprintf(fout,"The division product : . .\n");
                while (div->next!= NULL){
                    fprintf(fout,"%d  ",div->next->n1);
                    div=div->next;
                }
                fprintf(fout,"\n");
                fclose(fout);
                break;
            default:
                printf("please enter number of oprations... \n");
                break;
        }
    }
    printf("the program is exist ");

       return 0;
   }

