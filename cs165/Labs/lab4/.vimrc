filetype on
filetype plugin on
filetype indent on
autocmd FileType c,cpp set cindent “This allows for c-like indentation
set sw=3 “Set the sw for the auto indent to 3 spaces
set number “Show the line numbers on the left
“
Change the color of the text and turn on syntax highlighting
“
color desert
color torte
colorscheme evening
syntax on “Turn on syntax highlighting
set showmatch “Show matching braces
set showmode “Show current mode
“
When one of the chars is typed, the matching is typed and the cursor moves left
inoremap ' ''<Left> “These are all SINGLE QUOTES
inoremap " ""<Left> “These are all DOUBLE QUOTES
inoremap { {}<Left>
inoremap ( ()<Left>
