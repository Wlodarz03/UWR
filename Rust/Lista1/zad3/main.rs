fn square_area_to_circle(size:f64) -> f64 {
    let pi = std::f64::consts::PI;
    let r = size.sqrt()/2.0;
    return pi*r.powf(2.0);
}

fn main() {
    println!("{}",square_area_to_circle(16.0));
}

#[allow(dead_code)]
fn assert_close(a:f64, b:f64, epsilon:f64) {
    assert!( (a-b).abs() < epsilon, "Expected: {}, got: {}",b,a);
}

#[test]
fn test1() {
  assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
}

#[test]
fn test2() {
  assert_close(square_area_to_circle(20.0), 15.70796326794897, 1e-8);
}

#[test]
fn test3() {
  assert_close(square_area_to_circle(4.0), 3.141592653589793, 1e-8);
}
#[test]
fn test4() {
  assert_close(square_area_to_circle(25.0), 19.634954084936208, 1e-8);
}

#[test]
fn test5() {
  assert_close(square_area_to_circle(16.0), 12.566370614359172, 1e-8);
}
