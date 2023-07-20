#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

typedef struct TaskScheduler{
    int id;
    string tsk;
    struct TaskScheduler *next;
    struct TaskScheduler *prev;
}task;

task *home = NULL;
task *bin = NULL;

void mainSecondary();
void CreateTask();
task *DeleteTask(int); 
void TaskBin();
void ShowTask();
void ShowBin();
void prioritize();
void BackupList();

int main(){
    cout<<"             To do List\n";
    while(1){
        int n;
        cout<<"1. MENU BAR\t\t2. CLOSE PROGRAM\n";
        cin>>n;
        switch(n){
        case 1:mainSecondary(); break;
        case 2: exit(0);
        default: cout<<"Enter a valid option\n";
        }
    }
}

void mainSecondary(){
    while(1){
        int n;
        cout<<"\nEnter a choice\n";
        cout<<"1. Create task\t2. Delete Task\t3. Show tasks\t4. Show bin\t5.Prioritize tasks\t6. exit\nchoice: ";
        cin>>n;
        switch(n){
        case 1: CreateTask(); break;
        case 2: TaskBin(); break;
        case 3: ShowTask(); break;
        case 4: ShowBin(); break;
        case 5: prioritize(); break;
        case 6: BackupList(); return;
        default: cout << "\nEnter a valid choice\n";
        }
    }
}

void CreateTask(){
    task *node,*temp;
    node = new task;

    if(home==NULL){
        node->next=NULL;
        node->prev=NULL;
        node->id=1;
        home=node;
    }
    else{
        temp = home;
        int idd = home->id + 1;
        while(temp->next != NULL){
            temp = temp->next;
            idd++;
        }
        node->next = NULL;
        node->prev = temp;
        node->id = idd;
        temp->next = node;
    }
    cout<<"Enter task:\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, node->tsk);

    ShowTask();
}

task *DeleteTask(int s){
    task *temp;

    int k = 0;
    temp = home;
    while(temp!=NULL && temp->id != s)
        temp = temp->next;
    if(temp==NULL)
        return NULL;
    
    if(home==temp){
        home=temp->next;
        if (home != NULL)
            home->prev = NULL;
    }
    else{
        temp->prev->next = temp->next;
        if (temp->next != NULL)
            temp->next->prev = temp->prev;
    }
    

    task *ptr;
    ptr=home;
    int newId=1;
    while(ptr!=NULL){
        ptr->id=newId;
        ptr=ptr->next;
        newId++;
    }
    return temp;
}

void TaskBin(){
    if(home == NULL)
        cout << "\nNo tasks in list!\n";
    else{
        int s;
        cout<<"\nEnter serial number to delete:";
        cin>>s;
        task *temp = DeleteTask(s);
        if(temp==NULL) cout<<"\nNo tasks found!\n";
        else{
        temp->next = bin;       //as a stack.
        bin = temp;
        }
    }
    ShowTask();
}

void ShowBin(){
    task *temp = bin;
    if(temp == NULL)
        cout << "\nBin empty!\n";
    else{
        cout<<'\n';
        while(temp != NULL){
            cout<<temp->id<<". "<<temp->tsk<<'\n';
            temp = temp->next;
        }
    }
}

void ShowTask(){
    Sleep(300);
    task *temp;
    if(home == NULL)
        cout<<"\nNo tasks in list\n";
    else{
        temp = home;
        cout<<'\n';
        while(temp != NULL){
            cout<<temp->id<<". "<<temp->tsk<<'\n';
            temp = temp->next;
        }
        cout<<'\n';
    }
}

void prioritize(){
    if(home == NULL)
        cout<<"\nNo task in list!\n";
    else if(home->next==NULL)
        cout<<"\nCannot prioritize only one task!\n";
    else{
        int s;
        cout<<"\nEnter serial number to priritize to top:\n";
        cin>>s;
        task *temp = DeleteTask(s);
        if(temp==NULL) cout<<"\nNo tasks found!\n";
        else{
            temp->next=home;
            home->prev=temp;
            home=temp;
        }

        task *ptr;
        ptr = home;
        int newId = 1;
        while(ptr!=NULL){
            ptr->id = newId;
            ptr = ptr->next;
            newId++;
        }
    }
    ShowTask();
}

void BackupList(){
    ofstream of;
    of.open("backup.txt",ios::app);

    task *temp;
    temp = home;
    while(temp != NULL){
        of<<temp->tsk<<"\n";
        temp=temp->next;
    }
    of.close();
    exit(0);
}