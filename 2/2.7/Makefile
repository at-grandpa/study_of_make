# 2.7 自動的な依存関係の生成
#
# ## 自動的な依存関係の生成
#
# ・プログラムで自動的に依存関係を特定し、makeの文法で出力する
# ・間違いがないし、簡単
# ・C, C++ にはそういう機能がすでに存在する
# ・しかも、makeの文法で出力してくれる
#
# ```
# $ echo "#include <stdio.h>" > stdio.c
# $ gcc -M stdio.c
# stdio.o: stdio.c /usr/include/stdc-predef.h /usr/include/stdio.h \
#  /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
#  /usr/include/i386-linux-gnu/bits/wordsize.h \
#  /usr/include/i386-linux-gnu/gnu/stubs.h \
#  /usr/include/i386-linux-gnu/gnu/stubs-32.h \
#  /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
#  /usr/include/i386-linux-gnu/bits/types.h \
#  /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
#  /usr/include/_G_config.h /usr/include/wchar.h \
#  /usr/lib/gcc/i686-linux-gnu/4.8/include/stdarg.h \
#  /usr/include/i386-linux-gnu/bits/stdio_lim.h \
# ```
#
# ・これで作業は楽になったが、コピペしないといけない
# ・自動で取り込む方法が２つある
# ・1:シェルスクリプトで書き換える
#
# ```
# # 以下は自動生成された依存関係 - 変更不可
# ```
#
# ・このような文章をMakefileに書き込み、この部分を書き換えるシェルスクリプトを作成する
# ・2:makeのinclude命令を使用する
# ・全てのファイルに対して、gccを-Mオプションで実行するターゲットを作成し、その結果をファイルに保存するようにする
# ・makeを再実行し、ファイルをincludeする
# ・コード例
#
# ```
# depend: count_words.c lexer.c counter.c
#     $(CC) -M $(CPPFLAGS) $^ > $@
#
# include depend
# ```
#
# ・プログラム構築の前に、make depend を実行する必要がある
# ・これを忘れがち
# ・しかし、各ファイルの依存関係をそれぞれ.dサフィックスをつけてファイル化し、ソースファイルの依存関係ルールにターゲットとして置く
# ・そうすれば、.cなどのソースが更新された際、.oはもちろんのこと、.dも更新んしなければならないことを知ることができる
# ・.dファイルの更新ルールはパターンルールを用いて、以下のように書く
#
# ```
# %.d: %.c
#    $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
#    sed 's, \($*\)\.o[ :]*, \1.o $@ : ,g' < $@.$$$$ > $@; \
#    rm -f $@.$$$$
# ```
#
# ・Makefile内の「$$」は、シェルでの「$」に相当する
#     - Makefileでの$$$$ = シェルでの $$
# ・シェルでの$$は、現在実行しているシェルのプロセス番号
# ・この過程で、独自のファイル名が作成される
# ・sedは以下の様な置換をしている
#     - stdio.o: ->  stdio.o stdio.d :
#     - 依存関係のターゲットに.dファイルを追加している
#         - .cファイルと.hファイルが更新されたら、.dファイルも更新しないといけないので
# ・これで、依存ファイルのターゲットの更新を追加できる
# ・makeの挙動で忘れてはならないこと
#     - makeはルールを構築してから、デフォルトターゲットのルールを起点として、ルール連鎖を行う
#     - 同じ依存関係を持つターゲットが複数あった場合、どちらが先に実行されるか、という疑問はおかしい
#     - makeは上から実行するのではない
#     - makeは必須項目の更新があったら、各ターゲットを同時に更新するのではない
#     - あくまでルールを構築してから、デフォルトターゲットを起点に動き出す
# ・もう一つのmakeの機能は、includeされたファイルを「更新すべきターゲット」として扱うこと
# ・.dファイルをincludeすると、.dファイルを更新してくれる
#
#
# ## 自動依存関係生成機能つきMakefile

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

# ・デフォルトターゲットが依存関係ファイル内のルールに置き換わらないように、includeは後に置くべき
# ・include命令にはファイルのリストを渡すことができる
# ・$(subst .c,.d,$(SOURCES)) は、.cを.dに書き換える文字列処理
# ・--just-print (-n) で実行すると、以下の出力
#
# ```
# $ make -n
# Makefile:93: count_words.d: No such file or directory
# Makefile:93: lexer.d: No such file or directory
# Makefile:93: counter.d: No such file or directory
# cc -M -I include src/counter.c > counter.d.$$;                    \
# 	sed 's, \(counter\)\.o[ :]*, \1.o counter.d : ,g' < counter.d.$$ > counter.d; \
# 	rm -f counter.d.$$
# lex  -t src/lexer.l > lexer.c
# cc -M -I include lexer.c > lexer.d.$$;                    \
# 	sed 's, \(lexer\)\.o[ :]*, \1.o lexer.d : ,g' < lexer.d.$$ > lexer.d; \
# 	rm -f lexer.d.$$
# cc -M -I include src/count_words.c > count_words.d.$$;                    \
# 	sed 's, \(count_words\)\.o[ :]*, \1.o count_words.d : ,g' < count_words.d.$$ > count_words.d; \
# 	rm -f count_words.d.$$
# rm lexer.c
# cc  -I include  -c -o count_words.o src/count_words.c
# cc  -I include  -c -o counter.o src/counter.c
# cc  -I include  -c -o lexer.o lexer.c
# cc   count_words.o counter.o lexer.o /usr/lib/i386-linux-gnu/libfl.so   -o count_words
# ```
#
# ・最初のエラーっぽいものはただの警告
# ・include命令の前にマイナス記号を付けることで非表示にできる
# ・ちゃんと gcc -M で実行し、sedで依存関係ファイルを作成している

.PHONY: clean
clean:
	rm *.o *.d *.c count_words
