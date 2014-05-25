/******************************************************
** Author: Jason Dorweiler
** Date: 10-25-13
** Description: CS165 lab 9
** Input: ./movies to run. Then follow the prompts
** Output:
**************************
       Movie Database
**************************
Do you want to enter your own movies or load the top 5 most popular movies?
[1] Enter My Own
[0] Load Popular
0

List of Movies:
[1]The Shawshank Redemption
[2]The Godfather
[3]The Godfather pt2
[4]Pulp fiction
[5]The Good, the Bad and the Ugly

What would you like to do next?
[1] search by genre
[2] show movie descriptions
[3] rent a movie
[4] show avaliable movie titles
[0] QUIT
3

List of Movies:
[1]The Shawshank Redemption
[2]The Godfather
[3]The Godfather pt2
[4]Pulp fiction
[5]The Good, the Bad and the Ugly
What movie do you want to rent? enter number
3

You just rented The Godfather pt2
Copies remaining: 0


What would you like to do next?
[1] search by genre
[2] show movie descriptions
[3] rent a movie
[4] show avaliable movie titles
[0] QUIT
4

List of Movies:
[1]The Shawshank Redemption
[2]The Godfather
[4]Pulp fiction
[5]The Good, the Bad and the Ugly
*******************************************************/
#include <iostream>
#include <cstdlib>
#include <limits.h>

#define NUM_MOVIES 5 // we are only using 5 movies to make things easier

using namespace std;

// struct that holds the data for each movie
struct movies_collection{
    string title;
    int copies;
    float rating;
    string description;
    string genre;
};

void set_movies(movies_collection &movies, string title, int copies, string genre, string description, int rating); // loads data into the movie_collection struct
void set_user(movies_collection *movies); // this asks the user if they want to load the default or enter their own movies
void which_movie_to_view(movies_collection *movies, string output, string type); // gets user input and passes it to get_movie
void get_movies(movies_collection *movies, string choice, string type); // prints out data about a movie based on the string type that is sent to it
void get_movie_info(movies_collection *movies); // prints a list of all avaliable movies
void rent_movie(movies_collection *movies); // decreases the number of copies of a movie
void clearCin(); // clear the cin buffer
int errorCheck(int low, int high, int n); //error check on integer inputs

int main(int argc, char *argv[]){
    int repeat = 1;
    int user_choice;

    // declare array of structs
    movies_collection movies[5];

    cout << "**************************" << endl;
    cout << "       Movie Database     " << endl;
    cout << "**************************" << endl;

    // ask if the user want to enter their own or use the default movies
    set_user(movies);

    // print out the list of movies
    get_movie_info(movies);

    while(repeat){

        // ask the user what they want to do.. search the movies or rent
        cout << endl;
        cout << "What would you like to do next?" << endl;
        cout << "[1] search by genre" << endl;
        cout << "[2] show movie descriptions" << endl;
        cout << "[3] rent a movie" << endl;
        cout << "[4] show avaliable movie titles" << endl;
        cout << "[0] QUIT" << endl;
        cin >> user_choice;
        user_choice = errorCheck(0,4, user_choice);
        if(user_choice == 1){ // search by genre
            which_movie_to_view(movies, "What genre do you want to see? (drama, crime or action)... ", "genre");
        }

        if(user_choice == 2){ // show descriptions
            get_movie_info(movies);
            get_movies(movies,"","description");
        }

        if(user_choice == 3){ // rent a movie
            get_movie_info(movies);
            rent_movie(movies);
        }

        if(user_choice == 4){ // show all titles
            get_movie_info(movies);
        }

        if(user_choice == 0){ // quit
            return 0;
        }
    }
return 0;
}

void rent_movie(movies_collection *movies){
    /*
    This asks the user what movie they would like to rent and
    decreases the number of copies of that movie by one.
    */
    cout << "What movie do you want to rent? enter number " ;
    cout << endl;
    int selection;
    cin >> selection;
    selection = errorCheck(1, 5, selection);
    if(selection !=0){
        movies[selection-1].copies -= 1;
        cout << endl;
        cout << "You just rented " << movies[selection-1].title << endl;
        cout << "Copies remaining: " << movies[selection-1].copies << endl;
        cout << endl;
    }
}

void get_movie_info(movies_collection *movies){
    /*
    This prints out a formatted list of all the movie titles
    */
    cout << endl;
    cout << "List of Movies: " << endl;
    for(int i = 0; i < NUM_MOVIES; i++){
        if(movies[i].copies != 0){
            cout << "[" << i+1 << "]" << movies[i].title << endl;
        }
    }
clearCin();
}

void which_movie_to_view(movies_collection *movies, string output, string type){
    /*
    Takes in a output string and prints that back to the user.  Get input from the user
    based on what type of search they want to do.  Pass the value of the search type
    on to the get_movies function
    */
    string user_choice;
    cout << output;
    clearCin();
    getline(cin, user_choice);
    get_movies(movies, user_choice, type);
}

void get_movies(movies_collection *movies, string choice, string type){
    /*
    check s the string type and choice and prints out data for each movie
    based on those strings
    */
    cout << endl;

    // print out the movie descriptions.  Ask the user what movie they want to see
    // or print all movies
    if(type == "description"){
        cout << "What movie would you like to see more info about? enter number or type [0] to see all movies" << endl;
        int selection;
        cin >> selection;
        selection = errorCheck(0, 5, selection);
        cout << endl;

        // print all movies
        if(selection == 0){
            for(int i = 0; i < NUM_MOVIES; i++){
                    if( movies[i].copies != 0){
                    cout << "************************************************************" << endl;
                    cout << "Movie #" << i+1 << endl;
                    cout << endl;
                    cout << movies[i].title << endl;
                    cout << movies[i].description << endl;
                    cout << "Rating: " << movies[i].rating << endl;
                    cout << "No. Copies: " << movies[i].copies << endl;
                    cout << "************************************************************" << endl;
                }
            }
        }
        else{ // print out just the one movie that the user wants to see
            cout << movies[selection-1].title << endl;
            cout << movies[selection-1].description << endl;
            cout << endl;
        }
    }

    // search all movies by genre and print out matching results
    for(int i = 0; i < NUM_MOVIES; i++){
        if(type == "genre"){
            //cout << "IN TYPE " << choice << endl;
            if(movies[i].genre == choice){
                //cout << "IN CHOICE" << endl;
                cout << movies[i].title << endl;
            }
        }
    }
}

void set_user(movies_collection *movies){
    /*
    This function asks the user if they want to enter their own movies into the database
    or if they want to load the default movies.
    */
    int choice = 0;
    string title;
    string description;
    string genre;
    float rating;
    int copies;

    // get user's choice
    cout << "Do you want to enter your own movies or load the top 5 most popular movies?" << endl;
    cout << "[1] Enter My Own" << endl;
    cout << "[0] Load Popular " << endl;
    cin >> choice;
    choice = errorCheck(0,1,choice);
    // the user will enter their own movies.  Get the data from the user and
    // store in the movies struct
    if(choice == 1){
        for(int i = 0; i < NUM_MOVIES; i++){

            cout << " You are entering data for movie #" << i+1 << endl;
            cout <<"Enter the title" << endl;
            getline(cin, title);
            clearCin();
            movies[i].title = title;

            cout <<"Enter the number of copies" << endl;
            cin >> copies;
            clearCin();
            movies[i].copies = copies;

            cout << "Enter the description " << endl;
            getline(cin, description);
            clearCin();
            movies[i].description = description;

            cout << "Enter the genre " << endl;
            getline(cin, genre);
            clearCin();
            movies[i].genre = genre;

            cout << "Enter the rating (1-10)" << endl;
            cin >> rating;
            clearCin();
            movies[i].rating = rating;
        }
    }

    // load the default movies
    if(choice == 0){
        set_movies(movies[0], "The Shawshank Redemption", 2, "crime", "Two imprisoned men bond over a number of years, finding solace and eventual redemption through acts of common decency.", 9.3);
        set_movies(movies[1], "The Godfather", 3, "crime", "The aging patriarch of an organized crime dynasty transfers control of his clandestine empire to his reluctant son.", 9.2);
        set_movies(movies[2], "The Godfather pt2", 1, "action", "The early life and career of Vito Corleone in 1920s New York is portrayed while his son, Michael, expands and tightens his grip on his crime syndicate stretching from Lake Tahoe, Nevada to pre-revolution 1958 Cuba.", 9.0);
        set_movies(movies[3], "Pulp fiction", 2, "drama", "The lives of two mob hit men, a boxer, a gangster's wife, and a pair of diner bandits intertwine in four tales of violence and redemption", 9.0);
        set_movies(movies[4], "The Good, the Bad and the Ugly", 1, "drama", "A bounty hunting scam joins two men in an uneasy alliance against a third in a race to find a fortune in gold buried in a remote cemetery.", 9.0);
    }
}

void set_movies(movies_collection &movies, string title, int copies, string genre, string description, int rating){
    /*
    This is a function used to easily load data into the movies struct
    */
    movies.title = title;
    movies.copies = copies;
    movies.genre = genre;
    movies.description = description;
    movies.rating = rating;
}

void clearCin(){
    // clear the input buffer
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

int errorCheck(int low, int high, int n){
    while(n < low || n > high || !cin){
    cout << "Please enter a number from " << low << " to " << high << endl;
    clearCin();
    cin >> n;
    }
return n;
}
