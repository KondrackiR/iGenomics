//
//  FilePickerController.h
//  iGenomics
//
//  Created by Stuckinaboot Inc. on 1/4/13.
//
//

#import <UIKit/UIKit.h>
#import <dropbox/dropbox.h>

#import "ParametersController.h"

#define kTxt @"txt"

#define kDefaultRefFilesNamesFile @"NamesOfDefaultReferenceFiles"
#define kDefaultReadsFilesNamesFile @"NamesOfDefaultReadsFiles"

#define kNumOfComponentsInPickers 1

#define kComponent1Title @"Default"

#define kSavedFilesTitle @"Saved Files"
#define kSavedFilesIndex 0
#define kDropboxFilesTitle @"Dropbox Files"
#define kDropboxFilesIndex 1

#define kNumOfFilePickOptions 2

#define kExtDot '.'

@interface FilePickerController : UIViewController <UITableViewDelegate, UITableViewDataSource, UISearchBarDelegate> {
    ParametersController *parametersController;
    
    IBOutlet UITableView *referenceFilePicker;
    IBOutlet UISearchBar *refPickerSearchBar;
    IBOutlet UITableView *readsFilePicker;
    IBOutlet UISearchBar *readsPickerSearchBar;
    
    NSMutableArray *defaultRefFilesNames;
    NSMutableArray *filteredRefFileNames;
    NSMutableArray *defaultReadsFilesNames;
    NSMutableArray *filteredReadFileNames;
    
    NSMutableArray *allDropboxFiles;
    DBFilesystem *dbFileSys;
    
    int selectedOptionRef;
    int selectedRowRef;
    int selectedOptionReads;
    int selectedRowReads;
}
- (IBAction)showParametersPressed:(id)sender;
- (IBAction)backPressed:(id)sender;

- (IBAction)backRefTbl:(id)sender;
- (IBAction)backReadsTbl:(id)sender;

- (void)setUpDefaultFiles;
- (void)setUpAllDropboxFiles;

- (BOOL)folderIsNotEmptyAtPath:(DBPath*)path;//!!CURRENTLY!!: folder is not opened if it is empty, maybe a notification should be shown?

- (NSArray*)getFileNameAndExtForFullName:(NSString*)fileName;//returns array with two NSStrings, fileName and fileExt
@end
