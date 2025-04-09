fn zoom(n: i32) -> String {
    let mut square = vec![vec!['□'; n as usize]; n as usize];
    let mut a = (n-1)/2;
    let mut b = a;
    square[a as usize][b as usize] = '■';
    a-=2;
    b+=2;
    while a>=0{
        let range = a..b+1;
        for i in 0..n{
            for j in 0..n{
                if i == a && range.contains(&j) || i == b && range.contains(&j) || j == a && range.contains(&i) || j == b && range.contains(&i){
                    square[i as usize][j as usize] = '■';
                }
            }
        }
        a = a - 2;
        b = b + 2;

    }
    square.iter()
        .map(|row| row.iter().collect())
        .collect::<Vec<String>>()
        .join("\n")
}


fn main() {
    println!("{}",zoom(3));
}

#[test]
fn basic_test_1() {
  assert_eq!(zoom(1), "■");
}

#[test]
fn basic_test_2() {
  assert_eq!(zoom(3), "\
□□□
□■□
□□□"
  );
}

#[test]
fn basic_test_3() {
  assert_eq!(zoom(5), "\
■■■■■
■□□□■
■□■□■
■□□□■
■■■■■"
  );
}

#[test]
fn basic_test_4() {
  assert_eq!(zoom(7), "\
□□□□□□□
□■■■■■□
□■□□□■□
□■□■□■□
□■□□□■□
□■■■■■□
□□□□□□□"
  );
}

#[test]
fn basic_test_5() {
  assert_eq!(zoom(9), "\
■■■■■■■■■
■□□□□□□□■
■□■■■■■□■
■□■□□□■□■
■□■□■□■□■
■□■□□□■□■
■□■■■■■□■
■□□□□□□□■
■■■■■■■■■"
  );
}