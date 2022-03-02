(define get-operator (lambda (op-symbol)
  (cond
    ((equal? op-symbol '+) +)
    ((equal? op-symbol '-) -)
    ((equal? op-symbol '*) *)
    ((equal? op-symbol '/) /)
    (else (display "ERROR")))))

(define oprtr? (lambda (op_sym)
   (or
    (equal? op_sym '+)
    (equal? op_sym '-)
    (equal? op_sym '*)                                                                                                                                          
    (equal? op_sym '/)
   )
))

(define ifstmt?
  (lambda (e)
	(and 
	  (list? e)
	  (eq? (car e) 'if)
	  (= (length e) 4)
	)
  )
)

(define define-stmt? 
  (lambda (e)
     (and 
       (list? e) 
       (= (length e) 3) 
       (eq? (car e) 'define)
       (symbol? (cadr e))
     )
  )
)

(define get-value 
   (lambda (var env)
      (cond
        ((null? env) (display "ERROR"))
        ((eq? var (caar env)) (cdar env))
        (else (get-value var (cdr env)))
      )
   )
)

(define unbind
  (lambda (var old-env)
     (cond
       ((null? old-env) '())
       ((eq? (caar old-env) var) (cdr old-env))
       (else (cons (car old-env) (unbind var (cdr old-env))))
     )
  )
)

(define update-env 
  (lambda (var val old-env)
     (cons (cons var val) (unbind var old-env))
  )
)

(define cndtnl?
	(lambda (e)
		(and
			(list? e)
			(= (length e) 2)
		)
	)
)

(define getLastElem 
	(lambda (e)
		(cond
			((null? (cdr e)) (e))
			(else (getLastElem (cdr e)))
		))
)

(define conditionalList?
	(lambda (e)
		(cond
			((null? (cdr e)) (cndtnl? (car e)))	
			(else (and
				(cndtnl? (car e))
				(conditionalList? (cdr e))
				)
			)
		)
	)
)

(define elsestmt?
	(lambda (e)
		(and
			(list? (car e))
			(= (length (car e)) 2)
			(eq? (caar e) 'else)
		)
	)
)

(define cnd_stmt?
	(lambda (e)
	  (and
		(list? e)
		(eq? (car e) 'cond)
		(>= (length e) 3)
		(elsestmt? (getLastElem e))
		(conditionalList? (cdr e))
	  )
	)
)

(define return_true
	(lambda (e truth_values)
		(cond
			((null? (cdr e)) (cdar e))
			((eq? (car truth_values) 0) (return_true (cdr e) (cdr truth_values) ))
			(else (car e))
		)
	)
)

(define let_bind
	(lambda (expr old new)
		(cond
			((null? (cdr expr)) (cons (cons (caar expr) (s6-interpret (cadar expr) old)) new))
			(else 	(let	((tmp (cons (cons (caar expr) (s6-interpret (cadar expr) old)) new)) )
					(let_bind expr old tmp )
				)
			)
		) 
	)
)

(define let*bind
	(lambda (expr new)
		(cond
			((null? (cdr expr)) (cons (cons (caar expr) (s6-interpret (cadar expr) new)) new))
			(else   (let    ((tmp (cons (cons (caar expr) (s6-interpret (cadar expr) new)) new)))
					(let*bind expr tmp )
				)
			)
		)
	)
)

(define let_stmt?
	(lambda (e)
		(and
			(list? e)
			(= (length e) 3)
			(eq? (car e) 'let)
			
		)	
	)
)

(define binding_list?
	(lambda (lst)
		(cond
			((null? lst) #t)
			((null? (cdr lst)) 
				(and
					(list? (car lst))
                                        (symbol? (caar lst))
                                        (= (length (car lst)) 2)
				)
			)
			(else
				(and
					(list? (car lst))
					(symbol? (caar lst))
					(= (length (car lst)) 2)
					(binding_list? (cadr lst))
				)
			)
		)
	)
)

(define letStar?
	(lambda (e)
		(and
			(list? e)
			(= (length e) 3)
			(eq? (car e) 'let*)
			(binding_list? (cadr e))
		)		
	)
)

(define without_else
	(lambda (e)
		(cond 
			((null? (cdr e)) '())
			(else (cons (car e) (without_else (cdr e))))
		)
	)
)

(define s6-interpret
  (lambda (e env)
    (cond
      ((number? e) e)
      ((symbol? e) (get-value e env))
      ((not(list? e)) (display ("ERROR")))
      (else
	(cond
		((oprtr? (car e)) (let ((operator (get-operator (car e)))
					(operands (map s6-interpret (cdr e) (make-list (length (cdr e)) env))))
          				(apply operator operands))
        	)
		((ifstmt? e) (let ((cndtn (s6-interpret (cadr e) env)))
				     (cond
					((= cndtn 0) (s6-interpret (cadddr e) env))
					(else (s6-interpret (caddr e) env))))
		)
		((cnd_stmt? e) (let* (
					(lst (without_else (cdr e)))
					(truthVals (map s6-interpret lst (make-list (length (lst)) env))))
					( s6-interpret (return_true e truthVals) env)
				 )
		)
		((let_stmt? e)  (let ((newEnv (let_bind (cadr e) env env)))
					( s6-interpret (caddr e) newEnv)
 				)				
		)
		((letStar? e)   (let ((new_enw (let*bind (cadr e) env)))
					( s6-interpret (caddr e) new_enw)
				)
		)
		(else (display "ERROR"))
	)
      )
    ))
)

(define repl 
  (lambda (env)
    (let*
      (
        (dummy1 (display "cs305> "))
        (expr (read))
        (new-env (if (define-stmt? expr)
                     (update-env (cadr expr) (s6-interpret (caddr expr) env) env)
                     env))
        (val (if (define-stmt? expr)
                 (cadr expr) 
                 (s6-interpret expr env)))
        (dummy2 (display "cs305: "))
        (dummy3 (display val))
        (dummy4 (newline))
        (dummy5 (newline))
      )
      (repl new-env)
    )
  )
)

(define cs305 (lambda () (repl '())))

