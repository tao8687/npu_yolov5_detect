-include $(POLARIS_TOP)/build/Makefile.param


COMMON_DIR:=$(PWD)/../comm/
SYSLIBINC += $(POLARIS_INSTALL_LIB)
CFLAGS += -I $(SYSLIBINC)
SYSLIBINC += -I $(PWD)/../include/  -I $(COMMON_DIR)  -I $(POLARIS_INSTALL_CHIP_LIB_INC)/syslib/ 

COMM_SRC := $(wildcard $(COMMON_DIR)/*.cpp)
COMM_OBJ := $(COMM_SRC:%.cpp=%.o)
CC := $(CROSS_COMPILE)g++
STRIP=$(CROSS_COMPILE)strip
SRC  := $(wildcard *.c) 
OBJ  := $(SRC:%.c=%.o)
LDFLAGS += -L $(POLARIS_INSTALL_LIB) 
LDFLAGS += -lnpu  -lm -lpthread  -lnpu_alg -lstdc++ -lpthread -lc

CFLAGS += -DARM_LINUX 
TARGET := sample_yolov5
all:  $(TARGET) $(OBJ) $(COMM_OBJ)

$(OBJ): %.o: %.c
	$(CC) -Wall -O3 -c $< -o $@ $(CFLAGS) 
$(COMM_OBJ): %.o:%.cpp
	$(CC) -Wall -c $< -o $@  $(CFLAGS)
$(TARGET):  $(COMM_OBJ) $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS) $(LDFLAGS)
	$(STRIP) $(TARGET)	
install:all
	install -d $(POLARIS_INSTALL_APP)/npu_sample/yolov5/
	install -d $(POLARIS_INSTALL_CHIP_LIB_INC)/npu/
	@cp -fav $(TARGET) $(POLARIS_INSTALL_APP)/npu_sample/yolov5/
	@cp -fav ../include/*  $(POLARIS_INSTALL_CHIP_LIB_INC)/npu/
	@cp -fav ./bin_data/      $(POLARIS_INSTALL_APP)/npu_sample/yolov5/
	@cp -fav ./model/      $(POLARIS_INSTALL_APP)/npu_sample/yolov5/

clean:
	@rm -f $(TARGET)
	@rm -f $(OBJ)
	@rm -f $(COMM_OBJ)
