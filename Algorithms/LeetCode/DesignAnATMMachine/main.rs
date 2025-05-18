struct ATM {
    values: [i32; 5],
    banknotes: [i32; 5],
}

impl ATM {
    fn new() -> Self {
        ATM {
            values: [20, 50, 100, 200, 500],
            banknotes: [0, 0, 0, 0, 0],
        }
    }

    fn deposit(&mut self, banknotes_count: Vec<i32>) {
        for i in 0..banknotes_count.len() {
            self.banknotes[i] += banknotes_count[i];
        }
    }

    fn withdraw(&mut self, mut amount: i32) -> Vec<i32> {
        let mut take = vec![0; 5];

        for i in (0..5).rev() {
            take[i] = std::cmp::min(self.banknotes[i], amount / self.values[i]);
            amount -= take[i] * self.values[i];
        }

        if amount != 0 {
            return vec![-1];
        }

        for i in 0..5 {
            self.banknotes[i] -= take[i];
        }

        take
    }
}
