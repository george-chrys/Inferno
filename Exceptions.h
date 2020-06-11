#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


class Exceptions
{
    public:
        Exceptions();
        nameAlreadyExists(std::string x,std::string y);
        checkIfUserExists(int x,std::string y,std::string z);
        checkIfAlreadyFriends(int x,int y,std::string w,std::string z);
        requestAlreadyExists(int x, int y,std::string w,std::string z);
        checkIfRightRequest(int x, int y);
        checkIfFriendExists(int x, std::string y, std::string z);
        checkIfFriends(int x, int y, std::string w, std::string z);
    protected:

    private:
};

#endif // EXCEPTIONS_H
