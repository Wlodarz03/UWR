fn likes(names: &[&str]) -> String {
    let mut wyn = String::new();
    if names.len()>=4{
        wyn.push_str(&names[0][..]);
        wyn.push_str(", ");
        wyn.push_str(&names[1][..]);
        let rest = vec![" and ",&(names.len()-2).to_string()[..]," others like this"].into_iter().collect::<String>();
        wyn.push_str(&rest[..]);
        return wyn;
    }
    else if names.len() == 3{
        let mut wyn = String::new();
        for i in 0..2{
            wyn.push_str(names[i]);
            if i<1{
                wyn.push_str(", ");
            }
        }
        wyn.push_str(" and ");
        wyn.push_str(names[2]);
        wyn.push_str(" like this");
        return wyn;
    }
    else if names.len() == 2{
        let mut wyn = String::new();
        wyn.push_str(names[0]);
        wyn.push_str(" and ");
        wyn.push_str(names[1]);
        wyn.push_str(" like this");
        return wyn;
    }
    else if names.len() == 1{
        let mut wyn = String::new();
        wyn.push_str(names[0]);
        wyn.push_str(" likes this");
        return wyn;
    }
    else{
        return "no one likes this".to_string();
    }
}

fn main() {
    println!("{}",likes(&["Max","John","Mark"]));
}
