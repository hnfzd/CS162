/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utililties */

char *new_string(char *str) {
  return strcpy((char *)malloc(strlen(str)+1), str);
}

void init_words(WordCount **wclist) {
  /* Initialize word count.  */
  *wclist = NULL;
}

size_t len_words(WordCount *wchead) {
    size_t len = 0;
    while(wchead){
        wchead = wchead->next;
        len++;
    }
    return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
  /* Return count for word, if it exists */
    WordCount *wc = NULL;
    wc = wchead;
    while(wc && strcmp(wc->word,word)){
        wc = wc->next;         //move to next node
    }
  return wc;
}

void add_word(WordCount **wclist, char *word) {
    /* If word is present in word_counts list, increment the count, otw insert with count 1. */
    WordCount *wc = NULL;
    WordCount *new_wc = NULL;
    char * w;
    w = new_string(word);
    if((wc = find_word(*wclist,w)) != NULL){
        wc->count++;
    }else{
        wc = *wclist;
        /* Append new node in the end of link list */
        new_wc = (WordCount *)malloc(sizeof(WordCount));
        new_wc->count = 1;
        new_wc->word = w;
        new_wc->next = NULL;
        /* If wclist is not NULL, append node into last list */
        if(wc){   
          while(wc->next){
            wc = wc->next;
          }
          /* Stop before NULL, append */
          wc->next = new_wc;
        }
        else{
          /* Current list is NULL, init first node */
          *wclist = new_wc;
        }
    }
}

void fprint_words(WordCount *wchead, FILE *ofile) {
  /* print word counts to a file */
  WordCount *wc;
  for (wc = wchead; wc; wc = wc->next) {
    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}
