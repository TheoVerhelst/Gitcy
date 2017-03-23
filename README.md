# Gitcy: Functionnal programming language
## Gitcy: Gitcy Isn't Turing Complete Yet

```
(define expand-acronym
	(function (acronym)
		(if (= acronym "Gitcy")
			(for (word "Gitcy Isn't Turing Complete Yet")
				(expand-acronym word)
			)
		)
	)
)
(expand-acronym "Gitcy")

```
Will result in a stack overflow when Gitcy will be Turing Complete.
