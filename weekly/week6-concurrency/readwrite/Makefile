SEM_DIR=../semaphore

all:
	gcc $(SEM_DIR)/semaphore.c $(SEM_DIR)/semaphore_queue.c \
		reader_writer_simple.c -o simple.o	\
		-I$(SEM_DIR)
	gcc $(SEM_DIR)/semaphore.c $(SEM_DIR)/semaphore_queue.c \
		reader_writer_writeprior.c -o writeprior.o	\
		-I$(SEM_DIR)
1st:
	gcc $(SEM_DIR)/semaphore.c $(SEM_DIR)/semaphore_queue.c \
		rw_1stclass.c -o rw_1stclass.o	\
		-I$(SEM_DIR)
2nd:
	gcc $(SEM_DIR)/semaphore.c $(SEM_DIR)/semaphore_queue.c \
		rw_2ndclass.c -o rw_2ndclass.o	\
		-I$(SEM_DIR)

