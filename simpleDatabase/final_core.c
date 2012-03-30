/* This is the final project */
/* It is made by Nan Ding, Lloyd Mckenzie, Baldwin Ryan Tyler,Corey Hines */
/* It is made in 11/19/2010. */
/* It is the program to proceed the music play list*/


//Note: Please use the listed variable names for the structure and pointers so everything is consistent
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20//used for arrays, easier to change alloted memory for arrays
typedef struct node_s {//the structure that is used to make all of our songs
char artist[MAX];
char songname[MAX];
char album[MAX];
char genre[MAX];
int duration;
int year;
int count;//used to keep track of all of our elements
struct node_s *listp;//standard pointer used in our normal list
struct node_s *playpt;//added for an easy way to make a second list
struct node_s *searchp;//added for a way to make a seperate search list
} data;//name of new datatype
//Nan's part
void  scan_fun(data *temp, FILE *inp, int *count)//this function takes in data from outside file
   { //scans file and stores input on a data structure
        int i=0;
        fgets(temp->artist, MAX, inp);//uses fgets to read file
        fgets(temp->songname, MAX, inp);
        fgets(temp->album, MAX, inp);
        fgets(temp->genre, MAX, inp);
        for(i=0; i<MAX; i++)
        {
            if(temp->artist[i]=='\n'||temp->artist[i]=='\r')//gets rid of any newline characters
                temp->artist[i]='\0';
            if(temp->songname[i]=='\n'||temp->songname[i]=='\r')
                temp->songname[i]='\0';
            if(temp->album[i]=='\n'||temp->album[i]=='\r')
                temp->album[i]='\0';
            if(temp->genre[i]=='\n'||temp->genre[i]=='\r')
                temp->genre[i]='\0';
        }
        fscanf(inp, "%d", &temp->duration);
        fscanf(inp, "%d", &temp->year);
        for(i=0; i<(*count); i++)//automatically moves count variable for easy organization
        {
            temp->count++;
        }
        (*count)++;
   }
////////////////////////////////////////////////lloyd's individual function
void read(data *temp, int *count)//used to take in new user songs
{
    int i;
    for(i=0;i<MAX;i++);
    {
        temp->artist[i]='\0';
        temp->songname[i]='\0';
        temp->album[i]='\0';
        temp->genre[i]='\0';
    }
    printf("\nPlease give the name of the artist:\n");
    fflush(stdin);
    fgets(temp->artist, MAX, stdin);
    printf("Please give the name of the song:\n");
    fflush(stdin);
    fgets(temp->songname, MAX, stdin);
    printf("Please give the name of the album:\n");
    fflush(stdin);
    fgets(temp->album, MAX, stdin);
    printf("Please give the genre of music this song is classified as:\n");
    fflush(stdin);
    fgets(temp->genre, MAX, stdin);
    fflush(stdin);

    i=strlen(temp->artist);//takes out new line characters
    if(temp->artist[i-1]!='\0')
    temp->artist[i-1]='\0';
    i=strlen(temp->songname);
    if(temp->songname[i-1]!='\0')
    temp->songname[i-1]='\0';
    i=strlen(temp->album);
    if(temp->album[i-1]!='\0')
    temp->album[i-1]='\0';
    i=strlen(temp->genre);
    if(temp->genre[i-1]!='\0')
    temp->genre[i-1]='\0';

    printf("Please give the total length of the song in seconds:\n");
    scanf("%d", &temp->duration);
    fflush(stdin);
    printf("Please give the year this song was released:\n");
    scanf("%d", &temp->year);

    temp->count=1;//gives a baseline for the count variable
}
//Lloyd's part
void add_member(data **head, data **current, int *count)//add funct called from main. organizes addition of song
{
    int i=0;
    data *temp;
    temp=(data *)malloc(sizeof(data));//making new space as needed
    read(temp, count);
    if(*head==NULL)//next few statements used to decide where exactly the element is being added
    {
        *head=temp;
        temp->listp=NULL;
    }
    else
    {
        temp->listp=(*current)->listp;
        (*current)->listp=temp;
        *current=temp;
    }
    for(i=1; i<*count; i++)//automatically gives it a unique identification number
        {
            temp->count++;
        }
        (*count)++;
}

data *find_element(data *temp, int ans, int flag)//used to search through list and find certain element
{
    if(flag==2)//flag variable is used throughout program to inform functions which list it should follow as there can be up to three originating from a single head pointer
    {
        if(temp==NULL)//recursively checks to see if element exists
        return(NULL);
        else if(temp->count==ans)
        return(temp);
        else
        return(find_element(temp->searchp, ans, flag));
    }
    else
    {
        if(temp==NULL)
        return(NULL);
        else if(temp->count==ans)
        {return(temp);}
        else
        {return(find_element(temp->listp, ans, 0));}
    }
}

void print_members(data *head, int flag)//function used to print lists onto the screen. Again flags are used to seperate lists
{
    int min, sec;
    while(1)
    {
        min=(head->duration)/60;
        sec=(head->duration)%60;
        printf("\n%d.\nSong:%s\nArtist:%s\nAlbum:%s\nGenre:%s\nDuration:%d:%d\nRelease:%d\n\n", head->count, head->songname, head->artist, head->album, head->genre, min, sec, head->year);
       if(flag==0)
       {
           head=head->listp;//goes through list
           if(head==NULL)
           break;
       }
       if(flag==1)
       {
           head=head->playpt;
           if(head==NULL)
           break;
       }
       if(flag==2)
       {
           head=head->searchp;
           if(head==NULL)
           break;
       }
    }
}
//Corey's part
data *search_for( data *head, char *category, char *target, int numtar)//function similar to find function that goes through list, but this is looking for a specific target such as a keyword
{
if(head==NULL)
return(NULL);

if ( strcmp( category, "artist" ) == 0 )//all initial if statement strcmp's used to identify which category of data prog should look in. Second strcmp actually looks for specified target
{
    if(strcmp(head->artist, target)==0)
    return(head);
}
if ( strcmp( category, "song" ) == 0 )
{
  if( strcmp( head->songname, target ) == 0 )
   return head;
}
if ( strcmp( category, "genre" ) == 0 )
{
    if( strcmp( head->genre, target ) == 0 )
    return head;
}
if ( strcmp( category, "album" ) == 0 )
{
    if( strcmp(head->album, target ) == 0 )
    return head;
}
if ( strcmp( category, "duration" ) == 0 )
{
    if( head->duration ==numtar)
    return head;
}
if ( strcmp( category, "year" ) == 0 )
{
    if( head->year ==numtar)
    return head;
}
if ( strcmp( category, "count" ) == 0 )
{
    if( head->count ==numtar)
    return head;
}
else
return(search_for(head->listp, category, target, numtar));//recursive implementation of function
}
//Lloyd's part
void delete_member(data **head, data **current, int flag)//function that, based on flag, will delete single element from normal list, group of element, or element from search function
{
    int ans, sel, test, fake=0, i, tip=0;
    data *target, *blank;
    data **temp=head, *newhead=*head;
    char category[MAX], train[MAX];
    if(flag==2)//checking for flag. this part of function deals with deleting elements found in search function
    {
        printf("Choose the entry numbers of the songs to be deleted from the playlist\n");
        printf("When you are done deleting and want to see the new database, enter '0'\n");
        printf("Please be careful as to what numbers are entered as erroneous entries could make unwanted deletions\n");
        print_members((*head)->searchp, flag);//printing members in search list
        while (1)
        {
            scanf("%d", &sel);
            if(sel==0)
            break;
            target=find_element(*head, sel, 0);
            if (target==NULL)
            printf("Song does not exist please make another choice:");//error message
            else
            {
                if(target==*head)
                *head=target->listp;
                else
                {
                    while((*temp)->listp!=target)
                {
                    temp=&((*temp)->listp);
                }
                }
                if(target==*current)
                {   *current=*temp;
                (*current)->listp=NULL;
                }
                else if((*temp)->listp==target)
                {
                    (*temp)->listp=(target->listp);
                }
                free(target);
                printf("\nSong successfully deleted\n");
            }
        }
    }
    else//now moves onto normal list deletions
    {
        print_members(*head, flag);
        printf("If you would like to delete songs one by one, enter '0'. \nIf you would like to delete a group of songs by their categories, enter '1'\n");//checks for single deletion or group deletion
        fflush(stdin);
        scanf("%d", &test);
        if(test==1)//this if statement leads to group deletion
        {
            while(1)
            {
                printf("Please type the word 'artist', 'song', 'album', or 'genre', to delete by that category.\n");//implents search function to find desired elements
                fflush(stdin);
                fgets(category, MAX, stdin);
                for(i=0; i<MAX; i++)
                {
                    if(category[i]=='\n'||category[i]=='\r')
                    category[i]='\0';
                }
                if(strcmp(category, "artist")!=0 && strcmp(category, "song")!=0 && strcmp(category, "album")!=0 && strcmp(category, "genre"))
                printf("Error: Not a defined category\n");
                else
                break;
            }
            printf("Ok, please enter the target keyword(s) for the songs you would like to delete.\n");
            fflush(stdin);
            fgets(train, MAX, stdin);
            for(i=0; i<MAX; i++)
            {
                if(train[i]=='\n'||train[i]=='\r')
                train[i]='\0';
            }
            while(1)//then proceeds to delete them
            {
                blank=search_for(newhead, category, train, fake);
                if(blank==NULL)
                {
                    if(tip==0)//if no deletion occured, you'll get this error message
                    {
                        printf("Sorry, no song(s) was found that matched your search\n");
                        return;
                    }
                    printf("Song(s) successfully deleted\n");
                    break;
                }
                tip=1;
                if(blank==*head)
                *head=blank->listp;
                else
                {
                    while((*temp)->listp!=blank)
                    {
                        temp=&((*temp)->listp);
                    }
                }
                if(blank==*current)
                {
                    *current=*temp;
                    if(*current!=NULL)
                    (*current)->listp=NULL;
                }
                else if((*temp)->listp==blank)
                {
                    (*temp)->listp=(blank->listp);
                }
                newhead=blank->listp;
                free(blank);
            }
        }
        else{//area for single deletions. largely the same implementations as the above 2
        printf("\nPlease give the entry number of the song you wish to delete\n");
        fflush(stdin);
        scanf("%d", &ans);
        target=find_element(*head, ans, flag);
        if(target==NULL)
        printf("\nI'm sorry, but this song does not exist in this database\n");
        else
        {
            if(target==*head)
            *head=target->listp;
            else
            {
            while((*temp)->listp!=target)
                {
                temp=&((*temp)->listp);
                }
            }
            if(target==*current)
            {   *current=*temp;
                (*current)->listp=NULL;
            }
            else if((*temp)->listp==target)
            {
                (*temp)->listp=(target->listp);
            }
            free(target);
            printf("\nSong successfully deleted\n");
        }
    }
    }
}
//Ryan's part
void export_fun(data *pt, FILE *outp, int flag)//function to print out playlist to file
{
	int min, sec;
	while (1)
	{
	    min=(pt->duration)/60;
	    sec=(pt->duration)%60;
	    fprintf(outp,"%d.\n", pt->count);
        fprintf(outp,"%s\n", pt->artist);
        fprintf(outp,"%s\n", pt->songname);
        fprintf(outp,"%s\n", pt->album);
        fprintf(outp,"%s\n", pt->genre);
        fprintf(outp,"%d:%d\n", min, sec);
        fprintf(outp,"%d\n", pt->year);
        if(flag==0)//depending on flag, will either print out database or playlist
        {
            pt=pt->listp;
            if(pt==NULL)
            break;
        }
        if(flag==1)
        {
            pt=pt->playpt;
            if(pt==NULL)
            break;
        }
	}
}

void playlist_a(data **h, data **headp, FILE *outp)//function that handles creation of new playlist
{
	int sel;
	char ans;

	data *temp, *current=NULL;
	temp=(data *)malloc(sizeof (data));//necessary to make an extra data space so as not to have an infinite loop with the head pointer
	temp->playpt=NULL;
	printf("Choose the song numbers to be exported to the playlist\n");
	printf("Enter '0' to export after all songs are selected\n");
	print_members(*h, 0);//shows all elements

	while (1)
	{
		scanf("%d", &sel);//finds all elements user specifies and puts them into a list
		if(sel==0)
		break;
		temp=find_element(*h, sel, 0);
		if (temp==NULL)
			printf("Song does not exist please make another choice:");
		else
		{
			if(*headp==NULL)
            {
                *headp=temp;
                temp->playpt=NULL;
            }
            else
            {
                temp->playpt=current->playpt;
                current->playpt=temp;
            }
            current=temp;
		}
		fflush(stdin);
	}
	printf("Would you like to export songs to file? (Y/N):");//gives option to export
	fflush(stdin);
	scanf("%c", &ans);
    if (ans=='Y'||ans=='y')
		{
		    outp=fopen("playlist.dat", "w");
			export_fun(*headp, outp, 1);
            printf("The new playlist is located in file 'playlist.dat'\n");
            fclose(outp);
		}
}
//Corey's part
void swap( data *x, data *y )//function used to swap the data in two elements. similar to previous swap functins we've used
{
data t;
strcpy(t.artist, x->artist );
strcpy(t.songname, x->songname );
strcpy(t.album, x->album );
strcpy(t.genre, x->genre );
t.duration=x->duration;
t.year=x->year;
t.count = x->count;
strcpy( x->artist, y->artist );
strcpy( x->songname, y->songname );
strcpy( x->album, y->album );
strcpy( x->genre, y->genre );
x->duration = y->duration;
x->year = y->year;
x->count = y->count;
strcpy( y->artist, t.artist );
strcpy( y->songname, t.songname );
strcpy( y->album, t.album );
strcpy( y->genre, t.genre );
y->duration = t.duration;
y->year = t.year;
y->count = t.count;
}

void sort_by(data *head, char *target)//function to sort and print the list however the user wants
{
int flag=1;
int i;
data *p=head;

if(strcmp(target, "artist")==0)
{
while(flag==1)
{
flag=0;
 while(p->listp!=NULL)
 {
   if(strcmp(p->artist,p->listp->artist)>0)
   {
   swap(p, p->listp);
   flag=1;
   }
   p=p->listp;
 }
 p=head;
}}

else if(strcmp(target, "songname")==0)
{
while(flag==1)
{
flag=0;
 while(p->listp!=NULL)
 {
   if(strcmp(p->songname, p->listp->songname)>0)
   {
   swap(p, p->listp);
   flag=1;
   }
   p=p->listp;
 }
 p=head;
}}
else if(strcmp(target, "album")==0)
{
while(flag==1)
{
flag=0;
 while(p->listp!=NULL)
 {
   if(strcmp(p->album, p->listp->album)>0)
   {
   swap(p, p->listp);
   flag=1;
   }
   p=p->listp;
 }
 p=head;
}}

else if(strcmp(target, "genre")==0)
{
while(flag==1)
{
flag=0;
while(p->listp!=NULL)
{
   if(strcmp(p->genre, p->listp->genre)>0)
   {
   swap(p, p->listp);
   flag=1;
   }
   p=p->listp;
 }
 p=head;
}}

else if(strcmp(target, "duration")==0)
{
while(flag==1)
{
flag=0;
while(p->listp!=NULL)
{
   if(p->duration>p->listp->duration)
   {
   swap(p, p->listp);
   flag=1;
   }
   p=p->listp;
 }
 p=head;
}}

else if(strcmp(target, "year" ) == 0 )
{
while( flag == 1 )
{
flag = 0;
 while( p->listp != NULL )
 {
   if( p->year > p->listp->year )
   {
   swap( p, p->listp );
   flag = 1;
   }
   p = p->listp;
 }
 p = head;
}}

else
{
while( flag == 1 )
{
flag = 0;
 while( p->listp != NULL )
 {
   if( p->count > p->listp->count )
   {
   swap( p, p->listp );
   flag = 1;
   }
   p = p->listp;
 }
 p = head;
}}}

void copy(data *x, data *y)//function to copy the data from one element to another
{
    strcpy( x->artist, y->artist );
    strcpy( x->songname, y->songname );
    strcpy( x->album, y->album );
    strcpy( x->genre, y->genre );
    x->duration = y->duration;
    x->year = y->year;
    x->count = y->count;
    x->listp=y->listp;
    x->playpt=y->playpt;
    x->searchp=y->searchp;
}

void master_search(int flag, char *category, int numtar, data **head, data *newtemp, data *search, char *target, data **current)
{//function that handles searching by asking user for inputs and then fetching results. just an easy way to clean up the main function
    int i;
    char answer='y';
    data *hold, *curr_search;
    while(1){
    printf("Please type the word 'artist', 'song', 'album', or 'genre' to search by those parameters.\nType 'duration' to search by song length, 'year' if you want to search by the song's release year, \nor 'count' if you want to search by a song's entry into the database.\n");
    fflush(stdin);
    fgets(category, MAX, stdin);
    for(i=0; i<MAX; i++)
    {
        if(category[i]=='\n'||category[i]=='\r')
        category[i]='\0';
    }
    if(strcmp(category, "artist")!=0&&strcmp(category, "song")!=0&&strcmp(category, "album")!=0&&strcmp(category, "genre")!=0&&strcmp(category, "duration")!=0&&strcmp(category, "year")!=0&&strcmp(category, "count")!=0)
    printf("Error: Not a defined category\n");
    else
    break;
    }
    printf("Ok, please enter the target word you would like to search for.(ex:lazos)\nIf you are hoping to search by song duration, enter '1'. \nIf you wanted to search by release year, enter '2'. \nIf you wantd to search by the entry position of the song, enter '3'\n" );
    fflush(stdin);
    fgets(target, MAX, stdin);
    for(i=0; i<MAX; i++)
    {
        if(target[i]=='\n'||target[i]=='\r')
        target[i]='\0';
    }
    if(target[0]=='1')
    {
        printf("Please enter the requested length of the song in seconds(ex: 360)\n");
        fflush(stdin);
        scanf("%d", &numtar);
    }
    if(target[0]=='2')
    {
        printf("Please enter the year(ex: 2010).\n");
        fflush(stdin);
        scanf("%d", &numtar);
    }
    if(target[0]=='3')
    {
        printf("Please enter the entry number of the song you wish to find(ex: 1, 2, 3)\n");
        fflush(stdin);
        scanf("%d", &numtar);
    }
    while(1)
    {
        newtemp=search_for(search, category, target, numtar);//takes user inputs and finds desired elements. then proceeds to put them in a new list
        if(newtemp==NULL)
        {
            if((*head)->searchp==NULL)
            {
                printf("Sorry, no song was found that matched your search\n");
                return;
            }
            break;
        }
        if(*head==newtemp)
        {
            hold=(data *)malloc(sizeof(data));
            copy(hold, newtemp);
            newtemp=hold;
            (*head)->searchp=newtemp;
            newtemp->searchp=NULL;
        }
        else if((*head)->searchp==NULL)
        {
            (*head)->searchp=newtemp;
            newtemp->searchp=NULL;
        }
        else
        {
            curr_search->searchp=newtemp;
            newtemp->searchp=NULL;
        }
        curr_search=newtemp;
        search=newtemp->listp;
    }
    print_members((*head)->searchp, 2);
    answer='y';
    while(answer!='n'&&answer!='N')
    {
        printf("Would you like to delete any elements? <y/n>:");//then gives option to delete any of the elements found
        fflush(stdin);
        scanf("%c", &answer);
        if(answer=='y'||answer=='Y')
        {
            delete_member(head, current, flag);
            print_members(*head, 0);
            answer='n';
        }
    }
}
//Nan's part
int main(void)//actual main function
{
	int  count=1, ans, numtar, i=0, flag;////aa is user's command.//added in count var
	char category[MAX], target[MAX];
	int aa;
	data *head=NULL, *temp, *current=NULL, *playh=NULL, *search=NULL, *newtemp;//
	FILE *inp, *outp;
	inp=fopen("songs.dat", "r");
	int err=0;//to detect if the user input is illegal
	while(!feof(inp))//loop that calls scan function and takes in data from file
	{
		temp=(data *)malloc(sizeof (data));
		scan_fun(temp, inp, &count);
		if (current==NULL)
		{
		    head=temp;//pointing header to temp
            temp->listp=NULL;//temp left pointer also pointing to null
		}
		else
		{
		    current->listp=temp;//pointing current to temp
		}
		current=temp;//make new current
	}
	fclose(inp);

	printf("Welcome to PEAR company's super awesome media database.\n");

	while(aa!=8)//gets action user wants to do. then goes through switch functio to fulfill
	{
	printf("Please push from 1-7 to start the following action:\n");
	printf("1.insert a new element into the database.\n");
	printf("2.delete one/multiple songs from the database.\n");
	printf("3.sort the song list according to your will.\n");
	printf("4.search the database based on different attributes.\n");
	printf("5.create your own playlist.\n");
	printf("6.print the database, or the playlist to the screen.\n");
	printf("7.export the data base as a new file.\n");
	printf("8.exit.\n");

	while (1)
	{
	    fflush(stdin);
		scanf("%d", &aa); ///read user's command.
		if ((aa!=1)&&(aa!=2)&&(aa!=3)&&(aa!=4)&&(aa!=5)&&(aa!=6)&&(aa!=7)&&(aa!=8))
		{
			printf("Please input a number from 1 to 8!");
		}
		break;
	}

		switch(aa)
		{
			case 1:
			////insert
			while(1)
			{
                add_member(&head, &current, &count);
                fflush(stdin);
                printf("\nWould you like to add another song?\n1. yes 2. no\n");
                scanf("%d", &ans);
                if(ans==2)
                break;
			}

				break;

			case 2:
			/////delete
			flag=0;
			while(1)
			{
			    delete_member(&head, &current, flag);
                fflush(stdin);
                printf("\nWould you like to delete another song?\n1. yes 2. no\n");
                scanf("%d", &ans);
                if(ans==2)
                break;
			}
				break;

            case 3://////sort and print
            printf("What category would you like to sort by?\n");
            printf("Please type the word 'artist', 'song', 'album', or 'genre' to sort by those\nparameters.\nType 'duration' to sort by song length, or 'year' if you want to sort by the \nsong's release year.\n");
            printf("If you want to sort by the order the songs were entered into the database, type 'count'\n");
            fflush(stdin);
            scanf("%s", category);
            sort_by(head, category);
            printf("The database is now sorted by '%s'\n", category);
            print_members(head, 0);
            break;

            case 4:////search and print and delete
            flag=2;
            category[0]='\0';
            numtar=0;
            head->searchp=NULL;
            newtemp=head;
            search=head;
            master_search(flag, category, numtar, &head, newtemp, search, target, &current);
            break;

			case 5://////create a new playlist aside from the original playlist.
                playh=NULL;
                playlist_a(&head, &playh, outp);
            break;

			case 6://////print
                printf("Would you like to see the complete database, or your playlist?\n1. Database\n2. Playlist\n");
				fflush(stdin);
				scanf("%d", &ans);
				if(ans==1)
				print_members(head, 0);
				if(ans==2)
				{
				    if(playh==NULL)
				    printf("No Playlist found\n");
				    else
				    print_members(playh, 1);
                    fflush(stdin);
				}
				break;

			case 7:
				//////export the current playlist (not the new playlist) as a file "database.dat"
                // the current playlist should be different after sorting/adding/deleting. so database.dat is different from song2.dat
                outp=fopen("database.dat", "w");
                export_fun(head, outp, 0);
                printf("\nThe database is located in file 'database.dat'\n\n");
                fclose(outp);
				break;
		}
	}
	printf("Thank you for using PEAR's super awesome media database.\n");

	return (0);
}
//end of program
