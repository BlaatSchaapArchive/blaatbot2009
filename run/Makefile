.PHONY: debug release

DEBUGPATH=out/gcc/linux/x86_64/debug/
ROOTPATH=$(PWD)/../
debug:
	rm -rf debug
	make -C $(ROOTPATH)
	make -C $(ROOTPATH)/protocols
	make -C $(ROOTPATH)/clients
	make -C $(ROOTPATH)/clients/botmodules
	mkdir -p debug/protocols
	mkdir -p debug/clients
	mkdir -p debug/clients/botmodules
	ln -s $(ROOTPATH)/$(DEBUGPATH)/blaatbot2025 debug
	ln -s $(ROOTPATH)/protocols/$(DEBUGPATH)/libirc.so debug/protocols
	ln -s $(ROOTPATH)/clients/$(DEBUGPATH)/libbot.so debug/clients
	ln -s $(ROOTPATH)/clients/botmodules/$(DEBUGPATH)/libtest.so debug/clients/botmodules
	ln -s $(ROOTPATH)/config.xml debug
