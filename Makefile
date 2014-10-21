all:
		cd src; $(MAKE) $(MFLAGS)

clean:
		cd src; $(MAKE) clean
		
cleandisk:
		rm bootdisk/nebula.img

bootdisk: all
		scripts/install_to_bootdisk

bochs: bootdisk
		scripts/run_bochs
