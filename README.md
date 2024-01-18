notes:

	- strcmp in both search functions in search.c is gating us from a case-insensitive search.
	  There is a strncasecmp() function for that purpose. And using strcmp() in the first place
	  is false, cuz we want to have the option to compare with the compare function given as 
	  parameter. But use strncasecmp() maybe in the sort_description() method.
	- Ima be honest the file creating function in database.c is a bit crippled since for my
	  teacher on windows the constants F_OK/EEXIST aren't defined while they are for me, should
	  perhaps be changed.
	  