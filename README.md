# Problem : Create a tool to communicate with computers In the context of a 42-school project, we are asked to build our minishell. 

## Lexical Analysis :

- The process of splitting the input string into a stream of tokens. This is also called the lexer. The lexer needs to recognize each token and associate its correct type.

- Let's take some examples to understand this point :
`
	--> Input : "echo 'hello world'"
	--> Output :
			{ 
			 { Token : echo, Type : command  },
			 { Token : 'hello world', Type : argument}
			}
`
- In this case, we used an array, but in our implementation, we used a data structure known by simply linked lists. 

## Parsing Process :

- The process of parsing evolves taking a tokens stream, which is represented using a simple linked list. Then, we move on to iterating over this stream, and based on the type of the token we proceed parsing, in other words, constructing an AST (Abstract Syntax Tree).

- For a simple command like `echo "hello world"`, the syntax tree would look something like this : 
	
			"hello world" // right side child node
		echo 
			(null) // left side child node

- In case we have more than one argument, we proceed the following way : 

						"\n"
					"hey"
			"hello world"
		echo 
			"hi"

- So, the order of which the AST was constructed using is we fill in the right child node, and then the left child node and then keep filling the mostright child nodes of the first right child node. I hope you understand!

- During the lexical analysis part, we defined a set of TOKEN TYPES that we used to recognize each token. Similarly, when parsing, we have to consider the NODES TYPES.

	`
		enum {
			NODE_COMMAND, 
			NODE_ARGUMENT,
			NODE_PIPELINE,
			NODE_REDIRECTION_OUT,
			NODE_REDIRECTION_IN,
			NODE_REDIRECTION_APPEND,
			NODE_REDIRECTION_HEREDOC
		};
	`

### Parsing Redirection Characters :

1. '>' : output redirection
	- This type of redirection requires a command and a taget attached to it.		
	- After parsing, let's take as an example, a simple commnd like ls -al > file.txt, the AST should look something like this : 
  
	  
			`			------> -al
				----> ls ---->
   					  	------> null
  			> ---->
  
   				-----> file.txt
   			`
2. '>>' : appending commands output
3. '<' : Input redirection
4. '<<' : Here Document


### Execution :

	For this part, we'll need to traverse the AST in a manner we keep the right order of the command (simple or complex), and then print out the result.
