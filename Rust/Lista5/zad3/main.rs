fn reverse_words(str: &str) -> String {
    let v = str.split_whitespace()
               .collect::<Vec<_>>();
    for i in &v {
        i.chars()
         .rev()
         .collect::<String>();
    }
    v.join(" ")
}

fn main() {
    println!("{}",reverse_words("The quick brown fox jumps over the lazy dog."));
}
