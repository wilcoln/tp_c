#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "events.h"

const char MONTHS[12][10] = {"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"};

date* dates;

// --- Fonctions utilitaires
int index_of_month(char* month){
	int i = 0;
	while(strcmp(MONTHS[i], month) !=0 && i < 12){
		i++;
	}
	return i;
}
int numbify(date d){
	return d.year*10000 + (index_of_month(d.month) + 1)*100 + d.day;
}
void stringify(date d, char date_str[]){
	sprintf(date_str, "%d",numbify(d));
	date_str[9] = '\0';
}
// ---- Fin Fonctions utilitaires 

void remplissage_dates(int n){
	srand(time(NULL));
	int index_month;
	dates = malloc(n*sizeof(date));
	int i;
	for(i = 0; i < n; i++){
		dates[i].day =  1 + rand()%30;
		index_month = rand()%11;
		strcpy(dates[i].month, MONTHS[index_month]);
		dates[i].month[strlen(MONTHS[index_month])] = '\0';
		dates[i].year = 1999 + rand()%101;
	}
		
}

void create_events(int n, event events[]){
	int i;
	char date_str[9];
	for(i = 0; i < n; i++){
		events[i].date_of_event = dates[i];
		stringify(dates[i],date_str);
		strcpy(events[i].description,"Event-");
		strcat(events[i].description, date_str);
	}
}
void display_events(int n, event events[]){
	int i;
	for(i = 0; i < n; i++){
		printf("%s\n",events[i].description);
	}
}

//Renvoie  1 si d1 > d2, 0 si d1 = d2 et -1 si d1 >
int compare_dates(date d1, date d2){
	int nbd1 = numbify(d1);
	int nbd2 = numbify(d2);
	if( nbd1 > nbd2 ) 
		return 1;
	else if (nbd1 < nbd2)
		return -1;
	else 
		return 0;
}

int compare_events(event e1, event e2){
	return compare_dates(e1.date_of_event, e2.date_of_event);
}

void swap_events(event events[], int index1, int index2){
	event tmp = events[index1];
	events[index1] = events[index2];
	events[index2] = tmp;
}

void basic_sort(event events[], int n){
	int i,j,min_index;
	for(i = 0; i < n ; i++){
		min_index = i;
		for(j = i+1; j < n; j++){
			if(compare_events(events[min_index], events[j]) == 1 ){
				min_index = j;
			}
		}
		swap_events(events,min_index,i);
	}
}
void insertion_sort(event events[], int n){
	int i,j,min_index;
	event val;
	for(i = 1; i < n ; i++){
		val = events[i];
		j = i - 1;
		while(j > -1 && compare_events(events[j], val) == 1){
			events[j+1] = events[j];
			j--;
		}
		events[j+1] = val;
	}
}

int partition(event events[], int a, int b){
	int pivot = a;
	int i;
	event tmp;
	for(i = a + 1; i <= b; i++){
		if(compare_events(events[pivot],events[i]) == 1){
			tmp = events[i];
			events[i] = events[pivot+1];
			events[pivot] = events[pivot + 1];
			events[pivot] = tmp;
			pivot++;
		}
	}
	return pivot;
}
void quick_sort(event events[], int a, int b){
	if(b > a){
		int pivot = partition(events,a,b);
		quick_sort(events,a, pivot - 1);
		quick_sort(events,pivot + 1, b);
	}
}

