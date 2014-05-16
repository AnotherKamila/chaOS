divert(-1)
# pp_forloop(i, from, to, stmt)

define(`pp_forloop', `pushdef(`$1', `$2')_pp_forloop(`$1', `$2', `$3', `$4')popdef(`$1')')
define(`_pp_forloop',
       `$4`'ifelse($1, `$3', ,
			 `define(`$1', incr($1))_pp_forloop(`$1', `$2', `$3', `$4')')')
divert
