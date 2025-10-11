/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_PSL_YY_CODE_NUSMV_CORE_PARSER_PSL_PSL_GRAMMAR_H_INCLUDED
# define YY_PSL_YY_CODE_NUSMV_CORE_PARSER_PSL_PSL_GRAMMAR_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int psl_yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TKEOF = 258,                   /* "eof"  */
    TKSTRING = 259,                /* "string"  */
    TKERROR = 260,                 /* TKERROR  */
    TKSTRUCT = 261,                /* "struct"  */
    TKNUMBER = 262,                /* "number"  */
    TKREALNUMBER = 263,            /* "real number"  */
    TKWORDNUMBER = 264,            /* "word number"  */
    TKBASENUMBER = 265,            /* "based number"  */
    TKTRUE = 266,                  /* TKTRUE  */
    TKFALSE = 267,                 /* TKFALSE  */
    TKUNSIGNEDWORDNUMBER = 268,    /* TKUNSIGNEDWORDNUMBER  */
    TKSIGNEDWORDNUMBER = 269,      /* TKSIGNEDWORDNUMBER  */
    TKINCONTEXT = 270,             /* TKINCONTEXT  */
    TKEQDEF = 271,                 /* TKEQDEF  */
    TKNAME = 272,                  /* TKNAME  */
    TKSERE = 273,                  /* TKSERE  */
    TKSERECONCAT = 274,            /* TKSERECONCAT  */
    TKSEREFUSION = 275,            /* TKSEREFUSION  */
    TKSERECOMPOUND = 276,          /* TKSERECOMPOUND  */
    TKSEREREPEATED = 277,          /* TKSEREREPEATED  */
    TKCONS = 278,                  /* TKCONS  */
    TKCONCATENATION = 279,         /* TKCONCATENATION  */
    TKREPLPROP = 280,              /* TKREPLPROP  */
    TKARRAY = 281,                 /* TKARRAY  */
    TKCONTEXT = 282,               /* TKCONTEXT  */
    TKATOM = 283,                  /* TKATOM  */
    TKFAILURE = 284,               /* TKFAILURE  */
    TKITE = 285,                   /* TKITE  */
    TKVUNIT = 286,                 /* "vunit"  */
    TKVMODE = 287,                 /* "vmode"  */
    TKVPROP = 288,                 /* "vprop"  */
    TKSTRONG = 289,                /* "strong"  */
    TKDEFPARAM = 290,              /* "defparam"  */
    TKINHERIT = 291,               /* "inherit"  */
    TKFAIRNESS = 292,              /* "fairness"  */
    TKCONST = 293,                 /* "const"  */
    TKBEGIN = 294,                 /* "begin"  */
    TKEND = 295,                   /* "end"  */
    TKPARAMETER = 296,             /* "parameter"  */
    TKTASK = 297,                  /* "task"  */
    TKENDTASK = 298,               /* "endtask"  */
    TKFORK = 299,                  /* "fork"  */
    TKJOIN = 300,                  /* "join"  */
    TKSUPPLY0 = 301,               /* "supply0"  */
    TKSUPPLY1 = 302,               /* "supply1"  */
    TKSTRONG0 = 303,               /* "strong0"  */
    TKPULL0 = 304,                 /* "pull0"  */
    TKWEAK0 = 305,                 /* "weak0"  */
    TKHIGHZ0 = 306,                /* "highz0"  */
    TKSTRONG1 = 307,               /* "strong1"  */
    TKPULL1 = 308,                 /* "pull1"  */
    TKWEAK1 = 309,                 /* "weak1"  */
    TKHIGHZ1 = 310,                /* "highz1"  */
    TKINPUT = 311,                 /* "input"  */
    TKOUTPUT = 312,                /* "output"  */
    TKINOUT = 313,                 /* "inout"  */
    TKDEFAULT_CLOCK = 314,         /* "default clock"  */
    TKDEFAULT_COLON = 315,         /* "default"  */
    TKDEASSIGN = 316,              /* "deassign"  */
    TKDISABLE = 317,               /* "disable"  */
    TKENDSPECIFY = 318,            /* "endspecify"  */
    TKFOR = 319,                   /* "for"  */
    TKINITIAL = 320,               /* "initial"  */
    TKSPECIFY = 321,               /* "specify"  */
    TKWAIT = 322,                  /* "wait"  */
    TKFOREVER = 323,               /* "forever"  */
    TKREPEAT = 324,                /* "repeat"  */
    TKWHILE = 325,                 /* "while"  */
    TKENDMODULE = 326,             /* "endmodule"  */
    TKENDFUNCTION = 327,           /* "endfunction"  */
    TKWIRE = 328,                  /* "wire"  */
    TKTRI = 329,                   /* "tri"  */
    TKTRI1 = 330,                  /* "try1"  */
    TKWAND = 331,                  /* "wand"  */
    TKTRIAND = 332,                /* "triand"  */
    TKTRI0 = 333,                  /* "tri0"  */
    TKWOR = 334,                   /* "wor"  */
    TKTRIOR = 335,                 /* "trior"  */
    TKTRIREG = 336,                /* "trireg"  */
    TKREG = 337,                   /* "reg"  */
    TKINTEGER = 338,               /* "integer"  */
    TKINF = 339,                   /* "inf"  */
    TKDOT = 340,                   /* "dot"  */
    TKENDPOINT = 341,              /* "endpoint"  */
    TKASSIGN = 342,                /* "assign"  */
    TKFORCE = 343,                 /* "force"  */
    TKRELEASE = 344,               /* "release"  */
    TKPROPERTY = 345,              /* "property"  */
    TKSEQUENCE = 346,              /* "sequence"  */
    TKMODULE = 347,                /* "module"  */
    TKFUNCTION = 348,              /* "function"  */
    TKRESTRICT = 349,              /* "restrict"  */
    TKRESTRICT_GUARANTEE = 350,    /* "restrict_guarantee"  */
    TKFORALL = 351,                /* "forall"  */
    TKFORANY = 352,                /* "forany"  */
    TKASSERT = 353,                /* "assert"  */
    TKASSUME = 354,                /* "assume"  */
    TKASSUME_GUARANTEE = 355,      /* "assume_guarantee"  */
    TKCOVER = 356,                 /* "cover"  */
    TKBOOLEAN = 357,               /* "boolean"  */
    TKCASE = 358,                  /* "case"  */
    TKCASEX = 359,                 /* "casex"  */
    TKCASEZ = 360,                 /* "casez"  */
    TKELSE = 361,                  /* "else"  */
    TKENDCASE = 362,               /* "esac"  */
    TKIF = 363,                    /* "if"  */
    TKNONDET = 364,                /* "$nondet"  */
    TKNONDET_VECTOR = 365,         /* "$nondet_vector"  */
    TKNONDET_RANGE = 366,          /* "$nondet_range"  */
    TKWNONDET = 367,               /* "$wnondet"  */
    TKBASE = 368,                  /* TKBASE  */
    TKDOTDOT = 369,                /* ".."  */
    TKPIPEMINUSGT = 370,           /* "|->"  */
    TKPIPEEQGT = 371,              /* "|=>"  */
    TKIDENTIFIER = 372,            /* "identifier"  */
    TKHIERARCHICALID = 373,        /* TKHIERARCHICALID  */
    TKLP = 374,                    /* "("  */
    TKRP = 375,                    /* ")"  */
    TKLC = 376,                    /* "{"  */
    TKRC = 377,                    /* "}"  */
    TKLB = 378,                    /* "["  */
    TKRB = 379,                    /* "]"  */
    TKCOMMA = 380,                 /* ","  */
    TKDIEZ = 381,                  /* "#"  */
    TKTRANS = 382,                 /* "trans"  */
    TKHINT = 383,                  /* "hint"  */
    TKTEST_PINS = 384,             /* "test_pins"  */
    TKALWAYS = 385,                /* "always"  */
    TKNEVER = 386,                 /* "never"  */
    TKEVENTUALLYBANG = 387,        /* "eventually!"  */
    TKWITHINBANG = 388,            /* "within!"  */
    TKWITHIN = 389,                /* "within"  */
    TKWITHINBANG_ = 390,           /* "within!_"  */
    TKWITHIN_ = 391,               /* "within_"  */
    TKWHILENOTBANG = 392,          /* "whilenot!"  */
    TKWHILENOT = 393,              /* "whilenot"  */
    TKWHILENOTBANG_ = 394,         /* "whilenot!_"  */
    TKWHILENOT_ = 395,             /* "whilenot_"  */
    TKNEXT_EVENT_ABANG = 396,      /* "next_event_a!"  */
    TKNEXT_EVENT_A = 397,          /* "next_event_a"  */
    TKNEXT_EVENT_EBANG = 398,      /* "next_event_e!"  */
    TKNEXT_EVENT_E = 399,          /* "next_event_e"  */
    TKNEXT_EVENTBANG = 400,        /* "next_event!"  */
    TKNEXT_EVENT = 401,            /* "next_event"  */
    TKNEXT_ABANG = 402,            /* "next_a!"  */
    TKNEXT_EBANG = 403,            /* "next_e!"  */
    TKNEXT_A = 404,                /* "next_a"  */
    TKNEXT_E = 405,                /* "next_e"  */
    TKNEXTBANG = 406,              /* "next!"  */
    TKNEXT = 407,                  /* "next"  */
    TKNEXTfunc = 408,              /* "next (function)"  */
    TKBEFOREBANG = 409,            /* "before!"  */
    TKBEFORE = 410,                /* "before"  */
    TKBEFOREBANG_ = 411,           /* "before!_"  */
    TKBEFORE_ = 412,               /* "before_"  */
    TKUNTILBANG = 413,             /* "until!"  */
    TKUNTIL = 414,                 /* "until"  */
    TKUNTILBANG_ = 415,            /* "until!_"  */
    TKUNTIL_ = 416,                /* "until_"  */
    TKABORT = 417,                 /* "abort"  */
    TKROSE = 418,                  /* "rose"  */
    TKFELL = 419,                  /* "fell"  */
    TKPREV = 420,                  /* "prev"  */
    TKG = 421,                     /* "G"  */
    TKXBANG = 422,                 /* "X!"  */
    TKX = 423,                     /* "X"  */
    TKF = 424,                     /* "F"  */
    TKU = 425,                     /* "U"  */
    TKW = 426,                     /* "W"  */
    TKEG = 427,                    /* "EG"  */
    TKEX = 428,                    /* "EX"  */
    TKEF = 429,                    /* "EF"  */
    TKAG = 430,                    /* "AG"  */
    TKAX = 431,                    /* "AX"  */
    TKAF = 432,                    /* "AF"  */
    TKA = 433,                     /* "A"  */
    TKE = 434,                     /* "E"  */
    TKIN = 435,                    /* "in"  */
    TKUNION = 436,                 /* "union"  */
    TKQUESTIONMARK = 437,          /* "?"  */
    TKCOLON = 438,                 /* ":"  */
    TKSEMI = 439,                  /* ";"  */
    TKPIPEPIPE = 440,              /* "||"  */
    TKAMPERSANDAMPERSAND = 441,    /* "&&"  */
    TKMINUSGT = 442,               /* "->"  */
    TKLTMINUSGT = 443,             /* "<->"  */
    TKPIPE = 444,                  /* "|"  */
    TKTILDEPIPE = 445,             /* "~|"  */
    TKOR = 446,                    /* "or"  */
    TKPOSEDGE = 447,               /* "posedge"  */
    TKNEGEDGE = 448,               /* "negedge"  */
    TKCARET = 449,                 /* "^"  */
    TKXOR = 450,                   /* "xor"  */
    TKXNOR = 451,                  /* "xnor"  */
    TKCARETTILDE = 452,            /* "^~"  */
    TKTILDECARET = 453,            /* "~^"  */
    TKAMPERSAND = 454,             /* "&"  */
    TKTILDEAMPERSAND = 455,        /* "~&"  */
    TKEQEQ = 456,                  /* "=="  */
    TKBANGEQ = 457,                /* "!="  */
    TKEQEQEQ = 458,                /* "==="  */
    TKBANGEQEQ = 459,              /* "!=="  */
    TKEQ = 460,                    /* "="  */
    TKGT = 461,                    /* ">"  */
    TKGE = 462,                    /* ">="  */
    TKLT = 463,                    /* "<"  */
    TKLE = 464,                    /* "<="  */
    TKLTLT = 465,                  /* "<<"  */
    TKGTGT = 466,                  /* ">>"  */
    TKWSELECT = 467,               /* "select"  */
    TKGTGTGT = 468,                /* ">>>"  */
    TKLTLTLT = 469,                /* "<<<"  */
    TKPLUS = 470,                  /* "+"  */
    TKMINUS = 471,                 /* "-"  */
    TKSPLAT = 472,                 /* "*"  */
    TKSLASH = 473,                 /* "/"  */
    TKPERCENT = 474,               /* "mod"  */
    TKSPLATSPLAT = 475,            /* "**"  */
    TKBANG = 476,                  /* "!"  */
    TKTILDE = 477,                 /* "~"  */
    TKLBSPLAT = 478,               /* "[*"  */
    TKLBEQ = 479,                  /* "[="  */
    TKLBMINUSGT = 480,             /* "[->"  */
    TKLBPLUSRB = 481,              /* "[+]"  */
    TKWCONCATENATION = 482,        /* "::"  */
    TKBOOL = 483,                  /* "bool"  */
    TKWRESIZE = 484,               /* "resize"  */
    TKWSIZEOF = 485,               /* "sizeof"  */
    TKWTOINT = 486,                /* "toint"  */
    TKUWCONST = 487,               /* "uwconst"  */
    TKBITSELECTION = 488,          /* "bit selection"  */
    TKUMINUS = 489,                /* "unary minus"  */
    TKSWCONST = 490,               /* "swconst"  */
    TKWORD1 = 491,                 /* "word1"  */
    TKSIGNED = 492,                /* "signed"  */
    TKUNSIGNED = 493,              /* "unsigned"  */
    TKEXTEND = 494,                /* "extend"  */
    TKSTRUDLE = 495,               /* "@"  */
    TKSEREFORGR = 496,             /* "grsequence"  */
    TKPSLSPEC = 497                /* "PSLSPEC"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 64 "../code/nusmv/core/parser/psl/psl_grammar.y"

  node_ptr node;
  int lineno;

  /* these are news */
  int ival;
  char* wval;
  char* fval;
  char* baseval;
  char* idname;
  PslExpr psl_expr;
  PslOp operator;

#line 320 "code/nusmv/core/parser/psl/psl_grammar.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE psl_yylval;


int psl_yyparse (void);


#endif /* !YY_PSL_YY_CODE_NUSMV_CORE_PARSER_PSL_PSL_GRAMMAR_H_INCLUDED  */
