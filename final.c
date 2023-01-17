#include <stdio.h>
#include <string.h>
#include <unistd.h>

int char_index(char c, char *string) {
  for (int i = 0; string[i] != '\0'; i++)
    if (string[i] == c)
      return i;

  return -1;
}

void save(char *ch) {
  char *fn = "history.txt";

  // open the file for writing
  FILE *fp = fopen(fn, "a");
  if (fp == NULL) {
    printf("Error opening the file %s", fn);
  }
  // write to the text file

  fprintf(fp, "%s\n", ch);

  // close the file
  fclose(fp);
}

void history() {
  char *fn = "history.txt";

  // open the file for writing
  FILE *fp = fopen(fn, "r");
  if (fp == NULL) {
    printf("Error opening the file %s", fn);
  }
  // write to the text file
  char line[200];
  while (fgets(line, sizeof(line), fp)) {
    printf("%s", line);
  }

  // close the file
  fclose(fp);
}

int cd(char *c) {
  int ns = 0;
  int r;
  char ch[200];
  strcpy(ch, c);
  // Traverse a string and if it is non space character then, place it at index
  // non_space_count

  for (int i = 0; ch[i] != '\0'; i++) {
    if (ch[i] != ' ') {
      ch[ns] = ch[i];
      ns++; // non_space_count incremented
    }
  }

  // Finally placing final character at the string end
  ch[ns] = '\0';
  char *pos;
  pos=strchr(c,'d');
  if (ch[0] == 'c' && ch[1] == 'd' && pos!=NULL && *(pos+1)==' ') {
    char *to;
    to = strndup(&ch[2], strlen(ch));
    if (chdir(to) != 0){
      return 2 ;
      }
    else return 0 ; 
  } else
    return 1;
}

int quit(char *c) {
  int ns = 0;
  int r;
  char ch[200];
  strcpy(ch, c);
  for (int i = 0; ch[i] != '\0'; i++) {
    if (ch[i] != ' ') {
      ch[ns] = ch[i];
      ns++;
    }
  }
  ch[ns] = '\0';

  if (strcmp(ch, "quit") == 0) {
    return (1);
  } else
    return 0;
}

int verif(char *c) {
  char *pos;
  char *pos1;
  char *pos2;
  pos = strchr(c, ';');
  pos1 = strchr(c, '&');
  pos2 = strchr(c, '|');
  if (pos != NULL && *(pos + 1) != ';' ) {
    return 1;
  } else if (pos1 != NULL && *(pos1 + 1) == '&' && c[0] != '&') {
    return 2;
  } else if (pos2 != NULL && *(pos2 + 1) == '|' && c[0] != '|') {
    return 3;
  } else
    return 0;
}
char *deletelinebreak(char *ch) {
  char *pos;
  if ((pos = strchr(ch, '\n')) != NULL)
    *pos = '\0';
  return (ch);
}

void execution(char *com) {
  FILE *fp;
  int status;
  char path[200];
  int i = 0;
  fp = popen(com, "r");
  if (fp == NULL) {
    printf("%s", "handle error");
  } else {
    while (fgets(path, sizeof(path), fp) != NULL) {
      printf("%s", path);
    }
    status = pclose(fp);
  }
}

int main() {
  
  char c[100];
  char *command;
  char cd1[100];
  char s[100];
  const char ch[] = ";";
  const char ch1[] = "&&";
  const char ch2[] = "||";
  while (1) {

    // printing current working directory
    printf("%s%%", getcwd(s, 100));
    fgets(c, sizeof(c), stdin);
    command = deletelinebreak(c);
    save(command);

    if (verif(command) == 1) {
      char *ptr = strtok(command, ";");
      while (ptr != NULL) {
        if(cd(ptr)==0){
          
        }
          else if (cd(ptr)==2){
            printf("%s","No such file or directory \n");
          }
          else if (quit(ptr) == 1) {
          return (0);
        } else {
          execution(ptr);
        }
        ptr = strtok(NULL, ";");
      }
    }

    else if (verif(command) == 2) {
      execution(command);
    }
    else if (verif(command) == 3) {
      execution(command);
    }

    /*  else if (strstr(command, ".bat") != NULL && strstr(command, " ") ==
      NULL) { FILE *file = fopen(command, "r"); if (file == NULL) {
          printf("%s\n", "Fichier batch non existant");
        } else {
          char line[200];
          while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            if (strstr(line, ";&|") != NULL) {
              char *ptr = strtok(deletelinebreak(line), ";&|");
              while (ptr != NULL) {
                execution(ptr);
                save(ptr);
                ptr = strtok(NULL, ";&|");
              }
            } else {
              execution(line);
              save(deletelinebreak(line));
            }
          }
        }

      }*/

    else if (strcmp(command, "history") == 0) {
      history();
    } else if (cd(command) == 0) {

    }
      else if (cd(command) == 2) {
       printf("%s","No such file or directory \n");
    }
    else if (quit(command) == 1) {
      return (0);
    }

    else {
      execution(command);
    }
  }
}
