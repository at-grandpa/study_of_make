# 2.2.1 自動変数
#
# ## 自動変数とは
#
# ・$@ や $< などの変数
# ・実行するルールが決まった後にmakeにより設定される
#     - よって、使用できるのはコマンド行のみ
#     - ルール決定後はコマンドが実行されるため
# ・これらを設定すると、ファイル名を明示的に指定しなくて済む
# ・ターゲットや必須項目リストのを完結に書けるし、間違わなくて済む
# ・汎用のパターンルールで使用すると危険な点がある
#
#
# ## 主な自動変数
#
# $@ : ターゲットのファイル名
# $% : ライブラリの構成指定中の要素
# $< : 最初の必須項目のファイル名
# $^ : 全ての必須項目をスペースで区切ったリスト（uniq処理済）
# $+ : 全ての必須項目をスペースで区切ったリスト（重複含む）
# $* : ターゲットファイル名の一部（サフィックスを除いたファイル名）
#
#
# ## GNU make だけでなく、他のmakeとの互換性を持たすための拡張形
#
# 1. 値のディレクトリ部分を返すには、Dを挟む
#      ex) $(@D) $(<D)
# 2. 値のファイル部分を返すには、Fを挟む
#      ex) $(@F) $(<F)
#
# ** １文字以上になるので、括弧が必要
#
#
# ## count_wordsのMakefileの修正前
#
count_words_old: count_words_old.o lexer_old.o -lfl
	gcc count_words_old.o lexer_old.o -lfl -ocount_words_old

count_words_old.o: count_words_old.c
	gcc -c count_words_old.c

lexer_old.o: lexer_old.c
	gcc -c lexer_old.c

lexer_old.c: lexer_old.l
	flex -t lexer_old.l > lexer_old.c

# ## count_wordsのMakefileの修正前
#
count_words: count_words.o lexer.o -lfl
	gcc $^ -o $@

count_words.o: count_words.c
	gcc -c $<

lexer.o: lexer.c
	gcc -c $<

lexer.c: lexer.l
	flex -t $< > $@
