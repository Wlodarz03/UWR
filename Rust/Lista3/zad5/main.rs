fn last_digit(str1: &str, str2: &str) -> i32 {
    let a = str1
        .chars()
            .last()
                .unwrap()
                    .to_string()
                        .parse::<i32>()
                            .unwrap();
    let b: i32;
    if str2.len() < 2{
        b = str2
            .chars()
                .last()
                    .unwrap()
                        .to_string()
                            .parse::<i32>()
                                .unwrap();
        if b == 0{
            return 1;
        }
    }
    else{
        b = str2
            .get(str2.len()-2..)
                .unwrap()
                    .to_string()
                        .parse::<i32>()
                            .unwrap();
    }
    if b % 4 == 0{
        return a.pow(4) % 10;
    }
    else{
        let bv2 = b % 4;
        return a.pow(bv2 as u32) % 10;
    }
  }

fn main() {
    println!("{}", last_digit("4", "0"))
}
#[test]
fn returns_expected1() {
  assert_eq!(last_digit("4", "1"), 4);
}
#[test]
fn returns_expected2() {
  assert_eq!(last_digit("4", "2"), 6);
}
#[test]
fn returns_expected3() {
  assert_eq!(last_digit("9", "7"), 9);
}
#[test]
fn returns_expected4() {
  assert_eq!(last_digit("10","10000000000"), 0);
}
#[test]
fn returns_expected5() {
  assert_eq!(last_digit("1606938044258990275541962092341162602522202993782792835301376","2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376"), 6);
}
#[test]
fn returns_expected6() {
  assert_eq!(last_digit("3715290469715693021198967285016729344580685479654510946723", "68819615221552997273737174557165657483427362207517952651"), 7);
}
#[test]
fn returns_expected7() {
  assert_eq!(last_digit("2", "2"), 4);
}
#[test]
fn returns_expected8() {
  assert_eq!(last_digit("0", "2"), 0);
}
#[test]
fn returns_expected9() {
  assert_eq!(last_digit("0", "0"), 1);
}
#[test]
fn returns_expected10() {
  assert_eq!(last_digit("12", "1"), 2);
}
