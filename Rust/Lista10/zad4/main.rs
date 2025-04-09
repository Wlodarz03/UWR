use std::collections::HashMap;

fn encode(msg: String, n: i32) -> Vec<i32> {
    let mut dict = HashMap::from([
        ('a',1),('b',2),('c',3),('d',4),('e',5),('f',6),('g',7),
        ('h',8),('i',9),('j',10),('k',11),('l',12),('m',13),('n',14),
        ('o',15),('p',16),('q',17),('r',18),('s',19),('t',20),('u',21),
        ('v',22),('w',23),('x',24),('y',25),('z',26)
    ]);
    let nums:Vec<i32> = n.to_string()
                .chars()
                .map(|c| c.to_string().parse::<i32>().unwrap())
                .collect();
    let mut wyn = Vec::with_capacity(msg.len());
    for (i, c) in msg.chars().enumerate(){
        let new = *dict.get_mut(&c).unwrap() + nums[i % n.to_string().len()];
        wyn.push(new);
    }
    wyn
}


fn main() {
    println!("{:?}", encode("scout".to_string(), 1939));
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn fixed_tests1() {
        assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
    }
    #[test]
    fn fixed_tests2() {
        assert_eq!(encode("masterpiece".to_string(), 1939), vec![14, 10, 22, 29, 6, 27, 19, 18, 6, 12, 8]);
    }
    #[test]
    fn fixed_tests3() {
        assert_eq!(encode("a".to_string(), 2), vec![3]);
    }
    #[test]
    fn fixed_tests4() {
        assert_eq!(encode("abc".to_string(), 193), vec![2,11,6]);
    }
    #[test]
    fn fixed_tests5() {
        assert_eq!(encode("rust".to_string(), 12), vec![19,23,20,22]);
    }
}