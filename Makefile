TM_FILE = ./libft/tm.mk
FTST_MAKE = ./libft/ftst/ftst.mk

#######################################################
#
#			libft setup
#
include libft/libft.mk
LIBFT_DIR = libft/

#######################################################
#
#			MINISHELL build
#
NAME            = minishell
BUILD_NAME      = release
BUILD_DIR       = .release/
NAME_EXE        = minishell
PATH_EXE        = minishell
TARGET_TYPE     = exe
INC_DIR         =
FLAGS          += -O2 -fomit-frame-pointer
LIBS           += -lreadline
LIBS_DIRS      +=
SRCS           += ./main.c
IS_FTST         = 0
FTST_SRCS      +=
DEPEND_FILES   += ./Makefile


SETUP    =      ${addprefix BUILD_FLAGS+=, ${FLAGS}} \
                ${addprefix NAME=, ${NAME}} \
                ${addprefix BUILD_NAME=, ${BUILD_NAME}} \
                ${addprefix BUILD_TARGET_NAME=, ${NAME_EXE}} \
                ${addprefix BUILD_TARGET=, ${PATH_EXE}} \
                ${addprefix BUILD_DIR=, ${BUILD_DIR}} \
                ${addprefix BUILD_SRCS+=, ${SRCS}} \
                ${addprefix BUILD_INC_DIRS+=, ${INC_DIR}} \
                ${addprefix BUILD_LIBS_DIRS+=, ${LIBS_DIRS}} \
                ${addprefix BUILD_LIBS+=, ${LIBS}} \
                ${addprefix BUILD_IS_FTST=, ${IS_FTST}} \
                ${addprefix BUILD_DEPEND_FILES+=, ${DEPEND_FILES}} \
                ${addprefix FTST_SRCS+=, ${FTST_SRCS}} \
                ${addprefix BUILD_TARGET_TYPE=, ${TARGET_TYPE}}

ms/%:   lft/%
		${MAKE} -f ${TM_FILE} ${@:ms/%=%} ${SETUP}

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
re:			rems
