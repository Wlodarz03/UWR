use std::fs;

mod parser{
    
    use nom::{
        branch::alt,
        bytes::complete::tag,
        character::complete::{digit1, multispace0, alpha1},
        combinator::{map,map_res},
        multi::{many0,many1},
        sequence::{delimited,preceded},
        IResult,
    };

    #[derive(Debug,Clone)]
    pub enum Condition{
        Greater(Value,Value),
        Less(Value,Value),
    }

    pub fn parse_cond(input: &str) -> IResult<&str, Condition>{
        alt((
            parse_greater,
            parse_less,
        ))(input)
    }

    fn parse_greater(input: &str) -> IResult<&str, Condition>{
        let (input, left) = parse_value(input)?;
        let (input, _) = multispace0(input)?;
        let (input, _) = tag(">")(input)?;
        let (input, _) = multispace0(input)?;
        let (input, right) = parse_value(input)?;
        Ok((input,Condition::Greater(left, right)))
    }

    fn parse_less(input: &str) -> IResult<&str, Condition>{
        let (input, left) = parse_value(input)?;
        let (input, _) = multispace0(input)?;
        let (input, _) = tag("<")(input)?;
        let (input, _) = multispace0(input)?;
        let (input, right) = parse_value(input)?;
        Ok((input,Condition::Less(left, right)))
    }

    #[derive(Debug,Clone)]
    pub enum Value{
        Num(f64),
        Variable(String),
    }

    fn parse_value(input: &str) -> IResult<&str, Value> {
        alt((
            map_res(digit1, |s: &str| s.parse::<f64>().map(Value::Num)),
            map(parse_variable,|s: String| Value::Variable(s)),
        ))(input)
    }

    #[derive(Debug,Clone)]
    pub enum LogoCommand{
        Fd(Value),
        Bk(Value),
        Lt(Value),
        Rt(Value),
        Repeat(Value, Vec<LogoCommand>),
        Setcolor(String),
        Pick(Vec<String>),
        Wait(Value),
        Random(Value),
        Label(String), 
        Setlabelheight(Value),
        To(String,Vec<String>, Vec<LogoCommand>),
        //Fun(String, Vec<Value>),
        If(Condition,Vec<LogoCommand>),
        Setturtle(Value),
        Clearscreen,
        Penup,
        Pendown,
        Showturtle,
        Hideturtle,
        Stop,
        Window,
    }

    pub fn parse_logo_command(input: &str) -> IResult<&str, Vec<LogoCommand>>{
        many1(delimited(multispace0, parse_single_logo_command, multispace0))(input)
    }

    fn parse_single_logo_command(input: &str) -> IResult<&str, LogoCommand>{
        alt((
            parse_forward,
            parse_backward,
            parse_left,
            parse_right,
            parse_repeat,
            parse_setcolor,
            parse_pick,
            parse_wait,
            parse_random,
            parse_label,
            parse_setlabelheight,
            parse_to,
            parse_if,
            parse_clearscreen,
            parse_penup,
            parse_pendown,
            parse_showturtle,
            parse_hideturtle,
            parse_setturtle,
            parse_stop,
            parse_window,
        ))(input)
    }

    fn parse_variable(input: &str) -> IResult<&str, String> {
        preceded(multispace0, preceded(tag(":"), parse_string))(input)
    }

    fn parse_string(input: &str) -> IResult<&str, String>{
        map(
            delimited(
                multispace0,
                alpha1,      
                multispace0, 
            ),
            String::from,
        )(input)
    }

    fn parse_forward(input: &str) -> IResult<&str, LogoCommand> {
        let (input, _) = alt((tag("forward "),tag("fd ")))(input)?;
        let (input, lenght) = parse_value(input)?;
        Ok((input, LogoCommand::Fd(lenght)))
    }

    fn parse_backward(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = alt((tag("backward "),tag("bk ")))(input)?;
        let (input, lenght) = parse_value(input)?;
        Ok((input, LogoCommand::Bk(lenght)))
    }

    fn parse_left(input: &str) -> IResult<&str, LogoCommand> {
        let (input, _) = alt((tag("left "),tag("lt ")))(input)?;
        let (input, angle) = parse_value(input)?;
        Ok((input, LogoCommand::Lt(angle)))
    }

    fn parse_right(input: &str) -> IResult<&str, LogoCommand> {
        let (input, _) = alt((tag("right "),tag("rt ")))(input)?;
        let (input, angle) = parse_value(input)?;
        Ok((input, LogoCommand::Rt(angle)))
    }

    fn parse_repeat(input: &str) -> IResult<&str, LogoCommand> {
        let (input, _) = tag("repeat")(input)?;
        let (input, _) = multispace0(input)?;
        let (input, count) = parse_value(input)?;
        let (input, _) = multispace0(input)?;
        let (input, commands) = delimited(
            tag("["),
             parse_logo_command,
            tag("]"))(input)?;
        Ok((input, LogoCommand::Repeat(count, commands)))
    }

    fn parse_setcolor(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("setcolor ")(input)?;
        let (input, color) = parse_string(input)?;
        Ok((input, LogoCommand::Setcolor(color)))
    }

    fn parse_pick(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("pick ")(input)?;
        let (input, colors) = delimited(
        tag("["),
        many1(parse_string),
        tag("]"),
        )(input)?;
        Ok((input, LogoCommand::Pick(colors)))
    }

    fn parse_wait(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("wait")(input)?;
        let (input, _) = multispace0(input)?;
        let (input, time) = parse_value(input)?;
        Ok((input, LogoCommand::Wait(time)))
    }

    fn parse_random(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("random")(input)?;
        let (input, _) = multispace0(input)?;
        let (input, num) = parse_value(input)?;
        Ok((input, LogoCommand::Random(num)))
    }

    fn parse_label(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("label ")(input)?;
        let (input, lab) = parse_string(input)?;
        Ok((input, LogoCommand::Label(lab)))
    }

    fn parse_setlabelheight(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("setlabelheight ")(input)?;
        let (input, height) = parse_value(input)?;
        Ok((input, LogoCommand::Setlabelheight(height)))
    }

    fn parse_to(input: &str) -> IResult<&str, LogoCommand> {
        let (input, _) = alt((tag("to"),tag("TO")))(input)?;
        let (input, _) = multispace0(input)?;
    
        let (input, name) = parse_string(input)?;
        let (input, _) = multispace0(input)?;

        let (input, vars) = many0(parse_variable)(input)?;
        let (input, _) = multispace0(input)?;
        
        let (input, commands) = parse_logo_command(input)?;
    
        //let (input, _) = multispace0(input)?;
        let (input, _) = preceded(multispace0, alt((tag("end"),tag("END"))))(input)?;
    
        Ok((input, LogoCommand::To(name, vars, commands)))
    }

    fn parse_if(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("if")(input)?;
        let (input, _) = multispace0(input)?;
        let (input, cond) = parse_cond(input)?;
        let (input, _) = multispace0(input)?;
        let (input, rest) = delimited(
            tag("["),
             parse_logo_command,
            tag("]"))(input)?;
        Ok((input,LogoCommand::If(cond, rest)))
    }

    fn parse_clearscreen(input: &str) -> IResult<&str, LogoCommand> {
        let (input, _) = tag("clearscreen")(input)?;
        let (input, _) = multispace0(input)?;
        Ok((input, LogoCommand::Clearscreen))
    }

    fn parse_penup(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = alt((tag("pu"),tag("penup")))(input)?;
        let (input, _) = multispace0(input)?;
        Ok((input, LogoCommand::Penup))
    }

    fn parse_pendown(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = alt((tag("pd"),tag("pendown")))(input)?;
        let (input, _) = multispace0(input)?;
        Ok((input, LogoCommand::Pendown))
    }

    fn parse_showturtle(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("showturtle")(input)?;
        let (input, _) = multispace0(input)?;
        Ok((input, LogoCommand::Showturtle))
    }

    fn parse_hideturtle(input: &str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("hideturtle")(input)?;
        let (input, _) = multispace0(input)?;
        Ok((input, LogoCommand::Hideturtle))
    }
    
    fn parse_stop(input:&str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("stop")(input)?;
        let (input, _) = multispace0(input)?;
        Ok((input, LogoCommand::Stop))
    }

    fn parse_window(input:&str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("window")(input)?;
        let (input, _) = multispace0(input)?;
        Ok((input, LogoCommand::Window))
    }

    fn parse_setturtle(input:&str) -> IResult<&str, LogoCommand>{
        let (input, _) = tag("setturtle")(input)?;
        let (input, _) = multispace0(input)?;
        let (input, num) = parse_value(input)?;
        Ok((input,LogoCommand::Setturtle(num)))
    }

    // fn is_reserved_command(name: &str) -> bool {
    //     let reserved_commands = ["forward","fd","lt","left","rt","right","bk","backward","to","TO","repeat","setcolor","pick","wait","stop","window","pendown","pd","penup","pu","random","label","setlabel","clearscreen"];
    //     reserved_commands.contains(&name)
    // }

    // pub fn parse_fun(input: &str) -> IResult<&str, LogoCommand> {
    //     let (input, name) = parse_string(input)?;

    //     let (input, _) = multispace0(input)?;

    //     let (input, args) = many0(preceded(multispace0, parse_value))(input)?;

    //     if !is_reserved_command(&name) {
    //         return Ok((input, LogoCommand::Fun(name, args)));
    //     }
    //     else {
    //         Err(nom::Err::Error(nom::error::Error::new(
    //             input,
    //         nom::error::ErrorKind::Char,
    //         )))
    //     }
    // }
}

fn main() {

    println!("Program 1:");
    println!("");
    let data = fs::read_to_string("logo1.txt").unwrap();
    let mut s = String::new();
    for line in data.lines(){
        s.push_str(line);
    }
    let input = &s[..];
    let commands = parser::parse_logo_command(input).unwrap().1;

    for com in commands{
        println!("{:?}",com);
    }
    println!(" ");


    println!("Program 2:");
    println!("");
    let data2 = fs::read_to_string("logo2.txt").unwrap();
    let mut s2 = String::new();
    for line in data2.lines(){
        s2.push_str(line);
    }
    let input2 = &s2[..];
    let commands2 = parser::parse_logo_command(input2).unwrap().1;

    for com in commands2{
        println!("{:?}",com);
    }
    println!("");


    println!("Program 3:");
    println!("");
    let data3 = fs::read_to_string("logo3.txt").unwrap();
    let mut s3 = String::new();
    for line in data3.lines(){
        s3.push_str(line);
    }
    let input3 = &s3[..];
    let commands3 = parser::parse_logo_command(input3).unwrap().1;

    for com in commands3{
        println!("{:?}",com);
    }
}