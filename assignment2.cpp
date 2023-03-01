#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "assignment1_261002509.h"

using namespace std;

// typedef struct File {
//     string data;
//     File* next;
// } File;

// File* createFile(string data, File* next){
//     File* newFile = new File(data,next);
//     return newFile;
// }

// class File {
//     public:
//         ifstream data;
//         File* next;

//         File(){
//             this->data;
//             this->next = nullptr;
//         }
        
//         File(ifstream data) {
//             this->data = data;
//             this->next = nullptr;
//         }
// };

// class git322 {
//     public:
//         File head;
//         File prev;
        
//         git322() {
//             this->head = File();
//             this->prev = File();
//         }
        
//         void add(File file) {
//             if(head.data.empty()){
//                 this->head = file;
//                 this->prev = file;

//             } else if(enhanced_file_diff(prev.data, file.data)){
//                 cout << "git322 did not detect any change to your file and will not create a new version." << endl;
//                 return;
//             } else {

//             }
//         }
// };
int versionNum = 0;
class File {
    public:
        string data;
        File* next;
        int vNum;

        File(){
            vNum = versionNum += 1;
            this->data;
            this->next = nullptr;
        }
        
        File(string data) {
            vNum = versionNum += 1;
            this->data = data;
            this->next = nullptr;
        }
};

class git322 {
    public:
        File *head;
        File *tail;
        File *prev;
        ifstream in_file;
        string fileName;
        // ofstream out_file;
        int no;

        git322(){
            no = 0;
            this->head = new File();
            this->prev = new File();
            this->tail = new File();
            versionNum -= 3;
        }

        git322(string filename){
            no = 0;
            this->head = new File();
            this->prev = new File();
            this->tail = new File();
            in_file.open(filename);
            fileName = filename;
            // out_file.open(filename);
            versionNum -= 3;
        }

        void print(){
            File *curr = this->head;
            cout << "Number of versions: " << no << endl;

            while(curr != nullptr){
                cout << "Version number: " << curr->vNum << endl
                << "Hash Value: " << hash_it(curr->data) << endl
                << "Content: " << curr->data << "\n" << endl;

                curr = curr->next;
            }
            
        }
        
        void add(string content) {
            if(head->data.empty()){
                File *newFile = new File(content);
                this->head = newFile;
                this->prev = newFile;
                this->tail = newFile;
                cout << "Your content has been added successfully." << endl;
                return;

            } else if(hash_it(content) == hash_it(tail->data)) {
                cout << "git322 did not detect any change to your file and will not create a new version." << endl;
                return;

            } else {
                File *newFile = new File(content);
                this->no += 1;
                this->tail->next = newFile;
                this->tail = newFile;
                cout << "Your content has been added successfully." << endl;
                return;
            }
                
        }

        void load(int version){
            if(version > no){
                cout << "Please enter a valid version number. If you are not sure please press " <<
                "'p' to list all valid version numbers." << endl;
                return;
            }

            File *curr = this->head;

            while(curr != nullptr){
                if(curr->vNum == version){
                    ofstream out_file(this->fileName);
                    out_file << curr->data;

                    this->no += 1;
                    this->tail->next = curr;
                    this->tail = curr;

                    return;
                }
                curr = curr->next;
            }

            return;
        }

        void compare(int version1, int version2){
            cout << "in compare" << endl;
        }

};

string feed(string filename) {
    ifstream file(filename);
    string content;
    
    if(file) {
      ostringstream buffer;
      buffer << file.rdbuf(); // reading data
      content = buffer.str();
    }

    file.close();

   return content;
}

int main(){
    char l;
    
    cout << "Welcome to the Comp322 file versioning system!" << endl;
    cout << "To add the content of your file to version control press 'a'" << endl;
    cout << "To remove a version press 'r'" << endl;
    cout << "To load a version press 'l'" << endl;
    cout << "To print to the screen the detailed list of all versions press 'p'" << endl;
    cout << "To compare any 2 versions press 'c'" << endl;
    cout << "To search versions for a keyword press 's'" << endl;
    cout << "To exit press 'e'" << endl;

    string fileString = "./file.txt";

    string content;

    content = feed("./file.txt");
    git322 vcs(fileString); //version control system
    
    while(l != 'e'){
        content = feed("./file.txt");
        cin >> l;
        if(l == 'a'){
            cout << "in a" << endl;
            content = feed("./file.txt");
            vcs.add(content);
        }

        if(l == 'r'){
            
        }

        if(l == 'l'){
            int v;
            cout << "Which version would you like to load?" << endl;
            cin >> v;
            vcs.load(v);
        }

        if(l == 'p'){
            vcs.print();
            
        }

        if(l == 'c'){
            int v1;
            int v2;

            cout << "Please enter the number of the first version to compare:" << endl;
            cin >> v1;

            cout << "Please enter the number of the second version to compare:" << endl;
            cin >> v2;
        }

        if(l == 's'){
            
        }

        if(l == 'e'){
            cout << "Bye!" << endl;
            break;
        }
    }
    
    return 0;

}