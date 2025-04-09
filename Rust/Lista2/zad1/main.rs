fn get_count(string: &str) -> usize {
    let vowels = ['a','e','i','o','u'];
    string.chars().filter(|x| vowels.contains(x)).count()
}

fn main() {
    println!("{}",get_count("abracadabra"));
}

#[test]
fn my_tests1() {
  assert_eq!(get_count("abracadabra"), 5);
}
#[test]
fn my_tests2() {
  assert_eq!(get_count("ara"), 2);
}
#[test]
fn my_tests3() {
    assert_eq!(get_count("haaaaaa"), 6);
}
#[test]
fn my_tests4() {
    assert_eq!(get_count("ye lp"), 1);
}
#[test]
fn my_tests5() {
    assert_eq!(get_count("y y y y i y y o"), 2);
}


