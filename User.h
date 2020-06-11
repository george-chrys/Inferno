#ifndef USER_H
#define USER_H


class User
{
    public:
        User();

        signupUser();
        loginUser();



        setStatusOnline(int x);
        setStatusOffline(int x);
        std::string getUserFirstname(int x);
        std::string getUserLastname(int x);
        getUserId(std::string x,std::string y);

    protected:

    private:




};

#endif // USER_H
