fn string_to_number(s: &str) -> i32 {
  let num = s.parse().unwrap();
  num
}

#[cfg(test)]
mod tests {
    use super::string_to_number;
    use rand::prelude::*;

    #[test]
    fn returns_expected1() {
      assert_eq!(string_to_number("1234"), 1234);
    }
    #[test]
    fn returns_expected2() {
      assert_eq!(string_to_number("605"), 605);
    }
    #[test]
    fn returns_expected3() {
      assert_eq!(string_to_number("1405"), 1405);
    }
    #[test]
    fn returns_expected4() {

      assert_eq!(string_to_number("-7"), -7);
    }

    #[test]
    fn works_on_random() {
        let mut rng = thread_rng();
        for _ in 0..5 {
            let num : i32 = rng.gen();
            let input = num.to_string();
            assert_eq!(string_to_number(&input), num);
        }        
    }
}

 fn main() {
     println!("{}",string_to_number("12"));
}
