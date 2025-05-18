class LRUCache {
public:

    int keyValue[10001];
    int count[10001]; 

    queue <int> lru;
   
    int keyTotal = 0;
    int cap;
    LRUCache(int capacity) {
        cap = capacity;
    }
    int get(int key) {
        if (count[key] == 0) //key is not existed
            return -1;
        else {
            count[key]++;
            lru.push(key);
            return keyValue[key];
        }
    }
   
    void put(int key, int value) {
        if (keyTotal < cap) {
            keyValue[key] = value;
            if (!count[key]) keyTotal++;
            count[key]++;
            lru.push(key);
        }
        else {
            if (count[key] == 0) {
                while (true) {
                    if (!--count[lru.front()]) {
                        lru.pop();
                        break;
                    }
                    lru.pop();
                }
                keyValue[key] = value;
                count[key]++;
                lru.push(key);
            }
            else {
                keyValue[key] = value;
                count[key]++;
                lru.push(key);
            }
        }
    }
};
