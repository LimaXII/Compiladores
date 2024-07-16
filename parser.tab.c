/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser.y"

#include <stdio.h>
#include "valor_lexico.h"
#include "ast_tree.h"
#include "table.h"

// Importa as funções necessárias.
int get_line_number();
int yylex(void);
void yyerror (char const *message);
extern Node* arvore;
extern SymbolTableStack* globalSymbolTableStack;

DataType declared_type = DATA_TYPE_UNDECLARED; // O tipo atualmente declarado
Node* mainFunctionNode = NULL;


#line 89 ".//parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_PR_INT = 3,                  /* TK_PR_INT  */
  YYSYMBOL_TK_PR_FLOAT = 4,                /* TK_PR_FLOAT  */
  YYSYMBOL_TK_PR_BOOL = 5,                 /* TK_PR_BOOL  */
  YYSYMBOL_TK_PR_IF = 6,                   /* TK_PR_IF  */
  YYSYMBOL_TK_PR_ELSE = 7,                 /* TK_PR_ELSE  */
  YYSYMBOL_TK_PR_WHILE = 8,                /* TK_PR_WHILE  */
  YYSYMBOL_TK_PR_RETURN = 9,               /* TK_PR_RETURN  */
  YYSYMBOL_TK_OC_LE = 10,                  /* TK_OC_LE  */
  YYSYMBOL_TK_OC_GE = 11,                  /* TK_OC_GE  */
  YYSYMBOL_TK_OC_EQ = 12,                  /* TK_OC_EQ  */
  YYSYMBOL_TK_OC_NE = 13,                  /* TK_OC_NE  */
  YYSYMBOL_TK_OC_AND = 14,                 /* TK_OC_AND  */
  YYSYMBOL_TK_OC_OR = 15,                  /* TK_OC_OR  */
  YYSYMBOL_TK_IDENTIFICADOR = 16,          /* TK_IDENTIFICADOR  */
  YYSYMBOL_TK_LIT_INT = 17,                /* TK_LIT_INT  */
  YYSYMBOL_TK_LIT_FLOAT = 18,              /* TK_LIT_FLOAT  */
  YYSYMBOL_TK_LIT_FALSE = 19,              /* TK_LIT_FALSE  */
  YYSYMBOL_TK_LIT_TRUE = 20,               /* TK_LIT_TRUE  */
  YYSYMBOL_21_ = 21,                       /* '='  */
  YYSYMBOL_22_ = 22,                       /* '<'  */
  YYSYMBOL_23_ = 23,                       /* '>'  */
  YYSYMBOL_24_ = 24,                       /* '+'  */
  YYSYMBOL_25_ = 25,                       /* '-'  */
  YYSYMBOL_26_ = 26,                       /* '*'  */
  YYSYMBOL_27_ = 27,                       /* '/'  */
  YYSYMBOL_28_ = 28,                       /* '%'  */
  YYSYMBOL_29_ = 29,                       /* '!'  */
  YYSYMBOL_30_ = 30,                       /* '('  */
  YYSYMBOL_31_ = 31,                       /* ')'  */
  YYSYMBOL_TK_ERRO = 32,                   /* TK_ERRO  */
  YYSYMBOL_33_ = 33,                       /* ','  */
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_elements_list = 39,             /* elements_list  */
  YYSYMBOL_element = 40,                   /* element  */
  YYSYMBOL_global_vars_declaration = 41,   /* global_vars_declaration  */
  YYSYMBOL_ident_list = 42,                /* ident_list  */
  YYSYMBOL_function = 43,                  /* function  */
  YYSYMBOL_header = 44,                    /* header  */
  YYSYMBOL_parameters_list = 45,           /* parameters_list  */
  YYSYMBOL_parameter = 46,                 /* parameter  */
  YYSYMBOL_body = 47,                      /* body  */
  YYSYMBOL_command_block = 48,             /* command_block  */
  YYSYMBOL_simple_command_list = 49,       /* simple_command_list  */
  YYSYMBOL_command = 50,                   /* command  */
  YYSYMBOL_attribution_command = 51,       /* attribution_command  */
  YYSYMBOL_function_call = 52,             /* function_call  */
  YYSYMBOL_return_command = 53,            /* return_command  */
  YYSYMBOL_control_command = 54,           /* control_command  */
  YYSYMBOL_arguments = 55,                 /* arguments  */
  YYSYMBOL_expression = 56,                /* expression  */
  YYSYMBOL_expression7 = 57,               /* expression7  */
  YYSYMBOL_expression6 = 58,               /* expression6  */
  YYSYMBOL_expression5 = 59,               /* expression5  */
  YYSYMBOL_expression4 = 60,               /* expression4  */
  YYSYMBOL_expression3 = 61,               /* expression3  */
  YYSYMBOL_expression2 = 62,               /* expression2  */
  YYSYMBOL_expression1 = 63,               /* expression1  */
  YYSYMBOL_negation_expression = 64,       /* negation_expression  */
  YYSYMBOL_minus_expressison = 65,         /* minus_expressison  */
  YYSYMBOL_expression0 = 66,               /* expression0  */
  YYSYMBOL_operands = 67,                  /* operands  */
  YYSYMBOL_type = 68,                      /* type  */
  YYSYMBOL_literal = 69                    /* literal  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   141

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,     2,     2,    28,     2,     2,
      30,    31,    26,    24,    33,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
      22,    21,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    91,    91,    97,   102,   112,   116,   120,   126,   133,
     139,   147,   157,   161,   165,   169,   173,   179,   183,   187,
     191,   203,   209,   213,   217,   221,   225,   229,   233,   242,
     250,   258,   264,   272,   283,   291,   296,   302,   307,   313,
     318,   324,   329,   335,   341,   346,   352,   358,   364,   370,
     375,   381,   387,   392,   398,   404,   410,   415,   420,   425,
     430,   435,   439,   444,   449,   453,   457,   464,   468,   474,
     479,   484,   491,   495,   499,   505
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TK_PR_INT",
  "TK_PR_FLOAT", "TK_PR_BOOL", "TK_PR_IF", "TK_PR_ELSE", "TK_PR_WHILE",
  "TK_PR_RETURN", "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE",
  "TK_OC_AND", "TK_OC_OR", "TK_IDENTIFICADOR", "TK_LIT_INT",
  "TK_LIT_FLOAT", "TK_LIT_FALSE", "TK_LIT_TRUE", "'='", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'('", "')'", "TK_ERRO", "','",
  "';'", "'{'", "'}'", "$accept", "program", "elements_list", "element",
  "global_vars_declaration", "ident_list", "function", "header",
  "parameters_list", "parameter", "body", "command_block",
  "simple_command_list", "command", "attribution_command", "function_call",
  "return_command", "control_command", "arguments", "expression",
  "expression7", "expression6", "expression5", "expression4",
  "expression3", "expression2", "expression1", "negation_expression",
  "minus_expressison", "expression0", "operands", "type", "literal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      40,   -43,   -43,   -43,    31,     2,   -43,    40,   -43,   -43,
     -30,    -6,    -2,   -16,   -11,     4,   -43,   -43,     3,   -43,
     -43,    16,    28,    73,    22,    73,   -43,    33,    37,    55,
      -5,   -43,   -43,    58,    43,    24,    69,    84,    87,    88,
      -6,   -43,    91,    73,   -43,    55,    55,    92,   -43,   -43,
     -43,   -43,   -43,   -43,    55,   -43,   -43,   108,    44,    95,
      46,    85,    77,   -43,    70,    76,   -43,   -43,   -43,    55,
      35,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   109,
      97,    96,    98,    99,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,   -43,   -43,   -43,
     -43,   -43,   -43,   100,    94,   -43,   110,   -30,   -30,   -43,
      44,    95,    46,    46,    85,    85,    85,    85,    77,    77,
     -43,   -43,   -43,   -43,    55,   -43,   125,   -43,   -43,   -30,
     -43
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    69,    70,    71,     0,     0,     2,     5,     6,     7,
       0,     0,     0,     0,    15,     0,     1,     4,     0,    11,
      17,    10,     0,     0,     0,     0,    16,     0,     0,     0,
       0,    19,    23,     0,     0,    21,     0,     0,     0,     0,
       0,     8,     0,     0,    14,     0,     0,    66,    72,    73,
      75,    74,    63,    61,     0,    68,    31,    37,    39,    41,
      44,    49,    52,    56,     0,     0,    59,    64,    67,     0,
       0,    22,    18,    20,    24,    25,    26,    27,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    60,    57,    62,
      58,    28,    30,     0,    36,    13,     0,     0,     0,    65,
      38,    40,    42,    43,    45,    46,    47,    48,    50,    51,
      53,    54,    55,    29,     0,    12,    32,    34,    35,     0,
      33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   126,   -43,   -14,   101,   -43,   -43,   111,   -43,
     -43,   -10,   102,   -43,   -43,    -4,   -43,   -43,    10,   -28,
     -43,    54,    50,    25,   -42,    21,   -13,   -43,   -43,    51,
     -43,    -1,   -43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    22,     9,    10,    13,    14,
      19,    33,    34,    35,    36,    55,    38,    39,   103,   104,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    11,    68
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      20,    56,    16,    15,    32,    18,     1,     2,     3,    27,
      21,    28,    29,    23,    37,    24,    69,    81,    82,    30,
      26,    32,    42,    25,    15,    70,    83,     1,     2,     3,
      27,    37,    28,    29,     1,     2,     3,    43,    18,    31,
      30,   101,    80,     1,     2,     3,   114,   115,   116,   117,
      40,    47,    48,    49,    50,    51,    88,    89,    85,    18,
      52,    41,    12,    45,    53,    54,   102,    46,    90,    91,
       4,    47,    48,    49,    50,    51,     1,     2,     3,    72,
      52,   120,   121,   122,    53,    54,    47,    48,    49,    50,
      51,    71,    47,    48,    49,    50,    51,   126,   127,    97,
      54,    99,    74,    94,    95,    96,    54,    86,    87,    92,
      93,   112,   113,   118,   119,    98,   100,    75,    79,   130,
      76,    77,    70,    84,   106,   105,   125,   107,   124,   108,
     109,   123,   129,    17,   128,   111,    44,    73,   110,     0,
       0,    78
};

static const yytype_int16 yycheck[] =
{
      10,    29,     0,     4,    18,    35,     3,     4,     5,     6,
      16,     8,     9,    15,    18,    31,    21,    45,    46,    16,
      16,    35,    23,    34,    25,    30,    54,     3,     4,     5,
       6,    35,     8,     9,     3,     4,     5,    15,    35,    36,
      16,    69,    43,     3,     4,     5,    88,    89,    90,    91,
      34,    16,    17,    18,    19,    20,    10,    11,    14,    35,
      25,    33,    31,    30,    29,    30,    31,    30,    22,    23,
      30,    16,    17,    18,    19,    20,     3,     4,     5,    36,
      25,    94,    95,    96,    29,    30,    16,    17,    18,    19,
      20,    33,    16,    17,    18,    19,    20,   107,   108,    29,
      30,    25,    33,    26,    27,    28,    30,    12,    13,    24,
      25,    86,    87,    92,    93,    64,    65,    33,    27,   129,
      33,    33,    30,    15,    27,    16,    16,    31,    34,    31,
      31,    31,     7,     7,   124,    85,    25,    35,    84,    -1,
      -1,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    30,    38,    39,    40,    41,    43,
      44,    68,    31,    45,    46,    68,     0,    39,    35,    47,
      48,    16,    42,    15,    31,    34,    16,     6,     8,     9,
      16,    36,    41,    48,    49,    50,    51,    52,    53,    54,
      34,    33,    68,    15,    45,    30,    30,    16,    17,    18,
      19,    20,    25,    29,    30,    52,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    69,    21,
      30,    33,    36,    49,    33,    33,    33,    33,    42,    27,
      68,    56,    56,    56,    15,    14,    12,    13,    10,    11,
      22,    23,    24,    25,    26,    27,    28,    29,    66,    25,
      66,    56,    31,    55,    56,    16,    27,    31,    31,    31,
      58,    59,    60,    60,    61,    61,    61,    61,    62,    62,
      63,    63,    63,    31,    34,    16,    48,    48,    55,     7,
      48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    39,    39,    40,    40,    41,    42,
      42,    43,    44,    44,    45,    45,    46,    47,    48,    48,
      49,    49,    50,    50,    50,    50,    50,    50,    51,    52,
      52,    53,    54,    54,    54,    55,    55,    56,    57,    57,
      58,    58,    59,    59,    59,    60,    60,    60,    60,    60,
      61,    61,    61,    62,    62,    62,    62,    63,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    68,
      68,    68,    69,    69,    69,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     3,     3,
       1,     2,     7,     6,     3,     1,     2,     1,     3,     2,
       2,     1,     2,     1,     2,     2,     2,     2,     3,     4,
       3,     2,     5,     7,     5,     3,     1,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     1,
       2,     1,     2,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* program: elements_list  */
#line 92 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
    arvore = (yyval.node);
}
#line 1512 ".//parser.tab.c"
    break;

  case 3: /* program: %empty  */
#line 97 "parser.y"
{
    (yyval.node) = NULL;
    arvore = NULL;
}
#line 1521 ".//parser.tab.c"
    break;

  case 4: /* elements_list: element elements_list  */
#line 103 "parser.y"
{
    if ((yyvsp[-1].node)){
        (yyval.node) = (yyvsp[-1].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
    else{
        (yyval.node) = (yyvsp[0].node);
    }
}
#line 1535 ".//parser.tab.c"
    break;

  case 5: /* elements_list: element  */
#line 113 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1543 ".//parser.tab.c"
    break;

  case 6: /* element: global_vars_declaration  */
#line 117 "parser.y"
{
    (yyval.node) = NULL;
}
#line 1551 ".//parser.tab.c"
    break;

  case 7: /* element: function  */
#line 121 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1559 ".//parser.tab.c"
    break;

  case 8: /* global_vars_declaration: type ident_list ','  */
#line 127 "parser.y"
{
    (yyval.node) = NULL;
    remove_node((yyvsp[-1].node));

    declared_type = DATA_TYPE_UNDECLARED;
}
#line 1570 ".//parser.tab.c"
    break;

  case 9: /* ident_list: TK_IDENTIFICADOR ';' ident_list  */
#line 134 "parser.y"
{
    (yyval.node) = NULL;
    TableEntryValue value = create_table_entry_value(SYMBOL_NATURE_IDENTIFIER, declared_type, (yyvsp[-2].valor_lexico));
    add_symbol_value_to_global_table_stack(value);
}
#line 1580 ".//parser.tab.c"
    break;

  case 10: /* ident_list: TK_IDENTIFICADOR  */
#line 140 "parser.y"
{
    (yyval.node) = NULL;
    TableEntryValue value = create_table_entry_value(SYMBOL_NATURE_IDENTIFIER, declared_type, (yyvsp[0].valor_lexico));
    add_symbol_value_to_global_table_stack(value);
}
#line 1590 ".//parser.tab.c"
    break;

  case 11: /* function: header body  */
#line 148 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
    if ((yyvsp[0].node)){
        add_child((yyval.node), (yyvsp[0].node));
        pop_global_stack();
    }
}
#line 1602 ".//parser.tab.c"
    break;

  case 12: /* header: '(' parameters_list ')' TK_OC_OR type '/' TK_IDENTIFICADOR  */
#line 158 "parser.y"
{
    (yyval.node) = create_node_valor_lexico((yyvsp[0].valor_lexico), (yyvsp[-2].node));
}
#line 1610 ".//parser.tab.c"
    break;

  case 13: /* header: '(' ')' TK_OC_OR type '/' TK_IDENTIFICADOR  */
#line 162 "parser.y"
{
    (yyval.node) = create_node_valor_lexico((yyvsp[0].valor_lexico), (yyvsp[-2].node));
}
#line 1618 ".//parser.tab.c"
    break;

  case 14: /* parameters_list: parameter ';' parameters_list  */
#line 166 "parser.y"
{
    (yyval.node) = NULL;
}
#line 1626 ".//parser.tab.c"
    break;

  case 15: /* parameters_list: parameter  */
#line 170 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1634 ".//parser.tab.c"
    break;

  case 16: /* parameter: type TK_IDENTIFICADOR  */
#line 173 "parser.y"
                                {
    (yyval.node) = NULL;
    freeValor_lexico((yyvsp[0].valor_lexico));
}
#line 1643 ".//parser.tab.c"
    break;

  case 17: /* body: command_block  */
#line 180 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1651 ".//parser.tab.c"
    break;

  case 18: /* command_block: '{' simple_command_list '}'  */
#line 184 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1659 ".//parser.tab.c"
    break;

  case 19: /* command_block: '{' '}'  */
#line 188 "parser.y"
{
    (yyval.node) = NULL;
}
#line 1667 ".//parser.tab.c"
    break;

  case 20: /* simple_command_list: command simple_command_list  */
#line 192 "parser.y"
{
    if ((yyvsp[-1].node))
    {
        (yyval.node) = (yyvsp[-1].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
    else
    {
        (yyval.node) = (yyvsp[0].node);
    }
}
#line 1683 ".//parser.tab.c"
    break;

  case 21: /* simple_command_list: command  */
#line 204 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1691 ".//parser.tab.c"
    break;

  case 22: /* command: command_block ','  */
#line 210 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1699 ".//parser.tab.c"
    break;

  case 23: /* command: global_vars_declaration  */
#line 214 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1707 ".//parser.tab.c"
    break;

  case 24: /* command: attribution_command ','  */
#line 218 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1715 ".//parser.tab.c"
    break;

  case 25: /* command: function_call ','  */
#line 222 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1723 ".//parser.tab.c"
    break;

  case 26: /* command: return_command ','  */
#line 226 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1731 ".//parser.tab.c"
    break;

  case 27: /* command: control_command ','  */
#line 230 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 1739 ".//parser.tab.c"
    break;

  case 28: /* attribution_command: TK_IDENTIFICADOR '=' expression  */
#line 234 "parser.y"
{
    DataType type = infer_type_from_identifier((yyvsp[-2].valor_lexico));
    check_identifier_is_variable((yyvsp[-2].valor_lexico));
    
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), type);
    add_child((yyval.node), create_node_valor_lexico((yyvsp[-2].valor_lexico), type));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1752 ".//parser.tab.c"
    break;

  case 29: /* function_call: TK_IDENTIFICADOR '(' arguments ')'  */
#line 243 "parser.y"
{
    DataType type = infer_type_from_identifier((yyvsp[-3].valor_lexico));
    check_identifier_is_function((yyvsp[-3].valor_lexico));

    (yyval.node) = create_node_function((yyvsp[-3].valor_lexico), type);
    add_child((yyval.node), (yyvsp[-1].node));
}
#line 1764 ".//parser.tab.c"
    break;

  case 30: /* function_call: TK_IDENTIFICADOR '(' ')'  */
#line 251 "parser.y"
{
    DataType type = infer_type_from_identifier((yyvsp[-2].valor_lexico));
    check_identifier_is_function((yyvsp[-2].valor_lexico));

    (yyval.node) = create_node_function((yyvsp[-2].valor_lexico), type);
}
#line 1775 ".//parser.tab.c"
    break;

  case 31: /* return_command: TK_PR_RETURN expression  */
#line 259 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_node((yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1784 ".//parser.tab.c"
    break;

  case 32: /* control_command: TK_PR_IF '(' expression ')' command_block  */
#line 265 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-4].ast_token), infer_type_from_node((yyvsp[-2].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    if ((yyvsp[0].node)){
        add_child((yyval.node), (yyvsp[0].node));
    }
}
#line 1796 ".//parser.tab.c"
    break;

  case 33: /* control_command: TK_PR_IF '(' expression ')' command_block TK_PR_ELSE command_block  */
#line 273 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-6].ast_token), infer_type_from_node((yyvsp[-4].node)));
    add_child((yyval.node), (yyvsp[-4].node));
    if ((yyvsp[-2].node)){
        add_child((yyval.node), (yyvsp[-2].node));
    }
    if ((yyvsp[0].node)){
        add_child((yyval.node), (yyvsp[0].node));
    }
}
#line 1811 ".//parser.tab.c"
    break;

  case 34: /* control_command: TK_PR_WHILE '(' expression ')' command_block  */
#line 284 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-4].ast_token), infer_type_from_node((yyvsp[-2].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    if ((yyvsp[0].node)){
        add_child((yyval.node), (yyvsp[0].node));
    }
}
#line 1823 ".//parser.tab.c"
    break;

  case 35: /* arguments: expression ';' arguments  */
#line 292 "parser.y"
{
    (yyval.node) = (yyvsp[-2].node);
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1832 ".//parser.tab.c"
    break;

  case 36: /* arguments: expression  */
#line 297 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1840 ".//parser.tab.c"
    break;

  case 37: /* expression: expression7  */
#line 303 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1848 ".//parser.tab.c"
    break;

  case 38: /* expression7: expression7 TK_OC_OR expression6  */
#line 308 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1858 ".//parser.tab.c"
    break;

  case 39: /* expression7: expression6  */
#line 314 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1866 ".//parser.tab.c"
    break;

  case 40: /* expression6: expression6 TK_OC_AND expression5  */
#line 319 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1876 ".//parser.tab.c"
    break;

  case 41: /* expression6: expression5  */
#line 325 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1884 ".//parser.tab.c"
    break;

  case 42: /* expression5: expression5 TK_OC_EQ expression4  */
#line 330 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1894 ".//parser.tab.c"
    break;

  case 43: /* expression5: expression5 TK_OC_NE expression4  */
#line 336 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1904 ".//parser.tab.c"
    break;

  case 44: /* expression5: expression4  */
#line 342 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1912 ".//parser.tab.c"
    break;

  case 45: /* expression4: expression4 TK_OC_LE expression3  */
#line 347 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1922 ".//parser.tab.c"
    break;

  case 46: /* expression4: expression4 TK_OC_GE expression3  */
#line 353 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node))););
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1932 ".//parser.tab.c"
    break;

  case 47: /* expression4: expression4 '<' expression3  */
#line 359 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1942 ".//parser.tab.c"
    break;

  case 48: /* expression4: expression4 '>' expression3  */
#line 365 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1952 ".//parser.tab.c"
    break;

  case 49: /* expression4: expression3  */
#line 371 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1960 ".//parser.tab.c"
    break;

  case 50: /* expression3: expression3 '+' expression2  */
#line 376 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1970 ".//parser.tab.c"
    break;

  case 51: /* expression3: expression3 '-' expression2  */
#line 382 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1980 ".//parser.tab.c"
    break;

  case 52: /* expression3: expression2  */
#line 388 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 1988 ".//parser.tab.c"
    break;

  case 53: /* expression2: expression2 '*' expression1  */
#line 393 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 1998 ".//parser.tab.c"
    break;

  case 54: /* expression2: expression2 '/' expression1  */
#line 399 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 2008 ".//parser.tab.c"
    break;

  case 55: /* expression2: expression2 '%' expression1  */
#line 405 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[-1].ast_token), infer_type_from_nodes((yyvsp[-2].node), (yyvsp[0].node)));
    add_child((yyval.node), (yyvsp[-2].node));
    add_child((yyval.node), (yyvsp[0].node));
}
#line 2018 ".//parser.tab.c"
    break;

  case 56: /* expression2: expression1  */
#line 411 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 2026 ".//parser.tab.c"
    break;

  case 57: /* expression1: negation_expression expression0  */
#line 416 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
    add_child((yyval.node), (yyvsp[0].node));
}
#line 2035 ".//parser.tab.c"
    break;

  case 58: /* expression1: minus_expressison expression0  */
#line 421 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
    add_child((yyval.node), (yyvsp[0].node));
}
#line 2044 ".//parser.tab.c"
    break;

  case 59: /* expression1: expression0  */
#line 426 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 2052 ".//parser.tab.c"
    break;

  case 60: /* negation_expression: negation_expression '!'  */
#line 431 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[0].ast_token), infer_type_from_node((yyvsp[-1].node)));
    add_child((yyval.node), (yyvsp[-1].node));
}
#line 2061 ".//parser.tab.c"
    break;

  case 61: /* negation_expression: '!'  */
#line 436 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[0].ast_token), infer_type_from_node((yyvsp[0].ast_token)));
}
#line 2069 ".//parser.tab.c"
    break;

  case 62: /* minus_expressison: minus_expressison '-'  */
#line 440 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[0].ast_token), infer_type_from_node((yyvsp[-1].node)));
    add_child((yyval.node), (yyvsp[-1].node));
}
#line 2078 ".//parser.tab.c"
    break;

  case 63: /* minus_expressison: '-'  */
#line 445 "parser.y"
{
    (yyval.node) = create_node_token((yyvsp[0].ast_token), infer_type_from_node((yyvsp[0].ast_token)));
}
#line 2086 ".//parser.tab.c"
    break;

  case 64: /* expression0: operands  */
#line 450 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 2094 ".//parser.tab.c"
    break;

  case 65: /* expression0: '(' expression ')'  */
#line 454 "parser.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 2102 ".//parser.tab.c"
    break;

  case 66: /* operands: TK_IDENTIFICADOR  */
#line 458 "parser.y"
{
    DataType type = infer_type_from_identifier((yyvsp[0].valor_lexico));
    check_identifier_is_variable((yyvsp[0].valor_lexico));

    (yyval.node) = create_node_valor_lexico((yyvsp[0].valor_lexico), type);
}
#line 2113 ".//parser.tab.c"
    break;

  case 67: /* operands: literal  */
#line 465 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 2121 ".//parser.tab.c"
    break;

  case 68: /* operands: function_call  */
#line 469 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
}
#line 2129 ".//parser.tab.c"
    break;

  case 69: /* type: TK_PR_INT  */
#line 475 "parser.y"
{
    declared_type = DATA_TYPE_INT;
    (yyval.node) = DATA_TYPE_INT;
}
#line 2138 ".//parser.tab.c"
    break;

  case 70: /* type: TK_PR_FLOAT  */
#line 480 "parser.y"
{
    declared_type = DATA_TYPE_FLOAT;
    (yyval.node) = DATA_TYPE_FLOAT;
}
#line 2147 ".//parser.tab.c"
    break;

  case 71: /* type: TK_PR_BOOL  */
#line 485 "parser.y"
{
    declared_type = DATA_TYPE_BOOL;
    (yyval.node) = DATA_TYPE_BOOL;
}
#line 2156 ".//parser.tab.c"
    break;

  case 72: /* literal: TK_LIT_INT  */
#line 492 "parser.y"
{
    (yyval.node) = create_node_valor_lexico((yyvsp[0].valor_lexico), DATA_TYPE_INT);
}
#line 2164 ".//parser.tab.c"
    break;

  case 73: /* literal: TK_LIT_FLOAT  */
#line 496 "parser.y"
{
    (yyval.node) = create_node_valor_lexico((yyvsp[0].valor_lexico), DATA_TYPE_FLOAT);
}
#line 2172 ".//parser.tab.c"
    break;

  case 74: /* literal: TK_LIT_TRUE  */
#line 500 "parser.y"
{
    (yyval.node) = create_node_valor_lexico((yyvsp[0].valor_lexico), DATA_TYPE_BOOL);
    TableEntryValue value = create_table_entry_value(SYMBOL_NATURE_LITERAL, DATA_TYPE_BOOL, (yyvsp[0].valor_lexico));
    add_symbol_value_to_global_table_stack(value);
}
#line 2182 ".//parser.tab.c"
    break;

  case 75: /* literal: TK_LIT_FALSE  */
#line 506 "parser.y"
{
    (yyval.node) = create_node_valor_lexico((yyvsp[0].valor_lexico), DATA_TYPE_BOOL);
    TableEntryValue value = create_table_entry_value(SYMBOL_NATURE_LITERAL, DATA_TYPE_BOOL, (yyvsp[0].valor_lexico));
    add_symbol_value_to_global_table_stack(value);
}
#line 2192 ".//parser.tab.c"
    break;


#line 2196 ".//parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 511 "parser.y"


// Função que imprime na tela o erro encontrado.
void yyerror(char const *message)
{
    printf("Erro Sintático encontrado na linha %d: %s\n", get_line_number(), message);
}
