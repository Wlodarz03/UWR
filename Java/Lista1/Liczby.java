class Liczby{
    private static String[] jednosci = { "", "jeden ", "dwa ", "trzy ", "cztery ", "pięć ", "sześć ", "siedem ",
                                     "osiem ", "dziewięć "};
    private static String[] nastki = {"dziesięć ", "jedenaście ", "dwanaście ", "trzynaście ", "czternaście ", "piętnaście ",
                                 "szesnaście ","siedemnaście ", "osiemnaście ", "dziewiętnaście "};
    private static String[] dziesiatki = {"", "", "dwadzieścia ", "trzydzieści ", "czterdzieści ", "pięćdziesiąt ", "sześćdziesiąt ",
                                "siedemdziesiąt ", "osiemdziesiąt ", "dziewięćdziesiąt "};
    private static String[] setki = {"", "sto ", "dwieście ", "trzysta ", "czterysta ", "pięćset ", "sześćset ", "siedemset ",
                            "osiemset ", "dziewięćset "};

    private static String convert1(int x){
        String wyn = "";
        if (x<10){
            wyn += jednosci[x];
        }
        return wyn;
    }
    private static String convert2(int x){
        String wyn = "";
        if (x < 20){
            wyn += nastki[x%10];
        }
        else{
            wyn += dziesiatki[x/10];
            wyn += jednosci[x%10];
        }
        return wyn;
    }
    private static String convert3(int x){
        String wyn = "";
        int tmp = x/100;
        wyn += setki[tmp];
        if (x-tmp*100 >=10){
            wyn += convert2(x-tmp*100);
        }
        else{
            wyn += convert1(x-tmp*100);
        }
        return wyn;
    }

    private static String convert(int x, int n){
        StringBuilder wyn = new StringBuilder();
        if (x < 0){
            wyn.append("minus ");
            n-=1;
            x = x * -1;
        }
        while (n>0){
            if (n == 10){
                if (x/1_000_000_000 == 1){
                    wyn.append("miliard ");
                }
                else{
                    wyn.append("dwa miliardy ");
                }
                x = x - (x/1_000_000_000) * 1_000_000_000;
                n -= n - Integer.toString(x).length();
            }
            if (n == 9){
                int tmp = x / 1_000_000;
                wyn.append(convert3(tmp));
                if (tmp%10 >= 2 && tmp%10 <=4 && (tmp/10)%10>1){
                    wyn.append("miliony ");
                }
                else{
                    wyn.append("milionów ");
                }
                x = x - tmp*1_000_000;
                //n-=3;
                n -= n - Integer.toString(x).length();
            }
            if (n == 8){
                int tmp = x / 1_000_000;
                wyn.append(convert2(tmp));
                if (tmp%10 >= 2 && tmp%10 <=4 && tmp/10 >1){
                    wyn.append("miliony ");
                }
                else{
                    wyn.append("milionów ");
                }
                x = x - tmp*1_000_000;
                //n-=2;
                n -= n - Integer.toString(x).length();
            } 
            if (n == 7){
                int tmp = x / 1_000_000;
                if (tmp == 1){
                    wyn.append("milion ");
                }
                else if (tmp >=2 && tmp <=4){
                    wyn.append(convert1(tmp));
                    wyn.append("miliony ");
                }
                else{
                    wyn.append(convert1(tmp));
                    wyn.append("milionów ");
                }
                x = x - tmp*1_000_000;
                //n-=1;
                n -= n - Integer.toString(x).length();
            }
            if (n == 6){
                int tmp = x / 1000;
                wyn.append(convert3(tmp));
                if (tmp%10 >= 2 && tmp%10 <=4 && (tmp/10)%10>1){
                    wyn.append("tysiące ");
                }
                else{
                    wyn.append("tysięcy ");
                }
                x = x - tmp*1000;
                //n-=3;
                n -= n - Integer.toString(x).length();
            }
            if (n == 5){
                int tmp = x / 1000;
                wyn.append(convert2(tmp));
                if (tmp%10 >= 2 && tmp%10 <=4 && tmp/10 >1){
                    wyn.append("tysiące ");
                }
                else{
                    wyn.append("tysięcy ");
                }
                x = x - tmp*1000;
                //n-=2;
                n -= n - Integer.toString(x).length();
            }
            if (n == 4){
                int tmp = x / 1000;
                if (tmp == 1){
                    wyn.append("tysiąc ");
                }
                else if (tmp >=2 && tmp <=4){
                    wyn.append(convert1(tmp));
                    wyn.append("tysiące ");
                }
                else{
                    wyn.append(convert1(tmp));
                    wyn.append("tysięcy ");
                }
                x = x - tmp*1000;
                //n-=1;
                n -= n - Integer.toString(x).length();
            }
            if (n == 3){
                wyn.append(convert3(x));
                n-=3;
            }
            if (n == 2){
                wyn.append(convert2(x));
                n-=2;
            }
            if (n == 1){
                wyn.append(convert1(x));
                n-=1;
            }
        }
        return wyn.toString();
        
    }
    public static void main(String[] args){
        for (String s : args){
            if (Integer.parseInt(s) == 0){
                System.out.println("zero");
            }
            else{
                System.out.println( convert(Integer.parseInt(s), s.length()) );
            }
        }
    }
}