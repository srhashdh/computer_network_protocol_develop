# 編譯器
CC = gcc


# 可執行檔名稱
TARGET = client

# 源碼文件
SRCS = client.c loggin_toServer.c broadcast_fromServer.c handle_clientCommand.c request_listFromServer.c handle_serverResponse.c show_listFromServer.c request_battleFromServer.c battle_request.c battle.c battle_result.c cJSON.c

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
