#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "doubly_linked_list.h"


struct doubly_linked_list_t* dll_create(){
    struct doubly_linked_list_t *ret = (struct doubly_linked_list_t *)malloc(sizeof(struct doubly_linked_list_t));
    if(ret == NULL){
        return NULL;
    }

    ret->tail = NULL;
    ret->head = NULL;

    return ret;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value){
    if(dll == NULL)  return 1;
    struct node_t *temp;

    temp = (struct node_t*)malloc(sizeof(struct node_t));
    if(temp == NULL){
        return 2;
    }

    if (dll->head == NULL) {
        dll->head = temp;
        dll->head->data = value;
        dll->head->next = NULL;
        dll->head->prev = NULL;
        dll->tail = dll->head;
        dll->tail->data = value;
        dll->tail->next = NULL;
        dll->tail->prev = NULL;
        return 0;
    }

    struct node_t *t = dll->tail;
    dll->tail->next = temp;
    temp->data = value;
    temp->next = NULL;
    dll->tail = temp;
    dll->tail->data = value;
    dll->tail->next = NULL;
    dll->tail->prev = t;

    return 0;
}
int dll_push_front(struct doubly_linked_list_t* dll, int value){
    if(dll == NULL)  return 1;
    struct node_t *temp;

    temp = (struct node_t *)malloc(sizeof(struct node_t));
    if(temp == NULL){
        return 2;
    }

    if (dll->head == NULL) {
        dll->head = temp;
        dll->head->data = value;
        dll->head->next = NULL;
        dll->head->prev = NULL;
        dll->tail = dll->head;
        dll->tail->data = value;
        dll->tail->next = NULL;
        dll->tail->prev = NULL;
        return 0;
    }

    temp->data = value;
    temp->next = dll->head;
    dll->head->prev = temp;
    temp->prev = NULL;
    dll->head = temp;


    return 0;
}
int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }
    struct node_t *temp;
    int ret;

    if(dll->head == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(dll->head->next == NULL){
        ret = dll->head->data;
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
        if(err_code != NULL){
            *err_code = 0;
        }
        return ret;
    }

    ret = dll->head->data;
    temp = dll->head;
    dll->head = dll->head->next;
    dll->head->prev = NULL;
    free(temp);

    if(err_code != NULL){
        *err_code = 0;
    }
    return ret;
}
int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }
    struct node_t *temp;
    int ret;

    if(dll->head == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }
    if(dll->head->next == NULL){
        ret = dll->head->data;
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
        if(err_code != NULL){
            *err_code = 0;
        }
        return ret;
    }

    ret = dll->tail->data;

    temp = dll->tail;
    dll->tail = dll->tail->prev;
    dll->tail->next = NULL;
    free(temp);



    if(err_code != NULL){
        *err_code = 0;
    }
    return ret;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(dll->head == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(err_code != NULL){
        *err_code = 0;
    }
    return dll->head->data;
}
int dll_back(const struct doubly_linked_list_t* dll, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(dll->head == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(err_code != NULL){
        *err_code = 0;
    }

    return dll->tail->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll){
    if(dll == NULL){
        return NULL;
    }

    return dll->head;
}
struct node_t* dll_end(struct doubly_linked_list_t* dll){
    if(dll == NULL){
        return NULL;
    }

    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll){
    if(dll == NULL){
        return -1;
    }

    if(dll->head == NULL){
        return 0;
    }

    struct node_t *temp;
    temp = dll->head;

    int counter = 0;
    while(temp->next != NULL){
        temp = temp->next;
        counter ++;
    }

    return counter+1;
}
int dll_is_empty(const struct doubly_linked_list_t* dll){
    if(dll == NULL)  return -1;

    if(dll->head == NULL) return 1;

    return 0;
}
int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(dll == NULL){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if((int)index >= dll_size(dll)){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    struct node_t *temp = dll->head;
    for(int i = 1; i <= (int)index; i++){
        temp = temp->next;
    }

    if(err_code != NULL){
        *err_code = 0;
    }
    return temp->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value){
    if(dll == NULL || (int)index < 0){
        return 1;
    }

    if((int)index > dll_size(dll)){
        return 1;
    }

    if(index == 0){
        if(dll_push_front(dll, value) == 2){
            return 2;
        }
        return 0;
    }
    else if((int)index == dll_size(dll)){
        if(dll_push_back(dll, value) == 2){
            return 2;
        }
        return 0;
    }

    struct node_t *before = dll->head;
    struct node_t *after;
    for(int i = 1; i < (int)index; i++){
        before = before->next;
    }

    after = before->next;

    struct node_t *t = (struct node_t *)malloc(sizeof(struct node_t));
    if(t == NULL){
        return 2;
    }
    t->data = value;
    t->next = after;
    t->prev = before;
    before->next = t;
    after->prev = t;

    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(dll == NULL || (int)index < 0){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if((int)index >= dll_size(dll) || dll_is_empty(dll) == 1){
        if(err_code != NULL){
            *err_code = 1;
        }
        return 1;
    }

    if(index == 0){
        if(err_code != NULL){
            *err_code = 0;
        }
        return dll_pop_front(dll, NULL);
    }
    else if((int)index == dll_size(dll) - 1){
        if(err_code != NULL){
            *err_code = 0;
        }
        return dll_pop_back(dll, NULL);
    }
    int ret;

    struct node_t *before = dll->head;
    struct node_t *after;
    for(int i = 1; i < (int)index; i++){
        before = before->next;
    }

    after = before->next;
    struct node_t *delete = after;
    ret = delete->data;
    after = after->next;
    after->prev = before;
    free(delete);

    before->next = after;

    if(err_code != NULL){
        *err_code = 0;
    }

    return ret;
}

void dll_clear(struct doubly_linked_list_t* dll){
    if(dll == NULL){
        return;
    }

    if(dll->head == NULL){
        return;
    }

    struct node_t *delete = dll->head;

    while(dll->head != NULL){
        delete = dll->head;
        dll->head = dll->head->next;
        free(delete);
    }

}

void dll_display(const struct doubly_linked_list_t* dll){
    if(dll == NULL || dll->head == NULL){
        return;
    }

    struct node_t *temp = dll->head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }

    return;
}

void dll_display_reverse(const struct doubly_linked_list_t* dll){
    if(dll == NULL || dll->head == NULL){
        return;
    }

    struct node_t *temp = dll->tail;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->prev;
    }

    return;
}