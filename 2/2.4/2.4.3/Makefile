# 2.4.3 サフィックスルール
#
# ## サフィックスルール
#
# ・旧式の機能
#     - GNU make のパターンルールをサポートしていないmakeも存在するから
#     - この機能を理解することは重要
#
#
# ## サフィックスルールの文法
#
# ・２つのサフィックスが連結してターゲットに置かれる

all: foo.o

.c.o:
	$(COMPILE.c) $(OUTPUT_OPTION) $<

# ・これは以下のルールと同じ
#
# ```
# %.o: %.c
#	$(COMPILE.c) $(OUTPUT_OPTION) $<
# ```
#
# ・必須項目のサフィックスが前で、ターゲットのサフィックスが後（ややこしい！）
# ・２つのサフィックスがmakeにとって既知である場合に正しく認識される
# ・上記の例は、サフィックスが２つなので「ダブルサフィックスルール」という
# ・「シングルサフィックスルール」もある
#
# ```
# .p:
#	$(LINK.p) $^ $(LOADLIBS) $(LDLIBS) -o $@
# ```
#
# ・これは以下と同じ
#
# ```
# %: %.p
#	$(LINK.p) $^ $(LOADLIBS) $(LDLIBS) -o $@
# ```
#
# ・.pファイルがあれば、そこから実行ファイルを作成するルール
#
#
# ## makeの知っているサフィックス
#
# ・makeの知っているサフィックスは、 .SUFFIXES に入っている
# ・以下は、デフォルトで入っているサフィックス
#
# ```
# .SUFFIXES: .out .a .ln .o .c .cc .C .cpp .p .f .F .r .y .l
# ```
#
# ・ここに追加することで、独自のサフィックスを読み込ませることができる
#
# ```
# .SUFFIXES: .pdf .fo .html .xml
# ```
#
# ・（衝突などがあり）既知のサフィックスを無効にしたいなら、以下を記述
#
# ```
# .SUFFIXES:
# ```
#
# ・同じことは、コマンドラインオプション --no-buildin-rules (-r) を使っても良い
#
# makeのhelpより
#
# ---------------
#   -r, --no-builtin-rules      Disable the built-in implicit rules.
#     - 暗黙ルールを無効にしてビルド
#   -R, --no-builtin-variables  Disable the built-in variable settings.
#     - 変数を無効にしてビルド
# ---------------

.PHONY: clean
clean:
	rm *.o
