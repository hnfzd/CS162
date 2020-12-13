/*

  Word Count using dedicated lists

*/

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

*/

#include <assert.h>
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "word_count.h"

/* Global data structure tracking the words encountered */
WordCount *word_counts = NULL;

/* The maximum length of each word in a file */
#define MAX_WORD_LEN 64

/*
 * 3.1.1 Total Word Count
 *
 * Returns the total amount of words found in infile.
 * Useful functions: fgetc(), isalpha().
 */
int num_words(FILE* infile) {
    int num_words = 0;
    int last_character = 0;
    char ch;
/*     num_words increase by 1 if detect a word seperator pair
    In ascii, space:32, linefeed:10 */
    while((ch = fgetc(infile)) && ch!=EOF){
        if(((ch == 32)||(ch == 10)) && last_character){
            num_words++;
            last_character = 0;
        }else if((ch>0x1F) && (ch<0x7F)){
            last_character = 1;
        }
        else{
          /* Do nothing */
        }
    }
    /* If file end with a word */
    if(last_character){
        num_words++;
        last_character = 0;
    }

  return num_words;
}

/*
 * 3.1.2 Word Frequency Count
 *
 * Given infile, extracts and adds each word in the FILE to `wclist`.
 * Useful functions: fgetc(), isalpha(), tolower(), add_word().
 */
void count_words(WordCount **wclist, FILE *infile) {
    /*  1. Extract one word 
        2. Find in wclist
            2.1 If exist, counter +1
            2.2 If not exsit, create new node
    */
    char word[MAX_WORD_LEN];
    char ch;
    int index = 0;
    int last_character = 0;

    while((ch = fgetc(infile)) && ch!=EOF){
        if(((ch == 32)||(ch == 10)) && last_character){
            last_character = 0;
            word[index]=0;
            add_word(wclist,word);
            index = 0;
        }else if(isalpha(ch)){
            last_character = 1;
            if(isupper(ch)){
                ch = (char)tolower(ch);
            }
            word[index++] = ch;
        }
        else{
          /* Do nothing */
        }
    }
    /* If file end with a word */
    if(last_character){
        last_character = 0;
        word[index]=0;
        add_word(wclist,word);
        index = 0;
    }


}

/*
 * Comparator to sort list by frequency.
 * Useful function: strcmp().
 */
static bool wordcount_less(const WordCount *wc1, const WordCount *wc2) {
//  WordCount temp;
  if((wc1->count<wc2->count) || ((wc1->count==wc2->count) && (strcmp(wc1->word,wc2->word)<0))){
    /* Switch wc1 and wc2 */
/*     strcpy(temp.word,wc1->word);
    temp.count = wc1->count;
    strcpy(wc1->word,wc2->word);
    wc1->count = wc2->count;
    strcpy(wc2->word,temp.word);
    wc2->count = temp.count; */
    return 1;
  }

  return 0;
}

// In trying times, displays a helpful message.
static int display_help(void) {
	printf("Flags:\n"
	    "--count (-c): Count the total amount of words in the file, or STDIN if a file is not specified. This is default behavior if no flag is specified.\n"
	    "--frequency (-f): Count the frequency of each word in the file, or STDIN if a file is not specified.\n"
	    "--help (-h): Displays this help message.\n");
	return 0;
}

/*
 * Handle command line flags and arguments.
 */
int main (int argc, char *argv[]) {

  // Count Mode (default): outputs the total amount of words counted
  bool count_mode = true;
  int total_words = 0;

  // Freq Mode: outputs the frequency of each word
  bool freq_mode = false;

  FILE *infile = NULL;

  // Variables for command line argument parsing
  int i;
  static struct option long_options[] =
  {
      {"count", no_argument, 0, 'c'},
      {"frequency", no_argument, 0, 'f'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0}
  };
  // Sets flags
  while ((i = getopt_long(argc, argv, "cfh", long_options, NULL)) != -1) {
      switch (i) {
          case 'c':
              count_mode = true;
              freq_mode = false;
              break;
          case 'f':
              count_mode = false;
              freq_mode = true;
              break;
          case 'h':
              return display_help();
      }
  }

  if (!count_mode && !freq_mode) {
    printf("Please specify a mode.\n");
    return display_help();
  }

  /* Create the empty data structure */
  init_words(&word_counts);

  if ((argc - optind) < 1) {
    // No input file specified, instead, read from STDIN instead.
    infile = stdin;
  } else {
    // At least one file specified. Useful functions: fopen(), fclose().
    // The first file can be found at argv[optind]. The last file can be
    // found at argv[argc-1].

    if ((infile = fopen(argv[argc-1],"r")) == NULL){
        printf("\nError on open file %s, press ENTER to exit.", argv[argc-1]);
        getchar();
        exit(1);
    };
  }

  if (count_mode) {
    total_words = num_words(infile);
    printf("The total number of words is: %i\n", total_words);
  } else {
    count_words(&word_counts,infile);
    wordcount_sort(&word_counts, wordcount_less);
    printf("The frequencies of each word are: \n");
    fprint_words(word_counts, stdout);
}

fclose(infile);

  return 0;
}
