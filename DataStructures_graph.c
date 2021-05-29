// matris.txt ile projenin .c dosyasýnýn ayný konumda olduðuna dikkat edin.
// matris.txt proje dökümanýnda verilen graflara göre oluþuturulmuþtur.

#include <stdio.h> // standart kütüphanemiz
#include <stdbool.h> // bool için
#include <stdlib.h> // malloc için

int graph[6][6];
bool visited[5];

struct node{ // struct yapýmýz 1 tane veri ve next pointerimizden oluþuyor.
    int data;
    struct node *next;
};
// düðümde ileri geri yapmamýzý saðlayan pointerlar
struct node* first = NULL;
struct node* last = NULL;

struct node* createNode(int x) // dugum olusturma
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

void enQueue(int x) // kuyruk ekle
{
    struct node* newyNode = createNode(x);
    if(first == NULL)
    {
        first = newyNode;
        last = newyNode;
    }
    else
    {
        last->next = newyNode;
        last = newyNode;
    }
}

void deQueue() // kuyruk cikar
{
    if(first == NULL) // kuyruk cikinca eleman kalmiyorsa
    {
        printf("\n Dugumunuz bos.");
        return;
    }

    if(first->next == NULL) // kuyrukta 1 tane eleman kalýyorsa
    {
        first = NULL;
        last = NULL;
    }
    else
    {
        struct node* secondNode = first->next;
        free(first);
        first = secondNode;
    }

}

bool isEmpty() // boþ olup olmadýðýný kontrol eden bool fonksiyon
{
    if(first == NULL)
        return true;
    else
        return false;
}

int next()
{
    return first->data;
}

void printNeighbor(int dugum) // komþu olup olmadýðýný yazdýrýr.
{
	int i;
	
	printf("%d Dugumune Komsu dugumler: ",dugum+1);
	
	for(i=0; i<=6; i++)
	{
		if(graph[dugum][i] == 1)
		{
			printf("%d ",i+1);	
		}
	}
}

distanceCounter = 1;
void nodeDistance (int start, int finish) // dugum uzaklýðýný bulan fonksiyon
{
	int i;
	
	if(graph[start][finish]==1)
	{
		printf("Dugumler arasi mesafenin derecesi %d 'dir.", distanceCounter);
	}
	
	else
	{
		for (i=0; i<=5; i++)
		{
			if(graph[start][i]==1)
			{
				start = i;
				distanceCounter++;
				nodeDistance(start, finish);
			}	
		}
		
	}
	
	

}

void BFS(int root) // Breadth First Search algoritmasý
{
    int i;
    for(i = 0; i < 6; i++)
    {
        visited[i] = false;
    }

    visited[root]  = true;
    enQueue(root);

    while(isEmpty() == false)
    {
        root = next();
        printf("%d ", root);
        deQueue();

        for( i = 0; i < 6; i++)
        {
            if(visited[i] == false && graph[root][i] == 1)
            {
                visited[i] = true;
                enQueue(i);
            }
        }
    }
}

void readGraph() // matris.txt mizdeki matrisi okuyor.
{
    int i = 0;
    FILE *fp = fopen("matris.txt", "r"); // dosya okuma fonksiyonu --> r özelliði read yani okuma özelliði
    while(fscanf(fp, "%d %d %d %d %d %d",
                 &graph[i][0],
                 &graph[i][1],
                 &graph[i][2],
                 &graph[i][3],
                 &graph[i][4],
                 &graph[i][5]) !=EOF){
        i = i + 1;
    }

}

// main fonksiyonumuz
int main()
{
	int dugum, dugumtut, dugumson, islem, i, j;
    readGraph(); // Not defterinden graph ý okutuyoruz.
    
    printf ("Dugumlerin matris bicimi (1--> Komsu, 0--> Komsu degil): \n");
    
    for (i=0; i<6; i++)
    {
    	printf("\n");
    	for (j=0; j<6; j++)
    	{
    		printf ("%d ", graph[i][j]);
		}
	}
	printf("\n");
    
    
    while(1)
    {
    	printf("\n\n\n");
    printf("\nHangi Dugumle islem yapmak istediginizi seciniz (Dugumler 1-6 araligindadir) : ");
    scanf("%d",&dugumtut);
    
    dugum = dugumtut-1;
    
    printf("\n%d Dugumu ile yapmak istediginiz islemi seciniz: ",dugumtut);
    printf("\n Komsu Bul(1), Dugumler arasi uzakligi bul(2), BFS bul(3)\n");
    scanf("%d",&islem);
    
    switch(islem)
    {
    	case 1:
    		printNeighbor(dugum);
    		break;
    		
    	case 2:
    		printf("Hangi dugum ile aradaki uzakligi ogrenmek istiyorsunuz: ");
    		scanf("%d",&dugumson);
    		
    		nodeDistance(dugum, dugumson-1);
    		break;
    	
    	case 3:
    		printf("Breadth First Search --> ");
    		BFS(dugum);
    		break;
	}

    }
    return 0;
}
