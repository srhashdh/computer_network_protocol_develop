# 編譯器
CC = gcc


# 可執行檔名稱
TARGET = server

# 源碼文件
SRCS = server.c connect_toClients.c handle_admin_input.c display_online_clients.c broadcast_toClients.c handle_clientRequest.c send_showListToClient.c loggin.c cJSON.c

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
