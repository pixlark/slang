%% Factorial

let fact =
  lambda (x) if x == 0
  		 	 then 1
			 else x * fact(x - 1).

print fact(0).
print fact(7).

%%
