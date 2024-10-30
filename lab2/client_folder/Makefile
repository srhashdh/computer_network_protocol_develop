# 編譯器
CC = gcc


# 可執行檔名稱
TARGET = client

# 源碼文件
SRCS = client.c loggin_toServer.c broadcast_fromServer.c cJSON.c

# 目標文件
OBJS = $(SRCS:.c=.o)

.PHONY: all clean run

# 編譯目標
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $@ $^

run: $(TARGET)
	./$(TARGET)

# 清理生成的檔案
clean:
	rm -f $(OBJS) $(TARGET)
