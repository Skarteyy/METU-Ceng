#include "UserDatabase.h"
#include <stack>
// IMPLEMENT THESE
UserDatabase::UserDatabase()
{
	_load_factor = 0.75;
	_size = 0;
	_userTable.resize(11,NULL);
	_dummy = new UserNode("");
}

UserDatabase::UserDatabase(size_t s, double load)
{
	_load_factor = load;
	_size = 0;
	_userTable.resize(s,NULL);
	_dummy = new UserNode("");
}

UserDatabase::~UserDatabase()
{
    for (size_t i = 0; i < capacity(); i++) {
        if (_userTable[i] && _userTable[i] != _dummy) {
            delete _userTable[i];
        }
    }

	if(_dummy) delete _dummy;
}

size_t UserDatabase::size() const
{
	return _size;
}

size_t UserDatabase::capacity() const
{
	return _userTable.size();
}

bool UserDatabase::isEmpty() const
{
	return _size == 0;
}

void UserDatabase::addUser(string username) {
    if (userExists(username)) 
        throw UsernameTakenException(username);
    UserNode* node = new UserNode(username);
    _size++;
    _load_factor = (double)_size / capacity();
	if (_load_factor >= 0.7){
	    resize(2*_userTable.size() + 1);
	} 
	hash(node);
}

void UserDatabase::removeUser(string username)
{
    vector<string> v = getUserList();
    for (size_t i = 0; i < v.size(); i++){
        if (userFollows(v[i], username)){
            unfollow(v[i], username);
        }
    }
    size_t hashCode = hashFunction(username, capacity());
	while(_userTable[hashCode] != NULL){
	    if (_userTable[hashCode]->username == username){
	        delete _userTable[hashCode];
	        _userTable[hashCode] = _dummy;
	        _size --;
	        return;
	    }
	    hashCode = (hashCode + 1)%capacity();
	}
	
	throw UserDoesNotExistException(username);
}

UserNode* UserDatabase::getUser(string username) const
{
    size_t hashCode = hashFunction(username, capacity());
	while(_userTable[hashCode] != NULL){
	    if (_userTable[hashCode]->username == username)
	        return _userTable[hashCode];
	    hashCode = (hashCode + 1)%capacity();
	}
	
	throw UserDoesNotExistException(username);
}

void UserDatabase::resize(size_t size)
{
	vector<UserNode*> temp = _userTable; 
    for (int i = 0; i < _userTable.size(); i++){
        _userTable[i] = NULL;
    }
    _userTable.resize(size);
    
    for (int i = 0; i < temp.size(); i++){
        if (temp[i]){
            hash(temp[i]);
        }
    }
}

void UserDatabase::follow(string username1, string username2)
{
	UserNode *user1 = getUser(username1);
	UserNode *user2 = getUser(username2);
	
	if (userFollows(username1, username2)){
	    throw RedundantActionException(username1, username2, true);
	} else
	    user1->follows.push_back(username2);
}

void UserDatabase::unfollow(string username1, string username2)
{
	UserNode *user1 = getUser(username1);
	UserNode *user2 = getUser(username2);
	size_t i;
	if (!userFollows(username1, username2)){
	    throw RedundantActionException(username1, username2, false);
	    return;
	}
	for (i = 0; i < user1->follows.size(); i++){
	    if (user1->follows[i] == username2) break;
	}
	user1->follows.erase(user1->follows.begin() + i);
}


bool UserDatabase::userExists(string username) const
{
	size_t hashCode = hashFunction(username, capacity());
	while (_userTable[hashCode] != NULL){
	    if (_userTable[hashCode]->username == username)
	        return true;
        hashCode = (hashCode + 1) % capacity();
    }
	return false;
}

bool UserDatabase::userFollows(string username1, string username2) const
{
	UserNode *user1 = getUser(username1);
	UserNode *user2 = getUser(username2);
	for (int i = 0; i < user1->follows.size(); i++){
	    if (username2 == user1->follows[i]) return true;
	}
	return false;
}

size_t UserDatabase::userFollowerCount(string username) const
{
    size_t count = 0;
    for (size_t i = 0; i < capacity(); i++){
        if (_userTable[i] && _userTable[i] != _dummy){
            if (userFollows(_userTable[i]->username, username)){
                count++;
            }
        }
    }
	return count;
}

size_t UserDatabase::userFollowsCount(string username) const
{
	UserNode* user = getUser(username);
	return user->follows.size();
}

vector<string> UserDatabase::getUserList() const
{
    vector<string> v;
	for (size_t i = 0; i < capacity(); i++){
	    if (_userTable[i] && _userTable[i] != _dummy){
            v.push_back(_userTable[i]->username);
        }
	}
	return v;
}

void UserDatabase::printAdjacencyMatrix() const
{
	vector<string> v = getUserList();
	for (size_t i = 0; i < v.size(); i++){
	    for (size_t j = 0; j < v.size(); j++){
	        if (userFollows(v[i], v[j])){
	            cout << 1 << " ";
	        } else {
	            cout << 0 << " ";
	        }
	    }
	    cout << endl;
	}
}

int UserDatabase::BFS(string username1, string username2, bool printPath)
{
	UserNode *user1 = getUser(username1);
	UserNode *user2 = getUser(username2);
	
	vector<string> userList = getUserList();
	vector<int> distance(userList.size(), -1);

	int user1index = findUserIndex(username1);
	int user2index = findUserIndex(username2);
	
	distance[user1index] = 0;
	queue<int> q;
	q.push(user1index);
	
	while (!q.empty()){
	    int currIndex = q.front();
        q.pop();
        
        UserNode* curr = getUser(userList[currIndex]);
        
        if (printPath){
            cout << curr->username << " ";
        }
        
        if (currIndex == user2index){
            if (printPath) cout << endl;
            return distance[currIndex];
        }
        
        for (int i = 0; i < curr->follows.size(); i++){
            string follows = curr->follows[i];
            int followIndex = findUserIndex(follows);
            if (distance[followIndex] == -1){
                distance[followIndex] = distance[currIndex] + 1;
                q.push(followIndex);
            }
        }
	}
	if (printPath) cout << endl;
	return -1;
}

int UserDatabase::DFS(string username1, string username2, bool printPath)
{ 
	UserNode *user1 = getUser(username1);
	UserNode *user2 = getUser(username2);
	
	vector<string> userList = getUserList();
	vector<int> distance(userList.size(), -1);
	vector<bool> visited(userList.size(), false);
	
	int user1index = findUserIndex(username1);
	int user2index = findUserIndex(username2);
	
	distance[user1index] = 0;
	std::stack<int> s;
	s.push(user1index);
	
	while(!s.empty()){
	    int currIndex = s.top();
        s.pop();
        if (visited[currIndex]) continue;
        
        UserNode* curr = getUser(userList[currIndex]);
       
        if (printPath){
            cout << curr->username << " ";
        }
        
        if (currIndex == user2index){
            if (printPath) cout << endl;
            return distance[currIndex];
        }
        visited[currIndex] = true;
        
        for (int i = curr->follows.size() - 1; i >= 0; i--){
            string follows = curr->follows[i];
            int followIndex = findUserIndex(follows);
            distance[followIndex] = distance[currIndex] + 1;
            s.push(followIndex);
        }
        
	}
	if (printPath) cout << endl;
	return -1;
}

double UserDatabase::averageBFS()
{
	vector<string> userList = getUserList();
	double total = 0;
	int count = 0;
	for (int i = 0; i < userList.size(); i++){
	    for (int j = 0; j < userList.size(); j++){
	        if (i == j) continue;
	        int distance = BFS(userList[i], userList[j], false);
	        if (distance != -1) {
	            total += distance;
	            count++;
	        } 
	    }
	}
	if (count > 0)
	    return total / count;
	else 
	    return 0;
}

double UserDatabase::averageDFS()
{
	vector<string> userList = getUserList();
	double total = 0;
	int count = 0;
	for (int i = 0; i < userList.size(); i++){
	    for (int j = 0; j < userList.size(); j++){
	        if (i == j) continue;
	        int distance = DFS(userList[i], userList[j], false);
	        if (distance != -1) {
	            total += distance;
	            count++;
	        } 
	    }
	}
	if (count > 0)
	    return total / count;
	else 
	    return 0;
	return 0;
}

vector<string> UserDatabase::getSharedNeighbourhood(string username1, string username2, size_t k)
{
	vector<string> userList = getUserList();
	vector<string> neighbours;
	int dist1;
	int dist2;
	for (int i = 0; i < userList.size(); i++){
	    dist1 = BFS(username1, userList[i], false);
	    dist2 = BFS(username2, userList[i], false);
	    if (dist1 == -1 || dist2 == -1) continue;
	    if (dist1 < k && dist2 < k)
	        neighbours.push_back(userList[i]);
	}
	return neighbours; 
}

// ADD YOUR HELPER FUCTIONS HERE

void UserDatabase::hash(UserNode* node){
    size_t hashCode = hashFunction(node->username, capacity());
    while (_userTable[hashCode] != NULL && _userTable[hashCode] != _dummy){
        hashCode = (hashCode + 1) % capacity();
    }
    _userTable[hashCode] = node;
}

int UserDatabase::findUserIndex(string username){
    vector<string> userList = getUserList();
    int i;
    for (i = 0; i< userList.size(); i++){
        if (username == userList[i]) break;
    }
    return i;
}

































