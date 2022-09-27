#include <stdio.h>
#include <stdlib.h>

char* callNote() {
    // https://stackoverflow.com/questions/1088622/how-do-i-create-an-array-of-strings-in-c
    printf("I am note.\n");
    char *notes[] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    int r = rand() % 12;
    printf("One Note:  %s.\n", notes[r]);
    return notes[r];
};
void callClock(){
    printf("I am clock.\n");
}
void callSomething(){
    printf("I am something.\n");
}
