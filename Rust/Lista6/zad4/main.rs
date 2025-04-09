fn capitalize(s: &str) -> Vec<String> {
    let mut s1 = String::new();
    let mut s2 = String::new();
    for i in 0..s.len(){
        if i%2 == 0{
            s1.push(s.chars().nth(i).unwrap().to_ascii_uppercase());
            s2.push(s.chars().nth(i).unwrap())
        }
        else{
            s1.push(s.chars().nth(i).unwrap());
            s2.push(s.chars().nth(i).unwrap().to_ascii_uppercase())
        }
    }
    vec![s1,s2]
}


fn main() {
    println!("{:?}", capitalize("warriors"));
}

#[test]
fn example_test1() {
    assert_eq!(capitalize("abcdef"),["AbCdEf", "aBcDeF"]);
}
#[test]
fn example_test2() {
    assert_eq!(capitalize("codewars"),["CoDeWaRs", "cOdEwArS"]);
}
#[test]
fn example_test3() {
    assert_eq!(capitalize("abracadabra"),["AbRaCaDaBrA", "aBrAcAdAbRa"]);
}
#[test]
fn example_test4() {
    assert_eq!(capitalize("codewarriors"),["CoDeWaRrIoRs", "cOdEwArRiOrS"]);
}
#[test]
fn example_test5() {
    assert_eq!(capitalize("aleale"),["AlEaLe", "aLeAlE"]);
}
