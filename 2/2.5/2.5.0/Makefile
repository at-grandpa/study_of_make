# 2.5.0 暗黙ルールのデータベース
#
# ## 組み込み暗黙ルール
#
# ・暗黙ルール = パターンルール or サフィックスルール
# ・パターンルールはいろんな言語に対応
# ・各言語の補助ツールにも対応
# ・対応していない言語の場合は、自分で暗黙ルールを記述する
#     - 簡単なルールの記述で済む
#
#
# ## 組み込み暗黙ルールの確認
#
# ```
# make --print-data-base (-p)
# ```
#
# 一部抜粋
#
# ```
# %.o: %.c
# #  commands to execute (built-in):
# in$(COMPILE.c) $(OUTPUT_OPTION) $<
#
# %.cc:
#
# %: %.cc
# #  commands to execute (built-in):
#     $(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@
# ```
#
# -pオプションにMakefileを指定すると、Makefileに定義されたルールも出力する
# この時、どのMakefileの何行目に定義されているかも出力される

%.html: %.xml
	$(XMLTO) $(XMLTO_FLAGS) html-nochunks $<

# 試しに、このMakefileを指定して-pオプションを実行してみる
#
# ```
# %.html: %.xml
# #  commands to execute (from `Makefile', line 36):
#         $(XMLTO) $(XMLTO_FLAGS) html-nochunks $<
# ```
