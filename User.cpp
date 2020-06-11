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

User::User(){}

User::signupUser()
    {
        string signupFirstName, signupLastName;
        int signupPassword;
        //Ask new user for credentials of his/her choice
        cout<<"Enter first name"<<endl;
        cin>>signupFirstName;
        cout<<"Enter last name"<<endl;
        cin>>signupLastName;
        cout<<"Enter password"<<endl;
        cin>>signupPassword;
        //Check if combination of firstname & lastname already exists
        Exceptions excep1;
        excep1.nameAlreadyExists(signupFirstName,signupLastName);
        //Proceed to inserting new user's credentials to Database
        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate = 0;
        stringstream ss;

        ss <<"INSERT INTO users (firstName,lastName,password) values ('" << signupFirstName <<"','"<<signupLastName<<"',"<<signupPassword<<")";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        int onlineUserId = getUserId(signupFirstName,signupLastName);//Get new user's ID from Database
        User user1;
        user1.setStatusOnline(onlineUserId);//Set new user's status to online

        cout<<"\n!!!!!-----Congratulations! You are now a member of INFERNO!-----!!!!!\n"<<endl;
        Menu menu1;
        menu1.mainMenu(onlineUserId);
    return 0;
    }
//The loginUser method checks if the credentials given by the user are right and leads him to the main menu.
User::loginUser()
    {
        string loginFirstName, loginLastName;
        int loginPassword;
        //Ask for user to enter credentials for login
        cout<<"Enter your first name:"<<endl;
        cin>>loginFirstName;
        cout<<"Enter your last name:"<<endl;
        cin>>loginLastName;
        cout<<"Enter your password:"<<endl;
        cin>>loginPassword;

        //Connect to database
        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate;
        stringstream ss;
        //Access database to see if inserted credentials are right
        ss << "SELECT IF (COUNT(*) > 0, 1, 0) FROM users WHERE firstName = '"<<loginFirstName<<"' AND lastName = '"<<loginLastName<<"'AND password ="<<loginPassword;

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn,q);
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        string input(row[0]); //Pass query result into a string
        stringstream ss2(input);//Pass above string into stringstream
        int queryResult;
        ss2 >> queryResult;
            //User inserted wrong combination of credentials
            if(queryResult == 0)
            {
                cout<<"Sorry, wrong credentials. Try again!\n"<<endl;
                Menu menu1;
                menu1.introMenu();//If the given credentials are wrong, user is returned to start menu
            }
            //User inserted correct credentials.
            else
            {
                //Get his ID from Database
                int onlineUserId = getUserId(loginFirstName,loginLastName);
                //Set user's status online
                User user1;
                user1.setStatusOnline(onlineUserId);
                //Go to main menu
                Menu menu1;
                menu1.mainMenu(onlineUserId);
            }
        return 0;
}
User::setStatusOnline(int x)
{
        int onlineUserId = x;

        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate = 0;
        stringstream ss;
        ss <<"UPDATE users SET status = 1 WHERE id = "<<onlineUserId;
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
}
User::setStatusOffline(int x)
{
    int onlineUserId = x;

        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate = 0;
        stringstream ss;
        ss <<"UPDATE users SET status = 0 WHERE id = "<<onlineUserId;
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        cout<<"\nYou have succesfully logged out!!!\n"<<endl;
        Menu menu1;
        menu1.introMenu();
}
//The getUserId method takes user's firstname and lastname as arguments and returns his ID.
int User::getUserId(string x,string y)
{
               string FirstName = x;
               string LastName = y;

                MYSQL* conn;
                MYSQL_ROW row;
                MYSQL_RES* res;
                conn = mysql_init(0);
                conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
                int qstate;
                stringstream ss;

                ss << "SELECT id FROM users WHERE firstName ='"<<FirstName<<"' AND lastName = '"<<LastName<<"'";

                string query = ss.str();
                const char* q = query.c_str();
                qstate = mysql_query(conn,q);
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                string input(row[0]); //Pass query result into a string
                stringstream ss2(input);//Pass above string into stringstream
                int UserId;
                ss2 >> UserId;


                return UserId;
}
string User::getUserFirstname(int x)
{
    int onlineUserId = x;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss << "SELECT firstname FROM users WHERE id ="<<onlineUserId;

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string firstname(row[0]);


    return firstname;
}
string User::getUserLastname(int x)
{
    int onlineUserId = x;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
    int qstate;
    stringstream ss;

    ss << "SELECT lastname FROM users WHERE id ="<<onlineUserId;

    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn,q);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    string lastname(row[0]);


    return lastname;
}


