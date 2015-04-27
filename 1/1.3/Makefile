# 1.3 再構築作業を最小にする
#
# 現状のcount_wordsは、指定文字意外の文字列が出力されている
# これは望ましくないので修正する
#
# 修正したらmake
# 再構築される
#
# ```
# $ make
# flex -t lexer.l > lexer.c
# gcc -c lexer.c
# gcc count_words.o lexer.o -lfl -ocount_words
# ```
#
# count_words.cが再コンパイルされない
#   -> count_words.oが既に存在している
#   -> count_words.oがcount_words.cよりも新しい
# lexer.cは再生成される
#   -> lexer.cよりもlexer.lの方が新しかったため
#
# こうして、押し出されるように count_words が更新された

count_words: count_words.o lexer.o -lfl
	gcc count_words.o lexer.o -lfl -ocount_words

count_words.o: count_words.c
	gcc -c count_words.c

lexer.o: lexer.c
	gcc -c lexer.c

lexer.c: lexer.l
	flex -t lexer.l > lexer.c
