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
//User user1;


Admin::Admin()
{

}


Admin::adminMenu()
    {
        cout<<"\nWhat do you command master?\n"<<endl;
        cout<<"1. See the users."<<endl;
        cout<<"2. Create new user."<<endl;
        cout<<"3. Delete a user."<<endl;
        cout<<"4. See who is online"<<endl;
        cout<<"0. Exit to main menu."<<endl;

        int adminChoice;
        cin >>adminChoice;
            if(adminChoice == 0)
            {
                Menu menu1;
                menu1.introMenu();
            }
            if(adminChoice == 1)
            {
                 Admin admin1;
                 admin1.adminSeeUsers();
                 admin1.adminMenu();
            }

            if(adminChoice == 2)
            {
                Admin admin1;
                admin1.adminAddUser();
                admin1.adminMenu();
            }
            if(adminChoice == 3)
            {
                Admin admin1;
                admin1.adminDeleteUser();
                admin1.adminMenu();
            }
            if(adminChoice == 4)
            {
                Admin admin1;
                admin1.adminMenu();
            }
    return 0;
    }
Admin::adminSeeUsers()
    {
        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);
        int qstate;

        string query = "SELECT * FROM users";
        const char* q = query.c_str();
        qstate = mysql_query(conn,q);
               if(!qstate)
                {
                 res = mysql_store_result(conn);
                 cout<<"ID"<<"  "<<"FIRSTNAME"<<"       "<<"LASTNAME"<<"      "<<"PASSWORD"<<endl;
                        while(row = mysql_fetch_row(res))
                        {
                            cout<<row[0]<<"   "<<row[1]<<"       "<<row[2]<<"      "<<row[3]<<endl;
                        }
                }
                else
                    {
                        cout<<"command failed"<<mysql_error(conn)<<endl;
                    }
                    return 0;
    }
Admin::adminAddUser()
    {
        cout<<"Enter first name"<<endl;
        string first_name;
        cin>>first_name;
        cout<<"Enter last name"<<endl;
        string last_name;
        cin>>last_name;
        cout<<"Enter password"<<endl;
        int password;
        cin>>password;

        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);

        int qstate = 0;
        stringstream ss;
        ss <<"INSERT INTO users (firstName,lastName,password) values ('" << first_name <<"','"<<last_name <<"',"<<password<<")";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
    return 0;
    }
Admin::adminDeleteUser()
    {
        cout<<"Insert the id of the user you want to delete:"<<endl;
        int deleteId;
        cin>>deleteId;

        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","","infernoDB", 0, NULL, 0);

        int qstate = 0;
        stringstream ss;
        ss <<"DELETE FROM users WHERE id =" <<deleteId ;
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        cout<<"          "<<"!!!!!User deleted!!!!!"<<endl;

    return 0;
    }

