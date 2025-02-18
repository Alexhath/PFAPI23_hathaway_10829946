#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 999
 //Structures and functions declarations
void insert_station(struct station * z); //Inserts a station in the tree
void delete_station(struct station * z); //Deletes a station from the tree
void inorder(struct station * p); //Prints the tree in order
struct station * create_station(int km); //Creates a station
struct station * tree_search(struct station * x, int km); //Searches a station in the tree
struct station * tree_minimum(struct station * x); //Finds the station having the minimum distance in the tree
struct station * tree_successor(struct station * x); //Finds the successor of a station in the tree
struct station * tree_predecessor(struct station * x); //Finds the predecessor of a station in the tree
struct station * tree_maximum(struct station * x); //Finds the station having the maximum distance in the tree
struct percorso * insertpercorso(struct percorso ** testa, int km); //Insert a station in the path list that it's being calculated
int deleteCar(struct car** head, int autonomy); //Deletes a car from the list of cars

struct station{
    struct station * left;
    int km;
    struct station * right;
    struct station * parent;
    struct car * macchine;
}*station_tree = NULL;

struct car {
    int autonomy;
    struct car * next;
};

struct percorso {
    int km;
    struct percorso * next;
    struct percorso * prev;
};

struct percorso_inv {
    int km;
    struct percorso_inv * next;
    struct percorso_inv * prev;
};


struct percorso * insertpercorso(struct percorso ** testa, int km){
    struct percorso * newperc = (struct percorso *)malloc(sizeof(struct percorso));
    newperc->km = km;
    newperc->next = NULL;


    if((*testa) == NULL){
        (*testa) = newperc;
        return *testa;
    }else{
        newperc->next = (*testa);
        (*testa) = newperc;
    }
    return *testa;
}


int deleteCar(struct car** head, int autonomy){
    struct car * temp;

    if((*head)->autonomy == autonomy){
        temp = (*head);
        (*head) = (*head)->next;
        free(temp);
        return 0;
    }

    else{
        struct car * curr = (*head);
        while (curr->next != NULL)
        {
            if(curr->next->autonomy == autonomy){
                temp = curr->next;
                curr->next = curr->next->next;
                free(temp);
                return 0;
            }
            else{
                curr = curr->next;
            }
        }
    }
    return 1;
}


void insertCar(struct car ** head, int autonomy){
    struct car * newCar = (struct car *)malloc(sizeof(struct car));
    newCar->autonomy = autonomy;
    newCar->next = NULL;

    if((*head) == NULL){
        (*head) = newCar;
        return;
    }

    newCar->next = (*head);
    (*head) = newCar;
}

void deleteperc(struct percorso** testa){
    struct percorso * temp;

    temp = (*testa);
    (*testa) = (*testa)->next;
    free(temp);

}


int printListperc(struct percorso * head){
    while (head != NULL)
    {
        printf("%d ", head->km);
        head = head->next;
        if(head->next == NULL){
            printf("%d\n",head->km);
            return 0;
        }
    }
 return 0;
}

void printListCar(struct car * head){

    while (head != NULL)
    {
        printf("%d ", head->autonomy);
        head = head->next;
    }
    printf("\n");

}


void deleteListCar(struct car * head){
    __attribute__((unused)) struct car* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        temp = NULL;
    }
}


int getCarWithMaximumAutonomy(struct car * head){

    if(head == NULL){
        return 0;
    }

    int max = head->autonomy;

    while (head != NULL)
    {
        if(head->autonomy > max){
            max = head->autonomy;
        }
        head = head->next;
    }

    return 	max;
}

void insert_station(struct station * z){
    struct station * y = NULL;
    struct station * x = station_tree;

    while( x != NULL){
        y = x;
        if (z->km < x->km){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == NULL){
        station_tree = z;
    }
    else if(z->km < y->km){
        y->left = z;
    }
    else{
        y->right = z;
    }

}

void delete_station (struct station * z){
    struct station * y = NULL;
    struct station * x = NULL;
    deleteListCar(z->macchine);

    if(z->left == NULL || z->right == NULL){
        y = z;
    }
    else{
        y = tree_successor(z);
    }

    if(y->left != NULL){
        x = y->left;
    }
    else{
        x = y->right;
    }

    if(x != NULL){
        x->parent = y->parent;
    }
    if(y->parent == NULL){
        station_tree = x;
    }
    else if(y == y->parent->left){
        y->parent->left = x;
    }
    else{
        y->parent->right = x;
    }

    if(y != z){
        z->km = y->km;
        z->macchine = y->macchine;
    }
}

void inorder(struct station * p){
    if(p){
        inorder(p->left);
        printf("%d ", p->km);
        printListCar(p->macchine);
        inorder(p->right);
    }
}

struct station * create_station(int km){
    struct station * station = (struct station *)malloc(sizeof(struct station));
    station->km = km;
    station->macchine = NULL;

    return station;
}

struct station * tree_minimum(struct station * x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

struct station * tree_successor(struct station * x){
    if(x->right != NULL){
        return tree_minimum(x->right);
    }
    struct station * y = x->parent;
    while (y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

struct station * tree_maximum(struct station * x){
    while(x->right != NULL){
        x = x->right;
    }
    return x;
}

//This function ensures that each station in the path list is reachable from the previous station 
//by adjusting the distances in the path list accordingly.
int fixlist(struct percorso * x){
    struct station * curr_prec;
while(x->next->next!= NULL){
    curr_prec= tree_predecessor(tree_search(station_tree,x->next->km));
    while(curr_prec != tree_search(station_tree,x->km)){
    if(curr_prec->km-getCarWithMaximumAutonomy(curr_prec->macchine)<=x->km && x->next->next->km - getCarWithMaximumAutonomy(tree_search(station_tree,x->next->next->km)->macchine)<=curr_prec->km ){
        x->next->km = curr_prec->km;
        }
        curr_prec= tree_predecessor(curr_prec);
    }
    x=x->next;
}
    return 0;
}


    struct station *tree_predecessor(struct station *x) {
        if (x->left != NULL) {
            return tree_maximum(x->left);
        }
        struct station *y = x->parent;
        while (y != NULL && x == y->left) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    struct station *tree_search(struct station *x, int km) {
        if (x == NULL || km == x->km) {
            return x;
        }
        if (km < x->km) {
            return tree_search(x->left, km);
        } else return tree_search(x->right, km);
    }

//x is the starting station and y is the destination station
//testa is the head of the path list that is being calculated
//nuova_testa is the new head of the path list that is being calculated
    int pian_percorso(struct station *x, struct station *y, struct percorso *testa, int nuova_testa) {
        struct station *nodo_arrivo = tree_search(station_tree, y->km);
        struct station *predecessore = tree_predecessor(nodo_arrivo);

        while (predecessore->km != x->km) {
            int somma = predecessore->km + getCarWithMaximumAutonomy(predecessore->macchine);
            if (somma >= y->km && predecessore->km < testa->km) {
                nuova_testa = predecessore->km;
            }
            predecessore = tree_predecessor(predecessore);
        }
        if (x->km + getCarWithMaximumAutonomy(x->macchine) >= testa->km) {
            insertpercorso(&testa, x->km);
            printListperc(testa);
            return 0;
        } else {
            if (nuova_testa == testa->km) {
                printf("nessun percorso\n");
                return 0;
            }
            insertpercorso(&testa, nuova_testa);
            struct station *nuovo = tree_search(station_tree, testa->km);
            pian_percorso(x, nuovo, testa, nuova_testa);
        }
        return 0;
    }

int reversePrint(struct percorso * x, struct percorso * y);
struct percorso* pop(struct percorso * x);

int reversePrint(struct percorso * x, struct percorso * y){
    while(x->next != NULL) {
        insertpercorso(&y, pop(x)->km);
        x=x->next;
    }
    insertpercorso(&y,pop(x)->km);
    printListperc(y);
    return 0;
}

struct percorso* pop(struct percorso * x){
    if(x == NULL){
        return NULL;
    }else {
        return x;
    }
}

int pian_percorso_inv(struct station * x, struct station * y,struct percorso * testa,int nuova_testa){
    struct station * nodo_partenza = tree_search(station_tree, y->km);
    struct station * predecessore = tree_predecessor(nodo_partenza);
    int distmax_nuovo = 0;
    int diff = y->km - getCarWithMaximumAutonomy(y->macchine);

    while (predecessore->km!=x->km) {
        int distmax = y->km - (predecessore->km - getCarWithMaximumAutonomy(predecessore->macchine));
        if (diff <= predecessore->km && predecessore->km<=nuova_testa && distmax >=distmax_nuovo ) {
                nuova_testa = predecessore->km;
                distmax_nuovo = distmax;
        }
        predecessore = tree_predecessor(predecessore);
    }
    if(nuova_testa-getCarWithMaximumAutonomy(tree_search(station_tree,nuova_testa)->macchine)<=x->km){
        insertpercorso(&testa,nuova_testa);
        insertpercorso(&testa,x->km);
        struct percorso * lista_perc_inv = NULL;
        fixlist(testa);
        reversePrint(testa,lista_perc_inv);
        return 0;
    }else if(nuova_testa==testa->km){
            printf("nessun percorso\n");
            return 0;
        }else{
        insertpercorso(&testa,nuova_testa);
        struct station * nuovo = tree_search(station_tree, testa->km);
        pian_percorso_inv(x,nuovo,testa,nuova_testa);
    }
    return 0;
}

    int main() {
        char input[MAX];
        int num_car;
        int distanza;
        int autonomia;
        int staz_part;
        int staz_arr;
        while (scanf("%s", input) != EOF) {
            if (strcmp(input, "aggiungi-stazione") == 0) {
                if (scanf("%d", &distanza)) {}
                struct station *staz = tree_search(station_tree, distanza);
                if (staz != NULL) {
                    printf("non aggiunta\n");
                } else if (staz == NULL) {
                    struct station *current_station = create_station(distanza);
                    insert_station(current_station);
                    printf("aggiunta\n");
                    if (scanf("%d", &num_car)) {}
                    if (num_car != 0) {
                        for (int i = 0; i < num_car; i++) {
                            if (scanf("%d", &autonomia)) {}
                            insertCar(&current_station->macchine, autonomia);
                        }
                    }
                }
            } else if (strcmp(input, "demolisci-stazione") == 0) {
                if (scanf("%d", &distanza)) {}
                struct station *todelete = tree_search(station_tree, distanza);
                if (todelete == NULL) {
                    printf("non demolita\n");
                } else {
                    delete_station(todelete);
                    printf("demolita\n");
                }
            } else if (strcmp(input, "aggiungi-auto") == 0) {
                if (scanf("%d", &distanza)) {}
                struct station *agg_car = tree_search(station_tree, distanza);
                if (agg_car == NULL) {
                    printf("non aggiunta\n");
                } else {
                    if (scanf("%d", &autonomia)) {}
                    insertCar(&agg_car->macchine, autonomia);
                    printf("aggiunta\n");
                }
            } else if (strcmp(input, "rottama-auto") == 0) {
                if (scanf("%d", &distanza)) {}
                struct station *staz = tree_search(station_tree, distanza);
                if (scanf("%d", &autonomia)) {}
                if (staz != NULL) {
                    if (deleteCar(&staz->macchine, autonomia) == 0) {
                        printf("rottamata\n");
                    } else {
                        printf("non rottamata\n");
                    }
                } else if (staz == NULL) {
                    printf("non rottamata\n");
                }
            } else if (strcmp(input, "pianifica-percorso") == 0) {
                if (scanf("%d", &staz_part)) {}
                if (scanf("%d", &staz_arr)) {}
                struct station *partenza = tree_search(station_tree, staz_part);
                struct station *arrivo = tree_search(station_tree, staz_arr);
                struct percorso *testa = NULL;
                if (staz_part == staz_arr) {
                    printf("%d\n", staz_part);
                } else if (staz_part < staz_arr) {
                    struct percorso *testina = insertpercorso(&testa, staz_arr);
                    int nuova_testa = staz_arr;
                    pian_percorso(partenza, arrivo, testina, nuova_testa);
                } else {
                    //il percorso viene fatto andando indietro
                    struct percorso * testona = insertpercorso(&testa, staz_part);
                    int nuova_testa = staz_part;
                    pian_percorso_inv(arrivo, partenza,testona, nuova_testa);
                }
            }
       return 0;
        }
    }
