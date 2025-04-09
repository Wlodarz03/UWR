struct Cipher {
    m1: String,
    m2: String,
}

impl Cipher {
    fn new(map1: &str, map2: &str) -> Cipher {
      Cipher { m1: (map1.to_string()), m2: (map2.to_string()) }
    }
    
    fn encode(&self, string: &str) -> String {
        string.chars()
            .map(|c| match self.m1.find(c) {
              Some(x) => self.m2
                .chars()
                  .nth(x)
                    .unwrap(),
              None => c})
              .collect()                
    }
    
    fn decode(&self, string: &str) -> String {
        string.chars()
        .map(|c| match self.m2.find(c) {
          Some(x) => self.m1
            .chars()
              .nth(x)
                .unwrap(),
          None => c})
          .collect()  
    }
}



fn main() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";
  
    let cipher = Cipher::new(map1, map2);
    println!("{}",cipher.encode("abc"));
    println!("{}",cipher.decode("eta"));
}

#[test]
fn examples1() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.encode("abc"), "eta");
}
#[test]
fn examples2() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.encode("xyz"), "qxz");
}
#[test]
fn examples3() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.decode("eirfg"), "aeiou");
}
#[test]
fn examples4() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);

  assert_eq!(cipher.decode("erlang"), "aikcfu");
}
#[test]
fn examples5() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.encode("acd"), "eao");

}
#[test]
fn examples6() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.encode("aggc"), "essa");
}
#[test]
fn examples7() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.encode("sckd"), "valo");
}
#[test]
fn examples8() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.encode("ilgb"), "rust");
}
#[test]
fn examples9() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.encode("ccc"), "aaa");
}
#[test]
fn examples10() {
  let map1 = "abcdefghijklmnopqrstuvwxyz";
  let map2 = "etaoinshrdlucmfwypvbgkjqxz";

  let cipher = Cipher::new(map1, map2);
  
  assert_eq!(cipher.encode("ncr"), "map");
}
