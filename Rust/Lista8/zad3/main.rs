fn part_list(arr: Vec<&str>) -> String {
    let mut result = String::new();

    for i in 1..arr.len() {
        let left = arr[..i].join(" ");
        let right = arr[i..].join(" ");
        result.push_str(&format!("({}, {})", left, right));
    }

    result
}


fn main() {
    println!("{}",part_list(vec!["I", "wish", "I", "hadn't", "come"]));
}

#[cfg(test)]
    mod tests {
    use super::*;

    fn dotest(arr: Vec<&str>, exp: &str) -> () {
        println!("arr: {:?}", arr);
        let ans = part_list(arr);
        println!("actual:\n{}", ans);
        println!("expect:\n{}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
    }

    #[test]
    fn basis_test1() {
        dotest(vec!["I", "wish", "I", "hadn't", "come"],
                "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
    }
    #[test]
    fn basis_test2(){
        dotest(vec!["cdIw", "tzIy", "xDu", "rThG"], 
            "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)");
    }
    #[test]
    fn basis_test3(){
        dotest(vec!["essa", "essunia", "essesiti", "es"], 
            "(essa, essunia essesiti es)(essa essunia, essesiti es)(essa essunia essesiti, es)");
    }
    #[test]
    fn basis_test4(){
        dotest(vec!["a","b"], "(a, b)");
    }
    #[test]
    fn basis_test5(){
        dotest(vec!["a","b","c"], "(a, b c)(a b, c)");
    }
}