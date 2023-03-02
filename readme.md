# CSCI 2275 MiniGit Project (A mini version control system)

Author/Creator: Eric Fithian

This is a version control system. The goal of this program is to create a way to manage changes to a set of documents, typically containing computer programs, documents, websites, or other collections of information.

# Core Functionality:
1. Initialize a new repository
2. Add files to a commit
3. Remove files from a commit
4. Commit changes
5. Search past commits based on a key word
6. Checkout past commits based on commit number




# How to run/use:
1. Clone this repository
2. Change directory to the /build directory
3. Run 'cmake ..'
4. Run 'make'
5. Run './run_app_1'
   - Here you will be presented with eight program options in the terminal
   - You will follow the instructions as asked by the terminal print statements
6. Once you are done using the program you can quit using option '8'
   - CAUTION: Once you quit the program, none of the previous commits will be saved if you relaunch the app




# Use Conditions (8 seperate functions):
1. init
   - This will initialize a new repository for saving your commits
   - You must run this before any other operations can be performed. 
2. add
   - This function adds a new file to the current commit
   - The file being added must
      1) Already be created
      2) Be inside the /build directory
      3) Be either a .txt .cpp or .hpp file
3. rm
   - This function removes a file from the current commit
   - The file being removed must already be added to the commit or a previous commit
4. commit
   - This function commits the current changes to the repository
   - Will only commit changes that have been added through the add function
   - Or changes that have been made through the remove function
   - This will also ask for a commit message, which you can later use to find past commits
5. checkout
   - This function reverts changes back to previous commits
   - Requires a valid commit ID
   - Use the 'search' function or the 'print current structure' function to find previous commit ID's
   - IMPORTANT: Changes cannot be made unless the most recent 'uncommited' commit is checked out
6. search
   - This function requires a key word and returns the commit ID's of commit's with commit messages containing that keyword
7. print current structure
   - This function is mainly used for debugging and development
   - It will print
      1) The current commit and its singly linked list of files
      2) All commits that have been made with their respective sinly linked list of files
      3) The hash table containing the key words of each commit message as well as which commit ID's contain that key word
8. quit
   - This function will exit the program
   - All previous commits will be lost
   - Program will close and all data structures will be discarded



