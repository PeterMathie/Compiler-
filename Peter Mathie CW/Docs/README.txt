<program> ::= <methods> 
<methods> ::= <method>;[<methods>] 
<method> ::= method <id>([<args>]) [vars <args>] 
	begin <statements> [return <id>;] endmethod
<args> ::= <id>[,<args>] 
<statements> ::= <statement>;[<statements>] 
<statement> ::= <assign> | <if> | <while> | <rw>
<rw> ::= read <id> | write <exp>
<assign> ::= <id> := <exp>
<if> ::= if  <cond> then <statements> [else <statements>] endif 
<while> ::= while <cond> begin <statements> endwhile
<cond> ::= <bop> ( <exps> ) 
<bop> ::= less | lessEq | eq | nEq 
<exps> ::= <exp> [,<exps>] 
<exp> ::= <id>[( <exps> )] | <int> 
<int> is a natural number 
<id> is any string starting with character followed by characters or numbers (that is disjoint from the keywords)
