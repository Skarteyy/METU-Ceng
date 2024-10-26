#include "socialmedia.h"
#include <stdlib.h>

Database db;
Cache userCache;
Cache postCache;

void printUser(User *user) {
  printf("User: %d, Username: %s, Followers: %d, Following: %d, Liked: %d\n",
         user->userId, user->username, user->numOfFollowers,
         user->numOfFollowing, user->liked);
}

void printPost(Post *post) {
  printf("Post: %d, Author: %s, Likes: %d\n", post->postId,
         post->author->username, post->likes);
}

void printUserCache() {
  int i;
  Node *curr;
  curr = userCache.head;
  printf("UserCache:\n");
  for (i=0;i<userCache.size;i++){
      printUser(curr->data); 
      curr = curr->next;
  }

}

void printPostCache() {
  int i;
  Node *curr;
  curr = postCache.tail;
  printf("PostCache:\n");
  for(i=0;i<postCache.size;i++){/**/
      printPost(curr->data);
      curr = curr->prev;
  }
  /*printf("postCSize: %d, cap: %d",postCache.size,postCache.capacity);*/
}

Node *createNode(void *data) {
    Node *np;
    np = (Node*)malloc(sizeof(Node));
    if(np){
        np->data = data;
        np->next = NULL;
        np->prev = NULL;
    }
    return np;
}

void appendToCache(Cache *cache, void *data) { 
    /*cache->head->next*/
    Node *curr,*prev,*np;
    np = createNode(data);
    if(np){
        curr = cache->head;
        prev = NULL;
        if (cache->head == NULL){
            cache->head = np;
            cache->tail = np;
        }
        else{
            np->next = curr;
            curr->prev = np;
            cache->head = np;
            prev = np;
            /*prev*/
            
        }
        
        cache->size++;
    }
    else printf("ELSE");
    if(cache->size > cache->capacity){
        removeLast(cache);
        cache->size--;
    }
}

void moveToFront(Cache *cache, Node *node) { 
    Node *curr,*prev;
    curr = cache->head;prev = NULL; 
    if(curr == node) return;
    while(curr && curr != node){
        prev = curr;
        curr = curr->next;
    }
    if (prev!=NULL){
        prev->next = curr->next;
        if(curr->next) curr->next->prev = prev;/**/
    }
    else{
        cache->head = curr->next;
    } 
    if(!curr->next){
        cache->tail = prev; 
    }
    curr->next = cache->head;
    cache->head->prev=curr;
    curr->prev = NULL;
    cache->head = curr;
}

void removeLast(Cache *cache) {
    Node *prev;
    prev = cache->tail->prev;
    prev->next = NULL;
    free(cache->tail);
    cache->tail = prev;
}

User *fetchUser(int userId) { 
    
    Node *curr,*prev;
    User* user;
    curr = userCache.head;
    prev = NULL;

   if(curr){
    while(curr){
        user=curr->data;
        if(user->userId ==  userId){
            moveToFront(&userCache,curr);
            return user;
        }
        prev = curr;
        curr=curr->next;
    }
   }
    appendToCache(&userCache,&(db.users[userId]));
    user = userCache.head->data;
    return user;
}

Post *fetchPost(int postId) {
    Node *curr,*prev;
    Post* post;
    curr = postCache.head;
    prev = NULL;

    if(curr){
        while(curr){
            post = curr->data;
            if(post->postId == postId){
                moveToFront(&postCache,curr);
                printf("MOVED!!!");
                return post;
            }
            prev = curr;
            curr = curr->next;
        }
        printf("exited with noncurr ");
    }
    appendToCache(&postCache,&(db.posts[postId]));
    post = postCache.head->data;
    return post;
}

void followUser(int followerId, int followedId) {

    User *follower,*followed;
    Node* np;
    Node* temp;

    follower = fetchUser(followerId);
    followed = fetchUser(followedId);
    np = createNode(follower);

    if(followed->followers_tail == NULL){
        followed->followers_tail = np;
        followed->followers_tail->prev = NULL;
        followed->followers_tail->next = NULL;
    }
    else{
        followed->followers_tail->next = np;
        temp = followed->followers_tail;
        followed->followers_tail = followed->followers_tail->next;
        followed->followers_tail->prev = temp;   
    }
    
    followed->numOfFollowers++;
    follower->numOfFollowing++;
}

void likePost(int userId, int postId) {
    User* liker;
    Post* post;

    liker = fetchUser(userId);
    post = fetchPost(postId);
    liker->liked++;
    post->likes++;
}

void printFollowersInReverse() {
  Node *curr,*prev;
  Node *cur2,*prev2;
  User *user,*user2;
  prev = NULL;
  curr = userCache.head;
  prev2=NULL;
  printf("Followers of all users in UserCache in reverse:\n");
  
  while(curr->next){
      curr->prev = prev;
      prev = curr;
      curr = curr->next;
  }
    curr->prev = prev;
  
  while(curr){
      user = curr->data;
      cur2 = user->followers_tail;
      printf("Followers of user with id %d in reverse:\n",user->userId);
      while(cur2){
          user2 = cur2->data;
          printf("[%d] ",user2->userId);
          prev2 = cur2;
          cur2 = cur2->prev;
      }
      printf("\n");
      prev = curr;
      curr = curr->prev;
  }
  
}

void freeLinkedList(Node *head) {
    
    Node *curr,*next;
    curr = head;
    while(curr){
        next = curr->next;
        free(curr);
        curr = next;
    }
}
