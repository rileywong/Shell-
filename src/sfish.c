#include "sfish.h"
#include <unistd.h> 
#include <sys/types.h>
       #include <sys/wait.h>
#include <linux/limits.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//Global variables
char **cmdArray;
//char ***arrayOfCommands;
char **cmdArrayNew;
// SUPPOSED TO CARRY All cmds
char ** holder;
char ** pidArray;
int arrSize;
char *curDir;
char *prevDir;
char *dummy;
int retCode;
int userBool = 1;
int machBool = 1;

int userCol = 8;
int machCol = 8;
int boldBool = 0;

// CHILD PID ID
int pids[1024] = {0};


int pidsStatus[1024] = {0};

int pgid[1024] = {0};

double time1[1024] = {0};


int pidsSize = 0;
int pgidSize = 0;

char *changePrompt;
//char* stringToken1;



int main(int argc, char** argv) {






    //DO NOT MODIFY THIS. If you do you will get a ZERO.
    rl_catch_signals = 0;
    //This is disable readline's default signal handlers, since you are going
    //to install your own.

    pidArray = NULL;
    //memset(pidArray,0,strlen(pidArray));

     rl_command_func_t ctrlB;
     rl_bind_key (2,ctrlB);   
    

     rl_command_func_t ctrlG;
     rl_bind_key (7,ctrlG);   
    

     rl_command_func_t ctrlH;
     rl_bind_key (8,ctrlH);   
     

     rl_command_func_t ctrlP;
     rl_bind_key (16,ctrlP);   
    
    holder = malloc(sizeof (char*) * pidsSize+1);

    dummy = NULL;

    char *cmd;
    updatePrompt();
    while((cmd = readline(changePrompt)) != NULL) {
        if (strcmp(cmd,"quit")==0)
            break;
        
        holder = realloc(holder,sizeof (char*) * pidsSize+1);
        dummy = realloc (dummy, sizeof (char*) * PATH_MAX);
        dummy = memset(dummy,0,strlen(cmd));
        strcat(dummy,cmd);

        //Clear previous cmdArray in case and change arrSize
        cmdArray = NULL;
        cmdArrayNew = NULL;
        arrSize = 0;

        //Initialize the curDirectory
        //curDir = realloc(curDir,PATH_MAX);
       // printf("Before the loop starts%s\n",prevDir );
        size_t size = PATH_MAX;
          if(curDir==NULL){
        curDir= (char *) realloc (curDir, sizeof (char*) * size);
        memset(curDir,0,strlen(curDir));
    }
        if(prevDir==NULL){
        prevDir = (char *) realloc (prevDir, sizeof (char*) * size);
        memset(curDir,0,strlen(curDir));
    }
        getcwd(curDir,size);
        //printf("%s\n",curDir );
        // Split the new line into an array
        splitArray(cmd);

       

        /*
        char * part1 = NULL;
        char * part2 = NULL;
        char * part3 = NULL;
        part1 = (char *) realloc (part1, sizeof (char*) * PATH_MAX);
        part2 = (char *) realloc (part2, sizeof (char*) * PATH_MAX);
        part3 = (char *) realloc (part3, sizeof (char*) * PATH_MAX);
        */
        
        if(strlen(cmd)!=0){

         // Test if we're getting the right output, we should be
        pid_t childOrNot = 1;
        int case1 = 0;
        int case2 = 0;
        int case3 = 0;
        for (int i = 0; i < arrSize; ++i)
        {
           // printf("%s\n", cmdArray[i]);
            if(strcmp(cmdArray[i],"<") == 0 || strcmp(cmdArray[i],">")==0 || strcmp(cmdArray[i],"|") == 0
               || strcmp(cmdArray[i],"2>")==0 || strcmp(cmdArray[i],"0>")==0 || strcmp(cmdArray[i],"1>")==0){
                if (case1 == 0){
                    case1 = i;
                }
                else if(case2 == 0){
                    case2 = i;
                }
                else if( case3 == 0){
                    case3 = i;
                }


            }
        }

        /*
        //printf("%s\n","section 1" );
        extractString(0, case1);
        //printf("%s\n", "Section 2");
        extractString(case1 + 1,case2);
        //printf("%s\n", "Section 3");
        extractString(case2 + 1, arrSize);
        // THE HELP FUNCTION
        */
        //printf("%i%i%i\n", case1,case2,case3);
        
        //printf("case1 = %i case2 = %i arsize = %i\n", case1,case2,arrSize);

       
        if((case1 != 0 || case2 != 0)&& case3==0){
            //printf("This is the bofre of the command Array: %s\n", cmdArrayNew[0]);
            splitArray1(cmd,case1,case2);
           
            
            //printf("Case1 : %s Case 2 : %s \n", cmdArray[case1],cmdArray[case2]);
            /*
            int v = 0;
            
            for(v= 0; v < arrSize; v ++){
                printf("This is the first of the command Array11: %s\n", cmdArray[v]);
            }
            
            printf("This is the first of the command Array: %s\n", cmdArrayNew[0]);
            printf("This is the first of the command Array: %s\n", cmdArrayNew[0]);
            */
            //execvp(cmdArray[0], &cmdArray[0]);
           // printf("%s\n", "shouldnt get here?");
            if(case2 == 0){

                //printf("%s\n",cmdArray[case1] );
                // CASE FOR a < B
                // THIS IS NOT COMPLETE
                if(strcmp(cmdArray[case1],"<") == 0 ){
                    //printf("%s\n","should b here" );
                    childOrNot = fork();
                    int status = 0;
                    if(childOrNot==0){

                        int rightfile = 0 ;
                        rightfile = open(cmdArrayNew[case1+1],O_RDONLY 

                            |O_CLOEXEC | S_IWUSR | S_IRUSR , 0666);
                      
                        int check = dup2(rightfile,STDIN_FILENO); 
                        if(check == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      

                        fflush(stdout); 
                        
                        if(rightfile == -1){
                            printf("%s\n", "file failed");
                        }
                        
                       // printf("%s\n",cmdArrayNew[0] );
                        //printf("%s\n", cmdArrayNew[case1+1]);
                        execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        close(rightfile);
                        retCode = EXIT_SUCCESS;
                        exit(EXIT_SUCCESS);
                    }

                    else if (childOrNot == -1){
                        retCode = EXIT_FAILURE;
                        exit(EXIT_FAILURE);
                    }
                    else{
                        int test = waitpid(childOrNot,&status,WNOHANG);
                        incrPgid(1);
                        addPid(childOrNot, test);
                        if(WIFEXITED(&status) !=0){
                        retCode=EXIT_SUCCESS;
                    }
                        else{
                            retCode = EXIT_FAILURE;
                        }       
                    }
                    
                }

                // CASE FOR a > b

                else if(strcmp(cmdArray[case1],">") == 0 || strcmp(cmdArray[case1],"1>") == 0
                    || strcmp(cmdArray[case1],"0>") == 0){
                      

                    childOrNot = fork();
                    int status = 0;

                    if(childOrNot==0){
                        //printf("%s\n", "this file");
                        //int rightfile = open(cmdArray[case1+1],O_WRONLY | O_CREAT | S_IWUSR | S_IRUSR);
                        /*
                        char* test = NULL;
                        
                        test = (char *) realloc (test, sizeof (char*) * PATH_MAX);
                        strncpy(test,extractString(0,case1), sizeof (char*) * PATH_MAX);
                        printf("%s\n", test);
                        */
                        int rightfile = 0 ;
                        rightfile = open(cmdArrayNew[case1+1],O_WRONLY | O_CREAT 

                            /*| S_IWUSR | S_IRUSR*/,0666);
                      
                        //chmod(cmdArrayNew[2], 0644);
                        
                        //printf("%s\n","we here?" );
                            if(rightfile == -1){
                                printf("%s\n", "file creation failed");
                                printf("This is cmd 2: %s \n",cmdArrayNew[case1+1] );
                            }
                        
                        int check = dup2(rightfile,1); 
                        if(check == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      
                        fflush(stdout); 
                        close(rightfile);
                        /*
                        printf("what is this : %s\n",cmdArrayNew[0] );
                        printf("what is this : %s\n",cmdArrayNew[1] );
                        printf("what is this : %s\n",cmdArrayNew[2] );
                        printf("what is this : %s\n",cmdArrayNew[3] );
                        */
                        //system(cmdArrayNew[0]);
                        //printf("%s\n", cmdArrayNew[2]);
                        

                        execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        
                        

                        
                        retCode = EXIT_SUCCESS;
                        exit(EXIT_SUCCESS);
                    }

                    else if (childOrNot == -1){
                        retCode = EXIT_FAILURE;
                        exit(EXIT_FAILURE);
                    }
                    else{
                        int test = waitpid(childOrNot,&status,WNOHANG);
                        incrPgid(1);
                        addPid(childOrNot, test);
                        if(WIFEXITED(&status) !=0){
                        retCode=EXIT_SUCCESS;
                    }
                        else{
                            retCode = EXIT_FAILURE;
                        }       
                    }
                
                // CASE FOR a 2> b%s
                    
                }else if(strcmp(cmdArray[case1],"2>") == 0 ){
                    incrPgid(1);
                    childOrNot = fork();
                    int status = 0;

                    if(childOrNot==0){
                      
                        int rightfile = 0 ;
                        rightfile = open(cmdArrayNew[case1+1],O_WRONLY | O_CREAT 

                            /*| S_IWUSR | S_IRUSR*/,0666);
                      
                       
                            if(rightfile == -1){
                                printf("%s\n", "file creation failed");
                                printf("This is cmd 2: %s \n",cmdArrayNew[case1+1] );
                            }
                        
                        int check = dup2(rightfile,2); 
                        if(check == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      
                        fflush(stdout); 
                        close(rightfile);
                        

                        execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        
                        

                        
                        retCode = EXIT_SUCCESS;
                        exit(EXIT_SUCCESS);
                    }

                    else if (childOrNot == -1){
                        retCode = EXIT_FAILURE;
                        exit(EXIT_FAILURE);
                    }
                    else{
                        int test = waitpid(childOrNot,&status,WNOHANG);
                        addPid(childOrNot, test);
                        if(WIFEXITED(&status) !=0){
                        retCode=EXIT_SUCCESS;
                    }
                        else{
                            retCode = EXIT_FAILURE;
                        }       
                    }
                }
                // CASE FOR a | b 
                else if(strcmp(cmdArray[case1],"|") == 0 ){

                    //printf("command 1 %s command 2 %s\n", cmdArrayNew[0], cmdArrayNew[2]);
                    //printf("%s\n", cmdArrayNew[3]);
                    //printf("This is > %s\n", cmdArrayNew[4]);
                    
                    int pid;
                    int fileD[2];


                    pipe(fileD);

                    incrPgid(2);
                    pid = fork();
                  //  printf("pid number : %i\n",pid );
                    if(pid == 0){
                        //printf("%s\n",  " hwere?" );
                        int x = dup2(fileD[1],1);

                         //printf("Arrany New 01 %s\n", cmdArrayNew[0]);
                        if(x == -1){
                            printf("%s\n", "failed");
                        }
                        // printf("Arrany New 02 %s\n", cmdArrayNew[0]);
                        close(fileD[0]);
                       // printf("Arrany New 03 %s\n", cmdArrayNew[0]);
                        execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        perror(cmdArrayNew[0]);

                    }
                    else if(pid == -1){
                        //printf("%s\n",  " hwere?" );
                        perror("fork");
                        exit(1);
                    }
                    else{
                       // printf("%s\n", " im the parent");
                        //break;
                    }

                    pid = fork();
                   // printf("Number of 2nd fork %i\n", pid);
                    if(pid == 0){
                     //   printf("%s\n", "child of next one");
                        int x =dup2(fileD[0],0);
                        if(x == -1){
                            printf("%s\n", "failed");
                        }
                        close(fileD[1]);

                        execvp(cmdArrayNew[2],&cmdArrayNew[2]);
                        perror(cmdArrayNew[2]);

                    }
                    else if(pid == -1){
                        perror("fork");
                        exit(1);
                    }
                    else{
                      
                    }

                    close(fileD[0]); close(fileD[1]); 
                    int status;
                    // Wait for childnre if you're an adult
                    while ((pid = wait(&status)) != -1) 
                      
                      {
                        int test = waitpid(pid,&status,WNOHANG);
                        addPid(pid, test);
                      }  
                    

                    
                }



        }

        /// CASE WHERE ITS A > B > C

        else if((strcmp(cmdArray[case1],">") == 0 || strcmp(cmdArray[case1],"1>") == 0
                    || strcmp(cmdArray[case1],"0>") == 0) 
                    &&
                    (strcmp(cmdArray[case2],">") == 0 || strcmp(cmdArray[case2],"1>") == 0
                    || strcmp(cmdArray[case2],"0>") == 0) ){
                    printf("%s\n"," case a > b > c" );
                        incrPgid(2);
                        childOrNot = fork();
                    int status = 0;

                    if(childOrNot==0){
                        
                        int rightfile = 0 ;
                        rightfile = open(cmdArrayNew[case1+1],O_WRONLY | O_CREAT 


                            /*| S_IWUSR | S_IRUSR*/,0666);
                      int rightestfile = 0 ;
                        rightestfile = open(cmdArrayNew[case2+1],O_WRONLY | O_CREAT 
                            ,0666);

                       
                            if(rightfile == -1){
                                printf("%s\n", "file creation failed");
                                printf("This is cmd 2: %s \n",cmdArrayNew[case1+1] );
                            }
                        
                        int check = dup2(rightestfile,1); 
                        if(check == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      
                        fflush(stdout); 
                        close(rightfile);
                        close(rightestfile);


                        

                        execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        
                        
                        
                            /*| S_IWUSR | S_IRUSR*/
                      

                        
                        retCode = EXIT_SUCCESS;
                        exit(EXIT_SUCCESS);
                    }

                    else if (childOrNot == -1){
                        retCode = EXIT_FAILURE;
                        exit(EXIT_FAILURE);
                    }
                    else{
                        int test = waitpid(childOrNot,&status,WNOHANG);
                        addPid(childOrNot, test);
                        if(WIFEXITED(&status) !=0){
                        retCode=EXIT_SUCCESS;
                    }
                        else{
                            retCode = EXIT_FAILURE;
                        }       


                    }
        }
        //CASE FOR a 2> b > c
        else if((strcmp(cmdArray[case1],"2>") == 0 )
                    &&
                    (strcmp(cmdArray[case2],">") == 0 || strcmp(cmdArray[case2],"1>") == 0
                    || strcmp(cmdArray[case2],"0>") == 0) ){
                    incrPgid(2);
                    childOrNot = fork();
                    int status = 0;

                    //printf("%s\n","here?sdfadfs" );

                    if(childOrNot==0){
                      
                        int rightfile = 0 ;
                        rightfile = open(cmdArrayNew[case1+1],O_WRONLY | O_CREAT 

                            /*| S_IWUSR | S_IRUSR*/,0666);
                      
                       
                            if(rightfile == -1){
                                printf("%s\n", "file creation failed");
                                printf("This is cmd 2: %s \n",cmdArrayNew[case1+1] );
                            }
                        
                        int check = dup2(rightfile,2); 
                        if(check == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      
                        fflush(stdout); 
                        close(rightfile);
                        

                        
                        
                        int rightestfile = 0 ;
                        rightestfile = open(cmdArrayNew[case2+1],O_WRONLY | O_CREAT 

                            /*| S_IWUSR | S_IRUSR*/,0666);
                            int check1 = dup2(rightfile,1); 
                        if(check1 == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      
                        fflush(stdout); 

                        close(rightestfile);

                        execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        
                        retCode = EXIT_SUCCESS;
                        exit(EXIT_SUCCESS);
                    }

                    else if (childOrNot == -1){
                        retCode = EXIT_FAILURE;
                        exit(EXIT_FAILURE);
                    }
                    else{
                        int test = waitpid(childOrNot,&status,WNOHANG);
                        addPid(childOrNot, test);
                        if(WIFEXITED(&status) !=0){
                        retCode=EXIT_SUCCESS;
                    }
                        else{
                            retCode = EXIT_FAILURE;
                        }       
                    }

                

            }
            // CASE FOR a > b 2> c
            else if((strcmp(cmdArray[case2],"2>") == 0 )
                    &&
                    (strcmp(cmdArray[case1],">") == 0 || strcmp(cmdArray[case1],"1>") == 0
                    || strcmp(cmdArray[case1],"0>") == 0) ){
                    incrPgid(2);
                    childOrNot = fork();
                    int status = 0;

                    //printf("%s\n","here?sdfadfs" );

                    if(childOrNot==0){
                      
                        int rightfile = 0 ;
                        rightfile = open(cmdArrayNew[case2+1],O_WRONLY | O_CREAT 

                            /*| S_IWUSR | S_IRUSR*/,0666);
                      
                       
                            if(rightfile == -1){
                                printf("%s\n", "file creation failed");
                                printf("This is cmd 2: %s \n",cmdArrayNew[case1+1] );
                            }
                        
                        int check = dup2(rightfile,2); 
                        if(check == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      
                        fflush(stdout); 
                        close(rightfile);
                        

                        
                        
                        int rightestfile = 0 ;
                        rightestfile = open(cmdArrayNew[case1+1],O_WRONLY | O_CREAT 

                            /*| S_IWUSR | S_IRUSR*/,0666);
                            int check1 = dup2(rightfile,1); 
                        if(check1 == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      
                        fflush(stdout); 

                        close(rightestfile);

                        execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        
                        retCode = EXIT_SUCCESS;
                        exit(EXIT_SUCCESS);
                    }

                    else if (childOrNot == -1){
                        retCode = EXIT_FAILURE;
                        exit(EXIT_FAILURE);
                    }
                    else{
                        int test = waitpid(childOrNot,&status,WNOHANG);
                        addPid(childOrNot, test);
                        if(WIFEXITED(&status) !=0){
                        retCode=EXIT_SUCCESS;
                    }
                        else{
                            retCode = EXIT_FAILURE;
                        }       
                    }

                

            }


            //CASE FOR A > B < C
            else if((strcmp(cmdArray[case1],">") == 0 || strcmp(cmdArray[case1],"1>") == 0
                    || strcmp(cmdArray[case1],"0>") == 0 || strcmp(cmdArray[case1],"2>") == 0) 
                    &&
                    (strcmp(cmdArray[case2],"<") == 0 || strcmp(cmdArray[case2],"1<") == 0
                    || strcmp(cmdArray[case2],"0<") == 0 || strcmp(cmdArray[case2],"2<") == 0) ){


                    printf("%s\n", "Redirction is unclear");
            
            
            }
            //CASE FOR A < B > C
            else if((strcmp(cmdArray[case1],"<") == 0 || strcmp(cmdArray[case1],"1<") == 0
                    || strcmp(cmdArray[case1],"0<") == 0 || strcmp(cmdArray[case1],"2<") == 0) 
                    &&
                    (strcmp(cmdArray[case2],">") == 0 || strcmp(cmdArray[case2],"1>") == 0
                    || strcmp(cmdArray[case2],"0>") == 0 || strcmp(cmdArray[case2],"2>") == 0) ){
                    incrPgid(2);
                    childOrNot = fork();
                    int status = 0;
                    if(childOrNot==0){
                        printf("%s\n","should have goten her" );
                        int rightfile = 0 ;
                        rightfile = open(cmdArrayNew[case1+1],O_RDONLY 

                            |O_CLOEXEC | S_IWUSR | S_IRUSR , 0666);
                      
                        int check = dup2(rightfile,STDIN_FILENO); 
                        if(check == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      

                        fflush(stdout); 
                        
                        if(rightfile == -1){
                            printf("%s\n", "file failed");
                        }
                        
                       // printf("%s\n",cmdArrayNew[0] );
                        //printf("%s\n", cmdArrayNew[case1+1]);
                       



                        int rightfile1 = 0 ;
                        rightfile1 = open(cmdArrayNew[case2+1],O_WRONLY | O_CREAT , 0666);
                      

                        int check2 = dup2(rightfile1,STDOUT_FILENO); 
                        if(check2 == -1){
                            printf("%s\n", "dup2 Failed");
                        }

                        fflush(stdout); 
                         execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        close(rightfile);
                        close(rightfile1);

                      
                        retCode = EXIT_SUCCESS;
                        exit(EXIT_SUCCESS);
                    }

                    else if (childOrNot == -1){
                        retCode = EXIT_FAILURE;
                        exit(EXIT_FAILURE);
                    }
                    else{
                        int test = waitpid(childOrNot,&status,WNOHANG);
                        addPid(childOrNot, test);
                        if(WIFEXITED(&status) !=0){
                        retCode=EXIT_SUCCESS;
                    }
                        else{
                            retCode = EXIT_FAILURE;
                        }       
                    }
                
            
            
            }
            //CASE FOR A < B < C
            else if((strcmp(cmdArray[case1],"<") == 0 || strcmp(cmdArray[case1],"1<") == 0
                    || strcmp(cmdArray[case1],"0<") == 0 || strcmp(cmdArray[case1],"2<") == 0) 
                    &&
                    (strcmp(cmdArray[case2],"<") == 0 || strcmp(cmdArray[case2],"1<") == 0
                    || strcmp(cmdArray[case2],"0<") == 0 || strcmp(cmdArray[case2],"2<") == 0) ){
                        
                        incrPgid(2);
                        childOrNot = fork();
                        int status = 0;
                        if(childOrNot==0){

                        int rightfile = 0 ;
                        rightfile = open(cmdArrayNew[case1+1],O_RDONLY 

                            |O_CLOEXEC | S_IWUSR | S_IRUSR , 0666);
                      
                        int check = dup2(rightfile,STDIN_FILENO); 
                        if(check == -1){
                            printf("%s\n", "dup2 Failed");
                        }
                      

                        fflush(stdout); 
                        
                        if(rightfile == -1){
                            printf("%s\n", "file failed");
                        }
                        
                       // printf("%s\n",cmdArrayNew[0] );
                        //printf("%s\n", cmdArrayNew[case1+1]);
                        execvp(cmdArrayNew[0],&cmdArrayNew[0]);
                        close(rightfile);
                        retCode = EXIT_SUCCESS;
                        exit(EXIT_SUCCESS);
                    }

                    else if (childOrNot == -1){
                        retCode = EXIT_FAILURE;
                        exit(EXIT_FAILURE);
                    }
                    else{
                        int test = waitpid(childOrNot,&status,WNOHANG);
                        addPid(childOrNot, test);
                        if(WIFEXITED(&status) !=0){
                        retCode=EXIT_SUCCESS;
                    }
                        else{
                            retCode = EXIT_FAILURE;
                        }       
                    }

            }
    }
    
        else if(strcmp(cmdArray[0],"help")==0){
            childOrNot = fork();
            int status = 0;
            if(childOrNot==0){
                printHelp();
                retCode = EXIT_SUCCESS;
                exit(EXIT_SUCCESS);
            }

            else if (childOrNot == -1){
                retCode = EXIT_FAILURE;
               exit(EXIT_FAILURE);
            }
            else{
                int test = waitpid(childOrNot,&status,WNOHANG);
                addPid(childOrNot, test);
                incrPgid(1);
                if(WIFEXITED(&status) !=0){
                    retCode=EXIT_SUCCESS;
                }
                else{
                    retCode = EXIT_FAILURE;
                }
            }
            
        }

        else if(strcmp(cmdArray[0],"exit")==0){
            retCode = EXIT_SUCCESS;
            exit(3);
        }
        
        
        else if(strcmp(cmdArray[0],"cd")==0){
            if( cmdArray[1] == NULL){
             
                //printf("%s\n","hello?" );
                chdir(getenv("HOME"));

                //printf("This is before the swap%s\n", curDir);
               // printf("Before the swap%s\n", prevDir);
            
                
                
                getcwd(curDir,size);
                strncpy(prevDir,curDir,size);
               
                //printf("%s\n", curDir);
              //  printf("%s\n", prevDir);
            //printf("%s\n", getenv("HOME"));
                retCode = EXIT_SUCCESS;
            
        }
       
        
        else if(strcmp(cmdArray[1],"..")==0){
            
            chdir("..");
            strncpy(prevDir,curDir,size);
            getcwd(curDir,size);
            retCode = EXIT_SUCCESS;
             
        }
        else if(strcmp(cmdArray[1],".")==0){
            chdir(".");
            strncpy(prevDir,curDir,size);
            getcwd(curDir,size);
            retCode = EXIT_SUCCESS;
        }
        else if(strcmp(cmdArray[1],"-")==0){
           // printf("%s\n", "Reaching here?");
           
                
              //  printf("%s\n", prevDir);
                if(strlen(prevDir)!=0){
                   // printf("%s\n", "Reaching here??");
                    chdir(prevDir);
                    strncpy(prevDir,curDir,size);
                    getcwd(curDir,size);
                    retCode = EXIT_SUCCESS;
                }
                else{
                    printf("%s\n","bash: cd: OLDPWD not set" );
                    retCode = EXIT_FAILURE;
                }

             
            }

          
        
        //CASE WHERE WE SWAP DIRECTORYS ACCORDING TO THE ARRAY
        else{
            //char * waste = realloc(waste, sizeof(cmdArray[1]) * sizeof(char));
            //printf("%s\n","should be here" );
            chdir(cmdArray[1]);
            strncpy(prevDir,curDir,size);
            getcwd(curDir,size);
            retCode = EXIT_SUCCESS;
        }


        }
       
        
        else if(strcmp(cmdArray[0],"pwd")==0){
            childOrNot = fork();
            int status = 0;
            if(childOrNot==0){
                printf("%s\n", curDir);
                retCode = EXIT_SUCCESS;
                exit(EXIT_SUCCESS);
            }

            else if (childOrNot == -1){
                retCode = EXIT_FAILURE;
               exit(EXIT_FAILURE);
            }
            else{
                
                //printf("%i\n",pids[pidsSize] );
                int test = waitpid(childOrNot,&status,WNOHANG);
                addPid(childOrNot, test);
                incrPgid(1);
                if(WIFEXITED(&status) !=0){
                    retCode=EXIT_SUCCESS;
                }
                else{
                    retCode = EXIT_FAILURE;
                }
            }
        }
        else if(strcmp(cmdArray[0],"jobs")==0){
            printf("%s","" );
            printJobs();
        }
        else if(strcmp(cmdArray[0],"prt")==0){
            childOrNot = fork();
            int status = 0;
            if(childOrNot==0){
                printf("%i\n", retCode);
                retCode = EXIT_SUCCESS;
                exit(EXIT_SUCCESS);
            }

            else if (childOrNot == -1){
                retCode = EXIT_FAILURE;
               exit(EXIT_FAILURE);
            }
            else{
                int test = waitpid(childOrNot,&status,WNOHANG);
                addPid(childOrNot, test);
                incrPgid(1);
                if(WIFEXITED(&status) !=0){
                    retCode=EXIT_SUCCESS;
                }
                else{
                    retCode = EXIT_FAILURE;
                }
            }
            
        }
        else if(strcmp(cmdArray[0],"chpmt")==0){
            if(cmdArray[1] ==NULL || cmdArray[2]==NULL){
                retCode = EXIT_FAILURE;
                printf("%s\n", "Usage: chpmt SETTING TOGGLE");
                break;
            }
            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"0")==0){
                //printf("%s\n", "case 1");
                //printf("%s\n", cmdArray[1]);
                userBool = 0;
                retCode = EXIT_SUCCESS;
            }
            else if(strcmp(cmdArray[1],"user")==0 && strcmp(cmdArray[2],"1")==0){
                //printf("%s\n", "case 2");
                //printf("%s\n", cmdArray[1]);
                userBool = 1;
                retCode = EXIT_SUCCESS;
            }
            else if(strcmp(cmdArray[1],"machine")==0 && strcmp(cmdArray[2],"0")==0){
               // printf("%s\n", "case 3");
                //printf("%s\n", cmdArray[1]);
                machBool = 0;
                retCode = EXIT_SUCCESS;
            }
            else if(strcmp(cmdArray[1],"machine")==0 && strcmp(cmdArray[2],"1")==0){
                //printf("%s\n", "case 4");
                //printf("%s\n", cmdArray[1]);
                machBool = 1;
                retCode = EXIT_SUCCESS;
            }
            else{
                printf("%s\n", "Usage: chpmt SETTING TOGGLE");
                retCode = EXIT_FAILURE;
            }
            updatePrompt();
            
        }
        else if(strcmp(cmdArray[0],"chclr")==0){
            if(cmdArray[1] ==NULL || cmdArray[2]==NULL ||cmdArray[3] ==NULL){
                retCode = EXIT_FAILURE;
                printf("%s\n", "Usage: chclr SETTING COLOR BOLD");
                break;
            }

            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"red")==0){
                userCol = 1;
               
            }
            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"blue")==0){
                printf("%s\n","here?" );
                userCol = 2;
               
            }
            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"green")==0){
              
                userCol = 3;
            }
            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"yellow")==0){
                userCol = 4;
               
            }
            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"cyan")==0){
                userCol = 5;
               
            }
            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"magenta")==0){
                userCol = 6;
               
            }
            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"black")==0){
                userCol = 7;
               
            }
            else if(strcmp(cmdArray[1],"user") ==0&& strcmp(cmdArray[2],"white")==0){
                userCol = 8;
               
            }
             else if(strcmp(cmdArray[1],"machine") ==0&& strcmp(cmdArray[2],"red")==0){
                machCol = 1;
               
            }
            else if(strcmp(cmdArray[1],"machine") ==0&& strcmp(cmdArray[2],"blue")==0){
                machCol = 2;
               
            }
            else if(strcmp(cmdArray[1],"machine") ==0&& strcmp(cmdArray[2],"green")==0){
                machCol = 3;
               
            }
            else if(strcmp(cmdArray[1],"machine") ==0&& strcmp(cmdArray[2],"yellow")==0){
                machCol = 4;
               
            }
            else if(strcmp(cmdArray[1],"machine") ==0&& strcmp(cmdArray[2],"cyan")==0){
                machCol = 5;
               
            }
            else if(strcmp(cmdArray[1],"machine") ==0&& strcmp(cmdArray[2],"magenta")==0){
                machCol = 6;
               
            }
            else if(strcmp(cmdArray[1],"machine") ==0&& strcmp(cmdArray[2],"black")==0){
                machCol = 7;
               
            }
            else if(strcmp(cmdArray[1],"machine") ==0&& strcmp(cmdArray[2],"white")==0){
                machCol = 8;
               
            }
            if(strcmp(cmdArray[3],"1") == 0){
                boldBool = 1;
            }
            else{
                boldBool = 0;
            }
            updatePrompt();

           // textcolor("31m");
        }
        
        else if(strcmp(cmdArray[0],"fg")==0){
            if(cmdArray[1]!=NULL){
            printf("This brings the job with a PID of %s to the foreground\n", cmdArray[1]);
            int x = atoi(cmdArray[1]);
                kill(x,SIGCONT);
        }
        else{
            printf("%s\n", "fg [pid]");
        }
        }
        else if(strcmp(cmdArray[0],"bg")==0){
            if(cmdArray[1]!=NULL){
                int x = atoi(cmdArray[1]);
                printf("%i\n", x);
                kill(x,SIGSTOP);
                printf("This brings the job with a PID of %s to the background\n", cmdArray[1]);
            }
            else{
                printf("%s\n", "bg [pid]");
            }   
            
        }
        else if(strcmp(cmdArray[0],"kill")==0){
            if(cmdArray[1]== NULL){
                printf("%s\n","Function is kill [signal] PID|JID" );
            }
            else if (cmdArray[2]==NULL){
                int x = atoi(cmdArray[1]);
                kill(x,SIGTERM);

            }else{
                int x = atoi(cmdArray[1]);
                int y = atoi(cmdArray[2]);
                kill(x,y);
            }
        }

        else if(strcmp(cmdArray[0],"disown")==0){
            if(cmdArray[1] != NULL){
            int disown = atoi(cmdArray[1]);
            //kill(pids[disown],SIGTERM);
            disownThis(disown);

        }
        else{
            int killer = 0 ;
            for(killer = 0 ; killer < pidsSize;killer ++){
               // kill(pids[killer],SIGTERM);
                disownThis(pids[killer]);
                
            }
        }


        }
        //EXECVP
        else {

            int apple = -50;
            childOrNot = fork();
            int status = 0;
            if(childOrNot==0){

                
                //printf("before%s\n", cmdArray[0]);
                int whatToDo = 0;
                whatToDo = fileExist();
                if(whatToDo == 0){ 
                  //  printf("%s\n","here" );
                    //printf("This should be it%s \n", cmdArray[0]);
                    //printf("Array 2%s\n", cmdArray[1]);
                    // printf("%s\n","box 1 There was a /" );
                    // printf("CmdArray 0%s\n",cmdArray[0] );
                    apple = execvp(cmdArray[0], &cmdArray[0]);
                    
                    //printf("%s\n","wtf?" );
                
                }
                else if(whatToDo == 1){
                    //printf("%s\n","box 2 It was found" );
                    //printf("%s\n", "here1");
                    //printf("%s\n", cmdArray[0]);
                    // printf("CmdArray 0%s\n",cmdArray[0] );
                    // printf("CmdArray 0%s\n",cmdArray[1] );
                    // printf("CmdArray 0%s\n",cmdArray[2] );
                    apple = execvp(cmdArray[0], &cmdArray[0]);
                
                }
                else{
                    printf("%s\n","No such Command" );
                }
                

                
                exit(EXIT_SUCCESS);
                
                
            }

            else if (childOrNot == -1){
                retCode = EXIT_FAILURE;
               exit(EXIT_FAILURE);
            }
            else{
                int test = waitpid(childOrNot,&status,WNOHANG);
                // printf("APPLE : %i\n", apple);
                if((strcmp(cmdArray[0],"help")==0)||
                    (strcmp(cmdArray[0],"exit")==0)||
                    (strcmp(cmdArray[0],"cd")==0)||
                    (strcmp(cmdArray[0],"pwd")==0)||
                    (strcmp(cmdArray[0],"jobs")==0)||
                    (strcmp(cmdArray[0],"prt")==0)||
                    (strcmp(cmdArray[0],"chpmt")==0)||
                    (strcmp(cmdArray[0],"chclr")==0)||
                    (strcmp(cmdArray[0],"fg")==0)||
                    (strcmp(cmdArray[0],"bg")==0)||
                    (strcmp(cmdArray[0],"kill")==0)||
                    (strcmp(cmdArray[0],"disown")==0)
                    ||
                    (apple!= -1)){
                    addPid(childOrNot,test);
                }
                
                incrPgid(1);
                if(WIFEXITED(&status) !=0){
                    retCode=EXIT_SUCCESS;
                }
                else{
                    retCode = EXIT_FAILURE;
                }
            }
            
        }

        //printf("End the loop starts%s\n",prevDir );
    }
       
       
    //free(cmdArray);
        //All your debug print statments should be surrounded by this #ifdef
        //block. Use the debug target in the makefile to run with these enabled.
       /*
        #ifdef DEBUG
        fprintf(stderr, "Length of command entered: %ld\n", strlen(cmd));
        #endif
        */
        //You WILL lose points if your shell prints out garbage values.
        free(cmd);
        free(cmdArray);
        /*
        if(stringToken1!=NULL){
            write(2,stringToken1,10000);
        free(stringToken1);
    }*/
      //  int lop = 0;
        
        
        if(cmdArrayNew!=NULL){
            /*
            for(lop = 0; lop < 6; lop++){
            if(cmdArrayNew[lop]!=NULL){
           // printf("%s\n", cmdArrayNew[lop]);
            free(cmdArrayNew[lop]);
        }
        }
        */
            free(cmdArrayNew);

        }
        /*
        free(part1);
        free(part2);
        free(part3);
        */
        updatePrompt();
        //printf("%s\n", "");
    }

    //Don't forget to free allocated memory, and close file descriptors.
    free(cmd);
    free(changePrompt);
    
    //WE WILL CHECK VALGRIND!

    return EXIT_SUCCESS;
}

int ctrlB (int cnt, int key) {
   printf("%s\n","#User presses Ctrl+B" );
   rl_on_new_line ();
   return 0;
}

int ctrlG (int cnt, int key) {
   printf("%s\n", "#User presses Ctrl+G");
   rl_on_new_line ();
   return 0;
}

int ctrlH (int cnt, int key) {
   printHelp();
   rl_on_new_line ();
   return 0;
}

int ctrlP (int cnt, int key) {
    printf("\n%s\n", "----Info----" );
    printf("%s\n", "Help");
    printf("%s\n", "prt");
    printf("%s\n", "----CTRL----");
    printf("%s\n", "cd");                                        
    printf("%s\n", "chclr");
    printf("%s\n", "chpmt");
    printf("%s\n", "pwd");
    printf("%s\n", "exit");
    printf("%s\n", "----Job Control----");
    printf("%s\n", "bg");
    printf("%s\n", "fg");
    printf("%s\n", "disown");
    printf("%s\n", "jobs");
    printf("%s\n", "----Number of Commands Run----");
    printf("%i\n", pidsSize);
    printf("%s\n", "----Process Table----");
    printf("%s\t\t%s\t\t%s\t\t%s\n","PGID","PID","TIME","CMD" );
    
    for (int i = 0; i < pidsSize; i ++)
    {
       
        //printf("This is the pids[i] %i\n", pids[i]);

        if(pids[i]==-1){
            
        }
        else{


        printf("%i", getpgid(pids[i]));
        printf("%s", "\t\t");
        
        printf("%i", pids[i]);
        printf("%s", "\t\t");

        printf("0.0%s", "");
        printf("%s", "\t\t");
        
        printf("%s\n", holder[i]);
        //printf("%s", pidArray[i]);

        



    }
    }
    rl_on_new_line ();
    return 0;
}


void disownThis(int disown){
    int x;
    for(x = 0; x < pidsSize; x ++){
        if(pids[x] == disown){
            pids[x] = -1;
            break;
        }
    }
}

void incrPgid(int incr){
    int x;
    for(x = 0; x < incr; x++){
        pgid[pgidSize+x] = pgidSize + 1;
    }
    
    pgidSize = pgidSize + incr;
}
void addPid(int pid,int waitpid){
    pids[pidsSize]= pid;
    pidsStatus[pidsSize] = waitpid;

    /*
    pidArray = realloc (pidArray, sizeof (char*) * ++pidsSize);
    pidsSize++;
    pidArray[pidsSize-1] = cmdArray[0];
    */

    // printf("This is dummy: %s\n",dummy );
    //holder[pidsSize] = dummy;
    //strncpy(holder[pidsSize],dummy,sizeof (char*) * PATH_MAX);
    holder[pidsSize] = malloc(sizeof (dummy));
    int x = sizeof(dummy);
    memset(holder[pidsSize],0,x);

    strcat(holder[pidsSize],dummy);
    // printf("This is pids size %s\n",holder[pidsSize] );
    pidsSize ++;

    usleep(5000);

}

void printJobs(){
    int start=0;
   
    for (int i = start; i < pidsSize; i ++)
    {

       
        int throw;
        int test = waitpid(pids[i],&throw,WNOHANG);

        // printf("waitpid : %i\n", test);
        // printf("pids[i] :  %i\n", pids[i] );
        if(pids[i]==-1){
            
        }
        else{
        printf(" [%i]", i+1);
        printf("%s", "   ");
        
        if(test==pids[i] || test ==-1){
            printf("%s", "Stopped");
        }else
        {
            printf("%s", "Running");
        }

        printf("%s", "   ");

        printf("%i", pids[i]);


        printf("%s", "   ");

        printf("%s\n", holder[i]);

        //printf("%s", pidArray[i]);

       

        if(i + 1 == pidsSize){
            printf("This is the exit status code of bg Job last ended : %i\n", throw);
        }

    }
    }
}

int fileExist ()
{
   

   if (strchr("/", *cmdArray[0])== NULL){ 

   }
   else{
    //printf("%s\n", "therels a /");
    return 0;
   }

   char* realPath = NULL;
    realPath = (char *) malloc ( sizeof (char*) * PATH_MAX);
    memset(realPath,0,strlen(realPath));

    char* useless = strdup(getenv("PATH"));
    realPath = strtok(useless,":");

    while (realPath) {
       //  printf("What you're looking for%s\n", path);
       // printf("%s\n", realPath);

        if (realPath == NULL)
        exit(EXIT_FAILURE); 


        //strcat(realPath,path);
        char* pleaseWork = NULL;
        pleaseWork = (char *) realloc (pleaseWork, sizeof (char*) * PATH_MAX);
        memset(pleaseWork,0,strlen(pleaseWork));

        strcat(pleaseWork,realPath);
        strcat(pleaseWork,"/");
        strcat(pleaseWork,cmdArray[0]);


        struct stat helpME;
        
        //printf("%s\n",pleaseWork );

        int test = stat ( pleaseWork, &helpME );
            if ( test == 0 )
     {
        free(pleaseWork);
        //printf("%s\n", "It exists;");
        return 1;
     }
     //return 0;
        free(pleaseWork);
        realPath = strtok (NULL, ":");
    }
   
   // printf("%s\n","doesnt exist" );
     return 2;
       
}


void splitArray(char* cmd){

    if(cmd==NULL){
        return;
    }
    //Extract tokens from string and use space as delimiter
    char * stringToken = strtok (cmd, " ");

    while (stringToken) {
    cmdArray = realloc (cmdArray, sizeof (char*) * ++arrSize);

    //If realloc failed, then we failed
    if (cmdArray == NULL)
        exit(EXIT_FAILURE); 
    
    //Save new token into global var cmd Array and go to next token
    cmdArray[arrSize-1] = stringToken;
  
    stringToken = strtok (NULL, " ");
    
    }

    
    cmdArray = realloc (cmdArray, sizeof (char*) * (arrSize+1));
    cmdArray[arrSize] = NULL;

    free(stringToken);

}


void splitArray1(char* cmd, int start , int end){

    if(cmd==NULL){
        return;
    }
    //printf("%s\n","called ONCE" );
    //printf(" THIS IS THE COMMAND : %s\n",cmd );
    
    //printf("start: %i end : %i\n",start,end );
    cmdArrayNew = realloc (cmdArrayNew, sizeof (char*) * PATH_MAX);

    int x ;
    for (x = 0 ; x < start ; x ++){
        
        cmdArrayNew[x]=extractString(x,x+1);
    }
    
    //free(extractString(0,start));

    if(end == 0){
        
    //cmdArrayNew = realloc (cmdArrayNew, sizeof (char*) * ++arrSize);
   // strncpy(cmdArrayNew[1],extractString(start+1,arrSize), sizeof (char*) * PATH_MAX);
        int x ;
    for (x = start + 1 ; x < arrSize ; x ++){
        
        cmdArrayNew[x]=extractString(x,x+1);
    }
    //cmdArrayNew[2]=extractString(start+1,arrSize);
   // free(stringToken1);
    }
    else{
    
    for (x = start + 1 ; x <arrSize ; x ++){
        
        cmdArrayNew[x]=extractString(x,x+1);
    }
    //cmdArrayNew = realloc (cmdArrayNew, sizeof (char*) * ++arrSize);
   // strncpy(cmdArrayNew[1],extractString(start + 1,end), sizeof (char*) * PATH_MAX);
    //cmdArrayNew[2]=extractString(start+1,end);
   // free(stringToken1);
    
    for (x = end + 1 ; x < arrSize ; x ++){
        
        cmdArrayNew[x]=extractString(x,x+1);
    }
    //cmdArrayNew = realloc (cmdArrayNew, sizeof (char*) * ++arrSize);
   // strncpy(cmdArrayNew[2],extractString(end + 1,arrSize), sizeof (char*) * PATH_MAX);
    //cmdArrayNew[4]=extractString(end+1,arrSize);
    //free(stringToken1);
  
    }
    
    if(end == 0){
        cmdArrayNew[start] = NULL;
        cmdArrayNew[arrSize] = NULL;
        //printf("Arg Size : %i\n", arrSize);
        //printf("arrS -2 : %s\n", cmdArrayNew[arrSize-2]);
    }
    else{
        cmdArrayNew[start] = NULL;
        cmdArrayNew[end] = NULL;
        cmdArrayNew[arrSize] = NULL;
    }

   // printf("This is what we get for new CmdArray0 : %s\n", cmdArrayNew[0]);
    //printf("This is what we get for new CmdArray2 : %s\n", cmdArrayNew[2]);
    //printf("This is what we get for new CmdArray4 : %s\n", cmdArrayNew[4]);
    /*
    printf("%s\n", cmdArrayNew[0]);
    printf("%s\n", cmdArrayNew[1]);
   // printf("%s\n", cmdArrayNew[2]);
    printf("%s\n", cmdArrayNew[3]);
    printf("%s\n", cmdArrayNew[4]);
    //printf("%s\n", cmdArrayNew[5]);
    printf("%s\n", cmdArrayNew[6]);
    printf("%s\n", cmdArrayNew[7]);
    printf("%s\n", cmdArrayNew[8]);
    */
    //printf("%s\n", cmdArrayNew[5]);
    
  // printf("Command array 0%s\n",cmdArrayNew[0] ); 
   //printf("Command array 1 %s\n",cmdArrayNew[1] );    
   // printf("%s\n",cmdArrayNew[2] );       

}


// PRINT THE HELP MENU
void printHelp(){
    

    printf("%s\n", "help - Prints out help menu");
    printf("%s\n", "exit - Exits the program");
    printf("%s\n", "cd - change to directory, - , .. , ., [dir]");
    printf("%s\n", "pwd - prints absolute path ");
    printf("%s\n", "prt - prints return code of previous command exec");
    printf("%s\n", "chpmt - Change prompt settings");
    printf("%s\n", "chclr - change prompt colors");
    printf("%s\n", "jobs - Display list all jobs running in background");
    printf("%s\n", "fg - make specified job go into foreground");
    printf("%s\n", "bg - make specified job go into background");
    printf("%s\n", "kill - send signal to pid");
    printf("%s\n", "disown - disown [pid] ");
}

char* extractString(int lowerBound,int upperBound){
   
 
    char * test = NULL;
    test = (char *) malloc (sizeof (char*) * PATH_MAX);
    memset(test,0,strlen(test));
    /*
    if(test!=NULL){
        free(test);
        test = (char *) realloc (test, sizeof (char*) * PATH_MAX);
    }
    */
 //   printf("%i\n",lowerBound );
   // printf("%i\n", upperBound);
    int x = lowerBound;
    int y = upperBound;
    for(; x<y; x++){
       // printf("What test should be : %s\n", test);
        //printf("What gets added to test: %s\n", cmdArray[x]);
        strcat(test, cmdArray[x]);
        
        if(x+1 !=y){
        strcat(test, " ");
        }
    }
    //strcat(test, "\n");
    

   // printf("This is the string token: %s <<<<< \n", test);
    return test;
}


void updatePrompt(){
    
    char* mach = NULL;
    mach = (char *) realloc (mach, sizeof (char*) * PATH_MAX);
    memset(mach,0,strlen(mach));
    gethostname(mach,PATH_MAX);

    char* user = NULL; 
    user = (char *) realloc (user, sizeof (char*) * PATH_MAX);
    memset(user,0,strlen(user));
   // user = getenv("USERNAME");
    strncpy(user,getenv("USER"),sizeof (char*) * PATH_MAX);


    char* dir = NULL;
    dir = (char *) realloc (dir, sizeof (char*) * PATH_MAX);
    memset(dir,0,strlen(dir));
    getcwd(dir,sizeof(char*)*PATH_MAX);

    char* home = NULL;
    home=  (char *) realloc (home, sizeof (char*) * PATH_MAX);
    memset(home,0,strlen(home));
    strncpy(home,getenv("HOME"),sizeof (char*) * PATH_MAX);

    

    if(strcmp(home,dir)==0){
        strncpy(dir,"~",sizeof (char*) * PATH_MAX );
        //printf("SAME%s\n", dir);

    }
    else{
        dir =dir +strlen(home);
        //printf("NOT THE SAME%s\n", dir);
    }


    char* finString = NULL;
    finString = (char *) realloc (finString, sizeof (char*) * PATH_MAX);
    memset(finString,0,strlen(finString));
    strncpy(finString,"",sizeof (char*) * PATH_MAX);

    

    strcat(finString, "sfish");



    if(userBool && machBool){
        strcat(finString,"-");
        //printf("user colr : %i mach Col %i\n", userCol, machCol);
        if(userCol == 1){
            strcat(finString,"\x1b[0;31m");
        }
        if(userCol == 2){
            strcat(finString,"\x1b[0;34m");
        }
        if(userCol == 3){
            strcat(finString,"\x1b[0;32m");
        }
        if(userCol == 4){
            strcat(finString,"\x1b[0;33m");
        }
        if(userCol == 5){
            strcat(finString,"\x1b[0;36m");
        }
        if(userCol == 6){
            strcat(finString,"\x1b[0;35m");
        }
        if(userCol == 7){
            strcat(finString,"\x1b[0;30m");
        }
        if(userCol == 8){
            strcat(finString,"\x1b[0;37m");
        }


        strcat(finString,user);
        strcat(finString,"\x1b[0;0m");
        strcat(finString,"@");

        if(machCol == 1){
            strcat(finString,"\x1b[0;31m");
        }
        if(machCol == 2){
            strcat(finString,"\x1b[0;34m");
        }
        if(machCol == 3){
            strcat(finString,"\x1b[0;32m");
        }
        if(machCol == 4){
            strcat(finString,"\x1b[0;33m");
        }
        if(machCol == 5){
            strcat(finString,"\x1b[0;36m");
        }
        if(machCol == 6){
            strcat(finString,"\x1b[0;35m");
        }
        if(machCol == 7){
            strcat(finString,"\x1b[0;30m");
        }
        if(machCol == 8){
            strcat(finString,"\x1b[0;37m");
        }

        strcat(finString,mach);
        strcat(finString,"\x1b[0;0m");
    }
    else if(userBool== 0 && machBool){
        strcat(finString,"-");
        strcat(finString,"\x1b[0;0m");
        strcat(finString,"@");

        if(machCol == 1){
            strcat(finString,"\x1b[0;31m");
        }
        if(machCol == 2){
            strcat(finString,"\x1b[0;34m");
        }
        if(machCol == 3){
            strcat(finString,"\x1b[0;32m");
        }
        if(machCol == 4){
            strcat(finString,"\x1b[0;33m");
        }
        if(machCol == 5){
            strcat(finString,"\x1b[0;36m");
        }
        if(machCol == 6){
            strcat(finString,"\x1b[0;35m");
        }
        if(machCol == 7){
            strcat(finString,"\x1b[0;30m");
        }
        if(machCol == 8){
            strcat(finString,"\x1b[0;37m");
        }

        strcat(finString,mach);

        strcat(finString,"\x1b[0;0m");
    }
    else if(userBool && machBool ==0){
        strcat(finString,"-");
        if(userCol == 1){
            strcat(finString,"\x1b[0;31m");
        }
        if(userCol == 2){
            strcat(finString,"\x1b[0;34m");
        }
        if(userCol == 3){
            strcat(finString,"\x1b[0;32m");
        }
        if(userCol == 4){
            strcat(finString,"\x1b[0;33m");
        }
        if(userCol == 5){
            strcat(finString,"\x1b[0;36m");
        }
        if(userCol == 6){
            strcat(finString,"\x1b[0;35m");
        }
        if(userCol == 7){
            strcat(finString,"\x1b[0;30m");
        }
        if(userCol == 8){
            strcat(finString,"\x1b[0;37m");
        }


        strcat(finString,user);
        strcat(finString,"\x1b[0;0m");
    }


    strcat(finString,":");
    strcat(finString,"[");
    
    strcat(finString,dir);

    strcat(finString,"]");
    strcat(finString,"> ");

    changePrompt = (char *) realloc (changePrompt, sizeof (char*) * PATH_MAX);
    memset(changePrompt,0,strlen(changePrompt));
    strncpy(changePrompt,finString,sizeof (char*) * PATH_MAX);
   
    
    
    free(mach);

    if(strcmp(dir,"~") == 0){
        free(dir);
    }
    else{
        free(dir-strlen(home));
    }
    free(home);
    free(user);
    free(finString);



    /*
    free(finString);
    //free(dir);
    free(mach);
    free(user);
    free(home);

*/
    //printf("%s\n", finString);
}

// BOOLEAN TO SEE IF THE PATH EXISTS :)

int existPath(char* cmd){
    int boolean = 0;

    /*
    char * path;
    path = (char *) realloc (path, sizeof (char*) * PATH_MAX);
    strncpy(path,getenv("PATH"),sizeof (char*) * PATH_MAX);

     while (stringToken) {
    cmdArray = realloc (cmdArray, sizeof (char*) * ++arrSize);

    //If realloc failed, then we failed
    if (cmdArray == NULL)
        exit(EXIT_FAILURE); 
    
    //Save new token into global var cmd Array and go to next token
    cmdArray[arrSize-1] = stringToken;
  
    stringToken = strtok (NULL, " ");
    
    }
    */
    return boolean;
}