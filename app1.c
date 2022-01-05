#include<stdio.h>
#include<string.h>
typedef struct student
{
int rollNumber;           
char name[37];
char gender;
}struct1;

void addStudent()
{
struct1 g,t;
char m;
FILE *f;
printf("Enter Roll Number: ");
scanf("%d",&g.rollNumber); fflush(stdin);
if(g.rollNumber<=0) 
{
printf("Invalid roll number\n");
return;
}
f=fopen("student.data","rb");
if(f!=NULL)
{
while(1)
{

fread(&t,sizeof(struct1),1,f);
if(feof(f)) break;
if(t.rollNumber==g.rollNumber) 
{
printf("Roll number (%d) already exist....\n",g.rollNumber);
fclose(f);
return;
}
}
fclose(f);
}

printf("Enter Name : ");
fgets(g.name,37,stdin); fflush(stdin);
g.name[strlen(g.name)-1]='\0';
printf("Gender (M/F) : ");
g.gender=getchar(); fflush(stdin);

if(g.gender!='M' && g.gender!='m' && g.gender!='F' && g.gender!='f')
{
printf("Invalid Gender...\n");
return;
}

printf("save Y/N : ");
m=getchar(); fflush(stdin);
if(m!='y' && m!='Y')
{
printf("student not added\n");
return;
}

f=fopen("student.data","ab");
fwrite(&g,sizeof(struct1),1,f);
fclose(f);
printf("student added, Press enter to continue... ");
getchar(); fflush(stdin);

}

void dash(char m,int num)
{
for(; num>0; num--) printf("%c ",m);
}

void viewDetails()
{
struct1 g;
FILE *f;
int sno=1,j=0,page=1;
f=fopen("student.data","rb");
if(f==NULL) 
{
printf("no student added, press enter to continue.......");
getchar(); fflush(stdin);
printf("\n\n");
return;
}

while(1)
{

fread(&g,sizeof(struct1),1,f);
if(feof(f))
{
printf("\n_ _ _ _ End of the list ");
dash('_',49);
printf("\nPress enter to continue....");
getchar(); fflush(stdin);
break;
}

if(j==0)
{
dash('_',60);
printf("\n \n%60s %d \n\n","Student Module Page",page);
dash('_',60);
printf("\n%-8s %-20s %-30s %-6s\n","S.No","Roll Number","Name","Gender");
j=1;
}

printf("%-8d %-20d %-30s ",sno,g.rollNumber,g.name);
if(g.gender=='m' || g.gender=='M') printf("%-6s\n","Male");
else printf("%-6s\n","Female");

if((sno)%5==0)
{
printf("Page completed, press enter to continue...");
getchar(); fflush(stdin);
j=0;
page++;
}

sno++;
}


}

void removeStudent()
{
struct1 g;
FILE *f,*e;
char ch;

dash('_',60);
printf("\n%60s\n","Remove Module");
dash('_',60);

int rollNumber,found=0;


f=fopen("student.data","rb");
if(f==NULL)
{
printf("\nno student in list to remove...\n");
return;
}

printf("\nEnter roll number to Remove student : ");
scanf("%d",&rollNumber); fflush(stdin);

while(1)
{
fread(&g,sizeof(struct1),1,f);
if(feof(f))
{
printf("roll number(%d) is not in list\n",rollNumber);
break;
}
if(rollNumber==g.rollNumber)
{
printf("Are you sure to remove %s (Y/N): ",g.name);
ch=getchar(); fflush(stdin);
if(ch=='y' || ch=='Y') found=1;
else printf("process aborted by user...\n");
break; 
}
}

fclose(f);

if(found)                       //removing student
{
e=fopen("temp.data","wb");
f=fopen("student.data","rb");

while(1)                        //copying data to temp.data
{
fread(&g,sizeof(struct1),1,f);
if(feof(f)) break;
if(rollNumber==g.rollNumber) {}
else fwrite(&g,sizeof(struct1),1,e);
}
fclose(f);
fclose(e);

f=fopen("student.data","wb");
e=fopen("temp.data","rb");
while(1)
{
fread(&g,sizeof(struct1),1,e);
if(feof(e)) break;
fwrite(&g,sizeof(struct1),1,f);
}
fclose(f);
fclose(e);

printf("Student Removed...\n");
}

dash('_',60);
printf("\nPress enter key to continue....");
getchar(); fflush(stdin);
}

void editStudent()
{

struct1 g,t;
FILE *f,*e;
char ch;

dash('_',60);
printf("\n%60s\n","Edit Module");
dash('_',60);

int rollNumber,found=0;

f=fopen("student.data","rb");
if(f==NULL)
{
printf("\nno student in list to edit...\n");
return;
}

printf("\nEnter roll number to Edit details : ");
scanf("%d",&rollNumber); fflush(stdin);

while(1)
{
fread(&g,sizeof(struct1),1,f);
if(feof(f))
{
printf("roll number(%d) is not in list\n",rollNumber);
break;
}
if(rollNumber==g.rollNumber)
{
printf("Are you sure to edit %s (Y/N): ",g.name);
ch=getchar(); fflush(stdin);
if(ch=='y' || ch=='Y') found=1;
else printf("process aborted by user...\n");
break; 
}
}

fclose(f);

if(found)                       //edit student
{

printf("Enter new name: ");              //New name and gender
fgets(g.name,37,stdin); fflush(stdin);
g.name[strlen(g.name)-1]='\0';
printf("Gender (M/F): ");
g.gender=getchar(); fflush(stdin);
if(g.gender!='m' && g.gender!='M' && g.gender!='f' && g.gender!='f' )
{
printf("Invalid gender \n");
return;
}

e=fopen("temp.data","wb");
f=fopen("student.data","rb");

while(1)                        //copying data to temp.data
{
fread(&t,sizeof(struct1),1,f);
if(feof(f)) break;
if(rollNumber==t.rollNumber) 
{
fwrite(&g,sizeof(struct1),1,e);
}
else fwrite(&t,sizeof(struct1),1,e);
}
fclose(f);
fclose(e);

f=fopen("student.data","wb");
e=fopen("temp.data","rb");
while(1)                          //copying to student.data
{
fread(&g,sizeof(struct1),1,e);
if(feof(e)) break;
fwrite(&g,sizeof(struct1),1,f);
}
fclose(f);
fclose(e);

printf("Student edited...\n");
}

dash('_',60);
printf("\nPress enter key to continue....");
getchar(); fflush(stdin);

}

void searchStudent()
{

struct1 g;
FILE *f;

dash('_',60);
printf("\n%60s\n","Search Module");
dash('_',60);

int rollNumber,found=0;

f=fopen("student.data","rb");
if(f==NULL)
{
printf("\nno single student added in list...\n");
return;
}

printf("\nEnter roll number to search student : ");
scanf("%d",&rollNumber); fflush(stdin);

while(1)
{
fread(&g,sizeof(struct1),1,f);
if(feof(f)) break;
if(rollNumber==g.rollNumber)
{
found=1;
break;
}
}

fclose(f);
if(found)
{
printf("\n%-20s %-30s %-6s\n","Roll Number","Name","Gender");
printf("%-20d %-30s ",g.rollNumber,g.name);
if(g.gender=='m' || g.gender=='M') printf("%-6s\n\n","Male");
else printf("%-6s\n\n","Female");
}
else printf("Roll number %d is not in student list\n\n",rollNumber);

dash('_',60);
printf("\npress enter key continue....");
getchar(); fflush(stdin);

}
 

int main()
{
int ch;
while(1)
{

printf("\n1. Add student\n");
printf("2. View list of students\n");
printf("3. Remove student\n");
printf("4. Edit student\n");
printf("5. Search student\n");
printf("6. Exit\n");
printf("Enter your choice : ");
scanf("%d",&ch); fflush(stdin);
if(ch==1) addStudent();
else if(ch==2) viewDetails();
else if(ch==3) removeStudent();
else if(ch==4) editStudent();
else if(ch==5) searchStudent();
else if(ch==6) break;
else printf("Invalid Choice....\n");

}

return 0;
}