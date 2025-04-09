fn number(bus_stops:&[(i32,i32)]) -> i32 {
    bus_stops.iter()
        .map(|(x,y)| x-y)
            .sum()
}

fn main() {
    println!("{}",number(&[(10,0),(3,5),(5,8)]));
}

#[test]
fn returns_expected1() {
  assert_eq!(number(&[(10,0),(3,5),(5,8)]), 5);
}
#[test]
fn returns_expected2() {
  assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
}
#[test]
fn returns_expected3() {
  assert_eq!(number(&[(3,0),(9,1),(4,8),(12,2),(6,1),(7,8)]), 21);
}
#[test]
fn returns_expected4() {
  assert_eq!(number(&[(10,0),(5,5),(8,8)]), 10);
}
#[test]
fn returns_expected5() {
  assert_eq!(number(&[(15,0),(3,5),(5,8)]), 10);
}
#[test]
fn returns_expected6() {
  assert_eq!(number(&[(1,0),(1,1),(4,3)]), 2);
}
#[test]
fn returns_expected7() {
  assert_eq!(number(&[(2,0),(0,1),(0,1)]), 0);
}
#[test]
fn returns_expected8() {
  assert_eq!(number(&[(12,0),(5,12),(0,2)]), 3);
}
#[test]
fn returns_expected9() {
  assert_eq!(number(&[(0,0),(5,0),(0,1)]), 4);
}
#[test]
fn returns_expected10() {
  assert_eq!(number(&[(0,0),(0,0),(0,0)]), 0);
}
