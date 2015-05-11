# 2.8.1 ライブラリの作成と更新
#
# ## ライブラリの作成と更新
#
# ・makeではライブラリも他のファイルと同じように扱う

libcounter.a: count_words.o lexer.o
	$(AR) $(ARFLAGS) $@ $^

# ・組み込みの定義で ARにはarコマンドが、ARFLAGSにはrvが入っている
# ・count_wordsの必須項目にlibcounter.aを追加すると、実行形式の作成前にライブラリを更新する
# ・これはちょっとまずい時がある
# ・このケースの場合、更新の有無に限らず、全てのメンバが置き換わる
# ・もうちょっと良い方法がある

libcounter_02.a: count_words.o lexer.o
	$(AR) $(ARFLAGS) $@ $?

# ・$?: ターゲットより後の更新された必須項目のリスト
#
#
# ## さらに改善できるか？
#
# ・ライブラリの構築手順に注目してみる
# ・makeの主たる目的: 更新すべきファイルだけを処理することで効率化を図る
# ・更新すべきメンバ全てでarコマンドを実行するのはエレガントではないし、コストがかかる
# ・上述のようなarを明示的に実行するような形式にしておけば、各ファイルで１回だけ実行すれば良くなる
# ・多くの環境で、arのrオプションは効率的ではない
# ・余り多いと、最初から構築したほうが早い
# ・結局$?での更新も、ちょっと考えたほうが良い
# ・以下の方法が良い
# ・アーカイブのメンバの参照方法
#
# ```
# libgraphics.a(bitblt.o): bitblt.o
#     $(AR) $(ARFLAGS) $@ $<
# ```
#
# ・括弧内は、その前に書かれているライブラリのメンバを表す
#     - この場合は、ライブラリ名libgraphics.a、メンバ名bitblt.o
# ・$<は、必須項目の最初のものを取り出す
#
#
# ## 全てを考慮したMakefile
#

VPATH = src include
CPPFLAGS = -I include

.PHONY: all
all: count_words

count_words: libcounter.a /usr/lib/i386-linux-gnu/libfl.a

libcounter.a: libcounter.a(lexer.o) libcounter.a(counter.o)

libcounter.a(lexer.o): lexer.o
	$(AR) $(ARFLAGS) $@ $<

libcounter.a(counter.o): counter.o
	$(AR) $(ARFLAGS) $@ $<

count_words.o: counter.h
counter.o: counter.h lexer.h
lexer.o: lexer.h


.PHONY: clean
clean:
	rm *.o *.d *.c *.a count_words

#
# ・ターゲットとしてlibcounter.a(counter.o)と記述されていても、$@はライブラリ名を返す
#
#
# ## シンボルのインデックス
#
# ・アーカイブライブラリは収容しているシンボル（ファイル？）のインデックスを持っている
# ・最近のアーカイブプログラムは、モジュールの新規追加の際、自動的にindexを作成する
# ・昔のプログラムではそうはいかない
# ・その場合、以下のルールが必要となる
#
# ```
# libcounter.a: libcounter.a(lexer.o) libcounter.a(counter.o)
#     $(RUNLIB) $@
# ```
#
# ・別の手段
#
# ```
# libcounter.a: lexer.o counter.o
#     $(RM) $@
#     $(AR) $(ARFLAGS) $@ $^
#     $(RUNLIB) $@
# ```
#
# ・GNU make はアーカイブを更新する組み込みルールを提供している
# ・例のMakefileは以下になる
#
# ```
# VPATH = src include
# CPPFLAGS = -I include
#
# .PHONY: all
# all: count_words
#
# count_words: libcounter.a -lfl
# libcounter.a: libcounter.a(lexer.o) libcounter.a(counter.o)
# count_words.o: counter.h
# counter.o: counter.h lexer.h
# lexer.o: lexer.h
# ```
