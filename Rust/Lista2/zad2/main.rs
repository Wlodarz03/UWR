fn longest(a1: &str, a2: &str) -> String {
    ('a'..='z').filter(|c| a1.contains(*c) || a2.contains(*c)).collect()
}

fn main() {
    println!("{}",longest("aretheyhere", "yestheyarehere"));
}

#[cfg(test)]
    mod tests {
    use super::*;
   
    fn testing(s1: &str, s2: &str, exp: &str) -> () {
        println!("s1:{:?} s2:{:?}", s1, s2);
        println!("{:?} {:?}", longest(s1, s2), exp);
        println!("{}", longest(s1, s2) == exp);
        assert_eq!(&longest(s1, s2), exp)
    }

    #[test]
    fn basic_test1() {
        testing("aretheyhere", "yestheyarehere", "aehrsty");
        
    }
    #[test]
    fn basic_test2() {
        testing("loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");
        
    }
    #[test]
    fn basic_tests3() {
        testing("abcdefghijkl", "abcdefghijkl", "abcdefghijkl"); 
    }
    #[test]
    fn basic_test4() {
        testing("a", "b", "ab");
        
    }
    #[test]
    fn basic_test5() {
        testing("sasa", "dada", "ads");  
    }
}