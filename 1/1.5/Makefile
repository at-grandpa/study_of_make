# 1.5 makefileの基本文法
#
# ここまでで、makeの基礎の9割くらいを押さえた
# ここでは残りの部分を学ぶ
#
# # makeはトップダウンの構造
#
# ・先頭にある all というターゲットの動作が一般的
# ・その他、プログラムの保守のための clean などがある
# ・ターゲットは実際のファイルである必要はない
#
# # より詳細なmakeのルール構文
#
# ```
# target1 target2 target3 : prerequisite1 prerequisite2
#     command1
#     command2
#     command3
# ```
#
# ・必須項目が無い場合は、ターゲットの中で存在しないものだけが構築される
# ・このルールからは３つのターゲットが生成される
#
# # タブ
#
# ・commandはタブの後に置かれる
# ・タブの後じゃないと、commandとして認識されない
# ・タブの後ろにあるcommandをサブシェルに渡す
#
# # コメントやバックスラッシュ
#
# ・「#」以降がコメント
# ・長いコマンドは「\」で継続することができる

count_words: count_words.o lexer.o -lfl
	gcc count_words.o lexer.o -lfl -ocount_words

count_words.o: count_words.c
	gcc -c count_words.c

lexer.o: lexer.c
	gcc -c lexer.c

lexer.c: lexer.l
	flex -t lexer.l > lexer.c
