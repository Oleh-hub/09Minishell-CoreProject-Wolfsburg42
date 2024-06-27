# 09Minishell-CoreProject-Wolfsburg42
This project is about creating a simple shell (command-line interpreter).
A kind of little bash mimic. A lot about processes and file descriptors should be learned in the process.
## Short description of the project
It is a team project for two. One is supposed to do the parsing part, another - the execution part.
## The minishell functionality in compairition with bash:
- The shell will work only in interactive mode (no scripts, i.e. the executable takes no arguments)
- Run simple commands with absolute, relative path (e.g. /bin/ls, ../bin/ls)
- Run simple commands without a path (e.g. ls, cat, grep, etc…)
...
### The deatailed project overview:
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

### Bash manual:
https://www.gnu.org/software/bash/
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

### Minishell tests 
(https://github.com/t0mm4rx/minishell_tests?tab=readme-ov-file#tests)
ot interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon):
- echo bonjour ; | 
- echo bonjour |;
- echo bonjour |;
- echo bonjour ; ls
- export var; export var=test
- echo "\s" & echo "\s"
- cd ../../../../../.. ; pwd


- echo bonjour | |
- echo bonjour > test\ 1
- cd $HOME/Documents
- echo >
!:
- echo -n -n -nnnn -nnnnm
- cat /dev/random | head -n 1 | cat -e
- unset var1 # with undefined var1
!:
- export "" et unset ""
- echo test > file test1
!:
- $
- not_cmd bonjour > salut
!:
- env puis export puis env # vars aren't sorted
!:
// Bonus part : "&& and || with parenthesis for piorities:"
- cat Makefile | grep pr | head -n 5 | cd test (mybin) # check status code

- cat Makefile | grep pr | head -n 5 | cat test (bin) # check status code
- cat Makefile | grep pr | head -n 5 | hello (NA) # check status code

- echo bonjour >>> test
- echo bonjour > > out
- echo 2 >> out1 > out2
- echo 2 > out1 >> out2
<============>
- cat < test # with non-existent test
!
- echo bonjour > $test # with test not defined
! minishell # all the rest of files cause "name: command not found"
- file_name_in_current_dir
- cd ../../../../../.. | pwd
! other message but ok
- ctrl-C . 130 sur bin(ex : sleep 10)&line vide
! other message but ok
- ctrl-\ .131 sur bin
!passed because of subj: "Not interpret unclosed quotes"
- echo "bip | bip ; coyotte > < " "
- cat | cat | cat | ls # check outputs order
- $bla # with bla not defined
- export var ="cat Makefile | grep >"
! look next one
- export var="cat Makefile | grep >"
! the left part of pipe is not being exectuted first
- $var
!
- export "test=ici"=coucou
- c$var Makefile # with var=at
- $LESS$VAR
- /bin/echo bonjour
- not_cmd
- sleep 5 | exit
!
- echo $0
!
- echo bonjour > $test w/ t
- "exit retour a la ligne"
!
- minishell # binary not in path without "./" before
- cat diufosgid # check exit code
- exit # should return the last exit code value
! the build is should be exectuted with option exept 'echo -n'
- exit -10
- exit +10
- ;
- echo coucou | ;
- echo "$HOME"
- echo '$HOME'
- export ; env # display is different for both commands
- echo $HOME
- > log echo coucou
!
- echo hudifg d | | hugdfihd
! bonus part
- echo hudifg d || hugdfihd
- echo
- echo simple
- echo -n simple
- echo ''
- echo ""
- echo "\"
<=============2222222222222222=====>
- echo "\n \n \n"
!
- echo "\n \n \\n"
- echo ;;
- echo hi";" hihi
- echo hi " ; " hihi
- cd
- cd .
!
- cd ~
- cd /
- cd no_file
! another message but the idea is the same
- cd a b c d
- pwd a
- pwd a b c d
! second varialbe is not exported ONLY in my case!!!!!!!!!
- export LOL=lala ROR=rara
- unset LOL ROR
- export "HI= hi"
!
- export "HI =hi"
- /bin/ls
!  only in my case !!!!!!!!!!!!!
- "write something the press ctrl+c"
- "write something then press ctrl+d"
!
- "write something then press ctrl+\"
- echo $?
- |^Ds
! it is somwhere in the subj: pipe should not stay alone
- echo |
! it is somwhere in the subj: pipe should not stay alone
- | echo
! sorts, outputs but does not retuns to promt.
- sort | ls # check output order
- cat < >
- cat < <
- cat > >
- > a ls > b < Makefile
- echo > a Hello World!
- > a echo Hello World!
- cat < Makefile | grep gcc > output
!
- exit 0 | exit 1
- exit 1 | exit 0

# Please make sure to do a lexer -> parser -> expander -> executor to make your life easier. Here is a solid start:
https://harm-smits.github.io/42docs/projects/minishell
