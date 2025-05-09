#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

const char mainIcon[] = "/home/zoxlemonade/learningc/to_do_list/assets/icons/to-do-list-icon.txt";
const char TaskList[] = "/home/zoxlemonade/learningc/to_do_list/assets/tasklist.txt";
char task[256];
int task_no = 0;
int input;
int show_invalid = 0;



void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearscreen(void)
{
    printf("\033[H\033[J");
}

void print_options(void){
    printf("Select one option\n\n1. Add a new task\n2. Review incomplete task\n3. Review completed task\n4. List all Tasks\n5. Remove task\n6. Exit\n\n");
}

void welcome_icon(void);
int load_assets(void);
void home(void);
int add_task();
void incomplete_task();
void completed_task();
void list_task();
void remove_task();


int main(void)
{
    int status = load_assets();
    if(status != 0){
        printf("Exiting the program...\n");
        return 1;
    }
 
       
    sleep(1);

    FILE *file = fopen(TaskList, "r");
    while(fgets(task, sizeof(task),file))
        {
            int max = 0;
            if(sscanf(task, "%d.", &task_no) == 1)
            {
                if(max > task_no)
                task_no = max;
            }
        }

    home();
}



void welcome_icon(void)
{
    FILE *file = fopen(mainIcon, "r");
    if(!file)
    {
        fprintf(stderr, "Error: Could not found \"%s\"\n", mainIcon);
    }

    char asciiArt[sizeof(mainIcon)];
    while(fgets(asciiArt, sizeof(asciiArt), file))
    {
        printf("%s", asciiArt);
    }
    fclose(file);
}

int load_assets(void)
{

    FILE *file= fopen(TaskList, "r");
    if(file== NULL)
    {
       printf("You are missing TaskList file. Would you like to create it? y/n ");
           char ans = getchar(); 
           flush_input();
           if(ans != 'y')
           {
                return 1;
           }
           else{
               char make_file[256];
                snprintf(make_file, sizeof(make_file), "touch %s", TaskList);
                int result = system(make_file);
                if(result == 0)
                {
                    printf("File created successfully\n");
                }
                else{
                    printf("FIle could not be created\n");
                    return 1;
                }
                }
    }      
    else
    {
       printf("Assets successfully loaded\n");
    }
    return 0;
}

void home(void)
{
    clearscreen();
    welcome_icon();
    print_options();

        if (show_invalid) 
        {
        printf("\nInvalid input! Please try again.\n");
        show_invalid = 0;
        }
        scanf("%d", &input);
        flush_input();
       switch (input)
       {
           case 1:
               clearscreen();
               welcome_icon();
               add_task();
               break;
           case 2:
               clearscreen();
               welcome_icon();
               incomplete_task();
               break;
           case 3:
               clearscreen();
               welcome_icon();
               completed_task();
               break;
           case 4:
               clearscreen();
               welcome_icon();
               list_task();
               break;
           case 5:
               clearscreen();
               welcome_icon();
               remove_task();
               break;
           case 6:
            clearscreen();
            exit(0);
           default:
            show_invalid = 1;
            break;
       }
}


int add_task()
{
    FILE *file = fopen(TaskList, "a");
    if(file == NULL)
    {
        printf("Error\n");
        return 1;
    }

    int flag = 1;
    
    do
    {
    printf("Enter a task: ");
    fgets(task, sizeof(task), stdin);

    task[strcspn(task, "\n")] = '\0';

    if(strcmp(task, "exit") == 0)
    {
        flag = 0;  
    }

    else if(strlen(task)>0)
    {
    fprintf(file,"%d. %s\n", ++ task_no, task); 
    printf("Task successfully added!\n");
    }
    
    }while(flag == 1);

fclose(file);
home();
return 0;
}



void incomplete_task()
{
}

void completed_task()
{
}

void list_task()
{
    
    printf("List of All Tasks:\n");
    FILE *file = fopen(TaskList, "r");
    if(file == NULL)
    {
        printf("Error\n");
    }


    while(fgets(task, sizeof(task), file))
        printf("%s", task);
    fclose(file);
    
    printf("Press enter to return to home");
    flush_input();
    home();
}


void remove_task()
{

}
