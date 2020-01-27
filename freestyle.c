#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct {
	char *NAME;
	char *FN;
	char *LN;
	char *MSSV;
	int date;
	int month;
	int year;
	char *Town;
	float point;
	float pp;
}Data;
void CEW (char *A){
	int i;
	*A=toupper (*A);
	for (i=0;i<strlen(A);i++){
		if (*(A+i)==' ' && *(A+i+1)!=' '){
			*(A+i+1)=toupper (*(A+i+1));
		}
	}
}
void Space (char *A){
	int i,j,k=strlen(A);
	for (i=0;i<k;i++){
		if (*(A+i)==' ' && (i==0 || *(A+i+1)==' ' || i==k-1)){
			for (j=i;j<	k;j++){
				*(A+j)=*(A+j+1);
			}
			k--;
			i--;
		}
	}
	*(A+k)='\0';
}
Data* Crt (int n){
	Data *info=(Data*)malloc(sizeof(Data));
	char *tmp=(char*)malloc(sizeof(char)*100);
	int i;
	for (i=0;i<n;i++){
		printf ("Infomation of member number %d: \n",i+1);
		printf ("\tFull Name: ");	gets (tmp);	CEW(tmp);	Space(tmp); 	(info+i)->NAME=strdup(tmp);
		printf ("\tMSSV: ");	gets (tmp);	CEW(tmp);	Space(tmp);	(info+i)->MSSV=strdup(tmp);
		printf ("\tBorn (dd mm yyyy): "); scanf ("%d %d %d",&(info+i)->date,&(info+i)->month,&(info+i)->year); fflush (stdin);
		printf ("\tHome town: ");	gets (tmp);	CEW(tmp);	Space(tmp);	(info+i)->Town=strdup(tmp);
		printf ("\tPoint (point pluspoint): "); scanf ("%f %f",&(info+i)->point,&(info+i)->pp); fflush (stdin);
		info=realloc (info,sizeof(Data)*(i+1));
	}
	free (tmp);
	return info;
}
Data* Read (int *n){
	FILE *f;
	Data *info=(Data*)malloc(sizeof(Data));
	char *tmp=(char*)malloc(100);
	int i=0;
	f=fopen ("Data.out","r");
	if (f!=NULL){
		while (!feof (f)){
			fgets (tmp,5,f);
			fgets (tmp,31,f);	Space (tmp);	strlwr(tmp);	CEW(tmp);	(info+i)->NAME=strdup(tmp);
			fgets (tmp,11,f);	Space (tmp);	strlwr(tmp);	CEW(tmp); (info+i)->MSSV=strdup(tmp);
			fscanf (f,"%d",&(info+i)->date);fgets (tmp,2,f);fscanf (f,"%d",&(info+i)->month);fgets (tmp,2,f);fscanf (f,"%d",&(info+i)->year);
			fgets (tmp,20,f);	CEW(tmp);	Space(tmp); 	(info+i)->Town=strdup(tmp);
			fscanf (f,"%f %f",&(info+i)->point,&(info+i)->pp); fgets(tmp,50,f);
			i++;
			info=realloc (info,sizeof(Data)*(i+1));
		}
		fclose (f);
		*n=i-1;
	}
	else printf ("!!! Error to read file.\n");
	free (tmp);
	return info;
}
void Wrt (Data *info,int n){
	FILE *f=fopen ("Data.out","w");
	int i;
	if (f!=NULL){
		for (i=0;i<n;i++){
			fprintf (f,"%3d %-30s%-10s%02d%s%02d%s%04d%-17s%6.1f%10.1f\n",i+1,(info+i)->NAME,(info+i)->MSSV,(info+i)->date,"/",(info+i)->month,"/",(info+i)->year,(info+i)->Town,(info+i)->point,(info+i)->pp);
		}
		fclose (f);
	}
	else printf ("!!! Error to write file.\n");
	printf ("Done.\n");
}
void Prt (Data *info,int n){
	int i;
	printf ("%3s||%-30s%-10s%-12s%-10s||%7s%12s\n","STT","Name","MSSV","Born","Hometown","Point","PointPlus");
	for (i=0;i<n;i++){
		printf ("%3d||%-30s%-10s%02d%s%02d%s%04d  %-10s||%6.1f%10.1f\n",i+1,(info+i)->NAME,(info+i)->MSSV,(info+i)->date,"/",(info+i)->month,"/",(info+i)->year,(info+i)->Town,(info+i)->point,(info+i)->pp);
	}
}
void Prt1 (Data *info,int n){
	int i;
	char *tmp=(char*)malloc(100);
	printf ("Type member's MSSV you want to see: ");	gets (tmp); Space (tmp);	strlwr(tmp);
	printf ("%3s||%-30s%-10s%-12s%-10s||%7s%12s\n","STT","Name","MSSV","Born","Hometown","Point","PointPlus");
	for (i=0;i<n;i++){
		if (stricmp(tmp,(info+i)->MSSV)==0)	printf ("%3d||%-30s%-10s%02d%s%02d%s%04d  %-10s||%6.1f%10.1f\n",i+1,(info+i)->NAME,(info+i)->MSSV,(info+i)->date,"/",(info+i)->month,"/",(info+i)->year,(info+i)->Town,(info+i)->point,(info+i)->pp);
	}
}
void Swap (Data *A,Data *B){
	Data tmp;
	tmp=*A;
	*A=*B;
	*B=tmp;
}
void ArP (Data *info,int n){
	int i,j;
	for (i=0;i<n-1;i++){
		for (j=n-1;j>i;j--){
			if (((info+j)->point)>((info+j-1)->point)) Swap ((info+j),(info+j-1));
		}
	}
	printf ("Done.\n");
}
void takeFirst (Data *info){
	int i;
	char *tmp=strrchr (info->NAME,' ')+1;
	for (i=strlen(info->NAME)-1;i>=0 && *(info->NAME+i)!=' ';i--);
	if (i>0){
		info->FN=strdup(tmp);
		tmp=(char*)malloc(50);
		strncpy(tmp,info->NAME,i);
		info->LN=strdup(tmp);
	}
	else {
		info->FN=strdup(info->NAME);
		info->LN=(char*)malloc(1);
		*(info->LN)='\0';
	}
	free (tmp);
}
void ArN (Data *info,int n){
	int i,j;
	char *fakeF1,*fakeL1,*fakeF2,*fakeL2;
	for (i=0;i<n;i++){
		takeFirst (info+i);
	}
	for (i=0;i<n-1;i++){
		for (j=n-1;j>i;j--){
			int k=10;
			fakeF1=strdup((info+j)->FN);
			fakeF2=strdup((info+j-1)->FN);
			fakeL1=strdup((info+j)->LN);
			fakeL2=strdup((info+j-1)->LN);
			while (k!=0){
				if (stricmp(fakeF1,fakeF2)>0) k=0;
				else if (stricmp(fakeF1,fakeF2)<0) {
					Swap (info+j,info+j-1);
					k=0;
				}
				else if (stricmp(fakeF1,fakeF2)==0) {
					int z1,z2;
					for (z1=strlen(fakeL1)-1;(*(fakeL1+z1)!=' ' && z1!=0);z1--);
					for (z2=strlen(fakeL2)-1;(*(fakeL2+z2)!=' ' && z2!=0);z2--);
					if (z1>0 && z2>0){
						fakeF1=strrchr (fakeL1,' ')+1;
						*(fakeL1+z1)='\0';
						fakeF2=strrchr (fakeL2,' ')+1;
						*(fakeL2+z2)='\0';
					}
					else if (z1==0 && z2>0) {
						fakeF1=strdup(fakeL1);
						fakeF2=strrchr (fakeL2,' ')+1;
						*(fakeL2+z2)='\0';
					}
					else if (z1>0 && z2==0) {
						fakeF1=strrchr (fakeL1,' ')+1;
						*(fakeL1+z1)='\0';
						fakeF2=strdup(fakeL2);
					}
					else {
						fakeF1=strdup(fakeL1);
						fakeF2=strdup(fakeL2);
					}
				}
			}
		}
	}
	free(fakeF1);	free(fakeF2);	free(fakeL1);	free(fakeL2);
	printf ("Done.\n");
}
void Add (Data *info,int *n){
	char *tmp=(char*)malloc(sizeof(char)*100);
	int i=*n;
	info=realloc (info,sizeof(Data)*(i+1));
	printf ("Infomation of member number %d: \n",i+1);
	printf ("\tFull Name: ");	gets (tmp);	CEW(tmp);	Space(tmp); 	(info+i)->NAME=strdup(tmp);	tmp=(char*)malloc(sizeof(char)*100);
	printf ("\tMSSV: ");	gets (tmp);	CEW(tmp);	Space(tmp);	(info+i)->MSSV=strdup(tmp); tmp=(char*)malloc(sizeof(char)*100);
	printf ("\tBorn (dd mm yyyy): "); scanf ("%d %d %d",&(info+i)->date,&(info+i)->month,&(info+i)->year);	fflush (stdin);
	printf ("\tHome town: ");	gets (tmp);	CEW(tmp);	Space(tmp);	(info+i)->Town=strdup(tmp); tmp=(char*)malloc(sizeof(char)*100);
	printf ("\tPoints (point pluspoint): "); scanf ("%f %f",&(info+i)->point,&(info+i)->pp);
	*n=*n+1;
	free (tmp);
	printf ("Done.\n");
}
void Dlt (Data *info,int *n){
	int i,j;
	char *tmp=(char*)malloc(100);
	printf ("Type member's MSSV you want to delete: ");	gets (tmp); Space (tmp);	strlwr(tmp);
	for (i=0;i<*n;i++){
		if (stricmp(tmp,(info+i)->MSSV)==0)	{
			for (j=i;j<*n;j++){
				*(info+j)=*(info+j+1);
			}
			*n=*n-1;
		}
	}
	free (tmp);
	printf ("Done.\n");
}
void Fix (Data *info,int n){
	int i,select=0;
	char *tmp=(char*)malloc(100);
	printf ("Nhap MSSV muon sua: "); gets (tmp);	strlwr(tmp);	Space (tmp);
	for (i=0;i<n;i++){
		if (stricmp(tmp,(info+i)->MSSV)==0){
			printf ("%3d||%-30s%-10s%02d%s%02d%s%04d  %-10s||%6.1f%10.1f\n",i+1,(info+i)->NAME,(info+i)->MSSV,(info+i)->date,"/",(info+i)->month,"/",(info+i)->year,(info+i)->Town,(info+i)->point,(info+i)->pp);
			while (select==0){
				printf ("Which one would you like to change: ");
				gets (tmp);
				if (strcmp("-h",tmp)==0) printf ("-FIX's HELP menu:\n\t-n\t: to fix name.\n\t-ms\t: to MSSV.\n\t-d\t: to fix day born.\n\t-m\t: to fix month born\n\t-y\t: to fix year born\n\t-ht\t: to fix hometown\n\t-p\t: to fix point\n\t-pp\t: to fix pointplus\n");
				else if (strcmp (tmp,"-n")==0) {
					printf ("The old one: %-30s\n",(info+i)->NAME);	printf ("Type the new one: ");	gets ((info+i)->NAME);
				}
				else if (strcmp (tmp,"-ms")==0) {
					printf ("The old one: %-10s\n",(info+i)->MSSV);	printf ("Type the new one: ");	gets ((info+i)->MSSV);
				}
				else if (strcmp (tmp,"-d")==0) {
					printf ("The old one: %-02d\n",(info+i)->date);	printf ("Type the new one: ");	scanf ("%d",&(info+i)->date);
				}
				else if (strcmp (tmp,"-m")==0) {
					printf ("The old one: %-02d\n",(info+i)->month); printf ("Type the new one: ");	scanf ("%d",&(info+i)->month);
				}
				else if (strcmp (tmp,"-y")==0) {
					printf ("The old one: %-04d\n",(info+i)->year);	printf ("Type the new one: ");	scanf ("%d",&(info+i)->year);
				}
				else if (strcmp (tmp,"-ht")==0) {
					printf ("The old one: %-10s\n",(info+i)->Town);	printf ("Type the new one: ");	gets ((info+i)->Town);
				}
				else if (strcmp (tmp,"-p")==0) {
					printf ("The old one: %6.1f\n",(info+i)->year);	printf ("Type the new one: ");	scanf ("%f",&(info+i)->point);
				}
				else if (strcmp (tmp,"-pp")==0) {
					printf ("The old one: %10.1f\n",(info+i)->year); printf ("Type the new one: ");	scanf ("%f",&(info+i)->pp);
				}
		
				else if (stricmp(tmp,"0")==0) select++;
				else printf ("Please type -h to show -FIX's HELP menu or type 0 to quit the fix stuffs\n");
			}
		}
	}
	free (tmp);
}
int main(){
	Data *info=(Data*)malloc(sizeof(Data));
	int n,select=0;
	char *cmp=(char*)malloc(sizeof(char)*100);
	//printf ("Nhap n: ");	scanf ("%d",&n);
	//info=Crt (n);
	info=Read (&n);
	printf ("Danh sach gom %d phan tu.\n",n);
	while (select==0){
		gets (cmp);
		if (strcmp("/help",cmp)==0) printf ("/HELP menu:\n
							\t/Prt	\t: to print all data.\n
							\t/Prt1\t: to print one by MSSV.\n
							\t/Add\t: to add member.\n
							\t/Dlt\t: to delete member by MSSV\n
							\t/Fix\t: to fix member\n
							\t/Arr\t: to arrange\n");
		else if (strcmp (cmp,"/Arr")==0) printf ("/Arrange menu:\n\t/Arr -n :to arrange by name\n\t/Arr -p :to arrange by point\n");
		else if (strcmp (cmp,"/Arr -n")==0) ArN (info,n);
		else if (strcmp (cmp,"/Arr -p")==0) ArP (info,n);
		else if (strcmp (cmp,"/Prt1")==0) Prt1 (info,n);
		else if (strcmp("/Prt",cmp)==0) Prt (info,n);
		else if (strcmp (cmp,"/Add")==0) Add (info,&n);
		else if (strcmp (cmp,"/Dlt")==0) Dlt (info,&n);
		else if (strcmp (cmp,"/Wrt")==0) Wrt (info,n);
		else if (strcmp (cmp,"/Fix")==0) Fix (info,n);
		
		else if (stricmp(cmp,"0")==0) select++;
		else printf ("Please type /help to show /HELP menu or type 0 to quit\n");
	}
}
