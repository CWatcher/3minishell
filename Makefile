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
				./srcs/pipex/ft_perror.c		\
				./srcs/pipex/fork_cmd.c			\
				./srcs/pipex/fork_heredoc.c		\
				./srcs/pipex/run_pipeline.c		\
				./srcs/pipex/run_builtin.c		\
				./srcs/pipex/open_redirs.c		\
				./srcs/builtins/find_builtin.c	\
				./srcs/builtins/ms_cd.c			\
				./srcs/builtins/ms_echo.c		\
				./srcs/builtins/ms_exit.c		\
				./srcs/builtins/ms_export.c		\
				./srcs/builtins/ms_pwd.c		\
				./srcs/builtins/ms_unset.c		\
				./srcs/builtins/ms_env.c		\
				./srcs/builtins/update_shlvl.c	\
				./srcs/signal_handle.c			\
				./srcs/ms_perror.c				\
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
