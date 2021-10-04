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

SRCS		=	${shell find ./srcs/parser/ -name '*.c'} \
				srcs/pipex/exit_me.c		\
				srcs/pipex/fork_cmd.c		\
				srcs/pipex/fork_heredoc.c	\
				srcs/pipex/run_pipeline.c	\
				./srcs/signal_handle.c		\
				./srcs/main.c

RELEASE_MAKE = ./release.mk
ms/%:
		${MAKE} -f ${RELEASE_MAKE} ${@:ms/%=%} ${addprefix MSRCS+=, ${SRCS}}

DEBUG_MAKE = ./debug.mk
db/%:
		${MAKE} -f ${DEBUG_MAKE} ${@:db/%=%} ${addprefix MSRCS+=, ${SRCS}}

#######################################################

.PHONY:	all
all:		db/build

${NAME}:	all

.PHONY:	clean
clean:		db/clean

.PHONY:	fclean
fclean:		db/fclean

.PHONY:	norm
norm:		db/norm

.PHONY:	re
re:			db/re
