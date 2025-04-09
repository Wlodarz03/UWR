fn row_sum_odd_numbers(n:i64) -> i64 {
    n.pow(3)
  }

fn main() {
    println!("{}", row_sum_odd_numbers(3));
}

#[test]
fn returns_expected1() {
  assert_eq!(row_sum_odd_numbers(1), 1);
}
#[test]
fn returns_expected2() {
  assert_eq!(row_sum_odd_numbers(42), 74088);
}
#[test]
fn returns_expected3() {
  assert_eq!(row_sum_odd_numbers(2), 8);
}
#[test]
fn returns_expected4() {
  assert_eq!(row_sum_odd_numbers(3), 27);
}
#[test]
fn returns_expected5() {
  assert_eq!(row_sum_odd_numbers(4), 64);
}
#[test]
fn returns_expected6() {
  assert_eq!(row_sum_odd_numbers(5), 125);
}
#[test]
fn returns_expected7() {
  assert_eq!(row_sum_odd_numbers(6), 216);
}
#[test]
fn returns_expected8() {
  assert_eq!(row_sum_odd_numbers(7), 343);
}
#[test]
fn returns_expected9() {
  assert_eq!(row_sum_odd_numbers(8), 512);
}
#[test]
fn returns_expected10() {
  assert_eq!(row_sum_odd_numbers(10), 1000);
}