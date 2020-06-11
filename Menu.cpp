#include <iostream>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include "Admin.h"
#include "Menu.h"
#include "User.h"
#include "Friends.h"
#include "Exceptions.h"
#include "Wall.h"
using namespace std;

User user1;
Friends friend1;

Menu::Menu(){}

Menu::introMenu()
{
    cout<<"----------WELCOME TO INFERNO!!!----------"<<endl;
    cout<<"\nAre you new in Inferno? Then enter '1' to signup."<<endl;
    cout<<"Are you already a member? Then enter '2' to log in."<<endl;
    cout<<"Wanna leave? Then enter '0' to exit."<<endl;
    int userChoice = NULL;
    cin >>userChoice;
        if(userChoice == -1)
            {
             Admin admin1;
             admin1.adminMenu();
            }
        else if(userChoice == 0)
            {
                cout<<"\n!!!!!!!!!!!!!!!!!See ya!!!!!!!!!!!!!!!!!"<<endl;
                return 0;
            }
        else if(userChoice == 1)
            {
             user1.signupUser();
            }
        else if(userChoice == 2)
            {
            user1.loginUser();
            }
        else
            {
            cout<<"Sorry, no valid input. Try again\n"<<endl;
            introMenu();
            }
return 0;
}
Menu::mainMenu(int x)
{

    int userChoice = NULL;
    int onlineUserId = x;

                cout<<"\nWhat would you like to do?\n"<<endl;
                cout<<"1. See your wall"<<endl;
                cout<<"2. See friends wall"<<endl;
                cout<<"3. Send friend request"<<endl;
                cout<<"4. Accept/Reject friend request"<<endl;
                cout<<"5. See my friends"<<endl;
                cout<<"6. Log out"<<endl;
                cout<<"7. Exit INFERNO"<<endl;
                cin>>userChoice;
                    if(userChoice == -1)
                    {Admin admin1;
                    admin1.adminMenu();
                    }
                    else if(userChoice == 1)
                    {
                        Wall wall1;
                        wall1.seeYourWall(onlineUserId);
                    }
                    else if(userChoice == 2)
                    {
                        cout<<"Type firstname of the friend you want to visit"<<endl;
                        string friendFirstName;
                        cin>>friendFirstName;
                        cout<<"Type lastname of the friend you want to visit"<<endl;
                        string friendLastName;
                        cin>>friendLastName;

                        Exceptions excep1;
                        excep1.checkIfFriendExists(onlineUserId, friendFirstName, friendLastName);

                    }
                    else if(userChoice == 3)
                    {
                    friend1.sendFriendRequest(onlineUserId);
                    }
                    else if(userChoice == 4)
                    {
                    friend1.seeFriendRequests(onlineUserId);
                    }
                    else if(userChoice == 5)
                    {
                     friend1.seeFriends(onlineUserId);
                    }
                    else if(userChoice == 6)
                    {
                    user1.setStatusOffline(onlineUserId);
                    }
                    else if(userChoice == 7)
                    {
                     return 0;
                    }
                    else
                    {

                    }

return 0;
}
