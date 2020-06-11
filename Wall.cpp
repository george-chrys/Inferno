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

Wall::Wall(){}
//The seeYourWall method allows the online user to see and also interact with his wall.
//Firstly, it prints on the prompt window all the existing posts on his wall
//and then asks the user to write a new message or like an already existing message.
Wall::seeYourWall(int x)
{
    int onlineUserId = x;

    User user1;
    string firstname(user1.getUserFirstname(onlineUserId)); //Get online user's firstname
    string lastname(user1.getUserLastname(onlineUserId));   //Get online user's lastname
    cout<<"\n!!!!!!!!!!!!!!!!!!!!Welcome to "<<firstname<<" "<<lastname<<"'s wall!!!!!!!!!!!!!!!!!!!!!!!\n"<<endl;

        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate;
        stringstream ss;


        ss<<"SELECT writer,postdate,likes,postid,message FROM posts WHERE wallid ="<<onlineUserId;
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn,q);
               if(!qstate)
                {
                 res = mysql_store_result(conn);
                 while(row = mysql_fetch_row(res))
                        {
                            cout<<"Sent from: "<<row[0]<<" | On: "<<row[1]<<" | Message ID: "<<row[3]<<"| Likes: "<<row[2]<<"\nMessage: "<<row[4]<<"\n"<<endl;
                        }
                }
                else
                    {
                        cout<<"command failed"<<mysql_error(conn)<<endl;
                    }

    cout<<"\nPress 1 to post a message on your wall"<<endl;
    cout<<"Press 2 to 'like' a message on your wall"<<endl;
    cout<<"Press any other number to return to main menu"<<endl;
    int userChoice;
    cin>>userChoice;

        if(userChoice == 1)
        {   string message;
            cout<<"\nType the message you want to post on your wall and then press enter"<<endl;
            std::cin.ignore();//The use of this method clears the input buffer
            std::getline(std::cin,message);//Store the message written by the user
            cout<<message<<endl;

            Wall wall1;
            wall1.postMessage(onlineUserId,onlineUserId,firstname,lastname,message);
        }
        else if (userChoice == 2)
        {
            Wall wall2;
            wall2.likePost(onlineUserId);
        }
        //If user's input is not 1 or 2 the user is returned to main menu
        else
        {
        Menu menu1;
        menu1.mainMenu(onlineUserId);
        }

    return 0;
}
//The postMessage method allows the user to post a message on his wall or a friend's wall
Wall::postMessage(int x, int b, string y, string z,string m)
{
    int onlineUserId = x;
    int friendId =b;
    string fullname = y + ' ' + z;
    string message = m;

        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate;
        stringstream ss;

        ss<<"INSERT INTO posts (wallid,writer,message) VALUES ("<<friendId<<",'"<<fullname<<"','"<<message<<"')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
               if(!qstate)
                {
                    cout<<"\nYou posted a new message on this wall!!!\n"<<endl;
                    Menu menu1;
                    menu1.mainMenu(onlineUserId);
                }
                else
                {
                    cout<<"command failed"<<mysql_error(conn)<<endl;
                }
    return 0;
}
Wall::seeFriendWall(int x,int y)
{
    int onlineUserId = x;
    int friendId = y;
    User user1;
    string firstname(user1.getUserFirstname(friendId)); //Get online user's firstname
    string lastname(user1.getUserLastname(friendId));   //Get online user's lastname
    cout<<"\n!!!!!!!!!!!!!!!!!!!!Welcome to "<<firstname<<" "<<lastname<<"'s wall!!!!!!!!!!!!!!!!!!!!!!!\n"<<endl;

        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate;
        stringstream ss;

        ss<<"SELECT writer,postdate,likes,postid,message FROM posts WHERE wallid ="<<friendId;

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn,q);
               if(!qstate)
                {
                 res = mysql_store_result(conn);
                 while(row = mysql_fetch_row(res))
                {
                cout<<"Message: "<<row[4]<<"\nSent from: "<<row[0]<<" | On: "<<row[1]<<" | Message ID: "<<row[3]<<"| Likes: "<<row[2]<<"\n"<<endl;
                }
                }
                else
                    {
                        cout<<"command failed"<<mysql_error(conn)<<endl;
                    }
    cout<<"\nPress 1 to post a message on this wall"<<endl;
    cout<<"Press 2 to 'like' a message on this wall"<<endl;
    cout<<"Press any other number to return to main menu"<<endl;
    int userChoice;
    cin>>userChoice;

        if(userChoice == 1)
        {
            string message;
            cout<<"\nType the message you want to post on this wall and then press enter"<<endl;
            std::cin.ignore();//The use of this method clears the input buffer
            std::getline(std::cin,message);//Store the message written by the user
            User user1;
            string writerFirstName(user1.getUserFirstname(onlineUserId)); //Get online user's firstname
            string writerLastName(user1.getUserLastname(onlineUserId));//Get online user's lastname
            Wall wall1;
            wall1.postMessage(onlineUserId,friendId,writerFirstName,writerLastName,message);
        }
        else if (userChoice == 2)
        {
            Wall wall2;
            wall2.likePost(onlineUserId);
        }
        else
        {
            Menu menu1;
            menu1.mainMenu(onlineUserId);
        }

    return 0;
}
Wall::likePost(int x)
{
    int onlineUserId = x;
    cout<<"Insert the message ID of the post you want to 'Like' and press enter"<<endl;
    int messageId;
    cin>>messageId;

        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate = 0;
        stringstream ss;
        ss <<"UPDATE posts SET likes =likes + 1 WHERE postid="<<messageId;
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        Menu menu1;
        menu1.mainMenu(onlineUserId);

       return 0;
}
