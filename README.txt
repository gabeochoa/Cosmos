Gabriel Ochoa CMS
An electronic platform for trading commodities contracts

base program and extensions one implemented

Design:

All userinput is passed through a recursive descent parser for validation and then gets passed to our single processor. 

The processor breaks down the commands and handles the interface with our 'database'.

While running the database logs all output and passes it back up to the processor which in turn passes it back up for output to the user. 

no known bugs, but please inform me if any are found. 

**More Info in README.md**