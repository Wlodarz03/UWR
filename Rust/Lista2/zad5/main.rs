fn gimme_the_letters(sp: &str) -> String {
    let poczatek = sp.chars().next().unwrap();
    let koniec = sp.chars().last().unwrap();
    (poczatek..=koniec).collect()
}


fn main() {
    println!("{}",gimme_the_letters("h-o"));
}

#[cfg(test)]
mod tests {
    use super::gimme_the_letters;
        
    fn dotest(sp: &str, expected: &str) {
        let actual = gimme_the_letters(sp);
        assert!(actual == expected, 
            "With sp = \"{sp}\"\nExpected \"{expected}\" but got \"{actual}\"")
    }

    #[test]
    fn fixed_test1() {
        dotest("a-z", "abcdefghijklmnopqrstuvwxyz");
    }
    #[test]
    fn fixed_test2() {
        dotest("h-o", "hijklmno");
    }
    #[test]
    fn fixed_test3() {
        dotest("Q-Z", "QRSTUVWXYZ");
    }
    #[test]
    fn fixed_test4() {
        dotest("J-J", "J");
    }
    #[test]
    fn fixed_test5() {
        dotest("a-b", "ab");
    }
}