# 2.3 VPATHとvpathによるファイル検索
#
# ## 関数を切り出してライブラリ化
#
# 今までのMakefile
#
# ```
# count_words: count_words.o lexer.o -lfl
#     gcc $^ -o $@
#
# count_words.o: count_words.c
#     gcc -c $<
#
# lexer.o: lexer.c
#     gcc -c $<
#
# lexer.c: lexer.l
#     flex -t $< > $@
# ```
#
# 今後は、ソースファイル（*.c, *.l）はヘッダーファイルを持つ
# ヘッダーファイルが更新されたら、ソースファイルをコンパイルする
# その依存関係を記述する
#
# ```
count_words: count_words.o counter.o lexer.o -lfl
	gcc $(CPPFLAGS) $^ -o $@

count_words.o: count_words.c include/counter.h
	gcc $(CPPFLAGS) -c $<

counter.o: counter.c include/counter.h include/lexer.h
	gcc $(CPPFLAGS)  -c $<

lexer.o: lexer.c include/lexer.h
	gcc $(CPPFLAGS)  -c $<

lexer.c: lexer.l
	flex -t $< > $@
# ```
#
# この状態でmakeすると、
#
# make: *** No rule to make target `count_words.c', needed by `count_words.o'.  Stop.
#
# count_words.oの生成に必要なcount_words.cのターゲットが無い。
#
# 順を追って行く。
#
#  1. 最初のターゲットは count_words.o
#  2. そのファイルが見当たらないので、作成するためのルールを探す
#  3. ルールがある
#  4. そのルールの必須項目は count_words.c
#  5. makeはカレントディレクトリを探すが、存在しない
#  6. count_words.c は src/ に存在する
#  7. makeは何もしなければ、カレントディレクトリのみからターゲットや必須項目を探す
#  8. makeにソースコードの場所を教えてあげるにはどうすればよいのか
#
#
# ## VPATH or vpath で探索するディレクトリを追加
#
# ```
VPATH = src
# ```
#
# カレントディレクトリにファイルが存在しなければ、ここを探すようになる
# これを加えてmakeを実行すると、
#
# ```
# gcc -c src/count_words.c
# src/count_words.c:3:21: fatal counter.h: No such file or directory
#  #include <counter.h>
#                     ^
# compilation terminated.
# make: *** [count_words.o] Error 1
# ```
#
# 最初のコンパイルは、srcのパスを通したおかげでできた
# （ファイル名をハードコードすると、この部分の正しいパスが扱えない）
# gccがヘッダファイルを見つけられなかったので失敗した
# 解決するためには、gccに -I オプションを付けてコンパイルする
# gccには CPPFLAGS という変数が用意されているので、それを加える
#
# ```
CPPFLAGS = -I include
# ```
#
# gcc も gcc $(CPPFLAGS) に変更する
#
#
# ## VPATHの説明
#
# VPATH は、 makeがファイルを探すディレクトリのリスト
# 必須項目とターゲットを探す際に使われる
# コマンドスクリプトに書かれているファイルには無効
# リストの羅列は空白かコロンで行う
#
#
# ## VPATHの注意点
#
# makeの、VPATHを使った探索方法は、「各ディレクトリにファイルがあるか探す」
# そのため、複数のディレクトリに同名のファイルが存在した場合、最初にマッチしたファイルを使う
# この点は注意しなくてはならない
#
#
# ## vpath命令
#
# vpath命令のSyntax
#
# ```
# vpath pattern directory-list
# ```
#
# 今回のVPATHの記述をvpathで書くと以下になる
#
# ```
# vpath %.c src
# vpath %.l src
# vpath %.h  include
# ```
#
# より細かく設定できる
#
