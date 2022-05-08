/**
 * COSC 3250 - Project 2 Breaking the code
 * This code takes a user input from the key board, and a key, and decodes it into another 
 * another message. And is able to do this until the user quits 
 * Date 2/2/22
 * @author Emma Claire Kinnison
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void decoder_ring_printer(int* data, int key, int index){
    int c= 0;			//initilization
	int previousc=0;
	int previous=0;
	int sum=0;
    int y=0;
	while(y<index){	//auto cast the input char to an uppercase letter, run while loop while not the EOF char
		c=data[y];
        if(c==EOF){
            y=1026;
		}
		else{	//do this
			if((isalpha(c))||(isspace(c))){
				if(c==32){	//if its  a space, force it to 0
					c=0;
				}
				else if(c==10){	//if its an enter, reset everything, make c a non reachable number otherwise
					c=100;
					kprintf("\n");

				}
				else{	//make the value 0 to 26
					c=c-64;
				}
				sum=c-((previous+key)%27);	//decode
				if(sum<0){
					sum=sum+27;
				}
			
				int i=0;
			

				if((c!=100)){		//these are our enter and spaces
					if(sum<0){	//add to 64
						kputc(previous+64);
					}
					if(sum==0){		//make a space
						kprintf(" ");

					}
					else{		//make the correct uppercase value
						kputc(sum+64);
					}
				}
				else{
					if(c=100){		//reset
						
					}
				}
				if(c==100){

				}
				else{
					previous=c;		//maintain variables 

				}
			}
			else{
				if(c==10){
					c=0;
					previous=0;
					sum=0;
					kprintf("\n");
				}
				else{
					kprintf(" ");
				}
			}
		}
            y++;			
	}
}


int decoder_ring(int* data, int key){
    int z =0;
    int y=0;
    int c=0;
    int sum=0;
    int previous=0;
    int j=0;
    int decoded_data[1025];
    while(y<1025){	//auto cast the input char to an uppercase letter, run while loop while not the EOF char
        c=data[y];
        //printf("this is the value of the data %i", data[y]);
       // printf("%d,",data[y]);
        if(c==EOF){
            y=1026;
		}
		else{	//do this
			if((isalpha(c))||(isspace(c))){
				if(c==32){	//if its  a space, force it to 0
					c=0;
				}
				else if(c==10){	//if its an enter, reset everything, make c a non reachable number otherwise
					c=100;
				}
				else{	//make the value 0 to 26
					c=c-64;
				}
				//sum=c-previous-key;	//decode
				sum=c-((previous+key)%27);	//decode
				if(sum<0){
					sum=sum+27;
				}
				int i=0;
				// while(i==0){	//make it so if the indexes are weird they can be adjusted properly
				// 	if(sum==0){
				// 		i=1;
				// 	}
				// 	if((sum<0)){	//this helps to handle negative values
				// 		sum=sum+27;
				// 	}
				// 	else{
				// 		i=1;
				// 	}
				// }	
				if((c!=100)){		//these are our enter and spaces
					if(sum<0){	//add to 64
						//putchar(previous+64);
                        decoded_data[j] =previous+64;
                        j++;
					}
					if(sum==0){		//make a space
						//printf(" ");
                        decoded_data[j] =0;
                        j++;
					}
					else{		//make the correct uppercase value
					//	putchar(sum+64);
                        decoded_data[j] =sum+64;
                        j++;
					}
				}
				else{
					if(c=100){		//reset
					}
				}
				if(c==100){
				}
				else{
					previous=c;		//maintain variables 
				}
			}
			else{
				if(c==10){
					c=0;
					previous=0;
					sum=0;
					//printf("\n");
                    decoded_data[j] =10;
                    j++;
				}
				else{
					//printf(" ");
                    decoded_data[j] =0;
                    j++;
				}
			}
		}
        y++;
	}

    int counter=0;
    int k=0;
    while(k<1025){
        if(decoded_data[k]==69){
            counter++;
			//printf("%d\n", decoded_data[k]);
        }
        else{
        }
        k++;
    }
	//printf("end counter: %d\n", counter);
    return counter;
}


int main(int argc, char **argv){

	int c= 0;			//initilization
	int previousc=0;
	int previous=0;
	int key=0;
	int sum=0;
    int textarr[1025];
    textarr[1025]=EOF;
    int j=0;

    while (j<1025){         //populate with zeros
        textarr[j]=0;
        j++;
    }

    int index=0;    //more initiailizing
    int indexlooper=0;
    int keykey=0;
    int first=0;
    int second=-1;
    int temp=0;
    int keyfirst=0;
    int keysecond=0;
    int keytemp=0;

    while((c=toupper(getchar()))!=EOF){
        if(index>=1025){
        }
        else{
            textarr[index]=c;
            index++;
		}
	}

	while(indexlooper<27){
		keykey=decoder_ring(textarr, indexlooper);
		if(second==keykey){
		}
		else if(second<keykey){
			if(keykey>first){
				temp=first;
				first=keykey;
				second=temp;

				keytemp=keyfirst;
				keyfirst=indexlooper;
				keysecond=keytemp;
			}
			else{
				second=keykey;
				keysecond=indexlooper;
			}
		}
		indexlooper++;
	}
                
           

            
        


    printf("Most probable key is %d\n", keysecond);

    decoder_ring_printer(textarr, keysecond, index);
	printf("\n");
    
}
