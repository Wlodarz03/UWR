fn descending_order(x: u64) -> u64 {
    let mut numbers = Vec::new();
    for i in x.to_string().chars(){
        numbers.push(i)
    }
    numbers.sort();
    numbers.reverse();
    numbers.iter()
            .collect::<String>()
            .parse::<u64>()
            .unwrap()
}


fn main() {
    println!("{}",descending_order(123));
}

#[test]
fn returns_expected1() {
    assert_eq!(descending_order(0), 0);
}
#[test]
fn returns_expected2() {
    assert_eq!(descending_order(1), 1);
}
#[test]
fn returns_expected3() {
    assert_eq!(descending_order(15), 51);
}
#[test]
fn returns_expected4() {
    assert_eq!(descending_order(123456789), 987654321);
}
#[test]
fn returns_expected5() {
    assert_eq!(descending_order(1254859723), 9875543221);
}
