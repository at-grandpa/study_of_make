# 2.4.0 パターンルール
#
# ## 前までのMakefile
#
# ・冗長
# ・コマンドが重複している
# ・変更があったらかなり直さなければいけない
#
#
# ## 標準的な慣例を用いる
#
# Cコンパイラ：
# ・.cサフィックスはソースコード
# ・オブジェクトファイル名は.cを.oに置き換えたもの
# ・flexの例では、.lファイルから.cファイルを生成した
#
#
# ## 組み込みルールを用いて、慣例を適用する
#
# 組み込みルールを用いると、makefileは以下のようになる
#

VPATH = src include
CPPFLAGS = -I include

count_words: counter.o lexer.o -lfl
count_words.o: counter.h
counter.o: counter.h lexer.h
lexer.o: lexer.h

#
# ## 組み込みルール
#
# 組み込みルールはパターンルールで作成されている
#
# パターンルール：
# ・ファイル名の本体部分が % で表されているルール
#
#
# ## 今回使われた組み込みルール
#
# 1. .cファイルをコンパイルして.oファイルを作成
# ```
# %.o: %.c
#     $(COMPILE.c) $(OUTPUT_OPTION) $<
# ```
#
# 2. .lファイルから.cファイルを作成
# ```
# %.c: %.l
#     @$(RM) $@
#     $(LEX.l) $< > $@
# ```
#
# 3. サフィックスを持たないファイルを作り出す特別なルール
# ```
# %: %.o
#     $(LINK.o) $^ $(LOADLIBS) $(LDLIBS) -o $@
# ```
#
#
# ## makeの出力を元に動作を追ってみる
#
# ```
# cc  -I include  -c -o count_words.o src/count_words.c
# cc  -I include  -c -o counter.o src/counter.c
# lex  -t src/lexer.l > lexer.c
# cc  -I include  -c -o lexer.o lexer.c
# cc   count_words.o counter.o lexer.o /usr/lib/i386-linux-gnu/libfl.so   -o count_words
# rm lexer.c
# ```
#
#  1. makefileを読み込む
#  2. コマンドラインにターゲットが指定されていないので、count_wordsをデフォルトターゲットとする
#  3. 必須項目が4つだと特定する（count_words.oは暗黙ルールで追加される）
#  4. これらの必須項目を順に更新する
#  5. count_words.oを調べる
#  6. カレントディレクトリにファイルが存在しないのでVPATHのディレクトリを調べる
#  7. それでもcount_words.oというファイルは存在しないので、ルールを探索する
#  8. ルールが書いてある
#  9. ルールはコマンドも無いし、一見不備に思えるが、暗黙ルールが適用できる
# 10. 上記に書いた %.o のパターンルールに則る
# 11. パターンルールより、count_words.cが必須項目になる
# 12. 必須項目count_words.cは、VPATH設定のsrcディレクトリにある
# 13. count_words.cの必須項目はOK
# 14. count_words.oの必須項目はもうひとつ、counter.hが必要
# 15. これもVPATH設定のincludeディレクトリにある
# 16. よって、count_words.oの必須項目が揃った
# 17. コマンドも、暗黙ルールに設定されているものになる
# 18. これで、count_words.oの更新が可能になった
# 19. counter.o, lexer.oも同じような流れでOK
#
# ターゲットを更新するような一連の流れを「ルール連鎖」という
# 中間ファイルも最後は消してくれる
#
#
# ## デフォルトの組み込みルールの確認方法
#
# ```
# $ make --print-data-base
# ```
