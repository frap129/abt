#########################
## Makefile for ABT
#########################
version := 0.1
name    := Diamond is Unbreakable

# Environment Variables
local_flags := $(CFLAGS) $(cflags)
ifdef CC
  local_cc := $(CC)
else
  local_cc := gcc
endif

.PHONY: clean abt debug install install-debug
clean:
	@rm -f abt abt-debug $<
	@echo "Build files removed!" $<
  
abt: 
	@echo "Compiling..." $<
	@echo "" $<
	@$(local_cc) abt.c -O3 -g0 -Wno-unused-result $(local_flags) -o abt $<
	@echo "Done! Final Binary: ./abt" $<
  
debug: 
	@echo "Compiling..." $<
	@echo "" $<
	@$(local_cc) abt.c -g3 -Og $(local_flags) -o abt-debug $<
	@echo "Done! Final Binary: ./abt-debug" $<

install:
	@echo "Installing.." $<
	@echo "" $<
	@sudo mkdir -p /usr/local/bin $<
	@sudo cp abt /usr/bin/abt $<
	@echo "Done!" $<
	
install-debug:
	@echo "Installing..." $<
	@echo "" $<
	@sudo mkdir -p /usr/local/bin $<
	@sudo cp abt-debug /usr/bin/abt $<
	@echo "Done!" $<
	
