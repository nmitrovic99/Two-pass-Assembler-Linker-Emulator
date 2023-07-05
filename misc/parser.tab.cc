/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "misc/bison.y"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "lex.yy.h"
#include "../inc/assembler/handler.hpp"

extern int yylineno;
void yyerror(const char *);
Handler h;
std::string symbol_name;
std::string symbol_value;
std::vector<std::string> symbol_name_list;
int literal;
int literal_value;
std::vector<int> literal_list;
std::vector<int> kind_list;
int symbol_or_literal;
int symbol_or_literal_value;
std::string gpr1, gpr2;
std::string csr;
int operand_data_way;

#line 95 "misc/parser.tab.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_MISC_PARSER_TAB_HH_INCLUDED
# define YY_YY_MISC_PARSER_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    HEX_LITERAL = 259,
    INSTRUCTION = 260,
    DIRECTIVE = 261,
    END_OF_LINE = 262,
    MOV = 263,
    CMP = 264,
    GLOBAL = 265,
    EXTERN = 266,
    SECTION = 267,
    WORD = 268,
    SKIP = 269,
    END = 270,
    STATUS = 271,
    HANDLER = 272,
    CAUSE = 273,
    HALT = 274,
    INT = 275,
    IRET = 276,
    CALL = 277,
    RET = 278,
    JMP = 279,
    BEQ = 280,
    BNE = 281,
    BGT = 282,
    PUSH = 283,
    POP = 284,
    XCHG = 285,
    ADD = 286,
    SUB = 287,
    MUL = 288,
    DIV = 289,
    NOT = 290,
    AND = 291,
    OR = 292,
    XOR = 293,
    SHL = 294,
    SHR = 295,
    LD = 296,
    ST = 297,
    CSRRD = 298,
    CSRWR = 299,
    R0 = 300,
    R1 = 301,
    R2 = 302,
    R3 = 303,
    R4 = 304,
    R5 = 305,
    R6 = 306,
    R7 = 307,
    R8 = 308,
    R9 = 309,
    R10 = 310,
    R11 = 311,
    R12 = 312,
    R13 = 313,
    R14 = 314,
    R15 = 315,
    PC = 316,
    SP = 317,
    COLON = 318,
    OFFSET = 319,
    COMMA = 320,
    LEFT_SQUARE = 321,
    RIGHT_SQUARE = 322,
    PLUS = 323,
    POINT = 324
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "misc/bison.y"

    char *strval;
    int hexval;

#line 222 "misc/parser.tab.cc"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MISC_PARSER_TAB_HH_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  139
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   313

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  232

#define YYUNDEFTOK  2
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    53,    54,    57,    58,    59,    60,    61,
      62,    65,    68,    76,    78,    80,    82,    84,    86,    89,
      95,   101,   104,   109,   117,   122,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   161,   164,   167,   170,   185,   200,   216,   232,
     248,   254,   258,   264,   270,   277,   284,   291,   298,   305,
     312,   319,   326,   333,   340,   346,   352,   396,   439,   442,
     443,   446,   451,   473,   477,   481,   487,   490,   495,   498,
     501,   504,   507,   510,   513,   516,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   541,   542,   543,   546,   548,   551
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "HEX_LITERAL",
  "INSTRUCTION", "DIRECTIVE", "END_OF_LINE", "MOV", "CMP", "GLOBAL",
  "EXTERN", "SECTION", "WORD", "SKIP", "END", "STATUS", "HANDLER", "CAUSE",
  "HALT", "INT", "IRET", "CALL", "RET", "JMP", "BEQ", "BNE", "BGT", "PUSH",
  "POP", "XCHG", "ADD", "SUB", "MUL", "DIV", "NOT", "AND", "OR", "XOR",
  "SHL", "SHR", "LD", "ST", "CSRRD", "CSRWR", "R0", "R1", "R2", "R3", "R4",
  "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15",
  "PC", "SP", "COLON", "OFFSET", "COMMA", "LEFT_SQUARE", "RIGHT_SQUARE",
  "PLUS", "POINT", "$accept", "program", "assembler_program",
  "one_assembler_line", "label_directive", "label_instruction",
  "directive", "global_directive", "extern_directive", "section_directive",
  "word_directive", "skip_directive", "end_directive", "instruction",
  "halt_instruction", "int_instruction", "iret_instruction",
  "call_command", "jmp_command", "beq_command", "bne_command",
  "bgt_command", "push_command", "pop_command", "not_command",
  "xchg_command", "add_command", "sub_command", "mul_command",
  "div_command", "and_command", "or_command", "xor_command", "shl_command",
  "shr_command", "csrrd_command", "csrwr_command", "ld_command",
  "st_command", "ret_instruction", "symbol_or_literal_list", "symbol_list",
  "symbol_or_literal", "operand_destination_adress", "operand_data",
  "general_registers", "control_and_status_registers", "label", "symbol",
  "literal", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324
};
# endif

#define YYPACT_NINF (-87)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     231,   -87,   -87,     5,     5,     6,     8,    16,   -87,   -87,
     -87,   -87,    13,   -87,    13,   107,   107,   107,   107,    89,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,    38,   107,    -3,   107,    21,   231,   -87,   -87,   -87,
     -87,    15,    17,    18,    20,    22,    23,   -87,    25,    26,
      27,    28,    30,    31,    32,    33,    36,    37,    39,    41,
      42,    43,    44,    45,    46,    47,    64,    66,    69,    71,
      73,    74,    94,    96,   269,   -40,   -37,   -87,   -37,     5,
     -87,   -87,     5,   -20,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -18,    48,    49,   -87,   -87,   -87,   -87,   -87,   -87,    50,
      51,    52,    53,    54,   -87,    55,    56,    57,    58,    59,
      13,   107,    61,   -87,   -87,   -87,    62,    63,    67,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,     5,   -87,   -87,
       8,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   -87,   -87,   -49,   107,    38,   107,
      -3,   -87,   -87,    68,   105,   108,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,    13,   -87,   -87,
     -87,   -87,    13,    13,    13,   109,   111,   -87,   -87,   -87,
     -87,   -87
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,   118,    10,     0,     0,     0,     0,     0,    25,    52,
      53,    54,     0,    78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     8,     9,
       5,     0,     0,     0,     0,     0,     0,     6,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,    81,    20,     0,
      21,   119,     0,    23,    79,    83,    85,    24,    55,    86,
      87,    56,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   113,   112,
       0,     0,     0,    60,   114,   115,   116,    61,    62,     0,
       0,     0,     0,     0,    63,     0,     0,     0,     0,     0,
       0,     0,     0,    92,    90,    91,     0,     0,     0,     1,
       4,    13,    14,    15,    16,    17,    18,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    46,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    47,    48,
      49,    50,    51,     7,    11,    12,   117,     0,    22,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    88,    89,     0,     0,     0,     0,
       0,    82,    80,     0,     0,     0,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    93,     0,    76,    77,
      74,    75,     0,     0,     0,     0,     0,    57,    58,    59,
      95,    94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -87,   -87,   -87,    72,   -87,   -87,    35,   -87,   -87,   -87,
     -87,   -87,   -87,    98,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   106,   -69,    -4,   -86,    40,   -26,   -87,     0,    -5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      83,    76,    84,    88,   132,   133,   118,    74,    89,    90
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      75,    86,    87,    77,    77,    80,    85,   137,     1,     1,
      91,     1,    81,   114,   115,   116,     1,    81,   216,   217,
      81,   139,   141,   176,   142,   143,   135,   144,   177,   145,
     146,   134,   147,   148,   149,   150,    75,   151,   152,   153,
     154,     1,    81,   155,   156,   180,   157,   181,   158,   159,
     160,   161,   162,   163,   164,   110,   111,   112,   113,   117,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   165,   136,   166,   138,    79,   167,    82,   168,   178,
     169,   170,   179,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   171,   130,   172,   131,   114,   115,   116,   140,   174,
      78,   202,   219,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   195,   197,   198,   199,     0,
     194,     0,   200,   222,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     223,   196,   175,   224,   221,    86,   230,   201,   231,     0,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,     0,     0,     0,     0,   134,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   226,     0,     0,     0,     0,   225,   227,   228,
     229,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,     1,     0,     0,   218,     2,   220,
       0,     3,     4,     5,     6,     7,     8,     0,     0,     0,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,   173,     0,     0,     3,
       4,     5,     6,     7,     8,     0,     0,     0,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34
};

static const yytype_int16 yycheck[] =
{
       0,     6,     7,     3,     4,     5,     6,    33,     3,     3,
      14,     3,     4,    16,    17,    18,     3,     4,    67,    68,
       4,     0,     7,    63,     7,     7,    31,     7,    65,     7,
       7,    31,     7,     7,     7,     7,    36,     7,     7,     7,
       7,     3,     4,     7,     7,    65,     7,    65,     7,     7,
       7,     7,     7,     7,     7,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,     7,    32,     7,    34,    69,     7,    69,     7,    79,
       7,     7,    82,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,     7,    64,     7,    66,    16,    17,    18,    36,    74,
       4,   180,   198,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,   130,    65,    65,    65,    -1,
     130,    -1,    65,    65,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      65,   131,    74,    65,   200,   180,    67,   177,    67,    -1,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,    -1,    -1,    -1,    -1,   198,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   217,    -1,    -1,    -1,    -1,   217,   222,   223,
     224,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,     3,    -1,    -1,   197,     7,   199,
      -1,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,     7,    -1,    -1,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,    10,    11,    12,    13,    14,    15,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   117,   118,   111,   118,   111,    69,
     118,     4,    69,   110,   112,   118,   119,   119,   113,   118,
     119,   113,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
     115,   115,   115,   115,    16,    17,    18,   115,   116,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
      64,    66,   114,   115,   118,   119,   115,   116,   115,     0,
      73,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,    76,    83,    63,    65,   118,   118,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,   118,   119,   115,    65,    65,    65,
      65,   118,   112,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,    67,    68,   115,   114,
     115,   116,    65,    65,    65,   118,   119,   113,   113,   113,
      67,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    72,    72,    73,    73,    73,    73,    73,
      73,    74,    75,    76,    76,    76,    76,    76,    76,    77,
      78,    79,    79,    80,    81,    82,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     110,   111,   111,   112,   112,   112,   113,   113,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   117,   118,   119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     2,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     2,     2,     6,     6,     6,
       2,     2,     2,     2,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     1,     1,
       3,     1,     3,     1,     2,     1,     1,     1,     2,     2,
       1,     1,     1,     3,     5,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 19:
#line 89 "misc/bison.y"
                                     { 
        h.global_directive(symbol_name_list);
        symbol_name_list.clear();
    }
#line 1592 "misc/parser.tab.cc"
    break;

  case 20:
#line 95 "misc/bison.y"
                                     { 
        h.extern_directive(symbol_name_list);
        symbol_name_list.clear();
    }
#line 1601 "misc/parser.tab.cc"
    break;

  case 21:
#line 101 "misc/bison.y"
                                  {
        h.section_directive(symbol_name);
    }
#line 1609 "misc/parser.tab.cc"
    break;

  case 22:
#line 104 "misc/bison.y"
                           {
        h.section_directive("."+symbol_name);
    }
#line 1617 "misc/parser.tab.cc"
    break;

  case 23:
#line 109 "misc/bison.y"
                                            {
        h.word_directive(symbol_name_list, literal_list, kind_list);
        symbol_name_list.clear();
        literal_list.clear();
        kind_list.clear();
    }
#line 1628 "misc/parser.tab.cc"
    break;

  case 24:
#line 117 "misc/bison.y"
                             {
        h.skip_directive(literal);
    }
#line 1636 "misc/parser.tab.cc"
    break;

  case 25:
#line 122 "misc/bison.y"
                   {
        h.end_directive();
        //YYACCEPT;
    }
#line 1645 "misc/parser.tab.cc"
    break;

  case 52:
#line 161 "misc/bison.y"
                       { h.halt_instruction_handler(); }
#line 1651 "misc/parser.tab.cc"
    break;

  case 53:
#line 164 "misc/bison.y"
                     { h.int_instruction_handler(); }
#line 1657 "misc/parser.tab.cc"
    break;

  case 54:
#line 167 "misc/bison.y"
                       { h.iret_instruction_handler(); }
#line 1663 "misc/parser.tab.cc"
    break;

  case 55:
#line 170 "misc/bison.y"
                                              {
        if(symbol_or_literal==0){
            h.call_command_handler(symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.call_command_handler(ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.call_command_handler(std::to_string(literal), symbol_or_literal);
        }
        
    }
#line 1681 "misc/parser.tab.cc"
    break;

  case 56:
#line 185 "misc/bison.y"
                                            {
        if(symbol_or_literal==0){
            h.jmp_command_handler(symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.jmp_command_handler(ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.jmp_command_handler(std::to_string(literal), symbol_or_literal);
        }
        
    }
#line 1699 "misc/parser.tab.cc"
    break;

  case 57:
#line 200 "misc/bison.y"
                                                                                            {
        if(symbol_or_literal==0){
            h.beq_command_handler(gpr1, gpr2, symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.beq_command_handler(gpr1, gpr2, ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.beq_command_handler(gpr1, gpr2, std::to_string(literal), symbol_or_literal);
        }
        gpr1="";
        gpr2="";
    }
#line 1718 "misc/parser.tab.cc"
    break;

  case 58:
#line 216 "misc/bison.y"
                                                                                            {
        if(symbol_or_literal==0){
            h.bne_command_handler(gpr1, gpr2, symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.bne_command_handler(gpr1, gpr2, ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.bne_command_handler(gpr1, gpr2, std::to_string(literal), symbol_or_literal);
        }
        gpr1="";
        gpr2="";
    }
#line 1737 "misc/parser.tab.cc"
    break;

  case 59:
#line 232 "misc/bison.y"
                                                                                            {
        if(symbol_or_literal==0){
            h.bgt_command_handler(gpr1, gpr2, symbol_name, symbol_or_literal);
        }
        else{
            std::stringstream ss;
            ss << std::hex << literal;
            h.bgt_command_handler(gpr1, gpr2, ss.str(), symbol_or_literal);
            gpr1=""; gpr2="";
            //h.bgt_command_handler(gpr1, gpr2, std::to_string(literal), symbol_or_literal);
        }
        gpr1="";
        gpr2="";
    }
#line 1756 "misc/parser.tab.cc"
    break;

  case 60:
#line 248 "misc/bison.y"
                                     {
        h.push_command_handler(gpr1);
        gpr1="";
    }
#line 1765 "misc/parser.tab.cc"
    break;

  case 61:
#line 254 "misc/bison.y"
                                   {
        h.pop_command_handler(gpr1);
        gpr1="";
    }
#line 1774 "misc/parser.tab.cc"
    break;

  case 62:
#line 258 "misc/bison.y"
                                       {
        h.pop_command_handler(csr);
        csr="";
    }
#line 1783 "misc/parser.tab.cc"
    break;

  case 63:
#line 264 "misc/bison.y"
                                   {
        h.not_command_handler(gpr1);
        gpr1="";
    }
#line 1792 "misc/parser.tab.cc"
    break;

  case 64:
#line 270 "misc/bison.y"
                                                             {
        h.xchg_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1802 "misc/parser.tab.cc"
    break;

  case 65:
#line 277 "misc/bison.y"
                                                           {
        h.add_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1812 "misc/parser.tab.cc"
    break;

  case 66:
#line 284 "misc/bison.y"
                                                           {
        h.sub_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1822 "misc/parser.tab.cc"
    break;

  case 67:
#line 291 "misc/bison.y"
                                                           {
        h.mul_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1832 "misc/parser.tab.cc"
    break;

  case 68:
#line 298 "misc/bison.y"
                                                           {
        h.div_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1842 "misc/parser.tab.cc"
    break;

  case 69:
#line 305 "misc/bison.y"
                                                           {
        h.and_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1852 "misc/parser.tab.cc"
    break;

  case 70:
#line 312 "misc/bison.y"
                                                         {
        h.or_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1862 "misc/parser.tab.cc"
    break;

  case 71:
#line 319 "misc/bison.y"
                                                           {
        h.xor_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1872 "misc/parser.tab.cc"
    break;

  case 72:
#line 326 "misc/bison.y"
                                                           {
        h.shl_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1882 "misc/parser.tab.cc"
    break;

  case 73:
#line 333 "misc/bison.y"
                                                           {
        h.shr_command_handler(gpr1, gpr2);
        gpr1="";
        gpr2="";
    }
#line 1892 "misc/parser.tab.cc"
    break;

  case 74:
#line 340 "misc/bison.y"
                                                                          {
        h.csrrd_command_handler(csr, gpr1);
        gpr1="";
    }
#line 1901 "misc/parser.tab.cc"
    break;

  case 75:
#line 346 "misc/bison.y"
                                                                          {
        h.csrwr_command_handler(gpr1, csr);
        gpr1="";
    }
#line 1910 "misc/parser.tab.cc"
    break;

  case 76:
#line 352 "misc/bison.y"
                                                    {
        if(operand_data_way==0) {
            h.ld_command_handler(symbol_name, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==1) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.ld_command_handler(ss.str(), "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
            //h.ld_command_handler(std::to_string(literal), "", operand_data_way, gpr1);
        }
        else if(operand_data_way==2) {
            h.ld_command_handler(symbol_name, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==3) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.ld_command_handler(ss.str(), "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
            //h.ld_command_handler(std::to_string(literal), "", operand_data_way, gpr1);
        }
        else if(operand_data_way==4) {
            h.ld_command_handler(gpr1, "", operand_data_way, gpr2);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==5) {
            h.ld_command_handler(gpr1, "", operand_data_way, gpr2);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==6) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.ld_command_handler(gpr1, ss.str(), operand_data_way, gpr2);
            gpr1=""; gpr2="";
            //h.ld_command_handler(gpr1, std::to_string(literal), operand_data_way, gpr2);
        }
        else if(operand_data_way==7) {
            h.ld_command_handler(gpr1, symbol_name, operand_data_way, gpr2);
            gpr1=""; gpr2="";
        }
    }
#line 1958 "misc/parser.tab.cc"
    break;

  case 77:
#line 396 "misc/bison.y"
                                                    {
        if(operand_data_way==0) {
            h.st_command_handler(symbol_name, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==1) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.st_command_handler(ss.str(), "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
            //h.st_command_handler(std::to_string(literal), "", operand_data_way, gpr1);
        }
        else if(operand_data_way==2) {
            h.st_command_handler(symbol_name, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==3) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.st_command_handler(ss.str(), "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
            //h.st_command_handler(std::to_string(literal), "", operand_data_way, gpr1);
        }
        else if(operand_data_way==4) {
            h.st_command_handler(gpr2, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==5) {
            h.st_command_handler(gpr2, "", operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==6) {
            std::stringstream ss;
            ss << std::hex << literal;
            h.st_command_handler(gpr2, ss.str(), operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
        else if(operand_data_way==7) {
            h.st_command_handler(gpr2, symbol_name, operand_data_way, gpr1);
            gpr1=""; gpr2="";
        }
}
#line 2005 "misc/parser.tab.cc"
    break;

  case 78:
#line 439 "misc/bison.y"
                     { h.ret_instruction_handler(); }
#line 2011 "misc/parser.tab.cc"
    break;

  case 81:
#line 447 "misc/bison.y"
    {
        //symbol_name_list=$1;
        symbol_name_list.push_back(symbol_name);
    }
#line 2020 "misc/parser.tab.cc"
    break;

  case 82:
#line 452 "misc/bison.y"
    {
        //symbol_name_list=$1;
        symbol_name_list.push_back(symbol_name);
    }
#line 2029 "misc/parser.tab.cc"
    break;

  case 83:
#line 473 "misc/bison.y"
                          { 
        symbol_name_list.push_back(symbol_name); 
        kind_list.push_back(0);
    }
#line 2038 "misc/parser.tab.cc"
    break;

  case 84:
#line 477 "misc/bison.y"
                   { 
        symbol_name_list.push_back("."+symbol_name); 
        kind_list.push_back(0);
    }
#line 2047 "misc/parser.tab.cc"
    break;

  case 85:
#line 481 "misc/bison.y"
              { 
        literal_list.push_back(literal);
        kind_list.push_back(1); 
    }
#line 2056 "misc/parser.tab.cc"
    break;

  case 86:
#line 487 "misc/bison.y"
                                   {
        symbol_or_literal=0;
    }
#line 2064 "misc/parser.tab.cc"
    break;

  case 87:
#line 490 "misc/bison.y"
              {
        symbol_or_literal=1;
    }
#line 2072 "misc/parser.tab.cc"
    break;

  case 88:
#line 495 "misc/bison.y"
                            {
        operand_data_way=0;
    }
#line 2080 "misc/parser.tab.cc"
    break;

  case 89:
#line 498 "misc/bison.y"
                     {
        operand_data_way=1;
    }
#line 2088 "misc/parser.tab.cc"
    break;

  case 90:
#line 501 "misc/bison.y"
             {
        operand_data_way=2;
    }
#line 2096 "misc/parser.tab.cc"
    break;

  case 91:
#line 504 "misc/bison.y"
              {
        operand_data_way=3;
    }
#line 2104 "misc/parser.tab.cc"
    break;

  case 92:
#line 507 "misc/bison.y"
                        {
        operand_data_way=4;
    }
#line 2112 "misc/parser.tab.cc"
    break;

  case 93:
#line 510 "misc/bison.y"
                                                 {
        operand_data_way=5;
    }
#line 2120 "misc/parser.tab.cc"
    break;

  case 94:
#line 513 "misc/bison.y"
                                                              {
        operand_data_way=6;
    }
#line 2128 "misc/parser.tab.cc"
    break;

  case 95:
#line 516 "misc/bison.y"
                                                             {
        operand_data_way=7;
    }
#line 2136 "misc/parser.tab.cc"
    break;

  case 96:
#line 521 "misc/bison.y"
                      { if(gpr1=="") gpr1="r0"; else gpr2="r0"; }
#line 2142 "misc/parser.tab.cc"
    break;

  case 97:
#line 522 "misc/bison.y"
         { if(gpr1=="") gpr1="r1"; else gpr2="r1"; }
#line 2148 "misc/parser.tab.cc"
    break;

  case 98:
#line 523 "misc/bison.y"
         { if(gpr1=="") gpr1="r2"; else gpr2="r2"; }
#line 2154 "misc/parser.tab.cc"
    break;

  case 99:
#line 524 "misc/bison.y"
         { if(gpr1=="") gpr1="r3"; else gpr2="r3"; }
#line 2160 "misc/parser.tab.cc"
    break;

  case 100:
#line 525 "misc/bison.y"
         { if(gpr1=="") gpr1="r4"; else gpr2="r4"; }
#line 2166 "misc/parser.tab.cc"
    break;

  case 101:
#line 526 "misc/bison.y"
         { if(gpr1=="") gpr1="r5"; else gpr2="r5"; }
#line 2172 "misc/parser.tab.cc"
    break;

  case 102:
#line 527 "misc/bison.y"
         { if(gpr1=="") gpr1="r6"; else gpr2="r6"; }
#line 2178 "misc/parser.tab.cc"
    break;

  case 103:
#line 528 "misc/bison.y"
         { if(gpr1=="") gpr1="r7"; else gpr2="r7"; }
#line 2184 "misc/parser.tab.cc"
    break;

  case 104:
#line 529 "misc/bison.y"
         { if(gpr1=="") gpr1="r8"; else gpr2="r8"; }
#line 2190 "misc/parser.tab.cc"
    break;

  case 105:
#line 530 "misc/bison.y"
         { if(gpr1=="") gpr1="r9"; else gpr2="r9"; }
#line 2196 "misc/parser.tab.cc"
    break;

  case 106:
#line 531 "misc/bison.y"
          { if(gpr1=="") gpr1="r10"; else gpr2="r10"; }
#line 2202 "misc/parser.tab.cc"
    break;

  case 107:
#line 532 "misc/bison.y"
          { if(gpr1=="") gpr1="r11"; else gpr2="r11"; }
#line 2208 "misc/parser.tab.cc"
    break;

  case 108:
#line 533 "misc/bison.y"
          { if(gpr1=="") gpr1="r12"; else gpr2="r12"; }
#line 2214 "misc/parser.tab.cc"
    break;

  case 109:
#line 534 "misc/bison.y"
          { if(gpr1=="") gpr1="r13"; else gpr2="r13"; }
#line 2220 "misc/parser.tab.cc"
    break;

  case 110:
#line 535 "misc/bison.y"
          { if(gpr1=="") gpr1="r14"; else gpr2="r14"; }
#line 2226 "misc/parser.tab.cc"
    break;

  case 111:
#line 536 "misc/bison.y"
          { if(gpr1=="") gpr1="r15"; else gpr2="r15"; }
#line 2232 "misc/parser.tab.cc"
    break;

  case 112:
#line 537 "misc/bison.y"
         { if(gpr1=="") gpr1="sp"; else gpr2="sp"; }
#line 2238 "misc/parser.tab.cc"
    break;

  case 113:
#line 538 "misc/bison.y"
         { if(gpr1=="") gpr1="pc"; else gpr2="pc"; }
#line 2244 "misc/parser.tab.cc"
    break;

  case 114:
#line 541 "misc/bison.y"
                                     { csr="status"; }
#line 2250 "misc/parser.tab.cc"
    break;

  case 115:
#line 542 "misc/bison.y"
              { csr="handler"; }
#line 2256 "misc/parser.tab.cc"
    break;

  case 116:
#line 543 "misc/bison.y"
            { csr="cause"; }
#line 2262 "misc/parser.tab.cc"
    break;

  case 117:
#line 546 "misc/bison.y"
                    { h.label_handler(symbol_name); }
#line 2268 "misc/parser.tab.cc"
    break;

  case 118:
#line 548 "misc/bison.y"
                   {  symbol_name = yytext; }
#line 2274 "misc/parser.tab.cc"
    break;

  case 119:
#line 551 "misc/bison.y"
                     { literal = (yyvsp[0].hexval); }
#line 2280 "misc/parser.tab.cc"
    break;


#line 2284 "misc/parser.tab.cc"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 553 "misc/bison.y"


void yyerror(const char *s) {
    std::cerr << "Parser error: " << s << " on line " << yylineno << std::endl;
}
