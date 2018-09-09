# Gitcy: Functionnal programming language
## Gitcy: Gitcy Isn't Turing Complete Yet

```

(function expand-acronym acronym
	(if (= acronym "Gitcy")
		(for (split "Gitcy Isn't Turing Complete Yet")
			(expand-acronym word)
		)
	)
)
(expand-acronym "Gitcy")

```
Would result in a stack overflow if the function `split` where defined.
