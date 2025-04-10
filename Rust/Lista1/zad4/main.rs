fn printer_error(s: &str) -> String {
    let all = s.len();
    let wrong = s.chars().filter(|&ch| ch<'a' || ch>'m').count();
    format!("{}/{}",wrong,all)
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn should_pass_all_the_tests_provided1() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
    }
    #[test]
    fn should_pass_all_the_tests_provided2() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
    }
    #[test]
    fn should_pass_all_the_tests_provided3() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
    }
    #[test]
    fn should_pass_all_the_tests_provided4() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), "0/55");
    }
    #[test]
    fn should_pass_all_the_tests_provided5() {
        assert_eq!(&printer_error("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"), "55/55");
    }
}




fn main() {
    println!("{}",printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"));
    println!("{}","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa".len());
}
