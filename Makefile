TM_FILE = ./libft/tm.mk
FTST_MAKE = ./libft/ftst/ftst.mk

#######################################################
#
#			libft setup
#
include libft/libft.mk
LIBFT_DIR = libft/

СС	= clang
#######################################################
#
#			MINISHELL build
#

SRCS		=	./srcs/parser/dfa_arg.c \
				./srcs/parser/dfa_part1.c \
				./srcs/parser/parser.c \
				./srcs/main.c

RELEASE_MAKE = ./release.mk
ms/%:
		${MAKE} -f ${RELEASE_MAKE} ${@:ms/%=%} ${addprefix MSRCS+=, ${SRCS}}

DEBUG_MAKE = ./debug.mk
db/%:
		${MAKE} -f ${DEBUG_MAKE} ${@:db/%=%} ${addprefix MSRCS+=, ${SRCS}}

#######################################################

.PHONY:	all
all:		ms/build

${NAME}:	all

.PHONY:	clean
clean:		ms/clean

.PHONY:	fclean
fclean:		ms/fclean

.PHONY:	norm
norm:		ms/norm

.PHONY:	re
re:			ms/re
