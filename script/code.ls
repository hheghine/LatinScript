#functio sum
#
#numerus x
#numerus y = -1
#
#x = y
#
#x = 3 + y - -4 + 5 - x
#
#scribere << x
#
#x = x / y
#
#scribere << x
#
#numerus z = x + 11
#
#scribere << *x: * << x << * z: * << z
#
#z = z * 4 / 3
#
#scribere << z
#
#scribere << *blabla\t* << y << *aa* << x << *bb*
#
#scribere << x
#
###### this is IF
#< x == 3 >
#	scribere << *if condition worked!*
#
#<< x >= 1 >
#	scribere << *else if condition worked*
#	< x == 1 >
#		scribere << *YUP*
#	<< x > 1 >
#		scribere << *NO*
#
#<< x == 12 >
#	scribere << *else if condition worked*
#
#<<< >
#	scribere << *ELSE !!*
#
#scribere << x
#
#x = 42
#
#< x <= 42 >
#	scribere << *if condition worked!*
#
#scribere << y
#scribere << *hello\\\n*
#
#
#dum < x > 35 >
#	scribere << *x = * << x
#	x = x - 1
#
#scribere << *still working fine*
#
#

numerus x = 1

functio sum < numerus a, numerus b > : numerus
	scribere << *AAAA*
	< x == 0 >
		a = sum
	x = x - 1
	redire a + b
	

scribere << *BBBB*

numerus k = sum

