# Handmada - eQueue (version 1.0 - release) #
Pretends to be a client-server program.

## Participants ##
* **Users** can add their attributes and book services.
* **Administrators** can add new services, specialists and priority rules.
* **Server** (a non-playable one) just processes the requests sent by clients.

## Platform dependencies ##
The project is written for Unix and makes extensive (okay, not so extensive)
use of Unix low-level libraries.
Therefore, I guess, it should be run by Unix systems, 
although it's possible that the program can be run on Windows with Cygwin.

Please keep in mind, that embedded Makefile will try to launch **valgrind**.
If **valgrind** is not available on your system, just replace **valgrind**-aware recipes
with "non-**valgrind**" ones.

That is, the following recipes:

    user: semiuser
        valgrind bin/User localhost 50000
        
    admin: semiadmin
        valgrind bin/Admin localhost 50000
    	
    server: semiserver
        valgrind bin/Server 50000

should be replaced with these ones:

    user: semiuser
        bin/User localhost 50000
            
    admin: semiadmin
        bin/Admin localhost 50000
        	
    server: semiserver
        bin/Server 50000
    

## Installation and launch ##
If you are lucky, the embedded Makefile will setup the whole system on his own.
If you are not, you will have to rebuild **Google Test Framework** library 
(i.e. **gtest_main.a**) which is used
by this project. This depends on the Unix version you are using. 
You can also just skip this step if you're not going to run tests.

Upon project files unpacking type the command:

    make
    
in case you are really interested in this endless list of **RUN - OK** statements
produced by **Google Test Framework**.

If you are not, just type

    make build
    
to build the whole project and, after that, type

    make server
    make admin
    make user
    
*Please note:* use **separate** terminal windows for these commands in order to run
*server*, *admin* and *user* simultaneously! You are also not limited to only one *user* or
*admin* process, feel free to run as many as you want.

*Please note:* it's not recommended to start the program **manually**, i.e by typing

    cd bin
    ./Server
    
In case you do it, there is a chance the program won't be able to find dump-files directory.

## After launch ##
If you're using *user*/*admin* console, you're able to interact with the system by typing
commands from a predefined list. Keep in mind, that *user* will get the complete list only after
**signing in**. You will be able to see your login in the prompt when you are signed in. 
*Administrators* don't have to sign them up/in.
A typical session for not registered users looks like this:

    :\> sign up kunsar
    :\> sign in kunsar
    kunsar:\>

Please, don't forget to type

    help
    
in program's console to see the list of available commands and their usages.

*User*/*Admin* sessions can be closed with **exit** command. 
*Server* can be stopped by pressing **Ctrl+C** 
(or whatever combination that produces **SIGINT** signal on your machine).
***Don't confuse them! Otherwise valgrind will punish you for your crimes against the Earth!***

## Why can I undo only attribute related requests? ##
Because undo-mechanism was introduced only for demonstration purposes.
The whole project is just a kind of demo and therefore there is a certain
lack of functionality.
However, since the author is not interested in this project anymore,
please, don't expect the missing functionality will be added in future.


## Priority rules syntax ##
The priority rule syntax is very simple and straightforward.
The simplest possible rule looks like this:

    age > 18

and obeys the following structure:

    identifier operation literal
    
*Identifier* should be started with a lowercase letter. Spaces inside identifiers are forbidden.
If you need a complex name, you can link words together using **camelCase**
or **under_score_naming_style**. You can even **mixThe_styles**.

*Operation* can be one of these:

    > < >= <= == !=
    
Keep in mind that **string** and **boolean** attributes support only equality and inequality tests.
However a parser will remind you if you forget.

*Literal* is a kind of constant. It can be of **string**, **number** (i.e. double) and **boolean**
type. **String** literals should be enclosed in quotes, **boolean** literal can be
either **yes** or **no**. There is a list of valid literals:

    "goto statement considered helpfull"    // string
    47                                      // number
    -137.42                                 // number too
    yes                                     // boolean

The embedded parser is smart enough to deduce the type of entered attribute.

The basic priority rules (if you're looking through a code, 
they are called **ComparisonPredicate**'s)
can be combined with logical operations and can also be enclosed by parentheses.
Logical operation denotes in the same way as in C language. The following example illustrates
a complex priority rule:

    university == "MSU" || job == "programmer" || !(hasMoneyAndPower == no)
