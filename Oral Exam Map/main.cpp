#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<cstring>


using namespace std;

int main(){

    ifstream file;
    file.open("student8_DataFile.txt");

    //create a vector of vector of string
    vector<vector<string>> flavors;
    map<string,int> map;

    //string to save the header of the file. i.e. first line of the file
    
    string header;
    getline(file,header);
    string flavorText; 
  while(!file.eof()) {
  
    getline(file,flavorText);

        //create a new char array to store the readed line for spliting
        char *tempString = new char [flavorText.length()];

        //copy the readed line to this char array
        strcpy(tempString,flavorText.c_str());

        //split the char array by space
        char *counter = strtok(tempString," ");

        //make a vector to store all the flavour of a single line
        vector<string> temp;

        //iteratevely split the line
        while(counter != 0){

            //add this to the temp
            temp.push_back(counter);

            //check if it is already present on the map or no
            //for counting purpose
            if(map.find(counter) ==map.end()){

                //if not found on the map just add it
                map[counter] = 1;
            }
            else
            {

                //if found increament its value
               map[counter]++;
            }
          // split the string
          counter = strtok(NULL," ");
        }

        //delete the dynamically allocated arrray
        // delete[] cstr;

        //push this vector to the flavour object
        flavors.push_back(temp);
      }
    

    //close the file
    file.close();


  cout << header << endl;
    //print all the readed data from the files
    
    for(int i=0;i<flavors.size();i++){
        for(int j=0;j<flavors[i].size();j++){
            cout << flavors[i][j] <<" ";
        }
        cout<<endl;
    }

    //print how many times chocolate was favourite
   cout << endl;
    cout<<"Chocolate: "<<map["Chocolate"]<<endl;

    //print all different flavours
    cout << endl << "Total different flavours: "<<map.size()<< endl;
    for(auto x : map){
        cout << x.first << endl;
    }
    cout << endl << endl;

     
  }
