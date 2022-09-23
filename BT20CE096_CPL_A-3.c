#include<stdio.h>
#define heapsize 10000 

// approach: While allocating memory, metadata(data about the memory) is stored adjacent to allocated memory in order to keep a track of all other memory blocks.
//           Using first fit strategy I allocated memory using 'Malloc' function and seperated allocated blocks from freelist. Implemented free function and merged 
//           adjacent blocks  

char heap_memory[heapsize]; 

typedef struct meta_block 
{
    size_t size;
    int STATUS;                                                         // STATUS is 0 When it is allocated  ; 1  when it is free
    struct meta_block* next; 
}meta_block;

 meta_block* freeList=(void*)heap_memory;   

void initialize()                                                /* Initializing the block of memory */
{
   freeList->size=heapsize-sizeof(meta_block); 
   freeList->STATUS=1;
   freeList->next=NULL; 
}

void split(meta_block* curr,size_t size)                      /* seperating allocated blocks from freelist */
{
    meta_block* split_ptr=(void*)( (void*)curr+size+sizeof(meta_block) );
    
    split_ptr->size=(curr->size)-size-sizeof(meta_block);                    //  allocation of rest of demanded memory{ right part}
    split_ptr->STATUS=1;
    split_ptr->next=curr->next; 
    
    curr->size=size;                                                         //  allocation of demanded memory{ left part}
    curr->STATUS=0;
    curr->next=split_ptr;
}

void* Malloc(size_t bytes)                                 /* Implementation of malloc function using first fit strategy*/
{
    meta_block *curr,*prev;
    void* result;
    if(!(freeList->size))                                          
    { 
      initialize();
      printf("\n Memory initialization done ");
    }
    curr=freeList;
    while( (((curr->size)<bytes)||((curr->STATUS)==0))&&(curr->next!=NULL) )      /* move onto next block if space present is not enough */
    {    
      prev=curr;
      curr=curr->next;
      printf("\n surpassed a meta_block");
    }
    if((curr->size)==bytes)                                                      /* allocate whenever you find exact no of bytes */
    {
 	  curr->STATUS=0;
      result=(void*)(++curr);
      printf("\n Allocated Exactly demanded memory ");
     return result;
    }
    else if((curr->size)>(bytes+sizeof(meta_block)))                                 /* spilt the allocated blocks from the free list */
    {
 	  split(curr,bytes);
      result=(void*)(++curr);
      printf("\n memory allocated with a split ");
     return result;
    }
    else 
    {
      result=NULL;
      printf("\n Warning!! No sufficient memory to allocate "); 
     return result;
    }
}


void merge()                                                                   /* merge function for merging memory meta_blocks */
{
   meta_block *curr,*prev;
  curr=freeList;
   while((curr->next)!=NULL)
   {
     if((curr->STATUS) && (curr->next->STATUS))
	 {
       curr->size+=(curr->next->size)+sizeof(meta_block);
       curr->next=curr->next->next;
     }
     prev=curr;
     curr=curr->next;
   }
}

void Free(void* ptr)                                                         /* free function for deleting memory */
{
   if( ((void*)heap_memory<=ptr)&&(ptr<=(void*)(heap_memory+heapsize)) )
   {
     meta_block* curr=ptr;
     --curr;
     curr->STATUS=1;
     merge();
     printf("\n MEMORY deallocated sucessfully! ");
   }
   else
   {
   	 printf("\n Warning!! Invalid pointer ");
   } 
}

int main()
{

	 int *p=(int*)Malloc(30*sizeof(int));
	  printf("\n");
     char *q=(char*)Malloc(250*sizeof(char));
      printf("\n");
     int *r=(int*)Malloc(3000*sizeof(int));
      printf("\n");
     Free(p);
      printf("\n");
     char *w=(char*)Malloc(700);
      printf("\n");
     Free(r);
      printf("\n");
     int *k=(int*)Malloc(500*sizeof(int));
      printf("\n");
     printf("\n Allocation and deallocation is done successfully!");
}