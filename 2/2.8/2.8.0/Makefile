# 2.8 ライブラリ管理
#
# ## ライブラリ管理
#
# ・アーカイブライブラリ = メンバという他のファイルを内包している形式のファイル
# ・関連するオブジェクトファイルをまとめる
# ・makeは、ライブラリの作成、保守、参照するための機能を提供する
# ・アーカイブの作成や変更はarコマンドを使う
# ・まずはソースからcount_wordsを作成するMakefileを書く

VPATH = src include
CPPFLAGS = -I include

SOURCES = count_words.c \
		  lexer.c       \
		  counter.c

count_words: counter.o lexer.o -lfl
count_words.o: counter.h
counter.o: counter.h lexer.h
lexer.o: lexer.h

include $(subst .c,.d,$(SOURCES))

%.d: %.c
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$;                    \
	sed 's, \($*\)\.o[ :]*, \1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY: clean
clean:
	rm *.o *.d *.c count_words


# ・`make`で実行可能形式を作成する
# ・再利用可能な単語カウントライブラリを作成する
# ・arコマンドを使う
#
# ```
# $ ar rv libcounter.a counter.o lexer.o
# ```
#
# ・rv: リストされたオブジェクトでアカイブのメンバを置き換える＆詳細出力
# ・置き換えオプションを使うことでアーカイブの作成や更新を順次行うことができる
# ・追加の場合は、出力の行頭にaが、置き換えの場合はrが付く
# ・ライブラリはいくつかの方法で実行形式のファイルとリンクできる
#     - コマンドラインで指定
#     - サフィックスからライブラリと判断し処理してくれる
#     - cc count_words.o libcounter.a /lib/libfl.a -o count_words
#     - -lオプションを使うと、libプレフィックスとサフィックスが要らない
#     - また、標準ライブラリのディレクトリから自動的に探してくれる
#     - cc count_words.o -lcounter -lfl -o count_words
#     - リンカやコンパイラの既定動作
#     - -Lオプションで、検索ディレクトリを指定できる
#         - 指定されたディレクトリはシステムライブラリディレクトリの前に置かれる
#         - カレントディレクトリにライブラリがある場合は `-L.` を付ける必要がある
# ・ライブラリはプログラムの構築を複雑化する
# ・makeはどうやって簡単にするのか
