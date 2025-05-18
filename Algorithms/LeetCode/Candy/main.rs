use std::collections::linked_list::LinkedList;


struct LRUCache {
    capacity: i32,
    cache: [(i32, i32); 10001],
    history: LinkedList<(usize, i32)>,
    time: i32,
}

impl LRUCache {
    fn new(capacity: i32) -> Self {
        LRUCache { capacity, cache: [(-1, -1); 10001], history: LinkedList::new(), time: 0 }
    }

    fn get(&mut self, key: i32) -> i32 {
        let key = key as usize;
        unsafe {
            if self.cache.get_unchecked(key).1 == -1
            {
                return -1;
            }
            self.time += 1;
            self.history.push_back((key, self.time));
            self.cache.get_unchecked_mut(key).1 = self.time;
            self.cache.get_unchecked(key).0
        }
    }

    fn put(&mut self, key: i32, value: i32) {
        let key = key as usize;
        self.time += 1;
        unsafe {
            if self.cache.get_unchecked(key).1 != -1 {
                self.cache[key] = (value, self.time);
                self.history.push_back((key, self.time));
                return;
            }
            if self.capacity > 0 {
                self.cache[key] = (value, self.time);
                self.capacity -= 1;
                self.history.push_back((key, self.time));
                return;
            }
            while !self.history.is_empty() {
                let history_item = self.history.pop_front().unwrap();
                let cache_item = self.cache.get_unchecked(history_item.0 as usize);
                if history_item.1 == cache_item.1 {
                    self.cache[history_item.0 as usize] = (-1, -1);
                    self.cache[key] = (value, self.time);
                    self.history.push_back((key, self.time));
                    return;
                }
            }
        }
    }
}
