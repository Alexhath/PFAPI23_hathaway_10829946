#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 999


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
    //struct car * prev;
};

struct percorso {
    int km;
    struct percorso * next;
    struct percorso * prev;
    //struct percorso * ultimo;
};

struct percorso_inv {
    int km;
    struct percorso_inv * next;
    struct percorso_inv * prev;
    //struct percorso * ultimo;
};



void insert_station(struct station * z);
void delete_station(struct station * z);
void inorder(struct station * p);
struct station * create_station(int km);
struct station * tree_search(struct station * x, int km);
struct station * tree_minimum(struct station * x);
struct station * tree_successor(struct station * x);
struct station * tree_predecessor(struct station * x);
struct station * tree_maximum(struct station * x);
//void deleteListperc(struct percorso * testa);
struct percorso * insertpercorso(struct percorso ** testa, int km);
int deleteCar(struct car** head, int autonomy);

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

/*struct percorso_inv * insertpercinorder(struct percorso_inv ** head, int km){
    //ordered insertion
    struct percorso * newper = (struct percorso *)malloc(sizeof(struct percorso));
    newper->km = km;
    newper->next = NULL;
    newper->prev = NULL;

    if((*head) == NULL){
        (*head) = newper;
        return 0;
    }

    struct percorso_inv * current = (*head);
    while (current->next != NULL && current->next->km > km)
    {
        current = current->next;
    }

    if(current->prev == NULL){
        newper->next = current;
        current->prev = newper;
        (*head) = newper;
    }
    else if (current ->next == NULL)
    {
        current->next = newper;
        newper->prev = current;
    }
    else{
        newper->prev = current;
        newper->next = current->next;
        current->next->prev = newper;
        current->next = newper;
    }
    return current;
}*/

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
                //break;
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
    //newCar->prev = NULL;

    if((*head) == NULL){
        (*head) = newCar;
        return;
    }

    newCar->next = (*head);
    //(*head)->prev = newCar;
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

/*void deleteListperc(struct percorso_inv * testa){

    while(testa != NULL){
        __attribute__((unused)) struct percorso_inv * temp = testa;
        testa = testa->next;
        temp = NULL;
    }
}*/

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
        //printf("Non trovo il massimo\n");
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
    //return y;
}

void inorder(struct station * p){
    if(p){
       // printf("Sto per stampare il figlio sx %d\n", p->km);
        inorder(p->left);
        printf("%d ", p->km);
        //printf("Sto per stampare la lista del nodo %d\n", p->km);
        printListCar(p->macchine);
       // printf("Sto per stampare il figlio dx %d\n", p->km);
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

/*int fixlistperc(struct percorso * x){
    if(x->next == NULL){
        return 0;
    }
    while(x->km - getCarWithMaximumAutonomy(tree_search(station_tree,x->km)->macchine)<= tree_predecessor(tree_search(station_tree,x->next->km))->km){
        //x->next->next->km = tree_successor(tree_search(station_tree,x->next->km))->km;
        x->next->km = tree_predecessor(tree_search(station_tree,x->next->km))->km;
        //printf("%d\n",x->next->km);
    }
    //printf("%d\n",x->next->km);
    //printf("%d\n",x->next->next->km);
    fixlistperc(x->next);
    return 0;
}*/
int fixlist(struct percorso * x){
    struct station * curr_prec;
    //printf("Sono in fixlist!\n");
while(x->next->next!= NULL){
    //printf("Sono nel primo while\n");
    curr_prec= tree_predecessor(tree_search(station_tree,x->next->km));
    //printf("Prima del while curr_prec é %d\n",curr_prec->km);
    while(curr_prec != tree_search(station_tree,x->km)){
        //printf("Sono nel secondo while %d\n", curr_prec->km);
    if(curr_prec->km-getCarWithMaximumAutonomy(curr_prec->macchine)<=x->km && x->next->next->km - getCarWithMaximumAutonomy(tree_search(station_tree,x->next->next->km)->macchine)<=curr_prec->km ){
             //printf("1)Sono nell'if %d\n",x->next->km);
        x->next->km = curr_prec->km;
        //printf("2) Sono nell'if %d\n",x->next->km);
        }
        curr_prec= tree_predecessor(curr_prec);
    }
    x=x->next;
}
    return 0;
}


/*int fixlistperc(struct percorso * testa,int fine) {
    //struct station * boh = tree_search(station_tree,testa->next->km);// il mio primo boh é il secondo elemento della lista, poi andrá aggiornato
    struct station * nodo_succ = tree_search(station_tree,testa->next->next->km);
    struct station * succ = tree_successor(nodo_succ);
    if (testa->next->next->km == fine) {
        return 0;
    } else {
        while (testa->km != tree_successor(succ)->km) {
            printf("Iterazione: %d Succ: %d\n", testa->km, succ->km);
            struct station *tree_head = tree_search(station_tree,testa->km);
            printf("%d\n", tree_head->km);
            int diff = tree_head->km - getCarWithMaximumAutonomy(tree_head->macchine);
            if (diff <= succ->km) {
                testa->next->km = succ->km;
                testa = testa->next;
                printf("Sono nell if e la testa nuova é: %d\n", testa->km);
            } else {
                succ = tree_successor(succ);
            }
        }
    }
    fixlistperc(testa, fine);
    return 0;
}*/
/*int fixlistperc(struct percorso * testa,int fine) {
    struct station * boh = tree_search(station_tree, testa->next->next->km);
    while (boh->km != testa->km) {
        printf("Le prime tre sono : %d %d %d\n", testa->km, testa->next->km, boh->km);
        //printf("Sono entrato nell'if perche %d é > di %d\n",testa->next->km,tree_successor(boh)->km);
        struct station *station_head = tree_search(station_tree, testa->km);
        int diff = station_head->km - getCarWithMaximumAutonomy(station_head->macchine);
        if (diff <= tree_successor(boh)->km) {
            testa->next->km = tree_successor(boh)->km;
            boh = tree_successor(tree_successor(boh));
            testa = testa->next;
            testa->next = testa->next->next;
        } else {
            testa = testa->next;
            testa->next = testa->next->next;
            boh = tree_successor(tree_successor(boh));
        }
    }
    if(boh->km == fine){
        return 0;
    }else {
        fixlistperc(testa, fine);
    }
    return 0;
}*/



    /*int printListpercinv(struct percorso_inv ** head) {
    struct percorso_inv* tail = *head;
    while(tail->next!=NULL){
        tail = tail->next;
    }

    while(tail!= *head){
        printf("%d ", tail->km);
        tail = tail->prev;
    }
    printf("%d\n",tail->km);
    return 0;
    }*/

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

//x é la partenza, y é l'arrivo

    int pian_percorso(struct station *x, struct station *y, struct percorso *testa, int nuova_testa) {
        //printf("sono entrato nel pian_percorso\n");
        //printf("é l'array");
        //printf("passato head\n");
        //struct percorso * testa = NULL;
        //printf("passato hed 2\n");
        struct station *nodo_arrivo = tree_search(station_tree, y->km);
        struct station *predecessore = tree_predecessor(nodo_arrivo);
        //printf("trovato il predec: %d\n",predecessore->km);
        //printf("Dovrei stampare la lista\n");
        //printListperc(testa);

        while (predecessore->km != x->km) {
            //printf("iterazione : %d ", predecessore->km);
            int somma = predecessore->km + getCarWithMaximumAutonomy(predecessore->macchine);
            //printf("La somma é %d\n",somma);
            //se la somma tra la distanza del predecessore e la max autonomia é >= di quella a cui si deve arrivare
            //e la dist del predecessore é minore di quella che é nella lista del percorso inserisco la stazione nella lista
            if (somma >= y->km && predecessore->km < testa->km) {
                //printf("Sono nell'if che crea la nuova testa\n");
                //int somma_vera = predecessore->km + getCarWithMaximumAutonomy(predecessore->macchine);
                //insertpercorso(&testa,predecessore->km);
                //printListperc(testa);
                nuova_testa = predecessore->km;
                //printf("La nuova testa sará: %d\n",predecessore->km);
            }
            predecessore = tree_predecessor(predecessore);
        }
        //printf("Sono uscito dal while!\n");
        //printf("il vecchia testa della lista é %d\n",testa->km);
        if (x->km + getCarWithMaximumAutonomy(x->macchine) >= testa->km) {
            insertpercorso(&testa, x->km);
            //printf("Sono nell'if per stampare la lista!\n");
            printListperc(testa);
            //deleteListperc(testa);
            return 0;
        } else {
            if (nuova_testa == testa->km) {
                printf("nessun percorso\n");
                return 0;
            }
            insertpercorso(&testa, nuova_testa);
            struct station *nuovo = tree_search(station_tree, testa->km);
            pian_percorso(x, nuovo, testa, nuova_testa);
            //printListperc(testa);
        }
        return 0;
    }

int reversePrint(struct percorso * x, struct percorso * y);
struct percorso* pop(struct percorso * x);

int reversePrint(struct percorso * x, struct percorso * y){
    //printf("stampami x: %d", x->km);
    while(x->next != NULL) {
        insertpercorso(&y, pop(x)->km);
        x=x->next;
    }
    insertpercorso(&y,pop(x)->km);
    //fixlistperc(y);
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
    //printf("sono entrato nel pian_percorso\n");
    //printf("é l'array");
    //printf("passato head\n");
    //struct percorso * testa = NULL;
    //printf("passato hed 2\n");
    struct station * nodo_partenza = tree_search(station_tree, y->km);
    struct station * predecessore = tree_predecessor(nodo_partenza);
    //printf("trovato il predec: %d\n",predecessore->km);
    //printf("Dovrei stampare la lista\n");
    //printListperc(testa);
    int distmax_nuovo = 0;
    int diff = y->km - getCarWithMaximumAutonomy(y->macchine);

    while (predecessore->km!=x->km) {
        //printf("iterazione : %d ", predecessore->km);
        int distmax = y->km - (predecessore->km - getCarWithMaximumAutonomy(predecessore->macchine));
        //printf("La somma é %d\n",somma);
        //struct station * predipred = tree_predecessor(predecessore);
        //int maxdist = predecessore->km - getCarWithMaximumAutonomy(predecessore->macchine);
        //struct station * predecessore = tree_predecessor(predecessore);
        if (diff <= predecessore->km && predecessore->km<=nuova_testa && distmax >=distmax_nuovo ) {
            //printf("Sono nell'if che crea la nuova testa\n");
            //if(maxdist<=diff){
               // nuova_testa= predipred->km;
            //}else {

                //int somma_vera = predecessore->km + getCarWithMaximumAutonomy(predecessore->macchine);
                //insertpercorso(&testa,predecessore->km);
                //printListperc(testa);
                nuova_testa = predecessore->km;
                distmax_nuovo = distmax;
                //printf("La nuova testa sará: %d\n",predecessore->km);
            //}
        }
        predecessore = tree_predecessor(predecessore);
    }
    //printf("Sono uscito dal while!\n");
    //printf("il vecchia testa della lista é %d\n",testa->km);
    if(nuova_testa-getCarWithMaximumAutonomy(tree_search(station_tree,nuova_testa)->macchine)<=x->km){
        insertpercorso(&testa,nuova_testa);
        insertpercorso(&testa,x->km);
        struct percorso * lista_perc_inv = NULL;
        //printf("Sono nell'if per stampare la lista!\n");
        //printListperc(testa);
        //printf("La testa che sto per ritornare é: %d\n", testa->km);
        fixlist(testa);
        reversePrint(testa,lista_perc_inv);
        //fixlistperc(lista_perc_inv);
        //printListperc(testa);
        //printListpercinv(&testa);
        //deleteListperc(testa);
        return 0;
    }else if(nuova_testa==testa->km){
            printf("nessun percorso\n");
            //printf("Sto per ritornare NULL\n");
            return 0;
        }else{
        insertpercorso(&testa,nuova_testa);
        struct station * nuovo = tree_search(station_tree, testa->km);
        pian_percorso_inv(x,nuovo,testa,nuova_testa);
    }
    return 0;
}


   /* int pian_percorso_inv(struct station *x, struct station *y, struct percorso *testa, int nuova_testa, int fine) {
        //printf("Sono entrato!\n");
        struct station *nodo_arrivo = tree_search(station_tree, y->km);
        struct station *successore = tree_successor(nodo_arrivo);
        //printf("Il successore trovato é %d\n", successore->km);
        //printListperc(testa);

        while (successore->km != x->km) {

            int differenza = successore->km - getCarWithMaximumAutonomy(successore->macchine);
            //printf("La diff é: %d\n", differenza);

            if (differenza <= y->km && successore->km > testa->km) {

                nuova_testa = successore->km;

            }
            successore = tree_successor(successore);
        }
        //printf("Sono uscito dal while!\n");

        if (x->km - getCarWithMaximumAutonomy(x->macchine) <= testa->km) {
            insertpercorso(&testa, x->km);
            //printListpercinv(testa);
            fixlistperc(testa);
            printListpercinv(testa);
            deleteListperc(testa);
            return 0;
        } else {
            if (nuova_testa == testa->km) {
                printf("nessun percorso\n");
                return 0;
            }
            //printf("La nuova testa da inserire é: %d\n", nuova_testa);
            insertpercorso(&testa, nuova_testa);
            //printListperc(testa);
            struct station *nuovo = tree_search(station_tree, testa->km);
            pian_percorso_inv(x, nuovo, testa, nuova_testa, fine);
        }
        return 0;
    }
*/

    int main() {
        char input[MAX];
        int num_car;
        int distanza;
        int autonomia;
        int staz_part;
        int staz_arr;
        while (scanf("%s", input) != EOF) {
            //printf("Iterazione\n");
            if (strcmp(input, "aggiungi-stazione") == 0) {
                //printf("Nell'if\n");
                if (scanf("%d", &distanza)) {}
                struct station *staz = tree_search(station_tree, distanza);
                if (staz != NULL) {
                    // printf("Mi hai appena chiesto di aggiungere una stazione che c'é giá\n");
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
                    }//else{
                    // printf("0 macchine!!\n");
                    // inorder(station_tree);
                    //printList(current_station->macchine);
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
                //printf("Hey sono in rottama auto\n");
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
                //struct percorso_inv *zemel = NULL;
                if (staz_part == staz_arr) {
                    printf("%d\n", staz_part);
                } else if (staz_part < staz_arr) {
                    struct percorso *testina = insertpercorso(&testa, staz_arr);
                    int nuova_testa = staz_arr;
                    //inorder(station_tree);
                    pian_percorso(partenza, arrivo, testina, nuova_testa);
                } else {
                    //il percorso viene fatto andando indietro
                    //printf("Ho letto che la part é > dell'arr\n");
                    struct percorso * testona = insertpercorso(&testa, staz_part);
                    //struct percorso * lista_perc_inv = NULL;
                    int nuova_testa = staz_part;
                    //int fine = staz_arr;
                    //inorder(station_tree);
                    pian_percorso_inv(arrivo, partenza,testona, nuova_testa);
                    //struct percorso * boh = pian_percorso_inv(arrivo, partenza,testona, nuova_testa);
                    //printf("Il valore di boh é %d\n", boh->km);
                    //if(pian_percorso_inv(arrivo, partenza,testona, nuova_testa) == 1){
                       // printf("nessun percorso\n");
                    //}
                       //struct percorso * boh = pian_percorso_inv(arrivo, partenza,testona, nuova_testa);
                        //printf("Sto cercando di invertire la lista\n");
                       //reversePrint(boh,lista_perc_inv);
                    }
                    //reversePrint(testona,lista_perc_inv);
                }
            }
       return 0;
        }
        //inorder(station_tree);
        //return 0;
