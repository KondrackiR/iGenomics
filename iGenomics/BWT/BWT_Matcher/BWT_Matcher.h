//
//  BWT_Matcher.h
//  LabProject7
//
//  Created by Stuckinaboot Inc. on 9/15/12.
//
//

//ORGANIZE INTO FUNCTIONS

#import <Foundation/Foundation.h>
#import "GlobalVars.h"

#import "BWT_Matcher_InsertionDeletion.h"
#import "BWT_Matcher_InsertionDeletion_InsertionHolder.h"
#import "BWT_Matcher_Approxi.h"
#import "ED_Info.h"
#import "Chunks.h"
#import "BWT_MatcherSC.h"

//CONSTANTS
#define kReedsArraySeperationStr @"\n"

#define kMaxBytesForIndexer 101
#define kMaxMultipleToCountAt 100

//#define kBytesForIndexer 101//101
//#define kMultipleToCountAt 50//50

#define kACGTLen 4
#define kACGTStr "ACGT"

#define kDelMarker '-'
#define kInsMarker '+'

#define kLowestAllowedCoverage 5

#define kMaxEditDist 4

#define kDebugPrintInsertions 1
#define kDebugOn 0

#define kPrintReadInfo 0

extern int posOccArray[kACGTLen+2][kMaxBytesForIndexer*kMaxMultipleToCountAt];//+2 because of deletions +1(-) and insertions +2(+) __________________I----- GLOBAL ------I

@protocol BWT_MatcherDelegate <NSObject>
- (void)readProccesed;
@end
@interface BWT_Matcher : NSObject {
    
    //Constants made variable
    int kBytesForIndexer;
//    int kMultipleToCountAt;
    
    //Parameters
    int matchType;
    int alignmentType;
    
    //New Vars
    int maxSubs;
    NSArray *reedsArray;
//    char *refStrBWT;
//    int fileStrLen;
//    char *originalStr;
    
    NSMutableArray *insertionsArray;
    
    BWT_MatcherSC *exactMatcher;
    
    //Old Vars
//    int acgtOccurences[kMaxBytesForIndexer][kACGTLen];//Occurences for up to each multiple to count at
//    char *acgt;
//    int acgtTotalOccs[kACGTLen];
}
@property (nonatomic) id <BWT_MatcherDelegate> delegate;
@property (nonatomic) NSMutableArray *insertionsArray;
@property (nonatomic) int kBytesForIndexer, /*kMultipleToCountAt, */alignmentType, matchType;
@property (nonatomic) int readLen, refSeqLen, numOfReads;

- (id)initWithOriginalStr:(char*)orgStr;
- (void)setUpReedsFile:(NSString*)fileName fileExt:(NSString*)fileExt refStrBWT:(char*)bwt andMaxSubs:(int)subs;

- (char*)getReverseComplementForSeq:(char*)seq;

- (void)matchForJustIndels:(NSArray*)array withLastCol:(char*)lastCol;
- (void)matchReedsArray:(NSArray *)array withLastCol:(char*)lastCol andFirstCol:(char*)firstCol;

//- (NSArray*)positionInBWTwithPosInBWM:(NSArray*)posArray andFirstCol:(char*)firstColumn andLastCol:(char*)lastColumn;
//- (char*)unravelCharWithLastColumn:(char*)lastColumn firstColumn:(char*)firstColumn;//STILL NECCESSARY AT SOME POINT

//- (int)getIndexOfNth:(int)n OccurenceOfChar:(char)c inChar:(char*)container;
//- (int)whichOccurenceOfChar:(char)c inChar:(char*)container atPos:(int)pos;

//- (NSArray*)exactMatchForQuery:(char*)query withLastCol:(char*)lastCol andFirstCol:(char*)firstCol;
//- (int)LFC:(int)r andChar:(char)c withLastCol:(char*)lastCol;//The row (r) of the char (c)

- (void)setUpNumberOfOccurencesArray;
- (void)setUpBytesForIndexerAndMultipleToCountAt:(int)seqLen;//This can be modified if necessary

//- (int)whichChar:(char)c inContainer:(char*)container;

//- (int)charsBeforeChar:(char)c;

- (char*)getSortedSeq;

//APPROXI MATCH
- (int)getBestMatchForQuery:(char*)query withLastCol:(char*)lastCol andFirstCol:(char*)firstCol andNumOfSubs:(int)amtOfSubs;//returns >-1 for a match, -1 for no match, and <-1 for a rev comp match

//- (BOOL)isNotDuplicateAlignment:(NSArray*)subsArray andChunkNum:(int)chunkNum;
- (void)updatePosOccsArrayWithRange:(NSRange)range andQuery:(char*)query;
char *substr(const char *pstr, int start, int numchars);

//INSERTION/DELETION MATCH
- (NSMutableArray*)insertionDeletionMatchesForQuery:(char*)query andLastCol:(char*)lastCol andNumOfSubs:(int)numOfSubs;
- (void)recordInDel:(ED_Info*)info forLastCol:(char*)lastCol andFirstCol:(char*)firstCol;
- (void)recordInDelExactMatchForPos:(int)pos andReed:(char*)reed;
@end
