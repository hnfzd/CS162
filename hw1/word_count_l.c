/*
 * Implementation of the word_count interface using Pintos lists.
 *
 * You may modify this file, and are expected to modify it.
 */

/*
 * Copyright © 2019 University of California, Berkeley
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PINTOS_LIST
#error "PINTOS_LIST must be #define'd when compiling word_count_l.c"
#endif

#include "word_count.h"

void init_words(word_count_list_t *wclist) {
  list_init(wclist);
}

size_t len_words(word_count_list_t *wclist) {
  return list_size(wclist);
}

word_count_t *find_word(word_count_list_t *wclist, char *word) {
  /* TODO */
  word_count_t *word_count;

  if(list_empty(wclist)){
    word_count = NULL;
  }
  else{
    word_count = list_entry(list_front(wclist),word_count_t,elem);
    while (!strcmp(word_count->word,word)){
      /* Reach last elem of list */
      if(word_count->elem.next == NULL){
        word_count = NULL;
        break;
      }
      word_count = list_entry(list_next(&word_count->elem),word_count_t,elem);
    }
  }
  return word_count;
}

word_count_t *add_word(word_count_list_t *wclist, char *word) {
  /* TODO */
  word_count_t *word_count;
  word_count = find_word(wclist,word);
  if(word_count == NULL){
    word_count = (word_count_t *) malloc(sizeof(word_count_t));
    word_count->count = 1;
    strcpy(word_count->word,word);
    list_insert(list_tail(wclist),&word_count->elem);
  }
  else{
    word_count->count++;
  }
  return NULL;
}

void fprint_words(word_count_list_t *wclist, FILE *outfile) {
  /* TODO */
  word_count_t *word_count;
  if(wclist!=NULL){
    word_count = list_entry(list_begin(wclist),word_count_t,elem);
    for(word_count = list_entry(list_begin(wclist),word_count_t,elem);list_next(&word_count->elem)!=NULL;\
    word_count = list_entry(list_next(&word_count->elem),word_count_t,elem)){
      fprintf(outfile,"%i\t%s\n",word_count->count,word_count->word);
    }
  }
}

static bool less_list(const struct list_elem *ewc1,
                      const struct list_elem *ewc2, void *aux) {
  /* TODO */
  word_count_t *wc1,*wc2;
  wc1 = list_entry(list_next(ewc1),word_count_t,elem);
  wc2 = list_entry(list_next(ewc2),word_count_t,elem);
  if((wc1->count<wc2->count) || ((wc1->count==wc2->count) && (strcmp(wc1->word,wc2->word)<0))){
    return true;
    }
  return false;
}

void wordcount_sort(word_count_list_t *wclist,
                    bool less(const word_count_t *, const word_count_t *)) {
  list_sort(wclist, less_list, less);
}
