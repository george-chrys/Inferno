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

Exceptions::Exceptions(){}
//Method nameAlreadyExists checks if the credentials a new user inserted are already taken
//by another user and prevents him from using them again
Exceptions::nameAlreadyExists(string x,string y)
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss << "SELECT IF (COUNT(*) > 0, 1, 0) FROM users WHERE firstName = '"<<x<<"' AND lastName = '"<<y<<"'";

    string query = ss.str();const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string input(row[0]); //Pass query result into a string
    stringstream ss2(input);//Pass above string into stringstream
    int queryResult;
    ss2 >> queryResult;//Convert stringstream to integer

        if(queryResult == 1)
        {
            cout<<"User with firstnname '"<<x<<"' and lastname '"<<y<<"', already exists. Try something different!!\n"<<endl;
            User user1;
            user1.signupUser();//Credentials are already used. User is returned to sign up again.
        }
return 0;
}
Exceptions::checkIfUserExists(int x,string y,string z)
{
    int onlineUserId = x;
    string addFirstName = y;
    string addLastName = z;


    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss << "SELECT IF (COUNT(*) > 0, 1, 0) FROM users WHERE firstName = '"<<y<<"' AND lastName = '"<<z<<"'";

    string query = ss.str();const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string input(row[0]); //Pass query result into a string
    stringstream ss2(input);//Pass above string into stringstream
    int queryResult;
    ss2 >> queryResult;//Convert stringstream to integer

        if(queryResult == 0)
        {
            cout<<"User with firstnname '"<<y<<"' and lastname '"<<z<<"' does not exist"<<endl;
            Menu menu1;
            menu1.mainMenu(onlineUserId);//Request denied. Return to main menu
        }
        else if(queryResult == 1)
        {
            User user1;
            int friendID(user1.getUserId(addFirstName,addLastName));//Fetch the ID of the user that accepted the request
            Exceptions excep1;
            excep1.checkIfAlreadyFriends(onlineUserId,friendID,addFirstName,addLastName);//Go check if the two users are already friends
        }
return 0;
}
//The checkIfAlreadyFriends method checks if the online user is already friend with the user
//he wants to send a friend request
Exceptions::checkIfAlreadyFriends(int x,int y,string w, string z)
{
    int onlineUserId = x;
    int friendId = y;
    string addFirstName = w;
    string addLastName = z;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss <<"SELECT IF (COUNT(*) > 0, 1, 0) FROM friendreq WHERE reqstatus = 'accepted' AND (reqsender = "<<onlineUserId<<" AND reqreceiver ="<<friendId<<" OR reqsender ="<<friendId<<" AND reqreceiver ="<<onlineUserId<<")";

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string input(row[0]); //Pass query result into a string
    stringstream ss2(input);//Pass above string into stringstream
    int queryResult;
    ss2 >> queryResult;//Convert stringstream to integer

        if(queryResult == 1)
        {
            cout<<"\n!!!!!!!!!You are already friends with this user!!!!!!!!"<<endl;
            Menu menu1;
            menu1.mainMenu(onlineUserId);//Request denied. Return to main menu
        }
        else if(queryResult == 0)
        {
            Exceptions excep1;
            excep1.requestAlreadyExists(onlineUserId, friendId,addFirstName,addLastName);//Go check if there is already a friend request between these two users
        }
        return 0;
}
//The requestAlreadyExists method checks the daabese to see if there is already a friend request
//pending between the online user and the user he wants to send a friend request to.
Exceptions::requestAlreadyExists(int x,int y,string w,string z)
{
    int onlineUserId = x;
    int friendId = y;
    string addFirstName = w;
    string addLastName = z;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss << "SELECT IF (COUNT(*) > 0, 1, 0) FROM friendreq WHERE reqstatus = 'pending' AND (reqsender = "<<onlineUserId<<" AND reqreceiver ="<<friendId<<")OR (reqsender = "<<friendId<<" AND reqreceiver ="<<onlineUserId<<")";

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string input(row[0]); //Pass query result into a string
    stringstream ss2(input);//Pass above string into stringstream
    int queryResult;
    ss2 >> queryResult;//Convert stringstream to integer

        if(queryResult == 1)
        {
            cout<<"\n!!!!!!!!!There is already a friend request between these two users!!!!!!!!"<<endl;
            Menu menu1;
            menu1.mainMenu(onlineUserId);//Request denied. Return to main menu.
        }
        else if(queryResult == 0)
        {
            Friends friend1;
            friend1.insertIntoRequests(onlineUserId, friendId, addFirstName, addLastName);//Friend request correct. Insert request into friendreq table.
        }

return 0;
}
//The checkIfRightRequest method prevents the online user to accept a request by id which was not sent to him
Exceptions::checkIfRightRequest(int x, int y)
{
    int onlineUserId = x;
    int requestId = y;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss<< "SELECT IF (COUNT(*) > 0, 1, 0) FROM friendreq WHERE reqstatus = 'pending' AND reqreceiver ="<<onlineUserId<<" AND requestid ="<< requestId;

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string input(row[0]);
    stringstream ss2(input);
    int queryResult;
    ss2 >> queryResult;

        if(queryResult == 0)
        {
            cout<<"\n!!!!There is no friend request for you with this id!!!\n"<<endl;
            Friends friend1;
            friend1.seeFriendRequests(onlineUserId); //The user entered the wrong friend request Id. He isreturned to his friend requests list.
        }
        else if(queryResult ==1)
        {
            Friends friend1;
            friend1.manageFriendRequest(onlineUserId,requestId);//The friend request id was correct. He is now proceeded to accept or reject it.
        }

    return 0;
}
//The checkIfFriendExists method searches the database to find out if the fullname of the user's wall
//the user wants to visit exists
Exceptions::checkIfFriendExists(int x, string y, string z)
{
    int onlineUserId = x;
    string friendFirstName = y;
    string friendLastName = z;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss << "SELECT IF (COUNT(*) > 0, 1, 0) FROM users WHERE firstName = '"<<y<<"' AND lastName = '"<<z<<"'";

    string query = ss.str();const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string input(row[0]); //Pass query result into a string
    stringstream ss2(input);//Pass above string into stringstream
    int queryResult;
    ss2 >> queryResult;//Convert stringstream to integer

        if(queryResult == 0)
        {
            cout<<"User with firstnname '"<<y<<"' and lastname '"<<z<<"' does not exist"<<endl;
            Menu menu1;
            menu1.mainMenu(onlineUserId);//The requested user does not exist. The online user is returned to main menu
        }
        else if(queryResult == 1)
        {
            User user1;
            int friendId(user1.getUserId(friendFirstName,friendLastName));//The requested user exists. Fetch his ID from the database
            Exceptions excep1;
            excep1.checkIfFriends(onlineUserId,friendId,friendFirstName,friendLastName);
        }
return 0;
}
// The checkIfFriends method checks if the user whose wall the online user wants to visit is his friend.
Exceptions::checkIfFriends(int x, int y, string w, string z)
{
    int onlineUserId = x;
    int friendId = y;
    string friendFirstname = w;
    string friendLastname = z;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss << "SELECT IF (COUNT(*) > 0, 1, 0) FROM friendreq WHERE reqstatus = 'accepted' AND (reqsender = "<<onlineUserId<<" AND reqreceiver ="<<friendId<<" OR reqsender ="<<friendId<<" AND reqreceiver ="<<onlineUserId<<")";

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string input(row[0]); //Pass query result into a string
    stringstream ss2(input);//Pass above string into stringstream
    int queryResult;
    ss2 >> queryResult;//Convert stringstream to integer

        if(queryResult == 0)
        {
            cout<<"\n!!!!!!!!!You are not friends with this user!!!!!!!!"<<endl;
            Menu menu1;
            menu1.mainMenu(onlineUserId);//These two users are not friends. Online user is returned to main menu
        }
        else if(queryResult == 1)
        {
            Wall wall3;
            wall3.seeFriendWall(onlineUserId,friendId);//The two users are friends.  The online user gets to visit the requested wall
        }
        return 0;
}
