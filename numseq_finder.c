#include <stdio.h>
#include <stdlib.h>

/* ABOUT
 * Finds the longest number sequence in input and prints it.
 * if the longest number sequences are more than 1, prints all of them.
 * Has no limit for input.
 *
 * Using Unrolled Linked List, Dynamic matrix (string table) for result.
 * Program is complicated by purpose to learn dynamic memory management. */

#define NUM_SEQ_SIZE 64

enum sequence_state {
    SEQUENCE_PROCESS,
    SEQUENCE_END
};

struct node {
    char *num_seq;
    int capacity;
    int count;
    struct node *next;
};

struct str_table {
    char **rows;
    int total_rows;
    int capacity;
};

/* Allocates node and dynamic array in node (num_seq) */
int add_node(struct node **head, struct node **tail) {
    struct node *tmp = malloc(sizeof(struct node));
    if (!tmp) {
        return -1;
    }

    tmp->count = 1;
    tmp->next = NULL;
    tmp->num_seq = malloc(sizeof(char) * 64);
    if (!(tmp->num_seq)) {
        return -1;
    }
    tmp->capacity = 64;

    if (!*head) {
        *head = tmp;
    } else {
        (*tail)->next = tmp;
    }
    *tail = tmp;

    return 0;
}

int str_copy(char *dest, char *src, int size) {
    if (!dest || !src) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
    dest[size-1] = '\0';
    return 0;
}

/* Allocates memory for matrix. If matrix exists, reallocates. */
int matrix_allocate(struct str_table *table, int str_size, int capacity) {
    if (capacity == 1) {
        table->rows = malloc(capacity * sizeof(char *));
        if (!(table->rows)) return -1;

        for (int i = 0; i < capacity; i++) {
            table->rows[i] = malloc(str_size * sizeof(char));
            if (!(table->rows)[i]) return -1;
        }
    } else {
        char **tmp = realloc(table->rows, capacity * sizeof(char *));
        if (!tmp) return -1;
        table->rows = tmp;

        for (int i = table->total_rows; i < capacity; i++) {
            table->rows[i] = malloc(str_size * sizeof(char));
            if (!(table->rows[i])) return -1;
        }
    }

    return 0;
}

/* Finds longest sequences in linked list 
 * and writes num_seq into string table   */
int find_longest_sequences(struct node *src, struct str_table *dest) {
    if (!src || !dest) {
        return -1;
    }

    struct node *tmp = src->next;
    struct node *max = src;
    dest->total_rows = 1;
    dest->capacity = 1;

    int check;

    /* Searching for the longest number sequence */
    while (tmp) {
        if (tmp->count > max->count) {
            max = tmp;
        }
        tmp = tmp->next;
    }

    check = matrix_allocate(dest, max->count+1,
            dest->capacity);
    dest->capacity = dest->total_rows;

    if (check == -1) {
        fputs("[ERROR] Matrix allocation failed.\n", stderr);
        return -1;
    }

    check = str_copy(dest->rows[0], max->num_seq, max->count+1);
    if (check != 0) {
        return check;
    }
    
    tmp = src;

    /* Searching for number sequences that are 
     * as long as max->num_seq */
    while (tmp) {
        if (tmp != max && max->count == tmp->count) {
            if (dest->capacity <= dest->total_rows) {
                check = matrix_allocate(dest, max->count+1,
                        dest->total_rows+2);
                if (check == -1) {
                    fputs("[ERROR] Matrix allocation failed.\n", stderr);
                    return -1;
                }
                dest->capacity = dest->total_rows+2;
            }
            
            check = str_copy(dest->rows[dest->total_rows], 
                    tmp->num_seq, max->count+1);
            if (check != 0) {
                return check;
            }
            dest->total_rows++;
        }

        tmp = tmp->next;
    }
    return 0;
}

int main() {
    struct node *head = NULL, *tail = NULL;
    enum sequence_state seq_state = SEQUENCE_END;
     
    int ch; 
    int malloc_count = 1;
    while ((ch = getchar()) != EOF) {
        if ((ch >= '0') && (ch <= '9')) {
            int check;
            switch(seq_state) {
                case SEQUENCE_END: /* If we starting num sequence */
                    malloc_count = 1;
                    check = add_node(&head, &tail);
                    if (check != 0) {
                        fputs("[ERROR] Memory allocation failed.\n", stderr);
                        goto cleanup;
                    }
                    seq_state = SEQUENCE_PROCESS;
                    tail->num_seq[tail->count-1] = ch;
                    break;
                case SEQUENCE_PROCESS: /* adding elements to num_seq */
                    if (tail->count == tail->capacity) {
                        malloc_count++;
                        tail->capacity = NUM_SEQ_SIZE*malloc_count;
                        char *tmp = realloc(tail->num_seq,
                                tail->capacity);
                        if (!(tmp)) {
                            fputs("[ERROR] Memory reallocation failed.\n",
                                    stderr);
                            goto cleanup;
                        }
                        tail->num_seq = tmp;
                    }
                    tail->num_seq[tail->count] = ch;
                    tail->count++;
                    break;
                default:
                    fputs("[ERROR] Undefined sequence state.\n", stderr);
                    goto cleanup;
                    break;
            }
        } else {
                if (head && (seq_state == SEQUENCE_PROCESS 
                            && tail->num_seq)) {
                    tail->num_seq[tail->count] = '\0';
                    seq_state = SEQUENCE_END;
                }
        }
    }

    if (!head) return 0;

    if (seq_state == SEQUENCE_PROCESS) {
        tail->num_seq[tail->count] = '\0';
        seq_state = SEQUENCE_END;
    }

    struct str_table *num_seq_array = malloc(sizeof(struct str_table));
    if (!num_seq_array) {
        fputs("[ERROR] Matrix allocation failed.", stderr);
        goto cleanup;
    }

    int check = find_longest_sequences(head, num_seq_array);
    if (check == -1) {
        goto cleanup;
    }

    
    for (int i = 0; i < num_seq_array->total_rows; i++) {
        printf("%s ", num_seq_array->rows[i]);
    }
    putchar('\n');

    goto cleanup;
cleanup:
    while (head) {
        struct node *tmp = head;
        head = head->next;
        free(tmp->num_seq);
        free(tmp);
    }
    if (num_seq_array) {
        for (int i = 0; i < num_seq_array->capacity; i++) {
            free(num_seq_array->rows[i]);
        }
        free(num_seq_array->rows);
        free(num_seq_array);
    }

    return 0;
}
