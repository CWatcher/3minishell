TM_FILE = ./libft/tm.mk
include libft/libft.mk

#######################################################
#
# Release build
#
NAME            = minishell
BUILD_NAME      = debug
BUILD_DIR       = .debug/
NAME_EXE        = minishell
PATH_EXE        = minishell
TARGET_TYPE     = exe
INC_DIR         = ${LIBFT_INC} srcs/ ${HOME}/.brew/Cellar/readline/8.1.1/include
FLAGS          += -Wpedantic -O0 -g3 -fsanitize=address
LIBS           += -lreadline ${LIBFT_LIB}
LIBS_DIRS      += ${LIBFT_DB_LIB_DIR} ${HOME}/.brew/Cellar/readline/8.1.1/lib
IS_FTST         = 0
DEPEND_FILES   += ./Makefile ./debug.mk


SETUP    =      ${addprefix BUILD_FLAGS+=, ${FLAGS}} \
                ${addprefix NAME=, ${NAME}} \
                ${addprefix BUILD_NAME=, ${BUILD_NAME}} \
                ${addprefix BUILD_TARGET_NAME=, ${NAME_EXE}} \
                ${addprefix BUILD_TARGET=, ${PATH_EXE}} \
                ${addprefix BUILD_DIR=, ${BUILD_DIR}} \
                ${addprefix BUILD_SRCS+=, ${MSRCS}} \
                ${addprefix BUILD_INC_DIRS+=, ${INC_DIR}} \
                ${addprefix BUILD_LIBS_DIRS+=, ${LIBS_DIRS}} \
                ${addprefix BUILD_LIBS+=, ${LIBS}} \
                ${addprefix BUILD_IS_FTST=, ${IS_FTST}} \
                ${addprefix BUILD_DEPEND_FILES+=, ${DEPEND_FILES}} \
                ${addprefix FTST_SRCS+=, ${FTST_SRCS}} \
                ${addprefix BUILD_TARGET_TYPE=, ${TARGET_TYPE}}

%:		lftdb/%
		${MAKE} -f ${TM_FILE} $@ ${SETUP}
