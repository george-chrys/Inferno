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

Friends::Friends(){}
//The seeFriends method prints the list of the online user's friends
Friends::seeFriends(int x)
{
    int onlineUserId = x;

    cout<<"\nThis is your friendlist\n"<<endl;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss<< "SELECT firstName,lastName FROM friendreq join users ON id = reqsender WHERE reqstatus = 'accepted' AND reqreceiver = "<<onlineUserId<<" UNION SELECT firstName,lastName FROM friendreq join users ON id = reqreceiver WHERE reqstatus = 'accepted' AND reqsender ="<<onlineUserId;

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);

    while(row = mysql_fetch_row(res))
        {
            cout<<row[0]<<"   "<<row[1]<<endl;
        }
        Menu menu1;
        menu1.mainMenu(onlineUserId);
    return 0;
}
Friends::sendFriendRequest(int x)
{
    int onlineUserId = x;
    string addFirstName;
    string addLastName;

    cout<<"Write the first name of the user you want to add:"<<endl;
    cin>>addFirstName;
    cout<<"Write the last name of the user you want to add:"<<endl;
    cin>>addLastName;

    Exceptions excep1;
    excep1.checkIfUserExists(onlineUserId,addFirstName,addLastName);

    return 0;
}
//The seeFriendRequests prints all the friend requests that are sent to the online user and are still pending.
Friends::seeFriendRequests(int x)
{
    int onlineUserId = x;

        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate;
        stringstream ss;

        ss<<"SELECT requestid,firstName,lastName FROM friendreq join users ON id = reqsender WHERE reqstatus = 'Pending' AND reqreceiver = "<<onlineUserId;

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn,q);
        res = mysql_store_result(conn);
        cout<<"You have friend requests from:\n"<<endl;
                while(row = mysql_fetch_row(res))
                        {
                            cout<<row[0]<<"   "<<row[1]<<"   "<<row[2]<<endl;

                        }
       cout<<"Choose a friend request by number"<<endl;
       int friendReqNum;
       cin>>friendReqNum;

        Exceptions excep1;
        excep1.checkIfRightRequest(onlineUserId,friendReqNum);

        return 0;

}
Friends::insertIntoRequests(int x, int y, string w, string z)
{
    int onlineUserId = x;
    int requestedUserid = y;

    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate = 0;
    stringstream ss;
    ss <<"INSERT INTO friendreq (reqsender,reqreceiver) VALUES ("<<onlineUserId<<","<<requestedUserid<<")";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);

    cout<<"\n!!!!!!!!!!!!You just sent a friend request to "<<w<<" "<<z<<"!!!!!!!!!!!!!!"<<endl;

     Menu menu1;
    menu1.mainMenu(onlineUserId);

    return 0;
}
//This method allows the user to proceed to accepting or rejecting a friend request that was send to him
Friends::manageFriendRequest(int x,int y)
{
    int onlineUserId =x;
    int requestId =y;

    cout<<" 1. Accept request"<<endl;
    cout<<" 2. Reject request"<<endl;
    int userChoice;
    cin>>userChoice;


        if(userChoice == 1)
            {
                Friends friend1;
                friend1.acceptFriendRequest(requestId);
            }
        else if(userChoice == 2)
            {
                Friends friend1;
                friend1.rejectFriendRequest(requestId);
            }
        else
            {
                cout<<"\n!!!!!!Invalid choice!!!!!!"<<endl;
            }
        Menu menu1;
        menu1.mainMenu(onlineUserId);
}
Friends::acceptFriendRequest(int x)
{
    int requestId = x;

    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate = 0;
    stringstream ss;
    ss <<"UPDATE friendreq SET reqstatus = 'accepted' WHERE requestid = "<<requestId;
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);

    cout<<"!!!!!!!!!You accepted the friend request!!!!!!!!!"<<endl;

    return 0;
}
Friends::rejectFriendRequest(int x)
{
    int requestId = x;

    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate = 0;
    stringstream ss;
    ss <<"UPDATE friendreq SET reqstatus = 'rejected' WHERE requestid = "<<requestId;
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);

    cout<<"!!!!!!!!!You rejected the friend request!!!!!!!!!"<<endl;

    return 0;
}
