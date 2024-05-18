############################
#    NUMERUS [INT] TEST    #
############################

numerus x
numerus y = -1

x = y

x = 3 + y - -4 + 5 - x

scribere << x

numerus z = x + 11

scribere << *blabla\t* << y << *aa* << x << *bb* << z



############################
#      CONDITION TEST      #
############################

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


############################
# PRINTING [SCRIBERE] TEST #
############################

scribere << y
scribere << *hello\\\n*


############################
#      LOOP [DUM] TEST     #
############################

dum < x > 35 >
	scribere << *x = * << x
	x = x - 1

scribere << *still working fine*


############################
#  FUNCTION [FUNCTIO] TEST #
############################

numerus n

functio sum < numerus a, numerus b > : numerus
	n = a + b
	redire n

functio div < numerus c, numerus d > : numerus
	n = sum < 3, 10 >
	scribere << *n = * << n
	redire c / d

scribere << *Let's goooooooooo*

numerus k = sum < 4, 5 >
scribere << *k = * << k

numerus m = div < 10, 5 >
scribere << *m = * << m


############################
#      RECURSION TEST      #
############################

numerus res

functio rec_sum < numerus first, numerus second > : numerus
	res = first + second
	scribere << res
	< res < 100 >
		first = first + 1
		second = second + 1
		scribere << first << * * << second
		res = rec_sum < first, second >
	redire res

numerus test = rec_sum < 1, 2 >
scribere << test 


############################
#    FILUM [STRING] TEST   #
############################

filum l = *hello\t*

scribere << l

l = l + *world * + *!*

scribere << l

filum ll = *hello*

< l > ll >
	scribere << *YES*


############################
#    DOUBLE [DUPLUS] TEST  #
############################

x = 6

duplus dp = 3.14
scribere << dp

x = dp * x
scribere << x


############################
#  ARRAY [ORDINATA] TEST   #
############################

ordinata < numerus > arr = < 1, 2, 3, 4, 5 >

scribere << arr

arr < 2 > = 42

scribere << arr

numerus idx = 0

dum < idx < 5 >
	arr < idx > = 42
	idx = idx + 1

scribere << arr
scribere << *you have found the answer !!*