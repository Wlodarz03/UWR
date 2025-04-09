fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    let mut only_even = array.into_iter()
                             .filter(|x| *x%2==0)
                             .copied()
                             .collect::<Vec<i32>>();
    only_even.drain(0..only_even.len() - number);
    only_even
    
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_test1() {
        assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
    }
    #[test]
    fn sample_test2() {
        assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
    }   
    #[test]
    fn sample_test3() {
        assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
    }
    #[test]
    fn sample_test4() {
        assert_eq!(even_numbers(&vec!(2), 1), vec!(2));
    }
    #[test]
    fn sample_test5() {
        assert_eq!(even_numbers(&vec!(2,4,6,8), 2), vec!(6,8));
    }            
}

fn main() {
    println!("{}", even_numbers(&vec!(2,4,6,8), 2)[0]);
}
