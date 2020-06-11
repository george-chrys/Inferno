#ifndef FRIENDS_H
#define FRIENDS_H


class Friends
{
    public:
        Friends();

        seeFriends(int x);
        sendFriendRequest(int x);
        seeFriendRequests(int x);
        insertIntoRequests(int x, int y, std::string w, std::string z);
        manageFriendRequest(int x,int y);
        acceptFriendRequest(int x);
        rejectFriendRequest(int x);

    protected:

    private:
};

#endif // FRIENDS_H
