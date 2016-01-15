#########################
## Makefile for ABT
#########################
version := 1.0
name    := But C isn't

.PHONY: install
install:
	@echo "Installing.." $<
	@echo "" $<
	@sudo mkdir -p /usr/local/bin $<
	@sudo cp abt /usr/bin/abt $<
	@echo "Done!" $<
