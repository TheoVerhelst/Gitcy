# Gitcy: Functionnal programming language
## Gitcy: Gitcy Isn't Turing Complete Yet

```
(define expand-acronym
	(function (acronym)
		(for (word (apply expand-letter acronym))
			(if (is-acronym word)
				(expand-acronym word)
				word
			)
		)
	)
)
(expand-acronym "Gitcy")

```
Will result in a stack overflow when Gitcy will be Turing Complete.
