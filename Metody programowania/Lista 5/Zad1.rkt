#lang plait

;('a 'b - > 'a )
(define poda (lambda (a b) a))

;(('a 'b - > 'c ) ('a - > 'b ) 'a - > 'c )
(define (podb f g x) (f  x (g x)))

;((( 'a - > 'a ) - > 'a ) - > 'a )
(define id (lambda (a) a))
(define (pom f g) (g (f g)))
(define (podc f) (pom f id))

;(('a - > 'b ) ('a - > 'c ) - > ('a - > ('b * 'c ) ) ) , * - para
(define (podd f g) (lambda (x) (pair (f x) (g x))))

;(('a - > ( Optionof ('a * 'b ) ) ) 'a - > ( Listof 'b ) ) , Optionof - opcja lub jej brak
(define (pode f a)
  (if (none? (f a))
      '()
      (if (none? (f (fst (some-v (f a))))) ;ten if jest tylko po to zeby plait wiedzial ze first tez jest typu 'a a nie jakiegos innego bo inaczej wzialby pare ('b * 'c)
          (list (snd (some-v (f a))))
          (list (snd (some-v (f a)))))))

;przyklad bez tego ifa
(define (pode2 f a)
  (if (none? (f a))
      '()
       (list (snd (some-v (f a))))))
      

