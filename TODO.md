# TO-DO items

## Builtins
[ ]	pwd
[ ]	echo with option -n
[ ]	cd with only relative or absolute path
[ ]	export with no options
[ ] unset with no options
[ ]	env with no options
[ ] exit with no options

## Other stuff for future
[x] get env variables when shell starts and save them.
[x] create struct that has everything needed. Paths, inputs etc...
[ ] create a function to free struct variables in the end
	[ ] paths

## Known bugs
[ ] Sometimes the shell requires typing quit two times before it quits


--- 

### Completed

## Task: writing "echo "hello"" into our shell prints out "hello" in terminal

### To get there:
[x] We can get input from user
[x] We parse the command from the input
[x] We look for echo from environment
[x] Once found, we pass "hello" to echo command

