#ifndef GAME_H                                                                                                          
#define GAME_H                                                                                                          
                                                                                                                        
typedef struct Node{                                                                                                    
    int x;                                                                                                              
    int y;                                                                                                              
    struct Node *next;                                                                                                  
} linkedlist;                                                                                                           
                                                                                                                        
//function for inputing                                                                                                 
void inpath(char str[]);                                                                                                
                                                                                                                        
//function for generation of food                                                                                       
void generatefood(int *fx,int *fy,int n,int m,linkedlist *head);                                                        
                                                                                                                        
//func for changing position                                                                                            
void poschange(int *hx,int *hy,int n,int m,char move);                                                                  
                                                                                                                        
//function to check if prime                                                                                            
int isPrime(int n);                                                                                                     
                                                                                                                        
#endif                                                                                                                  
                                                                                                                        
                                                                                                                        
                                                                                                                        
                                                                                                                        
