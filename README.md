# Gitcy: Functionnal programming language
## Gitcy: Gitcy Isn't Turing Complete Yet

```
(define expand-acronym
	(function acronym
		(if (= acronym "Gitcy")
			(for (word "Gitcy Isn't Turing Complete Yet")
				(expand-acronym word)
			)
		)
	)
)
(expand-acronym "Gitcy")

```
Would result in a stack overflow if the function `word` where defined.
