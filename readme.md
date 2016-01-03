# Apply C++ Project

15Y1227 p.37
15Y1229 p.56
16Y0103 p.58

## For doxygen
`
doxygen -g
// edit DoxygenFile
doxygen -u
doxygen
`

## vim 
### moving
`
w/b, W/B
0/$
<C-D/U>, <C-B/F>
`

## ctags
`	
ctags -R
:set tags=./tags
<C-]> or <C-t>
tj <symbol>
`

## cscope
`
mkscope.sh
:cs add ./cscope.out
:cs find <f> <main>
`
