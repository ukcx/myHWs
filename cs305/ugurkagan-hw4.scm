(define twoOperatorCalculator ( lambda (lst)
        (cond
                ( (null? (cdr lst)) (car lst)  )
                ( ( eq? (cadr lst) '+ )  (twoOperatorCalculator ( cons (+ (car lst) (caddr lst)) (cdddr lst) )) )
		( ( eq? (cadr lst) '- )  (twoOperatorCalculator ( cons (- (car lst) (caddr lst)) (cdddr lst) )) )
	 ))
)

(define fourOperatorCalculator ( lambda (lst)
        (cond
                ( (null? (cdr lst)) lst  )
                ( ( eq? (cadr lst) '* )  (fourOperatorCalculator( cons (* (car lst) (caddr lst)) (cdddr lst) )) )
                ( ( eq? (cadr lst) '/ )  (fourOperatorCalculator( cons (/ (car lst) (caddr lst)) (cdddr lst) )) )
                ( else
                        (cons (car lst) (fourOperatorCalculator (cdr lst)) )
                )
         ))
)

(define calculatorNested (lambda (lst)
	(cond
		( (or (number? (car lst)) (symbol? (car lst)))
			(if ( null? (cdr lst) )
				lst
				(cons (car lst) (calculatorNested(cdr lst)) ) 
			)
		)
		( else
			(if (null? (cdr lst))
				(cons (twoOperatorCalculator(fourOperatorCalculator(calculatorNestedHelper(car lst)))) '())
				(cons (twoOperatorCalculator(fourOperatorCalculator(calculatorNestedHelper(car lst)))) (calculatorNested(cdr lst)) )
			)
		)
	))
)

(define calculatorNestedHelper (lambda (lst)
        (cond
		(  (number? (car lst))
			(if ( null? (cdr lst) )
				lst
 				( cons (car lst) (calculatorNestedHelper(cdr lst)))
			)
		)
		(  (symbol? (car lst))
			( cons (car lst) (calculatorNestedHelper(cdr lst)) )
		)
                ( else
			(if (null? (cdr lst))
				( cons (twoOperatorCalculator(fourOperatorCalculator(calculatorNestedHelper(car lst)))) '())                        
				( cons (twoOperatorCalculator(fourOperatorCalculator(calculatorNestedHelper(car lst)))) (calculatorNestedHelper(cdr lst)) )  
	       		)
		)
        ))
)

(define checkOperators (lambda (lst)
	(cond
		((not (list? lst)) #f)
		((null? lst) #f)
		((null? (cdr lst))
			(if (number? (car lst))
				#t
				(if (list? (car lst))
					(checkOperators(car lst))
					#f
				)
			)
		)
		((null? (cddr lst)) #f)
		((list? (car lst))
			(cond
				( (eq? (cadr lst) '+)
					(and (checkOperators(car lst)) (checkOperators(cddr lst)) )
				)
				( (eq? (cadr lst) '-)
					(and (checkOperators(car lst)) (checkOperators(cddr lst)) )
				)
				( (eq? (cadr lst) '*)
					(and (checkOperators(car lst)) (checkOperators(cddr lst)) )
				)
				( (eq? (cadr lst) '/)
					(and (checkOperators(car lst)) (checkOperators(cddr lst)) )
				)
				(else #f)
			)
		)
		((number? (car lst))
			(cond 
				( (eq? (cadr lst) '+)
					(checkOperators(cddr lst)))
				( (eq? (cadr lst) '-)
					(checkOperators(cddr lst)))
				( (eq? (cadr lst) '*)
					(checkOperators(cddr lst)))
				( (eq? (cadr lst) '/)
					(checkOperators(cddr lst)))
				(else #f)
			)
		)
		(else
			#f
		)
	))
)

(define calculator (lambda (lst)
	(cond
		((not( checkOperators lst )) #f)
		(else
			(twoOperatorCalculator( fourOperatorCalculator ( calculatorNested lst ) ))
		)
	))
)
