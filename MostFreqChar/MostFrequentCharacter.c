//
//  MostFrequentCharacter.c
//  MostFreqChar
//
//  Created by Kuragin Dmitriy on 29/04/16.
//  Copyright © 2016 Kuragin Dmitriy. All rights reserved.
//

#include "MostFrequentCharacter.h"

#include <stdlib.h>
#include <stdio.h>

#include <pthread/pthread.h>

// Default ASCII table contain 127 chars
#define ASCII_CHARS_TABLE_SIZE 127

// If input size less than this constant then use only one thread for computation
#define MAXIMUM_CHARS_FOR_SINGLE_THREAD 400

typedef struct __c_thread_info {
    const char* source;
    size_t size;
    
    size_t* result;
} c_thread_info;

typedef c_thread_info* c_thread_info_ref;

char mostFrequentCharacterSingleThread(const char* str, const size_t size);

char mostFrequentCharacter(char* str, int size) {
    return goodMostFrequentCharacter((const char *)str, (size_t)size);
}

void* c_thread(void *args) {
    c_thread_info_ref thread_info = (c_thread_info_ref)args;
    
    size_t *result = thread_info->result;
    
    for (size_t index = thread_info->size; index--;) {
        result[thread_info->source[index]] ++;
    }
    
    return NULL;
}

char goodMostFrequentCharacter(const char* str, const size_t size) {
    if (!str || !size) {
        exit(EXIT_FAILURE);
    }
    
    if (size < MAXIMUM_CHARS_FOR_SINGLE_THREAD) {
        return mostFrequentCharacterSingleThread(str, size);
    }
    
    size_t result0[ASCII_CHARS_TABLE_SIZE] = {0};
    size_t result1[ASCII_CHARS_TABLE_SIZE] = {0};
    
    pthread_t thread;
    
    c_thread_info thread_info0;
    c_thread_info thread_info1;
    
    thread_info0.source = str;
    thread_info0.size = size / 2;
    thread_info0.result = (size_t *)&result0;
    
    thread_info1.source = str + (size / 2);
    thread_info1.size = (size + 1) / 2;
    thread_info1.result = (size_t *)&result1;

    if (pthread_create(&thread, NULL, &c_thread, &thread_info1) != 0) {
        exit(EXIT_FAILURE);
    }
    
    c_thread(&thread_info0);
    
    if (pthread_join(thread, NULL) != 0) {
        exit(EXIT_FAILURE);
    }
    
    char maximum = result0[0];
    
    for (size_t index = ASCII_CHARS_TABLE_SIZE; index--;) {
        if ((result0[maximum] + result1[maximum]) < (result0[index] + result1[index])) {
            maximum = result0[index];
        }
    }
    
    return maximum;
}

char mostFrequentCharacterSingleThread(const char* str, const size_t size) {
    if (!size) {
        exit(EXIT_FAILURE);
    }
    
    size_t result[ASCII_CHARS_TABLE_SIZE] = {0};
    
    char maximum = str[0];
    
    for (size_t index = size; index--;) {
        if (result[maximum] < ++result[str[index]]) {
            maximum = str[index];
        }
    }
    
    return maximum;
}