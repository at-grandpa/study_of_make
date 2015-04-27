# 1.4 makeの実行
#
# 今までは暗黙に以下のルールがあった
#
# ・全てのソースコードとMakefileが１つのディレクトリにあった
# ・makeのルールを記述したファイルは makefile, Makefile, GNUMakefile のいずれか
# ・makeを実行したディレクトリに、makeのルールを記述したファイルが存在する
#
# makeの流れ再び
#
#  1. makeが実行されると、ターゲットを特定する
#  2. ターゲット or 必須項目が古かったら、コマンドを実行して生成する
#  3. コマンドを実行し終えたら、makeは終了する
#  4. ターゲットが存在しない場合は、エラーを表示して終了する

count_words: count_words.o lexer.o -lfl
	gcc count_words.o lexer.o -lfl -ocount_words

count_words.o: count_words.c
	gcc -c count_words.c

lexer.o: lexer.c
	gcc -c lexer.c

lexer.c: lexer.l
	flex -t lexer.l > lexer.c
