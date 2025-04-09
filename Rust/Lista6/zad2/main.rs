mod solution {
    fn helper(a: &[i32], p: usize) -> usize{
        let mut v = Vec::new();
        v.push(a[p]);
        for i in p+1..a.len(){
            if (a[i-1] - a[i]).abs() == 1{
                v.push(a[i])
            }
            else{
                break;
            }
        }
        if v.len()>=3{
            return v.len();
        }
        else{
            return 1;
        }
    }

    pub fn range_extraction(a: &[i32]) -> String {
        let mut p: usize = 0;
        let mut my_vec = Vec::new();

        while p!=a.len(){
            let cykl = helper(a,p);
            let mut newstring = String::new();
            if cykl>1{
                let pocz = a[p].to_string();
                p += cykl;
                let kon = a[p-1].to_string();
                newstring = format!("{pocz}-{kon}");
                my_vec.push(newstring)
            }
            else{
                my_vec.push(a[p].to_string());
                p += cykl;
            }
        }
        my_vec.join(",")
    }
}


fn main() {
    println!("Hello, world!");
}

#[test]
fn example1() {
    assert_eq!(solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]), "-6,-3-1,3-5,7-11,14,15,17-20");	
}
#[test]
fn example2() {
    assert_eq!(solution::range_extraction(&[-3,-2,-1,2,10,15,16,18,19,20]), "-3--1,2,10,15,16,18-20");
}
#[test]
fn example3() {
    assert_eq!(solution::range_extraction(&[-10,-9,-8,-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]), "-10--8,-6,-3-1,3-5,7-11,14,15,17-20");
}
#[test]
fn example4() {
    assert_eq!(solution::range_extraction(&[-3,-2,-1,0]), "-3-0");
}
#[test]
fn example5() {
    assert_eq!(solution::range_extraction(&[-3,-2,11,12]), "-3,-2,11,12");
}