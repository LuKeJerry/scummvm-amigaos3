/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UNARY = 258,
     vCASTREF = 259,
     vVOID = 260,
     vVAR = 261,
     vPOINT = 262,
     vRECT = 263,
     vARRAY = 264,
     vSYMBOL = 265,
     vINT = 266,
     vTHEENTITY = 267,
     vTHEENTITYWITHID = 268,
     vFLOAT = 269,
     vBLTIN = 270,
     vBLTINNOARGS = 271,
     vSTRING = 272,
     vHANDLER = 273,
     ID = 274,
     tDOWN = 275,
     tELSE = 276,
     tNLELSIF = 277,
     tEND = 278,
     tEXIT = 279,
     tFRAME = 280,
     tGLOBAL = 281,
     tGO = 282,
     tIF = 283,
     tINTO = 284,
     tLOOP = 285,
     tMACRO = 286,
     tMCI = 287,
     tMCIWAIT = 288,
     tMOVIE = 289,
     tNEXT = 290,
     tOF = 291,
     tPREVIOUS = 292,
     tPUT = 293,
     tREPEAT = 294,
     tSET = 295,
     tTHEN = 296,
     tTO = 297,
     tWHEN = 298,
     tWITH = 299,
     tWHILE = 300,
     tNLELSE = 301,
     tFACTORY = 302,
     tMETHOD = 303,
     tALERT = 304,
     tBEEP = 305,
     tGE = 306,
     tLE = 307,
     tGT = 308,
     tLT = 309,
     tEQ = 310,
     tNEQ = 311,
     tAND = 312,
     tOR = 313,
     tNOT = 314,
     tCONCAT = 315,
     tCONTAINS = 316,
     tSTARTS = 317,
     tSPRITE = 318,
     tINTERSECTS = 319,
     tWITHIN = 320
   };
#endif
/* Tokens.  */
#define UNARY 258
#define vCASTREF 259
#define vVOID 260
#define vVAR 261
#define vPOINT 262
#define vRECT 263
#define vARRAY 264
#define vSYMBOL 265
#define vINT 266
#define vTHEENTITY 267
#define vTHEENTITYWITHID 268
#define vFLOAT 269
#define vBLTIN 270
#define vBLTINNOARGS 271
#define vSTRING 272
#define vHANDLER 273
#define ID 274
#define tDOWN 275
#define tELSE 276
#define tNLELSIF 277
#define tEND 278
#define tEXIT 279
#define tFRAME 280
#define tGLOBAL 281
#define tGO 282
#define tIF 283
#define tINTO 284
#define tLOOP 285
#define tMACRO 286
#define tMCI 287
#define tMCIWAIT 288
#define tMOVIE 289
#define tNEXT 290
#define tOF 291
#define tPREVIOUS 292
#define tPUT 293
#define tREPEAT 294
#define tSET 295
#define tTHEN 296
#define tTO 297
#define tWHEN 298
#define tWITH 299
#define tWHILE 300
#define tNLELSE 301
#define tFACTORY 302
#define tMETHOD 303
#define tALERT 304
#define tBEEP 305
#define tGE 306
#define tLE 307
#define tGT 308
#define tLT 309
#define tEQ 310
#define tNEQ 311
#define tAND 312
#define tOR 313
#define tNOT 314
#define tCONCAT 315
#define tCONTAINS 316
#define tSTARTS 317
#define tSPRITE 318
#define tINTERSECTS 319
#define tWITHIN 320




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 69 "engines/director/lingo/lingo-gr.y"
{
	Common::String *s;
	int i;
	double f;
	int e[2];	// Entity + field
	int code;
	int narg;	/* number of arguments */
	Common::Array<double> *arr;
}
/* Line 1529 of yacc.c.  */
#line 189 "engines/director/lingo/lingo-gr.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

