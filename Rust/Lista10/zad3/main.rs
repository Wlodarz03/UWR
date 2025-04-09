fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    let mut new = a.into_iter().map(|x| x*x).collect::<Vec<i64>>();
    let mut c = b.clone();
    new.sort();
    c.sort();
    return new == c;
}

fn main() {
    println!("Hello, world!");
}

fn testing(a: Vec<i64>, b: Vec<i64>, exp: bool) -> () {
    assert_eq!(comp(a, b), exp)
}

#[test]
fn tests_comp1() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, true);
}
#[test]
fn tests_comp2() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*21, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, false);
}
#[test]
fn tests_comp3() {
    let a1 = vec![1];
    let a2 = vec![1];
    testing(a1, a2, true);
}
#[test]
fn tests_comp4() {
    let a1 = vec![];
    let a2 = vec![];
    testing(a1, a2, true);
}
#[test]
fn tests_comp5() {
    let a1 = vec![2,3];
    let a2 = vec![9,4];
    testing(a1, a2, true);
}
