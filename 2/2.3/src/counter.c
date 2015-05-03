#include <lexer.h>
#include <counter.h>

// ライブラリ化のため、mainの一部を関数化
void counter ( int counts[4] )
{
    while( yylex() );

    counts[0]= fee_count;
    counts[1]= fie_count;
    counts[2]= foe_count;
    counts[3]= fum_count;
}
