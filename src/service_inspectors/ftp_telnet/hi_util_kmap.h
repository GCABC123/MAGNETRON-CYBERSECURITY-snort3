//--------------------------------------------------------------------------
// Copyright (C) 2014-2015 Cisco and/or its affiliates. All rights reserved.
// Copyright (C) 2005-2013 Sourcefire, Inc.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------

// hi_util_kmap.h author Marc Norton

#ifndef HI_UTIL_KMAP_H
#define HI_UTIL_KMAP_H

// FIXIT-L this is a dup of the file in http_inspect
//
// Keyword Trie based Map Table
// The tree uses linked lists to build the finite automata
//
// MapKeyFind(): Performs a setwise strcmp() equivalant.
//
// Keys may be ascii or binary, both may be of random sizes.  Each key may
// be a different size, or all one size.  Fast dictionary lookup,
// proportional to the length of the key, and independent of the number of
// keys in the table.  May use more memory than a hash table, depends.
// Memory is allocated as needed, so none is wasted.

#define ALPHABET_SIZE 256

/*
*
*/
typedef struct _keynode
{
    struct  _keynode* next;

    unsigned char* key;
    int nkey;
    void* userdata;          /* data associated with this pattern */
} KEYNODE;

/*
*
*/
typedef struct _kmapnode
{
    int nodechar;     /* node character */

    struct  _kmapnode* sibling;
    struct  _kmapnode* child;

    KEYNODE* knode;
} KMAPNODE;

/*
*
*/
typedef void (* KMapUserFreeFunc)(void* p);
typedef struct _kmap
{
    KMAPNODE* root[256]; /* KTrie nodes */

    KEYNODE* keylist; // list of key+data pairs
    KEYNODE* keynext; // findfirst/findnext node

    KMapUserFreeFunc userfree; // fcn to free user data

    int nchars;      // # character nodes

    int nocase;
} KMAP;

/*
*  PROTOTYPES
*/
KMAP* KMapNew(KMapUserFreeFunc userfree);
void KMapSetNoCase(KMAP* km, int flag);
int KMapAdd(KMAP* km, void* key, int ksize, void* userdata);
void* KMapFind(KMAP* km, void* key, int ksize);
void* KMapFindFirst(KMAP* km);
void* KMapFindNext(KMAP* km);
KEYNODE* KMapFindFirstKey(KMAP* km);
KEYNODE* KMapFindNextKey(KMAP* km);
void KMapDelete(KMAP* km);

#endif

