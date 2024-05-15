
numerus x
numerus y = -1

x = y

x = 3 + y - -4 + 5 - x

scribere << x

x = x / y

scribere << x

numerus z = x + 11

scribere << *x: * << x << * z: * << z

z = z * 4 / 3

scribere << z

scribere << *blabla\t* << y << *aa* << x << *bb*

scribere << x

##### this is IF
< x == 3 >
	scribere << *if condition worked!*

<< x >= 1 >
	scribere << *else if condition worked*
	< x == 1 >
		scribere << *YUP*
	<< x > 1 >
		scribere << *NO*

<< x == 12 >
	scribere << *else if condition worked*

<<< >
	scribere << *ELSE !!*

scribere << x

x = 42

< x <= 42 >
	scribere << *if condition worked!*

scribere << y
scribere << *hello\\\n*


dum < x > 35 >
	scribere << *x = * << x
	x = x - 1

scribere << *still working fine*

functio sum < numerus a, numerus b > : numerus
	numerus n = a + b
	redire n

functio div < numerus a, numerus b > : numerus
	numerus n = sum < 3, 10 >
	scribere << *n = * << n
	redire a / b

scribere << *Let's goooooooooo*

numerus k = sum < 4, 5 >
scribere << *k = * << k

numerus m = div < 10, 5 >
scribere << *m = * << m

numerus res

functio rec_sum < numerus first, numerus second > : numerus
	res = first + second
	scribere << res
	< res < 5 >
		first = first + 1
		second = second + 1
		scribere << first << * * << second
		res = rec_sum < first, second >
	redire res

numerus test = rec_sum < 1, 2 >
scribere << test 

