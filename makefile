ODIR = obj
BUILD_DIR = build
BONUS_DIR = bonus

SERVER_SRCS = server.c utils.c
SERVER_OBJS = ${patsubst %.c, ${ODIR}/%.o, ${SERVER_SRCS}}
CLIENT_SRCS = client.c utils.c
CLIENT_OBJS = ${patsubst %.c, ${ODIR}/%.o, ${CLIENT_SRCS}}

SERVER_SRCS_BONUS = ${BONUS_DIR}/server_bonus.c ${BONUS_DIR}/utils_bonus.c
SERVER_OBJS_BONUS = ${patsubst %.c, ${ODIR}/%.o, ${SERVER_SRCS_BONUS}}
CLIENT_SRCS_BONUS = ${BONUS_DIR}/client_bonus.c ${BONUS_DIR}/utils_bonus.c
CLIENT_OBJS_BONUS = ${patsubst %.c, ${ODIR}/%.o, ${CLIENT_SRCS_BONUS}}

CC = cc
CC_FLAGS = -Wall -Werror -Wextra
RM = rm -rf

NAME = mintalk
SERVER_NAME = ${BUILD_DIR}/server
CLIENT_NAME = ${BUILD_DIR}/client
SERVER_BONUS_NAME = ${BUILD_DIR}/server_bonus
CLIENT_BONUS_NAME = ${BUILD_DIR}/client_bonus

${ODIR}/%.o: %.c utils.h
	@mkdir -p ${@D}
	${CC} ${CC_FLAGS} -c $< -o $@
${ODIR}/${BONUS_DIR}/%.o: %.c utils_bonus.h
	@mkdir -p ${@D}
	${CC} ${CC_FLAGS} -c $< -o $@

${NAME}: all
all: ${SERVER_NAME} ${CLIENT_NAME}
bonus: ${SERVER_BONUS_NAME} ${CLIENT_BONUS_NAME}

${SERVER_NAME}: ${SERVER_OBJS}
	@mkdir -p ${@D}
	${CC} ${CC_FLAGS} $^ -o $@
${CLIENT_NAME}: ${CLIENT_OBJS}
	@mkdir -p ${@D}
	${CC} ${CC_FLAGS} $^ -o $@
${SERVER_BONUS_NAME}: ${SERVER_OBJS_BONUS}
	@mkdir -p ${@D}
	${CC} ${CC_FLAGS} $^ -o $@
${CLIENT_BONUS_NAME}: ${CLIENT_OBJS_BONUS}
	@mkdir -p ${@D}
	${CC} ${CC_FLAGS} $^ -o $@


clean:
	${RM} ${ODIR}

fclean: clean
	${RM} ${BUILD_DIR}

re: fclean all

.PHONY: clean fclean re bonus all
