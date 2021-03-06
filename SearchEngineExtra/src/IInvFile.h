///////////////////////////////////////////////////////////////////////////////////////
//
// Author: Robert Luk
// Year: 2010
// Robert Luk (c) 2010
//
// Integrated Inverted Index Declaration:
// This software is made available only to students studying COMP433 (Information
// Retreieval). It should not be used or distributed without consent by the author.
//
////////////////////////////////////////////////////////////////////////////////////////


#ifndef _IINVFILE_
#define _IINVFIEL_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "stem.h"

// Posting structure
typedef struct _post {
	int docid;		// document id
	int freq;		// term frequency
	struct _post * next;	// next pointer
} post;

// Hash node structure
typedef struct _hnode {
	char * stem;		// stem
	post * posting;		// pointer to postings
	int df;			// document frequency
	struct _hnode * next;	// next pointer
} hnode;

// Document related information
typedef struct _DocRec {
	float len;
	char * TRECID;
} DocRec;

// Retrieval record
typedef struct _RetRec {
	int docid;
	float sim;
} RetRec;

// Integrated Inverted Index Class
class IInvFile {
public:
	IInvFile();			// Constructor
	virtual ~IInvFile();		// Deconstructor

	// Hashing related functions and values
	int hsize;			// hash table size
	int hvalue;			// current hash value
	int hash(char * s, int h);	// compute the hash value of s
	hnode * * htable;		// hash table pointer
	void MakeHashTable(int h);	// Create a hash table
	void Clear();			// Clear the hash table entries and postings
	hnode * Find(char * s);		// Find the hash node that has the same stem as s
	hnode * MakeHnode(char * s);	// Create a new hash node

	// File information
	int MaxDocid;			// the number of files indexed
	DocRec * Files; 		// An array to store information about each file

	// Inverted File processing
	post * FindPost(hnode * w, int docid);	// Got the lastest posting?
	float GetIDF(int df);			// Compute the IDF value using df
	post * Add(char * s, int docid, int f);	// Add a posting into the integrated inverted index
	int CountDF(post * p);			// Obsolete (count df from posting list)
	virtual void Save(char * f);			// Save the integrated inverted index to the file f
	virtual void Load(char * f);			// Load the file data into the integrated inverted index

	// Document length
	void MakeDocRec();		// allocate document records
	void DocLen(DocRec File[]);	// Compute document lengths
	void SaveDocRec(char * f);	// Save document record information
	void LoadDocRec(char * f);	// Load document record information
	void ReadTRECID(char * f);
	// Retrieval
	RetRec * result;					// Retrieval result set pointer
	void PrintTop(RetRec * r, int N);			// Print the top N retrieved documents
	void PrintTopTRECFormat(RetRec * r, int N, int queryNumber, char * identifier);			// Print the top N retrieved documents in TREC format
	void PrintTopTRECFormatInTxt(RetRec * r, int N, int queryNumber, char * identifier,  FILE * fp);
	void Normalize(RetRec * r, float qsize);
	void CombineResult(RetRec * r, post * p, float idf);	// Combine the partial retrieval results
	stemmer Stemming;					// Stemmer
	char * GotoNextWord(char * s);				// Delimit the next query term
	virtual void Search(char * q);					// Search one query
	virtual void SearchTRECFormat(char * q, int queryNumber, char * identifier, FILE * fp);					// Search TREC query
	void Retrieval();					// Interactive retrieval
	void RetrievalTRECFormat();
};


#endif // _IINVFILE_
