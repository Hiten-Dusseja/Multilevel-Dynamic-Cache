#include <bits/stdc++.h>
using namespace std;

class Cache{
    protected:
    int capacity;
    unordered_map<string,string> data;
    public:
    virtual int getcurrcapacity() { return 1; }
    virtual int gettotalcapacity() { return 1; }
    virtual pair<string,string> put(string key, string value) { return {"",""}; }
    virtual string get(string key) {return "";}
    virtual void show() {}
    virtual ~Cache() {} 
};
class LRU: public Cache{
    private:
    deque<string> dqforlru;
    public:
    int getcurrcapacity() override
    {
        return data.size();
    }
    int gettotalcapacity() override
    {
        return capacity;
    }
    void setcapacity(int c)
    {
        capacity = c;
    }
    string get(string key) override{
        if(data.find(key) == data.end()) return "";
        deque<string> temp;
        while(!dqforlru.empty())
        {
            if(dqforlru.front() != key)
            {
                temp.push_back(dqforlru.front());
            }
            dqforlru.pop_front();
        }
        dqforlru = temp;
        // dqforlru.push_back(key);
        // return data[key];
        string value = data[key];
        data.erase(key);
        return value;
    }
    pair<string,string> put(string key, string value) override
    {  

        if(dqforlru.size()>=capacity && data.size()>=capacity)
        {
            string delkey = dqforlru.front();
            dqforlru.pop_front();
            string delval = data[delkey];
            data.erase(delkey);
            data[key] = value;
            dqforlru.push_back(key);
            return {delkey,delval};
        }
        data[key] = value;
        dqforlru.push_back(key);
        return {"",""};
    }
    void show() override
    {
        for(auto it:data)
        {
            cout<<it.first<<"->"<<it.second<<endl;
        }
    }
};

class LFU: public Cache{
    private:
        priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> pqforlfu;
    public:
    int getcurrcapacity() override
    {
        return data.size();
    }
    int gettotalcapacity() override
    {
        return capacity;
    }
    void setcapacity(int c)
    {
        capacity = c;
    }
    string get(string key) override{
        if(data.find(key) == data.end()) return "";
        priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> temppq;
        int newfrequency = 0;
        while(!pqforlfu.empty())
        {
            if(pqforlfu.top().second == key)
            {
                newfrequency = pqforlfu.top().first+1;
            }
            else
            {
                temppq.push(pqforlfu.top());
            }
            pqforlfu.pop();
        }
        pqforlfu = temppq;
        // pqforlfu.push({newfrequency,key});
        // return data[key];
        string val = data[key];
        data.erase(key);
        return val;
    }
    pair<string,string> put(string key, string value) override
    {  
        if(pqforlfu.size()>=capacity && data.size()>=capacity)
        {
            string delkey = pqforlfu.top().second;
            pqforlfu.pop();
            string delval = data[delkey];
            data.erase(delkey);
            data[key] = value;
            pqforlfu.push({0,key});
            return {delkey,delval};
        }
        data[key] = value;
        pqforlfu.push({0,key});
        return {"",""};
    }
    void show() override
    {
        for(auto it:data)
        {   
            cout<<it.first<<"->"<<it.second<<endl;
        }
    }
};

int main()
{
    vector<Cache*> ListOfCache;
    // LRU l1;
    // LFU l2;
    // LRU l3;
    // LFU l4;
    // ListOfCache.push_back(&l1);
    // ListOfCache.push_back(&l2);
    // ListOfCache.push_back(&l3);
    // ListOfCache.push_back(&l4);
    // l1.setcapacity(2);
    // l2.setcapacity(2);
    // l3.setcapacity(2);
    // l4.setcapacity(2);
    // l1.put("1","100");
    // l1.put("2","200");
    // ListOfCache.front()->show();
    // pair<string,string> DeletedRecord = l1.put("3","300");
    // ListOfCache[1]->put(DeletedRecord.first,DeletedRecord.second);
    while(true)
    {
                
        int choice;
        cout<<"Enter your choice:"<<endl;
        cout<<"1. Add Cache Level"<<endl;
        cout<<"2. get"<<endl;
        cout<<"3. put"<<endl;  
        cout<<"4. Remove Cache Level"<<endl;
        cout<<"5. Display Cache"<<endl;
        cout<<"6. Exit"<<endl;
        cin>>choice;
        if(choice == 1)
        {
            int capacity;
            cout<<"Enter capacity: ";
            cin>>capacity;
            string eviction;
            cout<<"Enter eviction policy: ";
            cin>>eviction;
            if(eviction == "LRU")
            {
                LRU* cache = new LRU(); 
                ListOfCache.push_back(cache);
                cache->setcapacity(capacity);
            }
            else if(eviction == "LFU")
            {
                LFU* cache = new LFU();
                ListOfCache.push_back(cache);
                cache->setcapacity(capacity);
            }
        }
        else if(choice == 2)
        {
            string key;
            cout<<"Enter key: ";
            cin>>key;
            string ans = "";
            for(auto it:ListOfCache)
            {
                string temp = it->get(key);
                if(temp != "")
                {
                    ans = temp;
                }
            }
            if(ans != "")
            {
                cout<<key<<" "<<ans<<endl;
                pair<string,string> DeletedRecord = ListOfCache[0]->put(key,ans);
                if(DeletedRecord.first != "" && DeletedRecord.second != "")
                {
                    for(int i=1;i<ListOfCache.size();i++)
                    {
                        if(ListOfCache[i]->getcurrcapacity()<ListOfCache[i]->gettotalcapacity())
                        {
                            ListOfCache[i]->put(DeletedRecord.first,DeletedRecord.second);
                            break;
                        }
                    }
                }
            }
            else cout<<"Not Found!"<<endl;
        }
        else if(choice == 3)
        {
            string key,value;
            cout<<"Enter key and value seperated by space: ";
            cin>>key>>value;
            pair<string,string> DeletedRecord = ListOfCache[0]->put(key,value);
            if(DeletedRecord.first != "" && DeletedRecord.second != "")
            {
                for(int i=1;i<ListOfCache.size();i++)
                {
                    if(ListOfCache[i]->getcurrcapacity()<ListOfCache[i]->gettotalcapacity())
                    {
                        ListOfCache[i]->put(DeletedRecord.first,DeletedRecord.second);
                        break;
                    }
                }
            }
        }
        else if(choice == 4)
        {
            int ind;
            cout<<"Enter the level of cache to be removed: ";
            cin>>ind;
            if(ind<=ListOfCache.size())
            {   
                delete ListOfCache[ind - 1];
                ListOfCache.erase(ListOfCache.begin()+(ind-1));
                cout<<"Removed!"<<endl;
            }   
            else
            {
                cout<<"No such Cache"<<endl;
            }
        }
        else if(choice == 5)
        {
            for(int i=0;i<ListOfCache.size();i++)
            {
                cout<<"Level "<<i+1<<endl;
                ListOfCache[i]->show();
            }
        }    
        else if(choice == 6)
        {
            cout<<"Exiting...";
            for (Cache* cache : ListOfCache) {
                delete cache;
            }
            exit(0);
        }
    }
    for (Cache* cache : ListOfCache) {
        delete cache;
    }
    return 0;
    
}